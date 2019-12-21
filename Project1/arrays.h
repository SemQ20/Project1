#ifndef ARRAYS_H
#define ARRAYS_H

#include <vector>

typedef unsigned char byte;
typedef unsigned int uint;
extern byte b[1];
extern bool secondSending;

ref struct IPZO3PARAMS
{
	byte valueArm,
		valueFrequency,
		valuePrelimAtt,
		valueOutOK,
		valueOutPBL,
		typeOut,
		valueModulator;
};

//шаблон функции заполняющий массив либого типа вектором того же типа
template<typename T>
void fillArrays(array<T>^ arrayOne, std::vector<T> c)
{
	for (int i = 0; i != c.size(); i++)
	{
		arrayOne[i] = c[i];
	}
}

template<typename T, size_t x, size_t y, size_t z> //заполнение статичного массива другим статичным массивом, используя шаблон функции, возвращает наполняемую переменную
int arrayFillOutThree(T(&array)[x][y][z], double *buffer, int v)
{
	int c = v;
	for (int i = 0; i != x; i++)
		for (int j = 0; j != y; j++)
			for (int k = 0; k != z; k++)
			{
				if ((Convert::ToString(buffer[c])) == "NaN")
				{
					c++;
				}
				array[i][j][k] = buffer[c];
				c++;
			}
	return  c;
}

template<typename T, size_t x, size_t y>//заполнение статичного массива другим статичным массивом, используя шаблон функции, возвращает наполняемую переменную
int arrayFillOutTwo(T(&array)[x][y], double *buffer, int v)
{
	int c = v;
	for (int i = 0; i != x; i++)
		for (int j = 0; j != y; j++)
		{
			array[i][j] = buffer[c];
			c++;
		}
	return  c;
}

template <typename T, size_t x, size_t y, size_t z, size_t c, size_t v, size_t n, size_t b, size_t a, size_t x1, size_t y1, size_t x2, size_t y2, size_t z1>
void fillArraysAfterParse(T(&CABLE_KOEF_01dB)[x][y][z], T(&CABLE_KOEF)[c][v][n], T(&POWER_KOEF)[b][a], T(&SENS_KOEF_01dB)[x1][y1], T(&POWER_CORRECT)[x2][y2][z1], double* buffer)
{
	int c = 0;
	c = arrayFillOutThree(CABLE_KOEF_01dB, buffer, c);
	c = arrayFillOutThree(CABLE_KOEF, buffer, c);
	c = arrayFillOutTwo(POWER_KOEF, buffer, c);
	c = arrayFillOutTwo(SENS_KOEF_01dB, buffer, c);
	c = arrayFillOutThree(POWER_CORRECT, buffer, c);

}

//convert hex->char
byte LongToDigits(uint Value, byte Offset, byte DigitNum, byte *Digits);

void setIPZO3Params(byte Arm, byte Freq, byte PrelimAtt, byte OutOK, byte OutPBL, byte TypeOut, byte Modulator, IPZO3PARAMS^ Params);

array<byte>^ dArray(IPZO3PARAMS^ Params);

array<byte>^ crSarray();

//формирование массива посылок для заданного теста
array<byte>^ crArray(int Test, int ProdNum, bool i2c_status, bool checked, bool synchrCheck);


#endif