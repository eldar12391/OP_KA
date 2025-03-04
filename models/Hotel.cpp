#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <iomanip> // Для std::setw
#include "Hotel.h"
#include "Room.h"

void Hotel::addRoom(const Room& room){
    rooms.push_back(room); 
}

Room* Hotel::findRoom(unsigned int number) {
    for(Room& room : rooms){
        if(room.getNumber() == number){
            return &room;
        }
    }
    return nullptr;
}

std::vector<Room>& Hotel::getRooms() {
    return rooms;
}

void Hotel::editRoom(int number){
    Room* room;
    room = findRoom(number);

    int choice = 0;
    std::cout << "Выберите поле для изменения: " << std::endl;
    std:: cout << "1. Добавить клиента" << std::endl;
    std::cout << "2. Отредактировать поля клиента" << std::endl;
    std:: cout << "3. Удалить клиента" << std::endl;
    std::cout << ">> ";
    std::cin >> choice;

    switch(choice){
        case 1:
        {   room->populateClient();
            break;
        }
        case 2:
        {   room->editClient();
            break;
        }
        case 3:
        {   room->removeClient();
            break;
        }
        default:
        {
            std::cout << "Ошибка ввода";
        }
    }

}


std::string generateRandomDate(int startYear, int endYear) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> yearDist(startYear, endYear);
    std::uniform_int_distribution<> monthDist(1, 12);
    std::uniform_int_distribution<> dayDist(1, 28); // Чтобы избежать проблем с февралем и другими месяцами

    int year = yearDist(gen);
    int month = monthDist(gen);
    int day = dayDist(gen);

    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << day << "."
       << std::setfill('0') << std::setw(2) << month << "."
       << std::setfill('0') << std::setw(4) << year;

    return ss.str();
}

// Вспомогательная функция для генерации случайного имени
std::string generateRandomName() {
    std::vector<std::string> names = {"Иван", "Артём", "Георгий", "Александр", "Глеб", "Мария", "Максим", "Дмитрий", "Анастасия", "Данил"};
    std::vector<std::string> lastNames = {"Павлов", "Анохин", "Литвинов", "Шилов", "Новиков", "Блинов", "Ларионов", "Спиридонов", "Васильев", "Романов"};
    std::vector<std::string> patronymics = {"Алексеевич", "Макаров", "Борисович", "Егоров", "Дмитриевич", "Николаев", "Владимирович", "Захаров"};

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> nameDist(0, names.size() - 1);
    std::uniform_int_distribution<> lastNameDist(0, lastNames.size() - 1);
    std::uniform_int_distribution<> patronymicsDist(0, patronymics.size() - 1);

    return lastNames[lastNameDist(gen)] + " " + names[nameDist(gen)] + " " + patronymics[patronymicsDist(gen)];
}

void Hotel::generateRooms(int N) {
    int length = getRooms().size();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> discountDist(0, 20); // Скидка от 0 до 20%
    std::uniform_int_distribution<> extraSumDist(0, 500); // Дополнительная сумма от 0 до 500

    for (int i = 0; i < N; ++i) {
        unsigned int number = length + i + 1;
        RoomType type = static_cast<RoomType>(i % 5);
        double price = 1000.0 + (static_cast<int>(type) * 500.0);
        rooms.emplace_back(number, price, type);

        // Создание и добавление клиента
        Client newClient;
        newClient.fullName = generateRandomName();
        newClient.checkInDate = generateRandomDate(2023, 2024); // Даты заезда в 2023-2024 годах
        newClient.checkOutDate = generateRandomDate(2024, 2025); // Даты выезда в 2024-2025 годах
        newClient.discountAmount = discountDist(gen);
        newClient.extraSum = extraSumDist(gen);

        //  Находим только что созданную комнату и присваиваем ей клиента
        rooms.back().assignClient(newClient);  //Предполагается, что assignClient теперь принимает объект Client напрямую.
    }
}

void Hotel::loadFile(std::vector<Room> rms){
    rooms = rms;
}


std::vector<Room> Hotel::getClientsStayingLongerThan(int days) const {
    std::vector<Room> result;
    for (const Room& room : rooms) {
        if (room.getCurrClient() != nullptr) {
            int stay = daysBetween(room.getCheckInDate(), room.getCheckOutDate());
            if (stay > days) {
                result.push_back(room);
            }
        }
    }
    return result;
}

std::vector<Room> Hotel::getClientsStayingShorterThan(int days) const {
    std::vector<Room> result;
    for (const Room& room : rooms) {
        if (room.getCurrClient() != nullptr) {
            int stay = daysBetween(room.getCheckInDate(), room.getCheckOutDate());
            if (stay < days) {
                result.push_back(room);
            }
        }
    }
    return result;
}

std::vector<Room> Hotel::getClientsStayingEqual(int days) const {
    std::vector<Room> result;
    for (const Room& room : rooms) {
        if (room.getCurrClient() != nullptr) {
            int stay = daysBetween(room.getCheckInDate(), room.getCheckOutDate());
            if (stay == days) {
                result.push_back(room);
            }
        }
    }
    return result;
}

std::vector<Room> Hotel::getClientsPayingMoreThan(int amount) const {
    std::vector<Room> result;
    for (const Room& room : rooms) {
        if (room.getCurrClient() != nullptr && room.getAmountPaid() > amount) {
            result.push_back(room);
        }
    }
    return result;
}

std::vector<Room> Hotel::getClientsPayingLessThan(int amount) const {
    std::vector<Room> result;
    for (const Room& room : rooms) {
        if (room.getCurrClient() != nullptr && room.getAmountPaid() > amount) {
            result.push_back(room);
        }
    }
    return result;
}

std::vector<Room> Hotel::getClientsLeavingWithinDays(int days) const {
    std::vector<Room> result;
    // Получаем текущую дату
    std::time_t now = time(0);
    std::tm* ltm = localtime(&now);
    std::stringstream ss;
    ss << std::put_time(ltm, "%Y-%m-%d");
    std::string currentDate = ss.str();

    for (const Room& room : rooms) {
        if (room.getCurrClient() != nullptr) {
            int daysUntilDeparture = daysBetween(currentDate, room.getCheckOutDate());
            if (daysUntilDeparture >= 0 && daysUntilDeparture <= days) { // Учитываем, что дата выезда может быть в прошлом
                result.push_back(room);
            }
        }
    }
    return result;
}

#include "Hotel.h"
#include <limits>
#include <algorithm>


std::vector<std::pair<Room, int>> Hotel::getMaxMinStay(){
    int maxStay = std::numeric_limits<int>::min();
    int minStay = std::numeric_limits<int>::max();
    Room* maxStayRoom = nullptr;
    Room* minStayRoom = nullptr;

    for (Room& room : rooms) {
        if (room.getCurrClient() != nullptr) {
            int stay = daysBetween(room.getCheckInDate(), room.getCheckOutDate());

            if (stay > maxStay) {
                maxStay = stay;
                maxStayRoom = &room;
            }

            if (stay < minStay) {
                minStay = stay;
                minStayRoom = &room;
            }
        }
    }

    std::vector<std::pair<Room, int>> result;

    // Проверяем, были ли найдены комнаты с минимальным и максимальным сроком проживания
    if (minStayRoom != nullptr) {
        result.push_back({*minStayRoom, minStay}); // Добавляем комнату с минимальным сроком
    }
    if (maxStayRoom != nullptr && maxStayRoom != minStayRoom) { // Проверяем, что комната с макс. сроком не равна комнате с мин. сроком
        result.push_back({*maxStayRoom, maxStay}); // Добавляем комнату с максимальным сроком
    }

    return result;
}

std::vector<Room> Hotel::getReservedRoomNumbers() const {
    std::vector<Room> result;
    for (const Room& room : rooms) {
        if (room.getStatus() == RoomStatus::Reserved) {
            result.push_back(room);
        }
    }
    return result;
}

std::vector<Room> Hotel::getClientsNeedingToPayExtra() const {
    std::vector<Room> result;
    for (const Room& room : rooms) {
        if (room.getCurrClient() != nullptr) {
            if (room.getCurrClient()->extraSum != 0) {
                result.push_back(room);
            }
        }
    }
    return result;
}

std::vector<Room> Hotel::getClientsInRoomType(RoomType type) const {
    std::vector<Room> result;
    for (const Room& room : rooms) {
        if (room.getType() == type && room.getCurrClient() != nullptr) {
            result.push_back(room);
        }
    }
    return result;
}
