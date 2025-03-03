#include "Hotel.h"
#include <iostream>

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
        {   room->assignClient();
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


void Hotel::generateRooms(int N) {
    int length = getRooms().size();
    for (int i = 0; i < N; ++i) {
        unsigned int number = length + i + 1;
        RoomType type = static_cast<RoomType>(i % 5);
        double price = 1000.0 + (static_cast<int>(type) * 500.0);
        rooms.emplace_back(number, price, type);
    }
}

void Hotel::loadFile(std::vector<Room> rms){
    rooms = rms;
}