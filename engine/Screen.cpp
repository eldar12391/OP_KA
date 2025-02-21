#include "Screen.h"
#include <vector>
#include <iostream>
#include <iomanip>


//Private func -----------------------------------------------------------------------------------------------------------------------

std::string Screen::cutStr(const std::string str, int start, int end) const{
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

void Screen::printAligned(std::string str, size_t width) const {
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

size_t Screen::utf8_length(const std::string str) const {
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



//Public func -----------------------------------------------------------------------------------------------------------------------

void Screen::printTable() const {
    printAligned("№ Комнаты", 20); std::cout << "║";
    printAligned("Имя", 20); std::cout << "║";
    printAligned("Отчество", 20); std::cout << "║";
    printAligned("Год рождения", 17); std::cout << "║";
    printAligned("Курс", 8); std::cout << "║";
    printAligned("Группа", 8); std::cout << "║";
    printAligned("Предмет 1", 11); std::cout << "║";
    printAligned("Предмет 2", 11); std::cout << "║";
    printAligned("Предмет 3", 11); std::cout << "║"; std::cout << std::endl;
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
        std::cout << i << ". " << getMenuItem(i) << std::endl;
    }
}

void Screen::addMenuItem(const std::string& item){
    menuItems.push_back(item);
}

void Screen::userChoiceHandler() const {
    unsigned int choice = 0;
    bool choiceIsNotCorrect = true;

    while(!(std::cin >> choice) || choiceIsNotCorrect){
        if(choice > 0 && choice < getMenuSize()){
            choiceIsNotCorrect = false;
        }
    }
}

void Screen::processOptionSelection(unsigned int choice) const {
    switch(choice){
        case 1:
        {   
            break;
        }
    }
}

bool Screen::exitHandler() const {
    return !isNeedExit;
}

void Screen::printTable() const {

}