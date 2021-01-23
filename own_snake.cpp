#include <ncurses.h>

namespace Game_elements{
    
    namespace Local_elements{
    
        enum State{
            alive = 1,
            dead = 0
        };
    
        class OwnSnake{
            struct Star{
    	        int x, y;
    	        Star * next;
    	    };
            struct Direction{
    	        int x, y;
    	    };
        
            int data[4];
    
            Star * star;
            Direction direction;
            int down_edge;
            int right_edge;
            int points_per_game;
            WINDOW * win;
            State state;
    
        public:
    
            OwnSnake(WINDOW * win, int max_x, int max_y, int x, int y);
            ~OwnSnake();
    
            void turnLeft();
            void turnRight();
            void turnUp();
            void turnDown();
            void keepMoving();
            void addStar();
            inline int getX() { return star->x; }
            inline int getY() { return star->y; }
            inline int getState() { return state; }
        
            int * takeData();
    
        private:
    
            void hideStar();
            void changeLocation(Star * star, int x, int y);
            void checkEdges();
            void checkPosition();
            void refreshEdges();
        };
    
        int * OwnSnake::takeData()
        {
            data[0] = star->x;
            data[1] = star->y;
            data[3] = points_per_game;
            data[4] = state;
            return data;
        }
    
        void OwnSnake::refreshEdges()
        {
            for(int i = 0; i < right_edge; ++i){
                wmove(win, 0, i);
                waddch(win, ' ');
            }
            for(int i = 0; i < right_edge; ++i){
                wmove(win, down_edge - 1, i);
                waddch(win, ' ');
            }
            for(int i = 0; i < down_edge; ++i){
                wmove(win, i, 0);
                waddch(win, ' ');
            }
            for(int i = 0; i < down_edge; ++i){
                wmove(win, i, right_edge - 1);
                waddch(win, ' ');
            }
        }
    
        void OwnSnake::checkPosition()
        {
            if(points_per_game == 0) return;
            Star * tmp = star;
            while(tmp->next){
                tmp = tmp->next;
                if(star->x == tmp->x && star->y == tmp->y)
                    state = dead;
                }
        }

        void OwnSnake::addStar()
        {
            ++points_per_game;
            Star * tmp = star;
            while(tmp->next)
	        tmp = tmp->next;
	    tmp->next = new Star;
	    tmp->next->next = 0;
	}

        void OwnSnake::checkEdges()
        {
            if(star->x >= right_edge){
                star->x = 1;
                refreshEdges();
                return;
            }
            if(star->x <= 0){
                star->x = right_edge - 1;
                refreshEdges();
                return;
            }
            if(star->y >= down_edge){
                star->y = 1;
                refreshEdges();
                return;
            }
            if(star->y <= 0){
                star->y = down_edge - 1;
                refreshEdges();
                return;
            }
        }

        void OwnSnake::hideStar()
        {
            Star * tmp = star;
            while(tmp->next)
	        tmp = tmp->next;
	    wmove(win, tmp->y, tmp->x);
            waddch(win, ' ');
        }

        void OwnSnake::changeLocation(Star * star, int x, int y)
        {
            if(!star)
	        return;
	    changeLocation(star->next, star->x, star->y);
            star->x = x;
            star->y = y;
            wmove(win, star->y, star->x);
            waddch(win, '*');
        }

        void OwnSnake::keepMoving()
        {
            hideStar();
            changeLocation(star, star->x + direction.x, star->y + direction.y);
            checkEdges();
            checkPosition();
            wrefresh(win);
        }

        void OwnSnake::turnUp()
        {
            if(direction.x == 0 && direction.y == 1)
                return;
            direction.x = 0;
            direction.y = -1;
            keepMoving();
        }

        void OwnSnake::turnDown()
        {
            if(direction.x == 0 && direction.y == -1)
                return;
            direction.x = 0;
            direction.y = 1;
            keepMoving();
        }

        void OwnSnake::turnLeft()
        {
            if(direction.x == 1 && direction.y == 0)
                return;
            direction.x = -1;
            direction.y = 0;
            keepMoving();
        }

        void OwnSnake::turnRight()
        {
            if(direction.x == -1 && direction.y == 0)
                return;
            direction.x = 1;
            direction.y = 0;
            keepMoving();
        }

        OwnSnake::OwnSnake(WINDOW * win, int max_x, int max_y, int x, int y) : down_edge(max_y), right_edge(max_x), points_per_game(0)
        {
            state = alive;
            this->win = win;
            star = new Star;
            star->x = x;
            star->y = y;
            direction.x = 0;
            direction.y = 0;
            wmove(win, star->y, star->x);
            waddch(win, '*');
        }

        OwnSnake::~OwnSnake()
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
