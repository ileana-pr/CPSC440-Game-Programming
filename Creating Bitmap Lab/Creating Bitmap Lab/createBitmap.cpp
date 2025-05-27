#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>

struct arrow_class
{
	int x,y;
	int dir,speed;
	int color;

} arrow;

#define MAXSPEED 3

void create_arrow_bitmap(ALLEGRO_BITMAP * arrow_bmp[], ALLEGRO_DISPLAY *display);
void erase_arrow();
void move_arrow();
void up();
void down();
void right();
void left();

int main(void)
{

	ALLEGRO_BITMAP *arrow_bmp[4]={NULL,NULL,NULL,NULL};
	//variables
	int width = 640;
	int height = 480;
	bool done = false;

	//allegro variable
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;


	//program init
	if(!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(width, height);			//create our display object

	if(!display)										//test display object
		return -1;

	//addon init
	al_install_keyboard();
	al_init_primitives_addon();
	create_arrow_bitmap(arrow_bmp, display);


	al_set_target_bitmap(al_get_backbuffer(display));
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_clear_to_color(al_map_rgb(0,0,0));
	al_flip_display();
	while(!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			}
		}
		al_draw_bitmap(arrow_bmp[0], width / 2, 100, 0);
		al_draw_bitmap(arrow_bmp[1], width / 2, 200, 0);
		al_draw_bitmap(arrow_bmp[2], width / 2, 300, 0);
		al_draw_bitmap(arrow_bmp[3], width / 2, 400, 0);
		al_flip_display();
		al_clear_to_color(al_map_rgb(0,0,0));
	}
	for(int i=0; i<4; i++)
	{
		al_destroy_bitmap(arrow_bmp[i]);
	}
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);						//destroy our display object
	system("pause");
	return 0;
}

void create_arrow_bitmap(ALLEGRO_BITMAP * arrow_bmp[],ALLEGRO_DISPLAY *display)
{
	for(int i=0;i<4; i++)
	{
		arrow_bmp[i]=al_create_bitmap(32,32);   
		if(!arrow_bmp[i]) {
			exit(1);
			al_destroy_display(display);

		}

		al_set_target_bitmap(arrow_bmp[i]);
		al_clear_to_color(al_map_rgb(0, 0, 0));

		int x = 15;
		int y = 15;
		al_draw_filled_rectangle(x-10, y-10, x+10, y+10, al_map_rgb(255, 255, 255));

		switch(i)
		{
		case 0: //Up
			al_draw_filled_triangle(x-10,y-10,x+11,y-10,x,y-15,al_map_rgb(255, 0, 0));
			break;
		case 1://Right
			al_draw_filled_triangle(x+11,y-11,x+11,y+11,x+15,y,al_map_rgb(255, 0, 0));
			break;
		case 2://Down
			al_draw_filled_triangle(x-11,y+11,x+11,y+11,x,y+15,al_map_rgb(255, 0, 0));
			break;
		case 3: //Left
			al_draw_filled_triangle(x-11,y-11,x-11,y+11,x-15,y,al_map_rgb(255, 0, 0));
			break;
		}
	}
}


