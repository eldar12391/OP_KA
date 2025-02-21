#include "Screen.h"
#include <vector>
#include <iostream>

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
    std::cout << ">> ";
}

void Screen::addMenuItem(const std::string& item){
    menuItems.push_back(item);
}
