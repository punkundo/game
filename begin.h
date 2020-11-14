#pragma once
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <math.h>

using namespace sf;

bool begin(int& speed, int& sizeStone, bool& singlePlayer, int& sizeFood) {

	speed = 3; 
	sizeStone = 12;
	singlePlayer = false;
	sizeFood = 1;

	RenderWindow window(VideoMode(343, 515), "R&G", Style::Close);

	Texture t;
	t.loadFromFile("images/begin.png");
	Sprite s(t);

	Font font;
	font.loadFromFile("fonts/font.otf");
	Text textSpeed, textStone, textPlayer, textFood;
	textSpeed.setPosition(204, 128);
	textSpeed.setFont(font);
	textSpeed.setFillColor(Color::Black);
	textSpeed.setCharacterSize(42);
	textStone.setPosition(204, 198);
	textStone.setFont(font);
	textStone.setFillColor(Color::Black);
	textStone.setCharacterSize(42);
	textPlayer.setPosition(214, 274);
	textPlayer.setFont(font);
	textPlayer.setFillColor(Color::Black);
	textPlayer.setCharacterSize(42);
	textPlayer.setString("2");
	textFood.setPosition(214, 346);
	textFood.setFont(font);
	textFood.setFillColor(Color::Black);
	textFood.setCharacterSize(42);

	while (window.isOpen()) {
		Event e;
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed) {
				window.close();
				return false;
			}

			if (sqrt(abs(e.mouseMove.x - 322) * abs(e.mouseMove.x - 322) + abs(e.mouseMove.y - 497) * abs(e.mouseMove.y - 497)) <= 10) {
				RenderWindow htplay(VideoMode(404, 209), "HowToPlay", Style::None);
				htplay.setPosition({ Mouse::getPosition().x, Mouse::getPosition().y - 209 });
				while (htplay.isOpen()) {
					Texture tmpT;
					tmpT.loadFromFile("images/htplay.png");
					Sprite tmpS(tmpT);
					htplay.clear();
					htplay.draw(tmpS);
					htplay.display();
					while (window.pollEvent(e)) {
						if (sqrt(abs(e.mouseMove.x - 322) * abs(e.mouseMove.x - 322) + abs(e.mouseMove.y - 497) * abs(e.mouseMove.y - 497)) > 10) {
							htplay.close();
						}
					}
				}
			}

			if (Mouse::isButtonPressed(Mouse::Left)) {
				int x = e.mouseButton.x;
				int y = e.mouseButton.y;

				if (51 <= x && x <= 137 && 431 <= y && y <= 479) {//Start
					return true;
				}
				if (207 <= x && x <= 293 && 431 <= y && y <= 479) {//Quit
					return false;
				}
				if (262 <= x && x <= 286 && 141 <= y && y <= 153) {//Up speed
					if (speed < 5) speed++;
				}
				if (262 <= x && x <= 286 && 159 <= y && y <= 171) {//Down speed
					if (speed > 1) speed--;
				}
				if (262 <= x && x <= 286 && 210 <= y && y <= 222) {//Up sizeStone
					if (sizeStone < 50) sizeStone++;
				}
				if (262 <= x && x <= 286 && 228 <= y && y <= 240) {//Down sizeStone
					if (sizeStone > 0) sizeStone--;
				}
				if (262 <= x && x <= 286 && 286 <= y && y <= 298) {//Up Player
					if (singlePlayer) {
						singlePlayer = false;
						textPlayer.setString("2");
					}
				}
				if (262 <= x && x <= 286 && 304 <= y && y <= 316) {//Down Player
					if (!singlePlayer) {
						singlePlayer = true;
						textPlayer.setString("1");
					}
				}
				if (262 <= x && x <= 286 && 360 <= y && y <= 372) {//Up sizeFood
					if (sizeFood < 6) sizeFood++;
				}
				if (262 <= x && x <= 286 && 378 <= y && y <= 390) {//Down sizeFood
					if (sizeFood > 1) sizeFood--;
				}
			}
		}

		textSpeed.setString(to_string(speed));
		textStone.setString(to_string(sizeStone));
		textFood.setString(to_string(sizeFood));

		window.clear();

		window.draw(s);
		window.draw(textSpeed);
		window.draw(textStone);
		window.draw(textPlayer);
		window.draw(textFood);

		window.display();
	}

	return true;
}
