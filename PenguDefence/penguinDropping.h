#ifndef PENGUINDROPINGH
#define PENGUINDROPINGH
#include "iceberg.h"



class penguinDropping  
{
    public: 
    penguinDropping(); 
    ~penguinDropping();
    void draw_penguinDropping();
    void start_penguinDropping(int width, int height);
    void update_penguinDropping();
    void collide_penguinDropping(iceberg &iceberg);
    int get_x();
    int get_y();
    int get_bound_x();
    int get_bound_y();
    bool get_live();
    void set_live(bool live);

    private:
    int x;
    int y;
    int bound_x;
    int bound_y;
    bool live;
    int speed;
    ALLEGRO_BITMAP *image;
};
#endif