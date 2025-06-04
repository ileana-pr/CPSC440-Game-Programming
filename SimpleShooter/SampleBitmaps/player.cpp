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



	x = 20;
	y = HEIGHT / 2;

	speed = 7;
	boundx = al_get_bitmap_width(image);
	boundy = al_get_bitmap_height(image);

}

// collision detection 
bool player::playerCollision(int new_x, int new_y, BadGuy *BadGuys, int cSize)
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
	al_draw_bitmap(image, x,y, 0);
}
void player::MoveUp(BadGuy BadGuys[], int cSize)
{
	int new_y = y - speed;
	if(new_y < 0)
		new_y = 0;
	
	if(!playerCollision(x, new_y, BadGuys, cSize))
		y = new_y;
}
void player::MoveDown(int HEIGHT, BadGuy BadGuys[], int cSize)
{
	int new_y = y + speed;
	if(new_y > HEIGHT-boundy)
		new_y = HEIGHT-boundy;
	
	if(!playerCollision(x, new_y, BadGuys, cSize))
		y = new_y;
}
void player::MoveLeft(BadGuy BadGuys[], int cSize)
{
	int new_x = x - speed;
	if(new_x < 0)
		new_x = 0;
	
	if(!playerCollision(new_x, y, BadGuys, cSize))
		x = new_x;
}
void player::MoveRight(int WIDTH, BadGuy BadGuys[], int cSize)
{
	int new_x = x + speed;
	if(new_x > WIDTH-boundx)
		new_x = WIDTH-boundx;
	
	
	if(!playerCollision(new_x, y, BadGuys, cSize))
		x = new_x;
}

