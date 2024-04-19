﻿#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include "songlist.hpp"
using namespace std;

// setText function from "Minesweeper" assignment created by Dr. Cruz Castro for COP3530, University of Florida, Summer 2023
void setText(sf::Text &text, float x, float y){
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,
                   textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

/*
	Overall TODO:
	1. Finish SongList functionality + sorting
	2. Add SFML functionality
		a. Add some abstraction and classes to make things
		easier, like a button and slider class
		- NOTE: it takes in 3 variables to account for: danceability, energy, and a bool of explicit (yes/no)
		b. Create UI designs for the program
	3. Integrate the SFML functionality with the SongList
	and user input
*/

// Testing by Ryan
/*
	Results:
	Quicksort and Shellsort work as intended, and so does the
	maximum limits on the energy and danceability. Only problem is
	that some songs end up in flipped orders between the two
	sorts if they have the exact same sum. Probably fixable in
	the implementation of either sort.
*/
int main() {
	SongList s(0.25, 0.75, true);
	s.quicksort();
	vector<SongList::Song> l = s.topTen();
    for (SongList::Song song : l) {
		cout << song.artist << " " << song.track_name << " " << song.danceability << " " << song.energy << endl;
	}

    // creating main window
    sf::RenderWindow startWindow(sf::VideoMode(800, 600), "Start Window", sf::Style::Close);

    // setting fonts
    sf::Font font;
    if(!font.loadFromFile("..\\..\\files\\font1.ttf")){
        cout << "File not found.";
    }
    sf::Font font2;
    if(!font2.loadFromFile("..\\..\\files\\font2.ttf")){
        cout << "File not found.";
    }

    //creating welcomeText
    sf::Text welcomeText;
    welcomeText.setFont(font);
    welcomeText.setString("SongSage: Tailored Tunes Just For You!");
    welcomeText.setCharacterSize(36);
    welcomeText.setFillColor(sf::Color(77,93,83));
    setText(welcomeText, 400, 100);
    //creating instructionalText
    sf::Text instructionalText;
    instructionalText.setFont(font2);
    instructionalText.setString("First, set your preferences.");
    instructionalText.setCharacterSize(24);
    instructionalText.setFillColor(sf::Color(77,93,83));
    setText(instructionalText, 400, 200);

    // creating sliders
    // needs to be 200 pixels long
    // takes position divides by 200 and uses that as user input
    // display input on top?
    sf::Texture slider;
    if(!slider.loadFromFile("..\\..\\files\\greenSlider.jpg")){
        cout << "Slider not found." << endl;
    }
    //SLIDER 1 - Danceability
    sf::Sprite slider1;
    slider1.setPosition(30, 400);
    slider1.setTexture(slider);
    sf::RectangleShape toggle1(sf::Vector2f(15.0f, 60.0f));
    toggle1.setPosition(30, 390);
    sf::Text danceabilityText;
    danceabilityText.setFont(font2);
    danceabilityText.setString("Danceability");
    danceabilityText.setCharacterSize(24);
    danceabilityText.setFillColor(sf::Color::White);
    setText(danceabilityText, 150, 350);

    //SLIDER 2 - Energy
    sf::Sprite slider2;
    slider2.setTexture(slider);
    slider2.setPosition(300, 400);
    sf::RectangleShape toggle2(sf::Vector2f(15.0f, 60.0f));
    toggle2.setPosition(300, 390);
    sf::Text energyText;
    energyText.setFont(font2);
    energyText.setString("Energy");
    energyText.setCharacterSize(24);
    energyText.setFillColor(sf::Color::White);
    setText(energyText, 420, 350);


    while(startWindow.isOpen()){
        sf::Event event;

        while(startWindow.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                startWindow.close();
            }
        }

        startWindow.clear(sf::Color(143, 151, 121));

        startWindow.draw(welcomeText);
        startWindow.draw(instructionalText);
        startWindow.draw(slider1);
        startWindow.draw(toggle1);
        startWindow.draw(danceabilityText);
        startWindow.draw(slider2);
        startWindow.draw(toggle2);
        startWindow.draw(energyText);

        startWindow.display();
    }



	return 0;
}
