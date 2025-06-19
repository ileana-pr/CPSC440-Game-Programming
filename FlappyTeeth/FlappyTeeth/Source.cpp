// Name: Ileana Perez 
// CPSC 340 - Assignment 4

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "SpriteSheet.h"
#include "mappy_A5.h"
#include <iostream>
using namespace std;

int main(void)
{
	const int WIDTH = 900;
	const int HEIGHT = 480;
	bool keys[] = {false, false, false, false, false};
	enum KEYS{UP, DOWN, LEFT, RIGHT, SPACE};
	bool done = false;
	bool render = false;
	int currentLevel = 1;
	
	// scroll speed (pixels per frame)
	const float SCROLL_SPEED = 2.0f;
	float scrollX = 0;

	bool showEndMessage = false;
	float endMessageTimer = 5.0f;
	Sprite player;
	
	ALLEGRO_FONT* font = NULL;
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer;

	if(!al_init())										
		return -1;

	display = al_create_display(WIDTH, HEIGHT);			

	if(!display)										
		return -1;

	al_install_keyboard();
	al_init_image_addon();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	
	font = al_load_font("GROBOLD.ttf", 24, 0);
	if (!font) {
		cout << "Failed to load font!" << endl;
		return -1;
	}

	//load sprite sheet
	ALLEGRO_BITMAP *sprite = al_load_bitmap("guy.png");
	if (!sprite) {
		cout << "Failed to load guy.png!" << endl;
		return -1;
	}
	player.InitSprites(sprite);
	cout << "Loading map..." << endl;
	if(MapLoad("level1.FMP", 1)) {
		cout << "Failed to load map!" << endl;
		return -5;
	}
	cout << "Map loaded" << endl;
	cout << "Map dimensions: " << mapwidth << "x" << mapheight << " blocks of " << mapblockwidth << "x" << mapblockheight << " pixels" << endl;
	
	// total map size in pixels
	const int TOTAL_MAP_WIDTH = mapwidth * mapblockwidth;
	const int TOTAL_MAP_HEIGHT = mapheight * mapblockheight;
	
	cout << "Total map size in pixels: " << TOTAL_MAP_WIDTH << "x" << TOTAL_MAP_HEIGHT << endl;
	
	if (TOTAL_MAP_WIDTH < WIDTH || TOTAL_MAP_HEIGHT < HEIGHT) {
		cout << "Error: Map is smaller than screen size!" << endl;
		return -6;
	}

	// start near left side
	player.SetPosition(WIDTH/4, HEIGHT/2);

	int xOff = 0;
	int yOff = 0;

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_start_timer(timer);
	
	while(!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			render = true;
			
			// update game state if not showing end message
			if(!showEndMessage) {
				MapUpdateAnims();
				
				// scroll the map
				scrollX += SCROLL_SPEED;
				if(scrollX >= TOTAL_MAP_WIDTH - WIDTH) {
					// Player reached the end of the map
					if(currentLevel < 3) {
						currentLevel++;
						scrollX = 0;
						player.SetPosition(WIDTH/4, player.getY());
					} else {
						showEndMessage = true;
					}
				}

				// movement - only up and down
				if(keys[UP] && player.getY() > 0)
					player.UpdateSprites(WIDTH, HEIGHT, 0);
				else if(keys[DOWN] && player.getY() < HEIGHT - player.getHeight())
					player.UpdateSprites(WIDTH, HEIGHT, 1);

				// set map offset based on scroll position
				xOff = (int)scrollX;
				yOff = 0;  // no vertical scrolling
			} else {
				// end message timer
				endMessageTimer -= 1.0f/60.0f;
				if(endMessageTimer <= 0) {
					done = true;
				}
			}
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
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			}
		}

		if(render && al_is_event_queue_empty(event_queue))
		{
			render = false;

			// game state
			MapDrawBG(xOff, yOff, 0, 0, WIDTH, HEIGHT);
			MapDrawFG(xOff, yOff, 0, 0, WIDTH, HEIGHT, 0);
			player.DrawSprites(0, 0);  
			// level info
			char levelText[32];
			sprintf(levelText, "Level %d", currentLevel);
			al_draw_text(font, al_map_rgb(255, 255, 255), 10, 10, ALLEGRO_ALIGN_LEFT, levelText);

			// end game message
			if(showEndMessage) {
				al_draw_text(font, al_map_rgb(255, 215, 0), WIDTH/2, HEIGHT/2 - 30, ALLEGRO_ALIGN_CENTER, "CONGRATULATIONS!");
				al_draw_text(font, al_map_rgb(255, 215, 0), WIDTH/2, HEIGHT/2 + 10, ALLEGRO_ALIGN_CENTER, "You've completed all levels!");
			}
			
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}
	}

	// Cleanup
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_font(font);
	al_destroy_bitmap(sprite);
	MapFreeMem();
	
	return 0;
}
