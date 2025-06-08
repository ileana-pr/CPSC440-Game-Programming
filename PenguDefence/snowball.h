#ifndef SNOWBALLH
#define SNOWBALLH
#include "penguin.h"
#include "iceberg.h"

class snowball
{
    public:
    snowball();
    ~snowball();
    void fire_snowball(iceberg &iceberg);
    void draw_snowball();
    void update_snowball();
    void collide_snowball(penguin &penguin, iceberg &iceberg);

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
