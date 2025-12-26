#pragma once
#include "TransportCompany.h"
#include "EditForm.h"
#include "OrdersForm.h"

namespace Laba34 {
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    /// <summary>
    /// Сводка для MainForm
    /// </summary>
    public ref class MainForm : public System::Windows::Forms::Form
    {
    public:
        MainForm(TransportCompany^ c)
        {
            company = c;
            InitializeComponent();
            SetupUI();
        }

    protected:
        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        ~MainForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        TransportCompany^ company;
        System::Windows::Forms::DataGridView^ clientsGrid;
        System::Windows::Forms::DataGridView^ tariffsGrid;
        System::Windows::Forms::BindingSource^ clientsBindingSource;
        System::Windows::Forms::BindingSource^ tariffsBindingSource;
        System::Windows::Forms::Button^ btnAddClient;
        System::Windows::Forms::Button^ btnAddTariff;
        System::Windows::Forms::Button^ btnOpenOrders;
        System::Windows::Forms::Button^ btnDeleteClient;
        System::Windows::Forms::Button^ btnDeleteTariff;
        System::Windows::Forms::Button^ btnEditClient;
        System::Windows::Forms::Button^ btnEditTariff;
        System::Windows::Forms::Label^ label1;
        System::Windows::Forms::Label^ label2;
        System::Windows::Forms::Panel^ panel1;
        System::Windows::Forms::Panel^ panel2;
        System::ComponentModel::IContainer^ components;

    protected:
    private:
        void SetupUI()
        {
            // Настройка цветовой схемы
            this->BackColor = Color::FromArgb(240, 245, 249);

            // Настройка клиентской сетки
            clientsGrid->BackgroundColor = Color::White;
            clientsGrid->BorderStyle = BorderStyle::FixedSingle;
            clientsGrid->AlternatingRowsDefaultCellStyle->BackColor = Color::FromArgb(245, 249, 252);
            clientsGrid->DefaultCellStyle->Font = gcnew System::Drawing::Font("Segoe UI", 9);
            clientsGrid->ColumnHeadersDefaultCellStyle->Font = gcnew System::Drawing::Font("Segoe UI", 9, FontStyle::Bold);
            clientsGrid->ColumnHeadersDefaultCellStyle->BackColor = Color::FromArgb(248, 249, 250);
            clientsGrid->ColumnHeadersDefaultCellStyle->ForeColor = Color::FromArgb(33, 37, 41);

            // Настройка тарифной сетки
            tariffsGrid->BackgroundColor = Color::White;
            tariffsGrid->BorderStyle = BorderStyle::FixedSingle;
            tariffsGrid->AlternatingRowsDefaultCellStyle->BackColor = Color::FromArgb(245, 249, 252);
            tariffsGrid->DefaultCellStyle->Font = gcnew System::Drawing::Font("Segoe UI", 9);
            tariffsGrid->ColumnHeadersDefaultCellStyle->Font = gcnew System::Drawing::Font("Segoe UI", 9, FontStyle::Bold);
            tariffsGrid->ColumnHeadersDefaultCellStyle->BackColor = Color::FromArgb(248, 249, 250);
            tariffsGrid->ColumnHeadersDefaultCellStyle->ForeColor = Color::FromArgb(33, 37, 41);

            // Стилизация кнопок
            ApplyButtonStyle(btnAddClient, Color::FromArgb(76, 175, 80));       // Зеленый
            ApplyButtonStyle(btnDeleteClient, Color::FromArgb(244, 67, 54));    // Красный
            ApplyButtonStyle(btnEditClient, Color::FromArgb(33, 150, 243));     // Синий
            ApplyButtonStyle(btnAddTariff, Color::FromArgb(76, 175, 80));       // Зеленый
            ApplyButtonStyle(btnDeleteTariff, Color::FromArgb(244, 67, 54));    // Красный
            ApplyButtonStyle(btnEditTariff, Color::FromArgb(33, 150, 243));     // Синий
            ApplyButtonStyle(btnOpenOrders, Color::FromArgb(156, 39, 176));     // Фиолетовый

            // Настраиваем столбцы
            ConfigureDataGrids();
        }

        void ApplyButtonStyle(Button^ button, Color backColor)
        {
            button->BackColor = backColor;
            button->ForeColor = Color::White;
            button->FlatStyle = FlatStyle::Flat;
            button->FlatAppearance->BorderSize = 0;
            button->FlatAppearance->MouseOverBackColor = Color::FromArgb(
                Math::Min(backColor.R + 20, 255),
                Math::Min(backColor.G + 20, 255),
                Math::Min(backColor.B + 20, 255));
            button->Font = gcnew System::Drawing::Font("Segoe UI", 9, FontStyle::Bold);
            button->Cursor = Cursors::Hand;
            button->Padding = System::Windows::Forms::Padding(5);
        }

        void ConfigureDataGrids()
        {
            // Очищаем автоматически созданные столбцы
            clientsGrid->AutoGenerateColumns = false;
            tariffsGrid->AutoGenerateColumns = false;

            // Удаляем существующие столбцы
            clientsGrid->Columns->Clear();
            tariffsGrid->Columns->Clear();

            // Настраиваем столбцы для клиентов
            DataGridViewTextBoxColumn^ colName = gcnew DataGridViewTextBoxColumn();
            colName->HeaderText = "Имя клиента";
            colName->DataPropertyName = "Name";
            colName->Width = 170;
            colName->ReadOnly = true;
            clientsGrid->Columns->Add(colName);

            DataGridViewTextBoxColumn^ colPhone = gcnew DataGridViewTextBoxColumn();
            colPhone->HeaderText = "Телефон";
            colPhone->DataPropertyName = "Phone";
            colPhone->Width = 150;
            colPhone->ReadOnly = true;
            clientsGrid->Columns->Add(colPhone);

            // Настраиваем столбцы для тарифов
            DataGridViewTextBoxColumn^ colType = gcnew DataGridViewTextBoxColumn();
            colType->HeaderText = "Тип груза";
            colType->DataPropertyName = "TypeString";
            colType->Width = 150;
            colType->ReadOnly = true;
            tariffsGrid->Columns->Add(colType);

            DataGridViewTextBoxColumn^ colPrice = gcnew DataGridViewTextBoxColumn();
            colPrice->HeaderText = "Цена за единицу";
            colPrice->DataPropertyName = "PricePerUnit";
            colPrice->Width = 150;
            colPrice->ReadOnly = true;
            colPrice->DefaultCellStyle->Format = "N2";
            colPrice->DefaultCellStyle->Alignment = DataGridViewContentAlignment::MiddleRight;
            tariffsGrid->Columns->Add(colPrice);

            DataGridViewTextBoxColumn^ colId = gcnew DataGridViewTextBoxColumn();
            colId->HeaderText = "ID тарифа";
            colId->DataPropertyName = "Id";
            colId->Width = 80;
            colId->ReadOnly = true;
            colId->DefaultCellStyle->Alignment = DataGridViewContentAlignment::MiddleCenter;
            tariffsGrid->Columns->Add(colId);
        }

        void RefreshData()
        {
            try
            {
                if (company != nullptr)
                {
                    // Устанавливаем данные через BindingSource
                    clientsBindingSource->DataSource = company->GetClients();
                    tariffsBindingSource->DataSource = company->GetTariffs();

                    // Привязываем BindingSource к DataGridView
                    clientsGrid->DataSource = clientsBindingSource;
                    tariffsGrid->DataSource = tariffsBindingSource;

                    // Обновляем отображение
                    clientsGrid->Refresh();
                    tariffsGrid->Refresh();

                    // Обновляем заголовки с количеством записей
                    UpdatePanelTitles();
                }
            }
            catch (Exception^ ex)
            {
                MessageBox::Show("Ошибка при обновлении данных: " + ex->Message,
                    "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        void UpdatePanelTitles()
        {
            int clientCount = company->GetClients()->Count;
            int tariffCount = company->GetTariffs()->Count;

            label1->Text = String::Format("Клиенты компании ({0})", clientCount);
            label2->Text = String::Format("Тарифы компании ({0})", tariffCount);
        }

#pragma region Windows Form Designer generated code
        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        void InitializeComponent(void)
        {
            this->components = (gcnew System::ComponentModel::Container());
            this->clientsGrid = (gcnew System::Windows::Forms::DataGridView());
            this->clientsBindingSource = (gcnew System::Windows::Forms::BindingSource(this->components));
            this->tariffsGrid = (gcnew System::Windows::Forms::DataGridView());
            this->tariffsBindingSource = (gcnew System::Windows::Forms::BindingSource(this->components));
            this->btnAddClient = (gcnew System::Windows::Forms::Button());
            this->btnAddTariff = (gcnew System::Windows::Forms::Button());
            this->btnOpenOrders = (gcnew System::Windows::Forms::Button());
            this->btnDeleteClient = (gcnew System::Windows::Forms::Button());
            this->btnDeleteTariff = (gcnew System::Windows::Forms::Button());
            this->btnEditClient = (gcnew System::Windows::Forms::Button());
            this->btnEditTariff = (gcnew System::Windows::Forms::Button());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->panel1 = (gcnew System::Windows::Forms::Panel());
            this->panel2 = (gcnew System::Windows::Forms::Panel());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->clientsGrid))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->clientsBindingSource))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tariffsGrid))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tariffsBindingSource))->BeginInit();
            this->panel1->SuspendLayout();
            this->panel2->SuspendLayout();
            this->SuspendLayout();

            //
            // clientsGrid
            //
            this->clientsGrid->AllowUserToAddRows = false;
            this->clientsGrid->AllowUserToDeleteRows = false;
            this->clientsGrid->AllowUserToResizeRows = false;
            this->clientsGrid->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
            this->clientsGrid->BackgroundColor = System::Drawing::Color::White;
            this->clientsGrid->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
            this->clientsGrid->CellBorderStyle = System::Windows::Forms::DataGridViewCellBorderStyle::SingleHorizontal;
            this->clientsGrid->ColumnHeadersBorderStyle = System::Windows::Forms::DataGridViewHeaderBorderStyle::Single;
            this->clientsGrid->ColumnHeadersHeight = 35;
            this->clientsGrid->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
            this->clientsGrid->DataSource = this->clientsBindingSource;
            this->clientsGrid->Location = System::Drawing::Point(20, 50);
            this->clientsGrid->MultiSelect = false;
            this->clientsGrid->Name = L"clientsGrid";
            this->clientsGrid->ReadOnly = true;
            this->clientsGrid->RowHeadersVisible = false;
            this->clientsGrid->RowHeadersWidth = 51;
            this->clientsGrid->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
            this->clientsGrid->RowTemplate->Height = 30;
            this->clientsGrid->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
            this->clientsGrid->Size = System::Drawing::Size(360, 250);
            this->clientsGrid->TabIndex = 0;
            this->clientsGrid->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &MainForm::clientsGrid_CellContentClick);
            this->clientsGrid->DataError += gcnew System::Windows::Forms::DataGridViewDataErrorEventHandler(this, &MainForm::clientsGrid_DataError);
            this->clientsGrid->Enter += gcnew System::EventHandler(this, &MainForm::clientsGrid_Enter);

            //
            // clientsBindingSource
            //
            this->clientsBindingSource->AllowNew = false;
            this->clientsBindingSource->Sort = "";

            //
            // tariffsGrid
            //
            this->tariffsGrid->AllowUserToAddRows = false;
            this->tariffsGrid->AllowUserToDeleteRows = false;
            this->tariffsGrid->AllowUserToResizeRows = false;
            this->tariffsGrid->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
            this->tariffsGrid->BackgroundColor = System::Drawing::Color::White;
            this->tariffsGrid->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
            this->tariffsGrid->CellBorderStyle = System::Windows::Forms::DataGridViewCellBorderStyle::SingleHorizontal;
            this->tariffsGrid->ColumnHeadersBorderStyle = System::Windows::Forms::DataGridViewHeaderBorderStyle::Single;
            this->tariffsGrid->ColumnHeadersHeight = 35;
            this->tariffsGrid->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
            this->tariffsGrid->DataSource = this->tariffsBindingSource;
            this->tariffsGrid->Location = System::Drawing::Point(390, 50);
            this->tariffsGrid->MultiSelect = false;
            this->tariffsGrid->Name = L"tariffsGrid";
            this->tariffsGrid->ReadOnly = true;
            this->tariffsGrid->RowHeadersVisible = false;
            this->tariffsGrid->RowHeadersWidth = 51;
            this->tariffsGrid->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
            this->tariffsGrid->RowTemplate->Height = 30;
            this->tariffsGrid->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
            this->tariffsGrid->Size = System::Drawing::Size(360, 250);
            this->tariffsGrid->TabIndex = 1;
            this->tariffsGrid->DataError += gcnew System::Windows::Forms::DataGridViewDataErrorEventHandler(this, &MainForm::tariffsGrid_DataError);
            this->tariffsGrid->Enter += gcnew System::EventHandler(this, &MainForm::tariffsGrid_Enter);

            //
            // tariffsBindingSource
            //
            this->tariffsBindingSource->AllowNew = false;
            this->tariffsBindingSource->Sort = "";

            //
            // btnAddClient
            //
            this->btnAddClient->Location = System::Drawing::Point(20, 310);
            this->btnAddClient->Name = L"btnAddClient";
            this->btnAddClient->Size = System::Drawing::Size(85, 35);
            this->btnAddClient->TabIndex = 2;
            this->btnAddClient->Text = L"Добавить";
            this->btnAddClient->UseVisualStyleBackColor = true;
            this->btnAddClient->Click += gcnew System::EventHandler(this, &MainForm::btnAddClient_Click);

            //
            // btnAddTariff
            //
            this->btnAddTariff->Location = System::Drawing::Point(390, 310);
            this->btnAddTariff->Name = L"btnAddTariff";
            this->btnAddTariff->Size = System::Drawing::Size(85, 35);
            this->btnAddTariff->TabIndex = 3;
            this->btnAddTariff->Text = L"Добавить";
            this->btnAddTariff->UseVisualStyleBackColor = true;
            this->btnAddTariff->Click += gcnew System::EventHandler(this, &MainForm::btnAddTariff_Click);

            //
            // btnOpenOrders
            //
            this->btnOpenOrders->Location = System::Drawing::Point(20, 380);
            this->btnOpenOrders->Name = L"btnOpenOrders";
            this->btnOpenOrders->Size = System::Drawing::Size(730, 40);
            this->btnOpenOrders->TabIndex = 4;
            this->btnOpenOrders->Text = L"Управление заказами";
            this->btnOpenOrders->UseVisualStyleBackColor = true;
            this->btnOpenOrders->Click += gcnew System::EventHandler(this, &MainForm::btnOpenOrders_Click);

            //
            // btnDeleteClient
            //
            this->btnDeleteClient->Location = System::Drawing::Point(195, 310);
            this->btnDeleteClient->Margin = System::Windows::Forms::Padding(2);
            this->btnDeleteClient->Name = L"btnDeleteClient";
            this->btnDeleteClient->Size = System::Drawing::Size(85, 35);
            this->btnDeleteClient->TabIndex = 5;
            this->btnDeleteClient->Text = L"Удалить";
            this->btnDeleteClient->UseVisualStyleBackColor = true;
            this->btnDeleteClient->Click += gcnew System::EventHandler(this, &MainForm::btnDeleteClient_Click);

            //
            // btnDeleteTariff
            //
            this->btnDeleteTariff->Location = System::Drawing::Point(565, 310);
            this->btnDeleteTariff->Margin = System::Windows::Forms::Padding(2);
            this->btnDeleteTariff->Name = L"btnDeleteTariff";
            this->btnDeleteTariff->Size = System::Drawing::Size(85, 35);
            this->btnDeleteTariff->TabIndex = 6;
            this->btnDeleteTariff->Text = L"Удалить";
            this->btnDeleteTariff->UseVisualStyleBackColor = true;
            this->btnDeleteTariff->Click += gcnew System::EventHandler(this, &MainForm::btnDeleteTariff_Click);

            //
            // btnEditClient
            //
            this->btnEditClient->Location = System::Drawing::Point(295, 310);
            this->btnEditClient->Name = L"btnEditClient";
            this->btnEditClient->Size = System::Drawing::Size(85, 35);
            this->btnEditClient->TabIndex = 8;
            this->btnEditClient->Text = L"Редактировать";
            this->btnEditClient->UseVisualStyleBackColor = true;
            this->btnEditClient->Click += gcnew System::EventHandler(this, &MainForm::btnEditClient_Click);

            //
            // btnEditTariff
            //
            this->btnEditTariff->Location = System::Drawing::Point(665, 310);
            this->btnEditTariff->Name = L"btnEditTariff";
            this->btnEditTariff->Size = System::Drawing::Size(85, 35);
            this->btnEditTariff->TabIndex = 9;
            this->btnEditTariff->Text = L"Редактировать";
            this->btnEditTariff->UseVisualStyleBackColor = true;
            this->btnEditTariff->Click += gcnew System::EventHandler(this, &MainForm::btnEditTariff_Click);

            //
            // label1
            //
            this->label1->AutoSize = true;
            this->label1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11, FontStyle::Bold));
            this->label1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
                static_cast<System::Int32>(static_cast<System::Byte>(64)));
            this->label1->Location = System::Drawing::Point(10, 10);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(128, 20);
            this->label1->TabIndex = 10;
            this->label1->Text = L"Клиенты компании";

            //
            // label2
            //
            this->label2->AutoSize = true;
            this->label2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11, FontStyle::Bold));
            this->label2->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
                static_cast<System::Int32>(static_cast<System::Byte>(64)));
            this->label2->Location = System::Drawing::Point(10, 10);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(117, 20);
            this->label2->TabIndex = 11;
            this->label2->Text = L"Тарифы компании";

            //
            // panel1
            //
            this->panel1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
                static_cast<System::Int32>(static_cast<System::Byte>(192)));
            this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
            this->panel1->Controls->Add(this->label1);
            this->panel1->Location = System::Drawing::Point(20, 10);
            this->panel1->Name = L"panel1";
            this->panel1->Padding = System::Windows::Forms::Padding(5);
            this->panel1->Size = System::Drawing::Size(360, 40);
            this->panel1->TabIndex = 12;

            //
            // panel2
            //
            this->panel2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
                static_cast<System::Int32>(static_cast<System::Byte>(192)));
            this->panel2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
            this->panel2->Controls->Add(this->label2);
            this->panel2->Location = System::Drawing::Point(390, 10);
            this->panel2->Name = L"panel2";
            this->panel2->Padding = System::Windows::Forms::Padding(5);
            this->panel2->Size = System::Drawing::Size(360, 40);
            this->panel2->TabIndex = 13;

            //
            // MainForm
            //
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(240)), static_cast<System::Int32>(static_cast<System::Byte>(245)),
                static_cast<System::Int32>(static_cast<System::Byte>(249)));
            this->ClientSize = System::Drawing::Size(770, 435);
            this->Controls->Add(this->panel2);
            this->Controls->Add(this->panel1);
            this->Controls->Add(this->btnEditTariff);
            this->Controls->Add(this->btnEditClient);
            this->Controls->Add(this->btnDeleteTariff);
            this->Controls->Add(this->btnDeleteClient);
            this->Controls->Add(this->btnOpenOrders);
            this->Controls->Add(this->btnAddTariff);
            this->Controls->Add(this->btnAddClient);
            this->Controls->Add(this->tariffsGrid);
            this->Controls->Add(this->clientsGrid);
            this->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.25F));
            this->MinimumSize = System::Drawing::Size(786, 474);
            this->Name = L"MainForm";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"Транспортная компания - Главное окно";
            this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->clientsGrid))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->clientsBindingSource))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tariffsGrid))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tariffsBindingSource))->EndInit();
            this->panel1->ResumeLayout(false);
            this->panel1->PerformLayout();
            this->panel2->ResumeLayout(false);
            this->panel2->PerformLayout();
            this->ResumeLayout(false);
            this->PerformLayout();
        }
#pragma endregion

    private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
        RefreshData();
    }

    private: System::Void clientsGrid_DataError(System::Object^ sender, System::Windows::Forms::DataGridViewDataErrorEventArgs^ e) {
        e->ThrowException = false;
    }

    private: System::Void tariffsGrid_DataError(System::Object^ sender, System::Windows::Forms::DataGridViewDataErrorEventArgs^ e) {
        e->ThrowException = false;
    }

    private: System::Void clientsGrid_Enter(System::Object^ sender, System::EventArgs^ e) {
        tariffsGrid->ClearSelection();
    }

    private: System::Void tariffsGrid_Enter(System::Object^ sender, System::EventArgs^ e) {
        clientsGrid->ClearSelection();
    }

    private: System::Void btnAddClient_Click(System::Object^ sender, System::EventArgs^ e) {
        EditForm^ form = gcnew EditForm();
        form->SetMode("Client");
        if (form->ShowDialog() == System::Windows::Forms::DialogResult::OK)
        {
            Client^ c = gcnew Client(form->ClientName, form->ClientPhone);
            company->AddClient(c);
            RefreshData();
            MessageBox::Show("Клиент добавлен!", "Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }
    }

    private: System::Void btnAddTariff_Click(System::Object^ sender, System::EventArgs^ e) {
        EditForm^ form = gcnew EditForm();
        form->SetMode("Tariff");
        if (form->ShowDialog() == System::Windows::Forms::DialogResult::OK)
        {
            CargoType type;
            String^ t = form->TariffTypeString;
            if (t == "General") type = CargoType::General;
            else if (t == "Fragile") type = CargoType::Fragile;
            else if (t == "Hazardous") type = CargoType::Hazardous;
            else type = CargoType::Refrigerated;

            Tariff^ tariff = gcnew Tariff(type, form->TariffPrice);
            if (!company->AddTariff(tariff)) {
                MessageBox::Show("Тариф с таким типом уже существует!", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
            else {
                RefreshData();
                MessageBox::Show("Тариф добавлен!", "Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
        }
    }

    private: System::Void btnOpenOrders_Click(System::Object^ sender, System::EventArgs^ e) {
        if (company == nullptr) {
            MessageBox::Show("Ошибка: компания не инициализирована", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }
        OrdersForm^ ordersForm = gcnew OrdersForm(company);
        ordersForm->ShowDialog();
        // Обновляем данные после закрытия окна заказов
        RefreshData();
    }

    private: System::Void clientsGrid_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
        // Обработка клика по ячейке клиента
    }

    private: System::Void btnDeleteClient_Click(System::Object^ sender, System::EventArgs^ e) {
        if (clientsGrid->CurrentRow == nullptr || clientsGrid->CurrentRow->Index < 0) {
            MessageBox::Show("Выберите клиента для удаления", "Информация", MessageBoxButtons::OK, MessageBoxIcon::Information);
            return;
        }
        Client^ selected = (Client^)clientsGrid->CurrentRow->DataBoundItem;
        if (MessageBox::Show("Вы действительно хотите удалить клиента \"" + selected->Name + "\" и все его заказы?",
            "Подтверждение удаления", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes)
        {
            // Удаляем все заказы клиента
            auto orders = company->GetOrders();
            for (int i = orders->Count - 1; i >= 0; i--) {
                if (orders[i]->ClientData == selected) {
                    orders->RemoveAt(i);
                }
            }
            // Удаляем клиента
            company->RemoveClient(selected);
            RefreshData();
            // Обновляем окна заказов, если они открыты
            for each(Form ^ f in Application::OpenForms) {
                OrdersForm^ ordersForm = dynamic_cast<OrdersForm^>(f);
                if (ordersForm != nullptr) {
                    ordersForm->RefreshOrdersTable();
                }
            }
            MessageBox::Show("Клиент удален", "Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }
    }

    private: System::Void btnDeleteTariff_Click(System::Object^ sender, System::EventArgs^ e) {
        if (tariffsGrid->CurrentRow == nullptr || tariffsGrid->CurrentRow->Index < 0) {
            MessageBox::Show("Выберите тариф для удаления", "Информация", MessageBoxButtons::OK, MessageBoxIcon::Information);
            return;
        }
        Tariff^ selected = (Tariff^)tariffsGrid->CurrentRow->DataBoundItem;
        if (MessageBox::Show("Вы действительно хотите удалить тариф \"" + selected->TypeString + "\" и все связанные заказы?",
            "Подтверждение удаления", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes)
        {
            // Удаляем все заказы с этим тарифом
            auto orders = company->GetOrders();
            for (int i = orders->Count - 1; i >= 0; i--) {
                if (orders[i]->TariffData == selected) {
                    orders->RemoveAt(i);
                }
            }
            // Удаляем тариф
            company->RemoveTariff(selected);
            RefreshData();
            // Обновляем окна заказов
            for each(Form ^ f in Application::OpenForms) {
                OrdersForm^ ordersForm = dynamic_cast<OrdersForm^>(f);
                if (ordersForm != nullptr) {
                    ordersForm->RefreshOrdersTable();
                }
            }
            MessageBox::Show("Тариф удален", "Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }
    }

    private: System::Void btnEditClient_Click(System::Object^ sender, System::EventArgs^ e) {
        if (clientsGrid->CurrentRow == nullptr || clientsGrid->CurrentRow->Index < 0) {
            MessageBox::Show("Выберите клиента для редактирования", "Информация", MessageBoxButtons::OK, MessageBoxIcon::Information);
            return;
        }

        Client^ selectedClient = (Client^)clientsGrid->CurrentRow->DataBoundItem;
        EditForm^ form = gcnew EditForm();
        form->SetMode("Client");
        form->ClientName = selectedClient->Name;
        form->ClientPhone = selectedClient->Phone;

        if (form->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
            selectedClient->Name = form->ClientName;
            selectedClient->Phone = form->ClientPhone;
            RefreshData();
            MessageBox::Show("Данные клиента обновлены!", "Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }
    }

    private: System::Void btnEditTariff_Click(System::Object^ sender, System::EventArgs^ e) {
        if (tariffsGrid->CurrentRow == nullptr || tariffsGrid->CurrentRow->Index < 0) {
            MessageBox::Show("Выберите тариф для редактирования", "Информация", MessageBoxButtons::OK, MessageBoxIcon::Information);
            return;
        }

        Tariff^ selectedTariff = (Tariff^)tariffsGrid->CurrentRow->DataBoundItem;
        EditForm^ form = gcnew EditForm();
        form->SetMode("Tariff");
        switch (selectedTariff->Type) {
        case CargoType::General: form->TariffTypeString = "General"; break;
        case CargoType::Fragile: form->TariffTypeString = "Fragile"; break;
        case CargoType::Hazardous: form->TariffTypeString = "Hazardous"; break;
        case CargoType::Refrigerated: form->TariffTypeString = "Refrigerated"; break;
        }
        form->TariffPrice = selectedTariff->PricePerUnit;

        if (form->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
            CargoType newType;
            String^ t = form->TariffTypeString;
            if (t == "General") newType = CargoType::General;
            else if (t == "Fragile") newType = CargoType::Fragile;
            else if (t == "Hazardous") newType = CargoType::Hazardous;
            else newType = CargoType::Refrigerated;

            // Проверяем уникальность типа
            for each(Tariff ^ tr in company->GetTariffs()) {
                if (tr != selectedTariff && tr->Type == newType) {
                    MessageBox::Show("Тариф с таким типом уже существует!", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                    return;
                }
            }

            selectedTariff->Type = newType;
            selectedTariff->PricePerUnit = form->TariffPrice;
            RefreshData();
            MessageBox::Show("Данные тарифа обновлены!", "Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }
    }
    };
}