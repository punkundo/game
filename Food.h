#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include "Snake.h"
#include "setup.h"
class Food {
public:
	Food() {
		t.loadFromFile("images/food.png");
		s.setTexture(t);
		eatBuffer.loadFromFile("sounds/eat.wav");
		eat.setBuffer(eatBuffer);
	}
	bool check(Snake s1, Snake s2, Stone stone) {
		for (int i = 0; i < s1.length; i++) {
			if (x == s1.x[i] && y == s1.y[i]) {
				return 0;
			}
		}
		for (int i = 0; i < s2.length; i++) {
			if (x == s2.x[i] && y == s2.y[i]) {
				return 0;
			}
		}
		for (int i = 0; i < stone.sizeStone; i++) {
			if (x == stone.x[i] && y == stone.y[i]) {
				return 0;
			}
		}
		return 1;
	}
	void reset(Snake s1, Snake s2, Stone stone) {
		do {
			x = rand() % N;
			y = rand() % M;
		} while (!check(s1,s2,stone));
		
	}
	void update(Snake& s1, Snake& s2, Stone stone) {
		if (x == s1.x[0] && y == s1.y[0]) {
			eat.play();
			reset(s1, s2, stone);
			s1.length++;
		}
		if (x == s2.x[0] && y == s2.y[0]) {
			eat.play();
			reset(s1, s2, stone);
			s2.length++;
		}
	}
	void draw(RenderWindow& rd) {
		s.setPosition(x * Size, y * Size + sizeScore);
		rd.draw(s);
	}
	friend class Snake;
private:
	int x, y;
	Texture t;
	Sprite s;
	SoundBuffer eatBuffer;
	Sound eat;
};