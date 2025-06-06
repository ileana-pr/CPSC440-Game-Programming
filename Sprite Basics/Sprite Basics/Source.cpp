#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h> ///include the header to initialize the image addon
#include <allegro5/allegro_native_dialog.h>
#include <iostream>
using namespace std;
# define M_PI           3.14159265358979323846  /* pi */

int main()
{
	cout<<"Left Arrow Rotates Sprite Left\n";
	cout<<"Right Arrow Rotates Sprite Right\n";
	cout<<"Up Arrow Scales the sprites larger\n";
	cout<<"Down Arrow Scales the sprites smaller\n";
	cout<<"D draws the sprites in the natural form\n";
	cout<<"H draws the sprites with a Horizontal Flip\n";
	cout<<"V draws the sprites with a Vertical Flip\n";
	cout<<"B draws the sprites with a Vertical Flip and Horitzontal Flip\n";
	cout<<"T draws the sprites with a random tinted color\n";
	cout<<"P draws only a portion of the bitmap to the screen\n";
	ALLEGRO_DISPLAY *Screen;
	ALLEGRO_EVENT_QUEUE *EventQueue;
	ALLEGRO_EVENT Event;
	ALLEGRO_BITMAP *Image = NULL; ///object the holds the graphic. initialize it empty
	bool Exit = false;

	al_init();
	al_init_image_addon(); /// this must be called to load images. has to be called after al_init

	if(!al_init_image_addon())
	{
		return -1;
	}

	int width = 900;
	int height = 800;
	Screen = al_create_display(width, height);



	EventQueue = al_create_event_queue();
	al_register_event_source(EventQueue, al_get_display_event_source(Screen));
	if(!al_install_keyboard()) ///setup the keyboard
	{
		al_show_native_message_box(NULL, "Error!", "Failed to install keyboard.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	al_register_event_source(EventQueue, al_get_keyboard_event_source()); ///Tell allegro to get events from the keyboard
	Image = al_load_bitmap("piratepenguin.png"); ///load the bitmap from a file


	int x=width/2;
	int y=height/2;
	float angle=0;
	float size = 1;
	float w = al_get_bitmap_width(Image);
	float h = al_get_bitmap_height(Image);
	al_flip_display();
	while(Exit == false)
	{
		int xposition = x-(w/2);
		int yposition = y-(h/2);
		al_wait_for_event(EventQueue, &Event);

		if(Event.type == ALLEGRO_EVENT_KEY_DOWN) ///look for keyboard events
		{
			al_clear_to_color(al_map_rgb(0,0,0));
			if(Event.keyboard.keycode == ALLEGRO_KEY_LEFT){
				angle -= 0.1;
				al_draw_rotated_bitmap(Image, w / 2, h / 2, x, y, angle, 0);
			}else if(Event.keyboard.keycode == ALLEGRO_KEY_RIGHT){
				angle += 0.1;
				al_draw_rotated_bitmap(Image, w / 2, h / 2, x, y, angle, 0);
			}else if(Event.keyboard.keycode == ALLEGRO_KEY_UP){
				size += .2;
				xposition = x-(w*size/2);
				yposition = y-(h*size/2);
				al_draw_scaled_bitmap(Image, 0, 0, w, h,xposition, yposition,w*size,h*size,0);
			}else if(Event.keyboard.keycode == ALLEGRO_KEY_DOWN){
				size -= .2;
				xposition = x-(w*size/2);
				yposition = y-(h*size/2);
				al_draw_scaled_bitmap(Image, 0, 0, w, h,xposition, yposition,w*size,h*size,0);
			}else if(Event.keyboard.keycode == ALLEGRO_KEY_D){
				al_draw_bitmap(Image,xposition,yposition , 0);
			}else if(Event.keyboard.keycode == ALLEGRO_KEY_H){
				al_draw_bitmap(Image,xposition,yposition , ALLEGRO_FLIP_HORIZONTAL);
			}else if(Event.keyboard.keycode == ALLEGRO_KEY_V){
				al_draw_bitmap(Image,xposition,yposition , ALLEGRO_FLIP_VERTICAL);
			}else if(Event.keyboard.keycode == ALLEGRO_KEY_B){
				al_draw_bitmap(Image,xposition,yposition , ALLEGRO_FLIP_HORIZONTAL | ALLEGRO_FLIP_VERTICAL);
			}else if(Event.keyboard.keycode == ALLEGRO_KEY_T){
				float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				al_draw_tinted_bitmap(Image, al_map_rgba_f(r, g, b, 1), xposition, yposition, 0); 
			}else if(Event.keyboard.keycode == ALLEGRO_KEY_P){
				int x1 = rand () % al_get_bitmap_width(Image);
				int y1 = rand () % al_get_bitmap_height(Image);
				al_draw_bitmap_region(Image, 0, 0, x1, y1, xposition, yposition, 0);
			}else if(Event.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
				Exit=true;
			}
		}

		al_flip_display();

		al_wait_for_event(EventQueue, &Event);

		if(Event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			Exit = true;
		}

	}
	al_destroy_bitmap(Image);


	return 0;
}