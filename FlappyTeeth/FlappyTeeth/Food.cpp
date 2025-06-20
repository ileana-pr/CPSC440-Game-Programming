#include "Food.h"
#include <cstdlib>

Food::Food()
{
    image = NULL;
    live = false;
    speed = 3;
    score = 0;
    boundx = 72;  
    boundy = 72; 
    type = rand() % (16 * 8);  
}

Food::~Food()
{
}

void Food::Init(ALLEGRO_BITMAP* foodSprite)
{
    image = foodSprite;
}

void Food::DrawFood()
{
    if(live && image)
    {
        int col = type % 16;  
        int row = type / 16;  
        
        al_draw_bitmap_region(image, 
            col * boundx, row * boundy,  
            boundx, boundy,              
            x, y,                        
            0);                         
    }
}

bool Food::CheckSpawnCollision(Food foods[], int numFoods, float newX, float newY)
{
    for(int i = 0; i < numFoods; i++)
    {
        if(foods[i].isLive() && &foods[i] != this)  
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
    return false; 
}

void Food::StartFood(int WIDTH, int HEIGHT, Food foods[], int numFoods)
{
    if(!live)
    {
        if(rand() % 100 == 0) 
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
                if(!CheckSpawnCollision(foods, numFoods, newX, newY))
                {
                    validPosition = true;
                    live = true;
                    x = newX;
                    y = newY;
                    type = rand() % (16 * 8);
                }
                attempts++;
            }
        }
    }
}

void Food::UpdateFood()
{
    if(live)
    {
        x -= speed;
        
        if(x < -boundx) 
            live = false;
    }
}

bool Food::CollideFood(float playerX, float playerY, int playerWidth, int playerHeight)
{
    if(live)
    {
        if(x < playerX + playerWidth &&
           x + boundx > playerX &&
           y < playerY + playerHeight &&
           y + boundy > playerY)
        {
            score += 10;
            live = false;
            return true;  
        }
    }
    return false;  
} 