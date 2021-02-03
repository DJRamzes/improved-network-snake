namespace Game_elements
{
    namespace Network_elements
    {
        const int buffer_size = 6;
        
        class alien_snake
        {            
            struct Star;
            WINDOW * win;
            Star * star;
            int buff[buffer_size];
            int points_per_game;
            
        public:
            alien_snake(WINDOW * win, int x, int y);
            ~alien_snake();
            
            void getData(int * data);
            void move();
            
        private:
        
            void checkPoints();
            void changeLocation(Star * star, int x, int y);
            void hideSnake();
            void addStar();
        };
        
    }
}
