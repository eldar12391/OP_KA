#include "Screen.h"
#include "Processing.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <limits>

//Help func -----------------------------------------------------------------------------------------------------------------------
//Class func -----------------------------------------------------------------------------------------------------------------------


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

unsigned int Screen::userChoiceHandler() {
    unsigned int choice = -1;
    
    while(true) {
        std::cout << "Введите номер опции: ";
        
        if(!(std::cin >> choice)) {
            // Обработка нечислового ввода
            std::cout << "Ошибка: нужно ввести число!\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        
        if(choice >= 0 && choice <= getMenuSize()) { //ПОМЕНЯТЬ ПОТОМ НА 1!!!
            break; // Корректный выбор
        }
        
        // Некорректный диапазон
        std::cout << "Ошибка: выбор должен быть от 1 до " 
                  << getMenuSize() << "!\n";
    }
    
    return choice;
}

void Screen::exit(){
    isNeedExit = true;
}

bool Screen::exitHandler() const {
    return !isNeedExit;
}
