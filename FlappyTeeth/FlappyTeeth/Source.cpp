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

int collided(int x, int y);
bool endValue(int x, int y);
bool messageValue(int x, int y);
void findStartPosition(int& startX, int& startY);

int main(void)
{
	const int WIDTH = 900;
	const int HEIGHT = 480;
	bool keys[] = {false, false, false, false, false};
	enum KEYS{UP, DOWN, LEFT, RIGHT, SPACE};
	bool done = false;
	bool render = false;
	int currentLevel = 1;
	float levelTimer = 60.0f;  
	float endMessageTimer = 5.0f;  
	Sprite player;
	char timerText[32];

	bool showEndMessage = false;
	bool showTimeUpMessage = false;
	float messageTimer = 0;
	
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

	//find and set start position
	int startX, startY;
	findStartPosition(startX, startY);
	player.SetPosition(startX, startY);

	int xOff = 0;
	int yOff = 0;

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_start_timer(timer);
	
	//draw background tiles
	MapDrawBG(xOff,yOff, 0, 0, WIDTH-1, HEIGHT-1);

	//draw foreground tiles 
	MapDrawFG(xOff,yOff, 0, 0, WIDTH-1, HEIGHT-1, 0);
	player.DrawSprites(0,0);
	al_flip_display();
	al_clear_to_color(al_map_rgb(0,0,0));
	while(!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			render = true;
			
			// update game state if not showing end messages
			if(!showEndMessage && !showTimeUpMessage) {
				MapUpdateAnims();
				levelTimer -= 1.0f/60.0f;
				
				// player movement only if game is still active
				if(keys[UP])
					player.UpdateSprites(WIDTH,HEIGHT,0);
				else if(keys[DOWN])
					player.UpdateSprites(WIDTH,HEIGHT,1);
				else if(keys[LEFT])
					player.UpdateSprites(WIDTH,HEIGHT,2);
				else if(keys[RIGHT])
					player.UpdateSprites(WIDTH,HEIGHT,3);
				
				// check level completion only if game is active
				if (player.CollisionEndBlock()) {
					if (currentLevel == 1) {
						MapFreeMem();
						if(MapLoad("level2.FMP", 1)) {
							cout << "Failed to load level 2!" << endl;
							done = true;
						} else {
							currentLevel = 2;
							levelTimer = 60.0f;
							int startX, startY;
							findStartPosition(startX, startY);
							player.SetPosition(startX, startY);
						}
					} else if (currentLevel == 2) {
						MapFreeMem();
						if(MapLoad("level3.FMP", 1)) {
							cout << "Failed to load level 3!" << endl;
							done = true;
						} else {
							currentLevel = 3;
							levelTimer = 60.0f;
							int startX, startY;
							findStartPosition(startX, startY);
							player.SetPosition(startX, startY);
						}
					} else if (currentLevel == 3) {
						showEndMessage = true;
					}
				}

				// Check for time up
				if(levelTimer <= 0) {
					showTimeUpMessage = true;
					endMessageTimer = 5.0f;
					// Reset all movement keys
					for(int i = 0; i < 5; i++) {
						keys[i] = false;
					}
				}
			} else {
				// end message timer
				endMessageTimer -= 1.0f/60.0f;
				if(endMessageTimer <= 0) {
					done = true;
				}
			}

			if(render && al_is_event_queue_empty(event_queue))
			{
				render = false;

				//update the map scroll position
				xOff = player.getX()+player.getWidth() - WIDTH/2 ;
				yOff = player.getY()+player.getHeight()   - HEIGHT/2 ;

				//avoid moving beyond the map edge
				if (xOff < 0) xOff = 0;

				if (xOff > (mapwidth * mapblockwidth - WIDTH))
					xOff = mapwidth * mapblockwidth - WIDTH;
				if (yOff < 0) 
					yOff = 0;
				if (yOff > (mapheight * mapblockheight - HEIGHT)) 
					yOff = mapheight * mapblockheight - HEIGHT;

				//draw background tiles
				MapDrawBG(xOff,yOff, 0, 0, WIDTH, HEIGHT);

				//draw foreground tiles
				MapDrawFG(xOff,yOff, 0, 0, WIDTH, HEIGHT, 0);
				player.DrawSprites(xOff, yOff);

				//draw timer
				sprintf(timerText, "Time: %.1f", levelTimer);
				al_draw_text(font, al_map_rgb(255, 255, 255), WIDTH - 10, 10, ALLEGRO_ALIGN_RIGHT, timerText);

				// end game message
				if(showEndMessage) {
					al_draw_text(font, al_map_rgb(255, 215, 0), WIDTH/2, HEIGHT/2 - 30, ALLEGRO_ALIGN_CENTER, "CONGRATULATIONS!");
					al_draw_text(font, al_map_rgb(255, 215, 0), WIDTH/2, HEIGHT/2 + 10, ALLEGRO_ALIGN_CENTER, "You've completed all levels!");
				} else if(showTimeUpMessage) {
					al_draw_text(font, al_map_rgb(255, 0, 0), WIDTH/2, HEIGHT/2 - 30, ALLEGRO_ALIGN_CENTER, "TIME'S UP!");
					char levelText[64];  
					sprintf(levelText, "Level %d - Try again!", currentLevel);  
					al_draw_text(font, al_map_rgb(255, 0, 0), WIDTH/2, HEIGHT/2 + 10, ALLEGRO_ALIGN_CENTER, levelText);
				}
				
				al_flip_display();
				al_clear_to_color(al_map_rgb(0,0,0));
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
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
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
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				break;
			}
		}
	}
	
	if (event_queue) {
		al_unregister_event_source(event_queue, al_get_timer_event_source(timer));
		al_unregister_event_source(event_queue, al_get_keyboard_event_source());
	}
		al_stop_timer(timer);
		al_destroy_bitmap(sprite);
		al_destroy_font(font);
		MapFreeMem();
		al_destroy_timer(timer);
		al_destroy_event_queue(event_queue);
		al_destroy_display(display);
		

	return 0;
}

int collided(int x, int y)
{
	BLKSTR *blockdata;
	blockdata = MapGetBlock(x/mapblockwidth, y/mapblockheight);
	return blockdata->tl;
}

bool endValue(int x, int y)
{
	BLKSTR* data;
	data = MapGetBlock(x/mapblockwidth, y/mapblockheight);
	return data->user1 == 9;
}

bool messageValue(int x, int y)
{
	BLKSTR* data;
	data = MapGetBlock(x/mapblockwidth, y/mapblockheight);
	return data->user1 == 9;
}

void findStartPosition(int& startX, int& startY) 
{
	for(int y = 0; y < mapheight; y++) {
		for(int x = 0; x < mapwidth; x++) {
			BLKSTR* data = MapGetBlock(x, y);
			if(data->user1 == 7) {  
				startX = (x * mapblockwidth) + mapblockwidth;
				startY = y * mapblockheight;
				return;
			}
		}
	}
}
