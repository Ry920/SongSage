#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "songlist.hpp"
using namespace std;

// setText function from "Minesweeper Project" - created by Dr. Laura Cruz Casto for COP3503, Summer 2023
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

int main() {
    sf::RenderWindow w(sf::VideoMode(800, 600), "test");

    //setting font
    sf::Font font;
    if(!font.loadFromFile("files/font.ttf")){
        cout << "Font not found." << endl;
    }

    sf::Text welcomeText;
    welcomeText.setFont(font);
    welcomeText.setString("SongSage: Tailored Tunes Just for You");
    welcomeText.setCharacterSize(48);
    welcomeText.setFillColor(sf::Color::Black);
    setText(welcomeText, 400, 300);


	while (w.isOpen()) {
        sf::Event event;
		while(w.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				w.close();
			}
		}

        w.clear(sf::Color(208, 217, 179));

        w.draw(welcomeText);

		w.display();
	}
	return 0;
}
