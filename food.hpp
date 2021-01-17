#include <cstdlib>
#include <ctime>

namespace Game_elements{

    class Food{
        WINDOW * win;
        
        int max_x;
        int max_y;
        
        int x;
        int y;
        
    public:
        //Food(WINDOW * in_win, int in_max_x, int in_max_y);
        Food(WINDOW * in_win, int in_max_x, int in_max_y) : win(in_win), max_x(in_max_x), max_y(in_max_y)
        {
            srand(time(0));
	    x = 20 + rand() % max_x - 20;
	    y = 20 + rand() % max_y - 20;
	    wmove(win, y, x);
	    waddch(win, '*');
        }
        inline int getX() { return x; }
        inline int getY() { return y; }
        void changeLocation();
        void display();
    };
    
    bool checkContact(Food * food, OwnSnake * own_snake);
    
}
