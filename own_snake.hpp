namespace Game_elements{
    
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
    
    private:
    
        void hideStar();
        void changeLocation(Star * star, int x, int y);
        void checkEdges();
        void checkPosition();
    };
    
}
