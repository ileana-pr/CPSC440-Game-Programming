//Name: Ileana Perez 
//Programming assignment 2 
// CPSC 440 

// the object of the game is to find all the pairs of cards in the least number of moves 

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


// get mouse input: wait for user to click on the game board and make a selection 
void get_mouse_input(int &x, int &y);

// draw_objects: given an x and y location, it will draw the appropriate object x and y are the center of the box that was selected; you can draw any object. will call get_shape to figure out which shape is supposed to be drawn. 
void draw_objects(int x, int y);

// when the user clicks on the game board get the shape that is being clicked on  
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
void draw_grid();

// Draw_Status: draws the bottom right hand square that shows the number of pairs remaining and the number of moves made
void draw_status();

// draw_selection_bar: draws the selection bar

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
    {
        printf("Error creating display\n");								//test display object
        return -1;
    }

    //init primitives
    if (!al_init_primitives_addon()) {
        printf("Error initializing primitives\n");
        return -1;
    }

    //init font
    if (!al_init_font_addon()) {
        printf("Error initializing font addon\n");
        return -1;
    }
    if (!al_init_ttf_addon()) {
        printf("Error initializing ttf addon\n");
        return -1;
    }
    
    font = al_load_font("GROBOLD.ttf", 16, 0);
    if (!font) {
        printf("Error loading font - trying built-in font\n");
        font = al_create_builtin_font();
        if (!font) {
            printf("Error creating built-in font\n");
            return -1;
        }
    }

    //init keyboard
    if (!al_install_keyboard()) {
        printf("Error installing keyboard\n");
        return -1;
    }

    //init mouse
    if (!al_install_mouse()) {
        printf("Error installing mouse\n");
        return -1;
    }

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

    // initialize game and draw initial grid
    memory_game.setup();
    draw_grid();
    al_flip_display();

    while (!done) 
    {

        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            get_mouse_input(ev.mouse.x, ev.mouse.y);
        }

        // if first click flip card 
        // if second click: flip card, IF the shape is valid, X out both cards, and reset the click pattern,increase the number of pairs found, decrease number of pairs remaining, if not valid, reset the click pattern 

        // if the number of pairs remaining is 0, end the game 












        al_flip_display();
        al_rest(5.0); 
        al_destroy_display(display);
        al_destroy_event_queue(event_queue);
        al_destroy_timer(timer);
        al_destroy_font(font);
        
        
        
        
    }
}



// get_mouse_input: use an if else statement to figure out wat box is being selected  
void get_mouse_input(int &x, int &y)
{
    // placeholder implementation - just store the coordinates
    // will implement grid mapping later
}


// get_shape: given an x and y location, it will return the shape that is supposed to be drawn. 
// draw_objects: given an x and y location, it will draw the appropriate object x and y are the center of the box that was selected; you can draw any object. will call get_shape to figure out which shape is supposed to be drawn. 
void draw_objects(int x, int y);

void draw_grid()
{
    // vertical lines
    al_draw_line(50, 50, 50, 450, al_map_rgb(255, 255, 255), 2);   // left edge
    al_draw_line(130, 50, 130, 450, al_map_rgb(255, 255, 255), 2); // column 1
    al_draw_line(210, 50, 210, 450, al_map_rgb(255, 255, 255), 2); // column 2  
    al_draw_line(290, 50, 290, 450, al_map_rgb(255, 255, 255), 2); // column 3
    al_draw_line(370, 50, 370, 450, al_map_rgb(255, 255, 255), 2); // column 4
    al_draw_line(450, 50, 450, 450, al_map_rgb(255, 255, 255), 2); // right edge
    
    // horizontal lines
    al_draw_line(50, 50, 450, 50, al_map_rgb(255, 255, 255), 2);   // top edge
    al_draw_line(50, 130, 450, 130, al_map_rgb(255, 255, 255), 2); // row 1
    al_draw_line(50, 210, 450, 210, al_map_rgb(255, 255, 255), 2); // row 2
    al_draw_line(50, 290, 450, 290, al_map_rgb(255, 255, 255), 2); // row 3
    al_draw_line(50, 370, 450, 370, al_map_rgb(255, 255, 255), 2); // row 4
    al_draw_line(50, 450, 450, 450, al_map_rgb(255, 255, 255), 2); // bottom edge
}


