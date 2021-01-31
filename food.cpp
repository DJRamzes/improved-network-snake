#include <ncurses.h>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include "own_snake.hpp"

namespace Game_elements{
    
    namespace Local_elements{
    
        class Food{
            WINDOW * win;
        
            int max_x;
            int max_y;
        
            int x;
            int y;
        
            int data[2];
        
        public:
            Food(WINDOW * in_win, int in_max_x, int in_max_y) : win(in_win), max_x(in_max_x), max_y(in_max_y)
            {
                srand(time(0));
	        x = 5 + rand() % (max_x - 10);
	        y = 5 + rand() % (max_y - 10);
	        wmove(win, y, x);
	        waddch(win, '*');
	    }
    
            inline int getX() { return x; }
            inline int getY() { return y; }
            void changeLocation();
            void display();
        
            int * giveData();
        };
    
        int * Food::giveData()
        {
            data[0] = x;
            data[1] = y;
            return data;
        }

        void Food::changeLocation()
        {
            x = 5 + rand() % (max_x - 10);
            y = 5 + rand() % (max_y - 10);
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

}
