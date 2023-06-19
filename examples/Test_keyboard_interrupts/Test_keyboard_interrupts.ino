// --------------------------------------
// Test program for the bi2c_kbd firmware in the Bi2C KBD board 
//
//

#include <iLabs_Bi2C_KBD.h>

static volatile bool keypressed = false;

void setup()
{
  Wire.begin();
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.begin(115200);
  while (!Serial)
      delay(10);
      
  Serial.println("\nBi2C KBD tester using interrupts");
  bi2c_kbd.begin(KBD_CTRLR_ADDRESS, D12, keypress);
  bi2c_kbd.reset(); // Reset the keyboard controller.
}

uint32_t led_timer = 0;

void keypress() {
  keypressed = true;
  digitalWrite(LED_BUILTIN, HIGH);
  led_timer = millis() + 250;
}

void loop()
{
  if (keypressed) {
    uint8_t tmp;
 
    keypressed = false;
    uint8_t in = bi2c_kbd.read();
    Serial.printf("Keyboard stroke: %c\n\r", in);

    switch(in) {
      case 'A':
          if (bi2c_kbd.getLEDMode(INDICATOR_LED_A) == LED_ON)
            bi2c_kbd.setLEDMode(INDICATOR_LED_A, LED_OFF);
          else
            bi2c_kbd.setLEDMode(INDICATOR_LED_A, LED_ON);
        break;

      case 'B':
          if (bi2c_kbd.getLEDMode(INDICATOR_LED_B) == LED_ON)
            bi2c_kbd.setLEDMode(INDICATOR_LED_B, LED_OFF);
          else
            bi2c_kbd.setLEDMode(INDICATOR_LED_B, LED_ON);
        break;
      
      case 'C':
          if (bi2c_kbd.getLEDMode(INDICATOR_LED_C) == LED_ON)
            bi2c_kbd.setLEDMode(INDICATOR_LED_C, LED_OFF);
          else
            bi2c_kbd.setLEDMode(INDICATOR_LED_C, LED_ON);
        break;
      
      case 'D':
          if (bi2c_kbd.getLEDMode(INDICATOR_LED_D) == LED_ON)
            bi2c_kbd.setLEDMode(INDICATOR_LED_D, LED_OFF);
          else
            bi2c_kbd.setLEDMode(INDICATOR_LED_D, LED_ON);
        break;
      
      case '*':
          if (bi2c_kbd.getLEDMode(STATUS_LED) == LED_ON)
            bi2c_kbd.setLEDMode(STATUS_LED, LED_OFF);
          else
            bi2c_kbd.setLEDMode(STATUS_LED, LED_ON);
        break;

      case '3':
          if (bi2c_kbd.getLEDMode(INDICATOR_LED_A) != LED_BLINK_4HZ)
            bi2c_kbd.setLEDMode(INDICATOR_LED_A, LED_BLINK_4HZ);
          else
            bi2c_kbd.setLEDMode(INDICATOR_LED_A, LED_OFF);
        break;

      case '6':
          if (bi2c_kbd.getLEDMode(INDICATOR_LED_B) != LED_BLINK_2HZ)
            bi2c_kbd.setLEDMode(INDICATOR_LED_B, LED_BLINK_2HZ);
          else
            bi2c_kbd.setLEDMode(INDICATOR_LED_B, LED_OFF);
        break;

      case '9':
          if (bi2c_kbd.getLEDMode(INDICATOR_LED_C) != LED_BLINK_1HZ)
            bi2c_kbd.setLEDMode(INDICATOR_LED_C, LED_BLINK_1HZ);
          else
            bi2c_kbd.setLEDMode(INDICATOR_LED_C, LED_OFF);
        break;

      case '#':
          for (int i=1;i<6;i++) {
            bi2c_kbd.setLEDMode(i, LED_OFF);
          }
        break;
    }
  }

  if (led_timer && millis() >= led_timer) {
    led_timer = 0;
    digitalWrite(LED_BUILTIN, LOW);
  }
}
