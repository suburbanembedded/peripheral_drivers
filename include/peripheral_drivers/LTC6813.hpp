#pragma once

#include "emb_hal/hal/SPI_base.hpp"

class LTC6813
{
public:

	LTC6813();
	~LTC6813();

	static uint16_t calculate_pec(const uint16_t cmd);

	enum class COMMAND_CODE : uint16_t
	{
		WRCFGA  = 0x0001,
		WRCFGB  = 0x0024,
		RDCFGA  = 0x0002,
		RDCFGB  = 0x0026,
		
		RDCVA   = 0x0004,
		RDCVB   = 0x0006,
		RDCVC   = 0x0008,
		RDCVD   = 0x000A,
		RDCVE   = 0x0009,
		RDCVF   = 0x000B,
		
		RDAUXA  = 0x000C,
		RDAUXB  = 0x000E,
		RDAUXC  = 0x000D,
		RDAUXD  = 0x000F,
		
		RDSTATA = 0x0010,
		RDSTATB = 0x0012,

		WRSCTRL  = 0x0014,
		WRPWM    = 0x0020,
		WRPSB    = 0x001C,
		RDSCTRL  = 0x0016,
		RDPWM    = 0x0022,
		RDPSB    = 0x001E,
		STSCTRL  = 0x0019,
		CLRSCTRL = 0x0018,

		ADCV    = 0x0000,
		ADOW    = 0x0000,
		CVST    = 0x0000,
		ADOL    = 0x0000,
		ADAX    = 0x0000,
		ADAXD   = 0x0000,
		AXOW    = 0x0000,
		AXST    = 0x0000,
		ADSTAT  = 0x0000,
		SDSTATD = 0x0000,
		STATST  = 0x0000,
		ADCVAX  = 0x0000,
		ADCVSC  = 0x0000,
		CLRCELL = 0x0711,
		CLRAUX  = 0x0712,
		CLRSTAT = 0x0713,
		PLADC   = 0x0714,
		DIAGN   = 0x0715,
		WRCOMM  = 0x0722,
		RDCOMM  = 0x0722,
		STCOMM  = 0x0723,
		MUTE    = 0x0028,
		UNMUTE  = 0x0029
	};

	enum class ADC_MODE
	{
		ADC_422HZ,
		ADC_27KHZ,
		ADC_7KHZ,
		ADC_26HZ,
	};

	enum class DCHG_PERMITTED
	{
		DCHG_OK  = 0,
		DCHG_NOK = 1,
	};

	enum class CELL_SELECTION
	{
		ALL_CELLS     = 0,
		CELLS_1_7_13  = 1,
		CELLS_2_8_14  = 2,
		CELLS_3_9_15  = 3,
		CELLS_4_10_16 = 4,
		CELLS_5_11_17 = 5,
		CELLS_6_12_18 = 6,
	};

	enum class SELFTEST_MODE
	{
		SELF_TEST_1 = 1,
		SELF_TEST_2 = 2,
	};

	enum class REDUNDANCY_PATH
	{
		ADC123_SEQ = 0,
		ADC1_ONLY = 1,
		ADC2_ONLY = 2,
		ADC3_ONLY = 3
	};

	enum class DCTO
	{
		DISABLED = 0x0,
		MIN_1  = 0x1,
		MIN_2  = 0x2,
		MIN_3  = 0x3,
		MIN_4  = 0x4,
		MIN_5  = 0x5,
		MIN_10 = 0x6,
		MIN_15 = 0x7,
		MIN_20 = 0x8,
		MIN_30 = 0x9,
		MIN_40 = 0xA,
		MIN_60 = 0xB,
		MIN_75 = 0xC,
		MIN_90 = 0xD,
		MIN_120 = 0xF
	};

	class CFGA
	{
		bool GPIO1();
		bool GPIO2();
		bool GPIO3();
		bool GPIO4();
		bool GPIO5();
		uint16_t VUV();
		uint16_t VOV();
		DCTO DCTO();
		bool REFON();//reference stay on
		bool ADCOPT();//adc mode option bit
		bool DTEN();//discharge timer enable
		bool DCC1();
		bool DCC2();
		bool DCC3();
		bool DCC4();
		bool DCC5();
		bool DCC6();
		bool DCC7();
		bool DCC8();
		bool DCC9();
		bool DCC10();
		bool DCC11();
		bool DCC12();
	protected:
		std::array<uint8_t, 5> m_reg;
	}

	class CFGB
	{

		bool GPIO6();
		bool GPIO7();
		bool GPIO8();
		bool GPIO9();
		bool MUTE();//mute
		bool FDRF();//force digital redundancy failure
		REDUNDANCY_PATH PS();
		bool DTMEN();//enable discharge timer monitor
		bool DCC0();//gpio9 pull down
		bool DCC13();
		bool DCC14();
		bool DCC15();
		bool DCC16();
		bool DCC17();
		bool DCC18();
	protected:
		std::array<uint8_t, 5> m_reg;
	}

protected:

	SPI_base* m_spi;
};
