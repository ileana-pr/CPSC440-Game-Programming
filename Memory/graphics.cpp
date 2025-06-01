//Name: Ileana Perez 
//Programming assignment 2 
// CPSC 440 

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_native_dialog.h> 
#include "game.h"


#define FPS 60

//declare game finished 
bool finished = false;
//declare time out for the mismatch timer
bool timeOut = false;
int number_of_moves = 0;
int pairs_found = 0;
int pairs_remaining = 0;

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

// declare the 5 secondcountdown timer
void* countdown_timer(ALLEGRO_THREAD* ptr, void* arg);

int main(void)
{
    //init allegro
	if(!al_init()) return -1;

    game memory_game;

    int width = 640;
	int height = 520;
	bool done = false;

    //declare variables

    ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_FONT *font = NULL;
    al_init_font_addon();
    al_init_ttf_addon();
    font = al_load_font("GROBOLD.TTF", 16, 0);
    if (!font) return -1;

    //program init
	display = al_create_display(width, height);			//create our display object

	if(!display)										//test display object
		return -1;
    //addon init
	al_install_keyboard();
	al_init_primitives_addon();

    //create game objects 


    // create timer
	timer = al_create_timer(1.0 / FPS);

	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_clear_to_color(al_map_rgb(0,0,0));

    // thread to run the countdown timer
	ALLEGRO_THREAD* timer_thread = al_create_thread(countdown_timer, NULL);

    while (!done) 
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        
        
    }
}



