#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "player.h"

player::~player()
{
	al_destroy_bitmap(image);
}
player::player(int HEIGHT)
{

	image = al_create_bitmap(64,64);   
	if(!image) {
		exit(1);
	}

	al_set_target_bitmap(image);
	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_draw_filled_rectangle(0,25,64,39,al_map_rgb(75, 75, 75));
	al_draw_filled_rectangle(25,0,39,64,al_map_rgb(50, 50, 50));		
	al_draw_circle(32,32,8,al_map_rgb(0, 0, 0),5);

	al_draw_line(0,32,64,32,al_map_rgb(255, 100, 255),2);
	al_draw_line(32,0,32,64,al_map_rgb(255, 100, 255),2);
	al_draw_circle(32,32,16,al_map_rgb(200, 200, 200),5);

	// add yellow triangle 
	al_draw_filled_triangle(32, 2, 26, 14, 38, 14, al_map_rgb(255,255,0));

	x = 20;
	y = HEIGHT / 2;

	speed = 7;
	boundx = al_get_bitmap_width(image);
	boundy = al_get_bitmap_height(image);

	dir = 0; // set direction to up 
}

// collision detection 
bool player::playerCollision(int new_x, int new_y, BadGuy BadGuys[], int cSize)
{
	for(int i = 0; i < cSize; i++)
	{
		if(BadGuys[i].getLive())
		{
			// check if player rectangle would overlap with badguy rectangle
			if(new_x > (BadGuys[i].getX() - BadGuys[i].getBoundX()) &&
				new_x < (BadGuys[i].getX() + BadGuys[i].getBoundX()) &&
				new_y > (BadGuys[i].getY() - BadGuys[i].getBoundY()) &&
				new_y < (BadGuys[i].getY() + BadGuys[i].getBoundY()))
			{
				return true; 
			}
		}
	}
	return false; // no collision
}

void player::DrawPlayer()
{
	float angle = 0;
	switch(dir) {
		case 0: angle = 0; break; // up
		case 1: angle = ALLEGRO_PI / 2; break; // right
		case 2: angle = ALLEGRO_PI; break; // down
		case 3: angle = 3 * ALLEGRO_PI / 2; break; // left
	}
	al_draw_rotated_bitmap(image, boundx/2, boundy/2, x + boundx/2, y + boundy/2, angle, 0);
}
void player::MoveUp(BadGuy BadGuys[], int cSize)
{
	dir = 0;
	int new_y = y - speed;
	if(new_y < 0)
		new_y = 0;
	
	if(!playerCollision(x, new_y, BadGuys, cSize))
		y = new_y;
}
void player::MoveDown(int HEIGHT, BadGuy BadGuys[], int cSize)
{
	dir = 2;
	int new_y = y + speed;
	if(new_y > HEIGHT-boundy)
		new_y = HEIGHT-boundy;
	
	if(!playerCollision(x, new_y, BadGuys, cSize))
		y = new_y;
}
void player::MoveLeft(BadGuy BadGuys[], int cSize)
{
	dir = 3;
	int new_x = x - speed;
	if(new_x < 0)
		new_x = 0;
	
	if(!playerCollision(new_x, y, BadGuys, cSize))
		x = new_x;
}
void player::MoveRight(int WIDTH, BadGuy BadGuys[], int cSize)
{
	dir = 1;
	int new_x = x + speed;
	if(new_x > WIDTH-boundx)
		new_x = WIDTH-boundx;
	
	
	if(!playerCollision(new_x, y, BadGuys, cSize))
		x = new_x;
}


