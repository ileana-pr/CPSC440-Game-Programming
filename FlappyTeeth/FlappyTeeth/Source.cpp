// name: ileana perez 
// cpsc 340 - assignment 5

#define _CRT_SECURE_NO_WARNINGS  

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "SpriteSheet.h"
#include "mappy_A5.h"
#include <iostream>
#include "Food.h"
#include "Spider.h"
using namespace std;

int collided(int x, int y);
bool endValue(int x, int y);
void resetLevel(int level, Food foods[], Spider spiders[], int &numFoods, int &numSpiders, float &scrollSpeed, 
               int baseNumFoods, int baseNumSpiders, float baseScrollSpeed, int maxSpiders);
void initializeGame(int &numFoods, int &numSpiders, float &scrollSpeed, 
                   int baseNumFoods, int baseNumSpiders, float baseScrollSpeed);
void updateHealthBar(ALLEGRO_FONT* font, int health, int maxHealth, int barWidth, int barHeight, int screenHeight);
void handleDeathAnimation(bool &isDeathSequenceStarted, float &deathAnimationTimer, float &deathRotation, float &deathScale,
                         float deathDuration, float rotationSpeed, ALLEGRO_SAMPLE* gameOverSound, bool &gameOverSoundPlayed,
                         bool &showEndMessage);
void drawGameUI(ALLEGRO_FONT* font, ALLEGRO_FONT* bigFont, int currentLevel, float levelDisplayTimer,
                int totalScore, int screenWidth, int screenHeight);
void drawIntroScreen(ALLEGRO_FONT* font, ALLEGRO_FONT* bigFont, int screenWidth, int screenHeight);

int main(void)
{
	const int GAME_WIDTH = 900;
	const int GAME_HEIGHT = 480;
	const int BASE_NUM_FOODS = 5;
	const int BASE_NUM_SPIDERS = 3;
	const float BASE_SCROLL_SPEED = 12.0f;
	const int MAX_FOODS = BASE_NUM_FOODS;
	const int MAX_SPIDERS = BASE_NUM_SPIDERS * 4;
	const float LEVEL_DISPLAY_TIME = 2.0f;
	const int MAX_HEALTH = 20;
	const int HEALTH_BAR_WIDTH = 200;
	const int HEALTH_BAR_HEIGHT = 20;
	const float DEATH_ANIMATION_DURATION = 2.0f;
	const float DEATH_ROTATION_SPEED = 3.0f;

	int currentLevel = 1;
	int numFoods, numSpiders;
	float currentScrollSpeed;
	
	initializeGame(numFoods, numSpiders, currentScrollSpeed, 
				  BASE_NUM_FOODS, BASE_NUM_SPIDERS, BASE_SCROLL_SPEED);

	float scrollX = 0;
	float levelDisplayTimer = 0;
	int playerHealth = MAX_HEALTH;
	bool gameOverSoundPlayed = false;
	float deathAnimationTimer = 0;
	float deathRotation = 0;
	float deathScale = 1.0f;
	bool isDeathSequenceStarted = false;
	bool showIntro = true;

	bool keys[] = {false, false, false, false, false};
	enum KEYS{UP, DOWN, LEFT, RIGHT, SPACE};
	bool done = false;
	bool render = false;
	bool showEndMessage = false;
	float endMessageTimer = 5.0f;
	Sprite player;
	
	Food foods[MAX_FOODS];  
	Spider spiders[MAX_SPIDERS];  

	ALLEGRO_FONT* font = NULL;
	ALLEGRO_FONT* bigFont = NULL;
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer;
	ALLEGRO_SAMPLE *gameOverSound = NULL;
	ALLEGRO_SAMPLE *spiderMunchSound = NULL;
	ALLEGRO_SAMPLE *foodSound = NULL;
	ALLEGRO_AUDIO_STREAM *backgroundMusic = NULL;
	
	if(!al_init())										
		return -1;

	display = al_create_display(GAME_WIDTH, GAME_HEIGHT);			

	if(!display)										
		return -1;

	al_install_keyboard();
	al_init_image_addon();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_audio();
	al_init_acodec_addon();
	
	if (!al_reserve_samples(3)) {
		return -1;
	}
	
	gameOverSound = al_load_sample("game-over-2-sound-effect-230463.mp3");
	if (!gameOverSound) {
		fprintf(stderr, "failed to load game over sound\n");
	}
	
	spiderMunchSound = al_load_sample("spidermunch.mp3");
	if (!spiderMunchSound) {
		fprintf(stderr, "failed to load spider munch sound\n");
	}
	
	foodSound = al_load_sample("food.mp3");
	if (!foodSound) {
		fprintf(stderr, "failed to load food sound\n");
	}
	
	backgroundMusic = al_load_audio_stream("game-music-loop-7-145285.mp3", 2, 2048);
	if (!backgroundMusic) {
		fprintf(stderr, "failed to load background music\n");
	} else {
		al_set_audio_stream_playmode(backgroundMusic, ALLEGRO_PLAYMODE_LOOP);
		al_attach_audio_stream_to_mixer(backgroundMusic, al_get_default_mixer());
		al_set_audio_stream_gain(backgroundMusic, 0.5f);
	}
	
	event_queue = al_create_event_queue();
	
	al_register_event_source(event_queue, al_get_display_event_source(display));
	
	al_clear_to_color(al_map_rgb(135, 206, 235));
	al_flip_display();
	
	font = al_load_font("LilitaOne-Regular.ttf", 24, 0);
	bigFont = al_load_font("LilitaOne-Regular.ttf", 48, 0); 
	
	if(!font || !bigFont) {
		fprintf(stderr, "failed to load font\n");
		return -1;
	}

	ALLEGRO_BITMAP *sprite = al_load_bitmap("1432472502_chips2.png");
	if(!sprite)
		return -1;
		
	ALLEGRO_BITMAP *foodSprite = al_load_bitmap("food.png");
	if(!foodSprite)
		return -1;

	al_lock_bitmap(sprite, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READONLY);
	ALLEGRO_COLOR color = al_get_pixel(sprite, 0, 0);
	unsigned char r, g, b;
	al_unmap_rgb(color, &r, &g, &b);
	al_unlock_bitmap(sprite);
	al_convert_mask_to_alpha(sprite, al_map_rgb(r, g, b));
	
	player.InitSprites(sprite);
	player.SetSpriteParameters(32, 32, 3, 1, 11, 3);
	
	resetLevel(currentLevel, foods, spiders, numFoods, numSpiders, currentScrollSpeed,
			 BASE_NUM_FOODS, BASE_NUM_SPIDERS, BASE_SCROLL_SPEED, MAX_SPIDERS);

	for(int i = 0; i < MAX_FOODS; i++) {
		foods[i].Init(foodSprite);
	}
	for(int i = 0; i < MAX_SPIDERS; i++) {
		spiders[i].Init(sprite);
	}

	char* mapPath = (char*)"level1.FMP";
	if(MapLoad(mapPath, 1))
		return -1;

	const int TOTAL_MAP_WIDTH = mapwidth * mapblockwidth;
	const int TOTAL_MAP_HEIGHT = mapheight * mapblockheight;
	
	if(TOTAL_MAP_WIDTH < GAME_WIDTH || TOTAL_MAP_HEIGHT < GAME_HEIGHT)
		return -1;

	player.SetPosition(GAME_WIDTH/4, GAME_HEIGHT/2);

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
			
			if(showIntro) {
				// Wait for space key to start game
				if(keys[SPACE]) {
					showIntro = false;
				}
			}
			else if(!showEndMessage) {
				MapUpdateAnims();
				
				// check collision
				float nextScrollX = scrollX + currentScrollSpeed;
				bool willCollide = collided(player.getX() + (int)nextScrollX, player.getY()) ||
								 collided(player.getX() + player.getWidth() + (int)nextScrollX, player.getY()) ||
								 collided(player.getX() + (int)nextScrollX, player.getY() + player.getHeight()) ||
								 collided(player.getX() + player.getWidth() + (int)nextScrollX, player.getY() + player.getHeight());
				
				if (!willCollide && !isDeathSequenceStarted) {
					scrollX = nextScrollX;
					if(scrollX >= TOTAL_MAP_WIDTH - GAME_WIDTH) {
						if(currentLevel < 4) {
							currentLevel++;
							scrollX = 0;
							player.SetPosition(GAME_WIDTH/4, player.getY());
							
							resetLevel(currentLevel, foods, spiders, numFoods, numSpiders, currentScrollSpeed,
									 BASE_NUM_FOODS, BASE_NUM_SPIDERS, BASE_SCROLL_SPEED, MAX_SPIDERS);
							
							levelDisplayTimer = LEVEL_DISPLAY_TIME;
						} else {
							showEndMessage = true;
						}
					}
				}

				// handle movement - only if not dying
				if (!isDeathSequenceStarted) {
					if(keys[UP] && player.getY() > 0) {
						player.UpdateSprites(GAME_WIDTH, GAME_HEIGHT, 0);
						if(!collided(player.getX() + xOff, player.getY() - 4) && 
						   !collided(player.getX() + player.getWidth() + xOff, player.getY() - 4))
							player.SetPosition(player.getX(), player.getY() - 4);
					}
					else if(keys[DOWN] && player.getY() < GAME_HEIGHT - player.getHeight()) {
						player.UpdateSprites(GAME_WIDTH, GAME_HEIGHT, 1);
						if(!collided(player.getX() + xOff, player.getY() + player.getHeight() + 4) &&
						   !collided(player.getX() + player.getWidth() + xOff, player.getY() + player.getHeight() + 4))
							player.SetPosition(player.getX(), player.getY() + 4);
					}
					
					float currentY = player.getY();  
					const int LEFT_BOUNDARY = 0;
					const int RIGHT_BOUNDARY = GAME_WIDTH / 3;

					if(keys[LEFT] && player.getX() > LEFT_BOUNDARY) {
						player.UpdateSprites(GAME_WIDTH, GAME_HEIGHT, 0);  
						if(!collided(player.getX() - 4 + xOff, currentY) &&
						   !collided(player.getX() - 4 + xOff, currentY + player.getHeight())) {
							player.SetPosition(player.getX() - 4, currentY);  
						}
					}
					else if(keys[RIGHT] && player.getX() < RIGHT_BOUNDARY - player.getWidth()) {
						player.UpdateSprites(GAME_WIDTH, GAME_HEIGHT, 1);  
						if(!collided(player.getX() + player.getWidth() + 4 + xOff, currentY) &&
						   !collided(player.getX() + player.getWidth() + 4 + xOff, currentY + player.getHeight())) {
							player.SetPosition(player.getX() + 4, currentY); 
						}
					}
				}

				xOff = (int)scrollX;
				yOff = 0;

				// update food and spiders only if not dying
				if (!isDeathSequenceStarted) {
					// update food
					for(int i = 0; i < numFoods; i++) {
						foods[i].StartFood(GAME_WIDTH, GAME_HEIGHT, foods, numFoods);
						foods[i].UpdateFood();
						if(foods[i].CollideFood(player.getX(), player.getY(), player.getWidth(), player.getHeight())) {
							if (foodSound) {
								al_play_sample(foodSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
							}
						}
					}

					// update spiders
					for(int i = 0; i < numSpiders; i++) {
						spiders[i].StartSpider(GAME_WIDTH, GAME_HEIGHT, foods, numFoods, spiders, numSpiders);
						spiders[i].UpdateSpider();
						if(spiders[i].CollideSpider(player.getX(), player.getY(), player.getWidth(), player.getHeight())) {
							playerHealth--;
							if (spiderMunchSound) {
								al_play_sample(spiderMunchSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
							}
						}
					}
				}

				if(levelDisplayTimer > 0) {
					levelDisplayTimer -= 1.0f/60.0f;
				}

				// handle death animation and sound
				if(playerHealth <= 0) {
					handleDeathAnimation(isDeathSequenceStarted, deathAnimationTimer, deathRotation, deathScale,
									  DEATH_ANIMATION_DURATION, DEATH_ROTATION_SPEED, 
									  gameOverSound, gameOverSoundPlayed, showEndMessage);
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
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = true;
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
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				break;
			}
		}

		if(render && al_is_event_queue_empty(event_queue))
		{
			render = false;
			al_clear_to_color(al_map_rgb(135, 206, 235));

			if(showIntro) {
				drawIntroScreen(font, bigFont, GAME_WIDTH, GAME_HEIGHT);
			}
			else {
				MapDrawBG(xOff, yOff, 0, 0, GAME_WIDTH, GAME_HEIGHT);
				MapDrawFG(xOff, yOff, 0, 0, GAME_WIDTH, GAME_HEIGHT, 0);
				
				// draw food
				for(int i = 0; i < numFoods; i++) {
					foods[i].DrawFood();
				}
				// draw spiders
				for(int i = 0; i < numSpiders; i++) {
					spiders[i].DrawSpider();
				}
				
				// draw player with death animation
				if (isDeathSequenceStarted && deathAnimationTimer > 0) {
					player.DrawSpritesWithTransform(0, 0, deathRotation, deathScale);
				} else if (!showEndMessage) {
					player.DrawSprites(0, 0);
				}

				// draw ui
				char levelText[32];
				sprintf(levelText, "Level %d", currentLevel);
				al_draw_text(font, al_map_rgb(255, 0, 0), 10, 10, ALLEGRO_ALIGN_LEFT, levelText);

				// level transition display
				if(levelDisplayTimer > 0) {
					sprintf(levelText, "Level %d", currentLevel);
					al_draw_text(bigFont, al_map_rgb(255, 0, 0), GAME_WIDTH/2, GAME_HEIGHT/2 - 24, 
						ALLEGRO_ALIGN_CENTRE, levelText);
				}

				// calculate score
				int totalScore = 0;
				for(int i = 0; i < numFoods; i++) {
					totalScore += foods[i].getScore();
				}
				char scoreText[32];
				sprintf(scoreText, "Score: %d", totalScore);
				al_draw_text(font, al_map_rgb(255, 0, 0), GAME_WIDTH - 10, 10, ALLEGRO_ALIGN_RIGHT, scoreText);

				// draw health bar
				int healthBarX = 10;
				int healthBarY = GAME_HEIGHT - 30;
				
				al_draw_filled_rectangle(healthBarX, healthBarY, 
					healthBarX + HEALTH_BAR_WIDTH, healthBarY + HEALTH_BAR_HEIGHT, 
					al_map_rgb(255, 0, 0));
				
				float healthPercentage = (float)playerHealth / MAX_HEALTH;
				al_draw_filled_rectangle(healthBarX, healthBarY,
					healthBarX + (HEALTH_BAR_WIDTH * healthPercentage), 
					healthBarY + HEALTH_BAR_HEIGHT,
					al_map_rgb(0, 255, 0));
				
				char healthText[32];
				sprintf(healthText, "Health: %d/%d", playerHealth, MAX_HEALTH);
				al_draw_text(font, al_map_rgb(255, 0, 0), healthBarX + HEALTH_BAR_WIDTH + 10,
					healthBarY, ALLEGRO_ALIGN_LEFT, healthText);

				if(showEndMessage) {
					al_draw_text(font, al_map_rgb(255, 0, 0), GAME_WIDTH/2, GAME_HEIGHT/2, 
						ALLEGRO_ALIGN_CENTRE, "Game Over!");
					char finalScoreText[64];
					sprintf(finalScoreText, "Final Score: %d", totalScore);
					al_draw_text(font, al_map_rgb(255, 0, 0), GAME_WIDTH/2, GAME_HEIGHT/2 + 40, 
						ALLEGRO_ALIGN_CENTRE, finalScoreText);
				}
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
	if (gameOverSound) al_destroy_sample(gameOverSound);
	if (spiderMunchSound) al_destroy_sample(spiderMunchSound);
	if (foodSound) al_destroy_sample(foodSound);
	if (backgroundMusic) {
		al_set_audio_stream_playing(backgroundMusic, false);
		al_destroy_audio_stream(backgroundMusic);
	}

	return 0;
}

void initializeGame(int &numFoods, int &numSpiders, float &scrollSpeed, 
				   int baseNumFoods, int baseNumSpiders, float baseScrollSpeed) {
	numFoods = baseNumFoods;
	numSpiders = baseNumSpiders;
	scrollSpeed = baseScrollSpeed;
}

void resetLevel(int level, Food foods[], Spider spiders[], int &numFoods, int &numSpiders, float &scrollSpeed,
			   int baseNumFoods, int baseNumSpiders, float baseScrollSpeed, int maxSpiders) {
	numFoods = baseNumFoods / level;
	if(numFoods < 1) numFoods = 1;
	
	numSpiders = baseNumSpiders * (1 << (level - 1));
	if(numSpiders > maxSpiders) numSpiders = maxSpiders;
	
	scrollSpeed = baseScrollSpeed * (level / 2.0f);
	
	for(int i = 0; i < numFoods; i++) {
		foods[i].SetSpeed(scrollSpeed);
	}
	
	for(int i = 0; i < numSpiders; i++) {
		spiders[i].SetSpeed(scrollSpeed + 1.0f);
	}
}

void handleDeathAnimation(bool &isDeathSequenceStarted, float &deathAnimationTimer, float &deathRotation, float &deathScale,
						 float deathDuration, float rotationSpeed, ALLEGRO_SAMPLE* gameOverSound, bool &gameOverSoundPlayed,
						 bool &showEndMessage) {
	if (!isDeathSequenceStarted) {
		isDeathSequenceStarted = true;
		deathAnimationTimer = deathDuration;
		if (gameOverSound && !gameOverSoundPlayed) {
			al_play_sample(gameOverSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			gameOverSoundPlayed = true;
		}
	}
	
	if (deathAnimationTimer > 0) {
		deathAnimationTimer -= 1.0f/60.0f;
		deathRotation += rotationSpeed * ALLEGRO_PI * 2 / 60.0f;
		deathScale = deathAnimationTimer / deathDuration;
		
		if (deathAnimationTimer <= 0) {
			showEndMessage = true;
		}
	}
}

void updateHealthBar(ALLEGRO_FONT* font, int health, int maxHealth, int barWidth, int barHeight, int screenHeight) {
	int healthBarX = 10;
	int healthBarY = screenHeight - 30;
	
	al_draw_filled_rectangle(healthBarX, healthBarY, 
		healthBarX + barWidth, healthBarY + barHeight, 
		al_map_rgb(255, 0, 0));
	
	float healthPercentage = (float)health / maxHealth;
	al_draw_filled_rectangle(healthBarX, healthBarY,
		healthBarX + (barWidth * healthPercentage), 
		healthBarY + barHeight,
		al_map_rgb(0, 255, 0));
	
	char healthText[32];
	sprintf(healthText, "Health: %d/%d", health, maxHealth);
	al_draw_text(font, al_map_rgb(255, 0, 0), healthBarX + barWidth + 10,
		healthBarY, ALLEGRO_ALIGN_LEFT, healthText);
}

void drawGameUI(ALLEGRO_FONT* font, ALLEGRO_FONT* bigFont, int currentLevel, float levelDisplayTimer,
				int totalScore, int screenWidth, int screenHeight) {
	// draw level
	char levelText[32];
	sprintf(levelText, "Level %d", currentLevel);
	al_draw_text(font, al_map_rgb(255, 0, 0), 10, 10, ALLEGRO_ALIGN_LEFT, levelText);

	// level transition display
	if(levelDisplayTimer > 0) {
		al_draw_text(bigFont, al_map_rgb(255, 0, 0), screenWidth/2, screenHeight/2 - 24, 
			ALLEGRO_ALIGN_CENTRE, levelText);
	}

	// draw score
	char scoreText[32];
	sprintf(scoreText, "Score: %d", totalScore);
	al_draw_text(font, al_map_rgb(255, 0, 0), screenWidth - 10, 10, ALLEGRO_ALIGN_RIGHT, scoreText);
}

void drawIntroScreen(ALLEGRO_FONT* font, ALLEGRO_FONT* bigFont, int screenWidth, int screenHeight) {
	// title
	al_draw_text(bigFont, al_map_rgb(255, 0, 0), screenWidth/2, screenHeight/4, 
				 ALLEGRO_ALIGN_CENTRE, "Flappy Teeth");
	
	// instructions
	int startY = screenHeight/2 - 100;
	int lineSpacing = 30;
	
	startY += lineSpacing * 2;
	
	al_draw_text(font, al_map_rgb(255, 0, 0), screenWidth/2, startY, 
				 ALLEGRO_ALIGN_CENTRE, "use arrow keys to move");
	
	startY += lineSpacing;
	
	al_draw_text(font, al_map_rgb(255, 0, 0), screenWidth/2, startY, 
				 ALLEGRO_ALIGN_CENTRE, "food goes in your mouth");
	
	startY += lineSpacing;
	
	al_draw_text(font, al_map_rgb(255, 0, 0), screenWidth/2, startY, 
				 ALLEGRO_ALIGN_CENTRE, "spiders dont");
	
	startY += lineSpacing;
	
	al_draw_text(font, al_map_rgb(255, 0, 0), screenWidth/2, startY, 
				 ALLEGRO_ALIGN_CENTRE, "survive all 4 levels to win!");
	
	startY += lineSpacing * 2;
	
	al_draw_text(font, al_map_rgb(255, 0, 0), screenWidth/2, startY, 
				 ALLEGRO_ALIGN_CENTRE, "press space to start");
}

// collision detection
int collided(int x, int y)
{
	BLKSTR *blockdata;
	blockdata = MapGetBlock(x/mapblockwidth, y/mapblockheight);
	if (!blockdata) return 0;
	
	return (blockdata->tl || blockdata->tr || blockdata->bl || blockdata->br);
}

// check for end of level
bool endValue(int x, int y)
{
	BLKSTR* data;
	data = MapGetBlock(x/mapblockwidth, y/mapblockheight);
	if (!data) return false;
	return data->user1 == 9;  
}