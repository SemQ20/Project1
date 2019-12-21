#include "MyForm.h"
#include "Uart_settings.h"


#include "stdafx.h"
#include <windows.h>
//============================================================================
//  Use of FTDI D2XX library:
//----------------------------------------------------------------------------
//  Include the following 2 lines in your header-file
#pragma comment(lib, "ftd2xx.lib")
#include "ftd2xx.h"
//============================================================================

#include <stdlib.h>
#include "i2c_master.h"
#include "arrays.h"
#include "USB_set.h"
#include "parse.h"
#include "ConvertResI2C.h"
#include "PowerCorrect.h"
#include "IPZO2Tests.h"
#include "IPZO3Tests.h"
#include "IPZO4Tests.h"
#include "IPZO5Tests.h"
#include "I2C_R_W.h"
#include "except.h"
#include "ftdi_init.h"

bool measure;
bool pullup_enable;
bool PKSA_POWER;
double Volt;
unsigned char SlaveAddr;
bool i2c_send;
unsigned char Datalength;
int Testnum;
int ProductNum;
unsigned char firstbyte;
unsigned int timercount;
unsigned int timercount1;
bool ftdiStatus;

double CABLE_KOEF_01dB[10][2][3];
double CABLE_KOEF[10][2][3];
double POWER_KOEF[2][3];
double SENS_KOEF_01dB[2][3];
double POWER_CORRECT[15][2][3];



System::Void Project1::MyForm::Close_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	serialPort1->Close();
	Application::Exit();
}

System::Void Project1::MyForm::i2c_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	bool request = i2cm_for_pickit(Volt, PKSA_POWER);
	ftdiStatus = FTDI_init(toolStripStatusLabel1);
	if (request || ftdiStatus)
	{
		if (request)
		{
			PKSA_chBox->Checked = true;
			groupBox2->Enabled = true;
			i2c->System::Windows::Forms::Button::BackColor = Color::Green;
			toolStripStatusLabel1->Text = "PICkitS cofig for I2CM" + "\n";
		}
		else
		{
			FTDI_chBox->Checked = true;
			groupBox2->Enabled = true;
			i2c->System::Windows::Forms::Button::BackColor = Color::Green;
			toolStripStatusLabel1->Text = "FTDI click сконфигурирован";
		}
	}
	else
	{
		PKSA_chBox->Checked = false;
		FTDI_chBox->Checked = false;
		i2c->System::Windows::Forms::Button::BackColor = Color::Red;
		toolStripStatusLabel1->Text = "Не один из конвертеров интерфейса не сконфигурирован" + "\n";
	}
}

// ПУСК ИЗМЕРЕНИЯ
System::Void Project1::MyForm::Measure_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	I2CParams^i2cp;
	i2cp = gcnew I2CParams;
	Testnum = Convert::ToUInt16(textBox5->Text);
	ProductNum = Convert::ToUInt16(textBox4->Text);
	bool Modulation = checkBox3->Checked;
	bool Synchronization = checkBox2->Checked;
	richTextBox1->Clear();
	if (PKSA_chBox->Checked || FTDI_chBox->Checked || USB_chBox->Checked)
	{
		if ((USB->System::Windows::Forms::Button::BackColor == Color::Gray) || (Btn_FSU->System::Windows::Forms::Button::BackColor == Color::Gray))
		{
			Data_Send(serialPort1, textBox4->Text, textBox5->Text);
			timerCom_set();
			toolStripStatusLabel1->Text = "Запись в COM порт произведена успешно";
		}
		else if (ftdiStatus == true)
		{
			i2c_send_byte_ftdi(Testnum, ProductNum, i2cp, Modulation, Synchronization, toolStripStatusLabel1);
			timerFTDI_set();
			if (measure) toolStripStatusLabel1->Text = "Запись произведена успешно";
			else toolStripStatusLabel1->Text = "Ошибка записи";
		}
		else
		{
			measure = I2C_send_byte(Testnum, ProductNum, i2cp, Modulation, Synchronization);
			timer_set();
			if (measure) toolStripStatusLabel1->Text = "Запись произведена успешно";
			else toolStripStatusLabel1->Text = "Ошибка записи";
		}
	}
	else
	{
		toolStripStatusLabel1->Text = "Не октрыт порт или не сконфигурирован преобразователь интерфейса";
	}
}

//Extern Voltage PKSA
System::Void Project1::MyForm::checkBox1_CheckedChanged_1(System::Object ^ sender, System::EventArgs ^ e)
{
	if (checkBox1->Checked)
	{
		PICkitS::I2CM::Tell_PKSA_To_Use_External_Voltage_Source();
		PKSA_POWER = false;
		toolStripStatusLabel1->Text = "Внешнее питание для PKSA" + "\n";
	}
	else
	{
		PKSA_POWER = false;
		Volt = 3.3;
		PICkitS::I2CM::Set_Source_Voltage(Volt);
		toolStripStatusLabel1->Text = "Внешнее питание для PKSA отключено, включено ВНУТРЕННЕЕ ПИТАНИЕ" + "\n";
	}
}

//Accept IPZO3 Params
System::Void Project1::MyForm::button7_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	String^ Result;
	I2CParams^ i2cp;
	i2cp = gcnew I2CParams;
	IPZO3PARAMS^ Params; //указатель на структуру аргументов и выделение под него памяти
	Params = gcnew IPZO3PARAMS;
	unsigned char valueArm = Convert::ToByte(numericUpDown1->Value);
	unsigned char valueFrequency = Convert::ToByte(numericUpDown2->Value);
	unsigned char valuePrelimAtt = Convert::ToByte(numericUpDown3->Value);
	unsigned char valueOutOK = Convert::ToByte(numericUpDown4->Value);
	unsigned char valueOutPBL = Convert::ToByte(numericUpDown5->Value);
	unsigned char typeOut = Convert::ToByte(numericUpDown6->Value);
	unsigned char valueModulator = Convert::ToByte(numericUpDown7->Value);
	setIPZO3Params(valueArm, valueFrequency, valuePrelimAtt, valueOutOK, valueOutPBL, typeOut, valueModulator, Params);//передача параметров в структуру для создания массива
	Result = setIPZO3ParamsToI2c(i2cp);
	toolStripStatusLabel1->Text = Result;
}

//Product--
System::Void Project1::MyForm::button2_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	int Value;
	String^ Value1;
	Value = Convert::ToInt16(textBox4->Text);
	Value--;
	Value1 = Convert::ToString(Value);
	textBox4->Text = Value1;
}

//Product++
System::Void Project1::MyForm::button3_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	unsigned int Value;
	String^ Value1;
	Value = Convert::ToInt16(textBox4->Text);
	Value++;
	Value1 = Convert::ToString(Value);
	textBox4->Text = Value1;
}

//Test--
System::Void Project1::MyForm::button4_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	int Value;
	String^ Value1;
	Value = Convert::ToInt16(textBox5->Text);
	Value--;
	Value1 = Convert::ToString(Value);
	textBox5->Text = Value1;
}

//Test++
System::Void Project1::MyForm::button5_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	int Value;
	String^ Value1;
	Value = Convert::ToInt16(textBox5->Text);
	Value++;
	Value1 = Convert::ToString(Value);
	textBox5->Text = Value1;
}

//Open File
System::Void Project1::MyForm::button8_Click_2(System::Object ^ sender, System::EventArgs ^ e)
{
	openFileDialog1->InitialDirectory = "C:\\Desktop";
	openFileDialog1->Filter = "All files (*.*)|*.*|ctb files(*.ctb) | *.ctb";
	openFileDialog1->FilterIndex = 2;
	openFileDialog1->RestoreDirectory = true;
	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		if ((myStream = openFileDialog1->OpenFile()) != nullptr)
		{
			filename = openFileDialog1->FileName;
			textBox7->Text = filename;
			delete openFileDialog1;
			myStream->Close();
		}
	}
	else
	{
		toolStripStatusLabel1->Text = "Неверный тип файла или файл не был выбран";
		delete openFileDialog1;
	}
}

//Read File
System::Void Project1::MyForm::button9_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	double buffer[230];
	bool ex;
	Except exc;
	ex = exc.exCapture(filename, 1, toolStripStatusLabel1); if (!ex)return;
	parse(filename, buffer);
	fillArraysAfterParse(CABLE_KOEF_01dB, CABLE_KOEF, POWER_KOEF, SENS_KOEF_01dB, POWER_CORRECT, buffer);
}

//FSU
System::Void Project1::MyForm::button6_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	bool ex;
	Uart_settings ^f2 = gcnew Uart_settings();
	f2->ShowDialog();
	Except exc;
	ex=exc.exCapture(ComPort = f2->Comport, 0, toolStripStatusLabel1);
	if (!ex)return;
	Btn_FSU->System::Windows::Forms::Button::BackColor = Color::Gray;
	if (USB->System::Windows::Forms::Button::BackColor == Color::Gray)
	{
		USB->System::Windows::Forms::Button::BackColor = Color::White;
	}
	USB_Set(serialPort1, ComPort);
	if (serialPort1->IsOpen)
	{
		USB_chBox->Checked = true;
		groupBox2->Enabled = true;
		toolStripStatusLabel1->Text = "Порт открыт";
	}
	else
	{
		USB_chBox->Checked = false;
		toolStripStatusLabel1->Text = "Ошибка открытия порта";
	}
}

System::Void Project1::MyForm::USB_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	bool ex;
	Uart_settings ^f2 = gcnew Uart_settings();
	f2->ShowDialog();
	Except exc;
	ex = exc.exCapture(ComPort = f2->Comport, 0, toolStripStatusLabel1);
	if (!ex)return;
	USB->System::Windows::Forms::Button::BackColor = Color::Gray;
	if (Btn_FSU->System::Windows::Forms::Button::BackColor == Color::Gray)
	{
		Btn_FSU->System::Windows::Forms::Button::BackColor = Color::White;
	}
	USB_Set(serialPort1, ComPort);
	if (serialPort1->IsOpen)
	{
		USB_chBox->Checked = true;
		groupBox2->Enabled = true;
		toolStripStatusLabel1->Text = "Порт открыт";
	}
	else
	{
		USB_chBox->Checked = false;
		toolStripStatusLabel1->Text = "Ошибка открытия порта";
	}
}

void Project1::MyForm::timer_set()
{
	timercount = 0;
	timer1->Start();
}

void Project1::MyForm::timerCom_set()
{
	timercount1 = 0;
	timer2->Start();
}

void Project1::MyForm::timerFTDI_set()
{
	timercount1 = 0;
	timer3->Start();
}

System::Void Project1::MyForm::timer1_Tick(System::Object ^ sender, System::EventArgs ^ e)
{
	String^ Result;
	Testnum = Convert::ToUInt16(textBox5->Text);
	ProductNum = Convert::ToInt16(textBox4->Text);
	I2CParams^i2cp = gcnew I2CParams;
	timercount++;
	if (timercount >= 0 && timercount < 8) //3s
	{

		toolStripStatusLabel1->Text = "ПРОИЗВОДИТСЯ ИЗМЕРЕНИЕ";

	}
	if (timercount == 5)
	{
		Result = I2C_Read(Testnum, ProductNum, CABLE_KOEF, POWER_KOEF, POWER_CORRECT, i2cp);
		richTextBox1->Text = Result;

	}
	if (timercount == 8)
	{
		toolStripStatusLabel1->Text = "  ";
		timer1->Stop();
	}
}

System::Void Project1::MyForm::timer2_Tick(System::Object ^ sender, System::EventArgs ^ e)
{
	String^ Result;
	timercount1++;
	if (timercount1 > 0 && timercount1 < 8) //1s
	{
		toolStripStatusLabel1->Text = "ПРОИЗВОДИТСЯ ИЗМЕРЕНИЕ";
	}
	if (timercount1 == 5)
	{
		Result = DataRecieave(serialPort1, textBox5->Text);
		richTextBox1->Text = Result;
	}
	if (timercount1 == 8)
	{
		toolStripStatusLabel1->Text = " ";
		timer2->Stop();
	}
}

System::Void Project1::MyForm::timer3_Tick(System::Object ^ sender, System::EventArgs ^ e)
{
	String^ Result;
	I2CParams^i2cp = gcnew I2CParams;
	timercount1++;
	int TestNum = Convert::ToInt16(textBox5->Text);
	int ProdNum = Convert::ToInt16(textBox4->Text);
	if (timercount1 > 0 && timercount1 < 8) //1s
	{
		toolStripStatusLabel1->Text = "ПРОИЗВОДИТСЯ ИЗМЕРЕНИЕ";
	}
	if (timercount1 == 5)
	{
		Result = i2c_read_ftdi(TestNum, ProdNum, CABLE_KOEF, POWER_KOEF, POWER_CORRECT, i2cp);
		richTextBox1->Text = Result;
	}
	if (timercount1 == 8)
	{
		toolStripStatusLabel1->Text = " ";
		timer2->Stop();
	}
}

//Обработчик клавиатуры
System::Void Project1::MyForm::MyForm_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e)
{
	if (e->KeyChar == '\r')
	{
		Measure_Click(Measure, nullptr);
	}
	if (e->KeyChar == '\033')
	{
		if (MessageBox::Show("Вы действительно хотите закрыть программу?", "ИПЗО",
			MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes)
		{
			Application::Exit();
		}
		else {}
	}
	if (e->KeyChar >= '0'&&e->KeyChar <= '9')
	{
		if (textBox5->Text == "0")
		{
			textBox5->Text = Convert::ToString(e->KeyChar);
		}
		else
		{
			textBox5->Text += Convert::ToString(e->KeyChar);
		}
	}
	if(e->KeyChar== '\b')
	{
		int idx;
		String^ temp;
		idx=textBox5->Text->Length-1;
		temp=textBox5->Text->Remove(idx);
		textBox5->Text = temp;
	}
}

