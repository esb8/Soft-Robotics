# Soft Robotics PCB — ESP32 + Camera + Electromagnet Drivers

Electromagnet control, optical feedback, and vision on a single board.  
This project features a soft-robotics controller built around an ESP32 with an onboard camera, MOSFET/driver stages for multiple electromagnets, photoresistor sensing, SPI breakouts, and a UART header for easy flashing.


## Features
- **ESP32** (WROOM or WROVER) with **camera module** (OV2640 or similar)
- **4–8 electromagnet channels** with protected low-side MOSFET drivers (PWM capable)
- **Photoresistor (LDR) inputs** with RC dividers → ADC
- **SPI header** (3.3V) for add-ons (external ADCs, sensors, or LED drivers)
- **Dedicated UART header** for flashing (RTS/DTR optional) + **USB-C** or JST-PH power
- **Reverse-polarity & transient protection**, per-channel flyback/snubbers
- **Mounting + cable-reliefs** sized for soft-robotics rigs

## Suggested Parts (reference only)
- **ESP32 module:** ESP32-WROOM-32E (or ESP32-S3 if you want native camera lanes)
- **Camera:** OV2640 module (ESP32-CAM pinout compatible)
- **Drivers:** Logic-level N-MOSFETs (e.g., AO3400A/IRLML6344) or low-side driver ICs
- **Diodes:** Fast diodes per coil (SS14/SS24) or flyback array
- **Current sense:** 0.05–0.1 Ω shunts + op-amp (INA180/INA219 over I²C)
- **Photoresistors:** GL5528/VT90N2 + 10–100 kΩ divisor to 3.3 V (tune for range)
- **Regulation:** 2S LiPo input, 3.3 V 2.4 V and 1.8 V (LDO) for ESP32 & logic
- **Connectors:** JST-VH for magnets, JST-PH for I/O, 2×5 SPI, 1×6 UART


## Citation
If this helps your research or project, please cite this repository and star it 🌟
