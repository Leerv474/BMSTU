FROM python:3.10-slim

RUN apt-get update && apt-get install -y \
    git curl build-essential wget \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
RUN mkdir -p /app/ton_keystore
COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

COPY tonlibjson/ /app/tonlibjson/

COPY app.py .

CMD ["python", "app.py"]
