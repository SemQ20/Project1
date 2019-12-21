#pragma once


extern bool measure;
extern bool pullup_enable;
extern bool PKSA_POWER;
extern double Volt;
extern unsigned char SlaveAddr;
extern bool i2c_send;
extern unsigned char Datalength;
extern int Testnum;
extern int ProductNum;
extern unsigned char firstbyte;
extern unsigned int timercount;
extern unsigned int timercount1;
extern bool ftdiStatus;

extern double CABLE_KOEF_01dB[10][2][3];
extern double CABLE_KOEF[10][2][3];
extern double POWER_KOEF[2][3];
extern double SENS_KOEF_01dB[2][3];
extern double POWER_CORRECT[15][2][3];


namespace Project1 {
	using namespace System;
	using namespace System::Threading;
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
	/// <summary>T
	/// Summary for MyForm
	/// </summary>
	
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
		}
	public:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	
#pragma region
	private: System::Windows::Forms::Button^  Close;
	private: System::Windows::Forms::Button^  i2c;


	private: System::Windows::Forms::Button^  USB;

	private: System::Windows::Forms::RichTextBox^  richTextBox1;
	public: System::Windows::Forms::Button^  Measure;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown1;
	private: System::Windows::Forms::Label^  label1;

	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::TextBox^  textBox5;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::Button^  Btn_FSU;

	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown3;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown2;
	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown7;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown6;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown5;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown4;
	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::Button^  button7;
	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	public: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel1;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::TextBox^  textBox7;
	private: System::Windows::Forms::Button^  button8;
	private: System::Windows::Forms::Button^  button9;
	private: System::Windows::Forms::Label^  label18;
	private: System::ComponentModel::IContainer^  components;
	public:
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::IO::Ports::SerialPort^  serialPort1;
	private: System::Windows::Forms::CheckBox^  checkBox2;
	private: System::Windows::Forms::CheckBox^  checkBox3;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Button^  button6;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::RadioButton^  radioButton2;
	private: System::Windows::Forms::RadioButton^  radioButton1;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Timer^  timer2;
	private: System::Windows::Forms::CheckBox^  PKSA_chBox;
	private: System::Windows::Forms::CheckBox^  FTDI_chBox;
	private: System::Windows::Forms::CheckBox^  USB_chBox;
	private: System::Windows::Forms::GroupBox^  groupBox4;
	private: System::Windows::Forms::Timer^  timer3;
#pragma endregion

	protected:
	public:

		/*Глобальные переменные, которые в силу своих особенностей нельзя объявить вне namespace*/
		Stream^ myStream;
		String^ filename;
		OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;
		String^ ComPort;

		/// <summary>
		/// Required designer variable.
		/// </summary>

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->Close = (gcnew System::Windows::Forms::Button());
			this->i2c = (gcnew System::Windows::Forms::Button());
			this->USB = (gcnew System::Windows::Forms::Button());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->Measure = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown7 = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDown6 = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDown5 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->numericUpDown4 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown3 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown2 = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->Btn_FSU = (gcnew System::Windows::Forms::Button());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->serialPort1 = (gcnew System::IO::Ports::SerialPort(this->components));
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox3 = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->timer2 = (gcnew System::Windows::Forms::Timer(this->components));
			this->PKSA_chBox = (gcnew System::Windows::Forms::CheckBox());
			this->FTDI_chBox = (gcnew System::Windows::Forms::CheckBox());
			this->USB_chBox = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->timer3 = (gcnew System::Windows::Forms::Timer(this->components));
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown7))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown6))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
			this->statusStrip1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->SuspendLayout();
			// 
			// Close
			// 
			this->Close->BackColor = System::Drawing::SystemColors::Window;
			this->Close->Location = System::Drawing::Point(263, 557);
			this->Close->Name = L"Close";
			this->Close->Size = System::Drawing::Size(75, 23);
			this->Close->TabIndex = 0;
			this->Close->TabStop = false;
			this->Close->Text = L"Close";
			this->Close->UseVisualStyleBackColor = false;
			this->Close->Click += gcnew System::EventHandler(this, &MyForm::Close_Click);
			// 
			// i2c
			// 
			this->i2c->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->i2c->Location = System::Drawing::Point(489, 148);
			this->i2c->Name = L"i2c";
			this->i2c->Size = System::Drawing::Size(75, 23);
			this->i2c->TabIndex = 0;
			this->i2c->TabStop = false;
			this->i2c->Text = L"I2C";
			this->i2c->UseVisualStyleBackColor = false;
			this->i2c->Click += gcnew System::EventHandler(this, &MyForm::i2c_Click);
			// 
			// USB
			// 
			this->USB->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->USB->Location = System::Drawing::Point(489, 206);
			this->USB->Name = L"USB";
			this->USB->Size = System::Drawing::Size(75, 23);
			this->USB->TabIndex = 0;
			this->USB->TabStop = false;
			this->USB->Text = L"USB";
			this->USB->UseVisualStyleBackColor = false;
			this->USB->Click += gcnew System::EventHandler(this, &MyForm::USB_Click);
			// 
			// richTextBox1
			// 
			this->richTextBox1->Location = System::Drawing::Point(153, 45);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(276, 217);
			this->richTextBox1->TabIndex = 11;
			this->richTextBox1->TabStop = false;
			this->richTextBox1->Text = L"";
			// 
			// Measure
			// 
			this->Measure->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->Measure->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->Measure->Location = System::Drawing::Point(479, 119);
			this->Measure->Name = L"Measure";
			this->Measure->Size = System::Drawing::Size(91, 23);
			this->Measure->TabIndex = 12;
			this->Measure->TabStop = false;
			this->Measure->Text = L"ПУСК ИЗМЕР";
			this->Measure->UseVisualStyleBackColor = false;
			this->Measure->Click += gcnew System::EventHandler(this, &MyForm::Measure_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->label16);
			this->groupBox1->Controls->Add(this->label15);
			this->groupBox1->Controls->Add(this->numericUpDown7);
			this->groupBox1->Controls->Add(this->numericUpDown6);
			this->groupBox1->Controls->Add(this->numericUpDown5);
			this->groupBox1->Controls->Add(this->label14);
			this->groupBox1->Controls->Add(this->label13);
			this->groupBox1->Controls->Add(this->button7);
			this->groupBox1->Controls->Add(this->numericUpDown4);
			this->groupBox1->Controls->Add(this->label12);
			this->groupBox1->Controls->Add(this->numericUpDown3);
			this->groupBox1->Controls->Add(this->label11);
			this->groupBox1->Controls->Add(this->numericUpDown2);
			this->groupBox1->Controls->Add(this->numericUpDown1);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Location = System::Drawing::Point(12, 335);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(245, 245);
			this->groupBox1->TabIndex = 13;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Параметры ИПЗО";
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(6, 179);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(62, 13);
			this->label16->TabIndex = 43;
			this->label16->Text = L"Модулятор";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(6, 153);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(39, 13);
			this->label15->TabIndex = 36;
			this->label15->Text = L"Выход";
			// 
			// numericUpDown7
			// 
			this->numericUpDown7->Location = System::Drawing::Point(117, 179);
			this->numericUpDown7->Name = L"numericUpDown7";
			this->numericUpDown7->Size = System::Drawing::Size(120, 20);
			this->numericUpDown7->TabIndex = 42;
			this->numericUpDown7->TabStop = false;
			// 
			// numericUpDown6
			// 
			this->numericUpDown6->Location = System::Drawing::Point(117, 153);
			this->numericUpDown6->Name = L"numericUpDown6";
			this->numericUpDown6->Size = System::Drawing::Size(120, 20);
			this->numericUpDown6->TabIndex = 41;
			this->numericUpDown6->TabStop = false;
			// 
			// numericUpDown5
			// 
			this->numericUpDown5->Location = System::Drawing::Point(117, 127);
			this->numericUpDown5->Name = L"numericUpDown5";
			this->numericUpDown5->Size = System::Drawing::Size(120, 20);
			this->numericUpDown5->TabIndex = 40;
			this->numericUpDown5->TabStop = false;
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(6, 83);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(79, 13);
			this->label14->TabIndex = 39;
			this->label14->Text = L"Код предв. ат.";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(6, 129);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(103, 13);
			this->label13->TabIndex = 38;
			this->label13->Text = L"Код выход ат. ПБЛ";
			// 
			// button7
			// 
			this->button7->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->button7->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->button7->Location = System::Drawing::Point(81, 216);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(75, 23);
			this->button7->TabIndex = 35;
			this->button7->TabStop = false;
			this->button7->Text = L"Отправить";
			this->button7->UseVisualStyleBackColor = false;
			this->button7->Click += gcnew System::EventHandler(this, &MyForm::button7_Click);
			// 
			// numericUpDown4
			// 
			this->numericUpDown4->Location = System::Drawing::Point(117, 103);
			this->numericUpDown4->Name = L"numericUpDown4";
			this->numericUpDown4->Size = System::Drawing::Size(120, 20);
			this->numericUpDown4->TabIndex = 37;
			this->numericUpDown4->TabStop = false;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(6, 105);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(95, 13);
			this->label12->TabIndex = 36;
			this->label12->Text = L"Код выход ат. ОК";
			// 
			// numericUpDown3
			// 
			this->numericUpDown3->Location = System::Drawing::Point(117, 79);
			this->numericUpDown3->Name = L"numericUpDown3";
			this->numericUpDown3->Size = System::Drawing::Size(120, 20);
			this->numericUpDown3->TabIndex = 35;
			this->numericUpDown3->TabStop = false;
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(6, 58);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(49, 13);
			this->label11->TabIndex = 35;
			this->label11->Text = L"Частота";
			// 
			// numericUpDown2
			// 
			this->numericUpDown2->Location = System::Drawing::Point(117, 55);
			this->numericUpDown2->Name = L"numericUpDown2";
			this->numericUpDown2->Size = System::Drawing::Size(120, 20);
			this->numericUpDown2->TabIndex = 34;
			this->numericUpDown2->TabStop = false;
			this->numericUpDown2->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->Location = System::Drawing::Point(117, 31);
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(120, 20);
			this->numericUpDown1->TabIndex = 1;
			this->numericUpDown1->TabStop = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(6, 35);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(77, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Уровень АРМ";
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(232, 55);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(41, 20);
			this->textBox4->TabIndex = 26;
			this->textBox4->TabStop = false;
			this->textBox4->Text = L"0";
			this->textBox4->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(374, 55);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(41, 20);
			this->textBox5->TabIndex = 27;
			this->textBox5->TabStop = false;
			this->textBox5->Text = L"0";
			this->textBox5->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox5->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox5_TextChanged);
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->label9->Location = System::Drawing::Point(22, 17);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(62, 13);
			this->label9->TabIndex = 28;
			this->label9->Text = L"ИЗДЕЛИЯ";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(31, 59);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(42, 13);
			this->label10->TabIndex = 29;
			this->label10->Text = L"ТЕСТА";
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::SystemColors::Window;
			this->button2->Location = System::Drawing::Point(6, 33);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(38, 23);
			this->button2->TabIndex = 18;
			this->button2->TabStop = false;
			this->button2->Text = L"<";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button3
			// 
			this->button3->BackColor = System::Drawing::SystemColors::Window;
			this->button3->Location = System::Drawing::Point(60, 33);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(38, 23);
			this->button3->TabIndex = 30;
			this->button3->TabStop = false;
			this->button3->Text = L">";
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// button4
			// 
			this->button4->BackColor = System::Drawing::SystemColors::Window;
			this->button4->Location = System::Drawing::Point(6, 78);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(38, 23);
			this->button4->TabIndex = 31;
			this->button4->TabStop = false;
			this->button4->Text = L"<";
			this->button4->UseVisualStyleBackColor = false;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// button5
			// 
			this->button5->BackColor = System::Drawing::SystemColors::Window;
			this->button5->Location = System::Drawing::Point(60, 78);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(38, 23);
			this->button5->TabIndex = 32;
			this->button5->TabStop = false;
			this->button5->Text = L">";
			this->button5->UseVisualStyleBackColor = false;
			this->button5->Click += gcnew System::EventHandler(this, &MyForm::button5_Click);
			// 
			// Btn_FSU
			// 
			this->Btn_FSU->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->Btn_FSU->Location = System::Drawing::Point(489, 177);
			this->Btn_FSU->Name = L"Btn_FSU";
			this->Btn_FSU->Size = System::Drawing::Size(75, 23);
			this->Btn_FSU->TabIndex = 33;
			this->Btn_FSU->TabStop = false;
			this->Btn_FSU->Text = L"FSU";
			this->Btn_FSU->UseVisualStyleBackColor = false;
			this->Btn_FSU->Click += gcnew System::EventHandler(this, &MyForm::button6_Click);
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(473, 235);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(104, 17);
			this->checkBox1->TabIndex = 34;
			this->checkBox1->TabStop = false;
			this->checkBox1->Text = L"Внешн. пит. I2C";
			this->checkBox1->UseVisualStyleBackColor = true;
			this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBox1_CheckedChanged_1);
			// 
			// statusStrip1
			// 
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->toolStripStatusLabel1 });
			this->statusStrip1->Location = System::Drawing::Point(0, 593);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(577, 22);
			this->statusStrip1->TabIndex = 36;
			// 
			// toolStripStatusLabel1
			// 
			this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
			this->toolStripStatusLabel1->Size = System::Drawing::Size(0, 17);
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// textBox7
			// 
			this->textBox7->Location = System::Drawing::Point(12, 309);
			this->textBox7->Name = L"textBox7";
			this->textBox7->Size = System::Drawing::Size(471, 20);
			this->textBox7->TabIndex = 40;
			this->textBox7->TabStop = false;
			// 
			// button8
			// 
			this->button8->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->button8->Location = System::Drawing::Point(489, 304);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(75, 23);
			this->button8->TabIndex = 41;
			this->button8->TabStop = false;
			this->button8->Text = L"Select file";
			this->button8->UseVisualStyleBackColor = false;
			this->button8->Click += gcnew System::EventHandler(this, &MyForm::button8_Click_2);
			// 
			// button9
			// 
			this->button9->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->button9->Location = System::Drawing::Point(489, 333);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(75, 23);
			this->button9->TabIndex = 42;
			this->button9->TabStop = false;
			this->button9->Text = L"Read file";
			this->button9->UseVisualStyleBackColor = false;
			this->button9->Click += gcnew System::EventHandler(this, &MyForm::button9_Click);
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Location = System::Drawing::Point(9, 291);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(159, 13);
			this->label18->TabIndex = 43;
			this->label18->Text = L"Поправочные коэффициенты:";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->label9);
			this->groupBox2->Controls->Add(this->button3);
			this->groupBox2->Controls->Add(this->button2);
			this->groupBox2->Controls->Add(this->label10);
			this->groupBox2->Controls->Add(this->button5);
			this->groupBox2->Controls->Add(this->button4);
			this->groupBox2->Enabled = false;
			this->groupBox2->Location = System::Drawing::Point(466, 12);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(104, 107);
			this->groupBox2->TabIndex = 45;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"ВЫБОР";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label2->Location = System::Drawing::Point(164, 58);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(61, 13);
			this->label2->TabIndex = 33;
			this->label2->Text = L"ИЗДЕЛИЕ";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label3->Location = System::Drawing::Point(326, 58);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(35, 13);
			this->label3->TabIndex = 46;
			this->label3->Text = L"ТЕСТ";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label4->Location = System::Drawing::Point(256, 12);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(42, 13);
			this->label4->TabIndex = 47;
			this->label4->Text = L"ИПЗО";
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->Location = System::Drawing::Point(473, 258);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(94, 17);
			this->checkBox2->TabIndex = 48;
			this->checkBox2->TabStop = false;
			this->checkBox2->Text = L"Внешн. синхр";
			this->checkBox2->UseVisualStyleBackColor = true;
			// 
			// checkBox3
			// 
			this->checkBox3->AutoSize = true;
			this->checkBox3->Location = System::Drawing::Point(473, 281);
			this->checkBox3->Name = L"checkBox3";
			this->checkBox3->Size = System::Drawing::Size(93, 17);
			this->checkBox3->TabIndex = 49;
			this->checkBox3->TabStop = false;
			this->checkBox3->Text = L"Внешн.модул";
			this->checkBox3->UseVisualStyleBackColor = true;
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->label6);
			this->groupBox3->Controls->Add(this->button6);
			this->groupBox3->Controls->Add(this->button1);
			this->groupBox3->Controls->Add(this->radioButton2);
			this->groupBox3->Controls->Add(this->radioButton1);
			this->groupBox3->Controls->Add(this->label5);
			this->groupBox3->Enabled = false;
			this->groupBox3->Location = System::Drawing::Point(0, 12);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(147, 250);
			this->groupBox3->TabIndex = 50;
			this->groupBox3->TabStop = false;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->label6->Location = System::Drawing::Point(47, 170);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(66, 13);
			this->label6->TabIndex = 53;
			this->label6->Text = L"ПАРАМЕТР";
			// 
			// button6
			// 
			this->button6->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->button6->Location = System::Drawing::Point(50, 194);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(38, 23);
			this->button6->TabIndex = 52;
			this->button6->TabStop = false;
			this->button6->Text = L">";
			this->button6->UseVisualStyleBackColor = false;
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->button1->Location = System::Drawing::Point(50, 136);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(38, 23);
			this->button1->TabIndex = 51;
			this->button1->TabStop = false;
			this->button1->Text = L"<";
			this->button1->UseVisualStyleBackColor = false;
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Location = System::Drawing::Point(28, 90);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(72, 17);
			this->radioButton2->TabIndex = 36;
			this->radioButton2->Text = L"ЦИКЛИЧ";
			this->radioButton2->UseVisualStyleBackColor = true;
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Location = System::Drawing::Point(28, 67);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(82, 17);
			this->radioButton1->TabIndex = 35;
			this->radioButton1->Text = L"ОДИНОЧН";
			this->radioButton1->UseVisualStyleBackColor = true;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->label5->Location = System::Drawing::Point(47, 43);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(48, 13);
			this->label5->TabIndex = 34;
			this->label5->Text = L"ВЫВОД";
			// 
			// timer2
			// 
			this->timer2->Tick += gcnew System::EventHandler(this, &MyForm::timer2_Tick);
			// 
			// PKSA_chBox
			// 
			this->PKSA_chBox->AutoSize = true;
			this->PKSA_chBox->Location = System::Drawing::Point(6, 13);
			this->PKSA_chBox->Name = L"PKSA_chBox";
			this->PKSA_chBox->Size = System::Drawing::Size(54, 17);
			this->PKSA_chBox->TabIndex = 52;
			this->PKSA_chBox->TabStop = false;
			this->PKSA_chBox->Text = L"PKSA";
			this->PKSA_chBox->UseVisualStyleBackColor = true;
			// 
			// FTDI_chBox
			// 
			this->FTDI_chBox->AutoSize = true;
			this->FTDI_chBox->Location = System::Drawing::Point(65, 13);
			this->FTDI_chBox->Name = L"FTDI_chBox";
			this->FTDI_chBox->Size = System::Drawing::Size(50, 17);
			this->FTDI_chBox->TabIndex = 53;
			this->FTDI_chBox->TabStop = false;
			this->FTDI_chBox->Text = L"FTDI";
			this->FTDI_chBox->UseVisualStyleBackColor = true;
			// 
			// USB_chBox
			// 
			this->USB_chBox->AutoSize = true;
			this->USB_chBox->Location = System::Drawing::Point(117, 13);
			this->USB_chBox->Name = L"USB_chBox";
			this->USB_chBox->Size = System::Drawing::Size(48, 17);
			this->USB_chBox->TabIndex = 54;
			this->USB_chBox->TabStop = false;
			this->USB_chBox->Text = L"USB";
			this->USB_chBox->UseVisualStyleBackColor = true;
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->USB_chBox);
			this->groupBox4->Controls->Add(this->FTDI_chBox);
			this->groupBox4->Controls->Add(this->PKSA_chBox);
			this->groupBox4->Enabled = false;
			this->groupBox4->Location = System::Drawing::Point(194, 268);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(167, 36);
			this->groupBox4->TabIndex = 51;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Активное устройство";
			// 
			// timer3
			// 
			this->timer3->Tick += gcnew System::EventHandler(this, &MyForm::timer3_Tick);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(577, 615);
			this->Controls->Add(this->groupBox4);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->checkBox3);
			this->Controls->Add(this->checkBox2);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->label18);
			this->Controls->Add(this->button9);
			this->Controls->Add(this->button8);
			this->Controls->Add(this->textBox7);
			this->Controls->Add(this->statusStrip1);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->Btn_FSU);
			this->Controls->Add(this->i2c);
			this->Controls->Add(this->textBox5);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->Measure);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->USB);
			this->Controls->Add(this->Close);
			this->Name = L"MyForm";
			this->Text = L"ИПЗО";
			this->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::MyForm_KeyPress);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown7))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown6))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}

#pragma endregion
private: System::Void Close_Click(System::Object^  sender, System::EventArgs^  e);
 
//конфигурирование I2C для PKSA
public: System::Void i2c_Click(System::Object^  sender, System::EventArgs^  e);
		
//функции установки таймера
public:
	void timer_set();
	void timerCom_set();
	void timerFTDI_set();

//по нажатию кнопки начинает измерение по тому или иному интерфейсу
public: System::Void Measure_Click(System::Object^  sender, System::EventArgs^  e);

//установка внешнего питания для PKSA по нажатию на checkBox
private: System::Void checkBox1_CheckedChanged_1(System::Object^  sender, System::EventArgs^  e);

//отправляет заданные значения из numericDown в ИПЗО3
private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e);

//реализация кнопки уменьшения значения теста на 1
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e);

//реализация кнопки увеличения значения теста на 1
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e);

//реализация кнопки уменьшения значения теста на 1
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e);

//реализация кнопки увеличения значения теста на 1
private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e);

//Реализация таймера
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e);

//создание диалогового окна для выбора файла корректировочных коэффициентов
private: System::Void button8_Click_2(System::Object^  sender, System::EventArgs^  e);
		 
//парсер текста,заполнение массива по шаблону функций
private: System::Void button9_Click(System::Object^  sender, System::EventArgs^  e);

private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e);

private: System::Void USB_Click(System::Object^  sender, System::EventArgs^  e);

private: System::Void timer2_Tick(System::Object^  sender, System::EventArgs^  e);

private: System::Void timer3_Tick(System::Object^  sender, System::EventArgs^  e);
private: System::Void textBox5_TextChanged(System::Object^  sender, System::EventArgs^  e){};
private: System::Void MyForm_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);


};

}
