#include <iostream>
#include <ncurses.h>
#include <boost/asio.hpp>

class OwnSnake{
    struct Star{
        int x, y;
        Star * next;
    };
    struct Direction{
        int x, y;
    };
    
    Star * star;
    Direction direction;
    int down_edge;
    int right_edge;
    int points_per_game;
    WINDOW * win;
    
public:
    
    OwnSnake(WINDOW * win, int max_x, int max_y, int x, int y);
    ~OwnSnake();
    
    inline void turnLeft();
    inline void turnRight();
    inline void turnUp();
    inline void turnDown();
    void keepMoving();
    void addStar();
    
private:
    
    void hideStar();
    void changeLocation(Star * star, int x, int y);
    void checkEdges();
};

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
    
    OwnSnake own_snake(stdscr, max_x, max_y, max_x / 2, max_y / 2);
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
    }
    endwin();
    return 0;
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
    star->x = star->x >= down_edge ? 0 : star->x;
    star->x = star->x < 0 ? down_edge - 1 : star->x;
    star->y = star->y >= right_edge ? 0 : star->y;
    star->y = star->y < 0 ? right_edge - 1 : star->y;
}

void OwnSnake::hideStar()
{
    Star * tmp = star;
    while(tmp->next)
        tmp = tmp->next;
    wmove(win, tmp->y, tmp->x);
    waddch(win, ' ');
    return;
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
    star->x += direction.x;
    star->y += direction.y;
    checkEdges();
    changeLocation(star, star->x, star->y);
    wrefresh(win);
}

inline void OwnSnake::turnUp()
{
    direction.x = 0;
    direction.y = -1;
    keepMoving();
}

inline void OwnSnake::turnDown()
{
    direction.x = 0;
    direction.y = 1;
    keepMoving();
}

inline void OwnSnake::turnLeft()
{
    direction.x = -1;
    direction.y = 0;
    keepMoving();
}

inline void OwnSnake::turnRight()
{
    direction.x = 1;
    direction.y = 0;
    keepMoving();
}

OwnSnake::OwnSnake(WINDOW * win, int max_x, int max_y, int x, int y) : down_edge(max_x), right_edge(max_y), points_per_game(0)
{
    this->win = win;
    star = new Star;
    star->x = x;
    star->y = y;
    star->next = new Star;
    star->next->next = 0;
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
