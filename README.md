# BonsaiStatistics
ESP32 Soil Moisture Monitor

An end-to-end IoT project to monitor soil moisture for a bonsai tree, built on an ESP32-S2 (Wemos/LOLIN S2 Mini). The goal is a device that lives outside on the patio, logs moisture readings over WiFi, and — eventually — automates watering based on those readings.

Status
This first commit is a basic LED blink sketch, used to confirm the full toolchain works end to end: Arduino IDE set up, board support installed, firmware successfully flashed over USB, and the onboard status LED (GPIO15) blinking as expected.

Nothing sensor-related yet — this is purely a "the pipeline works" checkpoint before building actual functionality.

Hardware
Board: Wemos/LOLIN S2 Mini v1.0.0 (ESP32-S2FN4R2 — single-core, WiFi only, native USB, 4MB flash / 2MB PSRAM in-package)
Sensor: Capacitive soil moisture sensor v1.2 (not yet wired in)
