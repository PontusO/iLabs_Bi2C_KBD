/*--------------------------------------
 * Test program for the bi2c_kbd firmware in the Bi2C KBD board.
 *
 * This is the non interrupt version and it demonstrates on how
 * to use most functions of the keyboard.
 *
 */

#include <iLabs_Bi2C_KBD.h>

void setup()
{
  Wire.begin();
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.begin(115200);
  while (!Serial)
      delay(10);
      
  Serial.println("\nBi2C KBD tester using no interrupts");
  bi2c_kbd.begin();
  bi2c_kbd.reset(); // Reset the keyboard controller.
}

uint32_t led_timer = 0;

void loop()
{
  // Check if there are any characters in the buffer.
  // available() will also return how many characters are waiting in the
  // buffer. The keyboard will hold up to 16 characters before starting to
  // overwrite the circular buffer.
  if (bi2c_kbd.available()) {
    led_timer = millis() + 100;
    digitalWrite(LED_BUILTIN, HIGH);
 
    // Read the current character from the key board.
    uint8_t in = bi2c_kbd.read();
    Serial.printf("Keyboard stroke: %c\n\r", in);

    switch(in) {
      // Pressing 'A' will toggle the associated LED on and off.
      // It will also enable the numeric keys if they were disabled.
      case 'A':
        if (bi2c_kbd.getLEDMode(INDICATOR_LED_A) == LED_ON)
          bi2c_kbd.setLEDMode(INDICATOR_LED_A, LED_OFF);
        else
          bi2c_kbd.setLEDMode(INDICATOR_LED_A, LED_ON);
        bi2c_kbd.disableNumKeys(false);
        break;

      // Pressing 'B' will toggle the associated LED on and off.
      case 'B':
        if (bi2c_kbd.getLEDMode(INDICATOR_LED_B) == LED_ON)
          bi2c_kbd.setLEDMode(INDICATOR_LED_B, LED_OFF);
        else
          bi2c_kbd.setLEDMode(INDICATOR_LED_B, LED_ON);
        break;
      
      // Pressing 'C' will toggle the associated LED on and off.
      case 'C':
        if (bi2c_kbd.getLEDMode(INDICATOR_LED_C) == LED_ON)
          bi2c_kbd.setLEDMode(INDICATOR_LED_C, LED_OFF);
        else
          bi2c_kbd.setLEDMode(INDICATOR_LED_C, LED_ON);
        break;
      
      // Pressing 'D' will toggle the associated LED on and off.
      case 'D':
        if (bi2c_kbd.getLEDMode(INDICATOR_LED_D) == LED_ON)
          bi2c_kbd.setLEDMode(INDICATOR_LED_D, LED_OFF);
        else
          bi2c_kbd.setLEDMode(INDICATOR_LED_D, LED_ON);
        break;
      
      // Pressing '*' will toggle the status LED on and off.
      case '*':
        if (bi2c_kbd.getLEDMode(STATUS_LED) == LED_ON)
          bi2c_kbd.setLEDMode(STATUS_LED, LED_OFF);
        else
          bi2c_kbd.setLEDMode(STATUS_LED, LED_ON);
        break;

      // Pressing '3' will start a 4Hz blink on the the LED associated
      // with the A button.
      case '3':
        if (bi2c_kbd.getLEDMode(INDICATOR_LED_A) != LED_BLINK_4HZ)
          bi2c_kbd.setLEDMode(INDICATOR_LED_A, LED_BLINK_4HZ);
        else
          bi2c_kbd.setLEDMode(INDICATOR_LED_A, LED_OFF);
        break;

      // Pressing '6' will start a 2Hz blink on the the LED associated
      // with the B button.
      case '6':
        if (bi2c_kbd.getLEDMode(INDICATOR_LED_B) != LED_BLINK_2HZ)
          bi2c_kbd.setLEDMode(INDICATOR_LED_B, LED_BLINK_2HZ);
        else
          bi2c_kbd.setLEDMode(INDICATOR_LED_B, LED_OFF);
        break;

      // Pressing '9' will start a 1Hz blink on the the LED associated
      // with the C button.
      case '9':
        if (bi2c_kbd.getLEDMode(INDICATOR_LED_C) != LED_BLINK_1HZ)
          bi2c_kbd.setLEDMode(INDICATOR_LED_C, LED_BLINK_1HZ);
        else
          bi2c_kbd.setLEDMode(INDICATOR_LED_C, LED_OFF);
        break;

      // Pressing '1' will disable the numeric key pad (including the *
      // and # buttons-
      case '1':
        bi2c_kbd.disableNumKeys();
        break;

      // Pressing '4' will disable the alpha (A-D) keys.
      case '4':
        bi2c_kbd.disableAlphaKeys();
        break;

      // Pressing '7' will enable the alpha (A-D) keys.
      case '7':
        bi2c_kbd.disableAlphaKeys(false);
        break;      

      // Pressing the '#' button will reset all LED engines.
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
