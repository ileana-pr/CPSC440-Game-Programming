#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include "sprite.h"
using namespace std;

void setPower(sprite& s, int power) {
	for(int i = 0; i < 4; i++) s.specialtyPower[i] = false;
	s.specialtyPower[power] = true;
}

int main(void)
{
	//variables
	int width = 640;
	int height = 480;
	bool done = false;
	bool redraw = true;
	const int FPS = 60;

	//allegro variable
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	sprite alien[5];
	ALLEGRO_TIMER *timer = NULL;

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
		;
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

	//load sprites
	bool all_sprites_loaded = true;
	for(int i = 0; i < 5; i++)
	{
		if(!alien[i].load_animated_sprite(8))
		{
			
			all_sprites_loaded = false;
			break;
		}
		
		// For first 3 sprites, assign one of each power
		if(i < 3) {
			setPower(alien[i], i + 1);  // powers are 1=scared, 2=baby, 3=freeze
			
		}
		// For remaining sprites, use random power
		else {
			int power = (rand() % 3) + 1;
			setPower(alien[i], power);
			
		}
	}

	if(!all_sprites_loaded)
	{
		
		al_destroy_timer(timer);
		al_destroy_event_queue(event_queue);
		al_destroy_display(display);
		return -1;
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
					alien[i].destroy_images();
					alien[i] = sprite();  
					alien[i].live = true;
					alien[i].collisionIsTrue = false;
					alien[i].collisionTime = 0;
					if (!alien[i].load_animated_sprite(8)) {
						alien[i].live = false;
					}
				}
				
				alien[i].updatesprite();
				alien[i].bouncesprite(width,height);
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
			
			al_flip_display();
		}
	}

	// Cleanup
	for(int i = 0; i < 5; i++) {
		alien[i].destroy_images();
	}
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);

	return 0;
}


