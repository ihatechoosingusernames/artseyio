// ===================================================================================
// Project:   USB Rotary Encoder for CH551, CH552 and CH554
// Version:   v1.0
// Year:      2023
// Author:    Stefan Wagner
// Github:    https://github.com/wagiminator
// EasyEDA:   https://easyeda.com/wagiminator
// License:   http://creativecommons.org/licenses/by-sa/3.0/
// ===================================================================================
//
// Description:
// ------------
// Implements the ARTSEYIO format in a keyboard
//
// References:
// -----------
// - Blinkinlabs: https://github.com/Blinkinlabs/ch554_sdcc
// - Deqing Sun: https://github.com/DeqingSun/ch55xduino
// - Ralph Doncaster: https://github.com/nerdralph/ch554_sdcc
// - WCH Nanjing Qinheng Microelectronics: http://wch.cn
// - ATtiny85 TinyKnob: https://github.com/wagiminator/ATtiny85-TinyKnob
//
// Compilation Instructions:
// -------------------------
// - Chip:  CH551, CH552 or CH554
// - Clock: min. 12 MHz internal
// - Adjust the firmware parameters in include/config.h if necessary.
// - Make sure SDCC toolchain and Python3 with PyUSB is installed.
// - Press BOOT button on the board and keep it pressed while connecting it via USB
//   with your PC.
// - Run 'make flash'.
//
// Operating Instructions:
// -----------------------
// - Connect the board via USB to your PC. It should be detected as a HID device.
// - Turn the rotary endoder to increase/decrease volume.
// - Press rotary encoder button to mute.


// ===================================================================================
// Libraries, Definitions and Macros
// ===================================================================================

// Libraries
#include <config.h>                       // user configurations
#include <system.h>                       // system functions
#include <delay.h>                        // delay functions
#include <gpio.h>                         // GPIO functions
#include <usb_kbd.h>                      // USB HID consumer keyboard functions
#include <artseyio.h>                     // ARTSEYIO Layer logic

#define READ_PIN_BIT(PIN, BIT) ((PIN_read(PIN) ? 0x00 : 0x01) << BIT)

// Prototypes for used interrupts
void USB_interrupt(void);
void USB_ISR(void) __interrupt(INT_NO_USB) {
  USB_interrupt();
}

// ===================================================================================
// Main Function
// ===================================================================================
void main(void) {

  // Setup
  CLK_config();                           // configure system clock
  DLY_ms(5);                              // wait for clock to settle
  KBD_init();                             // init USB HID keyboard
  WDT_start();                            // start watchdog timer

  uint8_t input_key_state;

  PIN_input_PU(PIN_A);                    // Set input pins with pullups
  PIN_input_PU(PIN_R);
  PIN_input_PU(PIN_T);
  PIN_input_PU(PIN_S);
  PIN_input_PU(PIN_E);
  PIN_input_PU(PIN_Y);
  PIN_input_PU(PIN_I);
  PIN_input_PU(PIN_O);

  // Loop
  while(1) {
    DLY_ms(SCAN_DELAY);                    // a little delay (latch + debounce)
    WDT_reset();                           // reset watchdog

    input_key_state = 0x00;                // reset key state
    
    // Read GPIOS connected to keys
    input_key_state |= READ_PIN_BIT(PIN_A, 7);
    input_key_state |= READ_PIN_BIT(PIN_R, 6);
    input_key_state |= READ_PIN_BIT(PIN_T, 5);
    input_key_state |= READ_PIN_BIT(PIN_S, 4);
    input_key_state |= READ_PIN_BIT(PIN_E, 3);
    input_key_state |= READ_PIN_BIT(PIN_Y, 2);
    input_key_state |= READ_PIN_BIT(PIN_I, 1);
    input_key_state |= READ_PIN_BIT(PIN_O, 0);

    // Update key states
    set_key_state(input_key_state);
  }
}