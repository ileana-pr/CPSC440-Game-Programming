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

void get_mouse_input(int &x, int &y);
void handle_card_click(int row, int col, game &memory, ALLEGRO_FONT *font);
void draw_shape(int x, int y, int shape_type);
void draw_x_marks(game &memory);
int get_shape(int x, int y);
void draw_octagon(int x, int y);
void draw_triangle(int x, int y);
void draw_diamond(int x, int y);
void draw_rectangle(int x, int y);
void draw_oval(int x, int y);
void draw_circle(int x, int y);
void draw_grid();
void draw_square(int x, int y);

void draw_status(game &memory, ALLEGRO_FONT *font);


int main(void)
{
    game memory;
    bool done = false;
    
    ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_FONT *font = NULL;

    int width = 640;
	int height = 520;

    if(!al_init()) 
    {
        printf("Error initializing allegro\n");
        return -1;
    }

    display = al_create_display(width, height);		
    if(!display)		
    {
        printf("Error creating display\n");								
        return -1;
    }

    if (!al_init_primitives_addon()) {
        printf("Error initializing primitives\n");
        return -1;
    }

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
        printf("Error loading font\n");
        return -1;
    }

    if (!al_install_keyboard()) {
        printf("Error installing keyboard\n");
        return -1;
    }

    if (!al_install_mouse()) {
        printf("Error installing mouse\n");
        return -1;
    }

    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	event_queue = al_create_event_queue();

    al_register_event_source(event_queue, al_get_display_event_source(display));
	al_clear_to_color(al_map_rgb(0,0,0));

    al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());

    memory.setup();
    draw_grid();
    draw_status(memory, font);
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
                handle_card_click(mouse_y, mouse_x, memory, font);
                
                // check if game over 
                if (memory.game_over(memory.get_pairs_remaining())) {
                    al_clear_to_color(al_map_rgb(0,0,0));
                    draw_grid();
                    
                    // draw X on all matched cards 
                    draw_x_marks(memory);
                    
                    // display win message
                    if (font) {
                        al_draw_text(font, al_map_rgb(255, 255, 255), 320, 250, ALLEGRO_ALIGN_CENTER, "congratulations! you won!");
                        al_draw_text(font, al_map_rgb(255, 255, 255), 320, 270, ALLEGRO_ALIGN_CENTER, "press escape to exit");
                    }
                    draw_status(memory, font);
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

// get mouse input: wait for user to click on the game board and make a selection 
// @param x: the x coordinate of the mouse
// @param y: the y coordinate of the mouse
// @return: the grid coordinates of the mouse
void get_mouse_input(int &x, int &y)
{
    if (x >= 0 && x < 640 && y >= 0 && y < 520) {
        int col = x / 128; 
        int row = y / 104;   
        
        x = col;
        y = row;
    }
}

// draw the 5*5 grid 
void draw_grid()
{
    al_draw_line(0, 0, 0, 520, al_map_rgb(255, 255, 255), 2);     // left edge
    al_draw_line(128, 0, 128, 520, al_map_rgb(255, 255, 255), 2); // column 1
    al_draw_line(256, 0, 256, 520, al_map_rgb(255, 255, 255), 2); // column 2  
    al_draw_line(384, 0, 384, 520, al_map_rgb(255, 255, 255), 2); // column 3
    al_draw_line(512, 0, 512, 520, al_map_rgb(255, 255, 255), 2); // column 4
    al_draw_line(640, 0, 640, 520, al_map_rgb(255, 255, 255), 2); // right edge
    
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

void draw_filled_triangle(int x, int y)
{
    al_draw_filled_triangle(x, y - 25, x - 25, y + 20, x + 25, y + 20, al_map_rgb(100, 255, 100));
}

void draw_outlined_rectangle(int x, int y)
{
    al_draw_rectangle(x - 25, y - 20, x + 25, y + 20, al_map_rgb(100, 100, 255), 3);
}

void draw_outlined_circle(int x, int y)
{
    al_draw_circle(x, y, 25, al_map_rgb(255, 100, 100), 3);
}

void draw_filled_diamond(int x, int y)
{
    al_draw_filled_triangle(x, y - 25, x - 25, y, x, y + 25, al_map_rgb(255, 255, 100));
    al_draw_filled_triangle(x, y - 25, x + 25, y, x, y + 25, al_map_rgb(255, 255, 100));
}

void draw_outlined_oval(int x, int y)
{
    al_draw_ellipse(x, y, 30, 20, al_map_rgb(255, 150, 255), 3);
}

void draw_filled_octagon(int x, int y)
{
    al_draw_filled_rectangle(x - 20, y - 25, x + 20, y + 25, al_map_rgb(150, 255, 150));
    al_draw_filled_rectangle(x - 25, y - 20, x + 25, y + 20, al_map_rgb(150, 255, 150));
}

// draw X marks on all matched cards
// @param memory: the game object
void draw_x_marks(game &memory)
{
    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) {
            if (memory.is_card_matched(r, c)) {
                int center_x = c * 128 + 64;
                int center_y = r * 104 + 52;
                al_draw_line(center_x - 30, center_y - 30, center_x + 30, center_y + 30, al_map_rgb(255, 0, 0), 4);
                al_draw_line(center_x - 30, center_y + 30, center_x + 30, center_y - 30, al_map_rgb(255, 0, 0), 4);
            }
        }
    }
}

// handle card click: handle the card click 
// @param row: the row of the card
// @param col: the column of the card
// @param memory: the game object
// @param font: the font object
void handle_card_click(int row, int col, game &memory, ALLEGRO_FONT *font)
{
    if (!memory.is_first_card_flipped()) {
        if (memory.flip_first_card(row, col)) {
            al_clear_to_color(al_map_rgb(0,0,0));
            draw_grid();
            
            draw_x_marks(memory);
            // draw the cards that are not matched
            for (int r = 0; r < 5; r++) {
                for (int c = 0; c < 5; c++) {
                    if (memory.is_card_revealed(r, c) && !memory.is_card_matched(r, c)) {
                        int center_x = c * 128 + 64;
                        int center_y = r * 104 + 52;
                        int shape = memory.get_shape(r, c);
                        draw_shape(center_x, center_y, shape);
                    }
                }
            }
            draw_status(memory, font);
            al_flip_display();
        }
    } else {
        bool match_found = memory.flip_second_card(row, col);
        
        al_clear_to_color(al_map_rgb(0,0,0));
        draw_grid();
        
        draw_x_marks(memory);
        // draw the cards that are not matched
        for (int r = 0; r < 5; r++) {
            for (int c = 0; c < 5; c++) {
                if (memory.is_card_revealed(r, c) && !memory.is_card_matched(r, c)) {
                    int center_x = c * 128 + 64;
                    int center_y = r * 104 + 52;
                    int shape = memory.get_shape(r, c);
                    draw_shape(center_x, center_y, shape);
                }
            }
        }
        draw_status(memory, font);
        al_flip_display();
        
        if (!match_found) {
            al_rest(2.0);
            memory.hide_mismatched_cards();
            al_clear_to_color(al_map_rgb(0,0,0));
            draw_grid();
            draw_x_marks(memory);
            draw_status(memory, font);
            al_flip_display();
        }
    }
}

// draw shapes based on type
// @param x: the x coordinate of the shape
// @param y: the y coordinate of the shape
// @param shape_type: the type of shape to draw
void draw_shape(int x, int y, int shape_type) {
    switch(shape_type) {
        case 1:  // filled circle
            draw_circle(x, y);
            break;
        case 2:  // outlined triangle  
            draw_triangle(x, y);
            break;
        case 3:  // filled rectangle
            draw_rectangle(x, y);
            break;
        case 4:  // outlined diamond
            draw_diamond(x, y);
            break;
        case 5:  // filled oval
            draw_oval(x, y);
            break;
        case 6:  // outlined octagon
            draw_octagon(x, y);
            break;
        case 7:  // outlined circle (pair of 1)
            draw_outlined_circle(x, y);
            break;
        case 8:  // filled triangle (pair of 2)
            draw_filled_triangle(x, y);
            break;
        case 9:  // outlined rectangle (pair of 3)
            draw_outlined_rectangle(x, y);
            break;
        case 10: // filled diamond (pair of 4)
            draw_filled_diamond(x, y);
            break;
        case 11: // outlined oval (pair of 5)
            draw_outlined_oval(x, y);
            break;
        case 12: // filled octagon (pair of 6)
            draw_filled_octagon(x, y);
            break;
        default:
            break;
    }
}

// bottom right hand square that shows the number of pairs remaining and the number of moves made
// @param memory: the game object
// @param font: the font object
void draw_status(game &memory, ALLEGRO_FONT *font)
{
    int status_x = 512;
    int status_y = 416;
    int status_width = 128;
    int status_height = 104;
    
    al_draw_filled_rectangle(status_x, status_y, status_x + status_width, status_y + status_height, al_map_rgb(40, 40, 40));
    
    if (font) {
        al_draw_text(font, al_map_rgb(255, 255, 255), status_x + 3, status_y + 5, 0, "MEMORY");
        
        char moves_text[32];
        sprintf_s(moves_text, sizeof(moves_text), "moves: %d", memory.get_number_of_moves());
        al_draw_text(font, al_map_rgb(255, 255, 255), status_x + 5, status_y + 25, 0, moves_text);
        
        char pairs_found_text[32];
        sprintf_s(pairs_found_text, sizeof(pairs_found_text), "found: %d", memory.get_pairs_found());
        al_draw_text(font, al_map_rgb(255, 255, 255), status_x + 5, status_y + 45, 0, pairs_found_text);
        
        char pairs_left_text[32];
        sprintf_s(pairs_left_text, sizeof(pairs_left_text), "left: %d", memory.get_pairs_remaining());
        al_draw_text(font, al_map_rgb(255, 255, 255), status_x + 5, status_y + 65, 0, pairs_left_text);
    }
}

