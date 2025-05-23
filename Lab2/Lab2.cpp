#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>			
#include <allegro5/allegro_native_dialog.h> 

int main(void)
{
	ALLEGRO_DISPLAY* Screen = NULL;

	if (!al_init())
	{
		al_show_native_message_box(NULL, "Error!", "Allegro has failed to initialize.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	int width = 800, height = 600;
	Screen = al_create_display(width, height);
	if (Screen == NULL)
	{
		al_show_native_message_box(Screen, "Error!", "Failed to create the display.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	bool done = false;
	int pos_x = width / 2;
	int pos_y = height / 2;

	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_EVENT ev;

	al_init_primitives_addon();
	al_install_keyboard();

	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_keyboard_event_source());

	while (!done)
	{

		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				pos_y -= 30;
				break;
			case ALLEGRO_KEY_DOWN:
				pos_y += 30;
				break;
			case ALLEGRO_KEY_RIGHT:
				pos_x += 30;
				break;
			case ALLEGRO_KEY_LEFT:
				pos_x -= 30;
				break;
			case ALLEGRO_KEY_U: // upper left
				pos_x -= 30; 
				pos_y -= 30;
				break;
			case ALLEGRO_KEY_D: // lower right 
				pos_x += 30; 
				pos_y += 30;
				break;
			case ALLEGRO_KEY_R: // upper right
				pos_x += 30;
				pos_y -= 30;
				break;
			case ALLEGRO_KEY_L: // lower left
				pos_x -= 30;
				pos_y += 30;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
				done = true;
		}

		// Smiley face
		float center_x = pos_x;  
		float center_y = pos_y;
		float radius = 75.0;         

		// circle
		al_draw_filled_circle(center_x, center_y, radius, al_map_rgb(255, 255, 0)); 
		
		// eyes
		al_draw_line(center_x - 25, center_y - 25, center_x - 10, center_y - 10, al_map_rgb(0, 0, 0), 10);  
		al_draw_line(center_x + 10, center_y - 10, center_x + 25, center_y - 25, al_map_rgb(0, 0, 0), 10);  
		
		// mouth 
		al_draw_line(center_x - 25, center_y + 25, center_x + 25, center_y + 25, al_map_rgb(0, 0, 0), 10);

		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}

	al_destroy_event_queue(event_queue);
	al_destroy_display(Screen);					
	system("pause");
	return 0;
}