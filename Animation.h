#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;
using namespace sf;
class Animation {
public:
	Animation(){
		for (int i = 0; i < 20; i++) {
			Texture t;
			anime.push_back(t);
			//anime->at(i).loadFromFile("animations/" + to_string(i) + ".png");
			anime[i].loadFromFile("animations/" + to_string(i) + ".png");
		}
	}
	void draw(RenderWindow& rd, int t) {
		Sprite s(anime[t]);
		s.setPosition(1050, 10);
		rd.draw(s);
		s.setPosition(1190, 10);
		rd.draw(s);
	}
private:
	vector<Texture> anime;
};

