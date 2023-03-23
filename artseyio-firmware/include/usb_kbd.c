// ===================================================================================
// USB HID Consumer Keyboard Functions for CH551, CH552 and CH554
// ===================================================================================

#include "usb_kbd.h"
#include "usb_hid.h"
#include "usb_handler.h"
#include "usb_hid_keys.h"

// ===================================================================================
// Keyboard HID report
// ===================================================================================
__xdata uint8_t KBD_report[5] = {1,0,0,0,0};    // Max of 5 bytes required for Keyboard device

// ===================================================================================
// Press a key on a keyboard, for use with only KEY prefix macros
// ===================================================================================
void KBD_press(uint8_t key) {
  uint8_t last_free_index = 0;

  for (uint8_t i = 2; i < sizeof(KBD_report); ++i) {    // Loop through and check if the key already exists
    if(key == KBD_report[i]) return;                    // Return if key already pressed
    if (KBD_report[i] == KEY_NONE) last_free_index = i; // If this spot is free, remember it
  }

  if (last_free_index) {
    KBD_report[last_free_index] = key;              // Insert the key into the last free space in the report
    HID_sendReport(KBD_report, sizeof(KBD_report));   // send report
  }
}

// ===================================================================================
// Release a key on keyboard, for use with only KEY prefix macros
// ===================================================================================
void KBD_release(uint8_t key) {
  for (uint8_t i = 2; i < sizeof(KBD_report); ++i) {  // Loop through and check if the key is still pressed
    if(key == KBD_report[i]) {
      KBD_report[i] = KEY_NONE;                       // Unpress it
      HID_sendReport(KBD_report, sizeof(KBD_report)); // send report
      return;
    }
  }
}

// ===================================================================================
// Press and release a key on keyboard, for use with only KEY prefix macros
// ===================================================================================
void KBD_type(uint8_t key) {
  KBD_press(key);
  KBD_release(key);
}

// ===================================================================================
// Press a mod key on a keyboard, for use with only KEY_MOD prefix macros
// ===================================================================================
void KBD_mod_press(uint8_t key) {
  KBD_report[1] |= key;                           // set key in report
}

// ===================================================================================
// Release a mod key on a keyboard, for use with only KEY_MOD prefix macros
// ===================================================================================
void KBD_mod_release(uint8_t key) {
  KBD_report[1] &= !key;                      // release key in report
}

// ===================================================================================
// Release all mod keys on keyboard
// ===================================================================================
void KBD_mod_release_all() {
  KBD_report[1] = 0;
  HID_sendReport(KBD_report, sizeof(KBD_report));
}
