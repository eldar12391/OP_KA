#include "Screen.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <limits>
size_t utf8_length(const std::string str);
void printTable();
std::string cutStr(const std::string str, int start, int end);
void printAligned(std::string str, size_t width);
void clearConsole();

//Help func -----------------------------------------------------------------------------------------------------------------------

void printTable() {
    printAligned("№ Комнаты", 20); std::cout << "║";
    printAligned("Клиент", 20); std::cout << "║";
    printAligned("Дата заселения", 20); std::cout << "║";
    printAligned("Дата выезда", 17); std::cout << "║";
    printAligned("Класс номера", 8); std::cout << "║";
    printAligned("Оплата", 8); std::cout << "║";
    printAligned("Скидки", 11); std::cout << "║";
    printAligned("Бронь", 11); std::cout << "║";
    printAligned("Доплаты", 11); std::cout << "║"; std::cout << std::endl;
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
//Class func -----------------------------------------------------------------------------------------------------------------------

void Screen::processOptionSelection(unsigned int choice) {
    switch(choice){
        case 1:
        {   
            printTable();
            break;
        }

        case 4:
        {
            isNeedExit = true;
            break;
        }
    }
}

int Screen::getMenuSize() const{
    return menuItems.size();
}

std::string Screen::getMenuItem(const unsigned int num) const {
    return menuItems[num];
}

void Screen::displayMenu() const{
    std::cout << "\nВыберите опцию:\n\n";
    for(int i = 0; i < getMenuSize(); i++){
        std::cout << i+1 << ". " << getMenuItem(i) << std::endl;
    }
}

void Screen::addMenuItem(const std::string& item){
    menuItems.push_back(item);
}

void Screen::userChoiceHandler() {
    unsigned int choice = 0;
    
    while(true) {
        std::cout << "Введите номер опции: ";
        
        if(!(std::cin >> choice)) {
            // Обработка нечислового ввода
            std::cout << "Ошибка: нужно ввести число!\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        
        if(choice >= 1 && choice <= getMenuSize()) {
            break; // Корректный выбор
        }
        
        // Некорректный диапазон
        std::cout << "Ошибка: выбор должен быть от 1 до " 
                  << getMenuSize() << "!\n";
    }
    
    processOptionSelection(choice);
}


bool Screen::exitHandler() const {
    return !isNeedExit;
}
