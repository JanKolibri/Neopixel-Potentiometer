# Neopixel LED Controller with Arduino

This project is an Arduino-based controller for Neopixel LED strips, featuring multiple LED rows, potentiometer-based adjustments, button inputs, and EEPROM memory storage. It allows users to modify brightness, saturation, color, and balance across different LED rows.

![vlc_9uL7p5MVmG](https://github.com/user-attachments/assets/b450113f-58fd-4037-8ce3-e20d8e4df911)

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

![Screenshot 2025-02-24 164649](https://github.com/user-attachments/assets/85f2da62-e507-4449-b68d-171fe7fa36e5)


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

## **Menu Structure**

__Button 1__ (Fig.: (E.1)): Cycling through all the rows
- 4x Flashes (1x row) → This row selected for change of saturation, brightness, colour
- 4x Flashes (all row) → All rows selected for change of saturation, brightness, colour
![Screenshot 2025-02-24 174700](https://github.com/user-attachments/assets/fcdb957d-c98d-41aa-8f4a-23d80d7cee27)

__Button 2__ (Fig.: (G.1), (H.1)): Selecting the row for change
- 1x Flash → Change this row with the potentiometer for colour, saturation, brightness
- 2x Flashes → Change this row with the potentiometer for position, number and brightness of the LEDs
![Screenshot 2025-02-24 175807](https://github.com/user-attachments/assets/3e83a655-7f4b-4e08-97c8-744fbe5ff8dd)


## **Serial Output**

### Threshold
- to prevent overloading the serial output with thresholds
- potentiometers → amount of change
- buttons → triggering = refresh serial output

### Output
- when adjusting the brightness, saturation or color the values will be printed to the serial output (Fig.: (K.1))
- if it is in balance mode, it will show which LED is selected and how many are affected (Fig.: (K.2))
- a counter for button 1 will indicate when all the existing rows where selected, to switch to all rows being activated simultaneously

![Screenshot 2025-02-24 181035](https://github.com/user-attachments/assets/b169356e-412b-4c1a-995b-7ea57f945bff)

## **CAD Model**
- I made a CAD model of all the components needed for the project
- You can download and check it out here: https://grabcad.com/library/neopixel-potentiometer-1
  
![Screenshot 2025-02-24 184411](https://github.com/user-attachments/assets/ab211765-299f-427b-87c6-1b8e13ee8f70)

## **Configuration**
Change the following configuration in the code according to your needs
### #region ▀▄▀▄▀▄ CONFIGURATION - MEMORY 
- Fig.: (O.1): The number of rows that are in your setup; deactiviate the other

###  #region ▀▄▀▄▀▄ CONFIGURATION - NEOPIXEL */
- Fig.: (P.2): The connection of the Neopixels with the Arduino (i.e. Pin 3)
- Fig.: (P.3): The number of pixels in one row of the (i.e. 3 LEDs in one row of Neopixels)
- Fig.: (P.4): Activate the storage for the number of rows needed and deactivate the rest
- Fig.: (P.5): Activate the number of rows used
![Picture3](https://github.com/user-attachments/assets/0620635c-3406-49e2-9554-fe85c3156e10)

## **License**

This project is licensed under the MIT License. See LICENSE for details.

## **Contributions**

Contributions are welcome! Feel free to submit pull requests or report issues.
Developed with ❤️ for Neopixel enthusiasts!
