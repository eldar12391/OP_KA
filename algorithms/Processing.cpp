#include <iostream>
#include <vector>
#include "Screen.h"
#include <iomanip>
#include <limits>
#include "Processing.h"
#include "Hotel.h"
#include <termios.h>
#include <unistd.h>

void waitForAnyKey() {
    std::cout << "Введите '0' для выхода в меню." << std::endl;

    char garbage;
    std::cin >> garbage;
  }

  
void printTable() {
    std::cout << "╔════════════════════╦════════════════════════════════════════╦════════════════════╦═════════════════╦═════════════════╦═══════════╦═══════════╦═══════════╦═══════════╗" << std::endl;
    std::cout << "║"; printAligned("№ Комнаты", 20); std::cout << "║";
    printAligned("Клиент", 40); std::cout << "║";
    printAligned("Дата заселения", 20); std::cout << "║";
    printAligned("Дата выезда", 17); std::cout << "║";
    printAligned("Класс номера", 17); std::cout << "║";
    printAligned("Оплата", 11); std::cout << "║";
    printAligned("Скидки", 11); std::cout << "║";
    printAligned("Бронь", 11); std::cout << "║";
    printAligned("Доплаты", 11); std::cout << "║"; std::cout << std::endl;
    std::cout << "╠════════════════════╬════════════════════════════════════════╬════════════════════╬═════════════════╬═════════════════╬═══════════╬═══════════╬═══════════╬═══════════╣" << std::endl;

}

std::string cutStr(const std::string str, int start, int end){
    if (str.empty()){
        return "";
    }
    if(utf8_length(str) < end){
        end = utf8_length(str) - 1;
    }
    start = start * 2;
    end = end * 2;
    int len = end - start + 1;

    std::string newStr;
    for(int i = 0; i < len; i+=2){
        newStr[i] = str[start + i];
        newStr[i+1] = str[start + i + 1];
    }
    return newStr;
}

void printAligned(std::string str, size_t width) {
    size_t len = utf8_length(str);
    if (len > width) {
        std::string truncated;
        truncated = cutStr(str, 0, width - 1);
        std::cout << truncated;
    } else {
        std::cout << str;
        for (size_t i = 0; i < width - len; i++) {
            std::cout << ' ';
        }
    }
}


size_t utf8_length(const std::string str) {
    size_t length = 0;
    for (size_t i = 0; str[i] != '\0';) {
        if ((str[i] & 0x80) == 0) {
            i += 1;
        } else if ((str[i] & 0xE0) == 0xC0) {
            i += 2;
        } else if ((str[i] & 0xF0) == 0xE0) {
            i += 3;
        } else if ((str[i] & 0xF8) == 0xF0) {
            i += 4;
        } else {
            i += 1;
        }
        length++;
    }
    return length;
}




void clearConsole() {
    system("clear");
}

void printRooms(std::vector<Room>& rooms) {
    for (const Room& room : rooms) {
        if (room.getCurrClient() != nullptr) {
            std::cout << "║"; printAligned(std::to_string(room.getNumber()), 20);
            std::cout << "║"; printAligned(room.getCurrClient()->fullName, 40);

            std::cout << "║"; printAligned(room.getCurrClient()->checkInDate, 20);
            std::cout << "║"; printAligned(room.getCurrClient()->checkOutDate, 17);

            std::cout << "║"; printAligned(room.getTypeToStr(), 17);

            std::cout << "║"; printAligned(std::to_string(room.getPrice()), 11);
            std::cout << "║"; printAligned(std::to_string(room.getCurrClient()->discountAmount), 11);

            std::cout << "║"; printAligned(room.getStatusToStr(), 11);
            std::cout << "║"; printAligned(std::to_string(room.getCurrClient()->extraSum), 11); std::cout << "║";
            std::cout << std::endl;
            std::cout << "╠════════════════════╬════════════════════════════════════════╬════════════════════╬═════════════════╬═════════════════╬═══════════╬═══════════╬═══════════╬═══════════╣" << std::endl;

        } else {
            std::cout << "║"; printAligned(std::to_string(room.getNumber()), 20);
            std::cout << "║"; printAligned("", 20);

            std::cout << "║"; printAligned("", 20);
            std::cout << "║"; printAligned("", 17);

            std::cout << "║"; printAligned(room.getTypeToStr(), 17);

            std::cout << "║"; printAligned(std::to_string(room.getPrice()), 11);
            std::cout << "║"; printAligned("", 11);

            std::cout << "║"; printAligned(room.getStatusToStr(), 11);
            std::cout << "║"; printAligned("", 11); std::cout << "║";
            std::cout << std::endl;
            std::cout << "╠════════════════════╬════════════════════════════════════════╬════════════════════╬═════════════════╬═════════════════╬═══════════╬═══════════╬═══════════╬═══════════╣" << std::endl;

        }
    }
    std::cout << "╚════════════════════╩════════════════════════════════════════╩════════════════════╩═════════════════╩═════════════════╩═══════════╩═══════════╩═══════════╩═══════════╝" << std::endl;

}

