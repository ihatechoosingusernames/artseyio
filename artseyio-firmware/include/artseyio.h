// ===================================================================================
// ARTSEYIO Layout logic
// ===================================================================================

#pragma once

#include <stdint.h>
#include <usb_hid_keys.h>

// Delay between scans in ms
#define SCAN_DELAY 10

// Number of alternate key layers
#define NUM_LAYERS 4

#define MOD_COMBINE(mod_key, reg_key) ((uint16_t)mod_key << 8) | reg_key
#define GET_COMBINED_MOD(combined) combined >> 8
#define GET_COMBINED_KEY(combined) combined & 0xFF

struct KeyLayer {
	uint8_t layer_mask;		// The key combination required to activate this layer
	uint8_t layer_size;		// The number of keys in this layer
	struct KeyMap {
		uint8_t key_map;
		uint16_t key_code;
	} layer_codes[];		// An array of the key codes sent from this layer
};

void set_key_state(uint8_t key_state);	// Updates the state of the keys as a byte
void tap_keys(uint8_t key_state);		// Handles tap layer keys
void hold_keys(uint8_t key_state);		// Handles hold layer keys
void press_key(uint16_t key_code);		// Presses a single key