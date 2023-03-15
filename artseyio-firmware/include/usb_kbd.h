// ===================================================================================
// USB HID Keyboard Functions for CH551, CH552 and CH554
// ===================================================================================

#pragma once
#include <stdint.h>
#include "usb_hid.h"

// Functions
#define KBD_init() HID_init()         	// init keyboard

void KBD_press(uint8_t key);          	// press a key on keyboard
void KBD_release(uint8_t key);        	// release a key on keyboard
void KBD_type(uint8_t key);           	// press and release a key

void KBD_mod_press(uint8_t key);		// Press mod key
void KBD_mod_release(uint8_t key);		// Release mod key
void KBD_mod_release_all();				// Release all mod keys
