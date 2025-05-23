#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>			
#include <allegro5/allegro_native_dialog.h> 
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>

void drawShape(float center_x, float center_y, float radius) {
	// circle
	al_draw_filled_circle(center_x, center_y, radius, al_map_rgb(255, 255, 0));
	// eyes
	al_draw_line(center_x - 25, center_y - 25, center_x - 10, center_y - 10, al_map_rgb(0, 0, 0), 10);
	al_draw_line(center_x + 10, center_y - 10, center_x + 25, center_y - 25, al_map_rgb(0, 0, 0), 10);
	// mouth
	al_draw_line(center_x - 25, center_y + 25, center_x + 25, center_y + 25, al_map_rgb(0, 0, 0), 10);
}

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

	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_EVENT ev;

	event_queue = al_create_event_queue();
	if (event_queue == NULL)
	{
		al_show_native_message_box(Screen, "Error!", "Failed to create the event queue.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	if (!al_install_mouse()) {
		al_show_native_message_box(Screen, "Error!", "Failed to install the mouse.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(Screen));
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	ALLEGRO_FONT* font24 = al_load_font("AppleGaramond.ttf", 24, 0);
	ALLEGRO_FONT* font63 = al_load_font("Bombing.ttf", 63, 0);

	bool done = false;
	bool draw = false;
	int pos_x = width / 2;
	int pos_y = height / 2;

	while (!done)
	{
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (ev.mouse.button & 1)  // Left mouse button
			{
				draw = true;
				pos_x = ev.mouse.x;
				pos_y = ev.mouse.y;
			}
		}

		if (draw) {
			// Set background and text color based on quadrant
			ALLEGRO_COLOR bg_color, text_color;
			if (pos_x < width / 2 && pos_y < height / 2) {
				// upper left
				bg_color = al_map_rgb(255, 255, 255); // white
				text_color = al_map_rgb(0, 0, 0);     // black
			} else if (pos_x >= width / 2 && pos_y < height / 2) {
				// upper right
				bg_color = al_map_rgb(0, 0, 0);       // black
				text_color = al_map_rgb(255, 255, 255); // white
			} else if (pos_x < width / 2 && pos_y >= height / 2) {
				// lower left
				bg_color = al_map_rgb(0, 0, 255);     // blue
				text_color = al_map_rgb(255, 255, 0); // yellow
			} else {
				// lower right
				bg_color = al_map_rgb(255, 255, 0);   // yellow
				text_color = al_map_rgb(0, 0, 255);   // blue
			}
			al_clear_to_color(bg_color);
			drawShape(pos_x, pos_y, 75.0);
			char coords[50];
			sprintf_s(coords, "Mouse is at (%d, %d)", pos_x, pos_y);
			al_draw_text(font24, text_color, 10, 10, ALLEGRO_ALIGN_LEFT, coords);
			al_flip_display();
			draw = false;
		}
	}

	al_destroy_event_queue(event_queue);
	al_destroy_display(Screen);
	return 0;
}