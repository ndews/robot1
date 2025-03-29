
#!/bin/bash
# Setup script for Ollama + Whisper STT server (Linux/macOS)

echo "Installing Ollama..."
curl -fsSL https://ollama.com/install.sh | sh

echo "Installing Python whisper server..."
pip install faster-whisper flask

cat <<EOF > stt_server.py
from flask import Flask, request, jsonify
from faster_whisper import WhisperModel
import tempfile

app = Flask(__name__)
model = WhisperModel("base")

@app.route("/stt", methods=["POST"])
def stt():
    with tempfile.NamedTemporaryFile(suffix=".wav", delete=False) as f:
        f.write(request.data)
        segments, _ = model.transcribe(f.name)
        text = " ".join([s.text for s in segments])
    return jsonify({"text": text})

app.run(host="0.0.0.0", port=8080)
EOF

echo "Done. Run STT server with:"
echo "  python stt_server.py"
