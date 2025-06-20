#pragma once
#include <allegro5/allegro.h>
#include "Food.h"

class Spider {
public:
    Spider();
    ~Spider();
    
    void Init(ALLEGRO_BITMAP* spriteSheet);
    void DrawSpider();
    void StartSpider(int WIDTH, int HEIGHT, Food foods[], int numFoods, Spider spiders[], int numSpiders);
    void UpdateSpider();
    void CollideSpider(float playerX, float playerY, int playerWidth, int playerHeight);
    void SetSpeed(float newSpeed) { speed = newSpeed; }
    
    bool isLive() { return live; }
    float getX() { return x; }
    float getY() { return y; }
    int getBoundX() { return boundx; }
    int getBoundY() { return boundy; }

private:
    float x;
    float y;
    bool live;
    float speed;
    int boundx;
    int boundy;
    ALLEGRO_BITMAP* image;
    int type;  // which spider sprite to use from row 8

    bool CheckCollision(Food foods[], int numFoods, Spider spiders[], int numSpiders, float newX, float newY);
}; 