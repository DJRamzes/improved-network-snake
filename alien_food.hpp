namespace Game_elements{

    namespace Network_elements{
    
        class alien_food{
            WINDOW * win;
            int x, y;
            int data[2];
        
        public:
            alien_food(WINDOW * in_win) : win(in_win) {} 
            
            void getData(int * buff);
            void displayFood();
        };
        
    }
}
