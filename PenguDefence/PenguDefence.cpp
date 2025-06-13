#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <time.h>
#include "iceberg.h"
#include "penguinFiring.h"
#include "snowball.h"
#include "penguinDropping.h"

// The object of the game is to defend your iceberg from dropping penguins by firing snowballs at them. You will use the left and right keys to aim, and the spacebar to fire. If enough penguins land on the iceberg, it will sink. The penguins will drop from the top of the screen, and you will need to fire at them before they reach the iceberg. 

int main(void)
{
    if(!al_init()) return -1;
    if(!al_init_image_addon()) return -1;
    if(!al_init_primitives_addon()) return -1;
    if(!al_init_font_addon()) return -1;
    if(!al_init_ttf_addon()) return -1;
    if(!al_install_keyboard()) return -1;

    srand(time(NULL));

    bool done = false; 
    int width = 640;
    int height = 520;
    int score = 0;
    int FPS = 60;

    ALLEGRO_DISPLAY *display = al_create_display(width, height);
    if (!display) return -1;

    penguinFiring penguinFiring;
    iceberg iceberg;
    const int NUM_PENGUINS = 7;
    snowball snowballs[10];
    penguinDropping droppingPenguins[NUM_PENGUINS];

    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    if (!event_queue) {
        al_destroy_display(display);
        return -1;
    }

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 60);
    if (!timer) {
        al_destroy_display(display);
        al_destroy_event_queue(event_queue);
        return -1;
    }

    ALLEGRO_FONT *font = al_load_font("GROBOLD.TTF", 16, 0);
    if (!font) {
        font = al_create_builtin_font();
        if (!font) {
            al_destroy_display(display);
            al_destroy_event_queue(event_queue);
            al_destroy_timer(timer);
            return -1;
        }
    }

    // register event sources
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));

    // initialize game objects
    iceberg.start_iceberg(width, height);
    penguinFiring.start_penguinFiring(width, height);
    for(int i = 0; i < NUM_PENGUINS; i++) {
        droppingPenguins[i].start_penguinDropping(width, height, iceberg);
    }

    ALLEGRO_BITMAP* background_bmp = al_load_bitmap("background.png");
    if (!background_bmp) {
        background_bmp = al_create_bitmap(width, height);
        al_set_target_bitmap(background_bmp);
        al_clear_to_color(al_map_rgb(135, 206, 235)); 
        al_set_target_bitmap(al_get_backbuffer(display)); 
    }

    al_start_timer(timer);

    bool redraw = true;
    bool keys[5] = {false};
    const int NUM_SNOWBALLS = 10;

    enum KEYS {UP, DOWN, LEFT, RIGHT, SPACE};

    // Initial display flip to show the first frame
    al_clear_to_color(al_map_rgb(0,0,0));
    iceberg.draw_iceberg();
    penguinFiring.draw_penguinFiring();
    al_flip_display();

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

            // Try to spawn new penguins in any available slot
            for(int i = 0; i < NUM_PENGUINS; i++) {
                droppingPenguins[i].start_penguinDropping(width, height, iceberg);
            }

            // Update all penguins
            for(int i = 0; i < NUM_PENGUINS; i++) {
                droppingPenguins[i].update_penguinDropping(iceberg);
            }

            for(int i = 0; i < NUM_SNOWBALLS; i++) {
                snowballs[i].collide_snowball(droppingPenguins, NUM_PENGUINS, penguinFiring);
            }
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
            al_clear_to_color(al_map_rgb(0,0,0));

            // Draw background
            float bg_width = al_get_bitmap_width(background_bmp);
            float bg_height = al_get_bitmap_height(background_bmp);
            float scale_x = width / bg_width;
            float scale_y = height / bg_height;
            float scale = scale_x > scale_y ? scale_x : scale_y;
            
            int scaled_width = bg_width * scale;
            int scaled_height = bg_height * scale;
            int x_offset = (width - scaled_width) / 2;
            int y_offset = (height - scaled_height) / 2;
            
            al_draw_scaled_bitmap(background_bmp, 0, 0, bg_width, bg_height,
                                x_offset, y_offset, scaled_width, scaled_height, 0);

            // Draw game objects
            iceberg.draw_iceberg();
            penguinFiring.draw_penguinFiring();
            
            for(int i = 0; i < NUM_SNOWBALLS; i++) {
                snowballs[i].draw_snowball();
            }
            
            for(int i = 0; i < NUM_PENGUINS; i++) {
                droppingPenguins[i].draw_penguinDropping();
            }

            // Draw score and lives
            al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 10, 0, "Score: %d", penguinFiring.get_score());
            al_flip_display();
        }

        // Check game over 
        if(iceberg.get_lives() <= 0) {
            al_clear_to_color(al_map_rgb(0,0,0));
            al_draw_text(font, al_map_rgb(255, 0, 0), width/2, height/2, ALLEGRO_ALIGN_CENTER, "Game Over!");
            al_draw_textf(font, al_map_rgb(255, 255, 255), width/2, height/2 + 30, ALLEGRO_ALIGN_CENTER, 
                         "Final Score: %d", penguinFiring.get_score());
            al_flip_display();
            al_rest(3.0);
            done = true;
        }
    }

    al_destroy_bitmap(background_bmp);
    al_destroy_font(font);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);

    return 0;
}







