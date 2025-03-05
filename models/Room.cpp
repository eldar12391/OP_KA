#include "Room.h"
#include <limits>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>

std::string roomTypeToString(RoomType type) {
    switch (type) {
        case RoomType::Standard:   return "Standard";
        case RoomType::Superlor:  return "Superlor";
        case RoomType::Deluxe:     return "Deluxe";
        case RoomType::Suite:      return "Suite";
        case RoomType::Apartment:  return "Apartment";
        default:                  return "Unknown";
    }
}

RoomType stringToRoomType(const std::string& str) {
    if (str == "Standard")   return RoomType::Standard;
    if (str == "Superlor")  return RoomType::Superlor;
    if (str == "Deluxe")     return RoomType::Deluxe;
    if (str == "Suite")      return RoomType::Suite;
    if (str == "Apartment")  return RoomType::Apartment;
    return RoomType::Standard; // Default
}

std::string roomStatusToString(RoomStatus status) {
    switch (status) {
        case RoomStatus::Available: return "Available";
        case RoomStatus::Reserved:  return "Reserved";
        case RoomStatus::Occupied:  return "Occupied";
        default:                  return "Unknown";
    }
}

RoomStatus stringToRoomStatus(const std::string& str) {
    if (str == "Available") return RoomStatus::Available;
    if (str == "Reserved")  return RoomStatus::Reserved;
    if (str == "Occupied")  return RoomStatus::Occupied;
    return RoomStatus::Available; // Default
}


Room::Room() : number(0), price(0.0), type(RoomType::Standard), status(RoomStatus::Available), currClient(nullptr) {}  // Или любое другое значение по умолчанию
Room::Room(unsigned int num, int p, RoomType t) : number(num), price(p), type(t), status(RoomStatus::Available), currClient(nullptr){}

int Room::getNumber() const { return number; }
RoomType Room::getType() const { return type; }
RoomStatus Room::getStatus() const { return status; }
int Room::getPrice() const { return price; }
Client* Room::getCurrClient() const { return currClient; }

void Room::setStatus(RoomStatus newStatus){ status = newStatus; }
void Room::removeClient() { delete currClient; currClient = nullptr; status = RoomStatus::Available; }

void Room::assignClient(const Client& client) {
    if (currClient != nullptr) {
        delete currClient;
    }
    currClient = new Client(client);
    status = RoomStatus::Occupied;
    std::cout << "Заселён клиент " << client.fullName << " в комнату " << number << std::endl;
}

void Room::populateClient(const Client& client) {
    if (currClient != nullptr) {
        delete currClient;
    } 
    std::cout << "Введите ФИО: " << std::endl;
    std::cin >> getCurrClient()->fullName;
    
    std::cout << "Введите дату заселения: ";
    std::cin >> getCurrClient()->checkInDate;
    std::cout << std::endl;

    std::cout << "Введите дату выселения: ";
    std::cin >> getCurrClient()->checkOutDate;
    std::cout << std::endl;

    std::cout << "Введите размер скидки: ";
    std::cin >> getCurrClient()->discountAmount;
    std::cout << std::endl;

    std::cout << "Введите сумму доплаты: ";
    std::cin >> getCurrClient()->extraSum;
    std::cout << std::endl;
}

void Room::editClient() { 
    std::cout << "Выберите поле для редактирования: ";
    std::cout << "1. Дата выселения" << std::endl;
    std::cout << "2. Скидка" << std::endl;
    std::cout << "3. Доплата" << std::endl;
    std::cout << ">> ";

    int choice = 0;
    std::cin >> choice;

    switch(choice){
        case 1:
        {   std::cout << "Введите новое значание";
            std::cout << ">> ";
            std::cin >> getCurrClient()->checkOutDate;
            break;
        }
        case 2:
        {
            std::cout << "Введите новое значание";
            std::cout << ">> ";
            std::cin >> getCurrClient()->discountAmount;
            break;
        }
        case 3:
        {
            std::cout << "Введите новое значание";
            std::cout << ">> ";
            std::cin >> getCurrClient()->extraSum;
            break;
        }
        default:
        {
            std::cout << "Ошибка ввода.";
            break;
        }
    }
}

void Room::addClient(){
    if (currClient != nullptr) {
        std::cout << "Room already occupied. Cannot add a new client." << std::endl;
        return; //  Комната уже занята
    }

    currClient = new Client();

    std::cout << "Enter client full name: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищаем буфер ввода
        std::getline(std::cin, currClient->fullName); // Используем getline для чтения ФИО с пробелами

        std::cout << "Enter check-in date: ";
        std::cin >> currClient->checkInDate;

        std::cout << "Enter check-out date: ";
        std::cin >> currClient->checkOutDate;

        std::cout << "Enter discount amount: ";
        std::cin >> currClient->discountAmount;

        std::cout << "Enter extra sum: ";
        std::cin >> currClient->extraSum;

        setStatus(RoomStatus::Occupied);  //  Изменяем статус комнаты

}

std::string Room::getTypeToStr() const{
    RoomType type = getType();
        switch (type) {
            case RoomType::Standard:  return "Standard";
            case RoomType::Superlor:  return "Superior";
            case RoomType::Deluxe:    return "Deluxe";
            case RoomType::Suite:     return "Suite";
            case RoomType::Apartment: return "Apartment";
            default:                  return "Неизвестный класс номера";
        }
}

std::string Room::getStatusToStr() const {
    RoomStatus status = getStatus();
    switch (status) {
        case RoomStatus::Available: return "Свободна";
        case RoomStatus::Reserved:  return "Забронирована";
        case RoomStatus::Occupied:  return "Занята";
        default:                  return "Unknown Room Status";
    }
}

std::string Room::getCheckInDate() const{
    return currClient->checkInDate;
}

std::string Room::getCheckOutDate() const{
    return currClient->checkOutDate;
}

void Room::serializeToText(std::ofstream& os) const {
    os << number << ","
       << price << ","
       << roomTypeToString(type) << "," // Преобразуем enum в строку
       << roomStatusToString(status) << ","; // Преобразуем enum в строку

    // Сохраняем информацию о клиенте
    if (currClient != nullptr) {
        os << "true,"  // Индикатор наличия клиента
           << currClient->fullName << ","
           << currClient->checkInDate << ","
           << currClient->checkOutDate << ","
           << currClient->discountAmount << ","
           << currClient->extraSum;
    } else {
        os << "false"; // Индикатор отсутствия клиента
    }

    os << std::endl; // Разделитель для каждой комнаты
}

void Room::deserializeFromText(std::ifstream& is) {
    std::string line;
    if (std::getline(is, line)) {
        std::stringstream ss(line);
        std::string token;

        // Читаем данные комнаты
        std::getline(ss, token, ',');
        number = std::stoi(token);

        std::getline(ss, token, ',');
        price = std::stod(token);

        std::getline(ss, token, ',');
        type = stringToRoomType(token); // Преобразуем строку в enum

        std::getline(ss, token, ',');
        status = stringToRoomStatus(token); // Преобразуем строку в enum

        // Читаем данные о клиенте
        std::getline(ss, token, ',');
        bool hasClient = (token == "true");

        if (hasClient) {
            currClient = new Client();

            std::getline(ss, currClient->fullName, ',');
            std::getline(ss, currClient->checkInDate, ',');
            std::getline(ss, currClient->checkOutDate, ',');

            std::getline(ss, token, ',');
            currClient->discountAmount = std::stoi(token);

            std::getline(ss, token, ',');
            currClient->extraSum = std::stoi(token);
        } else {
            currClient = nullptr;
        }
    }
}


int daysBetween(const std::string& date1, const std::string& date2) {
    std::tm tm1 = {};
    std::tm tm2 = {};
    std::istringstream ss1(date1);
    std::istringstream ss2(date2);

    ss1 >> std::get_time(&tm1, "%Y-%m-%d");
    ss2 >> std::get_time(&tm2, "%Y-%m-%d");

    if (ss1.fail() || ss2.fail()) {
        return 0; // Или другое значение по умолчанию, указывающее на ошибку
    }

    std::time_t t1 = mktime(&tm1);
    std::time_t t2 = mktime(&tm2);

    if (t1 == -1 || t2 == -1) {
        return 0; // Или другое значение по умолчанию, указывающее на ошибку
    }

    return (t2 - t1) / (24 * 60 * 60);
}

int Room::getAmountPaid() const {
    int amount = daysBetween(getCheckInDate(), getCheckOutDate()) * price;
    return amount;
}