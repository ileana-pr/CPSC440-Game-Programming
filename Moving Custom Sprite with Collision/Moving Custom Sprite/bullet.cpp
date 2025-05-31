#include "bullet.h"
bullet::bullet()
{
	alive = false;
	bmp = NULL;
	srand(time(0));
}
bool bullet::getStatus()
{
	return alive;
}
void bullet::set_bitmap(ALLEGRO_BITMAP* b)
{
	bmp = b;
}
void bullet::fire()
{
	x = rand() % 625 + 10; 
	y = 10;
	alive = true;
}
void bullet::erase_bullet()
{
	al_draw_filled_rectangle(x, y, x + 16, y + 16, al_map_rgb(0, 0, 0)); 
}
int bullet::move_bullet(int arrowX, int arrowY, int width, int length, int height)
{
	y++;
	
	al_draw_bitmap(bmp, x, y, 0);

	// collision for 16x16 bullet
	if (x + 16 > arrowX && x < arrowX + width && y + 16 > arrowY && y < arrowY + length) {
		al_draw_filled_rectangle(x, y, x + 16, y + 16, al_map_rgb(0, 0, 0));
		alive = false;
		return 1;
	}
	if (y > height)
		alive = false;
	return 0;
}