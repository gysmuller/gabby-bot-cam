
#include <WiFi.h>
#include <HTTPClient.h>
#include "esp_camera.h"

#define CAMERA_MODEL_AI_THINKER
#include "camera_pins.h"

const char *ssid = "";
const char *password = "";
const char *serverName = "";  // Replace with your API endpoint

void setup() {
  Serial.begin(115200);
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  
  // Initialize the camera
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sccb_sda = SIOD_GPIO_NUM;
  config.pin_sccb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;    // Use JPEG format for image capture
  config.frame_size = FRAMESIZE_QVGA;      // Set resolution to QVGA (320x240)
  config.jpeg_quality = 12;                // Set JPEG quality (lower is higher quality)
  config.fb_count = 1;

  // Camera initialization
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }
  Serial.println("Camera initialized");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("1.Capture image");
    camera_fb_t * fb = esp_camera_fb_get();
    if (!fb) {
      Serial.println("Camera capture failed");
      return;
    }

    Serial.println("2.Prepare HTTP POST request");
    // Prepare HTTP POST request
    HTTPClient http;
    http.begin(serverName);                // Connect to the server
    http.addHeader("Content-Type", "image/jpeg");  // Set content type for the image

    Serial.println("3.Send POST request");
    // Send POST request
    int httpResponseCode = http.POST(fb->buf, fb->len);
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Image uploaded successfully");
      Serial.println(response);
    } else {
      Serial.printf("Error on sending POST: %d\n", httpResponseCode);
    }

    http.end();  // Close connection

    // Return the frame buffer
    esp_camera_fb_return(fb);
  } else {
    Serial.println("WiFi Disconnected");
  }

  delay(50);  // Wait for 500ms before capturing the next image
}
