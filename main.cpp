#include <iostream>
#include <string>
#include <vector>
#include <locale.h>
#include <ncursesw/ncurses.h>
#include "models/Room.h"
#include "models/Hotel.h"
#include "engine/Screen.h"

using namespace std;


int main()
{
	Hotel myHotel;
	Screen screen;
	setlocale(LC_CTYPE, "ru_RU.UTF8"); 
	screen.addMenuItem("Вывести таблицу");
	screen.addMenuItem("Список комнат");
	screen.addMenuItem("Поиск комнаты");
	screen.addMenuItem("Выход");
	screen.displayMenu();

	while(screen.exitHandler()){
		screen.userChoiceHandler();
	}
    return 0;
}