#include "arrow.h"
arrowClass::arrowClass()
{
	speed=0;
	x=100;
	y=100;
	dir=1;
	score = 0;
	for(int i=0; i<4; i++)
	{
		arrow_bmp[i]=NULL;
	}
}
arrowClass::~arrowClass()
{
	for(int i=0; i<4; i++)
	{
		al_destroy_bitmap(arrow_bmp[i]);
	}
}
void arrowClass::drawArrow()
{
	al_draw_bitmap(arrow_bmp[getDirection()], getX(), getY(), 0);
}
void arrowClass::create_arrow_bitmap(ALLEGRO_DISPLAY *display)
{
	for(int i=0;i<4; i++)
	{
		arrow_bmp[i]=al_create_bitmap(64,64);   
		if(!arrow_bmp[i]) {
			exit(1);
			al_destroy_display(display);
		}

		al_set_target_bitmap(arrow_bmp[i]);
		al_clear_to_color(al_map_rgb(0, 0, 0)); 

		int x = 32, y = 32;
		int width = 18, height = 40;
		int wing_width = 16, wing_height = 32; 
		int cockpit_width = 8, cockpit_height = 18; 

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

		// small red dot at the tip for the gun
		al_draw_filled_circle(
			x, y - height / 2 - 8, 4,
			al_map_rgb(255,0,0)
		);
	}

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
void arrowClass::erase_arrow()
{

	int left = x ;
	int top = y;
	int right = x + 32;
	int bottom =y + 32;

	al_draw_filled_rectangle(left, top, right, bottom, al_map_rgb(0, 0, 0));
}

void arrowClass::up()
{
	dir=0;
	speed++;
	if (speed > MAXSPEED)
		speed = MAXSPEED;
}

void arrowClass::down()
{
	dir=2;
	speed++;
	if (speed > MAXSPEED)
		speed = MAXSPEED;

}


void arrowClass::left()
{
	dir=3;
	speed++;
	if (speed > MAXSPEED)
		speed = MAXSPEED;

}

void arrowClass::right()
{
	dir=1;
	speed++;
	if (speed > MAXSPEED)
		speed = MAXSPEED;

}
int arrowClass::getDirection()
{
	return dir;
}
int arrowClass::getSpeed()
{
	return speed;
}
int arrowClass::getX()
{
	return x;
}
int arrowClass::getY()
{
	return y;
}
void arrowClass::move_arrow(int width, int height)
{

	//update arrow position based on direction
	switch(dir)
	{
	case 0:
		y -= speed;
		break;
	case 1:
		x += speed;
		break;
	case 2:
		y += speed;
		break;
	case 3:
		x -= speed;
	}

	//keep arrow inside the screen
	if (x > width-32)
	{
		x = width-32;
		speed = 0;
	}
	if (x < 0)
	{
		x = 0;
		speed = 0;
	}
	if (y > height-32)
	{
		y = height-32;
		speed = 0;
	}
	if (y < 0)
	{
		y = 0;
		speed = 0;
	}
}
