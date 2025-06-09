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
    void update_snowball();
    void collide_snowball(penguinDropping pd[], int cSize);

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
