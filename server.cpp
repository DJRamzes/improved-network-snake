#include <ncurses.h>
#include "windows_manager.hpp"
#include "own_snake.hpp"
#include "food.hpp"
#include "net_conf.hpp"
#include "alien_snake.hpp"
#include "alien_food.hpp"

int main()
{
    initscr();
    cbreak();
    keypad(stdscr, 1);
    noecho();
    curs_set(0);
    
    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);
    
    Game_elements::Network_elements::Server server(max_x, max_y);
    server.sync_screens();
    
    Game_elements::windowsManager windows_manager(server.giveSize_buff());
    windows_manager.menu();
    windows_manager.createWindows();
    //Game_elements::Network_elements::Server server(max_x, max_y);
    Game_elements::Local_elements::OwnSnake own_snake(windows_manager.giveFirstWin(), windows_manager.giveMax_x() - 1, windows_manager.giveMax_y() - 1,
                                                     windows_manager.giveMax_x() / 2, windows_manager.giveMax_y() / 2);
    Game_elements::Local_elements::Food food(windows_manager.giveFirstWin(), windows_manager.giveMax_x(), windows_manager.giveMax_y());
    Game_elements::Network_elements::alien_snake another_snake(windows_manager.giveSecondWin(), windows_manager.giveMax_x() - 1, windows_manager.giveMax_y() - 1);
    Game_elements::Network_elements::alien_food another_food(windows_manager.giveSecondWin());
    
    //server.sync_screens();
    
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
        server.getData(own_snake.giveData(), food.giveData());
        server.sendData();
        if(server.available()){
            server.recvData();
            another_snake.getData(server.giveData());
            another_snake.move();
            another_food.getData(server.giveData());
            another_food.displayFood();
            //if(another_snake.checkState())
            //	break;
        }
    }
    endwin();
    return 0;
}

