#include <iostream>
#include <vector>
#include <limits> // Для numeric_limits
#include "Processing.h"
#include "Requests.h"
#include "Room.h"
#include "Client.h"
#include "Hotel.h"
void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


void requestHandler(Hotel hotel) {
    std::vector<Room> rooms = hotel.getRooms();
    std::cout << "Выберите запрос:\n";
    std::cout << "1. Список клиентов, проживающих в номерах класса (с указанием фамилии клиента, № номера, даты выезда).\n";
    std::cout << "2. Список клиентов, проживающих в гостинице больше, меньше или равно дней (с указанием фамилии клиента, № номера, даты заселения).\n";
    std::cout << "3. Список клиентов, проживающих в гостинице и заплативших за номер больше, меньше или равно руб.\n";
    std::cout << "4. Список клиентов, которые должны освободить номер в течение дней; подсчитать количество таких клиентов.\n";
    std::cout << "5. Каково максимальное (минимальное) число дней проживания в гостинице.\n";
    std::cout << "7. Сколько номеров в гостинице было забронировано заранее? Получить список этих номеров.\n";
    std::cout << "8. Получить список клиентов, которые при выезде из гостиницы должны доплатить за проживание.\n";
    std::cout << "0. Выход.\n";

    int choice = 0;
    std::cout << ">> ";
    std::cin >> choice;

    switch (choice) {
    case 1: {
        //Standard, Superlor, Deluxe, Suite, Apartment
        int roomTypeChoice;
        std::cout << "Выберите класс номера:\n";
        std::cout << "1. Standart\n";
        std::cout << "2. Superlor\n";
        std::cout << "3. Deluxe\n";
        std::cout << "4. Suite\n";
        std::cout << "5. Apartment\n";
        std::cout << ">> ";
        std::cin >> roomTypeChoice;

        RoomType type;
        switch (roomTypeChoice) {
        case 1: type = RoomType::Standard; break;
        case 2: type = RoomType::Superlor; break;
        case 3: type = RoomType::Deluxe; break;
        case 4: type = RoomType::Suite; break;
        case 5: type = RoomType::Apartment; break;
        default:
            std::cout << "Неверный выбор класса номера.\n";
            return;
        }

        std::vector<Room> clients = hotel.getClientsInRoomType(type);
        if (clients.empty()) {
            std::cout << "Нет клиентов, проживающих в номерах выбранного класса.\n";
        }
        else {
            clearConsole();
            printTable();
            printRooms(clients);
        }
        break;
    }
    case 2: {
        int days;
        int comparisonType;
        std::cout << "Выберите тип сравнения:\n";
        std::cout << "1. Больше\n";
        std::cout << "2. Меньше\n";
        std::cout << "3. Равно\n";
        std::cout << ">> ";
        std::cin >> comparisonType;

        std::cout << "Введите количество дней: ";
        std::cin >> days;

        std::vector<Room> clients;
        switch (comparisonType) {
        case 1: clients = hotel.getClientsStayingLongerThan(days); break;
        case 2: clients = hotel.getClientsStayingShorterThan(days); break;
        case 3: clients = hotel.getClientsStayingEqual(days); break;
        default:
            std::cout << "Неверный тип сравнения.\n";
            return;
        }

        if (clients.empty()) {
            std::cout << "Нет клиентов, удовлетворяющих условию.\n";
        }
        else {
            clearConsole();
            printTable();
            printRooms(clients);
        }
        break;
    }
    case 3: {
        int amount;
        int comparisonType;
        std::cout << "Выберите тип сравнения:\n";
        std::cout << "1. Больше\n";
        std::cout << "2. Меньше\n";
        std::cout << ">> ";
        std::cin >> comparisonType;

        std::cout << "Введите сумму: ";
        std::cin >> amount;

        std::vector<Room> clients;
        switch (comparisonType) {
        case 1: clients = hotel.getClientsPayingMoreThan(amount); break;
        case 2: clients = hotel.getClientsPayingLessThan(amount); break;
        default:
            std::cout << "Неверный тип сравнения.\n";
            return;
        }

        if (clients.empty()) {
            std::cout << "Нет клиентов, удовлетворяющих условию.\n";
        }
        else {
            clearConsole();
            printTable();
            printRooms(clients);
        }
        break;
    }
    case 4: {
        int days;
        std::cout << "Введите количество дней: ";
        std::cin >> days;

        std::vector<Room> clients = hotel.getClientsLeavingWithinDays(days);
        if (clients.empty()) {
            std::cout << "Нет клиентов, выезжающих в течение " << days << " дней.\n";
        }
        else {
            clearConsole();
            std::cout << "Клиенты, выезжающие в течение " << days << " дней:\n";
            printTable();
            printRooms(clients);
            std::cout << std::endl << "Количество клиентов: " << clients.size() << std::endl;
        }
        break;
    }
    case 5: {
        std::vector<std::pair<Room, int>> minMax = hotel.getMaxMinStay();
    
        if (minMax.empty()) {
            std::cout << "Нет данных о проживании.\n";
        } else {
            if (minMax.size() >= 2) {
                std::cout << "Минимальное время проживания:\n";
                printTable();
                std::vector<Room> minRooms = {minMax[0].first}; // Create a named copy
                printRooms(minRooms);
                std::cout << "Количество дней: " << minMax[0].second << std::endl;
    
                std::cout << "\nМаксимальное время проживания:\n";
                printTable();
                std::vector<Room> maxRooms = {minMax[1].first}; // Create a named copy
                printRooms(maxRooms);
                std::cout << "Количество дней: " << minMax[1].second << std::endl;
            } else if (minMax.size() == 1) {
                std::cout << "Минимальное и максимальное время проживания:\n";
                printTable();
                std::vector<Room> singleRooms = {minMax[0].first}; // Create a named copy
                printRooms(singleRooms);
                std::cout << "Количество дней: " << minMax[0].second << std::endl;
            } else {
                std::cout << "Недостаточно данных для определения минимального и максимального времени проживания.\n";
            }
        }
        break;
    }
    case 6: {
        std::vector<Room> reservedRooms = hotel.getReservedRoomNumbers();
        if (reservedRooms.empty()) {
            std::cout << "Нет забронированных номеров.\n";
        }
        else {
            std::cout << "Забронированные номера: " << reservedRooms.size() << std::endl;
            clearConsole();
            printTable();
            printRooms(reservedRooms);
        }
        break;
    }
    case 7: {
        std::vector<Room> clientsToPayExtra = hotel.getClientsNeedingToPayExtra();
        if (clientsToPayExtra.empty()) {
            std::cout << "Нет клиентов, которым нужно доплатить.\n";
        }
        else {
            std::cout << "Клиенты, которым нужно доплатить:\n";
            clearConsole();
            printTable();
            printRooms(clientsToPayExtra);
        }
        break;
    }
    case 0: {
        std::cout << "Выход из меню запросов.\n";
        break;
    }
    default: {
        std::cout << "Неверный выбор запроса. Возвращение в меню.\n";
        break;
    }
    }
}