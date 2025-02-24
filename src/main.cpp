/* #region ▀▄▀▄▀▄ CONFIGURATION - MEMORY */

#include <avr/pgmspace.h>

struct MEMORY
{
  int MEMORY_BRIGHTNESS;
  int MEMORY_SATURATION;
  int MEMORY_COLOR;
  int MEMORY_BALANCE_INDEX;
  int MEMORY_BALANCE_NUMB;
};
MEMORY NEOPIXEL_ROW1_VALUES = {0, 0, 0, 0, 0}; // Initialize with default values
MEMORY NEOPIXEL_ROW2_VALUES = {0, 0, 0, 0, 0}; // Initialize with default values
MEMORY NEOPIXEL_ROW3_VALUES = {0, 0, 0, 0, 0}; // Initialize with default values
// MEMORY NEOPIXEL_ROW4_VALUES = {0, 0, 0}; // Initialize with default values
MEMORY *NEOPIXEL_VALUES = &NEOPIXEL_ROW1_VALUES;

/* #endregion  ▀▄▀▄▀▄ CONFIGURATION - MEMORY */

/* #region ▀▄▀▄▀▄ CONFIGURATION - NEOPIXEL */

#include <Adafruit_NeoPixel.h>

#define NEOPIXEL_ROW1_PIN 2
#define NEOPIXEL_ROW1_LENGTH 21

#define NEOPIXEL_ROW2_PIN 3
#define NEOPIXEL_ROW2_LENGTH 29

#define NEOPIXEL_ROW3_PIN 4
#define NEOPIXEL_ROW3_LENGTH 27

// #define NEOPIXEL_ROW4_PIN 5
// #define NEOPIXEL_ROW4_LENGTH 4

#define NEOPIXEL_ROWCOUNTER (sizeof(NEOPIXEL_CONFIG_ROWS_VALUES) / sizeof(NEOPIXEL_CONFIG_ROWS_VALUES[0]))

#define POTENTIOMETER_BRIGHTNESS_PIN A0
#define POTENTIOMETER_SATURATION_PIN A1
#define POTENTIOMETER_COLOR_PIN A2

int NEOPIXEL_PIN = NEOPIXEL_ROW1_PIN;
int NEOPIXEL_LENGTH = NEOPIXEL_ROW1_LENGTH;

int NEOPIXEL_COLOR_STEPS = 250;
int NEOPIXEL_COLOR_STEPS_WIDTH = 250;

int NEOPIXEL_FLASH_DELAY = 100;

Adafruit_NeoPixel NEOPIXEL = Adafruit_NeoPixel(NEOPIXEL_LENGTH, NEOPIXEL_PIN, NEO_RGB + NEO_KHZ800);

enum NEOPIXEL_STATE
{
  NEOPIXEL_ROW1_ON,
  NEOPIXEL_ROW2_ON,
  NEOPIXEL_ROW3_ON,
  // NEOPIXEL_ROW4_ON,
};
NEOPIXEL_STATE NEOPIXEL_STATE_CHECK = NEOPIXEL_ROW1_ON;

struct NEOPIXEL_CONFIG_ROWS 
{
  int pin;
  int numLEDs;
  MEMORY *values;
};
NEOPIXEL_CONFIG_ROWS NEOPIXEL_CONFIG_ROWS_VALUES[] =  
{ 
  {NEOPIXEL_ROW1_PIN, NEOPIXEL_ROW1_LENGTH, &NEOPIXEL_ROW1_VALUES},
  {NEOPIXEL_ROW2_PIN, NEOPIXEL_ROW2_LENGTH, &NEOPIXEL_ROW2_VALUES},
  {NEOPIXEL_ROW3_PIN, NEOPIXEL_ROW3_LENGTH, &NEOPIXEL_ROW3_VALUES},
  // {NEOPIXEL_ROW4_PIN, NEOPIXEL_ROW4_LENGTH, &NEOPIXEL_ROW4_VALUES}
};

enum NEOPIXEL_POTENTIOMETER_STATE
{
  NEOPIXEL_POTENTIOMETER_OFF,
  NEOPIXEL_CHANGE_SINGLE_ON,
  NEOPIXEL_BALANCE_SINGLE_ON,
  NEOPIXEL_CHANGE_ALL_ON,
  NEOPIXEL_TURNOFF_ON,
};
NEOPIXEL_POTENTIOMETER_STATE NEOPIXEL_SWITCH_CHECK = NEOPIXEL_POTENTIOMETER_OFF;

NEOPIXEL_CONFIG_ROWS *NEOPIXEL_CONFIG_ROWS_ACTIVE()
{
  return &NEOPIXEL_CONFIG_ROWS_VALUES[static_cast<int>(NEOPIXEL_STATE_CHECK)];
}

/* #endregion ▀▄▀▄▀▄ CONFIGURATION - NEOPIXEL */

/* #region ▀▄▀▄▀▄ CONFIGURATION - BUTTON */

#define BUTTON_1_PIN 11
#define BUTTON_2_PIN 12

bool BUTTON_1_STATE = false;
bool BUTTON_2_STATE = false;

static unsigned long BUTTON_1_DEBOUNCE_TIME = 0;
static unsigned long BUTTON_2_DEBOUNCE_TIME = 0;

const unsigned long BUTTON_1_DEBOUNCE_DELAY = 50;
const unsigned long BUTTON_2_DEBOUNCE_DELAY = 50;

bool BUTTON_1_PRESSED(unsigned long &BUTTON_1_TIME_LAST) 
{
  volatile static bool BUTTON_1_STATE_LAST = HIGH;
  volatile bool BUTTON_1_STATE_CURRENT = digitalRead(BUTTON_1_PIN);

  if (BUTTON_1_STATE_CURRENT != BUTTON_1_STATE_LAST)
  {
    BUTTON_1_TIME_LAST = millis();

    if ((millis() - BUTTON_1_DEBOUNCE_TIME) > BUTTON_1_DEBOUNCE_DELAY)
    {
      BUTTON_1_STATE_LAST = BUTTON_1_STATE_CURRENT;
      return BUTTON_1_STATE_CURRENT == LOW;
    }
  }
  return false;
}

bool BUTTON_2_PRESSED(unsigned long &BUTTON_2_TIME_LAST) 
{
  volatile static bool BUTTON_2_STATE_LAST = HIGH;
  volatile bool BUTTON_2_STATE_CURRENT = digitalRead(BUTTON_2_PIN);

  if (BUTTON_2_STATE_CURRENT != BUTTON_2_STATE_LAST)
  {
    BUTTON_2_TIME_LAST = millis();

    if ((millis() - BUTTON_2_DEBOUNCE_TIME) > BUTTON_2_DEBOUNCE_DELAY)
    {
      BUTTON_2_STATE_LAST = BUTTON_2_STATE_CURRENT;
      return BUTTON_2_STATE_CURRENT == LOW;
    }
  }
  return false;
}

int BUTTON_1_PRESS_COUNT = 0;

bool NEOPIXEL_ROWCOUNTER_CHECK()
{
  return (unsigned int) BUTTON_1_PRESS_COUNT < NEOPIXEL_ROWCOUNTER;
}

/* #endregion ▀▄▀▄▀▄ CONFIGURATION - BUTTON */

/* #region ▀▄▀▄▀▄ CONFIGURATION - DEBUGGER */

#include <ArduinoSTL.h>
#include <vector>
#include <avr8-stub.h>
// #include <SoftwareSerial.h>
// SoftwareSerial Serial(10, 11); // RX, TX pins

int POTENTIOMETER_BRIGHTNESS_THRESHOLD = 5;
int POTENTIOMETER_SATURATION_THRESHOLD = 5;
int POTENTIOMETER_COLOR_THRESHOLD = 800;

bool loop_DEBUGGER_CHANGE = false;

std::vector<int> DEBUGGER_CMD_PRE = {0, 0, 0, 0, 0}; // Store previous values
std::vector<int> DEBUGGER_CMD_NOW = {0, 0, 0, 0, 0}; // Store current values

/* #endregion ▀▄▀▄▀▄ CONFIGURATION - DEBUGGER */

/* #region ▀▄▀▄▀▄ CONFIGURATION - EEPROM */

#include <EEPROM.h>

#define EEPROM_ROW1_ADRESS 1
#define EEPROM_ROW2_ADRESS 11

/* #endregion ▀▄▀▄▀▄ CONFIGURATION - EEPROM */

/* #region ▀▄▀▄▀▄ CONFIGURATION - VOID  */

void setup_MEMORY();
void setup_BUTTON();
void setup_MEMORY();

void NEOPIXEL_INIT();
void NEOPIXEL_FLASH_SINGLE
(
  int NEOPIXEL_FLASH_TIMES
);
void NEOPIXEL_FLASH_ALL
(
  int NEOPIXEL_FLASH_TIMES
);

void NEOPIXEL_HANDOVER();
void NEOPIXEL_SHOW
(
  MEMORY &STORAGE, int NEOPIXEL_PIN, int NEOPIXEL_LENGTH
);
void NEOPIXEL_CHANGE_SINGLE();
void NEOPIXEL_TOGGLE();
void NEOPIXEL_SWITCHER();
void NEOPIXEL_BALANCE_SINGLE();
void NEOPIXEL_CHANGE_ALL();
void NEOPIXEL_TURNOFF();
void NEOPIXEL_SWITCH_CHECKER();

void BUTTON_1_CHECK();
void BUTTON_2_CHECK();

void loop_DEBUGGER(MEMORY *current_row_values);

void EEPROM_SAVE
(
  int ADRESS, 
  const MEMORY &STORAGE
);
void EEPROM_LOAD
(
  int ADRESS, 
  MEMORY &STORAGE
);

/* #endregion ▀▄▀▄▀▄ CONFIGURATION - VOID */

/* #region ✩░▒▓▆▅▃▂▁SETUP▁▂▃▅▆▓▒░✩ */

void setup()
{
  Serial.begin(9600);
  // Serial.begin(9600);
  // Serial.println("Debug message");
  // debug_init();

  setup_MEMORY();
  NEOPIXEL_INIT();
  setup_BUTTON();
  NEOPIXEL_HANDOVER();
}
/* #endregion ✩░▒▓▆▅▃▂▁SETUP▁▂▃▅▆▓▒░✩ */

/* #region ✩░▒▓▆▅▃▂▁𝐋𝐎𝐎𝐏▁▂▃▅▆▓▒░✩ */

void loop()
{
  BUTTON_1_CHECK();
  BUTTON_2_CHECK();
  NEOPIXEL_SWITCHER();
  NEOPIXEL_SWITCH_CHECKER();
  MEMORY *current_row_values = NEOPIXEL_CONFIG_ROWS_ACTIVE()->values;
  loop_DEBUGGER(current_row_values);
  delay(5);
}

/* #endregion ✩░▒▓▆▅▃▂▁𝐋𝐎𝐎𝐏▁▂▃▅▆▓▒░✩  */

/* #region ▌║█║▌│║▌ Neopixel │║▌║▌█║ */

void NEOPIXEL_SHOW(MEMORY &STORAGE, int NEOPIXEL_PIN, int NEOPIXEL_LENGTH)
{
  NEOPIXEL.updateLength(NEOPIXEL_LENGTH);
  NEOPIXEL.setPin(NEOPIXEL_PIN);
  NEOPIXEL.begin();
  NEOPIXEL.setBrightness(STORAGE.MEMORY_BRIGHTNESS);

  // Calculate the position of the LED to light up
  int NEOPIXEL_BALANCE_SINGLE_INDEX = STORAGE.MEMORY_BALANCE_INDEX;
  if (NEOPIXEL_BALANCE_SINGLE_INDEX < 0 || NEOPIXEL_BALANCE_SINGLE_INDEX >= NEOPIXEL_LENGTH) 
  {
      NEOPIXEL_BALANCE_SINGLE_INDEX = 0; // Fallback to the first LED if out of bounds
  }

  uint32_t NEOPIXEL_OUTPUT = NEOPIXEL.ColorHSV
  (
      STORAGE.MEMORY_COLOR,
      STORAGE.MEMORY_SATURATION,
      255
  );

  // Turn off all LEDs first
  for (int i = 0; i < NEOPIXEL_LENGTH; i++) 
  {
      NEOPIXEL.setPixelColor(i, 0); // Off (black)
  }

  // Light up the specified LED
  NEOPIXEL.setPixelColor(NEOPIXEL_BALANCE_SINGLE_INDEX, NEOPIXEL_OUTPUT);

  for (int i = STORAGE.MEMORY_BALANCE_INDEX; i < STORAGE.MEMORY_BALANCE_INDEX + STORAGE.MEMORY_BALANCE_NUMB && i < NEOPIXEL_LENGTH; i++) 
  {
    uint32_t NEOPIXEL_OUTPUT = NEOPIXEL.ColorHSV
    (
        NEOPIXEL_VALUES->MEMORY_COLOR,
        NEOPIXEL_VALUES->MEMORY_SATURATION,
        255
    );
    NEOPIXEL.setPixelColor(i, NEOPIXEL_OUTPUT); // Light up LED
  }
  NEOPIXEL.show();
}

void NEOPIXEL_CHANGE_SINGLE()
{
  int POTENTIOMETER_BRIGHTNESS_VALUE = analogRead(POTENTIOMETER_BRIGHTNESS_PIN);
  int POTENTIOMETER_SATURATION_VALUE = analogRead(POTENTIOMETER_SATURATION_PIN);
  int POTENTIOMETER_COLOR_VALUE = analogRead(POTENTIOMETER_COLOR_PIN);

  // Update brightness, saturation, and color from potentiometers
  NEOPIXEL_VALUES->MEMORY_BRIGHTNESS = map(POTENTIOMETER_BRIGHTNESS_VALUE, 0, 1023, 0, 255);
  NEOPIXEL_VALUES->MEMORY_SATURATION = map(POTENTIOMETER_SATURATION_VALUE, 0, 1023, 0, 255);
  NEOPIXEL_VALUES->MEMORY_COLOR = map(POTENTIOMETER_COLOR_VALUE, 0, 1023, 0, 65535);

  NEOPIXEL_SHOW(*NEOPIXEL_VALUES, NEOPIXEL_PIN, NEOPIXEL_LENGTH);
}

void NEOPIXEL_CHANGE_ALL()
{
  int POTENTIOMETER_BRIGHTNESS_VALUE = analogRead(POTENTIOMETER_BRIGHTNESS_PIN);
  int POTENTIOMETER_SATURATION_VALUE = analogRead(POTENTIOMETER_SATURATION_PIN);
  int POTENTIOMETER_COLOR_VALUE = analogRead(POTENTIOMETER_COLOR_PIN);

  // Map potentiometer values to appropriate ranges
  int newBrightness = map(POTENTIOMETER_BRIGHTNESS_VALUE, 0, 1023, 0, 255);
  int newSaturation = map(POTENTIOMETER_SATURATION_VALUE, 0, 1023, 0, 255);
  int newColor = map(POTENTIOMETER_COLOR_VALUE, 0, 1023, 0, 65535);

  // Iterate over all rows
  for (size_t i = 0; i < NEOPIXEL_ROWCOUNTER; ++i)
  {
    NEOPIXEL_CONFIG_ROWS *row = &NEOPIXEL_CONFIG_ROWS_VALUES[i];

    // Update each row's MEMORY struct
    row->values->MEMORY_BRIGHTNESS = newBrightness;
    row->values->MEMORY_SATURATION = newSaturation;
    row->values->MEMORY_COLOR = newColor;

    // Display the updated settings on each row
    NEOPIXEL_SHOW(*row->values, row->pin, row->numLEDs);
  }
}

void NEOPIXEL_HANDOVER()
{
  NEOPIXEL_CONFIG_ROWS *activeRow = NEOPIXEL_CONFIG_ROWS_ACTIVE();
  NEOPIXEL_SHOW(*activeRow->values, activeRow->pin, activeRow->numLEDs);
}

void NEOPIXEL_FLASH_SINGLE(int NEOPIXEL_FLASH_TIMES = 3)
{
  for (int k = 0; k < NEOPIXEL_FLASH_TIMES; k++)
  {
    for (int i = 0; i < NEOPIXEL_LENGTH; i++)
    {
      NEOPIXEL.setPixelColor(i, NEOPIXEL.Color(0, 0, 0));
    }
    NEOPIXEL.show();
    delay(NEOPIXEL_FLASH_DELAY);

    NEOPIXEL_HANDOVER();
    delay(NEOPIXEL_FLASH_DELAY);
  }
}

void NEOPIXEL_FLASH_ALL(int NEOPIXEL_FLASH_TIMES = 3)
{
  for (int k = 0; k < NEOPIXEL_FLASH_TIMES; k++)
  {
    // Turn off all rows
    for (size_t i = 0; i < NEOPIXEL_ROWCOUNTER; i++)
    {
      NEOPIXEL_CONFIG_ROWS *row = &NEOPIXEL_CONFIG_ROWS_VALUES[i];
      NEOPIXEL.updateLength(row->numLEDs);
      NEOPIXEL.setPin(row->pin);
      NEOPIXEL.begin();

      for (int j = 0; j < row->numLEDs; j++)
      {
        NEOPIXEL.setPixelColor(j, 0); // Turn off (black)
      }
      NEOPIXEL.show();
    }

    delay(NEOPIXEL_FLASH_DELAY);

    // Restore all rows to their respective saved states
    for (size_t i = 0; i < NEOPIXEL_ROWCOUNTER; i++)
    {
      NEOPIXEL_CONFIG_ROWS *row = &NEOPIXEL_CONFIG_ROWS_VALUES[i];
      NEOPIXEL_SHOW(*row->values, row->pin, row->numLEDs);
    }

    delay(NEOPIXEL_FLASH_DELAY);
  }
}

void NEOPIXEL_INIT()
{
  for (size_t i = 0; i < NEOPIXEL_ROWCOUNTER; i++)
  {
    NEOPIXEL_TOGGLE();
    NEOPIXEL_HANDOVER();
  }
}

void NEOPIXEL_TOGGLE()
{
  //  Simulate the first button press
  NEOPIXEL_CONFIG_ROWS *currentRow = NEOPIXEL_CONFIG_ROWS_ACTIVE();
  int currentRowIndex = static_cast<int>(NEOPIXEL_STATE_CHECK);
  EEPROM_SAVE(EEPROM_ROW1_ADRESS + currentRowIndex * 30, *currentRow->values);

  // Toggle to the next row
  NEOPIXEL_STATE_CHECK = static_cast<NEOPIXEL_STATE>((currentRowIndex + 1) % NEOPIXEL_ROWCOUNTER);

  // Update NEOPIXEL_VALUES pointer to the active row
  NEOPIXEL_CONFIG_ROWS *nextRow = NEOPIXEL_CONFIG_ROWS_ACTIVE();
  NEOPIXEL_VALUES = nextRow->values;
  NEOPIXEL_PIN = nextRow->pin;
  NEOPIXEL_LENGTH = nextRow->numLEDs;
}

void NEOPIXEL_SWITCHER()
{
  switch (NEOPIXEL_SWITCH_CHECK)
  {
    case NEOPIXEL_POTENTIOMETER_OFF:
      // do nothing
    break;

    case NEOPIXEL_TURNOFF_ON:
      NEOPIXEL_TURNOFF();
    break;

    case NEOPIXEL_CHANGE_SINGLE_ON:
      NEOPIXEL_CHANGE_SINGLE();
    break;

    case NEOPIXEL_CHANGE_ALL_ON:
      NEOPIXEL_CHANGE_ALL();
    break;

    case NEOPIXEL_BALANCE_SINGLE_ON:
      NEOPIXEL_BALANCE_SINGLE();
    break;

    default:
      // Do nothing
    break;
  }
}

void NEOPIXEL_SWITCH_CHECKER()
{
  if (NEOPIXEL_SWITCH_CHECK == NEOPIXEL_CHANGE_ALL_ON) 
  {
    // Debug all rows
    for (size_t i = 0; i < NEOPIXEL_ROWCOUNTER; i++) 
    {
      loop_DEBUGGER(NEOPIXEL_CONFIG_ROWS_VALUES[i].values);
    }
  } 
  else 
  {
    // Debug only the active row
    loop_DEBUGGER(NEOPIXEL_CONFIG_ROWS_ACTIVE()->values);
  }
}

void NEOPIXEL_BALANCE_SINGLE()
{
  int NEOPIXEL_BALANCE_SINGLE_BRIGHTNESS = analogRead(POTENTIOMETER_BRIGHTNESS_PIN);
  int NEOPIXEL_BALANCE_SINGLE_INDEX = analogRead(POTENTIOMETER_COLOR_PIN);
  int NEOPIXEL_BALANCE_SINGLE_NEXT = analogRead(POTENTIOMETER_SATURATION_PIN);
  
  NEOPIXEL_VALUES->MEMORY_BRIGHTNESS = map(NEOPIXEL_BALANCE_SINGLE_BRIGHTNESS, 0, 1023, 0, 255);
  
  int BALANCE_INDEX = map(NEOPIXEL_BALANCE_SINGLE_INDEX, 0, 1000, 0, NEOPIXEL_LENGTH - 1);
  int BALANCE_NUMB = map(NEOPIXEL_BALANCE_SINGLE_NEXT, 0, 1000, 1, NEOPIXEL_LENGTH);
  
  NEOPIXEL_VALUES->MEMORY_BALANCE_INDEX = BALANCE_INDEX;
  NEOPIXEL_VALUES->MEMORY_BALANCE_NUMB = BALANCE_NUMB; 

  NEOPIXEL.setBrightness(NEOPIXEL_VALUES->MEMORY_BRIGHTNESS);

  // Turn off all LEDs first
  for (int i = 0; i < NEOPIXEL_LENGTH; i++) 
  {
    NEOPIXEL.setPixelColor(i, 0); // Turn off (black)
  }
  
  // Light up the LEDs based on the BALANCE_INDEX and BALANCE_NUMB
  for (int i = BALANCE_INDEX; i < BALANCE_INDEX + BALANCE_NUMB && i < NEOPIXEL_LENGTH; i++) 
  {
    uint32_t NEOPIXEL_OUTPUT = NEOPIXEL.ColorHSV
    (
        NEOPIXEL_VALUES->MEMORY_COLOR,
        NEOPIXEL_VALUES->MEMORY_SATURATION,
        255
    );
    NEOPIXEL.setPixelColor(i, NEOPIXEL_OUTPUT); // Light up LED
  }
  
  // Show the updated LED states
  NEOPIXEL.show();
}

void NEOPIXEL_TURNOFF()
{
  for (size_t i = 0; i < NEOPIXEL_ROWCOUNTER; ++i)
  {
    NEOPIXEL_CONFIG_ROWS *row = &NEOPIXEL_CONFIG_ROWS_VALUES[i];

    NEOPIXEL.updateLength(row->numLEDs);
    NEOPIXEL.setPin(row->pin);
    NEOPIXEL.begin();

    for (int j = 0; j < row->numLEDs; j++)
    {
      NEOPIXEL.setPixelColor(j, 0); // Turn off LED
    }
    NEOPIXEL.show();
  }
}

/* #endregion ▌║█║▌│║▌ Neopixel │║▌║▌█║*/

/* #region ▌║█║▌│║▌ Button │║▌║▌█║ */

void setup_BUTTON()
{
  pinMode(BUTTON_1_PIN, INPUT_PULLUP);
  pinMode(BUTTON_2_PIN, INPUT_PULLUP);
}

void BUTTON_1_CHECK()
{
  static unsigned long BUTTON_1_DEBOUNCE_TIME = 0;

  if (BUTTON_1_PRESSED(BUTTON_1_DEBOUNCE_TIME))
  {
    BUTTON_1_PRESS_COUNT++;
    BUTTON_1_DEBOUNCE_TIME = millis();

    NEOPIXEL_SWITCH_CHECK = NEOPIXEL_POTENTIOMETER_OFF;
    NEOPIXEL_TOGGLE();
    NEOPIXEL_HANDOVER();

    if ((unsigned int) BUTTON_1_PRESS_COUNT == NEOPIXEL_ROWCOUNTER)
    {
      NEOPIXEL_FLASH_ALL(4);
      return;
    }

    else if((unsigned int) BUTTON_1_PRESS_COUNT < NEOPIXEL_ROWCOUNTER)
    {
      NEOPIXEL_SWITCH_CHECK = NEOPIXEL_POTENTIOMETER_OFF;
      NEOPIXEL_FLASH_SINGLE(4);
      return;
    }

    else if((unsigned int) BUTTON_1_PRESS_COUNT > NEOPIXEL_ROWCOUNTER)
    {
      BUTTON_1_PRESS_COUNT = 0;
      NEOPIXEL_SWITCH_CHECK = NEOPIXEL_POTENTIOMETER_OFF;
      NEOPIXEL_FLASH_SINGLE(4);
      return;
    }
  }
}

void BUTTON_2_CHECK()
{
  static unsigned long BUTTON_2_DEBOUNCE_TIME = 0;

  if (BUTTON_2_PRESSED(BUTTON_2_DEBOUNCE_TIME))
  {
    BUTTON_2_DEBOUNCE_TIME = millis();

    if (BUTTON_1_PRESS_COUNT == NEOPIXEL_ROWCOUNTER)
    {
      NEOPIXEL_SWITCH_CHECK = NEOPIXEL_CHANGE_ALL_ON;
      NEOPIXEL_FLASH_ALL(1);
      return;
    }

    else if(NEOPIXEL_SWITCH_CHECK == NEOPIXEL_POTENTIOMETER_OFF)
    {
      NEOPIXEL_SWITCH_CHECK = NEOPIXEL_CHANGE_SINGLE_ON;
      NEOPIXEL_FLASH_SINGLE(1);
      return;
    }

    else if(NEOPIXEL_SWITCH_CHECK == NEOPIXEL_CHANGE_SINGLE_ON)
    {
      NEOPIXEL_SWITCH_CHECK = NEOPIXEL_BALANCE_SINGLE_ON;
      NEOPIXEL_FLASH_SINGLE(2);
      return;
    }

    else if(NEOPIXEL_SWITCH_CHECK == NEOPIXEL_BALANCE_SINGLE_ON)
    {
      NEOPIXEL_SWITCH_CHECK = NEOPIXEL_CHANGE_SINGLE_ON;
      NEOPIXEL_FLASH_SINGLE(1);
      return;
    }
  }
}

/* #endregion ▌║█║▌│║▌ Button │║▌║▌█║ */

/* #region ▌║█║▌│║▌ Debugger │║▌║▌█║ */

void loop_DEBUGGER(MEMORY *current_row_values) 
{
  // Array for current row values
  DEBUGGER_CMD_NOW = 
  {
    current_row_values->MEMORY_COLOR,
    current_row_values->MEMORY_SATURATION,
    current_row_values->MEMORY_BRIGHTNESS,
    current_row_values->MEMORY_BALANCE_INDEX,
    current_row_values->MEMORY_BALANCE_NUMB,
  };

  // Define thresholds for changes
  const int thresholds[] = 
  {
    POTENTIOMETER_COLOR_THRESHOLD,    // Color threshold
    POTENTIOMETER_SATURATION_THRESHOLD, // Saturation threshold
    POTENTIOMETER_BRIGHTNESS_THRESHOLD // Brightness threshold
  };

  loop_DEBUGGER_CHANGE = false;

  // Compare current values with previous values
  for (size_t i = 0; i < DEBUGGER_CMD_NOW.size(); ++i) 
  {
    if (abs(DEBUGGER_CMD_NOW[i] - DEBUGGER_CMD_PRE[i]) > thresholds[i]) 
    {
      loop_DEBUGGER_CHANGE = true;
      break;
    }
  }

  // If changes are detected, print debug information
  if (loop_DEBUGGER_CHANGE) 
  {
    char buffer[102]; // Buffer for formatted output
    snprintf
    (
      buffer, sizeof(buffer),
      "[C|S|B]: %6d | %3d | %3d ▏Index: %2d Index +: %2d ▏Button 1: %d Nr[⭳]: %d ▏Button 2: %d" ,
      current_row_values->MEMORY_COLOR,
      current_row_values->MEMORY_SATURATION,
      current_row_values->MEMORY_BRIGHTNESS,
      current_row_values->MEMORY_BALANCE_INDEX,
      current_row_values->MEMORY_BALANCE_NUMB,
      BUTTON_1_STATE,
      BUTTON_1_PRESS_COUNT,
      BUTTON_2_STATE
    );
    Serial.println(buffer);
  }
  
  // Update previous values
  DEBUGGER_CMD_PRE = DEBUGGER_CMD_NOW;

  // //  Debugger Input

  //  int POTENTIOMETER_BRIGHTNESS_VALUE = analogRead(POTENTIOMETER_BRIGHTNESS_PIN);
  //   int POTENTIOMETER_SATURATION_VALUE = analogRead(POTENTIOMETER_SATURATION_PIN);
  //   int POTENTIOMETER_COLOR_VALUE = analogRead(POTENTIOMETER_COLOR_PIN);

  //   // Map values
  //   int newBrightness = map(POTENTIOMETER_BRIGHTNESS_VALUE, 0, 1023, 0, 255);
  //   int newSaturation = map(POTENTIOMETER_SATURATION_VALUE, 0, 1023, 0, 255);
  //   int newColor = map(POTENTIOMETER_COLOR_VALUE, 0, 1023, 0, 65535);

  //   // Check threshold conditions and print debug messages
  //   if (abs(DEBUGGER_CMD_PRE[0] - newBrightness) > POTENTIOMETER_BRIGHTNESS_THRESHOLD) {
  //       Serial.print("Brightness threshold exceeded: ");
  //       Serial.print(DEBUGGER_CMD_PRE[0]);
  //       Serial.print(" -> ");
  //       Serial.println(newBrightness);
  //   }
  //   if (abs(DEBUGGER_CMD_PRE[1] - newSaturation) > POTENTIOMETER_SATURATION_THRESHOLD) {
  //       Serial.print("Saturation threshold exceeded: ");
  //       Serial.print(DEBUGGER_CMD_PRE[1]);
  //       Serial.print(" -> ");
  //       Serial.println(newSaturation);
  //   }
  //   if (abs(DEBUGGER_CMD_PRE[2] - newColor) > POTENTIOMETER_COLOR_THRESHOLD) {
  //       Serial.print("Color threshold exceeded: ");
  //       Serial.print(DEBUGGER_CMD_PRE[2]);
  //       Serial.print(" -> ");
  //       Serial.println(newColor);
  //   }

  //   // Update the stored values for next loop iteration
  //   DEBUGGER_CMD_PRE[0] = newBrightness;
  //   DEBUGGER_CMD_PRE[1] = newSaturation;
  //   DEBUGGER_CMD_PRE[2] = newColor;
}

/* #endregion ▌║█║▌│║▌ Debugger │║▌║▌█║ */

/* #region ▌║█║▌│║▌ Memory │║▌║▌█║ */

void setup_MEMORY()
{  
  int baseAddress = EEPROM_ROW1_ADRESS;
  int rowSize = 30;

  for (size_t i = 0; i < NEOPIXEL_ROWCOUNTER; ++i)
  {
    EEPROM_LOAD(baseAddress + i * rowSize, *NEOPIXEL_CONFIG_ROWS_VALUES[i].values);
  }

  NEOPIXEL_VALUES = NEOPIXEL_CONFIG_ROWS_ACTIVE()->values; 
}


/* #endregion ▌║█║▌│║▌ Memory │║▌║▌█║ */

/* #region ▌║█║▌│║▌ EEPROM │║▌║▌█║ */

void EEPROM_SAVE(int ADRESS, const MEMORY &STORAGE)
{
  EEPROM.put(ADRESS, STORAGE);
}

// Generic function to load memory storage from EEPROM
void EEPROM_LOAD(int ADRESS, MEMORY &STORAGE)
{
  EEPROM.get(ADRESS, STORAGE);
}

/* #endregion  ▌║█║▌│║▌ EEPROM │║▌║▌█║  */