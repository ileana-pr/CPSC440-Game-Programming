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
#include "Food.h"
#include "Spider.h"
using namespace std;

// global constants for level progression
const int BASE_NUM_FOODS = 5;  // starting number of food items
const int BASE_NUM_SPIDERS = 3;  // starting number of spiders
const float BASE_SCROLL_SPEED = 12.0f;  // starting with level 2 speed (was 4.0f)
const int MAX_FOODS = BASE_NUM_FOODS;  // max food decreases with level
const int MAX_SPIDERS = BASE_NUM_SPIDERS * 4;  // allow for 4 levels of doubling
const float LEVEL_DISPLAY_TIME = 2.0f;  // seconds to show level transition
const int MAX_HEALTH = 20;  // player can take 20 hits before game over
const int HEALTH_BAR_WIDTH = 200;  // width of health bar in pixels
const int HEALTH_BAR_HEIGHT = 20;  // height of health bar in pixels

// forward declarations
int collided(int x, int y);
bool endValue(int x, int y);
void resetLevel(int level, Food foods[], Spider spiders[], int &numFoods, int &numSpiders, float &scrollSpeed);

int main(void)
{
	const int WIDTH = 900;
	const int HEIGHT = 480;
	
	int currentLevel = 1;
	int numFoods = BASE_NUM_FOODS;
	int numSpiders = BASE_NUM_SPIDERS;
	float currentScrollSpeed = BASE_SCROLL_SPEED;
	float scrollX = 0;
	float levelDisplayTimer = 0;  // timer for level transition display
	int playerHealth = MAX_HEALTH;  // initialize player health
	
	bool keys[] = {false, false, false, false, false};
	enum KEYS{UP, DOWN, LEFT, RIGHT, SPACE};
	bool done = false;
	bool render = false;
	bool showEndMessage = false;
	float endMessageTimer = 5.0f;
	Sprite player;
	
	// Create arrays with maximum possible size
	Food foods[MAX_FOODS];  
	Spider spiders[MAX_SPIDERS];  

	ALLEGRO_FONT* font = NULL;
	ALLEGRO_FONT* bigFont = NULL;  // larger font for level display
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
	bigFont = al_load_font("GROBOLD.ttf", 48, 0);  // larger size for level display
	
	if(!font || !bigFont)
		return -1;

	// load sprites
	ALLEGRO_BITMAP *sprite = al_load_bitmap("1432472502_chips2.png");
	if(!sprite)
		return -1;
		
	ALLEGRO_BITMAP *foodSprite = al_load_bitmap("food.png");
	if(!foodSprite)
		return -1;

	// initialize sprites
	al_lock_bitmap(sprite, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READONLY);
	ALLEGRO_COLOR color = al_get_pixel(sprite, 0, 0);
	unsigned char r, g, b;
	al_unmap_rgb(color, &r, &g, &b);
	al_unlock_bitmap(sprite);
	al_convert_mask_to_alpha(sprite, al_map_rgb(r, g, b));
	
	player.InitSprites(sprite);
	player.SetSpriteParameters(32, 32, 3, 1, 11, 3);
	
	// Initialize first level
	resetLevel(currentLevel, foods, spiders, numFoods, numSpiders, currentScrollSpeed);

	// Initialize sprites
	for(int i = 0; i < MAX_FOODS; i++) {
		foods[i].Init(foodSprite);
	}
	for(int i = 0; i < MAX_SPIDERS; i++) {
		spiders[i].Init(sprite);
	}

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
				float nextScrollX = scrollX + currentScrollSpeed;
				bool willCollide = collided(player.getX() + (int)nextScrollX, player.getY()) ||
								 collided(player.getX() + player.getWidth() + (int)nextScrollX, player.getY()) ||
								 collided(player.getX() + (int)nextScrollX, player.getY() + player.getHeight()) ||
								 collided(player.getX() + player.getWidth() + (int)nextScrollX, player.getY() + player.getHeight());
				
				// only scroll if no collision
				if (!willCollide) {
					scrollX = nextScrollX;
					if(scrollX >= TOTAL_MAP_WIDTH - WIDTH) {
						if(currentLevel < 4) {  // max 4 levels
							currentLevel++;
							scrollX = 0;
							player.SetPosition(WIDTH/4, player.getY());
							
							// Reset level with new difficulty
							resetLevel(currentLevel, foods, spiders, numFoods, numSpiders, currentScrollSpeed);
							
							// Start level display timer
							levelDisplayTimer = LEVEL_DISPLAY_TIME;
						} else {
							showEndMessage = true;
						}
					}
				}

				// handle player movement
				if(keys[UP] && player.getY() > 0) {
					player.UpdateSprites(WIDTH, HEIGHT, 0);
					if(!collided(player.getX() + xOff, player.getY() - 4) && 
					   !collided(player.getX() + player.getWidth() + xOff, player.getY() - 4))
						player.SetPosition(player.getX(), player.getY() - 4);
				}
				else if(keys[DOWN] && player.getY() < HEIGHT - player.getHeight()) {
					player.UpdateSprites(WIDTH, HEIGHT, 1);
					if(!collided(player.getX() + xOff, player.getY() + player.getHeight() + 4) &&
					   !collided(player.getX() + player.getWidth() + xOff, player.getY() + player.getHeight() + 4))
						player.SetPosition(player.getX(), player.getY() + 4);
				}
				
				float currentY = player.getY();  
				const int LEFT_BOUNDARY = 0;
				const int RIGHT_BOUNDARY = WIDTH / 3;  // restrict to left third

				if(keys[LEFT] && player.getX() > LEFT_BOUNDARY) {
					player.UpdateSprites(WIDTH, HEIGHT, 0);  
					if(!collided(player.getX() - 4 + xOff, currentY) &&
					   !collided(player.getX() - 4 + xOff, currentY + player.getHeight())) {
						player.SetPosition(player.getX() - 4, currentY);  
					}
				}
				else if(keys[RIGHT] && player.getX() < RIGHT_BOUNDARY - player.getWidth()) {
					player.UpdateSprites(WIDTH, HEIGHT, 1);  
					if(!collided(player.getX() + player.getWidth() + 4 + xOff, currentY) &&
					   !collided(player.getX() + player.getWidth() + 4 + xOff, currentY + player.getHeight())) {
						player.SetPosition(player.getX() + 4, currentY); 
					}
				}

				xOff = (int)scrollX;
				yOff = 0;

				// update all active food items
				for(int i = 0; i < numFoods; i++) {
					foods[i].StartFood(WIDTH, HEIGHT, foods, numFoods);
					foods[i].UpdateFood();
					foods[i].CollideFood(player.getX(), player.getY(), player.getWidth(), player.getHeight());
				}

				// update all active spiders
				for(int i = 0; i < numSpiders; i++) {
					spiders[i].StartSpider(WIDTH, HEIGHT, foods, numFoods, spiders, numSpiders);
					spiders[i].UpdateSpider();
					if(spiders[i].CollideSpider(player.getX(), player.getY(), player.getWidth(), player.getHeight())) {
						playerHealth--;  // reduce health on spider collision
						if(playerHealth <= 0) {
							showEndMessage = true;  // trigger game over
						}
					}
				}

				if(levelDisplayTimer > 0) {
					levelDisplayTimer -= 1.0f/60.0f;  // decrease timer (assuming 60 FPS)
				}

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
			
			// draw all active food items
			for(int i = 0; i < numFoods; i++) {
				foods[i].DrawFood();
			}
			// draw all active spiders
			for(int i = 0; i < numSpiders; i++) {
				spiders[i].DrawSpider();
			}
			player.DrawSprites(0, 0);

			// draw UI
			char levelText[32];
			sprintf(levelText, "Level %d", currentLevel);
			al_draw_text(font, al_map_rgb(255, 0, 0), 10, 10, ALLEGRO_ALIGN_LEFT, levelText);

			// Big level transition display (center screen)
			if(levelDisplayTimer > 0) {
				sprintf(levelText, "Level %d", currentLevel);
				al_draw_text(bigFont, al_map_rgb(255, 0, 0), WIDTH/2, HEIGHT/2 - 24, 
					ALLEGRO_ALIGN_CENTRE, levelText);
			}

			// calculate total score from all food items
			int totalScore = 0;
			for(int i = 0; i < numFoods; i++) {
				totalScore += foods[i].getScore();
			}
			char scoreText[32];
			sprintf(scoreText, "Score: %d", totalScore);
			al_draw_text(font, al_map_rgb(255, 0, 0), WIDTH - 10, 10, ALLEGRO_ALIGN_RIGHT, scoreText);

			// draw health bar
			int healthBarX = 10;
			int healthBarY = HEIGHT - 30;  // 30 pixels from bottom
			
			// draw health bar background (red)
			al_draw_filled_rectangle(healthBarX, healthBarY, 
				healthBarX + HEALTH_BAR_WIDTH, healthBarY + HEALTH_BAR_HEIGHT, 
				al_map_rgb(255, 0, 0));
			
			// draw current health (green)
			float healthPercentage = (float)playerHealth / MAX_HEALTH;
			al_draw_filled_rectangle(healthBarX, healthBarY,
				healthBarX + (HEALTH_BAR_WIDTH * healthPercentage), 
				healthBarY + HEALTH_BAR_HEIGHT,
				al_map_rgb(0, 255, 0));
			
			// draw health text
			char healthText[32];
			sprintf(healthText, "Health: %d/%d", playerHealth, MAX_HEALTH);
			al_draw_text(font, al_map_rgb(255, 0, 0), healthBarX + HEALTH_BAR_WIDTH + 10,
				healthBarY, ALLEGRO_ALIGN_LEFT, healthText);

			if(showEndMessage) {
				al_draw_text(font, al_map_rgb(255, 0, 0), WIDTH/2, HEIGHT/2, 
					ALLEGRO_ALIGN_CENTRE, "Game Over!");
				char finalScoreText[64];
				sprintf(finalScoreText, "Final Score: %d", totalScore);
				al_draw_text(font, al_map_rgb(255, 0, 0), WIDTH/2, HEIGHT/2 + 40, 
					ALLEGRO_ALIGN_CENTRE, finalScoreText);
			}

			al_flip_display();
		}
	}

	MapFreeMem();
	al_destroy_font(bigFont);
	al_destroy_font(font);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_bitmap(sprite);
	al_destroy_bitmap(foodSprite);

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

void resetLevel(int level, Food foods[], Spider spiders[], int &numFoods, int &numSpiders, float &scrollSpeed) {
	// Calculate new quantities
	numFoods = BASE_NUM_FOODS / level;
	if(numFoods < 1) numFoods = 1;  // ensure at least 1 food
	
	numSpiders = BASE_NUM_SPIDERS * (1 << (level - 1));  // double spiders each level
	if(numSpiders > MAX_SPIDERS) numSpiders = MAX_SPIDERS;
	
	scrollSpeed = BASE_SCROLL_SPEED * (level / 2.0f);  // adjusted formula to account for higher base speed
	
	// Reset all food items
	for(int i = 0; i < MAX_FOODS; i++) {
		if(i < numFoods) {
			foods[i].SetSpeed(scrollSpeed);
		}
	}
	
	// Reset all spiders
	for(int i = 0; i < MAX_SPIDERS; i++) {
		if(i < numSpiders) {
			spiders[i].SetSpeed(scrollSpeed + 1.0f);
		}
	}
}