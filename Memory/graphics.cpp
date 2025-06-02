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

// handle card click with graphics logic
void handle_card_click(int row, int col, game &memory);

// helper function to draw shapes
void draw_shape(int x, int y, int shape_type);

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
    game memory;
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
    memory.setup();
    draw_grid();
    al_flip_display();

    while (!done) 
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            done = true;
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                done = true;
            }
        }
        else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            int mouse_x = ev.mouse.x;
            int mouse_y = ev.mouse.y;
            get_mouse_input(mouse_x, mouse_y);
            
            // check valid grid position 
            if (mouse_x >= 0 && mouse_y >= 0) {
                // handle the card click first
                handle_card_click(mouse_y, mouse_x, memory);
                
                // then check if game is over after this move
                if (memory.game_over(memory.get_pairs_remaining())) {
                    // show win message
                    al_clear_to_color(al_map_rgb(0,0,0));
                    draw_grid();
                    
                   
                    al_flip_display();
                }
            }
        }
    }

    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    al_destroy_font(font);
    
    return 0;
}



// get_mouse_input 
void get_mouse_input(int &x, int &y)
{
    // convert mouse coordinates to grid position
    if (x >= 0 && x < 640 && y >= 0 && y < 520) {
        // convert to grid coordinates (0-4)
        int col = x / 128;  // 640 / 5 = 128 
        int row = y / 104;  // 520 / 5 = 104 
        
        // return grid coordinates
        x = col;
        y = row;
    }
}


// get_shape: given an x and y location, it will return the shape that is supposed to be drawn. 
// draw_objects: given an x and y location, it will draw the appropriate object x and y are the center of the box that was selected; you can draw any object. will call get_shape to figure out which shape is supposed to be drawn. 
void draw_objects(int x, int y);

void draw_grid()
{
    // full screen grid - 640x520 divided into 5x5 = 128x104 cells
    // vertical lines
    al_draw_line(0, 0, 0, 520, al_map_rgb(255, 255, 255), 2);     // left edge
    al_draw_line(128, 0, 128, 520, al_map_rgb(255, 255, 255), 2); // column 1
    al_draw_line(256, 0, 256, 520, al_map_rgb(255, 255, 255), 2); // column 2  
    al_draw_line(384, 0, 384, 520, al_map_rgb(255, 255, 255), 2); // column 3
    al_draw_line(512, 0, 512, 520, al_map_rgb(255, 255, 255), 2); // column 4
    al_draw_line(640, 0, 640, 520, al_map_rgb(255, 255, 255), 2); // right edge
    
    // horizontal lines
    al_draw_line(0, 0, 640, 0, al_map_rgb(255, 255, 255), 2);     // top edge
    al_draw_line(0, 104, 640, 104, al_map_rgb(255, 255, 255), 2); // row 1
    al_draw_line(0, 208, 640, 208, al_map_rgb(255, 255, 255), 2); // row 2
    al_draw_line(0, 312, 640, 312, al_map_rgb(255, 255, 255), 2); // row 3
    al_draw_line(0, 416, 640, 416, al_map_rgb(255, 255, 255), 2); // row 4
    al_draw_line(0, 520, 640, 520, al_map_rgb(255, 255, 255), 2); // bottom edge
}

void draw_circle(int x, int y)
{
    al_draw_filled_circle(x, y, 25, al_map_rgb(255, 100, 100));
}

void draw_triangle(int x, int y)
{
    al_draw_triangle(x, y - 25, x - 25, y + 20, x + 25, y + 20, al_map_rgb(100, 255, 100), 3);
}

void draw_rectangle(int x, int y)
{
    al_draw_filled_rectangle(x - 25, y - 20, x + 25, y + 20, al_map_rgb(100, 100, 255));
}

void draw_diamond(int x, int y)
{
    al_draw_triangle(x, y - 25, x - 25, y, x, y + 25, al_map_rgb(255, 255, 100), 3);
    al_draw_triangle(x, y - 25, x + 25, y, x, y + 25, al_map_rgb(255, 255, 100), 3);
}

void draw_oval(int x, int y)
{
    al_draw_filled_ellipse(x, y, 30, 20, al_map_rgb(255, 150, 255));
}

void draw_octagon(int x, int y)
{
    al_draw_rectangle(x - 20, y - 25, x + 20, y + 25, al_map_rgb(150, 255, 150), 3);
    al_draw_rectangle(x - 25, y - 20, x + 25, y + 20, al_map_rgb(150, 255, 150), 3);
}


// draw shapes based on type
void draw_shape(int x, int y, int shape_type) {
    switch(shape_type) {
        case 1: case 7:  // circle pairs
            draw_circle(x, y);
            break;
        case 2: case 8:  // triangle pairs  
            draw_triangle(x, y);
            break;
        case 3: case 9:  // rectangle pairs
            draw_rectangle(x, y);
            break;
        case 4: case 10: // diamond pairs
            draw_diamond(x, y);
            break;
        case 5: case 11: // oval pairs
            draw_oval(x, y);
            break;
        case 6: case 12: // octagon pairs
            draw_octagon(x, y);
            break;
        default:
            // empty space - do nothing
            break;
    }
}

