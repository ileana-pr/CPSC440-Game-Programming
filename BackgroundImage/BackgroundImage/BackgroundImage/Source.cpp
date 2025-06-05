//Name: Ileana Perez 
// CPSC 440: Lab 8

#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

int main(int argc, char **argv){

	const float FPS = 60;
	const int SCREEN_W = 900;
	const int SCREEN_H = 800;
	const int bee_SIZE = 64;
	const int bee_draw_size = 128;
	int bee_flip = 0;
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;

	float bee_x = SCREEN_W / 2.0 - bee_SIZE / 2.0;
	float bee_y = SCREEN_H / 2.0 - bee_SIZE / 2.0;
	float bee_dx = 0, bee_dy = -4.0;
	bool redraw = true;
	bool bee_moving = true;
	ALLEGRO_BITMAP *image=NULL;
	ALLEGRO_BITMAP *bee = NULL;
	float angle = 0; 
	float target_angle = 0;
	bool rotating = false;

	if(!al_init()) {
		return -1;
	}

	al_install_keyboard();

	timer = al_create_timer(1.0 / FPS);
	if(!timer) {
		return -1;
	}

	display = al_create_display(SCREEN_W, SCREEN_H);
	if(!display) {
		al_destroy_timer(timer);
		return -1;
	}



	al_init_image_addon();
	image = al_load_bitmap("flowers.png");
	bee = al_load_bitmap("bee.png");
	al_convert_mask_to_alpha(bee, al_map_rgb(255, 0, 255));
	event_queue = al_create_event_queue();
	if(!event_queue) {
		al_destroy_bitmap(bee);
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_clear_to_color(al_map_rgb(0,0,0));

	al_flip_display();

	al_start_timer(timer);

	while(1)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_TIMER) {
			if(bee_moving) {
				bee_x += bee_dx;
				bee_y += bee_dy;

				// left edge
				if(bee_x < 0) {
					bee_x = 0;
					bee_dx = -bee_dx;
					target_angle = angle + 3.14f;
					rotating = true;
				}
				// right edge
				if(bee_x > SCREEN_W - bee_draw_size) {
					bee_x = SCREEN_W - bee_draw_size;
					bee_dx = -bee_dx;
					target_angle = angle + 3.14f;
					rotating = true;
				}
				// top edge
				if(bee_y < 0) {
					bee_y = 0;
					bee_dy = -bee_dy;
					target_angle = angle + 3.14f;
					rotating = true;
				}
				// bottom edge
				if(bee_y > SCREEN_H - bee_draw_size) {
					bee_y = SCREEN_H - bee_draw_size;
					bee_dy = -bee_dy;
					target_angle = angle + 3.14f;
					rotating = true;
				}
			}

			// rotate towards target_angle
			if(rotating) {
				float rotation_speed = 0.1f; // adjust for smoothness
				if(angle < target_angle) {
					angle += rotation_speed;
					if(angle >= target_angle) {
						angle = target_angle;
						rotating = false;
					}
				} else if(angle > target_angle) {
					angle -= rotation_speed;
					if(angle <= target_angle) {
						angle = target_angle;
						rotating = false;
					}
				}
			}

			redraw = true;
		}
		
		else if(ev.keyboard.keycode == ALLEGRO_KEY_SPACE) {
			bee_moving = !bee_moving;
		}
		else if(ev.keyboard.keycode == ALLEGRO_KEY_LEFT) {
			bee_flip = ALLEGRO_FLIP_HORIZONTAL;
		}
		else if(ev.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
			bee_flip = 0;
		}
		else if(ev.keyboard.keycode == ALLEGRO_KEY_UP) {
			bee_flip = 0;
		}
		else if(ev.keyboard.keycode == ALLEGRO_KEY_DOWN) {
			bee_flip = ALLEGRO_FLIP_VERTICAL;
		}
	
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
		break;
		}

		if(redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			al_clear_to_color(al_map_rgb(0,0,0));
			al_draw_scaled_bitmap(
				image, 
				0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image), 
				0, 0, SCREEN_W, SCREEN_H, 
				0
			);
			float scale = (float)bee_draw_size / (float)al_get_bitmap_width(bee);
			al_draw_scaled_rotated_bitmap(
				bee,
				al_get_bitmap_width(bee)/2, al_get_bitmap_height(bee)/2,
				bee_x + bee_draw_size/2, bee_y + bee_draw_size/2,
				scale, scale,
				angle,
				bee_flip
			);
			al_flip_display();
		}
	}

	al_destroy_bitmap(bee);
	al_destroy_bitmap(image);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	system("pause");
	return 0;
}