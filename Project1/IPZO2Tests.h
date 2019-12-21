#pragma once

/*Параметры тестов ИПЗО2 и форматирование стиля вывода результатов на экран*/
String^ IPZO2_Test_Result(int TestNum, array<unsigned char>^ SendData, Vstr^ valStr);

bool setParamsForTest_IPZO2(int Testnum, I2CParams^ i2cp);