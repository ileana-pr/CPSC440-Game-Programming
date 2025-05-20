#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdlib.h>
#include <time.h> 

ALLEGRO_COLOR makeColor();
void draw_shape(ALLEGRO_COLOR color, const int SCREEN_WIDTH, const int SCREEN_HEIGHT);

int main(int argc, char** argv)
{
	ALLEGRO_DISPLAY* display = NULL;
	int width = 800;
	int height = 600;

	if (!al_init()) {
		fprintf(stderr, "Failed to initialize Allegro!\n");
		return -1;
	}

	display = al_create_display(width, height);
	if (!display) {
		fprintf(stderr, "Failed to create display!\n");
		return -1;
	}

	al_init_primitives_addon();
	srand(time(NULL));
	bool clear = false;

	bool done = false;

	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	al_install_keyboard();

	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();
	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		draw_shape(makeColor(), width, height);

		if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_SPACE:
				clear = true;
				break;
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}

		al_flip_display();
		if (clear == true) {
			al_clear_to_color(al_map_rgb(0, 0, 0));
			clear = false;
		}
	}

	al_destroy_event_queue(event_queue);
	al_destroy_display(display);

	return 0;
}

ALLEGRO_COLOR makeColor() {
	int red = rand() % 255;
	int green = rand() % 255;
	int blue = rand() % 255;
	return al_map_rgb(red, green, blue);
}

void draw_shape(ALLEGRO_COLOR color, const int SCREEN_W, const int SCREEN_H) {
	// Main floor location and size for the house
	int baseX = 300;
	int baseY = 400;
	int width = 200;
	int height = 150;
	float thickness = 2.0;

	// Draw base using lines  
	al_draw_line(baseX, baseY, baseX + width, baseY, color, thickness); // bottom
	al_draw_line(baseX, baseY - height, baseX + width, baseY - height, color, thickness); // top
	al_draw_line(baseX, baseY, baseX, baseY - height, color, thickness); // left
	al_draw_line(baseX + width, baseY, baseX + width, baseY - height, color, thickness); // right

	// Roof 
	int roofPeakY = baseY - height - 80;
	al_draw_line(baseX - 20, baseY - height, baseX + width + 20, baseY - height, color, thickness); // base
	al_draw_line(baseX - 20, baseY - height, baseX + width / 2, roofPeakY, color, thickness);         // left side
	al_draw_line(baseX + width + 20, baseY - height, baseX + width / 2, roofPeakY, color, thickness); // right side

	// Draw door
	int doorWidth = 40;
	int doorHeight = 70;
	int doorX = baseX + width / 2 - doorWidth / 2;
	int doorY = baseY - doorHeight;
	al_draw_filled_rectangle(doorX, doorY, doorX + doorWidth, doorY + doorHeight, color);

}


