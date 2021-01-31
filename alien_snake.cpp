#include <ncurses.h>

namespace Game_elements
{
    namespace Network_elements
    {     
        enum State{
            alive = 1,
            dead = 0
        };
        class alien_snake
        {        
            const int buffer_size = 6;
            
            struct Star{
                int x, y;
                Star * next;
            };
            int buff[buffer_size];
            int points_per_game;
            State state;
            
        public:
            
            void getData(int * data);
        };
        
        void alien_snake::getData(int * data){
            for(int i = 0; i < buffer_size; ++i)
                buff[i] = data[i];
        }
        
    }
}