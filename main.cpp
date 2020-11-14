
#include <SFML/Graphics.hpp>
#include "SFML/Audio.hpp"
#include <time.h>
#include <iostream>
#include <string.h>
#include <Windows.h>
#include "Food.h"
#include "setup.h"
#include "Score.h"
#include "begin.h"
#include "Animation.h"
#include <vector>
using namespace sf;
using namespace std;

int main() {
    
    Music music;
    music.openFromFile("sounds/song.wav");
    music.play();
    

    bool singlePlayer = false;
    int speed, sizeStone, sizeFood;
    


    Texture t,tBg;
    t.loadFromFile("images/gameover.png");
    tBg.loadFromFile("images/bg1.png");
    Sprite gameover(t),bg(tBg);
    gameover.setPosition(0, 100);
    bg.setPosition(0, sizeScore);
    srand(time(NULL)); 


    while (true) {

        if (!begin(speed, sizeStone, singlePlayer, sizeFood)) {
            return 0;
        }

        RenderWindow screen(VideoMode(Width, Height + sizeScore), "R & G", Style::Close);

        Clock clock;
        float time = 0, timer = 0, delay = (0.2 - speed * 0.03);

        Snake s1("red", 0, 0);
        Snake s2("green", N - 1, 0);
        Stone stone(sizeStone);
        vector<Food> food(sizeFood);
        Score score;
        Animation anime;

        for (int i = 0; i < sizeFood; i++) {
            food[i].reset(s1, s2, stone);
        }

        char dir_s1 = 'U', dir_s2 = 'D';
        int die_s1 = 0, die_s2 = 0;
        bool restart = false;

        while (screen.isOpen()) {
            Event e;
            while (screen.pollEvent(e)) {
                if (e.type == Event::Closed) {
                    if (MessageBox(NULL, TEXT("Are you sure?"), TEXT("R & G"), MB_YESNO | MB_ICONQUESTION) == IDYES) {
                        screen.close();
                        return 0;
                    }
                }
                if (e.type == Event::LostFocus) {
                    while (true) {
                        if (screen.pollEvent(e) && e.type == Event::GainedFocus) {
                            break;
                        }
                    }
                }
            }

            timer += clock.getElapsedTime().asSeconds();
            time += clock.getElapsedTime().asSeconds();
            if (time > 2) time = 0;
            clock.restart();


            if (Keyboard::isKeyPressed(Keyboard::W)) dir_s1 = 'U';
            if (Keyboard::isKeyPressed(Keyboard::S)) dir_s1 = 'D';
            if (Keyboard::isKeyPressed(Keyboard::A)) dir_s1 = 'L';
            if (Keyboard::isKeyPressed(Keyboard::D)) dir_s1 = 'R';

            if (Keyboard::isKeyPressed(Keyboard::Up)) dir_s2 = 'U';
            if (Keyboard::isKeyPressed(Keyboard::Down)) dir_s2 = 'D';
            if (Keyboard::isKeyPressed(Keyboard::Left)) dir_s2 = 'L';
            if (Keyboard::isKeyPressed(Keyboard::Right)) dir_s2 = 'R';
                    
            if (timer > delay) {
                timer = 0;
                bool die1 = false, die2 = false;
                if (singlePlayer) s2.turnOff();
                s1.update(dir_s1);
                die1 = s1.die(s2, stone);
                s2.update(dir_s2);
                die2 = s2.die(s1, stone);
                if (die1 || die2) {

                    Sleep(1500);

                    screen.draw(gameover);
                    screen.display();
                    while (true) {
                        while (screen.pollEvent(e)) {
                            if (e.type == Event::Closed) {
                                return 0;
                            }
                        }
                        if (Keyboard::isKeyPressed(Keyboard::Space)) {
                            restart = true;
                            break;
                        }
                        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                            return 0;
                        }
                    }
                }
                for (int i = 0; i < sizeFood; i++) {
                    food[i].update(s1, s2, stone);
                }
            }

            if (restart) {
                screen.close();
                break;
            }

            //Draw///
            screen.clear();

            /*bg.draw(screen);*/
            screen.draw(bg);
            stone.draw(screen);
            for (int i = 0; i < sizeFood; i++) {
                food[i].draw(screen);
            }
            s1.draw(screen);
            s2.draw(screen);
            if (singlePlayer) {
                score.draw(screen, s1.getlen(), 0);
            }
            else score.draw(screen, s1.getlen(), s2.getlen());

            anime.draw(screen,int(time*10));
            screen.display();
        }
    }
    return 0;
}