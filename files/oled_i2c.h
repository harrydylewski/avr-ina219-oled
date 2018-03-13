#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/twi.h>
#include "i2c.h"

#ifndef OLED_I2C_H
#define OLED_I2C_H




#define FONT5_MAXCHARS 25

#define OLED_ADD 0x78 //? try 3D or 3B , 3c is default or 78?


#define CONSTRAST_RESET_CMD 0x7F
#define CONTRAST_CMD 0x81

#define DISPLAYRAM_CMD 0xA4
#define DISPLAYALL_CMD 0xA5

#define NORMAL_DISPLAY_CMD 0xA6  //
#define INVERSE_DISPLAY_CMD 0xA7

#define DISPLAY_OFF_CMD 0xAE // sleep/reset
#define DISPLAY_ON_CMD  0xAF //display on in normal mode

#define RIGHT_SCROLL 0x26
#define LEFT_SCROLLL 0x27
#define UPRIGHT_SCROL 0x29
#define UPLEFT_SCROLL 0x2A

enum OLED_PAGES
{
PAGE0,
PAGE1,
PAGE2,
PAGE3,
PAGE4,
PAGE5,
PAGE6,
PAGE7
};

enum OLED_FRAMES
{
FRAMES5,
FRAMES64,
FRAMES128,
FRAMES256,
FRAMES3,
FRAMES4,
FRAMES2,
};

#define START_ADDRESS 0x00
#define END_ADDRESS   0x10

#define ADDRESS_MODE_ADD 0x20 

#define HORIZONTAL_MODE_CMD 0x20 //horizontal add mode
#define VERTICAL_MODE_CMD   0x21 //vertical add mode
#define SETPAGE__MODECMD    0x22 // page addr + resets pointers for mode
#define INVALID_CMD         0x23 //do not use

#define COLUMN_ADD 21
#define SET_PAGE_ADD 22

#define PAGE_CMD 0xB0

#define CONTRAST_ADD 0x81
#define CONTRAST_DEF_CMD 0x80


///

//HARDWARE DEFINES
#define SEGMENT_NOREMAP_CMD 0xA0
#define SEGMENT_REMAP_CMD  0xA1
#define COM_NOREMAP_CMD 0xC0
#define COM_REMAP_CMD   0xC8

//
#define CLOCKDIV_ADD     0xD5
#define CLOCKDIV_DEF_CMD 0x80

//
#define DISPLAYOFFSET_CMD 0xD3

//CHARGE PUMP
//if 
#define CHARGEPUMP_ADD            0x8D
#define CHARGEPUMP_ENABLE_CMD     0x14
#define CHARGEPUMP_DISENABLE_CMD  0x10

//MUX Ratio
#define MUX_ADD    0xA8
#define MUX_32_CMD 0x1F //32
#define MUX_64_CMD 0x3F //64

//display offsets
#define DISPLAY_OFFSET_ADD         0xD3
#define DISPLAY_OFFSET_DISABLE_CMD 0x00

//display startline
#define DISPLAY_STARTLINE_DEF_CMD 40

//com pin ocnfig
#define COMPIN_ADD 0xDA
#define COMPIN_CMD 0x02

// OSC FREQ
#define OSC_FREQ_ADD     0xD5
#define OSC_FREQ_DEF_CMD 0x80

//
#define DISPLAY_ENABLE_CMD      0xAF
#define DISPLAY_DISABLE_CMD 0xA4

//
#define PAGEADD_LN_0_CMD 0x00
#define PAGEADD_HN_0_CMD 0x10

//
#define PAGE_END 128
#define MAX_CHARS 26
#define ASCII_OFFSET 32 //my font starts at 0x20 which is space

//i2c stuff---------------------------------------
#define CONTINUE_DATA    0x40
#define CONTINUE_CMD     0x00

#define NO_CONTINUE_DATA 0xC0
#define NO_CONTINUE_CMD  0x80
//-----------------------------------------------
#define _CMD_PAGE0 0xB0
#define _CMD_PAGE1 0xB1
#define _CMD_PAGE2 0xB2
#define _CMD_PAGE3 0xB3
#define _CMD_PAGE4 0xB4
#define _CMD_PAGE5 0xB5
#define _CMD_PAGE6 0xB6
#define _CMD_PAGE7 0xB7


#define DUMMY_BYTE_00 0x00
#define DUMMY_BYTE_FF 0xFF

//frames for scrolling----------------------------------------------
//more frames = slower, less frames = faster
//2 =fastest, 256 = slowest
//25 or 64 are the preferable default values
//--------------------------------------------

#define SCROLL_STOP_CMD  0x2E
#define SCROLL_START_CMD 0x2F



//
void oled_init_def32(unsigned char address);

typedef struct
{
	unsigned char page_buffer[128];
	unsigned char address;
} OLED;

typedef struct
{
	unsigned char contrast;

} OLED_SETTINGS;


// send cmds


void oled_sel_page(void);

//specific settings that need multiple bytes
void oled_wr_contrast(unsigned char address, unsigned char constrast);

// memory mode selection
void oled_select_page(unsigned char address, unsigned char page);
void oled_wr_page(OLED *ptr, unsigned char end);

void oled_page_startcolumn(unsigned char address, unsigned char position);
void oled_wr_cmd(unsigned char address, unsigned char cmd);
void oled_config_hs(unsigned char address, unsigned char s_page,unsigned char e_page, unsigned time,unsigned char direction);

void oled_clear_display(OLED *ptr);

void oled_output_page(const char *translate_array);
void oled_write_display(unsigned char address, const char *msg, unsigned char column, unsigned char page);



#endif

