//Name: Ileana Perez 
//Programming assignment 2 
// CPSC 440 

#include <allegro5\allegro.h>
#include <cstdlib> 
#include <iostream>
#include <cstdio>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_native_dialog.h> 
#include "game.h"

using namespace std;


//get_mouse_input: use an if else statement to figure out wat box is being selected  
void get_mouse_input(int &x, int &y);

// draw_objects: given an x and y location, it will draw the appropriate object x and y are the center of the box that was selected; you can draw any object. will call get_shape to figure out which shape is supposed to be drawn. 
void draw_objects(int x, int y);

// get_shape: given an x and y location, it will return the shape that is supposed to be drawn. 
int get_shape(int x, int y);


// draw_octagon: draw the octagon shape
void draw_octagon(int x, int y);

// draw_triangle: draw the triangle shape
void draw_triangle(int x, int y);

// draw_diamond: draw the diamond shape
void draw_diamond(int x, int y);

// draw_rectangle: draw the rectangle shape
void draw_rectangle(int x, int y);

// Draw_Oval: draw the oval shape
void draw_oval(int x, int y);

// Draw_Circle: draw the circle shape
void draw_circle(int x, int y);

// Draw_Grid: draws the 5*5 grid, 
void draw_grid(int x, int y);

// Draw_Status: draws the bottom right hand square that shows the number of pairs remaining and the number of moves made
void draw_status(int x, int y);

// draw_circle: draw the circle shape
void draw_circle(int x, int y);

// draw_square: draw the square shape
void draw_square(int x, int y);


int main(void)
{
    game memory_game;
    bool done = false;
    
    ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_FONT *font = NULL;

    int width = 640;
	int height = 520;

    //init allegro
	if(!al_init()) 
    {
        printf("Error initializing allegro\n");
        return -1;
    }

    //create display
	display = al_create_display(width, height);			//create our display object
	if(!display)		
        printf("Error creating display\n");								//test display object
		return -1;

    //init primitives
	al_init_primitives_addon();

    //init font
    al_init_font_addon();
    al_init_ttf_addon();
    font = al_load_font("GROBOLD.TTF", 16, 0);
    if (!font) return -1;

    //init keyboard
	al_install_keyboard();

    //init mouse
    al_install_mouse();

    //create event queue
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	event_queue = al_create_event_queue();

     //clear to color
    al_register_event_source(event_queue, al_get_display_event_source(display));
	al_clear_to_color(al_map_rgb(0,0,0));

    //register event source
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());


    //create the game board

    // fill the game board with 25 cards 


    while (!done) 
    {
        // During the game play you must keep track of two click patterns. First click must select an object from the selection bar; the second must be on the draw grid.

        //On the first mouse click you must set a global variable indicating the shape (enum type) that was selected

        //On the second mouse click if it is a valid location you will set_shape and the draw_objects


        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            get_mouse_input(ev.mouse.x, ev.mouse.y);
        }









        al_flip_display();
        al_rest(5.0); 
        al_destroy_display(display);
        al_destroy_event_queue(event_queue);
        al_destroy_timer(timer);
        al_destroy_thread(timer_thread);
        al_destroy_font(font);
        
        
        
        
    }
}



