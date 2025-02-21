#pragma once
#include <ncurses.h>
#include <vector>
#include <string>
#include <functional>

class Screen{
    private:
        std::vector<std::string> menuItems;
        int selectedItem{};
        bool isNeedExit = false;

        void printAligned(const std::string, size_t width) const;
        size_t utf8_length(const std::string str) const;
        std::string cutStr(const std::string str, int start, int end) const;

    public:
        bool exitHandler() const;
        void processOptionSelection(unsigned int choice) const;
        int getMenuSize() const;
        std::string getMenuItem(const unsigned int num) const;
        void addMenuItem(const std::string& item);
        void displayMenu() const;
        void userChoiceHandler() const;
        void printTable() const;
};