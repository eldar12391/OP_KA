#include "Room.h"
#include <iostream>
Room::Room(unsigned int num, double p, RoomType t) : number(num), price(p), type(t), status(RoomStatus::Available), currClient(nullptr){}

unsigned int Room::getNumber() const { return number; }
RoomType Room::getType() const { return type; }
RoomStatus Room::getStatus() const { return status; }
double Room::getPrice() const { return price; }
Client* Room::getCurrClient() const { return currClient; }

void Room::setStatus(RoomStatus newStatus){ status = newStatus; }
void Room::assignClient(Client* client) { currClient = client; status = RoomStatus::Occupied; }
void Room::removeClient() { currClient = nullptr; status = RoomStatus::Available; }