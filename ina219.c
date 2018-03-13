#include "ina219.h"


unsigned char ina219_initDefault(unsigned char address)
{

	//unsigned int def = CONFIG_32V + CONFIG_320PG + (CONFIG_12BIT_8SAMP<<BADC_SHIFT) + (CONFIG_12BIT_8SAMP<<SADC_SHIFT) + CONFIG_SBVC ;

	i2c_start();  
		if((TWSR & 0xF8) != TW_START)
		return 1;
	
	i2c_write(address);
		if ( ((TWSR & 0xF8) != TW_MT_SLA_ACK) && ((TWSR & 0xF8) != TW_MR_SLA_ACK) )
		return 1;		
	
	i2c_write(CONFIG_ADD);
		if( (TWSR & 0xF8) != TW_MT_DATA_ACK )
		return 1;

	i2c_write(CONFIG_DEFAULT>>8);
		if( (TWSR & 0xF8) != TW_MT_DATA_ACK )
         return 1;
	
	i2c_write(CONFIG_DEFAULT&0x0F);
	   if( (TWSR & 0xF8) != TW_MT_DATA_ACK )
       return 1;
	   i2c_stop();
//-------------------------------------------------------------
	i2c_start();  
		if((TWSR & 0xF8) != TW_START)
		return 1;

	i2c_write(address);
		if ( ((TWSR & 0xF8) != TW_MT_SLA_ACK) && ((TWSR & 0xF8) != TW_MR_SLA_ACK) )
		return 1;

	i2c_write(CALIBRATION_ADD);
		if( (TWSR & 0xF8) != TW_MT_DATA_ACK )
		return 1;

	i2c_write(CALI_DEFAULT>>8);
		if( (TWSR & 0xF8) != TW_MT_DATA_ACK )
		return 1;

	i2c_write(CALI_DEFAULT&0x00FF);
		if( (TWSR & 0xF8) != TW_MT_DATA_ACK )
		return 1;

	i2c_stop();

	return 0;


//
}
 
unsigned char ina219_write(unsigned char i2c_address, unsigned char reg_address, unsigned int value)
{

	i2c_start();
		 if((TWSR & 0xF8) != TW_START)
         return 1;

	i2c_write(i2c_address);
		if ( ((TWSR & 0xF8) != TW_MT_SLA_ACK) && ((TWSR & 0xF8) != TW_MR_SLA_ACK) )
		return 1;
	
	i2c_write(reg_address);
		if( (TWSR & 0xF8) != TW_MT_DATA_ACK )
		 return 1;
	
	i2c_write(value>>8);
		if( (TWSR & 0xF8) != TW_MT_DATA_ACK )
         return 1;;
	
	i2c_write(value&0x000F);
		if( (TWSR & 0xF8) != TW_MT_DATA_ACK )
         return 1;

	i2c_stop();

	return 0;


}


unsigned int ina219_read(unsigned char i2c_address, unsigned char reg_address)
{

	int temp = 0;

	i2c_start();
		if((TWSR & 0xF8) != TW_START)
        return 1;

	i2c_write(i2c_address);
		if ( ((TWSR & 0xF8) != TW_MT_SLA_ACK) && ((TWSR & 0xF8) != TW_MR_SLA_ACK) )
		return 1;
	
	i2c_write(reg_address);
		if( (TWSR & 0xF8) != TW_MT_DATA_ACK )
		return 1;
	
	i2c_stop();
	
	i2c_start();
		if((TWSR & 0xF8) != TW_START)
        return 1;

	i2c_write(i2c_address+1);
		if( (TWSR & 0xF8) != TW_MT_DATA_ACK )
		return 1;
	
	temp=(i2c_read_ack()<<8);

	temp|=i2c_read_nack();
	
	i2c_stop();

	return(temp);
}


//--------------------------------------------------------------

unsigned int ina219_readContinuous(unsigned char i2c_address, unsigned char reg_address)
{
	
	int temp=0;
	
	i2c_start();
		if((TWSR & 0xF8) != TW_START)
        return 1;

	i2c_write(i2c_address);
		if ( ((TWSR & 0xF8) != TW_MT_SLA_ACK) && ((TWSR & 0xF8) != TW_MR_SLA_ACK) )
		return 1;
	
	i2c_write(reg_address);
		if( (TWSR & 0xF8) != TW_MT_DATA_ACK )
		return 1;

	i2c_start();
		if((TWSR & 0xF8) != TW_START)
        return 1;
		
	i2c_write(i2c_address+1);
		if( (TWSR & 0xF8) != TW_MT_DATA_ACK )
		return 1;
	
	temp=(i2c_read_ack()<<8);
	temp|=i2c_read_nack();
	
	return temp;
}

void ina219_readAndConvertAll(INA219 *ptr)
{
	ptr->bus=ina219_read(ptr->address,VOLT_ADD);
	ptr->bus>>=1; // same as /8, *4
		
	ptr->shunt=ina219_read(ptr->address,SHUNT_ADD);
		
	ptr->current=ina219_read(ptr->address,CURRENT_ADD);
		
	ptr->power=ina219_read(ptr->address,POWER_ADD);
	ptr->power*=2;
	
}
	
void ina219_writeToStrings(INA219_STRINGS *string_ptr,INA219 *val_ptr)
{
	_utoa10_asm(val_ptr->bus,string_ptr->bus_volt);
	_utoa10_asm(val_ptr->shunt,string_ptr->shunt_volt);
	_utoa10_asm(val_ptr->current,string_ptr->current);
	_utoa10_asm(val_ptr->power,string_ptr->power);	
}

void ina219_resetBuffer(INA219_STRINGS *ptr)
{
	for(unsigned char x=0;x<7;x++)
	{
			ptr->bus_volt[x]=0;
			ptr->shunt_volt[x]=0;
			ptr->current[x]=0;
			ptr->power[x]=0;
	}
}
	