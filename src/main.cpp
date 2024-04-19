#include <iostream>
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
    // main window
    sf::RenderWindow startWindow(sf::VideoMode(800, 600), "Start Window", sf::Style::Close);
    sf::Font font;

    if(!font.loadFromFile("..\\..\\files\\font1.ttf")){
        cout << "File not found.";
    }

    sf::Text welcomeText;
    welcomeText.setFont(font);
    welcomeText.setString("SongSage: Tailored Tunes Just For You!");
    welcomeText.setCharacterSize(36);
    welcomeText.setFillColor(sf::Color(77,93,83));
    setText(welcomeText, 400, 100);


    while(startWindow.isOpen()){
        sf::Event event;

        while(startWindow.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                startWindow.close();
            }
        }

        startWindow.clear(sf::Color(143, 151, 121));

        startWindow.draw(welcomeText);

        startWindow.display();


    }



	return 0;
}
