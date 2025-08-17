# Discord-DHT-Monitoring
Monitoring Suhu dan Kelembaban secara Realtime dengan Bot Discord

# 📡 Discord-DHT-Monitor  
**ESP32 / Arduino** ➜ **DHT11** ➜ **Discord**  
> Pesan monitoring suhu & kelembaban **real-time** di Discord – **tanpa spam**, **hanya 1 pesan yang terus di-update**.

---

## ✨ Fitur
| Fitur | Penjelasan |
|---|---|
| **Real-time edit** | 1 pesan Discord yang otomatis di-edit setiap kali ada perubahan |
| **Rate-limit safe** | 5 detik / edit sesuai kebijakan Discord |
| **Multi-board** | ESP32, ESP8266, Arduino MKR WiFi |
| **Ringan** | < 8 kB RAM, tidak butuh server pihak ketiga |

---

## 🧰 Persiapan
| Item | Contoh nilai |
|---|---|
| Board | **ESP32 DevKit** atau **Wemos D1 Mini** |
| Sensor | **DHT11** (atau DHT22) |
| Library | `DHT.h`, `WiFiClientSecure`, `HTTPClient` |
| Akun Discord | **Webhook URL** + **Bot Token** |

---

## 📥 Instalasi Cepat
1. **Fork / clone repo ini**
   ```bash
   git clone https://github.com/YOUR_USERNAME/discord-dht-monitor.git
   cd discord-dht-monitor
   ```

2. **Install Arduino IDE**  
   - Board **ESP32** → `Tools → Board → ESP32 Dev Module`  
   - Library **DHT sensor** → Library Manager → cari **“DHT sensor library”**

3. **Upload sketch**
   - Buka `discord_dht_monitor.ino`
   - Sesuaikan **konfigurasi** (lihat bagian 🔧 di bawah)
   - **Upload** ke board.

---

## 🔧 Apa yang harus diganti?
| Baris | Ganti dengan | Cara mendapatkan |
|---|---|---|
| `ssid` & `password` | WiFi Anda | – |
| `webhookURL` | Webhook channel Anda | Channel → Settings → Integrations → Webhooks → Copy URL |
| `botToken` | Token bot Anda | [Discord Developer Portal](https://discord.com/developers/applications) → Bot → Token |
| `channelId` | ID channel (bukan nama) | Aktifkan **Developer Mode** → kanan-klik channel → Copy ID |
| `DHTPIN` | Pin sensor Anda | Contoh `4` untuk GPIO4 |
| `DHTTYPE` | `DHT11` atau `DHT22` | Sesuaikan sensor |

---

## 📤 Contoh pesan di Discord
```
📊 Real-time Monitoring
Suhu: 27.3 °C 🌡️
Kelembaban: 58.0 %
Diperbarui: 3 detik lalu
```
Pesan tersebut **akan otomatis di-refresh** setiap 5 detik tanpa spam.

---

## 🧪 Test di Terminal
Setelah upload, buka **Serial Monitor** 115200:
```
Connected to WiFi
Pesan awal terkirim, id=1234567890...
```
Jika muncul **“HTTP error 401”** → token salah / belum di-enable.  
Jika **“HTTP error 404”** → webhook URL salah.

---

## 🛠️ Troubleshooting
| Masalah | Solusi |
|---|---|
| Error HTTPS | Tambah `client.setInsecure()` (ESP32) atau pakai **WiFiClientSecureBearSSL** (ESP8266) |
| Timeout Discord | Pastikan board **terhubung internet** & **token aktif** |
| Sensor NaN | Periksa kabel DHT11 & resistor **10 kΩ pull-up** |

---

## 📄 Lisensi
MIT © 2025 – bebas dipakai untuk pribadi, komersial, maupun edukasi.

---

> 🎯 **1 pesan – 1 kali upload – monitoring sepanjang hari!**
