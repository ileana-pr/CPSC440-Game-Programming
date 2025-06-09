#ifndef PENGUINH
#define PENGUINH
#include "iceberg.h"

class penguin 
{
    public:
    penguin();
    ~penguin();
    void draw_penguin();
    penguin start_penguin(int width, int height);
    void update_penguin();
    void collide_penguin(iceberg &iceberg);
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