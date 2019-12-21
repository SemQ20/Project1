#pragma once
/*Параметры тестов ИПЗО3 и форматирование стиля вывода результатов на экран*/
#include "arrays.h"

/*Функция для установки параметров аттенюаторов, арм и т.д для калибровки ИПЗО3*/
String^ setIPZO3ParamsToI2c(I2CParams^ i2cp);

String^ IPZO3_Test_Result(int TestNum, array<unsigned char>^ SendData, Vstr^ valStr);

bool setParamsForTest_IPZO3(int Testn, I2CParams^ i2cp);