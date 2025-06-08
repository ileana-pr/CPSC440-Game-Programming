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

    penguin penguin;
    iceberg iceberg;
    snowball snowball;
   

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

    al_install_keyboard();
	al_init_primitives_addon();

    
    // create the iceberg
    iceberg.create_iceberg_bitmap(display);

    // create the penguin
    penguin.create_penguin_bitmap(display);

    // create the snowball
    snowball.create_snowball_bitmap(display);

     while(!done)
      {
            ALLEGRO_EVENT ev;
            al_wait_for_event(event_queue, &ev);
            if(ev.type == ALLEGRO_EVENT_TIMER)
            {
                  redraw = true;
                  Left Keyboard Call
                        Call rotate cannon
                  Right Keyboard
                        Call rotate cannon
                  Update Snowballs
                  Start Penguins Dropping
                  Update Penguins Dropping
                  Collide Snowballs
                  Collide Penguins
            }
            else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
                  done = true;
            }
            else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                  switch(ev.keyboard.keycode)
                  {
                  case ALLEGRO_KEY_ESCAPE:
                        done = true;
                        break;
                  case ALLEGRO_KEY_UP:
                        keys[UP] = true;
                        break;
                  case ALLEGRO_KEY_DOWN:
                        keys[DOWN] = true;
                        break;
                  case ALLEGRO_KEY_LEFT:
                        keys[LEFT] = true;
                        break;
                  case ALLEGRO_KEY_RIGHT:
                        keys[RIGHT] = true;
                        break;
                  case ALLEGRO_KEY_SPACE:
                        keys[SPACE] = true;
                        for(int i=0;i<NUM_SNOWBALLS;i++)
                              snowballs.FireSnowballs(penguinFiring);
                        break;
                  }
            }
            else if(ev.type == ALLEGRO_EVENT_KEY_UP)
            {
                  switch(ev.keyboard.keycode)
                  {
                  case ALLEGRO_KEY_ESCAPE:
                        done = true;
                        break;
                  case ALLEGRO_KEY_UP:
                        keys[UP] = false;
                        break;
                  case ALLEGRO_KEY_DOWN:
                        keys[DOWN] = false;
                        break;
                  case ALLEGRO_KEY_LEFT:
                        keys[LEFT] = false;
                        break;
                  case ALLEGRO_KEY_RIGHT:
                        keys[RIGHT] = false;
                        break;
                  case ALLEGRO_KEY_SPACE:
                        keys[SPACE] = false;
                        break;
                  }
            }
            if(redraw && al_is_event_queue_empty(event_queue))
            {
                  redraw = false;
                  draw background
                  draw iceberg
                  draw penguinFiring
                  draw snowballs
                  draw penguin Dropping
                  al_flip_display();
                  al_clear_to_color(al_map_rgb(0,0,0));
            }
      }

    
}







