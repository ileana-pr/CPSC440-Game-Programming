#include "SpriteSheet.h"

Sprite::Sprite()
{
	image=NULL;
}
Sprite::~Sprite()
{
	al_destroy_bitmap(image);
}
void Sprite::InitSprites(int width, int height)
{
	// initial position
	x = 80;
	y = 80;  // changed from -10 since we don't need falling

	maxFrame = 8;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 6;
	frameWidth = 50;
	frameHeight = 64;
	animationColumns = 8;
	animationDirection = 4;  // start standing still

	image = al_load_bitmap("guy.png");
	al_convert_mask_to_alpha(image, al_map_rgb(255, 0, 255));
}

void Sprite::UpdateSprites(int width, int height, int dir)
{
	int oldx = x;
	int oldy = y;
	const int MOVE_SPEED = 2;

	// update position
	switch(dir) {
		case 0: // left
			x -= MOVE_SPEED;
			animationDirection = 0;
			break;
		case 1: // right
			x += MOVE_SPEED;
			animationDirection = 1;
			break;
		case 2: // up
			y -= MOVE_SPEED;
			animationDirection = 2;
			break;
		case 3: // down
			y += MOVE_SPEED;
			animationDirection = 3;
			break;
		case 4: // standing
			animationDirection = 4;
			break;
	}

	// animation frame
	if (dir != 4) {  // if moving
		if (++frameCount > frameDelay) {
			frameCount = 0;
			if (++curFrame > maxFrame)
				curFrame = 1;
		}
	}

	// collision
	if (collided(x + frameWidth/2, y + frameHeight) || 
		collided(x, y + frameHeight) ||
		collided(x + frameWidth, y + frameHeight)) {
		x = oldx;
		y = oldy;
	}
}

bool Sprite::CollisionEndBlock()
{
	if (endValue(x + frameWidth/2, y + frameHeight + 5))
		return true;
	else
		return false;
}

void Sprite::DrawSprites(int xoffset, int yoffset)
{
	int fx;
	int fy;
	
	if (isJumping) {
		// jumping frames are in the bottom row
		fx = ((curFrame - jumpStartFrame) % 4) * frameWidth;
		fy = frameHeight; // second row
	} else {
		// walking frames are in the top row
		fx = (curFrame % animationColumns) * frameWidth;
		fy = 0;
	}

	if (animationDirection==1){
		al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x-xoffset, y-yoffset, 0);
	}else if (animationDirection == 0 ){
		al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x-xoffset, y-yoffset, ALLEGRO_FLIP_HORIZONTAL);
	}else if (animationDirection == 2 ){
		al_draw_bitmap_region(image, 0, fy, frameWidth, frameHeight, x-xoffset, y-yoffset, 0);
	}
}

int Sprite::jumping(int jump, const int JUMPIT)
{	
	//if jump = JUMPIT, we're on the ground 
	if (jump == JUMPIT) { 
		if (!collided(x + frameWidth/2, y + frameHeight + 5)) {
			jump = -1; 
		}
		isJumping = false; 
	}
	else
	{
		// if jump is greater than 0, we're in the air
		if (jump > 0) {
			if (y < mapblockheight && collided(x + frameWidth/2, y)) {
				jump = -1; 
				isJumping = false;
			} else {
				y -= jump/3; 
				jump--; 
				isJumping = true;
				
				if (jump > JUMPIT/2) {
					curFrame = jumpStartFrame; // starting jump pose 
				} else {
					curFrame = jumpStartFrame + 1; //mid-jump pose 
				}
			}
		}
		// if jump is less than 0 , we're falling
		else {
			jump = -1; 
			y += 3; 
			curFrame = jumpStartFrame + 2; //falling pose
		}
	}
	// falling, check if we hit the ground
	if (jump < 0) 
	{ 
		if (collided(x + frameWidth/2, y + frameHeight))
		{ 
			jump = JUMPIT; 
			isJumping = false;
			curFrame = jumpStartFrame + 3; //landing pose
			
			while (collided(x + frameWidth/2, y + frameHeight))
			{
				y -= 3;
			}
		} 
		else {
			y += 3; 
			curFrame = jumpStartFrame + 2; // falling pose
		}
	}
	return jump;
}