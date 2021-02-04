#include <ncurses.h>
#include <string>
#include "windows_manager.hpp"
#include "own_snake.hpp"
#include "food.hpp"
#include "net_conf.hpp"

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
    
    Game_elements::windowsManager windows_manager;
    windows_manager.createWindows();
    Game_elements::Network_elements::Client client(std::string("127.0.0.1"));
    Game_elements::Local_elements::OwnSnake own_snake(windows_manager.giveFirstWin(), windows_manager.giveMax_x() - 1,
                                                      windows_manager.giveMax_y() - 1, windows_manager.giveMax_x() / 2, windows_manager.giveMax_y() / 2);
    Game_elements::Local_elements::Food food(windows_manager.giveFirstWin(), windows_manager.giveMax_x(), windows_manager.giveMax_y());
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
        client.getData(own_snake.giveData(), food.giveData());
        client.sendData();
        if(client.available())
            client.recvData();
    }
    endwin();
    return 0;
}

