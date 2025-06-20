#pragma once
#include <allegro5/allegro.h>

class Food {
public:
    Food();
    ~Food();
    
    void Init(ALLEGRO_BITMAP* foodSprite);
    void DrawFood();
    void StartFood(int WIDTH, int HEIGHT, Food foods[], int numFoods);
    void UpdateFood();
    void CollideFood(float playerX, float playerY, int playerWidth, int playerHeight);
    void SetSpeed(float newSpeed) { speed = newSpeed; }
    
    bool isLive() { return live; }
    int getScore() { return score; }
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
    int score;
    ALLEGRO_BITMAP* image;
    int type;  // which food sprite to use

    bool CheckSpawnCollision(Food foods[], int numFoods, float newX, float newY);
}; 