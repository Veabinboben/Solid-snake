#pragma once
class berry {
	friend class snake;
private:
	int x;
	int y;
public:
	berry();	
	int getx();
	int gety();
	void summon();	
	void draw2D();

};
class snake
{
private:
	int yspeed;
	int xspeed;
	struct cell {
		int x;
		int y;
	};
	int length;
public:
	
	cell* body;
	snake();
	
	int getlength();
	void increase();
	
	int move();
	
	void changespeed();

	void draw2D();
	
	void checkforberry(berry& a);

};