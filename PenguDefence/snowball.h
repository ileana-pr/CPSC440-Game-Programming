#ifndef SNOWBALLH
#define SNOWBALLH
#include "penguinFiring.h"
#include "penguinDropping.h"
#include <cmath>

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
    void update_snowball();
    bool is_live();



private:
    float angle;  // angle in degrees
    float x;
    float y;
    int speed;
    int bound_x;
    int bound_y;
    bool live;
    const float BALL_SPEED = 5.0;  // adjust as needed
    ALLEGRO_BITMAP *image;
};
#endif
