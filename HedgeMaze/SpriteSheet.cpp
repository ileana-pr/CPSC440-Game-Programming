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
	// Load original
	ALLEGRO_BITMAP* temp_image = al_load_bitmap("guy.png");
	if(!temp_image) {
		cout << "failed to load guy.png" << endl;
		return;
	}

	// create smaller bitmap 
	image = al_create_bitmap(96, 128);  // 24x32 * 4 frames
	if(!image) {
		cout << "failed to create resized bitmap" << endl;
		al_destroy_bitmap(temp_image);
		return;
	}

	// Draw large image onto smaller bitmap
	al_set_target_bitmap(image);
	al_draw_scaled_bitmap(temp_image,
		0, 0,                                    // source x, y
		al_get_bitmap_width(temp_image),         // source width
		al_get_bitmap_height(temp_image),        // source height
		0, 0,                                    // dest x, y  
		96, 128,                                 // dest width, height
		0                                        // flags
	);
	al_destroy_bitmap(temp_image);

	// Set correct frame dimensions 
	frameWidth = 24;     
	frameHeight = 32;    
	animationColumns = 4;
	animationRows = 4;
	maxFrame = 3;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 8;
	animationDirection = 1;

	// Find start position 
	for (int my = 0; my < mapheight; my++) {
		for (int mx = 0; mx < mapwidth; mx++) {
			BLKSTR* block = MapGetBlock(mx, my);
			if (block->user1 == 7) {
				x = (mx + 1) * mapblockwidth;
				y = my * mapblockheight;
				break;
			}
		}
	}

	al_convert_mask_to_alpha(image, al_map_rgb(255, 0, 255));

	scaleX = (mapblockwidth * 2.0f) / frameWidth;
	scaleY = scaleX;  // maintain aspect ratio
}

void Sprite::UpdateSprites(int width, int height, int dir)
{
	int oldx = x;
	int oldy = y;
	
	// Base movement speed on tile size
	const float MOVE_SPEED = mapblockwidth / 16.0f;  // adjust divisor to tune speed

	// Update position and direction
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

	// Update animation frame if moving
	if (dir != 4) {
		if (++frameCount > frameDelay) {
			frameCount = 0;
			if (++curFrame > maxFrame)
				curFrame = 0;
		}
	}

	// Collision detection with map boundaries
	if (x < 0) x = 0;
	if (y < 0) y = 0;
	if (x > width - (frameWidth * scaleX)) x = width - (frameWidth * scaleX);
	if (y > height - (frameHeight * scaleY)) y = height - (frameHeight * scaleY);

	// Collision detection with tiles
	float scaledWidth = frameWidth * scaleX;
	float scaledHeight = frameHeight * scaleY;
	
	if (collided(x + scaledWidth/2, y + scaledHeight) || 
		collided(x, y + scaledHeight) ||
		collided(x + scaledWidth, y + scaledHeight)) {
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
	int fx = (curFrame % animationColumns) * frameWidth;
	int fy = 0;

	// Calculate scale to fit character within two map tiles
	float targetWidth = mapblockwidth * 2;  // width of two tiles
	float scaleX = targetWidth / frameWidth;
	float scaleY = scaleX; // maintain aspect ratio

	// Select the correct row based on direction
	switch(animationDirection) {
		case 0: // left
			fy = 2 * frameHeight;
			break;
		case 1: // right
			fy = 0;
			break;
		case 2: // up
			fy = 3 * frameHeight;
			break;
		case 3: // down
			fy = frameHeight;
			break;
		case 4: // standing
			curFrame = 0;
			break;
	}

	// Draw the sprite scaled to fit two map tiles
	al_draw_scaled_bitmap(image,
		fx, fy,                           // source x, y
		frameWidth, frameHeight,          // source width, height
		x - xoffset, y - yoffset,         // dest x, y
		frameWidth * scaleX, frameHeight * scaleY,  // dest width, height
		0                                 // flags
	);
}

