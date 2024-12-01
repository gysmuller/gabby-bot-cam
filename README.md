# Gabby Bot Camera

This project is for a camera module using an ESP32 microcontroller. The camera captures images and uploads them to a server.

## Overview

The Gabby Bot Camera project leverages the ESP32-CAM module to capture images and upload them to a server. It is designed for applications such as remote monitoring, security, and IoT projects.

## Files

- `camera_pins.h`: This file contains the GPIO pin definitions for various camera models.
- `gabby_bot_cam.ino`: The main Arduino sketch that initializes the camera, connects to WiFi, captures images, and uploads them to a server.

## Usage

1. **Upload the Sketch**: Connect your ESP32 board to your computer and upload the `gabby_bot_cam.ino` sketch using the Arduino IDE.

2. **Monitor Serial Output**: Open the Serial Monitor in the Arduino IDE to view the status messages. The device will:
    - Connect to the specified WiFi network.
    - Initialize the camera.
    - Capture images and upload them to the specified server.

## Pin Configuration

The pin configurations for various camera models are defined in `camera_pins.h`. Ensure that the correct camera model is defined in `gabby_bot_cam.ino` to match your hardware setup.

## Example Output

When the device is running, you should see output similar to the following in the Serial Monitor:

## Setup

1. **Install Dependencies**: Ensure you have the necessary libraries installed in your Arduino IDE:
    - `WiFi.h`
    - `HTTPClient.h`
    - `esp_camera.h`

2. **Configure WiFi**: Update the WiFi credentials and server endpoint in `gabby_bot_cam.ino`:
    ```ino
    const char *ssid = "your-ssid";
    const char *password = "your-password";
    const char *serverName = "your-server-endpoint";
    ```

3. **Select Camera Model**: Uncomment the appropriate camera model in `gabby_bot_cam.ino`:
    ```ino
    #define CAMERA_MODEL_AI_THINKER
    // #define CAMERA_MODEL_WROVER_KIT
    // #define CAMERA_MODEL_ESP_EYE
    // Add other camera models as needed
    ```

## Example Output

When the device is running, you should see output similar to the following in the Serial Monitor:
```
Connecting to WiFi... Connected! IP address: 192.168.1.XXX Camera initialization successful Starting capture loop... Image captured Uploading to server... HTTP POST successful - Response code: 200
```

## Hardware Requirements

- ESP32-CAM module (AI-Thinker or compatible)
- USB-to-TTL converter for programming
- 5V power supply
- Jumper wires for connections


## Troubleshooting

- **WiFi Connection Issues**: Ensure that the SSID and password are correct and that the ESP32 is within range of the WiFi network.
- **Camera Initialization Failed**: Check the pin configurations in `camera_pins.h` and ensure they match your camera module.
- **HTTP POST Failed**: Verify that the server endpoint is correct and that the server is running and accessible.
- **Serial Post Output**: Ensure that the correct port is selected during debugging.
