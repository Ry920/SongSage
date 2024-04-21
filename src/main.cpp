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
		- NOTE: it takes in 3 variables to account for: danceability, energy, and a bool of explicit (yes/no)
		b. Create UI designs for the program
	3. Integrate the SFML functionality with the SongList
	and user input
    4. Ria adding this 4/18: Also include error message, if user doesnt select
    one of the three varibles, include error message so they put it
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
//    for (SongList::Song song : l) {
//		cout << song.artist << " " << song.track_name << " " << song.danceability << " " << song.energy << endl;
//	}

    // set default values
    float danceability = 0.00;
    float energy = 0.00;
    bool explicitLanguage = 0.00;
    int sortStyle = 0; // sortStyle variable: quickSort will be 1 and shellShort will be 2

    // creating main window
    sf::RenderWindow startWindow(sf::VideoMode(800, 600), "Song Sage - Welcome!", sf::Style::Close);

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
    welcomeText.setStyle(sf::Text::Underlined);
    welcomeText.setCharacterSize(36);
    welcomeText.setFillColor(sf::Color(77,93,83));
    setText(welcomeText, 400, 100);

    //creating instructionalText
    sf::Text instructionalText;
    instructionalText.setFont(font2);
    instructionalText.setString("First, set your preferences.");
    instructionalText.setCharacterSize(24);
    instructionalText.setFillColor(sf::Color(77,93,83));
    setText(instructionalText, 400, 250);

    // creating sliders
    // NOTE: they are 250 pixels long now
    // takes position divides by 250 and uses that as user input
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

    // NEXT arrow
    sf::Sprite nextArrow;
    sf::Texture nextArrowGraphic;
    if(!nextArrowGraphic.loadFromFile("..\\..\\files\\nextArrow.png")){
        cout << "Next arrow not foud." << endl;
    }
    nextArrow.setTexture(nextArrowGraphic);
    nextArrow.setPosition(630, 480);


    // ON/OFF SWITCH - Explicit (YES/NO)
    sf::Texture onSwitch;
    if(!onSwitch.loadFromFile("..\\..\\files\\on_toggle.png")){
        cout << "Switch not found." << endl;
    }
    sf::Texture offSwitch;
    if(!offSwitch.loadFromFile("..\\..\\files\\off_toggle.png")){
        cout << "Switch not found." << endl;
    }
    sf::Sprite explicitSwitch;
    explicitSwitch.setTexture(onSwitch);
    explicitSwitch.setPosition(630, 390);
    sf::Text explicitText;
    explicitText.setFont(font2);
    explicitText.setString("Explicit?");
    explicitText.setCharacterSize(24);
    explicitText.setFillColor(sf::Color::White);
    setText(explicitText, 690, 350);

    // SORT STYLE - select: quick sort or shell sort
    sf::Text selectText;
    selectText.setFont(font2);
    selectText.setString("Select:");
    selectText.setCharacterSize(24);
    selectText.setFillColor(sf::Color::White);
    setText(selectText, 420, 500);

    sf::Text quickSortText;
    quickSortText.setFont(font2);
    quickSortText.setString("Quick Sort");
    quickSortText.setCharacterSize(24);
    quickSortText.setFillColor(sf::Color::White);
    setText(quickSortText, 350, 530);

    sf::Text shellSortText;
    shellSortText.setFont(font2);
    shellSortText.setString("Shell Sort");
    shellSortText.setCharacterSize(24);
    shellSortText.setFillColor(sf::Color::White);
    setText(shellSortText, 490, 530);

    // error message: please select sort type
    sf::Text errorMessageText;
    errorMessageText.setFont(font2);
    errorMessageText.setString("Please select a sort style.");
    errorMessageText.setCharacterSize(20);
    errorMessageText.setFillColor(sf::Color(143, 151, 121));
    setText(errorMessageText, 140, 515);

    while(startWindow.isOpen()){
        sf::Event event;

        while(startWindow.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                startWindow.close();
            }

            if(event.type == sf::Event::MouseButtonPressed){
                if(event.mouseButton.button == sf::Mouse::Left){
                    // IF DANCE SLIDER IS MOVED:
                    auto slider1Bound = slider1.getGlobalBounds();
                    if(slider1Bound.contains(event.mouseButton.x, event.mouseButton.y)){
                        if(event.mouseButton.x >= 30 && event.mouseButton.x <= 280) {
                            toggle1.setPosition((float) event.mouseButton.x, 390);
                            // set danceability variable relative to toggle position
                            danceability = ((float) event.mouseButton.x - 30.0) / 250.00;
                        }

                    }

                    // IF ENERGY SLIDER IS MOVED:
                    auto slider2Bound = slider2.getGlobalBounds();
                    if(slider2Bound.contains(event.mouseButton.x, event.mouseButton.y)){
                        if(event.mouseButton.x >= 300 && event.mouseButton.x <= 550){
                            toggle2.setPosition((float)event.mouseButton.x, 390);
                            // set energy variable relative to toggle position:
                            energy = ((float)event.mouseButton.x - 300.0) / 250.00;
                        }
                    }

                    // IF EXPLICIT SWITCH IS PRESSED
                    auto explicitSwitchBound = explicitSwitch.getGlobalBounds();
                    if(explicitSwitchBound.contains(event.mouseButton.x, event.mouseButton.y)){
                        // Switch its image to display opposite image
                        if(explicitSwitch.getTexture() == &onSwitch){
                            explicitSwitch.setTexture(offSwitch);
                            // set bool to false
                            explicitLanguage = false;
                        }
                        else{
                            explicitSwitch.setTexture(onSwitch);
                            // set bool to true
                            explicitLanguage = true;
                        }
                    }

                    //IF "QUICK SORT" IS PRESSED
                    auto quickSortBound = quickSortText.getGlobalBounds();
                    if(quickSortBound.contains(event.mouseButton.x, event.mouseButton.y)){
                        quickSortText.setStyle(sf::Text::Underlined | sf::Text::Bold);
                        shellSortText.setStyle(sf::Text::Regular);
                        // quickSort is selected
                        sortStyle = 1;
                    }

                    //IF "SHELL SORT" IS PRESSED
                    auto shellSortBound = shellSortText.getGlobalBounds();
                    if(shellSortBound.contains(event.mouseButton.x, event.mouseButton.y)){
                        shellSortText.setStyle(sf::Text::Underlined | sf::Text::Bold);
                        quickSortText.setStyle(sf::Text::Regular);
                        // shellSort is selected
                        sortStyle = 2;
                    }

                    //IF NEXT ARROW IS PRESSED and a sort style is selected
                    auto nextArrowBound = nextArrow.getGlobalBounds();
                    if(nextArrowBound.contains(event.mouseButton.x, event.mouseButton.y)){
                        ////TODO: close out window and load results screen. "finalList" is where the matches are stored
                        if(sortStyle == 1){
                            // quickSort;
                            SongList newList(danceability, energy, explicitLanguage);
                            newList.quicksort();
                            vector<SongList::Song> finalList = newList.topTen();

                            ////this is printing out the list in command line, you can delete in the final implementation
                            for (SongList::Song song : finalList) {
                                cout << song.artist << " " << song.track_name << " " << song.danceability << " " << song.energy << endl;
                            }
                            cout << endl;
                        }
                        if(sortStyle == 2){
                            // shellSort
                            SongList newList(danceability, energy, explicitLanguage);
                            newList.shellsort();
                            vector<SongList::Song> finalList = newList.topTen();

                            ////this is printing out the list in command line, you can delete in the final implementation
                            for (SongList::Song song : finalList) {
                                cout << song.artist << " " << song.track_name << " " << song.danceability << " " << song.energy << endl;
                            }
                            cout << endl;
                        }

                        // if not sortStyle has been selected, display error message
                        if(sortStyle == 0){
                            errorMessageText.setFillColor(sf::Color(77,93,83));
                        }
                    }
                }
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

        startWindow.draw(nextArrow);

        startWindow.draw(explicitText);
        startWindow.draw(explicitSwitch);

        startWindow.draw(selectText);
        startWindow.draw(quickSortText);
        startWindow.draw(shellSortText);
        startWindow.draw(errorMessageText);

        startWindow.display();

    }



	return 0;
}
