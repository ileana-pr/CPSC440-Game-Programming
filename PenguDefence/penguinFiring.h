#ifndef PENGUINFIRINGH
#define PENGUINFIRINGH
#include "iceberg.h"
#include "penguinDropping.h"

class penguinFiring  
{
    public:
    penguinFiring();
    ~penguinFiring();
    void draw_penguinFiring();
    penguinFiring start_penguinFiring(int width, int height);
    void update_penguinFiring();
    void collide_penguinFiring(iceberg &iceberg);
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