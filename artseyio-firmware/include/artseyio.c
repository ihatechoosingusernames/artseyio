#include "artseyio.h"
#include <usb_kbd.h>

// __code prefix stores this in code memory, so this array will be read only


// Brace Layer
__code const struct KeyLayer brace_layer = {
	.layer_mask = 0b10000000,	// Top left key held to activate
	.layer_size = 6,			// 6 keys in layer
	.layer_codes = {			// Output keys
		{
			.key_map = 0b11000000,
			.key_code = MOD_COMBINE(KEY_MOD_LSHIFT, KEY_9)
		},
		{
			.key_map = 0b10100000,
			.key_code = MOD_COMBINE(KEY_MOD_LSHIFT, KEY_0)
		},
		{
			.key_map = 0b10010000,
			.key_code = MOD_COMBINE(KEY_MOD_LSHIFT, KEY_LEFTBRACE)
		},
		{
			.key_map = 0b10000100,
			.key_code = KEY_LEFTBRACE
		},
		{
			.key_map = 0b10000010,
			.key_code = KEY_RIGHTBRACE
		},
		{
			.key_map = 0b10000001,
			.key_code = MOD_COMBINE(KEY_MOD_LSHIFT, KEY_RIGHTBRACE)
		}
	}
};

// Number Layer
__code const struct KeyLayer number_layer = {
	.layer_mask = 0b00010000,
	.layer_size = 10,
	.layer_codes = {
		{
			.key_map = 0b10010000,
			.key_code = KEY_1
		},
		{
			.key_map = 0b01010000,
			.key_code = KEY_2
		},
		{
			.key_map = 0b00110000,
			.key_code = KEY_3
		},
		{
			.key_map = 0b00011000,
			.key_code = KEY_4
		},
		{
			.key_map = 0b00010100,
			.key_code = KEY_5
		},
		{
			.key_map = 0b00010010,
			.key_code = KEY_6
		},
		{
			.key_map = 0b11000000,
			.key_code = KEY_7
		},
		{
			.key_map = 0b01100000,
			.key_code = KEY_8
		},
		{
			.key_map = 0b00011100,
			.key_code = KEY_9
		},
		{
			.key_map = 0b00010110,
			.key_code = KEY_0
		}
	},
};

// Symbol Layer
__code const struct KeyLayer symbol_layer = {
	.layer_mask = 0b00001000,
	.layer_size = 7,
	.layer_codes = {
		{
			.key_map = 0b10001000,
			.key_code = MOD_COMBINE(KEY_MOD_LSHIFT, KEY_1)
		},
		{
			.key_map = 0b01001000,
			.key_code = KEY_BACKSLASH
		},
		{
			.key_map = 0b00101000,
			.key_code = KEY_SEMICOLON
		},
		{
			.key_map = 0b00011000,
			.key_code = KEY_GRAVE
		},
		{
			.key_map = 0b00001100,
			.key_code = MOD_COMBINE(KEY_MOD_LSHIFT, KEY_SLASH)
		},
		{
			.key_map = 0b00001010,
			.key_code = KEY_MINUS
		},
		{
			.key_map = 0b00001001,
			.key_code = KEY_EQUAL
		}
	},
};

// Custom Layer
__code const struct KeyLayer custom_layer = {
	.layer_mask = 0b00000001,
	.layer_size = 6,
	.layer_codes = {
		{
			.key_map = 0b10000001,
			.key_code = KEY_MUTE
		},
		{
			.key_map = 0b01000001,
			.key_code = KEY_INSERT
		},
		{
			.key_map = 0b00100001,
			.key_code = KEY_VOLUMEUP
		},
		{
			.key_map = 0b00001001,
			.key_code = MOD_COMBINE(KEY_MOD_RSHIFT, KEY_NONE)
		},
		{
			.key_map = 0b00000101,
			.key_code = KEY_SYSRQ
		},
		{
			.key_map = 0b00000011,
			.key_code = KEY_VOLUMEDOWN
		}
	}
};

// Nav Layer
__code const struct KeyLayer navigation_layer = {
	.layer_mask = 0b01001010,
	.layer_size = 8,
	.layer_codes = {
		{
			.key_map = 0b10000000,
			.key_code = KEY_LEFT
		},
		{
			.key_map = 0b01000000,
			.key_code = KEY_UP
		},
		{
			.key_map = 0b00100000,
			.key_code = KEY_DOWN
		},
		{
			.key_map = 0b00010000,
			.key_code = KEY_RIGHT
		},
		{
			.key_map = 0b00001000,
			.key_code = KEY_HOME
		},
		{
			.key_map = 0b00000100,
			.key_code = KEY_PAGEUP
		},
		{
			.key_map = 0b00000010,
			.key_code = KEY_PAGEDOWN
		},
		{
			.key_map = 0b00000001,
			.key_code = KEY_END
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

// Alternate hold functions
__code const struct KeyLayer* hold_layers[] = {
	&brace_layer,
	&number_layer,
	&symbol_layer,
	&custom_layer
};

__code const struct KeyLayer* lock_layers[] = {
	&navigation_layer
};

__code const unsigned int hold_time = 250;	// How long in milliseconds constitutes holding vs tapping

uint8_t layer_state = 0;  	// This variable keeps track of the active layer
uint8_t prev_key_state = 0;	// The previous key state
uint8_t last_press = 0;		// The last key press that was handled

unsigned int hold_timer = 0;		// How long a key has been held for

struct KeyLayer* current_layer = 0;	// The currently selected alternate layer

void set_key_state(uint8_t key_state) {
	if ((key_state) && (prev_key_state == key_state)) {	// If a key is being held
		
		hold_timer += SCAN_DELAY;		// Update hold_timer

		if ((hold_timer > hold_time) && !layer_state)	// If key is held longer than timer, update
			search_layers(key_state, hold_layers, HOLD_LAYERS);

	// If keys are still being released from the last press
	} else if (last_press > key_state) {
		hold_timer = 0;
		last_press = key_state;

	// If a key has been released
	} else if (prev_key_state > key_state) {
		hold_timer = 0;					// Reset the hold timer

		// If the hold layer key has been released, only reset the layer state
		if ((layer_state | key_state) > key_state && search_layers(layer_state, hold_layers, HOLD_LAYERS)) {
			layer_state = 0;
		} else {
			tap_keys(prev_key_state);	// A key has been tapped
			last_press = key_state;
		}
	}

	prev_key_state = key_state;
}

void tap_keys(uint8_t key_state) {
	// Do a forward lookup for basic tap keys
	if (!layer_state) {
		// If tapped, use the tap key lookup
		if (tap_lookup[key_state] != KEY_NONE)
			return press_key(tap_lookup[key_state]);

		// If key not in tap key lookup, check in lock states
		search_layers(key_state, lock_layers, LOCK_LAYERS);

	// Do a reverse lookup for layered keys
	} else {
		// Find the correct key in the layer
		for (uint8_t key_index = 0; key_index < current_layer->layer_size; key_index++) {
			// Find the correct key combination
			if (current_layer->layer_codes[key_index].key_map == key_state)
				return press_key(current_layer->layer_codes[key_index].key_code);
		}

		// If key not found, check if it was the lock layer mask tapped again for release
		if (layer_state == key_state && search_layers(layer_state, lock_layers, LOCK_LAYERS))
			layer_state = 0;
	}
}

void press_key(uint16_t key_code) {
	uint8_t out_key = GET_COMBINED_KEY(key_code);
	uint8_t out_mod = GET_COMBINED_MOD(key_code);

	KBD_mod_press(out_mod);

	// In case of oneshot mods, no report is sent and the mod waits until the next key press
	if (out_key) {
		KBD_type(out_key);
		KBD_mod_release_all();	// Release the given mod as well as any other oneshot mods
	}
}

__bit search_layers(uint8_t key_state, __code const struct KeyLayer* layers[], uint8_t layer_size) {
	// Update the layer state mask if it is a valid layer
	for (uint8_t layer_index = 0; layer_index < layer_size; layer_index++) {
		if (layers[layer_index]->layer_mask == key_state) {
			current_layer = layers[layer_index];
			layer_state = key_state;
			return 1;
		}
	}

	return 0;
}