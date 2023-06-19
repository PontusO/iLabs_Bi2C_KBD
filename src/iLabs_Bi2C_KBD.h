/*
 *                   GNU GENERAL PUBLIC LICENSE
 *                      Version 3, 29 June 2007
 *
 * Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
 * 
 * A complete copy of the license is attached to this library.
 */

#include <Wire.h>

static const uint8_t KBD_CTRLR_ADDRESS = 0x32;

typedef enum led_mode_e {
  LED_OFF = 0,
  LED_ON,
  LED_BLINK_1HZ,
  LED_BLINK_2HZ,
  LED_BLINK_4HZ,
  LED_CANDLE,        // Currently only supported on B LED
  LED_MODE_END,
} led_mode_t;

static const int DONT_USE_INT = -1;

// Registers
#define CTRL_REG_W                  0
#define CTRL_REG_INTERRUPT_ENABLE   0x01
#define CTRL_REG_INT_PIN_MODE_0     0x02
#define CTRL_REG_INT_PIN_MODE_1     0x04
#define CTRL_REG_NUM_KEYS_DISABLE   0x08
#define CTRL_REG_ALPHA_KEYS_DISABLE 0x10
#define CTRL_REG_RESET              0x80

#define STAT_REG_R                  0
#define STAT_REG_INTERRUPT_STATUS   0x01
#define STAT_REG_KEY_PRESS          0x02

#define KEY_REG_R                   1
#define NUM_KEYS_REG_R              2
#define LED_CTRL_REG_1_W            3
#define LED_CTRL_REG_2_W            4
#define LED_CTRL_REG_3_W            5

// LED's
#define NUM_LEDS                    5
#define STATUS_LED                  1
#define INDICATOR_LED_A             2
#define INDICATOR_LED_0             2
#define INDICATOR_LED_B             3
#define INDICATOR_LED_1             3
#define INDICATOR_LED_C             4
#define INDICATOR_LED_2             4
#define INDICATOR_LED_D             5
#define INDICATOR_LED_3             5

class Bi2C_KBD {
    public:
        void begin(uint8_t address = KBD_CTRLR_ADDRESS, int intpin = -1, void (*int_cb)() = NULL);
        void reset();
        size_t available();
        uint8_t read();
        void flush();
        void disableNumKeys(bool disable = true);
        void disableAlphaKeys(bool disable = true);
        bool setLEDMode(uint32_t led, uint8_t mode);
        uint8_t getLEDMode(uint32_t led);

    private:
        volatile bool keypressed = false;
        uint8_t _address;
        int _intpin = -1;
        uint8_t _ctrl_reg;
        void i2cWriteReg(uint8_t reg, uint8_t data);
        uint8_t i2cReadReg(uint8_t reg);
        void writeCtrlReg(uint8_t data);
        uint8_t readCtrlReg();
        void (*_intcb)();
};

extern Bi2C_KBD bi2c_kbd;