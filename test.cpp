#include <locale.h>
#include <ncursesw/ncurses.h>

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    initscr();
    printw("ТЕСТ РУССКОЙ ЛОКАЛКИ");
    refresh();
    getch();
    endwin();
    return 0;
}