#pragma once

#include <iostream>
#include <vector>
#include <string>

// Класс для хранения информации о клиенте
class Client {
public:
    // Конструктор с инициализацией имени и телефона
    Client(const std::string& name, const std::string& phone)
        : name(name), phone(phone) {
    }

    // Геттеры для получения данных
    std::string getName() const { return name; }
    std::string getPhone() const { return phone; }

    // Метод для вывода информации о клиенте
    void displayInfo() const {
        std::cout << "Имя: " << name << ", Телефон: " << phone << std::endl;
    }

private:
    std::string name;   // Имя клиента
    std::string phone;  // Номер телефона клиента
};

// Класс для управления списком клиентов
class ClientManager {
public:
    // Добавление нового клиента в список
    void addClient(const std::string& name, const std::string& phone) {
        clients.push_back(Client(name, phone));
    }

    // Вывод информации о всех клиентах
    void displayAllClients() const {
        if (clients.empty()) {
            std::cout << "Список клиентов пуст." << std::endl;
            return;
        }
        std::cout << "=== Список клиентов ===" << std::endl;
        for (const auto& client : clients) {
            client.displayInfo();
        }
        std::cout << "======================" << std::endl;
    }

    // Получение количества клиентов
    int getClientCount() const {
        return clients.size();
    }

private:
    std::vector<Client> clients; // Вектор для хранения клиентов
};