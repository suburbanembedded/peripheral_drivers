#include "peripheral_drivers/LTC6813/LTC6813.hpp"

LTC6813::LTC6813()
{
	m_spi = nullptr;
}

LTC6813::~LTC6813()
{

}

bool LTC6813::convert_all_cells()
{
	const uint16_t cmd = get_adcv_command(ADC_MODE::ADC_MODE_1, DCHG_PERMITTED::DCHG_NOK, CELL_SELECTION::ALL_CELLS);

	std::array<uint8_t, 4> packet;
	gen_command(cmd, &packet);

	//wait for timeout or "hold CSB low and wait for SDO to go high"
}

bool LTC6813::convert_all_cells_and_sum();
{
	const uint16_t cmd = get_adcvsc(ADC_MODE::ADC_MODE_1, DCHG_PERMITTED::DCHG_NOK, CELL_SELECTION::ALL_CELLS);

	std::array<uint8_t, 4> packet;
	gen_command(cmd, &packet);

	m_spi->write(packet.data(), packet.size());

	//Read cell group A
	CVA cva;
	gen_command(COMMAND_CODE::RDCVA, &packet);
	m_spi->write_then_read(packet.data(), packet.size(), cva.m_reg.data(), cva.m_reg.size())
}

bool LTC6813::read_cell_group_a(CVA* const out_cv);
{
	read_command(COMMAND_CODE::RDCVA, out_cv);
}
bool LTC6813::read_cell_group_b(CVB* const out_cv);
{
	read_command(COMMAND_CODE::RDCVB, out_cv);
}
bool LTC6813::read_cell_group_c(CVC* const out_cv);
{
	read_command(COMMAND_CODE::RDCVC, out_cv);
}
bool LTC6813::read_cell_group_d(CVD* const out_cv);
{
	read_command(COMMAND_CODE::RDCVD, out_cv);
}
bool LTC6813::read_cell_group_e(CVE* const out_cv);
{
	read_command(COMMAND_CODE::RDCVE, out_cv);
}
bool LTC6813::read_cell_group_f(CVF* const out_cv);
{
	read_command(COMMAND_CODE::RDCVF, out_cv);
}
bool LTC6813::read_statusa(STATUSA* const out_statusa)
{
	read_command(COMMAND_CODE::RDSTATA, out_statusa);
}
bool LTC6813::read_command(const COMMAND_CODE cmd, COMM_Reg* const reg);
{
	std::array<uint8_t, 4> packet;
	gen_command(cmd, &packet);
	m_spi->write_then_read(packet.data(), packet.size(), reg->m_reg.data(), reg->m_reg.size());
}

bool LTC6813::poll_adc_status(bool* const done)
{
	//send N clocks after PLADC where N = number of slaves
	//so here we check 8 slaves
	//if SDO is high, all conversions are done

	std::array<uint8_t, 4> cmd_packet;
	std::array<uint8_t, 1> poll_packet;

	gen_command(COMMAND_CODE::PLADC, &cmd_packet);
	m_spi->write_then_read(cmd_packet.data(), cmd_packet.size(), poll_packet.data(), poll_packet.size());

	if(poll_packet[0] != 0)
	{
		*done = true;
	}
	else
	{
		*done = false;
	}
}

bool LTC6813::read_all_cells_and_sum()
{
	CVA cva;
	read_cell_group_a(&cva);
	CVB cvb;
	read_cell_group_b(&cvb)
	CVC cvc;
	read_cell_group_c(&cvc)
	CVD cvd;
	read_cell_group_d(&cvd)
	CVE cve;
	read_cell_group_e(&cve)
	CVF cvf;
	read_cell_group_f(&cvf)

	STATUSA statusa;
	read_statusa(&statusa)
}
