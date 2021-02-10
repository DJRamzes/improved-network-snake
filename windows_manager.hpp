namespace Game_elements{

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
    };

}
