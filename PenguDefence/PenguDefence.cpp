#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "iceberg.h"
#include "penguinFiring.h"
#include "snowball.h"
#include "penguinDropping.h"


// The object of the game is to defend your iceberg from dropping penguins by firing snowballs at them. You will use the left and right keys to aim, and the spacebar to fire. If enough penguins land on the iceberg, it will sink. The penguins will drop from the top of the screen, and you will need to fire at them before they reach the iceberg. 



int main(void)
{
     // initialize allegro
    if(!al_init()) return -1;

    al_init_image_addon();

    bool done = false; 
    int width = 640;
    int height = 520;
    int score = 0;
    int FPS = 60;

    penguinFiring penguinFiring;
    iceberg iceberg;
    const int NUM_PENGUINS = 5;
    snowball snowballs[10];
    penguinDropping droppingPenguins[NUM_PENGUINS];
   
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
    al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

    
    // create the iceberg
    iceberg.start_iceberg(width, height);
    // create the penguinFiring
    penguinFiring.start_penguinFiring(width, height);
    // create the snowballs
    for(int i = 0; i < 10; i++) {
        snowballs[i].fire_snowball(penguinFiring);
    }
    // create the penguinDropping
    for(int i = 0; i < NUM_PENGUINS; i++) {
        droppingPenguins[i].start_penguinDropping(width, height);
    }

    ALLEGRO_BITMAP* background_bmp = al_create_bitmap(width, height);
    al_set_target_bitmap(background_bmp);
    al_clear_to_color(al_map_rgb(0, 0, 0));

    //draw snowball 
    for(int i = 0; i < 10; i++) {
        snowballs[i].draw_snowball();
    }
    al_flip_display();

    al_start_timer(timer);


    bool redraw = false;
    bool keys[5] = {false};
    const int NUM_SNOWBALLS = 10;

    enum KEYS {UP, DOWN, LEFT, RIGHT, SPACE};

     while(!done)
      {
            ALLEGRO_EVENT ev;
            al_wait_for_event(event_queue, &ev);
            if(ev.type == ALLEGRO_EVENT_TIMER)
            {
                  redraw = true;
                  if(keys[LEFT])
                        penguinFiring.rotate_left();
                  if(keys[RIGHT])
                        penguinFiring.rotate_right();
                  for(int i = 0; i < NUM_SNOWBALLS; i++) {
                        snowballs[i].update_snowball(width, height);
                  }
                  penguinFiring.update_penguinFiring();

                  //Start and Update Penguins
                  for(int i = 0; i < NUM_PENGUINS; i++) {
                      droppingPenguins[i].update_penguinDropping();
                  }

                  //Collide Snowballs with Penguins
                  for(int i = 0; i < NUM_SNOWBALLS; i++) {
                        snowballs[i].collide_snowball(droppingPenguins, NUM_PENGUINS, penguinFiring);
                  }

                  //Collide Penguins with Iceberg
                  for(int i = 0; i < NUM_PENGUINS; i++) {
                      droppingPenguins[i].collide_penguinDropping(iceberg);
                  }

                  penguinFiring.collide_penguinFiring(iceberg);
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
                        for(int i = 0; i < NUM_SNOWBALLS; i++) {
                              if(!snowballs[i].is_live()) {
                                    snowballs[i].fire_snowball(penguinFiring);
                                    break;
                              }
                        }
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
                  al_draw_bitmap(background_bmp, 0, 0, 0);
                  iceberg.draw_iceberg();
                  penguinFiring.draw_penguinFiring();
                  for(int i = 0; i < NUM_SNOWBALLS; i++) {
                        snowballs[i].draw_snowball();
                  }
                  for(int i = 0; i < NUM_PENGUINS; i++) {
                        droppingPenguins[i].draw_penguinDropping();
                  }
                  al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 10, 0, "Score: %d", penguinFiring.get_score());
                  al_flip_display();
                  al_clear_to_color(al_map_rgb(0,0,0));
            }
            if(iceberg.get_lives() <= 0) {
                done = true;
            }
      }

    
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    al_destroy_font(font);
    al_destroy_bitmap(background_bmp);

   
}







