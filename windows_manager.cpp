#include <ncurses.h>

namespace Game_elements{

    int timeout_val = 50;

    class windowsManager{ // not the OS Windows, this is a unit which will be manage windows on the screen.
        int max_x, max_y;
        int amount_of_players;
        WINDOW * own_win, * another_win;
    
    public:
        windowsManager();
        ~windowsManager();
        void createWindows();
        WINDOW * giveFirstWin() { return own_win; }
        WINDOW * giveSecondWin() { return another_win; }
        int giveMax_x() { return max_x - max_x / 2; }
        int giveMax_y() { return max_y - 1; }
    };
    
    windowsManager::windowsManager()
    {
        initscr();
        cbreak();
        timeout(timeout_val);
        keypad(stdscr, 1);
        noecho();
        curs_set(0);
        getmaxyx(stdscr, max_y, max_x);
        amount_of_players = 2;
    }
    
    windowsManager::~windowsManager() { endwin(); }
    
    void windowsManager::createWindows()
    {
        if(amount_of_players == 2){
            own_win = newwin(max_y - 1, max_x - max_x / 2 - 1, 1, 1);
            another_win = newwin(max_y - 1, max_x - max_x / 2 - 1, 1, max_x - max_x / 2);
            box(own_win, '|', '-');
            box(another_win, '|', '-');
            wrefresh(own_win);
            wrefresh(another_win);
        }
    }

}
