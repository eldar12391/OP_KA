#include <iostream>
#include <string>
#include <vector>
#include <locale.h>

#include "Room.h"
#include "models/Room.h"
#include "models/Hotel.h"
#include "engine/Screen.h"
#include "Processing.h"
using namespace std;


int main()
{
	Hotel myHotel;
	Screen screen;
	setlocale(LC_CTYPE, "ru_RU.UTF8"); 
	screen.addMenuItem("Вывести таблицу");
	screen.addMenuItem("Добавить комнату");
	screen.addMenuItem("Список комнат");
	screen.addMenuItem("Поиск комнаты");
	screen.addMenuItem("Выход");
	screen.displayMenu();
	while(screen.exitHandler()){
		unsigned int choice = screen.userChoiceHandler();
		
		switch(choice){
			case 1:
			{   
				printTable();
				printRooms(myHotel);
				break;
			}

			case 2:
			{   
				Room room1(101, 100.0, RoomType::Standard);
				room1.addClient();
				myHotel.addRoom(room1);
				std::cout << std::endl << "Успех!" << std::endl;
				break;
			}

			case 4:
			{   
				break;
			}

			case 5:
			{
				screen.exit();
				break;
			}
		}
	}
    return 0;
}