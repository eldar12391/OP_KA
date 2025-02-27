#pragma once
#include <vector>
#include <string>
#include <functional>

class Screen{
    private:
        std::vector<std::string> menuItems;
        int selectedItem{};
        bool isNeedExit = false;
        void processOptionSelection(unsigned int choice);
    public:
        bool exitHandler() const;
        std::string getMenuItem(const unsigned int num) const;
        void addMenuItem(const std::string& item);
        void displayMenu() const;
        int getMenuSize() const;
        unsigned int userChoiceHandler();
        void exit();
};
