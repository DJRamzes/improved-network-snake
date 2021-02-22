#include <ncurses.h>

namespace Game_elements{

    int timeout_val = 50;

    class windowsManager{ // not the OS Windows, this is a unit which will be manage windows on the screen.
        int player_win_size[2];
        int max_x, max_y;
        int amount_of_players;
        WINDOW * own_win, * another_win;
    
    public:
        windowsManager(int * size_buff);
        ~windowsManager();
        void createWindows();
        WINDOW * giveFirstWin() { return own_win; }
        WINDOW * giveSecondWin() { return another_win; }
        int giveMax_x() { return player_win_size[0]; }
        int giveMax_y() { return player_win_size[1]; }
        int menu();
    };
    
    /*
    *	If below function returns 1 - local game mode
    *	If below function returns 2 - network game mode
    *	If below function returns 3 - exit the game
    */
    int windowsManager::menu()
    {
        wmove(stdscr, max_y / 4, max_x / 2 - 3); // 3 - size of half a str "SNAKE"
        waddstr(stdscr, "SNAKE");
        wmove(stdscr, max_y / 2 - max_y / 10, max_x / 2 - 5); // 5 - size of half a str "Local game"
        waddstr(stdscr, "Local game - 1");
        wmove(stdscr, max_y / 2 - max_y / 15, max_x / 2 - 6);
        waddstr(stdscr, "Network game - 2");
        wmove(stdscr, max_y / 2 - max_y / 30, max_x / 2 - 2);
        waddstr(stdscr, "Exit - 3");
        wmove(stdscr, max_y / 2 + max_y / 10, max_x / 2 - 7);
        waddstr(stdscr, "PRESS 1, 2 OR 3");
        wrefresh(stdscr);
        int key = getch();
        switch(key){
            case 49: // 49 = key 1
                key = 1;
                break;
            case 50: // 50 - key 2
                key = 2;
                break;
            case 51: // 51 - key 3
                key = 3;
                break;
        }
        timeout(timeout_val);
        return key;
    }
    
    windowsManager::windowsManager(int * size_buff)
    {
        player_win_size[0] = size_buff[0];
        player_win_size[1] = size_buff[1];
        initscr();
        cbreak();
        //timeout(timeout_val);
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
            own_win = newwin(player_win_size[1], player_win_size[0], 1, 1);
            another_win = newwin(player_win_size[1], player_win_size[0], 1, max_x - max_x / 2);
            box(own_win, '|', '-');
            box(another_win, '|', '-');
            wrefresh(own_win);
            wrefresh(another_win);
        }
    }

}
