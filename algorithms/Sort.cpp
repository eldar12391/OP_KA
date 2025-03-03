#include <vector>
#include <algorithm>
#include <string>
#include "Room.h"
#include <sstream>
#include <iomanip>
#include <iostream>
#include <limits>
enum class SortOrder { Ascending, Descending }; // Добавляем enum для направления сортировки


// 1. Сортировка по типу комнаты (с направлением)
void sortByRoomType(std::vector<Room>& rooms, SortOrder order) {
    std::sort(rooms.begin(), rooms.end(), [order](const Room& a, const Room& b) {
        if (order == SortOrder::Ascending) {
            return a.getType() < b.getType();
        } else {
            return a.getType() > b.getType();
        }
    });
}

// 2. Сортировка по фамилии жильца (с направлением)
void sortByClientFullName(std::vector<Room>& rooms, SortOrder order) {
    std::sort(rooms.begin(), rooms.end(), [order](const Room& a, const Room& b) {
        if (a.getCurrClient() == nullptr && b.getCurrClient() == nullptr) return false;
        if (a.getCurrClient() == nullptr) return true;
        if (b.getCurrClient() == nullptr) return false;

        if (order == SortOrder::Ascending) {
            return a.getCurrClient()->fullName < b.getCurrClient()->fullName;
        } else {
            return a.getCurrClient()->fullName > b.getCurrClient()->fullName;
        }
    });
}


// Вспомогательная функция для преобразования даты в структуру tm
tm parseDate(const std::string& dateStr) {
    std::tm tm = {};
    std::istringstream ss(dateStr);
    ss >> std::get_time(&tm, "%d.%m.%Y");
    if (ss.fail()) {
        std::cerr << "Ошибка разбора даты: " << dateStr << std::endl;
        return {};
    }
    return tm;
}

// 3. Сортировка по дате заселения (с направлением)
void sortByCheckInDate(std::vector<Room>& rooms, SortOrder order) {
    std::sort(rooms.begin(), rooms.end(), [order](const Room& a, const Room& b) {
        if (a.getCurrClient() == nullptr && b.getCurrClient() == nullptr) return false;
        if (a.getCurrClient() == nullptr) return true;
        if (b.getCurrClient() == nullptr) return false;

        tm tmA = parseDate(a.getCurrClient()->checkInDate);
        tm tmB = parseDate(b.getCurrClient()->checkInDate);

        if (order == SortOrder::Ascending) {
            return mktime(&tmA) < mktime(&tmB);
        } else {
            return mktime(&tmA) > mktime(&tmB);
        }
    });
}

// 4. Сортировка по дате выезда (с направлением)
void sortByCheckOutDate(std::vector<Room>& rooms, SortOrder order) {
    std::sort(rooms.begin(), rooms.end(), [order](const Room& a, const Room& b) {
        if (a.getCurrClient() == nullptr && b.getCurrClient() == nullptr) return false;
        if (a.getCurrClient() == nullptr) return true;
        if (b.getCurrClient() == nullptr) return false;

        tm tmA = parseDate(a.getCurrClient()->checkOutDate);
        tm tmB = parseDate(b.getCurrClient()->checkOutDate);

        if (order == SortOrder::Ascending) {
            return mktime(&tmA) < mktime(&tmB);
        } else {
            return mktime(&tmA) > mktime(&tmB);
        }
    });
}

// 5. Сортировка по статусу комнаты (с направлением)
void sortByRoomStatus(std::vector<Room>& rooms, SortOrder order) {
    std::sort(rooms.begin(), rooms.end(), [order](const Room& a, const Room& b) {
        if (order == SortOrder::Ascending) {
            return a.getStatus() < b.getStatus();
        } else {
            return a.getStatus() > b.getStatus();
        }
    });
}

SortOrder getUserSortOrder() {
    int choice;
    while (true) {
        std::cout << "Выберите направление сортировки:\n";
        std::cout << "1. По возрастанию\n";
        std::cout << "2. По убыванию\n";
        std::cout << ">> ";
        std::cin >> choice;

        // Проверка ввода на корректность
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Некорректный ввод. Пожалуйста, введите 1 или 2.\n";
            continue;
        }

        if (choice == 1) {
            return SortOrder::Ascending;
        } else if (choice == 2) {
            return SortOrder::Descending;
        } else {
            std::cout << "Некорректный выбор. Пожалуйста, введите 1 или 2.\n";
        }
    }
}

void sortField(std::vector<Room>& rooms){
    std::cout << "Выберите поле для сортировки:\n";
    std::cout << "1. ФИО\n";
    std::cout << "2. Дата заселения\n";
    std::cout << "3. Дата выселения\n";
    std::cout << "4. Класс номера\n";
    std::cout << "5. Статус номера\n";

    int choice = 0;
    std::cout << ">> ";
    std::cin >> choice;

    SortOrder order = getUserSortOrder();

    switch(choice){
        case 1:
        {
            sortByClientFullName(rooms, order);
            break;
        }
        case 2:
        {
            sortByCheckInDate(rooms, order);
            break;
        }
        case 3:
        {
            sortByCheckOutDate(rooms, order);
            break;
        }
        case 4:
        {
            sortByRoomType(rooms, order);
            break;
        }
        case 5:
        {
            sortByRoomStatus(rooms, order);
            break;
        }
        default:
        {
            std::cout << "Неверно выбрано поле сортировки. Возвращение в меню.";
            return;
            break;
        }
    }
    

}