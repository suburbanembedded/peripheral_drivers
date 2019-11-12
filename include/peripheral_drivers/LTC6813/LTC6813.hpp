#pragma once

#include "peripheral_drivers/LTC6813/PEC.hpp"

#include "emb_hal/hal/SPI_base.hpp"
#include "common_util/Byte_util.hpp"

#include <algorithm>
#include <array>
#include <cmath>

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

		ADCV    = 0x0260,
		ADOW    = 0x0228,
		CVST    = 0x0207,
		ADOL    = 0x0201,
		ADAX    = 0x0460,
		ADAXD   = 0x0400,
		AXOW    = 0x0410,
		AXST    = 0x0407,
		ADSTAT  = 0x0468,
		STATST  = 0x040F,
		ADCVAX  = 0x046F,
		ADCVSC  = 0x0467,
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
		ADC_MODE_0 = 0, //ADC_422HZ, ADC_1kHZ
		ADC_MODE_1 = 1, //ADC_27KHZ, ADC_14kHZ
		ADC_MODE_2 = 2, //ADC_7KHZ,  ADC_3kHZ
		ADC_MODE_3 = 3  //ADC_26HZ,  ADC_2kHZ
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

	enum class PULL_MODE
	{
		PULL_DOWN  = 0,
		PULL_UP    = 1
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

	enum class DCTO_TIM
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

	enum class PWM_ON_OFF
	{
		ON_ALL        = 0xF,
		ON_28S_OFF_2S = 0xE,
		ON_26S_OFF_4S = 0xD,
		ON_24S_OFF_6S = 0xC,
		ON_22S_OFF_8S = 0xB,
		ON_20S_OFF_10S = 0xA,
		ON_18S_OFF_12S = 0x9,
		ON_16S_OFF_14S = 0x8,
		ON_14S_OFF_16S = 0x7,
		ON_12S_OFF_18S = 0x6,
		ON_10S_OFF_20S = 0x5,
		ON_8S_OFF_22S = 0x4,
		ON_6S_OFF_24S = 0x3,
		ON_4S_OFF_26S = 0x2,
		ON_2S_OFF_28S = 0x1,
		OFF_ALL       = 0x0
	};

	enum class S_PIN_CTL
	{

	};

	constexpr static uint16_t get_adcv_command(const ADC_MODE md, const DCHG_PERMITTED dcp, const uint8_t ch)
	{
		return uint16_t(COMMAND_CODE::ADCV) | Byte_util::mask_rshift<uint16_t>(md, 0x03, 7) | Byte_util::mask_rshift<uint16_t>(dcp, 0x01, 4) | Byte_util::mask_rshift<uint16_t>(ch, 0x07, 0);
	}

	constexpr static uint16_t get_adow_command(const ADC_MODE md, const PULL_MODE pup, const DCHG_PERMITTED dcp, const uint8_t ch)
	{
		return uint16_t(COMMAND_CODE::ADOW) | Byte_util::mask_rshift<uint16_t>(md, 0x03, 7) | Byte_util::mask_rshift<uint16_t>(pup, 0x01, 6) | Byte_util::mask_rshift<uint16_t>(dcp, 0x01, 4) | Byte_util::mask_rshift<uint16_t>(ch, 0x07, 0);
	}

	constexpr static uint16_t get_adstat_command(const ADC_MODE md, const uint8_t ch)
	{
		return uint16_t(COMMAND_CODE::ADSTAT) | Byte_util::mask_rshift<uint16_t>(md, 0x03, 7) | Byte_util::mask_rshift<uint16_t>(ch, 0x07, 0);
	}

	constexpr static uint16_t get_adcvax_command(const ADC_MODE md, const DCHG_PERMITTED dcp)
	{
		return uint16_t(COMMAND_CODE::ADCVAX) | Byte_util::mask_rshift<uint16_t>(md, 0x03, 7) | Byte_util::mask_rshift<uint16_t>(dcp, 0x01, 4);
	}

	constexpr static uint16_t get_adcvsc(const ADC_MODE md, const DCHG_PERMITTED dcp)
	{
		return uint16_t(COMMAND_CODE::ADCVSC) | Byte_util::mask_rshift<uint16_t>(md, 0x03, 7) | Byte_util::mask_rshift<uint16_t>(dcp, 0x01, 4);
	}

	static void gen_command(const uint16_t command, std::array<uint8_t, 4> out_array)
	{
		const uint16_t pec = LTC6813_PEC::pec15(command);
		out_array[0] = Byte_util::get_b1(command);
		out_array[1] = Byte_util::get_b0(command);
		out_array[2] = Byte_util::get_b1(pec);
		out_array[3] = Byte_util::get_b0(pec);
	}

	class COMM_Reg
	{
	protected:
		std::array<uint8_t, 6> m_reg;	
	};

	class CFGA : public COMM_Reg
	{
		bool GPIO1();
		bool GPIO2();
		bool GPIO3();
		bool GPIO4();
		bool GPIO5();
		uint16_t VUV();
		uint16_t VOV();
		DCTO_TIM DCTO();
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
	};

	class CFGB : public COMM_Reg
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
	};

	class CV : public COMM_Reg
	{
	public:

	protected:

		uint16_t ConeV() const
		{
			return Byte_util::make_u16(m_reg[1], m_reg[0]);
		}
		uint16_t CtwoV() const
		{
			return Byte_util::make_u16(m_reg[3], m_reg[2]);	
		}
		uint16_t CthreeV() const
		{
			return Byte_util::make_u16(m_reg[5], m_reg[4]);
		}
	};

	class CVA : public CV
	{
	public:
		uint16_t C1V() const
		{
			return ConeV();
		}
		uint16_t C2V() const
		{
			return CtwoV();
		}
		uint16_t C3V() const
		{
			return CthreeV();
		}
	protected:
		
	};

	class CVB : public CV
	{
	public:
		uint16_t C4V() const
		{
			return ConeV();
		}
		uint16_t C5V() const
		{
			return CtwoV();
		}
		uint16_t C6V() const
		{
			return CthreeV();
		}
	protected:
		
	};

	class CVC : public CV
	{
	public:
		uint16_t C7V() const
		{
			return ConeV();
		}
		uint16_t C8V() const
		{
			return CtwoV();
		}
		uint16_t C9V() const
		{
			return CthreeV();
		}
	protected:
		
	};

	class CVD : public CV
	{
	public:
		uint16_t C10V() const
		{
			return ConeV();
		}
		uint16_t C11V() const
		{
			return CtwoV();
		}
		uint16_t C12V() const
		{
			return CthreeV();
		}
	protected:
		
	};

	class CVE : public CV
	{
	public:
		uint16_t C13V() const
		{
			return ConeV();
		}
		uint16_t C14V() const
		{
			return CtwoV();
		}
		uint16_t C15V() const
		{
			return CthreeV();
		}
	protected:
		
	};

	class CVF : public CV
	{
	public:
		uint16_t C16V() const
		{
			return ConeV();
		}
		uint16_t C17V() const
		{
			return CtwoV();
		}
		uint16_t C18V() const
		{
			return CthreeV();
		}
	protected:
		
	};

	class AUXA : public COMM_Reg
	{
	public:
		uint16_t G1V() const
		{
			return Byte_util::make_u16(m_reg[1], m_reg[0]);
		}
		uint16_t G2V() const
		{
			return Byte_util::make_u16(m_reg[3], m_reg[2]);
		}
		uint16_t G3V() const
		{
			return Byte_util::make_u16(m_reg[5], m_reg[4]);
		}
	};

	class AUXB : public COMM_Reg
	{
	public:
		uint16_t G4V() const
		{
			return Byte_util::make_u16(m_reg[1], m_reg[0]);
		}
		uint16_t G5V() const
		{
			return Byte_util::make_u16(m_reg[3], m_reg[2]);
		}
		uint16_t REF() const
		{
			return Byte_util::make_u16(m_reg[5], m_reg[4]);
		}
	};

	class AUXC : public COMM_Reg
	{
	public:
		uint16_t G6V() const
		{
			return Byte_util::make_u16(m_reg[1], m_reg[0]);
		}
		uint16_t G7V() const
		{
			return Byte_util::make_u16(m_reg[3], m_reg[2]);
		}
		uint16_t G8V() const
		{
			return Byte_util::make_u16(m_reg[5], m_reg[4]);
		}
	};

	class AUXD : public COMM_Reg
	{
	public:
		uint16_t G9V() const
		{
			return Byte_util::make_u16(m_reg[1], m_reg[0]);
		}
		bool C13_uv() const
		{
			return m_reg[4] & Byte_util::bv_8(0);
		}
		bool C13_ov() const
		{
			return m_reg[4] & Byte_util::bv_8(1);
		}
		bool C14_uv() const
		{
			return m_reg[4] & Byte_util::bv_8(2);
		}
		bool C14_ov() const
		{
			return m_reg[4] & Byte_util::bv_8(3);
		}
		bool C15_uv() const
		{
			return m_reg[4] & Byte_util::bv_8(4);
		}
		bool C15_ov() const
		{
			return m_reg[4] & Byte_util::bv_8(5);
		}
		bool C16_uv() const
		{
			return m_reg[4] & Byte_util::bv_8(6);
		}
		bool C16_ov() const
		{
			return m_reg[4] & Byte_util::bv_8(7);
		}
		bool C17_uv() const
		{
			return m_reg[5] & Byte_util::bv_8(0);
		}
		bool C17_ov() const
		{
			return m_reg[5] & Byte_util::bv_8(1);
		}
		bool C18_uv() const
		{
			return m_reg[5] & Byte_util::bv_8(2);
		}
		bool C18_ov() const
		{
			return m_reg[5] & Byte_util::bv_8(3);
		}
	};

	class STATUSA : public COMM_Reg
	{
	public:
		uint16_t SC() const
		{
			return Byte_util::make_u16(m_reg[1], m_reg[0]);
		}
		uint16_t ITMP() const
		{
			return Byte_util::make_u16(m_reg[3], m_reg[2]);
		}
		uint16_t VA() const
		{
			return Byte_util::make_u16(m_reg[5], m_reg[4]);
		}
	};

	class STATUSB : public COMM_Reg
	{
	public:
		uint16_t VD() const
		{
			return Byte_util::make_u16(m_reg[1], m_reg[0]);
		}

		bool C1_uv() const
		{
			return m_reg[2] & Byte_util::bv_8(0);
		}
		bool C1_ov() const
		{
			return m_reg[2] & Byte_util::bv_8(1);
		}
		bool C2_uv() const
		{
			return m_reg[2] & Byte_util::bv_8(2);
		}
		bool C2_ov() const
		{
			return m_reg[2] & Byte_util::bv_8(3);
		}
		bool C3_uv() const
		{
			return m_reg[2] & Byte_util::bv_8(4);
		}
		bool C3_ov() const
		{
			return m_reg[2] & Byte_util::bv_8(5);
		}
		bool C4_uv() const
		{
			return m_reg[2] & Byte_util::bv_8(6);
		}
		bool C4_ov() const
		{
			return m_reg[2] & Byte_util::bv_8(7);
		}
		bool C5_uv() const
		{
			return m_reg[3] & Byte_util::bv_8(0);
		}
		bool C5_ov() const
		{
			return m_reg[3] & Byte_util::bv_8(1);
		}
		bool C6_uv() const
		{
			return m_reg[3] & Byte_util::bv_8(2);
		}
		bool C6_ov() const
		{
			return m_reg[3] & Byte_util::bv_8(3);
		}
		bool C7_uv() const
		{
			return m_reg[3] & Byte_util::bv_8(4);
		}
		bool C7_ov() const
		{
			return m_reg[3] & Byte_util::bv_8(5);
		}
		bool C8_uv() const
		{
			return m_reg[3] & Byte_util::bv_8(6);
		}
		bool C8_ov() const
		{
			return m_reg[3] & Byte_util::bv_8(7);
		}
		bool C9_uv() const
		{
			return m_reg[4] & Byte_util::bv_8(0);
		}
		bool C9_ov() const
		{
			return m_reg[4] & Byte_util::bv_8(1);
		}
		bool C10_uv() const
		{
			return m_reg[4] & Byte_util::bv_8(2);
		}
		bool C10_ov() const
		{
			return m_reg[4] & Byte_util::bv_8(3);
		}
		bool C11_uv() const
		{
			return m_reg[4] & Byte_util::bv_8(4);
		}
		bool C11_ov() const
		{
			return m_reg[4] & Byte_util::bv_8(5);
		}
		bool C12_uv() const
		{
			return m_reg[4] & Byte_util::bv_8(6);
		}
		bool C12_ov() const
		{
			return m_reg[4] & Byte_util::bv_8(7);
		}

		bool THSD() const
		{
			return m_reg[5] & Byte_util::bv_8(0);
		}
		
		bool MUXFAIL() const
		{
			return m_reg[5] & Byte_util::bv_8(1);
		}

		uint8_t REV() const
		{
			return Byte_util::mask_lshift(m_reg[5], 0x0F << 4, 4);
		}

	};

	class SCTL : public COMM_Reg
	{
	public:
		S_PIN_CTL SCTL1() const
		{
			return get_s_pin_ctl(m_reg[0], 0);
		}
		S_PIN_CTL SCTL2() const
		{
			return get_s_pin_ctl(m_reg[0], 4);
		}
		S_PIN_CTL SCTL3() const
		{
			return get_s_pin_ctl(m_reg[1], 0);
		}
		S_PIN_CTL SCTL4() const
		{
			return get_s_pin_ctl(m_reg[1], 4);
		}
		S_PIN_CTL SCTL5() const
		{
			return get_s_pin_ctl(m_reg[2], 0);
		}
		S_PIN_CTL SCTL6() const
		{
			return get_s_pin_ctl(m_reg[2], 4);
		}
		S_PIN_CTL SCTL7() const
		{
			return get_s_pin_ctl(m_reg[3], 0);
		}
		S_PIN_CTL SCTL8() const
		{
			return get_s_pin_ctl(m_reg[3], 4);
		}
		S_PIN_CTL SCTL9() const
		{
			return get_s_pin_ctl(m_reg[4], 0);
		}
		S_PIN_CTL SCTL10() const
		{
			return get_s_pin_ctl(m_reg[4], 4);
		}
		S_PIN_CTL SCTL11() const
		{
			return get_s_pin_ctl(m_reg[5], 0);
		}
		S_PIN_CTL SCTL12() const
		{
			return get_s_pin_ctl(m_reg[5], 4);
		}
	protected:
		constexpr static S_PIN_CTL get_s_pin_ctl(const uint8_t reg, const uint8_t offset)
		{
			return static_cast<S_PIN_CTL>(Byte_util::mask_lshift(reg, uint8_t(0x07) << offset, offset));
		}
	};

	class PWM : public COMM_Reg
	{
	public:
		PWM_ON_OFF PWM1();
		PWM_ON_OFF PWM2();
		PWM_ON_OFF PWM3();
		PWM_ON_OFF PWM4();
		PWM_ON_OFF PWM5();
		PWM_ON_OFF PWM6();
		PWM_ON_OFF PWM7();
		PWM_ON_OFF PWM8();
		PWM_ON_OFF PWM9();
		PWM_ON_OFF PWM10();
		PWM_ON_OFF PWM11();
		PWM_ON_OFF PWM12();
	};

	class PSB : public COMM_Reg
	{
	public:
		PWM_ON_OFF PWM13();
		PWM_ON_OFF PWM14();
		PWM_ON_OFF PWM15();
		PWM_ON_OFF PWM16();
		PWM_ON_OFF PWM17();
		PWM_ON_OFF PWM18();

		S_PIN_CTL SCTL13(); 
		S_PIN_CTL SCTL14();
		S_PIN_CTL SCTL15();
		S_PIN_CTL SCTL16();
		S_PIN_CTL SCTL17();
		S_PIN_CTL SCTL18();
	};

	constexpr static float vuv_to_volts(const uint16_t vuv)
	{
		return float((uint32_t(vuv)+1U) * 16U) * 0.0001f;
	}

	static bool volts_to_vuv(const float volts, uint16_t* const out_vuv)
	{
		// volts = (vuv+1) * 16.0f * 0.0001f
		// volts * 10000.0f / 16.0f = (vuv+1)
		// volts * 10000.0f / 16.0f - 1 = vuv
		// volts * 625.0f - 1 = vuv

		if(!std::isfinite(volts))
		{
			return false;
		}

		float vuv = round(volts / 625.0f);
		vuv = std::max(1.0f, vuv);
		vuv = std::min(65536.0f, vuv);

		*out_vuv = uint16_t(uint32_t(vuv) - 1U);

		return true;
	}

	constexpr static float vov_to_volts(const uint16_t vov)
	{
		return float(uint32_t(vov) * 16U) * 0.0001f;
	}

	static bool volts_to_vov(const float volts, uint16_t* const out_vov)
	{
		// volts = vov * 16.0f * 0.0001f
		// volts * 10000.0f / 16.0f = vov
		// volts * 625.0f = vov

		if(!std::isfinite(volts))
		{
			return false;
		}

		float vov = round(volts * 625.0f);
		vov = std::max(0.0f, vov);
		vov = std::min(65535.0f, vov);

		*out_vov = uint16_t(vov);

		return true;
	}

	constexpr static float cell_to_volts(const uint16_t cell)
	{
		return float(cell) * 0.0001f;
	}

	constexpr static float gpio_to_volts(const uint16_t gpio)
	{
		return float(gpio) * 0.0001f;
	}

	constexpr static float ref_to_volts(const uint16_t ref)
	{
		return float(ref) * 0.0001f;
	}

	constexpr static float sc_to_volts(const uint16_t sc)
	{
		return float(sc) * 0.0030f;
	}

	constexpr static float itmp_to_degC(const uint16_t itmp)
	{
		return float(itmp) * 0.001f / 7.6f - 276.0f;
	}

	constexpr static float va_to_volts(const uint16_t va)
	{
		return float(va) * 0.0001f;
	}

	constexpr static float vd_to_volts(const uint16_t vd)
	{
		return float(vd) * 0.0001f;
	}

protected:

	SPI_base* m_spi;
};
