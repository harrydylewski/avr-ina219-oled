//my defaults for 20V MAX / 250uA current measure
//#define F_CPU 16000000UL

#define _CURLSB 250

#define _CONFIG_ADD 0x00

#define _RESET 0x8000

#define _CONFIG_32V 0x2000 //default
#define _CONFIG_16V 0x0000

#define _CONFIG_40PG  0x0000
#define _CONFIG_80PG  0x0800
#define _CONFIG_160PG 0x1000
#define _CONFIG_320PG 0x1800 //default

#define _CONFIG_9BIT    0x0000
#define _CONFIG_10BIT   0x0080
#define _CONFIG_11BIT   0x0100
#define _CONFIG_12BIT1  0x0180 //default
#define _CONFIG_12BIT2  0x0400


#define _CONFIG_SAMP2   0x0048
#define _CONFIG_SAMP4   0x0050
#define _CONFIG_SAMP8   0x0058
#define _CONFIG_SAMP16  0x0060
#define _CONFIG_SAMP32  0x0068 
#define _CONFIG_SAMP64  0x0070
#define _CONFIG_SAMP128 0x0078

#define _CONFIG_PWRDOWN 0x0000
#define _CONFIG_SVT     0x0001
#define _CONFIG_BST     0x0002
#define _CONFIG_BSVT    0x0003
#define _CONFIG_ADCOFF  0x0004
#define _CONFIG_SVC     0x0005
#define _CONFIG_BVC     0x0006
#define _CONFIG_SBVC    0x0007 //default

#define _ADD0_INA219 0x80 //A1:0 gnd
#define _INA219_ADD1 0x82 //A1:GND A0 VS
#define _INA219_ADD2 0x84
#define _INA219_ADD3 0x86 // 
#define _INA219_ADD4 0x88 // A1: VS A0: GND
#define _INA219_ADD5 0x8A // A1:0 GND
#define _INA219_ADD6 0x8C
#define _INA219_ADD7 0x8E
#define _INA219_ADD8 0x90
#define _INA219_ADD9 0x92
#define _INA219_ADDA 0x94
#define _INA219_ADDB 0x96
#define _INA219_ADDC 0x98
#define _INA219_ADDD 0x9A
#define _INA219_ADDE 0x9C
#define _INA219_ADDF 0x9E

#define _SV_ADD 0x01
#define _BV_ADD 0x02
#define _P_ADD  0x03
#define _C_ADD  0x04
#define _CAL_ADD 0x05

  // VBUS_MAX = 32V             (Assumes 32V, can also be set to 16V)
  // VSHUNT_MAX = 0.32          (Assumes Gain 8, 320mV, can also be 0.16, 0.08, 0.04)
  // RSHUNT = 0.1               (Resistor value in ohms)

  /*mine
  0)
  VBUS_MAX = 16V  
  VSHUNT_MAX = 0.32 V
  RSHUNT = 0.1
  
  1)
  MaxPossible_I = VSHUNT_MAX / RSHUNT
  MaxPossible_I = .32V / .1
  MaxPossible_I = 3.2A

   2)
   MaxExpected_I = 1.31A

   3)

	MinimumLSB = MaxExpected_I/32767
    MinimumLSB = 40 uA 


    MaximumLSB = MaxExpected_I/4096
    MaximumLSB = 320 uA             

   4) Choose an LSB between the min and max values
  	currentLSB =  250uA
  
   5. Compute the calibration register
       Cal = trunc (0.04096 / (Current_LSB (250) * (.1) RSHUNT))
       Cal = 1638 (0x0666)

   6. Calculate the power LSB
      PowerLSB = 20 * CurrentLSB
      PowerLSB = 0.005 
	
	7. Compute the maximum current and shunt voltage values before overflow
       Max_Current = Current_LSB * 32767
       Max_Current = 8.19A before overflow

  // If Max_Current > Max_Possible_I then
  //    Max_Current_Before_Overflow = MaxPossible_I <this
  // Else
  //    Max_Current_Before_Overflow = Max_Current
  // End If
  
   Max_ShuntVoltage = Max_Current_Before_Overflow * RSHUNT
   Max_ShuntVoltage = 0.32V
  
  // If Max_ShuntVoltage >= VSHUNT_MAX
  //    Max_ShuntVoltage_Before_Overflow = VSHUNT_MAX <this
  // Else
  //    Max_ShuntVoltage_Before_Overflow = Max_ShuntVoltage
  // End If
  
   8. Compute the Maximum Power
   MaximumPower = Max_Current_Before_Overflow * VBUS_MAX
   MaximumPower = 3.2 * 16V
   MaximumPower = 32W
  */ 
  
  // 1. Determine max possible current
  // MaxPossible_I = VSHUNT_MAX / RSHUNT
  // MaxPossible_I = 3.2A
  
  // 2. Determine max expected current
  // MaxExpected_I = 2.0A
  
  // 3. Calculate possible range of LSBs (Min = 15-bit, Max = 12-bit)
  // MinimumLSB = MaxExpected_I/32767
  // MinimumLSB = 0.000061              (61uA per bit)
  // MaximumLSB = MaxExpected_I/4096
  // MaximumLSB = 0,000488              (488uA per bit)
  
  // 4. Choose an LSB between the min and max values
  //    (Preferrably a roundish number close to MinLSB)
  // CurrentLSB = 0.0001 (100uA per bit)
  
  // 5. Compute the calibration register
  // Cal = trunc (0.04096 / (Current_LSB * RSHUNT))
  // Cal = 4096 (0x1000)
  
  // ina219_calValue = 4096;
  
  // 6. Calculate the power LSB
  // PowerLSB = 20 * CurrentLSB
  // PowerLSB = 0.002 (2mW per bit)
  
  // 7. Compute the maximum current and shunt voltage values before overflow
  //
  // Max_Current = Current_LSB * 32767
  // Max_Current = 3.2767A before overflow
  //
  // If Max_Current > Max_Possible_I then
  //    Max_Current_Before_Overflow = MaxPossible_I
  // Else
  //    Max_Current_Before_Overflow = Max_Current
  // End If
  //
  // Max_ShuntVoltage = Max_Current_Before_Overflow * RSHUNT
  // Max_ShuntVoltage = 0.32V
  //
  // If Max_ShuntVoltage >= VSHUNT_MAX
  //    Max_ShuntVoltage_Before_Overflow = VSHUNT_MAX
  // Else
  //    Max_ShuntVoltage_Before_Overflow = Max_ShuntVoltage
  // End If
  
  // 8. Compute the Maximum Power
  // MaximumPower = Max_Current_Before_Overflow * VBUS_MAX
  // MaximumPower = 3.2 * 32V
  // MaximumPower = 102.4W
