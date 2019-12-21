#pragma once
#include "namespaces.h"

ref struct I2CParams
{
	unsigned char SlaveAddr;
	unsigned char firstbyte;
};


//функция выделения целой части измеренного параметра по I2C в соотвествии с протоколом, возвращает значения типа String для вывода на экран
String^ ConvertI2CHbyte(array<unsigned char>^ Data, int Testn);

//функция выделения дробной части измеренного параметра по I2C в соотвествии с протоколом, возвращает значения типа String для вывода на экран
String^ ConvertI2CLbyte(array<unsigned char>^ Data, int Testn);

String^ ConvResI2CFromIPZO5(int TestNum, array<unsigned char>^ SendData);

String^ ConvResI2CFromIPZO3(int TestNum, array<unsigned char>^ SendData);

