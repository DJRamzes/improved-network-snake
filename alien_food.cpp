#include <ncurses.h>

namespace Game_elements{

    namespace Network_elements{
    
        class alien_food{
            WINDOW * win;
            int x, y;
            int data[2];
        
        public:
            alien_food(WINDOW * in_win) : win(in_win) {} 
            
            void getData(int * buff);
            void displayFood();
        };
        
        void alien_food::getData(int * buff)
        {
            x = buff[4];
            y = buff[5];
        }
        
        void alien_food::displayFood()
        {
            wmove(win, y, x);
            waddch(win, '*');
        }
                
    }

}
