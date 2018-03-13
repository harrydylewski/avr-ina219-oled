#include "oled_i2c.h"
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

//--------------------------------------------------
void oled_init_def32(unsigned char address)
{
	i2c_start();
		if (i2c_getstatus() != 0x08)
        return;
	//
	i2c_write(address);
		if (i2c_getstatus() != 0x18)
        return;
		 
	i2c_write(CONTINUE_CMD);
		if (i2c_getstatus() != 0x28)
        return;
	//

	//1 set mux
	i2c_write(MUX_ADD);
		if (i2c_getstatus() != 0x28)
        return;

	i2c_write(MUX_32_CMD);
		if (i2c_getstatus() != 0x28)
        return;
	//2 set display offset
	i2c_write(DISPLAY_OFFSET_ADD);
		if (i2c_getstatus() != 0x28)
        return;

	i2c_write(DISPLAY_OFFSET_DISABLE_CMD);
		if (i2c_getstatus() != 0x28)
        return;
	
	//3 set display startline
	i2c_write(DISPLAY_STARTLINE_DEF_CMD);
		if (i2c_getstatus() != 0x28)
        return;
	//4	segment remap
	i2c_write(SEGMENT_NOREMAP_CMD);
		if (i2c_getstatus() != 0x28)
        return;

	//5 com remap
	i2c_write(COM_NOREMAP_CMD);
		if (i2c_getstatus() != 0x28)
        return;
	//6 com pins config
	i2c_write(COMPIN_ADD);
		if (i2c_getstatus() != 0x28)
        return;
	i2c_write(COMPIN_CMD);
		if (i2c_getstatus() != 0x28)
        return;

	//7 set contrast 
	i2c_write(CONTRAST_ADD);
		if (i2c_getstatus() != 0x28)
        return;
	i2c_write(CONTRAST_DEF_CMD);
		if (i2c_getstatus() != 0x28)
        return;

	//9
	i2c_write(DISPLAY_DISABLE_CMD);
		if (i2c_getstatus() != 0x28)
        return;
	//10
	i2c_write(NORMAL_DISPLAY_CMD);
		if (i2c_getstatus() != 0x28)
        return;
	//11
	i2c_write(OSC_FREQ_ADD);
		if (i2c_getstatus() != 0x28)
        return;

	i2c_write(OSC_FREQ_DEF_CMD);
		if (i2c_getstatus() != 0x28)
        return;
	//12 charge pump enabled
	i2c_write(CHARGEPUMP_ADD);
		if (i2c_getstatus() != 0x28)
        return;

	i2c_write(CHARGEPUMP_ENABLE_CMD);
		if (i2c_getstatus() != 0x28)
        return;
	//13
	i2c_write(DISPLAY_ON_CMD);
		if (i2c_getstatus() != 0x28)
        return;

	i2c_stop();


}

void oled_pageadd_scheme(unsigned char address)
{
	i2c_start();
			if (i2c_getstatus() != TW_START)
        	return;

	i2c_write(address);
			if (i2c_getstatus() != TW_MR_SLA_ACK)

	i2c_write(CONTINUE_CMD);
			if (i2c_getstatus() != TW_MT_DATA_ACK)
        	return; 
	
	i2c_write(PAGEADD_LN_0_CMD);
			if (i2c_getstatus() != TW_MT_DATA_ACK)
        	return; 
	i2c_write(PAGEADD_HN_0_CMD);
			if (i2c_getstatus() != TW_MT_DATA_ACK)
        	return; 

	i2c_stop();
}

void oled_select_page(unsigned char address, unsigned char page)
{
	i2c_start();
		if (i2c_getstatus() != 0x08)
       	return;

	i2c_write(address);
		if (i2c_getstatus() != 0x18)
       	return;

	i2c_write(NO_CONTINUE_CMD);
		if (i2c_getstatus() != 0x28)
       	return;

	i2c_write(page);
		if (i2c_getstatus() != 0x28)
       	return;

	i2c_stop();
}

void oled_wr_page(OLED *ptr, unsigned char end)
{
	unsigned char x=0;

		i2c_start();
			if (i2c_getstatus() != 0x08)
        	return;

		i2c_write(ptr->address);
			if (i2c_getstatus() != 0x18)
        	return; 
		
		i2c_write(CONTINUE_DATA);
			if (i2c_getstatus() != 0x28)
        	return; 

		for(x=0;x<end;x++)
		{
			i2c_write(ptr->page_buffer[x]);
			if (i2c_getstatus() != 0x28)
        	return;
		} 

		i2c_stop();

}

void oled_wr_cmd(unsigned char address, unsigned char cmd)
{
	i2c_start();
		if (i2c_getstatus() != 0x08)
       	return;

	i2c_write(address);
		if (i2c_getstatus() != 0x18)
       	return;

	i2c_write(NO_CONTINUE_CMD);
		if (i2c_getstatus() != 0x28)
       	return;
	
	i2c_write(cmd);
		if (i2c_getstatus() != 0x28)
       	return;
	
	i2c_stop();
}

void oled_wr_contrast(unsigned char address, unsigned char contrast)
{
	//start+add+continue commands
	i2c_start();
		if (i2c_getstatus() != 0x08)
        return;

	i2c_write(address);
		if (i2c_getstatus() != 0x18)
        return; 

	i2c_write(CONTINUE_CMD);
		if (i2c_getstatus() != 0x28)
        return; 			
	//
	i2c_write(CONTRAST_ADD);
		if (i2c_getstatus() != 0x28)
        return;

	i2c_write(contrast);
		if (i2c_getstatus() != 0x28)
        return;

	i2c_stop();
}

void oled_page_startcolumn(unsigned char address, unsigned char position)
{
	////start+add+continue commands
	unsigned char low_nib, high_nib;

	if(position>15)
	{
		high_nib=0x10+((position>>4)&0x0F);
		low_nib=position&0x0F;
	}

	else
	{
		high_nib=0x10;
		low_nib=position;
	}

	i2c_start();
		if (i2c_getstatus() != 0x08)
        return;

	i2c_write(address);
		if (i2c_getstatus() != 0x18)
        return;

	i2c_write(CONTINUE_CMD);
		if (i2c_getstatus() != 0x28)
        return; 
	//
	i2c_write(low_nib);
		if (i2c_getstatus() != 0x28)
        return;

	i2c_write(high_nib);
		if (i2c_getstatus() != 0x28)
        return;
	i2c_stop();
}

void oled_config_hs(unsigned char address, unsigned char s_page,unsigned char e_page, unsigned time,unsigned char direction)
{
	i2c_start();
		if (i2c_getstatus() != 0x08)
        return;

	i2c_write(address);
		if (i2c_getstatus() != 0x18)
        return;

	i2c_write(CONTINUE_CMD);
		if (i2c_getstatus() != 0x28)
        return; 

	i2c_write(direction);
		if (i2c_getstatus() != 0x28)
        return;	
	
	i2c_write(DUMMY_BYTE_00);
		if (i2c_getstatus() != 0x28)
        return;	

	i2c_write(s_page);
		if (i2c_getstatus() != 0x28)
        return;

	i2c_write(time);
		if (i2c_getstatus() != 0x28)
        return;	
			
	i2c_write(e_page);
		if (i2c_getstatus() != 0x28)
        return;	

	i2c_write(DUMMY_BYTE_00);
		if (i2c_getstatus() != 0x28)
        return;	

	i2c_write(DUMMY_BYTE_FF);
		if (i2c_getstatus() != 0x28)
        return;	
	i2c_write(SCROLL_START_CMD);
		if (i2c_getstatus() != 0x28)
        return;	

	i2c_stop();
} 

void oled_clear_display(OLED *ptr)
{
	unsigned char x,y;
	/*
	for(x=0;x<128;x++)
	ptr->page_buffer[x]=0;
	*/
		
	
	i2c_start();
		if (i2c_getstatus() != 0x08)
       	return;

	i2c_write(ptr->address);
		if (i2c_getstatus() != 0x18)
       	return;

	for(x=0;x<8;x++)
	{	
			
		i2c_start();
			if (i2c_getstatus() != 0x08)
       		return;

		i2c_write(NO_CONTINUE_CMD);
			if (i2c_getstatus() != 0x28)
        	return; 

		i2c_write(PAGE_CMD+x);
			if (i2c_getstatus() != 0x28)
       		return;	
		
		i2c_write(CONTINUE_DATA);
			if (i2c_getstatus() != 0x28)
        	return; 

		for(y=0;y<128;y++)
		{
			i2c_write(ptr->page_buffer[x]);
				if (i2c_getstatus() != 0x28)
        		return;
		} 
	}

	i2c_stop();


}

void oled_write_display(unsigned char address, const char *msg, unsigned char column, unsigned char page)
{

	oled_page_startcolumn(address,column);
	oled_select_page(address,page);
	//
	oled_output_page(msg);

}

void oled_flash_2_font(const char *translate_array, OLED *ptr)
{

	unsigned char x=0;

	//unsigned char total_lines=0;

	unsigned char line_counter=0,total_chars=0,fontlines_counter=0;

	unsigned int output_array[FONT5_MAXCHARS];
	
	for(x=0;pgm_read_byte(&translate_array[x])!='\0';x++)
	output_array[x]=(pgm_read_byte(&translate_array[x])-ASCII_OFFSET)*5;
	
	total_chars=x;

	for(x=0;x<total_chars;x++)
	{
		for(fontlines_counter=0;fontlines_counter<FONT5_MAXCHARS;fontlines_counter++)
		ptr->page_buffer[line_counter++]=pgm_read_byte(&font[output_array[x]+fontlines_counter]);
	}

	//oled_wr_page(page_buffer,line_counter);
}

