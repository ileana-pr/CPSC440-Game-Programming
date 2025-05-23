#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_primitives.h>	
#include <allegro5\allegro_native_dialog.h> 

int main(void)
{

	ALLEGRO_DISPLAY *Screen = NULL;

	if(!al_init())
	{
		al_show_native_message_box(NULL, "Error!", "Allegro has failed to initialize.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	int width=840, height=600;
	Screen = al_create_display(width, height);
	if(Screen == NULL)
	{
		al_show_native_message_box(Screen, "Error!", "Failed to create the display.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	bool draw = false, done=false;;
	int pos_x = width / 2;
	int pos_y = height / 2;


	ALLEGRO_EVENT_QUEUE *event_queue = NULL;


	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	ALLEGRO_FONT *font24 = al_load_font("AppleGaramond.ttf", 24, 0);
	event_queue = al_create_event_queue();


	al_register_event_source(event_queue, al_get_display_event_source(Screen));
	al_clear_to_color(al_map_rgb(0,0,0));

	if(!al_install_mouse()) {
		al_show_native_message_box(Screen, "Error!", "Failed to initialize the mouse!\n.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
      return -1;
   }

	al_register_event_source(event_queue, al_get_mouse_event_source());

	//al_hide_mouse_cursor(display);

	while(!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
		{
			done = true;
		}
		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if(ev.mouse.button & 1)
			{
				draw = true;
				pos_x = ev.mouse.x;
				pos_y = ev.mouse.y;
			}
		}


		if(draw)
		{
			if( pos_x<=200 && pos_x>= 0 && pos_y>=0 && pos_y<=200){

				al_draw_filled_rectangle(0,0,200,200,al_map_rgb(150, 150, 150));
				al_draw_filled_rectangle(400,400,640,480,al_map_rgb(0, 0, 0));
				al_draw_textf(font24, al_map_rgb(255, 255, 255), pos_x,pos_y, ALLEGRO_ALIGN_LEFT, "The mouse is located at = %i / %i" , pos_x, pos_y);
				al_flip_display();
			}else if ( pos_x>=400 && pos_x<=640 && pos_y>=400 && pos_y<=480){
				al_draw_filled_rectangle(400,400,640,480,al_map_rgb(150, 0, 150));
				al_draw_filled_rectangle(0,0,200,200,al_map_rgb(0, 0, 0));
				al_draw_textf(font24, al_map_rgb(255, 255, 255), pos_x,pos_y, ALLEGRO_ALIGN_LEFT, "The mouse is located at = %i / %i" , pos_x, pos_y);
				al_flip_display();
			}
			else{
				al_draw_filled_rectangle(0,0,200,200,al_map_rgb(0, 0, 0));
				al_draw_filled_rectangle(400,400,640,480,al_map_rgb(0, 0, 0));
				al_draw_textf(font24, al_map_rgb(255, 255, 255), pos_x,pos_y, ALLEGRO_ALIGN_LEFT, "The mouse is located at = %i / %i" , pos_x, pos_y);
				al_flip_display();
			}

			draw=false;
		}


		al_clear_to_color(al_map_rgb(0,0,0));
	}

	al_destroy_event_queue(event_queue);
	al_destroy_display(Screen);						//destroy our display object
	system("pause");
	return 0;
}