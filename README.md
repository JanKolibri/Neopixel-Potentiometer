# Neopixel LED Controller with Arduino

This project is an Arduino-based controller for Neopixel LED strips, featuring multiple LED rows, potentiometer-based adjustments, button inputs, and EEPROM memory storage. It allows users to modify brightness, saturation, color, and balance across different LED rows.

## **Features**

- Multi-row Neopixel Control: Supports up to three rows of Neopixel LEDs with dynamic configuration.
- Potentiometer Controls: Adjust brightness, saturation, and color in real-time.
- Button Inputs: Toggle between different LED rows and states.
- EEPROM Memory Storage: Saves LED settings for persistent state retention.
- Flashing Effects: Individual and full-row flashing modes.
- Debugging Support: Provides real-time debugging outputs.

## **Hardware Requirements**

- Arduino board (e.g., Arduino Uno, Mega)
- Neopixel LED strips (compatible with Adafruit_NeoPixel library)
- Potentiometers (x3)
- Push buttons (x2)

## **Software Requirements**

- Arduino IDE
- Adafruit NeoPixel Library
- EEPROM Library
- ArduinoSTL (for debugging)

## **Wiring Guide**

| Component | Arduino Pin |
|-----------|-------------|
| Neopixel Row 1 | Pin 2 |
| Neopixel Row 2 |  Pin 3 |
|Neopixel Row 3| Pin 4 |
|Potentiometer 1 (Brightness)|A0|
|Potentiometer 2 (Saturation)|A1|
|Potentiometer 3 (Color)|A2|
|Button 1|Pin 11|
|Button 2|Pin 12|

## **Installation & Usage**

1. Clone the repository:
 `git clone https://github.com/yourusername/neopixel-Potentiometer.git`
3. Open the Arduino project in the Arduino IDE.
4. Install the required libraries via the Library Manager.
5. Connect the hardware as per the wiring guide.
6. Upload the code to the Arduino.

Use the potentiometers to adjust the LED colors and buttons to switch between LED rows.

## **Functionality Overview**

- __setup():__ Initializes memory, button states, and Neopixel settings.
- __loop():__ Continuously checks for button presses and potentiometer changes to update LED behavior.
- __NEOPIXEL_SHOW():__ Updates LED colors and brightness dynamically.
- __EEPROM_SAVE() / EEPROM_LOAD():__ Saves and loads LED states to/from memory.

## **License**

This project is licensed under the MIT License. See LICENSE for details.

## **Contributions**

Contributions are welcome! Feel free to submit pull requests or report issues.
Developed with ❤️ for Neopixel enthusiasts!
