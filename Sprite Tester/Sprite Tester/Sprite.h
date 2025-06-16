class sprite
{
public: 
	sprite();  
	~sprite();
	void updatesprite();
	void bouncesprite(int SCREEN_W, int SCREEN_H);
	bool load_animated_sprite(int size);
	void drawSprite();
	void scaredSprite();
	void babySprite();
	void freezeSprite();
	void spinningSprite();
	void setPower(int power);  // 0=spinning, 1=scared, 2=baby, 3=freeze
	void collision(sprite aliens[], int size, int currentIndex, int SCREEN_W, int SCREEN_H);
	int getX(){return x;}
	int getY(){return y;}
	bool hasSpinningPower() const {return specialtyPower[0];}
	bool hasScaredPower() const {return specialtyPower[1];}
	bool hasBabyPower() const {return specialtyPower[2];}
	bool hasFreezePower() const {return specialtyPower[3];}
	bool live;
	bool specialtyPower[4];  
	void destroy_images();
	bool collisionIsTrue;
	double collisionTime;

private:
	int x,y;
	int width,height;
	int xspeed,yspeed;
	int xdelay,ydelay;
	int xcount,ycount;
	int curframe,maxframe;
	int framecount,framedelay;
	int scaredLifetime;  
	int spinningLifetime;
	float scale;
	float rotation_angle;
	ALLEGRO_COLOR currentColor;
	ALLEGRO_BITMAP *image[9];
};