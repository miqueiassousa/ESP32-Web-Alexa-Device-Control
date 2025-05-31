# Guia para Subir Projeto no ESP32 (SPIFFS + Código)

Este guia descreve o processo completo para subir os arquivos e o código no ESP32 usando PlatformIO.

---

## 🛠️ Passos para Subir o Projeto

### 1️⃣ Pré-requisitos

✅ Projeto criado com PlatformIO (`platformio.ini` configurado)  
✅ Arquivos web (`index.html`, `style.css`, `script.js`) dentro da pasta `data/`  
✅ Código fonte no `src/main.cpp`  
✅ ESP32 Dev Module selecionado no `platformio.ini`

---

## 🚀 Sequência de Passos

### 🧭 Antes de qualquer comando: **Coloque o ESP32 em modo boot**

1. **Pressione e segure o botão BOOT do ESP32**  
2. **Conecte o ESP32 via USB no computador**

---

### 📦 Subindo os arquivos e enviando para o ESP

```bash
pio run --target uploadfs # Subindo os arquivos da pasta `data/` (SPIFFS)
pio run --target upload # Subindo o código para o ESP32
```

🔄 Após o upload:
✅ Desconecte o cabo USB do ESP32
✅ Reconecte o cabo USB
✅ Pressione e solte o botão RESET do ESP32

🌐 Obtendo o IP do ESP32
Abra o monitor serial para ver o IP atribuído pelo WiFi:

```bash
pio device monitor
```

## Aguarde até aparecer algo como:

WiFi conectado!
192.168.x.x

