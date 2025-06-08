#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "iceberg.h"
#include "penguin.h"
#include "snowball.h"


// The object of the game is to defend your iceberg from dropping penguins by firing snowballs at them. You will use the left and right keys to aim, and the spacebar to fire. If enough penguins land on the iceberg, it will sink. The penguins will drop from the top of the screen, and you will need to fire at them before they reach the iceberg. 



int main(void)
{
     // initialize allegro
    if(!al_init()) return -1;


    bool done = false; 
    int width = 640;
    int height = 520;
    int score = 0;
    int FPS = 60;

    penguinClass penguin;
    icebergClass iceberg;
    snowballClass snowball;
   

    // create the display
    ALLEGRO_DISPLAY *display = NULL;
    display = al_create_display(width, height);
    if (!display) return -1;


    // create the event queue
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    event_queue = al_create_event_queue();
    if (!event_queue) return -1;

    // create the timer
    ALLEGRO_TIMER *timer = NULL;
    timer = al_create_timer(1.0 / 60);
    if (!timer) return -1;

    // create the font
    ALLEGRO_FONT *font = NULL;
    al_init_font_addon();
    al_init_ttf_addon();
    font = al_load_font("GROBOLD.TTF", 16, 0);
    if (!font) return -1;

    // create the iceberg
    iceberg.create_iceberg_bitmap(display);

    // create the penguin
    penguin.create_penguin_bitmap(display);

    // create the snowball
    snowball.create_snowball_bitmap(display);
    
}







