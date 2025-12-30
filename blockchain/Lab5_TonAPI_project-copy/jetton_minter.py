from __future__ import annotations

from pathlib import Path
import json
import struct
import base64  # можно оставить, но тут не нужен
from tonsdk.contract.token.ft import JettonMinter, JettonWallet
from tonsdk.utils import Address, to_nano, bytes_to_b64str
import random
from tonsdk.boc import Cell
from tonsdk.utils import Address

from config import JETTON_CONTENT_URI, MINTER_ADDRESS_FILE
from wallet import wallet, wallet_address
from net import get_seqno, send_boc


def build_minter() -> JettonMinter:
    admin_addr = Address(wallet_address)

    wallet_code_cell = JettonWallet().create_code_cell()
    wallet_code_boc = wallet_code_cell.to_boc(False)
    wallet_code_hex = wallet_code_boc.hex()

    minter = JettonMinter(
        admin_address=admin_addr,
        jetton_content_uri=JETTON_CONTENT_URI,
        jetton_wallet_code_hex=wallet_code_hex,
    )
    return minter


def save_minter_address(addr: str) -> None:
    Path(MINTER_ADDRESS_FILE).write_text(addr, encoding="utf-8")


def load_minter_address() -> str:
    p = Path(MINTER_ADDRESS_FILE)
    if not p.exists():
        raise RuntimeError(
            f"Файл {MINTER_ADDRESS_FILE} не найден. Сначала запусти deploy_minter."
        )
    return p.read_text(encoding="utf-8").strip()


def deploy_minter() -> None:
    minter = build_minter()
    state_init_dict = minter.create_state_init()
    state_init = state_init_dict["state_init"]

    print(f"Admin wallet address: {wallet_address}")
    print(f"Jetton content URI: {JETTON_CONTENT_URI}")
    print(
        "Jetton minter address (calculated):",
        minter.address.to_string(True, True, True),
    )

    seqno = get_seqno(wallet_address)

    query = wallet.create_transfer_message(
        to_addr=minter.address.to_string(),
        amount=to_nano(0.05, "ton"),
        seqno=seqno,
        state_init=state_init,
    )

    boc = query["message"].to_boc(False)
    boc_b64 = bytes_to_b64str(boc)

    send_boc(boc_b64)

    minter_user_friendly = minter.address.to_string(True, True, True)
    save_minter_address(minter_user_friendly)
    print("Deploy-сообщение отправлено.")
    print("Адрес минтера сохранён в", MINTER_ADDRESS_FILE)


def mint_to_self(count: int = 1) -> None:
    """
    Минтим `count` джеттонов на СВОЙ кошелёк через уже задеплоенный минтер.
    Этот код у тебя уже работал — оставляем как есть.
    """
    minter = build_minter()

    minter_addr_str = load_minter_address()
    minter_addr = Address(minter_addr_str)

    destination = Address(wallet_address)

    jetton_amount = count * (10 ** 9)

    body = minter.create_mint_body(
        destination,
        jetton_amount,
    )

    seqno = get_seqno(wallet_address)

    query = wallet.create_transfer_message(
        to_addr=minter_addr.to_string(),
        amount=to_nano(0.05, "ton"),
        seqno=seqno,
        payload=body,
    )

    boc = query["message"].to_boc(False)
    boc_b64 = bytes_to_b64str(boc)

    send_boc(boc_b64)
    print(f"Запрос на минт {count} джеттонов на свой кошелёк отправлен.")
# ---------- до сюда — как было ----------


# ---------- НОВЫЕ transfer_jetton и burn_jetton ----------

def transfer_jetton(jetton_wallet_addr: str, to_owner_addr: str, count: int) -> None:
    """
    Трансфер jetton'ов с указанного jetton-кошелька на кошелёк другого владельца.
    ВАЖНО: jetton_wallet_addr — это АДРЕС JETTON-КОШЕЛЬКА (0Q...), а не обычный EQ-кошелёк.
    """
    # Сколько jetton'ов переводим (в nano-джеттонах)
    jetton_amount = count * (10 ** 9)

    # Формируем payload для JETTON TRANSFER.
    # ВАЖНО: JettonWallet() БЕЗ аргументов (как в примере с create_code_cell)
    payload = JettonWallet().create_transfer_body(
        Address(to_owner_addr),
        jetton_amount,
    )

    seqno = get_seqno(wallet_address)

    # Сообщение: наш кошелёк -> контракт jetton-кошелька
    query = wallet.create_transfer_message(
        to_addr=jetton_wallet_addr,          # адрес jetton-кошелька (строка 0Q...)
        amount=to_nano(0.05, "ton"),         # немного TON на газ
        seqno=seqno,
        payload=payload,                     # СЮДА кладём payload (Cell/bytes), НЕ строку
    )

    boc = query["message"].to_boc(False)
    boc_b64 = bytes_to_b64str(boc)

    send_boc(boc_b64)
    print(
        f"Запрос на трансфер {count} jetton'ов "
        f"({jetton_amount} nano-jetton) на адрес {to_owner_addr} отправлен."
    )

def burn_jetton(jetton_wallet_addr: str, amount: int) -> None:
    jetton_amount = amount * (10 ** 9)
    query_id = random.randint(1, 2**64 - 1)

    burn_body = JettonWallet().create_burn_body(
        jetton_amount,
        Address(wallet_address),
        query_id
    )

    seqno = get_seqno(wallet_address)

    query = wallet.create_transfer_message(
        to_addr=jetton_wallet_addr,        # адрес JETTON WALLET
        amount=to_nano(0.12, "ton"),       # дайте запас на газ
        seqno=seqno,
        payload=burn_body,
    )

    boc_b64 = bytes_to_b64str(query["message"].to_boc(False))
    send_boc(boc_b64)
    print(f"Burn отправлен: {amount} jetton, query_id={query_id}")

OP_CHANGE_ADMIN = 0x6501F354
OP_CLAIM_ADMIN  = 0xFB88E119

def _make_change_admin_body(new_admin_addr: str, query_id: int) -> Cell:
    c = Cell()
    c.bits.write_uint(OP_CHANGE_ADMIN, 32)
    c.bits.write_uint(query_id, 64)
    c.bits.write_address(Address(new_admin_addr))
    return c

def _make_claim_admin_body(query_id: int) -> Cell:
    c = Cell()
    c.bits.write_uint(OP_CLAIM_ADMIN, 32)
    c.bits.write_uint(query_id, 64)
    return c

def change_admin(new_admin_addr: str) -> None:
    minter_address = load_minter_address()

    minter = build_minter()
    body = minter.create_change_admin_body(
        Address(new_admin_addr),
        query_id=random.randint(1, 2**64 - 1)
    )

    seqno = get_seqno(wallet_address)

    query = wallet.create_transfer_message(
        to_addr=minter_address,
        amount=to_nano(0.07, "ton"),
        seqno=seqno,
        payload=body,
    )

    boc_b64 = bytes_to_b64str(query["message"].to_boc(False))
    send_boc(boc_b64)
    print(f"change_admin отправлен -> {new_admin_addr}")


async def claim_admin() -> None:
    minter_address = load_minter_address()
    seqno = get_seqno(wallet_address)
    qid = random.randint(1, 2**64 - 1)

    body = _make_claim_admin_body(qid)
    msg = wallet.create_transfer_message(
        to_addr=minter_address,
        amount=to_nano(0.07, "ton"),
        seqno=seqno,
        payload=body,
    )
    boc_b64 = bytes_to_b64str(msg["message"].to_boc(False))
    send_boc(boc_b64)
    print(f"claim_admin отправлен, query_id={qid}")
