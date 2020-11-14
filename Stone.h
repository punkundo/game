#pragma once
#include "SFML/Graphics.hpp"
#include "setup.h"
using namespace sf;
class Stone {
public:
	Stone(int size) {
		sizeStone = size;
		for (int i = 0; i < sizeStone; i++) {
			x[i] = rand() % (N - 2) + 1;
			y[i] = rand() % (M - 2) + 1;
		}
		t.loadFromFile("images/stone2.png");
		s.setTexture(t);
	}
	void draw(RenderWindow& rd) {
		for (int i = 0; i < sizeStone; i++) {
			s.setPosition(x[i] * Size, y[i] * Size + sizeScore);
			rd.draw(s);
		}
	}
	friend class Snake;
	friend class Food;
private:
	Texture t;
	Sprite s;
	int sizeStone = 0;
	int x[100] = { 0 }, y[100] = { 0 };
};
