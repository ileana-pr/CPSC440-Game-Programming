#include "Spider.h"
#include <cstdlib>

Spider::Spider()
{
    image = NULL;
    live = false;
    speed = 3;  
    boundx = 32;  
    boundy = 32; 
    type = rand() % 4;  
}

Spider::~Spider()
{
}

void Spider::Init(ALLEGRO_BITMAP* spriteSheet)
{
    image = spriteSheet;
}

void Spider::DrawSpider()
{
    if(live && image)
    {
        const int SPIDER_ROW = 7;  
        const int START_COL = 8;   
        
        al_draw_bitmap_region(image, 
            (START_COL + type) * boundx, SPIDER_ROW * boundy,  
            boundx, boundy,              
            x, y,                        
            0);                         
    }
}

bool Spider::CheckCollision(Food foods[], int numFoods, Spider spiders[], int numSpiders, float newX, float newY)
{
    // Check collision with food
    for(int i = 0; i < numFoods; i++)
    {
        if(foods[i].isLive())
        {
            if(newX > (foods[i].getX() - foods[i].getBoundX()) &&
               newX < (foods[i].getX() + foods[i].getBoundX()) &&
               newY > (foods[i].getY() - foods[i].getBoundY()) &&
               newY < (foods[i].getY() + foods[i].getBoundY()))
            {
                return true;
            }
        }
    }

    // Check collision with other spiders
    for(int i = 0; i < numSpiders; i++)
    {
        if(spiders[i].isLive() && &spiders[i] != this)
        {
            if(newX > (spiders[i].getX() - spiders[i].getBoundX()) &&
               newX < (spiders[i].getX() + spiders[i].getBoundX()) &&
               newY > (spiders[i].getY() - spiders[i].getBoundY()) &&
               newY < (spiders[i].getY() + spiders[i].getBoundY()))
            {
                return true;  
            }
        }
    }
    
    return false;  // no collision
}

void Spider::StartSpider(int WIDTH, int HEIGHT, Food foods[], int numFoods, Spider spiders[], int numSpiders)
{
    if(!live)
    {
        if(rand() % 150 == 0)  
        {
            float newX = WIDTH;
            float newY;
            bool validPosition = false;
            int attempts = 0;
            const int MAX_ATTEMPTS = 10;
            const int BORDER_SIZE = 32;  

            while(!validPosition && attempts < MAX_ATTEMPTS)
            {
                // Spawn between top and bottom borders
                newY = BORDER_SIZE + (rand() % (HEIGHT - 2 * BORDER_SIZE - boundy));
                if(!CheckCollision(foods, numFoods, spiders, numSpiders, newX, newY))
                {
                    validPosition = true;
                    live = true;
                    x = newX;
                    y = newY;
                    type = rand() % 4; 
                }
                attempts++;
            }
        }
    }
}

void Spider::UpdateSpider()
{
    if(live)
    {
        x -= speed;
        
        if(x < -boundx) 
            live = false;
    }
}

bool Spider::CollideSpider(float playerX, float playerY, int playerWidth, int playerHeight)
{
    if(live)
    {
        if(x < playerX + playerWidth &&
           x + boundx > playerX &&
           y < playerY + playerHeight &&
           y + boundy > playerY)
        {
            live = false;
            return true;  
        }
    }
    return false;  
} 