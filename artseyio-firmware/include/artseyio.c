#include "artseyio.h"
#include <usb_kbd.h>

__code long hold_time = 300;	// How long in milliseconds constitutes holding vs tapping

// __code prefix stores this in code memory, so this array will be read only
__code const KeyLayer* hold_layers[NUM_LAYERS] = { // Alternate hold functions
	// Brace Layer
	{
		0b10000000,	// Top left key held to activate
		6,			// 6 keys in layer
		{			// Output keys
			MOD_COMBINE(KEY_MOD_LSHIFT, KEY_9),
			MOD_COMBINE(KEY_MOD_LSHIFT, KEY_0),
			MOD_COMBINE(KEY_MOD_LSHIFT, KEY_LEFTBRACE),
			KEY_LEFTBRACE,
			KEY_RIGHTBRACE,
			MOD_COMBINE(KEY_MOD_LSHIFT, KEY_RIGHTBRACE)
		},
		{			// Key mappings for the above output keys
			0b01000000,
			0b00100000,
			0b00010000,
			0b00000100,
			0b00000010,
			0b00000001
	} },

	// Number Layer
	{
		0b00010000,
		10,
		{
			KEY_1,
			KEY_2,
			KEY_3,
			KEY_4,
			KEY_5,
			KEY_6,
			KEY_7,
			KEY_8,
			KEY_9,
			KEY_0
		},
		{
			0b10000000,
			0b01000000,
			0b00100000,
			0b00001000,
			0b00000100,
			0b00000010,
			0b11000000,
			0b01100000,
			0b00001100,
			0b00000110
		}
	},

	// Symbol Layer
	{
		0b00001000,
		7,
		{
			MOD_COMBINE(KEY_MOD_LSHIFT, KEY_1),
			KEY_BACKSLASH,
			KEY_SEMICOLON,
			KEY_GRAVE,
			MOD_COMBINE(KEY_MOD_LSHIFT, KEY_SLASH),
			KEY_MINUS,
			KEY_EQUAL
		},
		{
			0b10000000,
			0b01000000,
			0b00100000,
			0b00010000,
			0b00000100,
			0b00000010,
			0b00000001
		}
	},

	// Custom Layer
	{
		0b00000001,
		6,
		{
			KEY_MUTE,
			KEY_INSERT,
			KEY_VOLUMEUP,
			MOD_COMBINE(KEY_MOD_RSHIFT, KEY_NONE),
			KEY_SYSRQ,
			KEY_VOLUMEDOWN
		},
		{
			0b10000000,
			0b01000000,
			0b00100000,
			0b00001000,
			0b00000100,
			0b00000010
		}
	}
};

// Lookup for the tap codes. High Bytes are MOD keys, low bytes are regular keys.
// The index in binary is the state of the keys for that tap code. This trades off memory space for speed.
__code const uint16_t tap_lookup[0xF1] = {
	KEY_NONE,
	KEY_O,		// 0000 0001
	KEY_I,		// 0000 0010
	KEY_N,		// 0000 0011
	KEY_Y,		// 0000 0100
	KEY_K,		// 0000 0101
	KEY_U,		// 0000 0110
	KEY_M,		// 0000 0111
	KEY_E,		// 0000 1000
	KEY_B,		// 0000 1001
	KEY_H,		// 0000 1010
	KEY_P,		// 0000 1011
	KEY_C,		// 0000 1100
	KEY_NONE,
	KEY_L,		// 0000 1110
	KEY_SPACE,	// 0000 1111
	KEY_S,		// 0001 0000
	KEY_NONE,
	MOD_COMBINE(KEY_MOD_LALT, KEY_NONE),	// 0001 0010
	KEY_NONE,
	MOD_COMBINE(KEY_LEFTMETA, KEY_NONE),	// 0001 0100
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	MOD_COMBINE(KEY_MOD_LCTRL, KEY_NONE),	// 0001 1000
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_T,		// 0010 0000
	KEY_NONE,
	MOD_COMBINE(KEY_MOD_LSHIFT, KEY_1),	// 0010 0010
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_J,		// 0011 0000
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_R, 		// 0100 0000
	KEY_NONE,
	KEY_DELETE,	// 0100 0010
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_BACKSPACE,	// 0100 1000
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_V,		// 0101 0000
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_G,		// 0110 0000
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_X,		// 0111 0000
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	MOD_COMBINE(KEY_MOD_LSHIFT, KEY_NONE),	// 0111 1000
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_A, 		// 1000 0000
	KEY_SLASH,	// 1000 0001
	MOD_COMBINE(KEY_MOD_LSHIFT, KEY_APOSTROPHE),	// 1000 0010
	KEY_NONE,
	KEY_DOT,	// 1000 0100
	KEY_NONE,
	KEY_APOSTROPHE,	// 1000 0110
	KEY_CAPSLOCK,	// 1000 0111
	KEY_ENTER, 	// 1000 1000
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_W,		// 1001 0000
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_Q,		// 1011 0000
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_F,		// 1100 0000
	KEY_ESC,	// 1100 0001
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_D,		// 1110 0000
	KEY_TAB,	// 1110 0001
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_NONE,
	KEY_Z		// 1111 0000
};

uint8_t layer_state = 0;  	// This variable keeps track of the active layer
uint8_t prev_key_state = 0;	// The previous key state
long hold_timer = 0;		// How long a key has been held for

void set_key_state(uint8_t key_state) {
	if (prev_key_state == key_state) {	// If a key is being held
		
		hold_timer += SCAN_DELAY;		// Update hold_timer

		if (hold_timer > hold_time && !layer_state) hold_keys(key_state);
	} else if (prev_key_state > key_state) {	// If a key has been released
		hold_timer = 0;					// Reset the hold timer

		// If the hold layer key has been released, only reset the layer state
		if (layer_state && (layer_state | key_state) <= key_state)
			layer_state = 0;
		else
			tap_keys(prev_key_state);	// A key has been tapped
	}

	prev_key_state = key_state;
}

void tap_keys(uint8_t key_state) {
	// Do a forward lookup for basic tap keys
	if (!layer_state) {
		// If tapped, use the tap key lookup
		press_key(tap_lookup[key_state]);
	// Do a reverse lookup for layered keys
	} else {
		// Subtract layer state from key state
		key_state &= !layer_state;

		// Look up the relevant layer
		for (uint8_t layer_index = 0; layer_index < NUM_LAYERS; layer_index++) {
			if (hold_layers[layer_index]->layer_mask == layer_state) {

				// Find the correct key in the layer
				for (uint8_t key_index = 0; key_index < hold_layers[layer_index]->layer_size; key_index++) {
					if (hold_layers[layer_index]->layer_keys[key_index] == key_state)
						press_key(hold_layers[layer_index]->layer_codes[key_index]);
				}
			}
		}
	}
}

void hold_keys(uint8_t key_state) {
	// Update the layer state mask if it is a valid layer
	for (uint8_t layer_index = 0; layer_index < NUM_LAYERS; layer_index++) {
		if (hold_layers[layer_index]->layer_mask == key_state)
			layer_state = key_state;
	}
}

void press_key(uint16_t key_code) {
	uint8_t out_key = GET_COMBINED_KEY(key_code);
	uint8_t out_mod = GET_COMBINED_MOD(key_code);

	// KBD_mod_press(out_mod);

	// In case of oneshot mods, no report is sent and the mod waits until the next key press
	if (out_key) {
		KBD_type(out_key);
		KBD_mod_release_all();	// Release the given mod as well as any other oneshot mods
	}
}