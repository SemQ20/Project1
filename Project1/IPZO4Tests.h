#pragma once
/*Параметры тестов ИПЗО4 и форматирование стиля вывода результатов на экран*/
String^ IPZO4_Test_Result(int TestNum, array<unsigned char>^ SendData);

bool setParamsForTest_IPZO4(int Testnum, I2CParams^ i2cp);