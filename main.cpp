#include <ncurses.h>
#include "own_snake.hpp"
#include "food.hpp"

int main()
{
    initscr();
    cbreak();
    timeout(50);
    keypad(stdscr, 1);
    noecho();
    curs_set(0);
    
    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);
    
    Game_elements::Local_elements::OwnSnake own_snake(stdscr, max_x, max_y, max_x / 2, max_y / 2);
    Game_elements::Local_elements::Food food(stdscr, max_x, max_y);
    int key;
    while(1){
        key = getch();
        switch(key){
            case KEY_UP:
                own_snake.turnUp();
                break;
            case KEY_DOWN:
                own_snake.turnDown();
                break;
            case KEY_LEFT:
                own_snake.turnLeft();
                break;
            case KEY_RIGHT:
                own_snake.turnRight();
                break;
            case ERR:
                own_snake.keepMoving();
                break;
        }
        if(Game_elements::Local_elements::checkContact(&food, &own_snake)){
            own_snake.addStar();
            food.changeLocation();
        }
        food.display();
        if(own_snake.getState() == Game_elements::Local_elements::dead)
            break;
    }
    endwin();
    return 0;
}
