#pragma once
#include "namespaces.h"

ref struct Vstr { //структура аргументов используемых функций
	String^ PValue; // целая часть мощности взятая типом String после парса файла поправочных коэф-ов
	String^ DValue; // дробная часть мощности взятая типом String после парса файла поправочных коэф-ов
	int OKnum; // номер канала ок1 или ок2
	int Fnum; // частота (f2,f3,f4)
	int CableNum; // номер кабеля для поправочных коэф-ов по мощности
	double power;
	double(*CABLE_KOEF)[2][3]; //массив поправок для кабелей
	double(*POWER_KOEF)[3]; //массив коэ-ов для мощности
	double(*POWER_CORRECT)[2][3];
};

void setStrParams(int Test, Vstr ^valStr, String^ integer, String^ tenth);

double PowerCorrection(Vstr ^valStr);

String^ PowerCorrect(Vstr ^valStr);
