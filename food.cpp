#include <ncurses.h>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include "own_snake.hpp"

namespace Game_elements{
    
    class Food{
        WINDOW * win;
        
        int max_x;
        int max_y;
        
        int x;
        int y;
        
    public:
        Food(WINDOW * in_win, int in_max_x, int in_max_y) : win(in_win), max_x(in_max_x), max_y(in_max_y)
        {
            srand(time(0));
	    x = rand() % max_x;
	    y = rand() % max_y;
	    wmove(win, y, x);
	    waddch(win, '*');
        }
    
        inline int getX() { return x; }
        inline int getY() { return y; }
        void changeLocation();
        void display();
    };

    void Food::changeLocation()
    {
        x = rand() % max_x;
        y = rand() % max_y;
        wmove(win, y, x);
        waddch(win, '*');
    }

    void Food::display()
    {
        wmove(win, y, x);
        waddch(win, '*');
    }


    bool checkContact(Food * food, OwnSnake * own_snake)
    {
        return food->getX() == own_snake->getX() && food->getY() == own_snake->getY() ? true : false;
    }

}
