#ifndef SNOWBALLH
#define SNOWBALLH
#include "penguinFiring.h"
#include "penguinDropping.h"

class snowball
{
public:
    snowball();
    ~snowball();
    void fire_snowball(penguinFiring &penguinFiring);
    void draw_snowball();
    void update_snowball(int width, int height);
    void collide_snowball(penguinDropping pd[], int cSize, penguinFiring &penguinFiring);
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
