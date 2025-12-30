# from __future__ import annotations

# import requests
# from typing import Any, Dict

# from config import TONAPI_BASE_URL, TONAPI_API_KEY


# def _headers() -> Dict[str, str]:
#     h: Dict[str, str] = {"Accept": "application/json"}
#     if TONAPI_API_KEY:
#         h["Authorization"] = f"Bearer {TONAPI_API_KEY}"
#     return h


# def _base_params() -> Dict[str, str]:
#     """
#     Общие GET/POST-параметры для TonAPI.
#     Явно говорим, что работаем с testnet.
#     """
#     return {"network": "testnet"}


# def get_balance(address: str) -> int:
#     """
#     Получить баланс аккаунта (в нанотонах) через TonAPI testnet.
#     """
#     url = f"{TONAPI_BASE_URL}/v2/accounts/{address}"
#     resp = requests.get(
#         url,
#         headers=_headers(),
#         params=_base_params(),
#         timeout=20,
#     )
#     resp.raise_for_status()
#     data: Dict[str, Any] = resp.json()
#     # TonAPI обычно возвращает {"balance": "2000000000", ...}
#     balance_str = data.get("balance", "0")
#     return int(balance_str)


# def get_seqno(address: str) -> int:
#     """
#     Получить seqno кошелька через TonAPI testnet.
#     """
#     url = f"{TONAPI_BASE_URL}/v2/wallet/{address}/seqno"
#     resp = requests.get(
#         url,
#         headers=_headers(),
#         params=_base_params(),
#         timeout=20,
#     )
#     resp.raise_for_status()
#     data: Dict[str, Any] = resp.json()
#     return int(data.get("seqno", 0))


# def send_boc(boc_b64: str) -> None:
#     """
#     Отправить произвольный BOC-сообщение в сеть через TonAPI testnet.
#     """
#     url = f"{TONAPI_BASE_URL}/v2/liteserver/send_message"
#     payload = {"boc": boc_b64}

#     print(f"BOC to send (len={len(boc_b64)}): {boc_b64[:80]}...")

#     resp = requests.post(
#         url,
#         headers=_headers(),
#         params=_base_params(),
#         json=payload,
#         timeout=20,
#     )

#     print("TonAPI HTTP status:", resp.status_code)
#     try:
#         print("TonAPI response body:", resp.json())
#     except Exception:
#         print("TonAPI raw response:", resp.text)

#     resp.raise_for_status()

from __future__ import annotations

import requests
from typing import Any, Dict

from config import TONAPI_BASE_URL, TONAPI_API_KEY


def _headers() -> Dict[str, str]:
    h: Dict[str, str] = {"Accept": "application/json"}
    if TONAPI_API_KEY:
        h["Authorization"] = f"Bearer {TONAPI_API_KEY}"
    return h


def _base_params() -> Dict[str, str]:
    """
    Общие параметры для всех запросов к TonAPI.
    Явно говорим, что работаем с testnet.
    """
    return {"network": "testnet"}


def get_balance(address: str) -> int:
    """
    Получить баланс аккаунта (в нанотонах) через TonAPI.
    """
    url = f"{TONAPI_BASE_URL}/v2/accounts/{address}"
    resp = requests.get(
        url,
        headers=_headers(),
        params=_base_params(),
        timeout=20,
    )
    resp.raise_for_status()
    data: Dict[str, Any] = resp.json()
    # TonAPI обычно возвращает {"balance": "2000000000", ...}
    balance_str = data.get("balance", "0")
    return int(balance_str)


def get_seqno(address: str) -> int:
    """
    Получить seqno кошелька через TonAPI.
    """
    url = f"{TONAPI_BASE_URL}/v2/wallet/{address}/seqno"
    resp = requests.get(
        url,
        headers=_headers(),
        params=_base_params(),
        timeout=20,
    )
    resp.raise_for_status()
    data: Dict[str, Any] = resp.json()
    return int(data.get("seqno", 0))


def send_boc(boc_b64: str) -> None:
    """
    Отправить произвольный BOC в сеть через TonAPI.
    """
    url = f"{TONAPI_BASE_URL}/v2/liteserver/send_message"
    payload = {
        "boc": boc_b64,
        "body": boc_b64,  # Дублируем поле "body", так как TonAPI может его требовать
    }

    print(f"BOC to send (len={len(boc_b64)}): {boc_b64[:80]}...")

    resp = requests.post(
        url,
        headers=_headers(),
        params=_base_params(),
        json=payload,
        timeout=60,
    )

    print("TonAPI HTTP status:", resp.status_code)
    try:
        print("TonAPI response body:", resp.json())
    except Exception:
        print("TonAPI raw response:", resp.text)

    resp.raise_for_status()

