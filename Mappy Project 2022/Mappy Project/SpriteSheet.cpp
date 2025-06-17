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
	x = 80;
	y = -10;

	maxFrame = 8;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 6;
	frameWidth = 50;
	frameHeight = 64;
	animationColumns = 8;
	animationDirection = 1;
	isJumping = false;  // start not jumping
	jumpStartFrame = 8; // jumping frames start at index 8 (after walking frames)

	// start in standing position for initial drop
	curFrame = 0;  // use first frame for initial drop

	image = al_load_bitmap("guy.bmp");
	al_convert_mask_to_alpha(image, al_map_rgb(255,0,255));
}

void Sprite::UpdateSprites(int width, int height, int dir)
{
	int oldx = x;
	int oldy = y;

	if(dir == 1){ //right key
		animationDirection = 1; 
		x+=2; 
		if (++frameCount > frameDelay)
		{
			frameCount=0;
			if (++curFrame > maxFrame)
				curFrame=1;
		}
	} else if (dir == 0){ //left key
		animationDirection = 0; 
		x-=2; 
		if (++frameCount > frameDelay)
		{
			frameCount=0;
			if (++curFrame > maxFrame)
				curFrame=1;
		}
	}else //represent that they hit the space bar and that mean direction = 0
		animationDirection = dir;

	//check for collided with foreground tiles
	if (animationDirection==0)
	{ 
		if (collided(x, y + frameHeight)) { //collision detection to the left
			x = oldx; 
			y= oldy;
		}

	}
	else if (animationDirection ==1)
	{ 
		if (collided(x + frameWidth, y + frameHeight)) { //collision detection to the right
			x = oldx; 
			y= oldy;
		}
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
	// if jump equals JUMPIT, we're on the ground
	if (jump == JUMPIT) { 
		// check if there's ground below us
		if (!collided(x + frameWidth/2, y + frameHeight + 5)) {
			jump = -1; // start falling if no ground below
		}
		isJumping = false; // not jumping when on ground
	}
	else
	{
		// going up (positive jump value means moving up)
		if (jump > 0) {
			// only stop upward movement if we hit blocks at the top of screen
			if (y < mapblockheight && collided(x + frameWidth/2, y)) {
				jump = -1; // start falling
				isJumping = false;
			} else {
				// move upward
				y -= jump/3; 
				jump--; 
				isJumping = true;
				
				// use first two jump frames for going up
				if (jump > JUMPIT/2) {
					curFrame = jumpStartFrame; // starting jump pose
				} else {
					curFrame = jumpStartFrame + 1; // mid-jump pose
				}
			}
		}
		// if jump is 0 or negative, we should be falling
		else {
			jump = -1; // make sure we're falling
			y += 3; // move downward
			// use last two jump frames for falling
			curFrame = jumpStartFrame + 2; // falling pose
		}
	}

	// falling (negative jump value means moving down)
	if (jump < 0) 
	{ 
		// check if we hit the ground
		if (collided(x + frameWidth/2, y + frameHeight))
		{ 
			jump = JUMPIT; // back to ground state
			isJumping = false;
			curFrame = jumpStartFrame + 3; // landing pose
			
			// make sure we don't get stuck in the ground
			while (collided(x + frameWidth/2, y + frameHeight))
			{
				y -= 3;
			}
		} 
		else {
			y += 3; // keep falling if we haven't hit ground
			curFrame = jumpStartFrame + 2; // falling pose
		}
	}
	return jump;
}