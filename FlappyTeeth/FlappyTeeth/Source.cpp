// Name: Ileana Perez 
// CPSC 340 - Assignment 4

#define _CRT_SECURE_NO_WARNINGS  

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
	
	// scroll speed 
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

	event_queue = al_create_event_queue();
	
	
	al_register_event_source(event_queue, al_get_display_event_source(display));
	
	al_clear_to_color(al_map_rgb(135, 206, 235));
	al_flip_display();
	
	font = al_load_font("GROBOLD.ttf", 24, 0);
	

	// load sprite
	ALLEGRO_BITMAP *sprite = al_load_bitmap("1432472502_chips2.png");
	if(!sprite)
		return -1;
		
	al_lock_bitmap(sprite, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READONLY);
	ALLEGRO_COLOR color = al_get_pixel(sprite, 0, 0);
	unsigned char r, g, b;
	al_unmap_rgb(color, &r, &g, &b);
	al_unlock_bitmap(sprite);
	al_convert_mask_to_alpha(sprite, al_map_rgb(r, g, b));
	
	player.InitSprites(sprite);
	player.SetSpriteParameters(32, 32, 3, 1, 11, 3); // width, height, frames, rows, startRow (0-based), startCol (starting at col 3)

	char* mapPath = (char*)"level1.FMP";
	if(MapLoad(mapPath, 1))
		return -1;

	// total map size in pixels
	const int TOTAL_MAP_WIDTH = mapwidth * mapblockwidth;
	const int TOTAL_MAP_HEIGHT = mapheight * mapblockheight;
	
	if(TOTAL_MAP_WIDTH < WIDTH || TOTAL_MAP_HEIGHT < HEIGHT)
		return -1;

	// near left side
	player.SetPosition(WIDTH/4, HEIGHT/2);

	int xOff = 0;
	int yOff = 0;

	timer = al_create_timer(1.0 / 60);
	if(!timer)
		return -1;

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_start_timer(timer);

	while(!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			render = true;
			
			if(!showEndMessage) {
				MapUpdateAnims();
				
				// check if scrolling would cause collision
				float nextScrollX = scrollX + SCROLL_SPEED;
				bool willCollide = collided(player.getX() + (int)nextScrollX, player.getY()) ||
								 collided(player.getX() + player.getWidth() + (int)nextScrollX, player.getY()) ||
								 collided(player.getX() + (int)nextScrollX, player.getY() + player.getHeight()) ||
								 collided(player.getX() + player.getWidth() + (int)nextScrollX, player.getY() + player.getHeight());
				
				// only scroll if no collision
				if (!willCollide) {
					scrollX = nextScrollX;
					if(scrollX >= TOTAL_MAP_WIDTH - WIDTH) {
						if(currentLevel < 3) {
							currentLevel++;
							scrollX = 0;
							player.SetPosition(WIDTH/4, player.getY());
						} else {
							showEndMessage = true;
						}
					}
				}

				// movement
				if(keys[UP] && player.getY() > 0) {
					player.UpdateSprites(WIDTH, HEIGHT, 0);
					// check collision at both top corners
					if(!collided(player.getX() + xOff, player.getY() - 4) && 
					   !collided(player.getX() + player.getWidth() + xOff, player.getY() - 4))
						player.SetPosition(player.getX(), player.getY() - 4);
				}
				else if(keys[DOWN] && player.getY() < HEIGHT - player.getHeight()) {
					player.UpdateSprites(WIDTH, HEIGHT, 1);
					// check collision at both bottom corners
					if(!collided(player.getX() + xOff, player.getY() + player.getHeight() + 4) &&
					   !collided(player.getX() + player.getWidth() + xOff, player.getY() + player.getHeight() + 4))
						player.SetPosition(player.getX(), player.getY() + 4);
				}
				
				// left/right movement (horizontal only)
				float currentY = player.getY();  // store current Y to maintain it
				if(keys[LEFT] && player.getX() > 0) {
					player.UpdateSprites(WIDTH, HEIGHT, 0);  // animation only
					// check collision at both left corners
					if(!collided(player.getX() - 4 + xOff, currentY) &&
					   !collided(player.getX() - 4 + xOff, currentY + player.getHeight())) {
						player.SetPosition(player.getX() - 4, currentY);  // keep same Y
					}
				}
				else if(keys[RIGHT] && player.getX() < WIDTH - player.getWidth()) {
					player.UpdateSprites(WIDTH, HEIGHT, 1);  // animation only
					// check collision at both right corners
					if(!collided(player.getX() + player.getWidth() + 4 + xOff, currentY) &&
					   !collided(player.getX() + player.getWidth() + 4 + xOff, currentY + player.getHeight())) {
						player.SetPosition(player.getX() + 4, currentY);  // keep same Y
					}
				}

				xOff = (int)scrollX;
				yOff = 0;
			} else {
				endMessageTimer -= 1.0f/60.0f;
				if(endMessageTimer <= 0)
					done = true;
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
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
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
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			}
		}

		if(render && al_is_event_queue_empty(event_queue))
		{
			render = false;
			al_clear_to_color(al_map_rgb(135, 206, 235));

			MapDrawBG(xOff, yOff, 0, 0, WIDTH, HEIGHT);
			MapDrawFG(xOff, yOff, 0, 0, WIDTH, HEIGHT, 0);
			player.DrawSprites(0, 0);

			char levelText[32];
			sprintf(levelText, "Level %d", currentLevel);
			al_draw_text(font, al_map_rgb(255, 255, 255), 10, 10, ALLEGRO_ALIGN_LEFT, levelText);

			if(showEndMessage) {
				al_draw_text(font, al_map_rgb(255, 255, 255), WIDTH/2, HEIGHT/2, 
					ALLEGRO_ALIGN_CENTRE, "Game Over!");
			}

			al_flip_display();
		}
	}

	MapFreeMem();
	al_destroy_font(font);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_bitmap(sprite);

	return 0;
}

// collision detection for teeth vs obstacles/candies
int collided(int x, int y)
{
	BLKSTR *blockdata;
	blockdata = MapGetBlock(x/mapblockwidth, y/mapblockheight);
	if (!blockdata) return 0;
	
	// check if any corner has collision enabled
	return (blockdata->tl || blockdata->tr || blockdata->bl || blockdata->br);
}

// check for end of level condition
bool endValue(int x, int y)
{
	BLKSTR* data;
	data = MapGetBlock(x/mapblockwidth, y/mapblockheight);
	if (!data) return false;
	return data->user1 == 9;  
}