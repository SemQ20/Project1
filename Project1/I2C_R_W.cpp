#include "arrays.h"
#include "ConvertResI2C.h"
#include "PowerCorrect.h"
#include "IPZO2Tests.h"
#include "IPZO3Tests.h"
#include "IPZO4Tests.h"
#include "IPZO5Tests.h"
#include "I2C_R_W.h"

String ^ I2C_Read(int testn, int ProdNum, double(*CABLE_KOEF)[2][3], double(*POWER_KOEF)[3], double(*POWER_CORRECT)[2][3], I2CParams ^ i2cp)
{
	array<unsigned char>^ SendData;
	SendData = crSarray();
	unsigned char DataLength;
	String^ Return_str = " ";
	String^ Result;
	DataLength = SendData->Length;
	Vstr^ valStr; //указатель на структуру аргументов
	valStr = gcnew Vstr;
	valStr->CABLE_KOEF = CABLE_KOEF;
	valStr->POWER_KOEF = POWER_KOEF;
	valStr->POWER_CORRECT = POWER_CORRECT;

	setParamsForTest_IPZO2(testn, i2cp);
	setParamsForTest_IPZO3(testn, i2cp); //установка параметров в соотвествии с номером модуля и его тестом для Read
	setParamsForTest_IPZO4(testn, i2cp);
	setParamsForTest_IPZO5(testn, ProdNum, i2cp);

	if (PICkitS::I2CM::Receive((unsigned char)i2cp->SlaveAddr + 1, DataLength, SendData, Return_str))
	{
		Result = IPZO2_Test_Result(testn, SendData, valStr);
		if (Result)return Result;
		Result = IPZO3_Test_Result(testn, SendData, valStr);       //выводы результатов после обработки, типа стринг
		if (Result)return Result;
		Result = IPZO4_Test_Result(testn, SendData);       //выводы результатов после обработки, типа стринг
		if (Result)return Result;
		Result = IPZO5_Test_Result(testn, ProdNum, SendData, valStr);
		if (Result)return Result;
	}
}

bool I2C_send_byte(int Testn, int ProdNum, I2CParams ^ ParmsI2c, bool checked, bool synchrCheck)
{
	bool i2c_send = true;
	array<unsigned char> ^DataArray;
	DataArray = crArray(Testn, ProdNum, i2c_send, checked, synchrCheck);//создание массива для конкретного теста
	String^ Return_str;

	setParamsForTest_IPZO2(Testn, ParmsI2c);
	setParamsForTest_IPZO3(Testn, ParmsI2c); //установка параметров в соотвествии с номером модуля и его тестом для Write
	setParamsForTest_IPZO4(Testn, ParmsI2c);
	setParamsForTest_IPZO5(Testn, ProdNum, ParmsI2c);

	if (PICkitS::I2CM::Write(ParmsI2c->SlaveAddr, ParmsI2c->firstbyte, DataArray->Length, DataArray, Return_str))
	{
		delete[]DataArray;
	}
	else
	{

		PICkitS::Device::Reset_Control_Block();       //clear any errors in PKSA
	}
	return true;
}
