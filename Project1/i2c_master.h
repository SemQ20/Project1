#pragma once

//инициализация I2C в режиме мастера для PKSA
bool i2cm_for_pickit(double volt,bool pksa_power)
{
	if (PICkitS::Device::Initialize_PICkitSerial())
	{
		if(PICkitS::I2CM::Configure_PICkitSerial_For_I2CMaster())
		{
			PICkitS::I2CM::Get_I2C_Bit_Rate();
			PICkitS::I2CM::Get_Source_Voltage(volt, pksa_power);
		}
	}
	else
	{
		PICkitS::Device::Reset_Control_Block();
	}
	if (PICkitS::I2CM::Configure_PICkitSerial_For_I2CMaster())
	{
		return true;
	}
	else
	{
		PICkitS::Device::Reset_Control_Block();
		return false;
	}
}




