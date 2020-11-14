#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include <string.h>
#include <iostream>
#include "Stone.h"
#include "setup.h"
using namespace sf;
using namespace std;
class Snake {
public:
	Snake(string fileName,int x, int y) {
		name = fileName;
		t.loadFromFile("images/" + name + ".png");
		s.setTexture(t);
		this->x[0] = x; this->y[0] = y;
		dieBuffer.loadFromFile("sounds/die.wav");
		dieSound.setBuffer(dieBuffer);
	}

	void update(char _dir) {

		if (disable) return;

		if (dir == NULL)  dir = _dir;
		if (dir == 'U' && _dir != 'D') dir = _dir;
		else if (dir == 'D' && _dir != 'U')  dir = _dir;
		else if (dir == 'L' && _dir != 'R')  dir = _dir;
		else if (dir == 'R' && _dir != 'L')  dir = _dir;

		for (int i = length; i >= 1; i--) {
			x[i] = x[i - 1]; 
			y[i] = y[i - 1];
		}
		if (dir == 'U') --y[0];
		if (dir == 'D') ++y[0];
		if (dir == 'L') --x[0];
		if (dir == 'R') ++x[0];

		if (x[0] < 0) x[0] = N - 1;
		if (x[0] == N) x[0] = 0;
		if (y[0] < 0) y[0] = M - 1;
		if (y[0] == M) y[0] = 0;
	}

	bool die(Snake s, Stone stone) {
		if (disable) return false;
		for (int i = 1; i < length; i++) {//tự đâm
			if (x[0] == x[i] && y[0] == y[i]) {
				dieSound.play();
				return true;
			}
		}
		for (int i = 0; i < s.length; i++) {//đâm vào con khác
			if (x[0] == s.x[i] && y[0] == s.y[i]) {
				if (!i) {
					if (dir == 'U' && s.dir == 'D') return -1;
					if (dir == 'D' && s.dir == 'U') return -1;
					if (dir == 'L' && s.dir == 'R') return -1;
					if (dir == 'R' && s.dir == 'L') return -1;
				}
				dieSound.play();
				return true;
			}
		}
		for (int i = 0; i < stone.sizeStone; i++) {//đâm vào chướng ngại vật
			if (x[0] == stone.x[i] && y[0] == stone.y[i]) {
				dieSound.play();
				return true;
			}
		}
		return false;
	}

	void draw(RenderWindow& rd) {
		if (disable) return;
		Texture tmpTexture;
		string tmpS;
		tmpS += dir;
		tmpTexture.loadFromFile(("images/" + name + tmpS + ".png"));
		Sprite tmpSprite(tmpTexture);
		tmpSprite.setPosition(x[0] * Size , y[0] * Size + sizeScore);
		rd.draw(tmpSprite);
		for (int i = 1; i < length; i++) {
			s.setPosition(x[i] * Size, y[i] * Size + sizeScore);
			rd.draw(s);
		}
	}

	int getlen(){ return length; }

	void turnOff() {
		length = 0;
		disable = true;
	}

	friend class Food;

private:
	int length = 2;
	char dir = NULL;
	int x[200] , y[200];
	bool disable = false;
	Texture t;
	Sprite s;
	SoundBuffer dieBuffer;
	Sound dieSound;
	string name;
};