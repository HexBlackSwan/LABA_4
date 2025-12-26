#pragma once

namespace Laba34 {
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    /// <summary>
    /// Сводка для EditForm
    /// </summary>
    public ref class EditForm : public System::Windows::Forms::Form
    {
    public:
        String^ mode;
        EditForm(void)
        {
            InitializeComponent();
            SetupUI();
        }

        void SetMode(String^ m)
        {
            mode = m;
            if (mode == "Client")
            {
                this->Text = "Редактирование клиента";
                txtName->Visible = true;
                txtPhone->Visible = true;
                lblName->Visible = true;
                lblPhone->Visible = true;
                Combotype->Visible = false;
                txtPrice->Visible = false;
                lblType->Visible = false;
                lblPrice->Visible = false;
            }
            else if (mode == "Tariff")
            {
                this->Text = "Редактирование тарифа";
                txtName->Visible = false;
                txtPhone->Visible = false;
                lblName->Visible = false;
                lblPhone->Visible = false;
                Combotype->Visible = true;
                txtPrice->Visible = true;
                lblType->Visible = true;
                lblPrice->Visible = true;
                // Установим варианты типов
                Combotype->Items->Clear();
                Combotype->Items->Add("General");
                Combotype->Items->Add("Fragile");
                Combotype->Items->Add("Hazardous");
                Combotype->Items->Add("Refrigerated");
                Combotype->SelectedIndex = 0;
            }
        }

        // Для клиента
        property String^ ClientName {
            String^ get() { return txtName->Text; }
            void set(String^ value) { txtName->Text = value; }
        }

        property String^ ClientPhone {
            String^ get() { return txtPhone->Text; }
            void set(String^ value) { txtPhone->Text = value; }
        }

        // Для тарифа
        property String^ TariffTypeString {
            String^ get() {
                if (Combotype->SelectedItem != nullptr)
                    return Combotype->SelectedItem->ToString();
                return "";
            }
            void set(String^ value) { Combotype->SelectedItem = value; }
        }

        property double TariffPrice {
            double get() {
                double price = 0;
                Double::TryParse(txtPrice->Text, price);
                return price;
            }
            void set(double value) { txtPrice->Text = value.ToString("F2"); }
        }

    protected:
        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        ~EditForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        void SetupUI()
        {
            this->BackColor = Color::FromArgb(250, 250, 250);
            // Настройка стилей
            btnSave->BackColor = Color::FromArgb(76, 175, 80);
            btnSave->ForeColor = Color::White;
            btnSave->FlatStyle = FlatStyle::Flat;
            btnSave->FlatAppearance->BorderSize = 0;
            btnSave->Font = gcnew System::Drawing::Font("Segoe UI", 9, FontStyle::Bold);
            btnSave->Cursor = Cursors::Hand;
            txtName->BackColor = Color::White;
            txtPhone->BackColor = Color::White;
            txtPrice->BackColor = Color::White;
            Combotype->BackColor = Color::White;
        }

    private:
        System::Windows::Forms::Button^ btnSave;
        System::Windows::Forms::ToolTip^ toolTip1;
        System::Windows::Forms::TextBox^ txtName;
        System::Windows::Forms::TextBox^ txtPhone;
        System::Windows::Forms::ComboBox^ Combotype;
        System::Windows::Forms::TextBox^ txtPrice;
        System::Windows::Forms::Label^ lblName;
        System::Windows::Forms::Label^ lblPhone;
        System::Windows::Forms::Label^ lblType;
        System::Windows::Forms::Label^ lblPrice;
        System::ComponentModel::IContainer^ components;

#pragma region Windows Form Designer generated code
        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        void InitializeComponent(void)
        {
            this->components = (gcnew System::ComponentModel::Container());
            this->btnSave = (gcnew System::Windows::Forms::Button());
            this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
            this->txtName = (gcnew System::Windows::Forms::TextBox());
            this->txtPhone = (gcnew System::Windows::Forms::TextBox());
            this->txtPrice = (gcnew System::Windows::Forms::TextBox());
            this->Combotype = (gcnew System::Windows::Forms::ComboBox());
            this->lblName = (gcnew System::Windows::Forms::Label());
            this->lblPhone = (gcnew System::Windows::Forms::Label());
            this->lblType = (gcnew System::Windows::Forms::Label());
            this->lblPrice = (gcnew System::Windows::Forms::Label());
            this->SuspendLayout();

            //
            // btnSave
            //
            this->btnSave->Location = System::Drawing::Point(120, 180);
            this->btnSave->Name = L"btnSave";
            this->btnSave->Size = System::Drawing::Size(100, 35);
            this->btnSave->TabIndex = 0;
            this->btnSave->Text = L"Сохранить";
            this->btnSave->UseVisualStyleBackColor = true;
            this->btnSave->Click += gcnew System::EventHandler(this, &EditForm::btnSave_Click);

            //
            // txtName
            //
            this->txtName->Location = System::Drawing::Point(120, 40);
            this->txtName->Name = L"txtName";
            this->txtName->Size = System::Drawing::Size(200, 25);
            this->txtName->TabIndex = 1;
            this->toolTip1->SetToolTip(this->txtName, L"Введите имя клиента");

            //
            // txtPhone
            //
            this->txtPhone->Location = System::Drawing::Point(120, 80);
            this->txtPhone->Name = L"txtPhone";
            this->txtPhone->Size = System::Drawing::Size(200, 25);
            this->txtPhone->TabIndex = 2;
            this->toolTip1->SetToolTip(this->txtPhone, L"Введите номер клиента");

            //
            // txtPrice
            //
            this->txtPrice->Location = System::Drawing::Point(120, 80);
            this->txtPrice->Name = L"txtPrice";
            this->txtPrice->Size = System::Drawing::Size(200, 25);
            this->txtPrice->TabIndex = 4;
            this->toolTip1->SetToolTip(this->txtPrice, L"Введите цену за единицу");
            this->txtPrice->Visible = false;

            //
            // Combotype
            //
            this->Combotype->FormattingEnabled = true;
            this->Combotype->Location = System::Drawing::Point(120, 40);
            this->Combotype->Name = L"Combotype";
            this->Combotype->Size = System::Drawing::Size(200, 25);
            this->Combotype->TabIndex = 3;
            this->Combotype->Visible = false;

            //
            // lblName
            //
            this->lblName->AutoSize = true;
            this->lblName->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, FontStyle::Bold));
            this->lblName->Location = System::Drawing::Point(40, 43);
            this->lblName->Name = L"lblName";
            this->lblName->Size = System::Drawing::Size(35, 15);
            this->lblName->TabIndex = 5;
            this->lblName->Text = L"Имя:";

            //
            // lblPhone
            //
            this->lblPhone->AutoSize = true;
            this->lblPhone->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, FontStyle::Bold));
            this->lblPhone->Location = System::Drawing::Point(40, 83);
            this->lblPhone->Name = L"lblPhone";
            this->lblPhone->Size = System::Drawing::Size(59, 15);
            this->lblPhone->TabIndex = 6;
            this->lblPhone->Text = L"Телефон:";

            //
            // lblType
            //
            this->lblType->AutoSize = true;
            this->lblType->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, FontStyle::Bold));
            this->lblType->Location = System::Drawing::Point(40, 43);
            this->lblType->Name = L"lblType";
            this->lblType->Size = System::Drawing::Size(66, 15);
            this->lblType->TabIndex = 7;
            this->lblType->Text = L"Тип груза:";
            this->lblType->Visible = false;

            //
            // lblPrice
            //
            this->lblPrice->AutoSize = true;
            this->lblPrice->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, FontStyle::Bold));
            this->lblPrice->Location = System::Drawing::Point(40, 83);
            this->lblPrice->Name = L"lblPrice";
            this->lblPrice->Size = System::Drawing::Size(40, 15);
            this->lblPrice->TabIndex = 8;
            this->lblPrice->Text = L"Цена:";
            this->lblPrice->Visible = false;

            //
            // EditForm
            //
            this->AutoScaleDimensions = System::Drawing::SizeF(7, 17);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(250)), static_cast<System::Int32>(static_cast<System::Byte>(250)),
                static_cast<System::Int32>(static_cast<System::Byte>(250)));
            this->ClientSize = System::Drawing::Size(384, 241);
            this->Controls->Add(this->lblPrice);
            this->Controls->Add(this->lblType);
            this->Controls->Add(this->lblPhone);
            this->Controls->Add(this->lblName);
            this->Controls->Add(this->txtPrice);
            this->Controls->Add(this->Combotype);
            this->Controls->Add(this->txtPhone);
            this->Controls->Add(this->txtName);
            this->Controls->Add(this->btnSave);
            this->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F));
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->Name = L"EditForm";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
            this->Text = L"Редактирование";
            this->Load += gcnew System::EventHandler(this, &EditForm::EditForm_Load);
            this->ResumeLayout(false);
            this->PerformLayout();
        }
#pragma endregion

    private: System::Void btnSave_Click(System::Object^ sender, System::EventArgs^ e) {
        this->ActiveControl = nullptr;
        // Проверка режима
        if (mode == "Client") {
            // Проверяем имя и телефон
            if (String::IsNullOrWhiteSpace(txtName->Text)) {
                MessageBox::Show("Пожалуйста, введите имя клиента.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                txtName->Focus();
                return;
            }
            if (String::IsNullOrWhiteSpace(txtPhone->Text)) {
                MessageBox::Show("Пожалуйста, введите телефон клиента.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                txtPhone->Focus();
                return;
            }
        }
        else if (mode == "Tariff") {
            // Проверяем цену
            if (String::IsNullOrWhiteSpace(txtPrice->Text)) {
                MessageBox::Show("Пожалуйста, введите цену тарифа.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                txtPrice->Focus();
                return;
            }
            // Проверяем, что цена — число
            double price;
            if (!Double::TryParse(txtPrice->Text, price)) {
                MessageBox::Show("Цена тарифа должна быть числом.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                txtPrice->Focus();
                txtPrice->SelectAll();
                return;
            }
            if (price <= 0) {
                MessageBox::Show("Цена должна быть положительным числом.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                txtPrice->Focus();
                txtPrice->SelectAll();
                return;
            }
        }
        // Всё корректно — закрываем форму с OK
        this->DialogResult = System::Windows::Forms::DialogResult::OK;
        this->Close();
    }

    private: System::Void EditForm_Load(System::Object^ sender, System::EventArgs^ e) {
    }
    };
}