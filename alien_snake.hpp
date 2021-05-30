namespace Game_elements
{
    namespace Network_elements
    {
        const int buffer_size = 6;
        struct Star{
        	int x, y;
        	Star * next;
        };
        class alien_snake
        {            
            WINDOW * win;
            Star * star;
            int buff[buffer_size];
            int points_per_game;
            int down_edge;
            int right_edge;
            
        public:
            alien_snake(WINDOW * win, int max_x, int max_y);
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
        
    }
}
