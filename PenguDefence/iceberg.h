#ifndef ICEBERGH
#define ICEBERGH

class iceberg 
{
    public: 
    iceberg();
    ~iceberg();
    void draw_iceberg();
    void update_iceberg();
    void removeLife();
    void start_iceberg(int width, int height);
  

    int get_x();
    int get_y();
    int get_bound_x();
    int get_bound_y();
    bool get_live();
    void set_live(bool live);
    int get_lives();

    private:
    int x;
    int y;
    int bound_x;
    int bound_y;
    bool live;
    int speed;
    ALLEGRO_BITMAP *image;
    int lives;
};
#endif
