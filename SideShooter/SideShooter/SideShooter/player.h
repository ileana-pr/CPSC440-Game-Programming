#ifndef PLAYERH
#define PLAYERH
class player
{
public:
	player(int HEIGHT);
	~player();
	void DrawPlayer();
	void MoveUp();
	void MoveDown(int HEIGHT);
	void MoveLeft();
	void MoveRight();
	int getBoundX(){return boundx;}
	int getBoundY(){return boundy;}
	int getX(){return x;}
	int getY(){return y;}
	void removeLife();
	int getLives(){return lives;}
	int getScore(){return score;}
private:
	int x;
	int y;
	int lives;
	int speed;
	int boundx;
	int boundy;
	int score;
	int image_index;
	ALLEGRO_BITMAP *images[5];
};
#endif
