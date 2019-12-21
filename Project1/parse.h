#pragma once


#pragma region
using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::ComponentModel;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Text;
using namespace System::Text::RegularExpressions;
using namespace System::IO;
using namespace System::IO::Ports;
using namespace System::Runtime::InteropServices;
using namespace System::Globalization;
#pragma endregion

static double ParseDouble(String^ text)
{
	double result;
	if (!Double::TryParse(text, NumberStyles::Any, CultureInfo::GetCultureInfo("ru-RU"), result))
	{
		if (!Double::TryParse(text, NumberStyles::Any, CultureInfo::GetCultureInfo("en-US"), result))
		{
			result = Double::NaN;
		}
	}
	return result;
}


void parse(String^ filename,double *buffer)
{
	String^ str;
	int c = 0;
	List<array<String^>^>^ list = gcnew List<array<String^>^>();
	for each (String^ line in File::ReadLines(filename))
	{
		list->Add(line->Replace("{",",")->Split(','));
	}
	array<String^>^ row = list[0]; 
	String^ cell = row[0];         						  
	int length = row->Length;
	cell = dynamic_cast<array<String^>^>(list[0])[0];
	for each (array<String^>^ row in list)
	{
		for (int i = 0; i < row->Length; i++)
		{
				if (row[i]->Length > 10)
				{}
				if (row[i]->Length > 0 && row[i]->Length < 12)
				{
					cell = row[i];
					buffer[c]=ParseDouble(str = cell->Replace("{", "")->Replace("}", "")->Replace("\t", ""));
					if (Convert::ToString(buffer[c]) == "NaN")
					{}
					else
					{c++;}	
				}
		}
	}
	delete[]row;
	delete[]list;
	delete[]cell;	
}


