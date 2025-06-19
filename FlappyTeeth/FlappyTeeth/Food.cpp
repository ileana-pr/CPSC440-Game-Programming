#include "Food.h"
#include <cstdlib>

Food::Food()
{
    image = NULL;
    live = false;
    speed = 2;
    score = 0;
    boundx = 72;  
    boundy = 72; 
    type = rand() % (16 * 8);  
}

Food::~Food()
{
    // image is destroyed in main
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

void Food::StartFood(int WIDTH, int HEIGHT)
{
    if(!live)
    {
        if(rand() % 100 == 0) 
        {
            live = true;
            x = WIDTH;
            y = rand() % (HEIGHT - boundy);
            type = rand() % (16 * 8);  
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

void Food::CollideFood(float playerX, float playerY, int playerWidth, int playerHeight)
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
        }
    }
} 