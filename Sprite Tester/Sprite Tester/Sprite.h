class sprite
{
public: 
	~sprite();
	void updatesprite();
	void bouncesprite(int SCREEN_W, int SCREEN_H);
	void load_animated_sprite(int size);
	void drawSprite();
	void scaredSprite();
	void babySprite();
	void spinningSprite();
	void freezeSprite();
	void collision(sprite aliens[], int size, int currentIndex, int SCREEN_W, int SCREEN_H);
	bool isColliding(sprite& other);
	int getX(){return x;}
	int getY(){return y;}


private:
	int x,y;
	int width,height;
	int xspeed,yspeed;
	int xdelay,ydelay;
	int xcount,ycount;
	int curframe,maxframe,animdir;
	int framecount,framedelay;
	bool specialtyPower[4];  // [spinning, scared, baby, freeze]
	bool collisionIsTrue; 
	float scale;
	float rotation;
	ALLEGRO_COLOR currentColor;
	double collisionTime;
	ALLEGRO_BITMAP *image[9];
};