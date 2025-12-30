import base64
import json
from pathlib import Path

def make_meta(image_path: str) -> None:
    img = Path(image_path).read_bytes()
    meta_binary = {
        "name": "HotMonkey Token (BIN)",
        "symbol": "HMTB",
        "description": "Metadata with image stored as raw bytes array (binary representation).",
        "decimals": 9,

        "amount_style": "n-of-total",

        "image_bytes": list(img),
        "image_mime": "image/png",
    }
    b64 = base64.b64encode(img).decode("ascii")
    meta_base64 = {
        "name": "HotMonkey Token (B64)",
        "symbol": "HMTB",
        "description": "Metadata with image stored as base64 data URL.",
        "decimals": 9,

        "amount_style": "%",

        "image": f"data:image/png;base64,{b64}",
    }

    Path("jetton_meta_binary.json").write_text(json.dumps(meta_binary, ensure_ascii=False, indent=2), encoding="utf-8")
    Path("jetton_meta_base64.json").write_text(json.dumps(meta_base64, ensure_ascii=False, indent=2), encoding="utf-8")

    print("OK: jetton_meta_binary.json + jetton_meta_base64.json created")

if __name__ == "__main__":
    make_meta("assets/logo.png")
