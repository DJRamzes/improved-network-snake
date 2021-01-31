#include <ncurses.h>

namespace Game_elements
{
    namespace Network_elements
    {
        const int buffer_size = 6;
        
        class alien_snake
        {            
            struct Star{
                int x, y;
                Star * next;
            };
            WINDOW * win;
            Star * star;
            int buff[buffer_size];
            int points_per_game;
            
        public:
            alien_snake(WINDOW * win, int x, int y);
            ~alien_snake();
            
            void getData(int * data);
            void move();
            void checkPoints();
            void changeLocation(Star * star, int x, int y);
            void hideSnake();
        };
        
        void alien_snake::getData(int * data){
            for(int i = 0; i < buffer_size; ++i)
                buff[i] = data[i];
        }
        
        void alien_snake::move()
        {
            hideSnake();
            changeLocation(star, buff[0], buff[1]);
        }
        
        void alien_snake::changeLocation(Star * star, int x, int y)
        {
            if(!star)
                return;
            changeLocation(star->next, star->x, star->y);
            star->x = x;
            star->y = y;
            wmove(win, star->y, star->x);
            waddch(win, '*');
        }
        
        void alien_snake::hideSnake()
        {
            Star * tmp = star;
            while(tmp->next)
                tmp = tmp->next;
            wmove(win, tmp->y, tmp->x);
            waddch(win, ' ');
        }
        
        alien_snake::alien_snake(WINDOW * win, int x, int y) : points_per_game(0)
        {
            this->win = win;
            star = new Star;
            star->x = x;
            star->y = y;
            wmove(win, star->y, star->x);
            waddch(win, '*');
        }
        
        alien_snake::~alien_snake()
        {
            Star * tmp;
            while(star){
                tmp = star;
                star = star->next;
                delete tmp;
            }
        }
        
    }
}