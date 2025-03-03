#pragma once
#include <iostream>
#include <vector>
#include "Room.h"

enum class SortOrder;

void sortByRoomType(std::vector<Room>& rooms, SortOrder order);
void sortByClientFullName(std::vector<Room>& rooms, SortOrder order);
tm parseDate(const std::string& dateStr);
void sortByCheckInDate(std::vector<Room>& rooms, SortOrder order);
void sortByCheckOutDate(std::vector<Room>& rooms, SortOrder order);
void sortByRoomStatus(std::vector<Room>& rooms, SortOrder order);
SortOrder getUserSortOrder();
void getUserFieldSort();
void sortField(std::vector<Room>& rooms);