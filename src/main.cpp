#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "songlist.hpp"
using namespace std;

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

	while (w.isOpen()) {
		for (auto event = sf::Event{}; w.pollEvent(event);)
		{
			if (event.type == sf::Event::Closed)
			{
				w.close();
			}
		}
        sf::Text welcomeText;
        welcomeText.setString("SongSage: Tailored Tunes Just for You");
        welcomeText.setCharacterSize(48);
        welcomeText.setFillColor(sf::Color(1, 50, 32));

        w.clear(sf::Color(208, 217, 179));

		w.display();

		w.clear();
	}
	return 0;
}
