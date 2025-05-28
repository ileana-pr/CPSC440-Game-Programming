//Name: Ileana Perez
//Program: Creating Bitmap Lab

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>

struct spaceship_class
{
	int x,y;
	int dir,speed;
	int color;

} spaceship;

#define MAXSPEED 3

void create_spaceship_bitmap(ALLEGRO_BITMAP * spaceship_bmp[], ALLEGRO_DISPLAY *display);
void erase_spaceship();		
void move_spaceship();
void up();
void down();
void right();
void left();

int main(void)
{

	ALLEGRO_BITMAP *spaceship_bmp[4]={NULL,NULL,NULL,NULL};
	//variables
	int width = 640;
	int height = 480;
	bool done = false;

	//allegro variable
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;


	//program init
	if(!al_init())									
		return -1;

	display = al_create_display(width, height);		

	if(!display)										
		return -1;

	//addon init
	al_install_keyboard();
	al_init_primitives_addon();
	create_spaceship_bitmap(spaceship_bmp, display);


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
		al_draw_bitmap(spaceship_bmp[0], width / 2, 100, 0);
		al_draw_bitmap(spaceship_bmp[1], width / 2, 200, 0);
		al_draw_bitmap(spaceship_bmp[2], width / 2, 300, 0);
		al_draw_bitmap(spaceship_bmp[3], width / 2, 400, 0);
		al_flip_display();
		al_clear_to_color(al_map_rgb(0,0,0));
	}
	for(int i=0; i<4; i++)
	{
		al_destroy_bitmap(spaceship_bmp[i]);
	}
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);					
	system("pause");
	return 0;
}

void create_spaceship_bitmap(ALLEGRO_BITMAP * spaceship_bmp[], ALLEGRO_DISPLAY *display)
{
	for(int i=0;i<4; i++)
	{
		spaceship_bmp[i]=al_create_bitmap(64,64);   
		if(!spaceship_bmp[i]) {
			exit(1);
			al_destroy_display(display);
		}

		al_set_target_bitmap(spaceship_bmp[i]);
		al_clear_to_color(al_map_rgb(0, 0, 0)); 

		int x = 32, y = 32;
		int width = 18, height = 40;
		int wing_width = 16, wing_height = 32; 
		int cockpit_width = 8, cockpit_height = 18; 
		int antenna_length = 15; 

		// body - white
		al_draw_filled_rectangle(
			x - width / 2, 
			y - height / 2, 
			x + width / 2, 
			y + height / 2, 
			al_map_rgb(255,255,255)
		);

		// nose - white 
		al_draw_filled_triangle(
			x - width / 2, y - height / 2, 
			x + width / 2, y - height / 2, 
			x, y - height / 2 - 8,
			al_map_rgb(255,255,255)
		);

		// left wing - red
		al_draw_filled_triangle(
			x - width / 2, y - height / 6, 
			x - width / 2 - wing_width, y + wing_height / 2, 
			x - width / 2, y + height / 2, 
			al_map_rgb(255,0,0)
		);

		// right wing - red
		al_draw_filled_triangle(
			x + width / 2, y - height / 6, 
			x + width / 2 + wing_width, y + wing_height / 2, 
			x + width / 2, y + height / 2, 
			al_map_rgb(255,0,0)
		);

		// blue cockpit 
		al_draw_filled_rectangle(
			x - cockpit_width / 2, 
			y - height / 2 + 8, 
			x + cockpit_width / 2, 
			y - height / 2 + 8 + cockpit_height, 
			al_map_rgb(0,120,255)
		); 

		// yellow lights 
		al_draw_filled_rectangle(
			x - 2, y + height / 4, x + 2, y + height / 4 + 6, 
			al_map_rgb(255,255,0)
		);
		al_draw_filled_rectangle(
			x - width / 2 - 6, y + 10, x - width / 2 - 2, y + 16, 
			al_map_rgb(255,255,0)
		);
		al_draw_filled_rectangle(
			x + width / 2 + 2, y + 10, x + width / 2 + 6, y + 16, 
			al_map_rgb(255,255,0)
		);

		// small white dot at the tip for the gun
		al_draw_filled_circle(
			x, y - height / 2 - 8, 4,
			al_map_rgb(255,0,0)
		);
	}
}


