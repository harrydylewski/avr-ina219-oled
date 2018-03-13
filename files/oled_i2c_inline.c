#include "oled_i2c_inline.h"
//------------------------------------------------------------

const char font[] PROGMEM =
{
    0x00, 0x00, 0x00, 0x00, 0x00, // (space) 0
    0x00, 0x00, 0x5F, 0x00, 0x00, // !
    0x00, 0x07, 0x00, 0x07, 0x00, // "
    0x14, 0x7F, 0x14, 0x7F, 0x14, // #
    0x24, 0x2A, 0x7F, 0x2A, 0x12, // $
    0x23, 0x13, 0x08, 0x64, 0x62, // %       5
    0x36, 0x49, 0x55, 0x22, 0x50, // &
    0x00, 0x05, 0x03, 0x00, 0x00, // '
    0x00, 0x1C, 0x22, 0x41, 0x00, // (
    0x00, 0x41, 0x22, 0x1C, 0x00, // )
    0x08, 0x2A, 0x1C, 0x2A, 0x08, // *       10
    0x08, 0x08, 0x3E, 0x08, 0x08, // +
    0x00, 0x50, 0x30, 0x00, 0x00, // ,
    0x08, 0x08, 0x08, 0x08, 0x08, // -
    0x00, 0x60, 0x60, 0x00, 0x00, // .
    0x20, 0x10, 0x08, 0x04, 0x02, // /      15
    0x3E, 0x51, 0x49, 0x45, 0x3E, // 0
    0x00, 0x42, 0x7F, 0x40, 0x00, // 1
    0x42, 0x61, 0x51, 0x49, 0x46, // 2
    0x21, 0x41, 0x45, 0x4B, 0x31, // 3
    0x18, 0x14, 0x12, 0x7F, 0x10, // 4      20
    0x27, 0x45, 0x45, 0x45, 0x39, // 5
    0x3C, 0x4A, 0x49, 0x49, 0x30, // 6
    0x01, 0x71, 0x09, 0x05, 0x03, // 7
    0x36, 0x49, 0x49, 0x49, 0x36, // 8
    0x06, 0x49, 0x49, 0x29, 0x1E, // 9      25
    0x00, 0x36, 0x36, 0x00, 0x00, // :
    0x00, 0x56, 0x36, 0x00, 0x00, // ;
    0x00, 0x08, 0x14, 0x22, 0x41, // <
    0x14, 0x14, 0x14, 0x14, 0x14, // =
    0x41, 0x22, 0x14, 0x08, 0x00, // >      30
    0x02, 0x01, 0x51, 0x09, 0x06, // ?
    0x32, 0x49, 0x79, 0x41, 0x3E, // @
    0x7E, 0x11, 0x11, 0x11, 0x7E, // A
    0x7F, 0x49, 0x49, 0x49, 0x36, // B
    0x3E, 0x41, 0x41, 0x41, 0x22, // C      35
    0x7F, 0x41, 0x41, 0x22, 0x1C, // D     
    0x7F, 0x49, 0x49, 0x49, 0x41, // E
    0x7F, 0x09, 0x09, 0x01, 0x01, // F
    0x3E, 0x41, 0x41, 0x51, 0x32, // G
    0x7F, 0x08, 0x08, 0x08, 0x7F, // H
    0x00, 0x41, 0x7F, 0x41, 0x00, // I
    0x20, 0x40, 0x41, 0x3F, 0x01, // J
    0x7F, 0x08, 0x14, 0x22, 0x41, // K
    0x7F, 0x40, 0x40, 0x40, 0x40, // L
    0x7F, 0x02, 0x04, 0x02, 0x7F, // M
    0x7F, 0x04, 0x08, 0x10, 0x7F, // N
    0x3E, 0x41, 0x41, 0x41, 0x3E, // O
    0x7F, 0x09, 0x09, 0x09, 0x06, // P
    0x3E, 0x41, 0x51, 0x21, 0x5E, // Q
    0x7F, 0x09, 0x19, 0x29, 0x46, // R
    0x46, 0x49, 0x49, 0x49, 0x31, // S
    0x01, 0x01, 0x7F, 0x01, 0x01, // T
    0x3F, 0x40, 0x40, 0x40, 0x3F, // U
    0x1F, 0x20, 0x40, 0x20, 0x1F, // V
    0x7F, 0x20, 0x18, 0x20, 0x7F, // W
    0x63, 0x14, 0x08, 0x14, 0x63, // X
    0x03, 0x04, 0x78, 0x04, 0x03, // Y
    0x61, 0x51, 0x49, 0x45, 0x43, // Z
    0x00, 0x00, 0x7F, 0x41, 0x41, // [
    0x02, 0x04, 0x08, 0x10, 0x20, // "\"
    0x41, 0x41, 0x7F, 0x00, 0x00, // ]
    0x04, 0x02, 0x01, 0x02, 0x04, // ^
    0x40, 0x40, 0x40, 0x40, 0x40, // _
    0x00, 0x01, 0x02, 0x04, 0x00, // `
    0x20, 0x54, 0x54, 0x54, 0x78, // a
    0x7F, 0x48, 0x44, 0x44, 0x38, // b
    0x38, 0x44, 0x44, 0x44, 0x20, // c
    0x38, 0x44, 0x44, 0x48, 0x7F, // d
    0x38, 0x54, 0x54, 0x54, 0x18, // e
    0x08, 0x7E, 0x09, 0x01, 0x02, // f
    0x08, 0x14, 0x54, 0x54, 0x3C, // g
    0x7F, 0x08, 0x04, 0x04, 0x78, // h
    0x00, 0x44, 0x7D, 0x40, 0x00, // i
    0x20, 0x40, 0x44, 0x3D, 0x00, // j
    0x00, 0x7F, 0x10, 0x28, 0x44, // k
    0x00, 0x41, 0x7F, 0x40, 0x00, // l
    0x7C, 0x04, 0x18, 0x04, 0x78, // m
    0x7C, 0x08, 0x04, 0x04, 0x78, // n
    0x38, 0x44, 0x44, 0x44, 0x38, // o
    0x7C, 0x14, 0x14, 0x14, 0x08, // p
    0x08, 0x14, 0x14, 0x18, 0x7C, // q
    0x7C, 0x08, 0x04, 0x04, 0x08, // r
    0x48, 0x54, 0x54, 0x54, 0x20, // s
    0x04, 0x3F, 0x44, 0x40, 0x20, // t
    0x3C, 0x40, 0x40, 0x20, 0x7C, // u
    0x1C, 0x20, 0x40, 0x20, 0x1C, // v
    0x3C, 0x40, 0x30, 0x40, 0x3C, // w
    0x44, 0x28, 0x10, 0x28, 0x44, // x
    0x0C, 0x50, 0x50, 0x50, 0x3C, // y
    0x44, 0x64, 0x54, 0x4C, 0x44, // z
    0x00, 0x08, 0x36, 0x41, 0x00, // {
    0x00, 0x00, 0x7F, 0x00, 0x00, // |
    0x00, 0x41, 0x36, 0x08, 0x00, // }
    0x08, 0x08, 0x2A, 0x1C, 0x08, // ->
    0x08, 0x1C, 0x2A, 0x08, 0x08  // <-
 };
 
const char default_init[] PROGMEM =
{
MUX_ADD,                    MUX_32_CMD,                    DISPLAY_OFFSET_ADD,   DISPLAY_OFFSET_DISABLE_CMD,
DISPLAY_STARTLINE_DEF_CMD,  SEGMENT_NOREMAP_CMD,           COM_NOREMAP_CMD,      COMPIN_ADD,
COMPIN_CMD,                 CONTRAST_ADD,CONTRAST_DEF_CMD, DISPLAY_DISABLE_CMD,  NORMAL_DISPLAY_CMD, 
OSC_FREQ_ADD,               OSC_FREQ_DEF_CMD,              CHARGEPUMP_ADD,       CHARGEPUMP_ENABLE_CMD, 
DISPLAY_ON_CMD
};

//--------------------------------------------------
unsigned char oled_initDefault32(unsigned char address)
{
	i2c_start();
		if((TWSR & 0xF8) != TW_START)
		return 1;
	//
	i2c_write(address);
		if ( ((TWSR & 0xF8) != TW_MT_SLA_ACK) && ((TWSR & 0xF8) != TW_MR_SLA_ACK) )
		return 1;

	i2c_write(CONTINUE_CMD);
		if( (TWSR & 0xF8) != TW_MT_DATA_ACK )
		return 1;	
		 
	for(unsigned char x=0;x<ARR_SIZE(default_init);x++)
	{
		i2c_write(pgm_read_byte(&default_init[x]));
			if( (TWSR & 0xF8) != TW_MT_DATA_ACK )
			return 1;
	}

	i2c_stop();

	return 0;

}

unsigned char oled_pageAddressScheme(unsigned char address)
{
	i2c_start();
		if((TWSR & 0xF8) != TW_START)
		return 1;

	i2c_write(address);
		if ( ((TWSR & 0xF8) != TW_MT_SLA_ACK) && ((TWSR & 0xF8) != TW_MR_SLA_ACK) )
		return 1;

	i2c_write(CONTINUE_CMD);
		if( (TWSR & 0xF8) != TW_MT_DATA_ACK )
		return 1;
		/*
	i2c_write(SETPAGE_MODECMD);
		if( (TWSR & 0xF8) != TW_MT_DATA_ACK )
		return 1;
	*/
	i2c_write(PAGEADD_LN_0_CMD);
		if( (TWSR & 0xF8) != TW_MT_DATA_ACK )
		return 1;
		
	i2c_write(PAGEADD_HN_0_CMD);
		if( (TWSR & 0xF8) != TW_MT_DATA_ACK )
		return 1;

	i2c_stop();

	return 0;
}

unsigned char oled_selectPageAndColumn(unsigned char address, unsigned char page, unsigned char column)
{

	unsigned char high_nib;
	unsigned char low_nib;

	i2c_start();
		if((TWSR & 0xF8) != TW_START)
		return 1;

	i2c_write(address);
		if ( ((TWSR & 0xF8) != TW_MT_SLA_ACK) && ((TWSR & 0xF8) != TW_MR_SLA_ACK) )
		return 1;

	i2c_write(CONTINUE_CMD);
		if( (TWSR & 0xF8) != TW_MT_DATA_ACK )
		return 1;

	i2c_write(PAGE_CMD+page);
		if( (TWSR & 0xF8) != TW_MT_DATA_ACK )
		return 1;

	if(column>15)
	{
		high_nib=0x10+((column>>4)&0x0F);
		low_nib=column&0x0F;
	}

	else
	{
		high_nib=0x10;
		low_nib=column;
	}

	i2c_write(low_nib);
		if( (TWSR & 0xF8) != TW_MT_DATA_ACK )
		return 1;

	i2c_write(high_nib);
		if( (TWSR & 0xF8) != TW_MT_DATA_ACK )
		return 1;

	i2c_stop();

	return 0;

}


unsigned char oled_writeBufferToPage(OLED *ptr)
{
	unsigned char x=0;
	//ptr->buffer_limit=0;

	i2c_start();
	if((TWSR & 0xF8) != TW_START)
	return 1;

	i2c_write(ptr->address);
	if ( ((TWSR & 0xF8) != TW_MT_SLA_ACK) && ((TWSR & 0xF8) != TW_MR_SLA_ACK) )
	return 1;
	
	i2c_write(CONTINUE_DATA);
	if( (TWSR & 0xF8) != TW_MT_DATA_ACK )
	return 1;

	for(x=0;x<ptr->buffer_limit;x++)
	{
		i2c_write(ptr->page_buffer[x]);
			if( (TWSR & 0xF8) != TW_MT_DATA_ACK )
			return 1;
	}

	i2c_stop();

	return 0;
}

unsigned char oled_writeCommand(unsigned char address, unsigned char cmd)
{
	i2c_start();
		if((TWSR & 0xF8) != TW_START)
		return 1;

	i2c_write(address);
		if ( ((TWSR & 0xF8) != TW_MT_SLA_ACK) && ((TWSR & 0xF8) != TW_MR_SLA_ACK) )
		return 1;

	i2c_write(NO_CONTINUE_CMD);
		if( (TWSR & 0xF8) != TW_MT_DATA_ACK )
		return 1;
	
	i2c_write(cmd);
		if( (TWSR & 0xF8) != TW_MT_DATA_ACK )
		return 1;
	
	i2c_stop();

	return 0;
}

unsigned char oled_writeContrast(unsigned char address, unsigned char contrast)
{

	i2c_start();
		if((TWSR & 0xF8) != TW_START)
		return 1;

	i2c_write(address);
		if ( ((TWSR & 0xF8) != TW_MT_SLA_ACK) && ((TWSR & 0xF8) != TW_MR_SLA_ACK) )
		return 1;

	i2c_write(CONTINUE_CMD);
		if( (TWSR & 0xF8) != TW_MT_DATA_ACK )
		return 1;			
	
	i2c_write(CONTRAST_ADD);
		if( (TWSR & 0xF8) != TW_MT_DATA_ACK )
		return 1;

	i2c_write(contrast);
		if( (TWSR & 0xF8) != TW_MT_DATA_ACK )
		return 1;

	i2c_stop();

	return 0;
}


unsigned char oled_HorizontalScroll(unsigned char address, unsigned char start_page,unsigned char end_page, unsigned char frames,unsigned char direction)
{
	i2c_start();
		if((TWSR & 0xF8) != TW_START)
		return 1;

	i2c_write(address);
		if ( ((TWSR & 0xF8) != TW_MT_SLA_ACK) && ((TWSR & 0xF8) != TW_MR_SLA_ACK) )
		return 1;

	i2c_write(CONTINUE_CMD);
		if( (TWSR & 0xF8) != TW_MT_DATA_ACK )
		return 1; 

	i2c_write(direction);
		if( (TWSR & 0xF8) != TW_MT_DATA_ACK )
		return 1;	
	
	i2c_write(DUMMY_BYTE_00);
		if( (TWSR & 0xF8) != TW_MT_DATA_ACK )
		return 1;

	i2c_write(start_page);
		if( (TWSR & 0xF8) != TW_MT_DATA_ACK )
		return 1;

	i2c_write(frames);
		if( (TWSR & 0xF8) != TW_MT_DATA_ACK )
		return 1;	
			
	i2c_write(end_page);
		if( (TWSR & 0xF8) != TW_MT_DATA_ACK )
		return 1;	

	i2c_write(DUMMY_BYTE_00);
		if( (TWSR & 0xF8) != TW_MT_DATA_ACK )
		return 1;	

	i2c_write(DUMMY_BYTE_FF);
		if( (TWSR & 0xF8) != TW_MT_DATA_ACK )
		return 1;	

	i2c_write(SCROLL_START_CMD);
		if( (TWSR & 0xF8) != TW_MT_DATA_ACK )
		return 1;

	i2c_stop();

	return 0;
} 

unsigned char oled_clearDisplay(unsigned char oled_address)
{
	unsigned char x,y;

	for(x=0;x<8;x++)
	{	
			
		i2c_start();
			if((TWSR & 0xF8) != TW_START)
			return 1;

		i2c_write(oled_address);
			if ( ((TWSR & 0xF8) != TW_MT_SLA_ACK) && ((TWSR & 0xF8) != TW_MR_SLA_ACK) )
			return 1;

		i2c_write(NO_CONTINUE_CMD);
			if( (TWSR & 0xF8) != TW_MT_DATA_ACK )
			return 1;

		i2c_write(PAGE_CMD+x);
			if( (TWSR & 0xF8) != TW_MT_DATA_ACK )
			return 1;

		i2c_stop();	

		i2c_start();
			if((TWSR & 0xF8) != TW_START)
			return 1;

		i2c_write(oled_address);
			if ( ((TWSR & 0xF8) != TW_MT_SLA_ACK) && ((TWSR & 0xF8) != TW_MR_SLA_ACK) )
			return 1;
		
		i2c_write(CONTINUE_DATA);
			if( (TWSR & 0xF8) != TW_MT_DATA_ACK )
			return 1; 

		for(y=0;y<128;y++)
		{			
			i2c_write(0);
				if( (TWSR & 0xF8) != TW_MT_DATA_ACK )
				return 1;
		} 

		i2c_stop();
	}
	
	return 0;
}

void oled_writeFlashToBuffer(const char *input, OLED *oled_ptr)
{
	
	unsigned int temp_ptr=0;
	oled_ptr->buffer_limit=0;
	unsigned char x,y;

	
	for(x=0;pgm_read_byte(&input[x])>=20;x++)
	{
		
		temp_ptr=(pgm_read_byte(&input[x])-ASCII_OFFSET)*FONT5;
		
		for(y=0;y<FONT5;y++)
		{
			oled_ptr->page_buffer[oled_ptr->buffer_limit++]=pgm_read_byte(&(font[temp_ptr+y]));
		}
		
	}
}

void oled_writeNumStringToBuffer(char *input, OLED *oled_ptr)
{

	unsigned int temp_ptr=0; 

	//unsigned char total_lines_ctr=0;    
	unsigned char x,y;
	oled_ptr->buffer_limit=0;

	//for(x=0;array[x]!='\0';x++)
	for(x=0;input[x]!='\0'&&x<128;x++)
	{
		//temp_ptr=(array[x]-ASCII_OFFSET)*FONT5;
		temp_ptr=(input[x]-ASCII_OFFSET)*FONT5;
		
		for(y=0;y<FONT5;y++)
		{
			oled_ptr->page_buffer[oled_ptr->buffer_limit++]=pgm_read_byte(&(font[temp_ptr+y]));
		}
		//output[total_lines_ctr++]=pgm_read_byte(&(font[temp_ptr+y]));
		
		
		//{
		//ptr->page_buffer[total_lines_ctr++]=pgm_read_byte(&font[temp_ptr+y]);
		//}
				
	}

	//ptr->page_buffer[total_lines_ctr]='\0';
	//output[total_lines_ctr]='\0';

	
}


unsigned char oled_writeIntAsFloat(OLED *ptr, unsigned char decimal)
{
	unsigned char x=0;

	i2c_start();
		if((TWSR & 0xF8) != TW_START)
		return 1;

	i2c_write(ptr->address);
		if ((TWSR & 0xF8) != 0x18)
		return 1;
	
	i2c_write(CONTINUE_DATA);
		if ( (TWSR & 0xF8) != 0x28)
		return 1;

	for(x=0;x<ptr->buffer_limit;x++)
	{
		if(x==decimal*FONT5)
		{
			for(unsigned char y=0;y<FONT5;y++)
			{
				i2c_write(pgm_read_byte(&font[(('.'-ASCII_OFFSET)*FONT5)+y]));
				if ((TWSR & 0xF8)!= 0x28)
				return 1;
			}		
		}
		
		i2c_write(ptr->page_buffer[x]);
			if ((TWSR & 0xF8)!= 0x28)
			return 1;
	}

	i2c_stop();
	
	return 0;
}


