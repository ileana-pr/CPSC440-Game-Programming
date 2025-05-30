#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include "arrow.h"
#include "bullet.h"

bool finished = false;
bool timeOut = false;
int time_left = 30;

void* countdown_timer(ALLEGRO_THREAD* ptr, void* arg);

int main(void)
{
	arrowClass arrow;
	bullet mybullet[10];
	int score=0;
	bool redraw=true;
	const int FPS = 60;

	//variables
	int width = 640;
	int height = 520;
	bool done = false;

	//allegro variable
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_FONT *font = NULL;
    al_init_font_addon();
    al_init_ttf_addon();
    font = al_load_font("GROBOLD.TTF", 16, 0);
    if (!font) return -1;

	//program init
	if(!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(width, height);			//create our display object

	if(!display)										//test display object
		return -1;

	//addon init
	al_install_keyboard();
	al_init_primitives_addon();
	
	//create arrow 
	arrow.create_arrow_bitmap(display);

	// create bullet bitmap 
	ALLEGRO_BITMAP* bullet_bmp = al_create_bitmap(16, 16);
	al_set_target_bitmap(bullet_bmp);
	al_clear_to_color(al_map_rgba(0, 0, 0, 0));
	al_draw_filled_circle(8, 8, 7, al_map_rgb(255, 0, 0)); // red circle
	al_draw_filled_rectangle(4, 4, 12, 12, al_map_rgb(0, 255, 255)); // cyan square
	al_set_target_bitmap(al_get_backbuffer(display));
	for (int i = 0; i < 10; i++) mybullet[i].set_bitmap(bullet_bmp);
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_clear_to_color(al_map_rgb(0,0,0));
	arrow.drawArrow();
	al_flip_display();
	al_start_timer(timer);

	ALLEGRO_THREAD* timer_thread = al_create_thread(countdown_timer, NULL);
	al_start_thread(timer_thread);

	while(!done && !timeOut)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			redraw = true;
			for(int i=0;i<10;i++)
			{
				if (!mybullet[i].getStatus()) {
					mybullet[i].fire();
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
				arrow.up();
				break;
			case ALLEGRO_KEY_DOWN:
				arrow.down();
				break;
			case ALLEGRO_KEY_LEFT:
				arrow.left();
				break;
			case ALLEGRO_KEY_RIGHT:
				arrow.right();
				break;
			}
		}
		if(redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;
			al_clear_to_color(al_map_rgb(0,0,0));
			if (arrow.getSpeed()!=0){
				arrow.erase_arrow();
				arrow.move_arrow(width,480);
			}
			arrow.drawArrow();
			for(int i=0;i<10;i++)
			{
				mybullet[i].erase_bullet();
				score+=mybullet[i].move_bullet(arrow.getX(),arrow.getY(),32,32,480);
			}
			// info area
			al_draw_filled_rectangle(0, 480, width, 520, al_map_rgb(30,30,30));
			al_draw_textf(font, al_map_rgb(255,255,255), 10, 490, 0, "time: %d", time_left);
			al_draw_textf(font, al_map_rgb(255,255,255), 200, 490, 0, "score: %d", score);
			al_flip_display();
		}
	}

	al_destroy_thread(timer_thread);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_font(font);
	system("pause");
	return 0;
}

void* countdown_timer(ALLEGRO_THREAD* ptr, void* arg) {
	long startTime, currentTime;
	startTime = al_get_time();
	currentTime = al_get_time();
	while (currentTime - startTime < 30 && !finished) {
		currentTime = al_get_time();
		time_left = 30 - (int)(currentTime - startTime);
	}
	timeOut = true;
	return NULL;
}