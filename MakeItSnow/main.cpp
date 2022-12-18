#include <iostream>  
#include <SFML/Graphics.hpp> 
#include <SFML/Audio.hpp>
#include <Windows.h>
#include <vector>
//These were imported too save space & make the code more readable
using namespace sf;
using namespace std;
// define render window size constants
#define winWidth 1114
#define winHeight 860

int main()
{
    //here are the verables I will use for the minulatble condisions
    float fallangle = 0;
    float fallintensity = 2;

    //Here are instructions for users
    cout << "use the up & down arrows to alter the snow intensaty \n left & right arrows to alter the fall angle \n click to play the windsound \n Click on the snowman to drage him";

    //Wind sound stuff.
    SoundBuffer wind;
    Sound sound;
    wind.loadFromFile("mixkit-light-wind-1165.WAV");
    sound.setBuffer(wind);

    // create the window
    RenderWindow window(VideoMode(winWidth, winHeight), "Object Orentated Programing Assigment 1");

    // Texture set up
    Texture tex_background, tex_snowman;
    tex_background.loadFromFile("Tranparent_background.PNG");
    tex_snowman.loadFromFile("snowdude.png");

    // Sprite set up
    Sprite spr_background, spr_snowman;
    spr_background.setTexture(tex_background);
    spr_background.scale(0.8, 0.8);
    spr_snowman.setTexture(tex_snowman);
    spr_snowman.scale(0.2, 0.2);
    spr_snowman.setPosition(800, 600); // absolute position

    //Sun & moon drawings & setup
    CircleShape moon, sun;
    moon.setRadius(200.0f);
    moon.setRotation(285);
    moon.setFillColor(Color(200, 200, 200));
    moon.setOrigin(winWidth / 2, winHeight);
    moon.setPosition(winWidth / 2, winHeight);

    sun.setRadius(200.0f);
    sun.setRotation(75);
    sun.setFillColor(Color::Yellow);
    sun.setOrigin(winWidth / 2, winHeight);
    sun.setPosition(winWidth / 2, winHeight);

    //We use this object for the onClick events
    CircleShape mouseon;
    mouseon.setRadius(2);
    mouseon.setFillColor(Color(255, 255, 255));
    mouseon.setPosition(Mouse::getPosition().x, Mouse::getPosition().y);

    //Vector Setup
    vector<ConvexShape> flakes;

    //used for picking up the snowman
    bool pickedup = false;

    //Clock setup
    Clock clock;
    Time elapsedTime;

    // run the program as long as the window is open
    while (window.isOpen()) {
        //Tjis boolen is used too determen weither or not we are holding the snowman
        bool clicker = false;
        // check all the window's events that were triggered since the last iteration of the loop
        Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == Event::Closed)
                window.close();
        }

        //when you click on the snowman he will follow the object that is assigned to your mouse 
        if (spr_snowman.getGlobalBounds().intersects(mouseon.getGlobalBounds()) && event.type == Event::MouseButtonPressed && !pickedup) {
            spr_snowman.setPosition(Mouse::getPosition().x - 500, Mouse::getPosition().y - 150);
            pickedup = true;
        }
        else if (spr_snowman.getGlobalBounds().intersects(mouseon.getGlobalBounds()) && event.type == Event::MouseButtonPressed && pickedup) {
            pickedup = false;
        }
        else if (event.type == Event::MouseButtonPressed) {
            sound.play();
        }
        if (pickedup) {
            spr_snowman.setPosition(Mouse::getPosition().x - 500, Mouse::getPosition().y - 150);
        }

        //used so the sky colour can change in a resonbal amount of time
        int seconds = elapsedTime.asSeconds() * 3;

        // clear the window & changes the background colour depending on how much time has passed
        if (seconds >= 510) {
            clock.restart();
            elapsedTime = clock.getElapsedTime();
        }
        else if (seconds >= 255) {
            window.clear(Color(0, 0, -1 * seconds));
        }
        else {
            window.clear(Color(0, 0, seconds));
        }
        //Setup the object following your mouse
        window.draw(mouseon);
        mouseon.setPosition(Mouse::getPosition().x - 410, Mouse::getPosition().y - 135);

        // draw everything here...
        window.draw(moon);
        window.draw(sun);
        window.draw(spr_background);
        window.draw(spr_snowman);

        //Make our sun & moon rotate
        moon.setRotation(340 + elapsedTime.asSeconds() * 4);
        sun.setRotation(200 + elapsedTime.asSeconds() * 4);

        //fill up the flakes vector with our custom shape I add some randome numbers to manke the snowflakes more unque like real life. All together there are 1600 posable snowflakes
        flakes.push_back(ConvexShape());
        flakes.back().setPointCount(25);
        flakes.back().setPoint(0, Vector2f(15, 0));
        flakes.back().setPoint(1, Vector2f(10, 0));
        flakes.back().setPoint(2, Vector2f(10, 7.5));
        flakes.back().setPoint(3, Vector2f(2.5, 0));
        flakes.back().setPoint(4, Vector2f(0, 2.5));
        flakes.back().setPoint(5, Vector2f(7.5, 10));
        flakes.back().setPoint(6, Vector2f(0, 10));
        flakes.back().setPoint(7, Vector2f(0, 15));
        flakes.back().setPoint(8, Vector2f(7.5, 15));
        flakes.back().setPoint(9, Vector2f(0, 22.5));
        flakes.back().setPoint(10, Vector2f(2.5, 25));
        flakes.back().setPoint(11, Vector2f(10, 17.5));
        flakes.back().setPoint(12, Vector2f(10 + 5, 25));
        flakes.back().setPoint(13, Vector2f(15 + 5, 25));
        flakes.back().setPoint(14, Vector2f(15, 17.5));
        flakes.back().setPoint(15, Vector2f(22.5, 25));
        flakes.back().setPoint(16, Vector2f(25, 22.5));
        flakes.back().setPoint(17, Vector2f(17.5, 15));
        flakes.back().setPoint(18, Vector2f(25, 15));
        flakes.back().setPoint(19, Vector2f(25, 10));
        flakes.back().setPoint(20, Vector2f(17.5, 10));
        flakes.back().setPoint(21, Vector2f(25, 2.5));
        flakes.back().setPoint(22, Vector2f(22.5, 0));
        flakes.back().setPoint(23, Vector2f(15, 7.5));
        flakes.back().setPoint(24, Vector2f(15, 0));

        //Create the snowflakes & allow them too sway
        float rotation = rand() % 4;
        for (int i = 0; i < flakes.size(); i++) {
            rotation *= -1;
            flakes.back().setPosition(rand() % winWidth, -100);
            flakes[i].move(fallangle, fallintensity);
            flakes[i].rotate(rotation);
            if (i % 4 == 0) {
                flakes[i].setFillColor(Color(200, 200, 250));
            }
            else {
                flakes[i].setFillColor(Color(255, 255, 255));
            }
            window.draw(flakes[i]);
        }

        elapsedTime = clock.getElapsedTime();

        //Allows the program to take in button inputs & respond accorlly
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            fallangle -= 0.01;
        }if (Keyboard::isKeyPressed(Keyboard::Right)) {
            fallangle += 0.01;
        }if (Keyboard::isKeyPressed(Keyboard::Up) && fallintensity > 1) {
            fallintensity -= 1;
        }if (Keyboard::isKeyPressed(Keyboard::Down) && fallintensity < 7) {
            fallintensity += 1;
        }if (Keyboard::isKeyPressed(Keyboard::R)) {
            fallangle = 0;
            fallintensity = 3;
        }if (Keyboard::isKeyPressed(Keyboard::B)) {
            sound.stop();
        }if (Keyboard::isKeyPressed(Keyboard::Space)) {
        }
        window.display();

    }
    return 0;
}