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
            int down_edge;
            int right_edge;
            
        public:
            alien_snake(WINDOW * win, int x, int y);
            ~alien_snake();
            
            int getPoints();
            void getData(int * data);
            void move();
            int checkState();
            
        private:
        
            void checkPoints();
            void changeLocation(Star * star, int x, int y);
            void hideStar();
            void addStar();
            void refreshEdges();
        };
        
        int alien_snake::getPoints() { return points_per_game; }
        
        void alien_snake::refreshEdges()
        {
            for(int i = 0; i < 3; ++i){
                wmove(win, 0, i);
                waddch(win, ' ');
                wmove(win, 1, i);
                waddch(win, ' ');
            }
        }
        
        int alien_snake::checkState()
        {
            if(!buff[3])
                return 1;
            return 0;
        }
        
        void alien_snake::addStar()
        {
            Star * tmp = star;
            while(tmp->next)
                tmp = tmp->next;
            tmp->next = new Star;
            tmp->next->next = 0;
            tmp->x = -1;
            tmp->y = -1;
        }
        
        void alien_snake::checkPoints()
        {
            if(buff[2] != points_per_game){
                addStar();
                points_per_game = buff[2];
            }
        }
        
        void alien_snake::getData(int * data){
            for(int i = 0; i < buffer_size; ++i)
                buff[i] = data[i];
        }
        
        void alien_snake::move()
        {
            hideStar();
            changeLocation(star, buff[0], buff[1]);
            checkPoints();
            checkState();
            refreshEdges();
            box(win, '|', '-');
            wrefresh(win);
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
        
        void alien_snake::hideStar()
        {
            Star * tmp = star;
            while(tmp->next)
                tmp = tmp->next;
            wmove(win, tmp->y, tmp->x);
            waddch(win, ' ');
            wmove(win, tmp->y - 1, tmp->x - 1);
            waddch(win, ' ');
            wmove(win, tmp->y + 1, tmp->x + 1);
            waddch(win, ' ');
            wmove(win, tmp->y + 1, tmp->x - 1);
            waddch(win, ' ');
            wmove(win, tmp->y - 1, tmp->x + 1);
            waddch(win, ' ');
            wmove(win, tmp->y, tmp->x + 1);
            waddch(win, ' ');
            wmove(win, tmp->y, tmp->x - 1);
            waddch(win, ' ');
            wmove(win, tmp->y + 1, tmp->x);
            waddch(win, ' ');
            wmove(win, tmp->y - 1, tmp->x);
            waddch(win, ' ');
        }
        
        alien_snake::alien_snake(WINDOW * win, int max_x, int max_y) : points_per_game(0), down_edge(max_y), right_edge(max_x)
        {
            this->win = win;
            star = new Star;
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



