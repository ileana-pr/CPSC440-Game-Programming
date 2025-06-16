/*Name: Ileana Perez 
CPSC 440 - Lab 10
*/

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>
#include "sprite.h"
using namespace std;

int main(void)
{
	//variables
	int width = 640;
	int height = 480;
	bool done = false;
	bool redraw = true;
	const int FPS = 60;
	float message_timer = 0;
	bool show_death_message = false;

	//allegro variable
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	sprite alien[5];
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_FONT *font = NULL;

	//program init
	if(!al_init())
	{
		return -1;
	}

	display = al_create_display(width, height);
	if(!display)
	{
		return -1;
	}

	//addon init
	if(!al_install_keyboard())
	{
		return -1;
	}
	
	if(!al_init_image_addon())
	{
		return -1;
	}

	if(!al_init_font_addon() || !al_init_ttf_addon())
	{
		return -1;
	}

	font = al_load_font("GROBOLD.ttf", 36, 0);
	if(!font)
	{
		return -1;
	}

	timer = al_create_timer(1.0 / FPS);
	if(!timer)
	{
		return -1;
	}

	event_queue = al_create_event_queue();
	if(!event_queue)
	{
		return -1;
	}

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_set_target_bitmap(al_get_backbuffer(display));
	al_start_timer(timer);

	//initialize sprites with powers
	for(int i = 0; i < 5; i++)
	{
		// assign one of each power and one random power for the 5th sprite
		if(i < 4) {
			alien[i].setPower(i);  
		}
		else {
			int power = rand() % 4;
			alien[i].setPower(power);
		}
	}

	while(!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			// Update sprite positions first
			for(int i = 0; i < 5; i++)
			{
				if (!alien[i].live) {
					// check if baby sprite died from being too small
					if(alien[i].hasBabyPower()) {
						show_death_message = true;
						message_timer = 0;
					}
					
					alien[i].destroy_images();
					alien[i] = sprite();  
					alien[i].setPower(i < 4 ? i : rand() % 4);
				}
				
				alien[i].updatesprite();
				alien[i].bouncesprite(width,height);
			}

			// update message timer
			if(show_death_message) {
				message_timer += 1.0/FPS;
				if(message_timer >= 2.0) { // show message for 2 seconds
					show_death_message = false;
				}
			}

			redraw = true;
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
			}
		}

		if(redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;
			
			// Clear screen BEFORE drawing
			al_clear_to_color(al_map_rgb(0, 0, 0));
			
			// Check collisions
			for(int i = 0; i < 5; i++)
			{
				alien[i].collision(alien, 5, i, width, height);
			}
			
			// Draw sprites
			for(int i = 0; i < 5; i++)
			{
				alien[i].drawSprite();
			}

			// Draw death message if needed
			if(show_death_message) {
				al_draw_text(font, al_map_rgb(255, 255, 255), width/2, 20, ALLEGRO_ALIGN_CENTER, "banana shrunk to death!");
			}
			
			al_flip_display();
		}
	}

	// Cleanup
	for(int i = 0; i < 5; i++) {
		alien[i].destroy_images();
	}
	al_destroy_font(font);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);

	return 0;
}


