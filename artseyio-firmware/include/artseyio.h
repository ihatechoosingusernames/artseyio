// ===================================================================================
// ARTSEYIO Layout logic
// ===================================================================================

#pragma once

#include <stdint.h>
#include <usb_hid_keys.h>

// Delay between scans in ms
#define SCAN_DELAY 10

#define MOD_COMBINE(mod_key, reg_key) (mod_key << 8) | reg_key
#define GET_COMBINED_MOD(combined) combined >> 8
#define GET_COMBINED_KEY(combined) combined & 0xFF

typedef struct {
	uint8_t layer_mask;		// The key combination required to activate this layer
	const uint8_t layer_size;		// The number of keys in this layer
	uint16_t* layer_codes;	// An array of the key codes sent from this layer
	uint8_t* layer_keys;	// An array of the key states in this layer, mapped to the key codes by index
} KeyLayer;

// Reverse lookup for key layers
#define NUM_LAYERS 4

void set_key_state(uint8_t key_state);	// Updates the state of the keys as a byte
void tap_keys(uint8_t key_state);		// Handles tap layer keys
void hold_keys(uint8_t key_state);		// Handles hold layer keys
void press_key(uint16_t key_code);		// Presses a single key