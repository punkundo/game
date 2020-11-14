#pragma once
#include <SFML/Graphics.hpp>
#include <string.h>
using namespace std;
using namespace sf;
class Score {
public:
	Score() {}
	void draw(RenderWindow& rd, int a, int b) {
		Texture t;
		t.loadFromFile("images/bg2.png");
		Sprite s(t);
		rd.draw(s);
		for (int i = 2; i >= 0; i--) {
			Texture t;
			t.loadFromFile("images/r" + to_string(a % 10) + ".png");
			a /= 10;
			Sprite tmp(t);
			tmp.setPosition(500 + i * 40, 20);
			rd.draw(tmp);
			t.loadFromFile("images/g" + to_string(b % 10) + ".png");
			b /= 10;
			tmp.setTexture(t);
			tmp.setPosition(700 + i * 40, 20);
			rd.draw(tmp);
		}
	}
};

