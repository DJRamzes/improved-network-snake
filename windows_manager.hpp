namespace Game_elements{

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
        int giveMax_x() { return max_x - max_x / 2 - 1; }
        int giveMax_y() { return max_y - 1; }
    };

}
