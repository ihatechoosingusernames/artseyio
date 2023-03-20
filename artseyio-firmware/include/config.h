// ===================================================================================
// User Configurations for CH552E USB Rotary Encoder
// ===================================================================================

#pragma once

// Pin definitions
#define PIN_A P32
#define PIN_R P33
#define PIN_T P34
#define PIN_S P16
#define PIN_E P17
#define PIN_Y P31
#define PIN_I P30
#define PIN_O P11

// USB device descriptor
#define USB_VENDOR_ID       0x0000    // VID
#define USB_PRODUCT_ID      0x0000    // PID
#define USB_DEVICE_VERSION  0x0100    // v1.0 (BCD-format)

// USB configuration descriptor
#define USB_MAX_POWER_mA    50        // max power in mA 

// USB descriptor strings
#define MANUFACTURER_STR    'A','n','d','r','e','w','\'','s',' ','k','b'
#define PRODUCT_STR         'A','R','T','S','E','Y','I','O'
#define SERIAL_STR          'C','H','5','5','2','x','H','I','D'
#define INTERFACE_STR       'H','I','D','-','K','e','y','b','o','a','r','d'
