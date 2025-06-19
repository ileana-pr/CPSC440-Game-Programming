#pragma once
#include <allegro5/allegro.h>

class Food {
public:
    Food();
    ~Food();
    
    void Init(ALLEGRO_BITMAP* foodSprite);
    void DrawFood();
    void StartFood(int WIDTH, int HEIGHT);
    void UpdateFood();
    void CollideFood(float playerX, float playerY, int playerWidth, int playerHeight);
    
    bool isLive() { return live; }
    int getScore() { return score; }

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
}; 