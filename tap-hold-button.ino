// Ref: https://github.com/JChristensen/JC_Button
#include <JC_Button.h>

const int PIN_FOOTSWITCH = 5;
const unsigned long LONG_PRESS_THRESHOLD = 600;
const unsigned long DOUBLE_TAP_THRESHOLD = 300;

Button footSwitch(PIN_FOOTSWITCH, 50);

bool isMomentaryActive = false; // Momentary state.
bool isLatchModeActive = false; // Latch mode state.
bool isSkipNextRelease = false; // flag to skip release after double tap
unsigned long footSwitchPressedAt = 0;
unsigned long lastFootSwitchPressedTime = 0;

void setup() {
  footSwitch.begin();
  Serial.begin(9600);
}

void loop() {
  footSwitch.read();

  if (footSwitch.wasPressed()) {
    unsigned long now = millis();

    if (isLatchModeActive) {
      if (now - footSwitchPressedAt < DOUBLE_TAP_THRESHOLD) {
        // Double tap: exit latch mode
        isMomentaryActive = false;
        isLatchModeActive = false;
        isSkipNextRelease = true;
        Serial.println("MODE: LATCH OFF");
        return;
      }
    } else {
      // Start momentary mode
      isMomentaryActive = true;
      Serial.println("MODE: MOMENTARY ON");
    }

    footSwitchPressedAt = now;
  }

  if (footSwitch.wasReleased()) {
    if (isSkipNextRelease) {
       // Ignore this release due to prior double tap
      isSkipNextRelease = false;
      Serial.println("RELEASE SKIPPED");
      return;
    }

    if (millis() - footSwitchPressedAt < LONG_PRESS_THRESHOLD) {
      // Short press: cancel momentary mode on
      if (isMomentaryActive) {
        isMomentaryActive = false;
        Serial.println("MODE: MOMENTARY CANCEL");
      }

      if (isLatchModeActive) {
        // Latch tap
        Serial.println("MODE: LATCH TAP");
      } else {
        // First tap to enter latch mode
        Serial.println("MODE: LATCH ON");
      }
      isLatchModeActive = true;

    } else {
      if (isMomentaryActive) {
        // Long press release
        isMomentaryActive = false;
        Serial.println("MODE: MOMENTARY OFF");
      }
    }
  }
}
