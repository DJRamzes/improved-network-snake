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
    
    int own_snake_points, another_snake_points;
    
    Game_elements::windowsManager windows_manager;
    int players_amount = windows_manager.menu();
    try
    {
        if(players_amount == 2){
    	    Game_elements::Network_elements::Server server(max_x, max_y);
    	    server.sync_screens();
    	    windows_manager.getSize(server.giveSize_buff());
    	    windows_manager.createWindows();
        
    	    Game_elements::Local_elements::OwnSnake own_snake(windows_manager.giveFirstWin(), windows_manager.giveMax_x() - 1, windows_manager.giveMax_y() - 1,
                                                     windows_manager.giveMax_x() / 2, windows_manager.giveMax_y() / 2);
            Game_elements::Local_elements::Food food(windows_manager.giveFirstWin(), windows_manager.giveMax_x(), windows_manager.giveMax_y());
            Game_elements::Network_elements::alien_snake another_snake(windows_manager.giveSecondWin(), windows_manager.giveMax_x() - 1, windows_manager.giveMax_y() - 1);
            Game_elements::Network_elements::alien_food another_food(windows_manager.giveSecondWin());
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
                    if(another_snake.checkState())
            	        break;
                }
                own_snake_points = own_snake.getPoints();
                another_snake_points = another_snake.getPoints();
            }
            endwin();
        } else if(players_amount == 1){
    	    windows_manager.createWindows();
    	    Game_elements::Local_elements::OwnSnake own_snake(windows_manager.giveFirstWin(), max_x - 1, max_y - 1, max_x / 2, max_y / 2);
    	    Game_elements::Local_elements::Food food(windows_manager.giveFirstWin(), max_x, max_y);
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
        } else if(players_amount == 3)
            endwin();
    }
    
    catch(std::exception& ex){
        wmove(windows_manager.giveFirstWin(), windows_manager.giveMax_y() / 2, windows_manager.giveMax_x() / 2 - 10);
        waddstr(windows_manager.giveFirstWin(), "Your points: ");
        waddstr(windows_manager.giveFirstWin(), std::to_string(own_snake_points).c_str());
        
        wmove(windows_manager.giveSecondWin(), windows_manager.giveMax_y() / 2, windows_manager.giveMax_y() / 2 - 10);
        waddstr(windows_manager.giveSecondWin(), "Enemy's points: ");
        waddstr(windows_manager.giveSecondWin(), std::to_string(another_snake_points).c_str());
        
        wrefresh(windows_manager.giveFirstWin());
        wrefresh(windows_manager.giveSecondWin());
        while(1);
    }
    
    return 0;
}

