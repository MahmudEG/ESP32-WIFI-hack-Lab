# ESP32-WROVER-E Wi-Fi Hack Lab Access Point

[![ESP-IDF Version](https://img.shields.io/badge/ESP--IDF-v5.4.1-blue)](https://docs.espressif.com/projects/esp-idf/en/v5.4.1/)
[![License](https://img.shields.io/badge/License-MIT-green)](LICENSE)

A configurable Wi-Fi Access Point (AP) for security testing labs, supporting **WPA/WPA2/WPA3-Personal** on ESP32-WROVER-E modules. Certified for WPA3 interoperability (WFA99981).

---

## Features
- ✅ Modern Security Protocols:
  - WPA-Personal (AES/TKIP)
  - WPA2-Personal (AES-CCMP)
  - WPA3-Personal (SAE/PMF)
- 🔧 Easy Configuration:
  - Custom SSID and password
  - Switch security modes via code macros
- 📶 2.4 GHz band support
- 🛠️ Compatible with ESP-IDF v5.4.1

---

## Prerequisites
### Hardware
- ESP32-WROVER-E module
- USB-to-Serial adapter (e.g., CP2102, CH340)

### Software
- [ESP-IDF v5.4.1](https://docs.espressif.com/projects/esp-idf/en/v5.4.1/)
- Python 3.11+
- [VS Code](https://code.visualstudio.com/) (recommended)

### Tools
- `esptool` (for flashing)
- Wi-Fi analyzer (e.g., `airodump-ng`, Wireshark)

---

## Getting Started
### 1. Clone the Repository
```bash
git clone https://github.com/MahmudEG/esp32-wifi-hack-lab.git
cd esp32-wifi-hack-lab
```

### 2. Set Up ESP-IDF Environment
Configure ESP-IDF for your OS:
```bash
. $HOME/esp/esp-idf/export.sh  # Linux/macOS
```

### 3. Configure the Project
Enable **WPA3 (SAE)** support:
```bash
idf.py menuconfig
```
Navigate to:  
`Component config → Wi-Fi → Enable SAE (WPA3-Personal)` and enable it.

### 4. Customize Settings
Modify `main/main.c`:
```c
#define AP_SSID       "HackLabAP"          // Change AP name
#define AP_PASSWORD   "password123"        // Set password (min 8 chars)
#define AP_SECURITY_MODE WIFI_AUTH_WPA2_PSK // Options: WIFI_AUTH_WPA_PSK, WIFI_AUTH_WPA2_PSK, WIFI_AUTH_WPA3_PSK
```

### 5. Build & Flash
```bash
idf.py build flash monitor
```

---

## Usage
1. Power on the ESP32.
2. Scan for Wi-Fi networks - `HackLabAP` (or your custom SSID) will appear.
3. Connect using the configured password and security protocol.
4. Use tools like `airodump-ng` or `Wireshark` for penetration testing.

---

## Notes
- **Certification**: Validated for WPA3-Personal (WFA99981).
- **Password Requirements**:
  - WPA/WPA2: 8-63 characters.
  - WPA3: 8-64 characters (supports stronger passphrases).
- **WEP**: Not supported (deprecated in ESP-IDF v5.x).

---

## Troubleshooting
| Error | Solution |
|-------|----------|
| `Failed to connect` | Ensure PMF is enabled for WPA3 in `menuconfig`. |
| `Build failed` | Clean build with `idf.py fullclean`. |
| `AP not visible` | Check ESP32 power and Wi-Fi channel (1-14). |

---

## Contributing
Pull requests are welcome! For major changes, open an issue first.

---

## License
[MIT](LICENSE)

### How to Use This README:
1. Save as `README.md` in your project root.
2. Replace `yourusername` in the clone URL with your GitHub username.
3. Update the [License](LICENSE) file if needed.
4. Customize the "Features" and "Notes" sections as desired.