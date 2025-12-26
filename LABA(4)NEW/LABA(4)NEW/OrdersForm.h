#pragma once
#include "TransportCompany.h"
#include "Client.h"
#include "Tariff.h"
#include "Order.h"

namespace Laba34 {
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Runtime::InteropServices;

    /// <summary>
    /// Сводка для OrdersForm
    /// </summary>
    public ref class OrdersForm : public System::Windows::Forms::Form
    {
    private:
        TransportCompany^ company;
        System::Windows::Forms::Button^ exportOrders;
        System::Windows::Forms::Button^ importOrders;
        BindingSource^ ordersBinding;
        System::Data::DataTable^ ordersTable;

    public:
        OrdersForm(TransportCompany^ c)
        {
            InitializeComponent();
            company = c;
            SetupUI();
            ordersGrid->AutoGenerateColumns = false;
            DataGridViewTextBoxColumn^ colClient = gcnew DataGridViewTextBoxColumn();
            colClient->Name = "ClientName";
            colClient->HeaderText = "Клиент";
            colClient->DataPropertyName = "ClientName";
            colClient->SortMode = DataGridViewColumnSortMode::Automatic;
            ordersGrid->Columns->Add(colClient);
            DataGridViewTextBoxColumn^ colPhone = gcnew DataGridViewTextBoxColumn();
            colPhone->Name = "ClientPhone";
            colPhone->HeaderText = "Телефон";
            colPhone->DataPropertyName = "ClientPhone";
            colPhone->SortMode = DataGridViewColumnSortMode::Automatic;
            ordersGrid->Columns->Add(colPhone);
            DataGridViewTextBoxColumn^ colTariff = gcnew DataGridViewTextBoxColumn();
            colTariff->Name = "TariffType";
            colTariff->HeaderText = "Тариф";
            colTariff->DataPropertyName = "TariffType";
            colTariff->SortMode = DataGridViewColumnSortMode::Automatic;
            ordersGrid->Columns->Add(colTariff);
            DataGridViewTextBoxColumn^ colVolume = gcnew DataGridViewTextBoxColumn();
            colVolume->Name = "Volume";
            colVolume->HeaderText = "Объём (м³)";
            colVolume->DataPropertyName = "Volume";
            colVolume->SortMode = DataGridViewColumnSortMode::Automatic;
            ordersGrid->Columns->Add(colVolume);
            DataGridViewTextBoxColumn^ colTotal = gcnew DataGridViewTextBoxColumn();
            colTotal->Name = "TotalCost";
            colTotal->HeaderText = "Сумма (руб.)";
            colTotal->DataPropertyName = "TotalCost";
            colTotal->DefaultCellStyle->Format = "F2";
            colTotal->SortMode = DataGridViewColumnSortMode::Automatic;
            ordersGrid->Columns->Add(colTotal);
            // Заполняем ComboBox клиентами
            comboClients->DataSource = company->GetClients();
            comboClients->DisplayMember = "Name";
            // Заполняем ComboBox тарифами
            comboTariffs->DataSource = company->GetTariffs();
            comboTariffs->DisplayMember = "TypeString";
            // Создаем DataTable для заказов
            ordersTable = gcnew System::Data::DataTable("Orders");
            // Колонки
            ordersTable->Columns->Add("ClientName", String::typeid);
            ordersTable->Columns->Add("ClientPhone", String::typeid);
            ordersTable->Columns->Add("TariffType", String::typeid);
            ordersTable->Columns->Add("Volume", Double::typeid);
            ordersTable->Columns->Add("TotalCost", Double::typeid);
            // Колонка для хранения самого объекта Order
            ordersTable->Columns->Add("OrderObject", Order::typeid);
            // Заполняем таблицу заказами
            RefreshOrdersTable();
        }

    protected:
        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        ~OrdersForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        void SetupUI()
        {
            this->BackColor = Color::FromArgb(240, 245, 249);
            // Настройка стилей кнопок
            ApplyButtonStyle(btnAddOrder, Color::FromArgb(76, 175, 80));
            ApplyButtonStyle(btnDeleteOrder, Color::FromArgb(244, 67, 54));
            ApplyButtonStyle(exportOrders, Color::FromArgb(33, 150, 243));
            ApplyButtonStyle(importOrders, Color::FromArgb(255, 152, 0));
            // Настройка DataGridView
            ordersGrid->BackgroundColor = Color::White;
            ordersGrid->BorderStyle = BorderStyle::FixedSingle;
            ordersGrid->AlternatingRowsDefaultCellStyle->BackColor = Color::FromArgb(245, 249, 252);
            // Настройка заголовков
            ordersGrid->ColumnHeadersDefaultCellStyle->BackColor = Color::FromArgb(33, 150, 243);
            ordersGrid->ColumnHeadersDefaultCellStyle->ForeColor = Color::White;
            ordersGrid->ColumnHeadersDefaultCellStyle->Font = gcnew System::Drawing::Font("Segoe UI", 9, FontStyle::Bold);
            // Настройка панели ввода
            lblClient->Font = gcnew System::Drawing::Font("Segoe UI", 9, FontStyle::Bold);
            lblTariff->Font = gcnew System::Drawing::Font("Segoe UI", 9, FontStyle::Bold);
            lblVolume->Font = gcnew System::Drawing::Font("Segoe UI", 9, FontStyle::Bold);
        }

        void ApplyButtonStyle(Button^ button, Color backColor)
        {
            button->BackColor = backColor;
            button->ForeColor = Color::White;
            button->FlatStyle = FlatStyle::Flat;
            button->FlatAppearance->BorderSize = 0;
            button->Font = gcnew System::Drawing::Font("Segoe UI", 9, FontStyle::Bold);
            button->Cursor = Cursors::Hand;
        }

    private:
        System::Windows::Forms::DataGridView^ ordersGrid;
        System::Windows::Forms::ComboBox^ comboClients;
        System::Windows::Forms::Label^ lblClient;
        System::Windows::Forms::ComboBox^ comboTariffs;
        System::Windows::Forms::Label^ lblTariff;
        System::Windows::Forms::TextBox^ txtVolume;
        System::Windows::Forms::Label^ lblVolume;
        System::Windows::Forms::Button^ btnAddOrder;
        System::Windows::Forms::Button^ btnDeleteOrder;
        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        void InitializeComponent(void)
        {
            this->ordersGrid = (gcnew System::Windows::Forms::DataGridView());
            this->comboClients = (gcnew System::Windows::Forms::ComboBox());
            this->lblClient = (gcnew System::Windows::Forms::Label());
            this->comboTariffs = (gcnew System::Windows::Forms::ComboBox());
            this->lblTariff = (gcnew System::Windows::Forms::Label());
            this->txtVolume = (gcnew System::Windows::Forms::TextBox());
            this->lblVolume = (gcnew System::Windows::Forms::Label());
            this->btnAddOrder = (gcnew System::Windows::Forms::Button());
            this->btnDeleteOrder = (gcnew System::Windows::Forms::Button());
            this->exportOrders = (gcnew System::Windows::Forms::Button());
            this->importOrders = (gcnew System::Windows::Forms::Button());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ordersGrid))->BeginInit();
            this->SuspendLayout();

            //
            // ordersGrid
            //
            this->ordersGrid->AllowUserToAddRows = false;
            this->ordersGrid->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
            this->ordersGrid->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->ordersGrid->Location = System::Drawing::Point(12, 12);
            this->ordersGrid->Name = L"ordersGrid";
            this->ordersGrid->ReadOnly = true;
            this->ordersGrid->RowHeadersWidth = 51;
            this->ordersGrid->Size = System::Drawing::Size(750, 250);
            this->ordersGrid->TabIndex = 0;
            this->ordersGrid->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &OrdersForm::ordersGrid_CellClick);

            //
            // comboClients
            //
            this->comboClients->FormattingEnabled = true;
            this->comboClients->Location = System::Drawing::Point(80, 280);
            this->comboClients->Name = L"comboClients";
            this->comboClients->Size = System::Drawing::Size(180, 25);
            this->comboClients->TabIndex = 1;

            //
            // lblClient
            //
            this->lblClient->AutoSize = true;
            this->lblClient->Location = System::Drawing::Point(20, 283);
            this->lblClient->Name = L"lblClient";
            this->lblClient->Size = System::Drawing::Size(48, 17);
            this->lblClient->TabIndex = 2;
            this->lblClient->Text = L"Клиент:";

            //
            // comboTariffs
            //
            this->comboTariffs->FormattingEnabled = true;
            this->comboTariffs->Location = System::Drawing::Point(80, 320);
            this->comboTariffs->Name = L"comboTariffs";
            this->comboTariffs->Size = System::Drawing::Size(180, 25);
            this->comboTariffs->TabIndex = 3;

            //
            // lblTariff
            //
            this->lblTariff->AutoSize = true;
            this->lblTariff->Location = System::Drawing::Point(20, 323);
            this->lblTariff->Name = L"lblTariff";
            this->lblTariff->Size = System::Drawing::Size(45, 17);
            this->lblTariff->TabIndex = 4;
            this->lblTariff->Text = L"Тариф:";

            //
            // txtVolume
            //
            this->txtVolume->Location = System::Drawing::Point(80, 360);
            this->txtVolume->Name = L"txtVolume";
            this->txtVolume->Size = System::Drawing::Size(100, 25);
            this->txtVolume->TabIndex = 5;

            //
            // lblVolume
            //
            this->lblVolume->AutoSize = true;
            this->lblVolume->Location = System::Drawing::Point(20, 363);
            this->lblVolume->Name = L"lblVolume";
            this->lblVolume->Size = System::Drawing::Size(55, 17);
            this->lblVolume->TabIndex = 6;
            this->lblVolume->Text = L"Объём:";

            //
            // btnAddOrder
            //
            this->btnAddOrder->Location = System::Drawing::Point(300, 300);
            this->btnAddOrder->Name = L"btnAddOrder";
            this->btnAddOrder->Size = System::Drawing::Size(120, 35);
            this->btnAddOrder->TabIndex = 7;
            this->btnAddOrder->Text = L"Добавить заказ";
            this->btnAddOrder->UseVisualStyleBackColor = true;
            this->btnAddOrder->Click += gcnew System::EventHandler(this, &OrdersForm::btnAddOrder_Click);

            //
            // btnDeleteOrder
            //
            this->btnDeleteOrder->Location = System::Drawing::Point(440, 300);
            this->btnDeleteOrder->Margin = System::Windows::Forms::Padding(2);
            this->btnDeleteOrder->Name = L"btnDeleteOrder";
            this->btnDeleteOrder->Size = System::Drawing::Size(120, 35);
            this->btnDeleteOrder->TabIndex = 8;
            this->btnDeleteOrder->Text = L"Удалить заказ";
            this->btnDeleteOrder->UseVisualStyleBackColor = true;
            this->btnDeleteOrder->Click += gcnew System::EventHandler(this, &OrdersForm::btnDeleteOrder_Click);

            //
            // exportOrders
            //
            this->exportOrders->Location = System::Drawing::Point(300, 350);
            this->exportOrders->Name = L"exportOrders";
            this->exportOrders->Size = System::Drawing::Size(120, 35);
            this->exportOrders->TabIndex = 9;
            this->exportOrders->Text = L"Выгрузить заказы";
            this->exportOrders->UseVisualStyleBackColor = true;
            this->exportOrders->Click += gcnew System::EventHandler(this, &OrdersForm::exportOrders_Click);

            //
            // importOrders
            //
            this->importOrders->Location = System::Drawing::Point(440, 350);
            this->importOrders->Name = L"importOrders";
            this->importOrders->Size = System::Drawing::Size(120, 35);
            this->importOrders->TabIndex = 10;
            this->importOrders->Text = L"Загрузить заказы";
            this->importOrders->UseVisualStyleBackColor = true;
            this->importOrders->Click += gcnew System::EventHandler(this, &OrdersForm::importOrders_Click);

            //
            // OrdersForm
            //
            this->AutoScaleDimensions = System::Drawing::SizeF(7, 17);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(240)), static_cast<System::Int32>(static_cast<System::Byte>(245)),
                static_cast<System::Int32>(static_cast<System::Byte>(249)));
            this->ClientSize = System::Drawing::Size(784, 411);
            this->Controls->Add(this->importOrders);
            this->Controls->Add(this->exportOrders);
            this->Controls->Add(this->btnDeleteOrder);
            this->Controls->Add(this->btnAddOrder);
            this->Controls->Add(this->lblVolume);
            this->Controls->Add(this->txtVolume);
            this->Controls->Add(this->lblTariff);
            this->Controls->Add(this->comboTariffs);
            this->Controls->Add(this->lblClient);
            this->Controls->Add(this->comboClients);
            this->Controls->Add(this->ordersGrid);
            this->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F));
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->Name = L"OrdersForm";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
            this->Text = L"Управление заказами";
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ordersGrid))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();
        }
#pragma endregion

    private: System::Void lblClient_Click(System::Object^ sender, System::EventArgs^ e) {
    }

    private: System::Void btnAddOrder_Click(System::Object^ sender, System::EventArgs^ e) {
        // Проверка, выбран ли клиент
        if (comboClients->SelectedItem == nullptr) {
            MessageBox::Show("Пожалуйста, выберите клиента.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            comboClients->Focus();
            return;
        }
        // Проверка, выбран ли тариф
        if (comboTariffs->SelectedItem == nullptr) {
            MessageBox::Show("Пожалуйста, выберите тариф.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            comboTariffs->Focus();
            return;
        }
        // Проверка ввода объёма
        if (String::IsNullOrWhiteSpace(txtVolume->Text)) {
            MessageBox::Show("Пожалуйста, введите объём заказа.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            txtVolume->Focus();
            return;
        }
        // Попытка конвертации в число
        double volume;
        if (!Double::TryParse(txtVolume->Text, volume)) {
            MessageBox::Show("Объём заказа должен быть числом.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            txtVolume->Focus();
            txtVolume->SelectAll();
            return;
        }
        if (volume <= 0) {
            MessageBox::Show("Объём должен быть положительным числом.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            txtVolume->Focus();
            txtVolume->SelectAll();
            return;
        }
        // Создание заказа
        Client^ client = (Client^)comboClients->SelectedItem;
        Tariff^ tariff = (Tariff^)comboTariffs->SelectedItem;
        company->CreateOrder(client, tariff, volume);
        // Обновление таблицы
        RefreshOrdersTable();
        // Очистка полей ввода
        txtVolume->Clear();
        MessageBox::Show("Заказ успешно добавлен!", "Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
    }

    public: void RefreshOrdersTable() {
        // Очищаем старые строки
        ordersTable->Rows->Clear();
        // Добавляем все текущие заказы из компании
        for each (Order ^ order in company->GetOrders()) {
            ordersTable->Rows->Add(
                order->ClientName,
                order->ClientPhone,
                order->TariffType,
                order->Volume,
                order->TotalCost,
                order   // Храним сам объект заказа
            );
        }
        // Обновляем привязку
        ordersGrid->DataSource = ordersTable;
        // Обновляем Combobox
        comboClients->DataSource = nullptr;
        comboClients->DataSource = company->GetClients();
        comboClients->DisplayMember = "Name";
        comboTariffs->DataSource = nullptr;
        comboTariffs->DataSource = company->GetTariffs();
        comboTariffs->DisplayMember = "TypeString";
    }

    private: System::Void btnDeleteOrder_Click(System::Object^ sender, System::EventArgs^ e) {
        if (ordersGrid->CurrentRow == nullptr || ordersGrid->CurrentRow->Index < 0) {
            MessageBox::Show("Пожалуйста, выберите заказ для удаления.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }
        System::Data::DataRowView^ rowView = dynamic_cast<System::Data::DataRowView^>(ordersGrid->CurrentRow->DataBoundItem);
        if (rowView == nullptr) {
            MessageBox::Show("Не удалось получить данные выбранного заказа.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }
        Order^ order = (Order^)rowView["OrderObject"];
        if (MessageBox::Show("Вы действительно хотите удалить выбранный заказ?",
            "Подтверждение удаления", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes)
        {
            company->RemoveOrder(order);
            RefreshOrdersTable();
            MessageBox::Show("Заказ удален", "Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }
    }

    private: System::Void ordersGrid_CellClick(System::Object^ sender,
        System::Windows::Forms::DataGridViewCellEventArgs^ e)
    {
        if (e->RowIndex < 0) return; // Нажали на заголовок — игнор
    }

    private:
        Client^ GetOrCreateClient(String^ name, String^ phone)
        {
            for each (Client ^ c in company->GetClients())
                if (c->Name == name)
                    return c;
            // Если клиента нет — создаём
            Client^ newClient = gcnew Client(name, phone);
            company->AddClient(newClient);
            return newClient;
        }

        Tariff^ GetOrCreateTariff(String^ typeStr, double price)
        {
            for each (Tariff ^ t in company->GetTariffs())
                if (t->TypeString == typeStr)
                    return t;
            // Если тарифа нет — создаём
            CargoType type;
            if (typeStr == "General") type = CargoType::General;
            else if (typeStr == "Fragile") type = CargoType::Fragile;
            else if (typeStr == "Hazardous") type = CargoType::Hazardous;
            else type = CargoType::Refrigerated;
            Tariff^ newTariff = gcnew Tariff(type, price);
            company->AddTariff(newTariff);
            return newTariff;
        }

    private: System::Void exportOrders_Click(System::Object^ sender, System::EventArgs^ e) {
        SaveFileDialog^ saveDialog = gcnew SaveFileDialog();
        saveDialog->Filter = "CSV файлы (*.csv)|*.csv";
        saveDialog->FileName = "Заказы.csv";
        saveDialog->Title = "Экспорт заказов";
        if (saveDialog->ShowDialog() != System::Windows::Forms::DialogResult::OK)
            return;
        try {
            System::IO::StreamWriter^ writer = gcnew System::IO::StreamWriter(saveDialog->FileName, false, System::Text::Encoding::UTF8);
            // Записываем заголовки
            writer->WriteLine("Клиент;Телефон;Тариф;Объем;Сумма");
            // Записываем данные
            for each (Order ^ order in company->GetOrders()) {
                writer->WriteLine("{0};{1};{2};{3};{4:F2}",
                    EscapeCSV(order->ClientName),
                    EscapeCSV(order->ClientPhone),
                    EscapeCSV(order->TariffType),
                    order->Volume,
                    order->TotalCost);
            }
            writer->Close();
            MessageBox::Show("Заказы успешно экспортированы в файл:\n" + saveDialog->FileName,
                "Экспорт завершен", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }
        catch (Exception^ ex) {
            MessageBox::Show("Ошибка при экспорте в CSV: " + ex->Message,
                "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    private: String^ EscapeCSV(String^ value)
    {
        if (String::IsNullOrEmpty(value)) return "";
        // Если строка содержит разделители или кавычки, обрамляем её кавычками
        if (value->Contains(";") || value->Contains("\"") || value->Contains("\n") || value->Contains("\r"))
        {
            return "\"" + value->Replace("\"", "\"\"") + "\"";
        }
        return value;
    }

    private: System::Void importOrders_Click(System::Object^ sender, System::EventArgs^ e) {
        OpenFileDialog^ openDialog = gcnew OpenFileDialog();
        openDialog->Filter = "CSV файлы (*.csv)|*.csv";
        openDialog->Title = "Импорт заказов";
        if (openDialog->ShowDialog() != System::Windows::Forms::DialogResult::OK)
            return;
        try {
            array<String^>^ lines = System::IO::File::ReadAllLines(openDialog->FileName, System::Text::Encoding::UTF8);
            if (lines->Length < 2) {
                MessageBox::Show("CSV файл пуст или содержит только заголовок.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }
            // Пропускаем заголовок
            int importedCount = 0;
            int skippedCount = 0;
            for (int i = 1; i < lines->Length; i++) {
                String^ line = lines[i]->Trim();
                if (line->Length == 0) continue;
                try {
                    array<String^>^ parts = line->Split(';');
                    if (parts->Length < 5) {
                        skippedCount++;
                        continue;
                    }
                    String^ clientName = parts[0]->Trim('\"');
                    String^ clientPhone = parts[1]->Trim('\"');
                    String^ tariffType = parts[2]->Trim('\"');
                    double volume;
                    double totalCost;
                    if (!Double::TryParse(parts[3], volume) || !Double::TryParse(parts[4], totalCost)) {
                        skippedCount++;
                        continue;
                    }
                    if (volume <= 0 || totalCost <= 0) {
                        skippedCount++;
                        continue;
                    }
                    double pricePerUnit = totalCost / volume;
                    // Находим или создаем клиента
                    Client^ client = GetOrCreateClient(clientName, clientPhone);
                    // Находим или создаем тариф
                    Tariff^ tariff = GetOrCreateTariff(tariffType, pricePerUnit);
                    // Создаем заказ
                    company->CreateOrder(client, tariff, volume);
                    importedCount++;
                }
                catch (Exception^) {
                    skippedCount++;
                }
            }
            // Обновляем таблицу
            RefreshOrdersTable();
            MessageBox::Show(String::Format("Импорт завершен.\nУспешно импортировано: {0}\nПропущено: {1}",
                importedCount, skippedCount), "Импорт завершен",
                MessageBoxButtons::OK, MessageBoxIcon::Information);
        }
        catch (Exception^ ex) {
            MessageBox::Show("Ошибка при загрузке CSV: " + ex->Message,
                "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }
    };
}