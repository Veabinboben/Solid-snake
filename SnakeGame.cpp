#include <iostream>
#include <Windows.h>
#include <stdlib.h>     
#include "ScreenSpecs.h";
#include "Snake.h";
#include <time.h>
using namespace std;


wchar_t  snakebody = 664;
wchar_t berrybody = 44;

	berry::berry()
	{
		srand(time(NULL));
		do {
			x = rand() % gamefieldsize;
			y = rand() % gamefieldsize;
		} while (gamefield[x + y * gamefieldsize] == snakebody);
		gamefield[x + y * gamefieldsize] = berrybody;
		return;
	}
	void berry::summon()
	{
		gamefield[x + y * gamefieldsize] = '0';
		do {
			x = rand() % gamefieldsize;
			y = rand() % gamefieldsize;
		} while (gamefield[x + y * gamefieldsize] == snakebody);
		gamefield[x + y * gamefieldsize] = berrybody;
		return;
	}
	void berry::draw2D()
	{

		SetConsoleCursorPosition(console, { (short)x,(short)y });
		cout << "@";

		return;
	}

	int berry::getx() {
		return this->x; 
	}
	int berry::gety() { 
		return this->y; 
	}



	snake::snake()
	{
		length = 1;
		body = new cell[1];
		body[0].x = gamefieldsize / 2;
		body[0].y = gamefieldsize / 2;
		yspeed = 0;
		xspeed = 1;

		return;
	}
	void snake::increase()
	{
		length++;
		cell* temp = new cell[length];
		for (int i = 0; i < length - 1; i++)
		{
			temp[i].x = body[i].x;
			temp[i].y = body[i].y;
		}
		temp[length - 1].x = body[0].x + xspeed;
		temp[length - 1].y = body[0].y + yspeed;
		delete[] body;
		body = temp;
		return;
	}
	int snake::move()
	{
		cell* temp = new cell[length];
		temp[0].x = body[0].x + xspeed;
		temp[0].y = body[0].y + yspeed;

		gamefield[body[length - 1].x + body[length - 1].y* gamefieldsize] = ' ';

		if (gamefield[temp[0].x + temp[0].y* gamefieldsize] == snakebody) { GameKill(); return -1; }
		else if ((temp[0].x >= gamefieldsize || temp[0].x < 0) || (temp[0].y >= gamefieldsize || temp[0].y < 0)) { GameKill(); return -1; }
		else gamefield[temp[0].x + temp[0].y* gamefieldsize] = snakebody;

		//display[body[length].x][body[length].y] = 0;
		for (int i = 1; i < length; i++)
		{
			temp[i].x = body[i - 1].x;
			temp[i].y = body[i - 1].y;
			if ((temp[i].x >= gamefieldsize || temp[i].x < 0) || (temp[i].y >= gamefieldsize || temp[i].y < 0)) { GameKill(); return -1; }
			else gamefield[temp[i].x + temp[i].y * gamefieldsize] = snakebody;

		}
		delete[] body;
		body = temp;
		return 0;
	}
	void snake::changespeed()
	{
		if (GetAsyncKeyState(VK_RIGHT) && this->xspeed != -1) {
			this->xspeed = 1; this->yspeed = 0;
		}
		else if (GetAsyncKeyState(VK_LEFT) && this->xspeed != 1) {
			this->xspeed = -1; this->yspeed = 0;
		}
		else if (GetAsyncKeyState(VK_UP) && this->yspeed != 1) {
			this->xspeed = 0; this->yspeed = -1;
		}
		else if (GetAsyncKeyState(VK_DOWN) && this->yspeed != -1) {
			this->xspeed = 0; this->yspeed = 1;
		}
		return;
	}
	void snake::draw2D()
	{
		for (int i = 0; i < this->length; i++)
		{
			SetConsoleCursorPosition(console, { (short)this->body[i].x,(short)this->body[i].y });
			cout << gamefield[body[i].x + body[i].y * gamefieldsize];
		}
		return;
	}
	void snake::checkforberry(berry& a)
	{
		if (body[0].x + xspeed == a.x && body[0].y + yspeed == a.y)
		{
			increase();
			a.summon();
		}
		return;
	}

	int snake::getlength()
	{
		return this->length;
	}