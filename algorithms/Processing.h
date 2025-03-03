#pragma once
#include "Hotel.h"
void printRooms(Hotel hotel);
size_t utf8_length(const std::string str);
void printTable();
std::string cutStr(const std::string str, int start, int end);
void printAligned(std::string str, size_t width);
void clearConsole();
void waitForAnyKey();