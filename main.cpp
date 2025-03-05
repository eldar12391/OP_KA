#include <iostream>
#include <string>
#include <vector>
#include <locale.h>
#include <fstream>
#include "Room.h"
#include "models/Room.h"
#include "models/Hotel.h"
#include "engine/Screen.h"
#include "Processing.h"
#include "Sort.h"
#include "Requests.h"

void saveRoomsToTextFile(const std::vector<Room>& rooms, const std::string& filename);
std::vector<Room> loadRoomsFromTextFile(const std::string& filename);

int main()
{
	Hotel myHotel;
	Screen screen;
	setlocale(LC_CTYPE, "ru_RU.UTF8"); 
	screen.addMenuItem("Вывести таблицу");
	screen.addMenuItem("Изменить информацию о комнате");
	screen.addMenuItem("Сортировка");
	screen.addMenuItem("Запросы");
	//screen.addMenuItem("Добавить запись");
	//screen.addMenuItem("Список комнат");
	//screen.addMenuItem("Поиск комнаты");
	screen.addMenuItem("Сохранить информацию в файл");
	screen.addMenuItem("Загрузить информацию из файла");
	screen.addMenuItem("Выход");

	
	while(screen.exitHandler()){
		clearConsole();
		screen.displayMenu();
		unsigned int choice = screen.userChoiceHandler();
		
		switch(choice){
			case 0:
			{
				clearConsole();
				std::cout << "Введите количество комнат: ";
				int count = 0;
				std::cin >> count;
				myHotel.generateRooms(count);
				std::cout << "Успех!";
				break;
			}
			case 1:
			{   clearConsole();
				printTable();
				printRooms(myHotel.getRooms());
				break;
			}

			case 2:
			{   
				clearConsole();
				std::cout << "Введите номер комнаты: " << std::endl;
				std::cout << ">> ";
				int num = 0;
				std::cin >> num;
				
				if(myHotel.findRoom(num) != nullptr){
					myHotel.editRoom(num);
				}
				else{
					clearConsole();
					std::cout << "Комната с этим номером не найдена." << std::endl;
					break;
				}
				break;
			}
			
			case 3:
			{
				sortField(myHotel.getRooms());
				break;
			}
			case 4:
			{
				requestHandler(myHotel);
				break;
			}
			case 8:
			{   
				int length = myHotel.getRooms().size() + 1;
				Room room1(length, 100.0, RoomType::Standard);
				room1.addClient();
				myHotel.addRoom(room1);
				std::cout << std::endl << "Успех!" << std::endl;
				break;
			}

			case 7:
			{
				screen.exit();
				return 0;
			}
			case 5:
			{
				std::string filename;
				std::cout << "Введите имя файла: ";
				std::cin >> filename;
				saveRoomsToTextFile(myHotel.getRooms(), filename);
				break;
			}
			case 6:
			{	
				std::string filename;
				std::cout << "Введите имя файла: ";
				std::cin >> filename;
				myHotel.loadFile(loadRoomsFromTextFile(filename));
				break;
			}
		}
		waitForAnyKey();
	}
    return 0;
}



void saveRoomsToTextFile(const std::vector<Room>& rooms, const std::string& filename) {
    std::ofstream outFile(filename); // Открываем файл для записи

    if (outFile.is_open()) {
        for (const auto& room : rooms) {
            room.serializeToText(outFile); // Используем метод serializeToText
        }
        outFile.close();
    } else {
        std::cerr << "Ошибка: невозможно сохранить файлы " << filename << std::endl;
    }
}

// Функция для загрузки вектора комнат из текстового файла
std::vector<Room> loadRoomsFromTextFile(const std::string& filename) {
    std::vector<Room> rooms;
    std::ifstream inFile(filename); // Открываем файл для чтения

    if (inFile.is_open()) {
        Room room;
        while (inFile.peek() != EOF) {
            room.deserializeFromText(inFile); // Используем метод deserializeFromText
            rooms.push_back(room);
        }
        inFile.close();
    } else {
        std::cerr << "Ошибка: невозможно открыть файл: " << filename << std::endl;
    }

    return rooms;
}

