#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <chrono>
#include <future>
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
int main() {
    // set default values
    float danceability = 0.00;
    float energy = 0.00;
    bool explicitLanguage = 0.00;
    int sortStyle = 0; // sortStyle variable: quickSort will be 1 and shellShort will be 2

    // creating main window
    sf::RenderWindow startWindow(sf::VideoMode(800, 600), "Song Sage - Welcome!", sf::Style::Close);

    // setting fonts
    sf::Font font;
    string path1 = "files/font1.ttf";
    while (!font.loadFromFile(path1)) {
        path1 = "../" + path1;
    }
    sf::Font font2;
    string path2 = "files/font1.ttf";
    while (!font2.loadFromFile(path2)) {
        path2 = "../" + path2;
    }

    //creating welcomeText
    sf::Text welcomeText;
    welcomeText.setFont(font);
    welcomeText.setString("SongSage: Tailored Tunes Just For You!");
    welcomeText.setStyle(sf::Text::Underlined);
    welcomeText.setCharacterSize(36);
    welcomeText.setFillColor(sf::Color(77, 93, 83));
    setText(welcomeText, 400, 100);

    // creating rectangle for background
    sf::RectangleShape rectangle1(sf::Vector2f(800,100));
    rectangle1.setFillColor(sf::Color(206,216,199));
    rectangle1.setPosition(0, 50);

    //creating instructionalText
    sf::Text instructionalText;
    instructionalText.setFont(font2);
    instructionalText.setString("First, set your preferences.");
    instructionalText.setCharacterSize(24);
    instructionalText.setFillColor(sf::Color(77,93,83));
    setText(instructionalText, 400, 225);

    // creating sliders
    // NOTE: they are 250 pixels long now
    // takes position divides by 250 and uses that as user input
    // display input on top?
    sf::Texture slider;
    string path3 = "files/greenSlider.jpg";
    while (!slider.loadFromFile(path3)) {
        path3 = "../" + path3;
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
    string path4 = "files/nextArrow.png";
    while (!nextArrowGraphic.loadFromFile(path4)) {
        path4 = "../" + path4;
    }
    nextArrow.setTexture(nextArrowGraphic);
    nextArrow.setPosition(630, 480);


    // ON/OFF SWITCH - Explicit (YES/NO)
    sf::Texture onSwitch;
    string path5 = "files/on_toggle.png";
    while (!onSwitch.loadFromFile(path5)) {
        path5 = "../" + path5;
    }
    sf::Texture offSwitch;
    string path6 = "files/off_toggle.png";
    while (!offSwitch.loadFromFile(path6)) {
        path6 = "../" + path6;
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

    // final list vector declared
    vector<SongList::Song> finalList;
    // used in results page
    string sortMethod;

    string time = "";

    while(startWindow.isOpen()){
        sf::Event event;


        while(startWindow.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                startWindow.close();
                return 0;
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
                        if(sortStyle == 1){
                            // quickSort;
                            // Start async process to build list
                            future<SongList> fut = async(launch::async, [&] { return SongList(danceability, energy, explicitLanguage); });
                            string load = "Loading   ";
                            sf::Text loading;
                            loading.setFont(font2);
                            loading.setString(load);
                            loading.setCharacterSize(50);
                            loading.setFillColor(sf::Color(77, 93, 83));
                            setText(loading, 400, 300);
                            chrono::time_point<chrono::system_clock> s, e;
                            s = chrono::system_clock::now();
                            // While list is building, allow window actions to be performed
                            // Display loading screen
                            while (fut.wait_for(0ms) != future_status::ready) {
                                e = chrono::system_clock::now();
                                loading.setString(load);
                                while (startWindow.pollEvent(event)) {
                                    if (event.type == sf::Event::Closed) {
                                        startWindow.close();
                                        return 0;
                                    }
                                }
                                startWindow.clear(sf::Color(143, 151, 121));
                                startWindow.draw(loading);
                                startWindow.display();
                                // Have a ... cycle every second, one . per 1/3 second
                                if (load.size() >= 10 && (e - s).count() / 10000 >= 333) {
                                    load = "Loading";
                                    s = chrono::system_clock::now();
                                }
                                else if ((e - s).count() / 10000 >= 333) {
                                    load += ".";
                                    s = chrono::system_clock::now();
                                }
                            }
                            SongList newList = fut.get();
                            chrono::time_point<chrono::high_resolution_clock> start, end;
                            // Start timer on quicksort
                            start = chrono::high_resolution_clock::now();

                            // Replace loading screen with "sorting" screen
                            sf::Text sort;
                            sort.setFont(font2);
                            sort.setString("Sorting...");
                            sort.setCharacterSize(50);
                            sort.setFillColor(sf::Color(77, 93, 83));
                            setText(sort, 400, 300);
                            startWindow.clear(sf::Color(143, 151, 121));
                            startWindow.draw(sort);
                            startWindow.display();

                            newList.quicksort();
                            // End timer on quicksort
                            end = chrono::high_resolution_clock::now();

                            // Grab time elapsed
                            time = to_string((end - start).count() / 1000000.0);
                            finalList = newList.topTen();
                            sortMethod = "quick sort";
                            startWindow.close();
                        }
                        if(sortStyle == 2){
                            // shellSort
                            // Start async process to build song list
                            future<SongList> fut = async(launch::async, [&] { return SongList(danceability, energy, explicitLanguage); });
                            string load = "Loading   ";
                            sf::Text loading;
                            loading.setFont(font2);
                            loading.setString(load);
                            loading.setCharacterSize(50);
                            loading.setFillColor(sf::Color(77, 93, 83));
                            setText(loading, 400, 300);
                            chrono::time_point<chrono::system_clock> s, e;
                            s = chrono::system_clock::now();
                            // While list is building, allow window actions to be performed
                            // Display loading screen
                            while (fut.wait_for(0ms) != future_status::ready) {
                                e = chrono::system_clock::now();
                                loading.setString(load);
                                while (startWindow.pollEvent(event)) {
                                    if (event.type == sf::Event::Closed) {
                                        startWindow.close();
                                        return 0;
                                    }
                                }
                                startWindow.clear(sf::Color(143, 151, 121));
                                startWindow.draw(loading);
                                startWindow.display();
                                // Have a ... cycle every second, one . per 1/3 second
                                if (load.size() >= 10 && (e - s).count() / 10000 >= 333) {
                                    load = "Loading";
                                    s = chrono::system_clock::now();
                                }
                                else if ((e - s).count() / 10000 >= 333) {
                                    load += ".";
                                    s = chrono::system_clock::now();
                                }
                            }
                            SongList newList = fut.get();
                            chrono::time_point<chrono::high_resolution_clock> start, end;
                            // Start timer on shellsort
                            start = chrono::high_resolution_clock::now();
                            
                            // Replace loading screen with "sorting" screen
                            sf::Text sort;
                            sort.setFont(font2);
                            sort.setString("Sorting...");
                            sort.setCharacterSize(50);
                            sort.setFillColor(sf::Color(77, 93, 83));
                            setText(sort, 400, 300);
                            startWindow.clear(sf::Color(143, 151, 121));
                            startWindow.draw(sort);
                            startWindow.display();

                            newList.shellsort();
                            // End timer on shellsort
                            end = chrono::high_resolution_clock::now();
                            // Get time elapsed
                            time = to_string((end - start).count() / 1000000.0);
                            finalList = newList.topTen();
                            sortMethod = "shell sort";
                            startWindow.close();
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

        startWindow.draw(rectangle1);
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

    // RESULTS WINDOW

    // creating result window
    sf::RenderWindow resultsWindow(sf::VideoMode(800, 600), "Song Sage - Results!",sf::Style::Close);

    // creating top of result text
    sf::Text topText;
    topText.setFont(font);
    topText.setString("Your Top 5 Recommended Songs Are:");
    topText.setStyle(sf::Text::Underlined);
    topText.setCharacterSize(36);
    topText.setFillColor(sf::Color::White);
    setText(topText, 400, 60);


    // creating rectangle for background
    sf::RectangleShape rectangle(sf::Vector2f(800,250));
    rectangle.setFillColor(sf::Color(206,216,199));
    rectangle.setPosition(0, 125);


    // creating result 1 text
    sf::Text res1Text;
    string res1_track = finalList[0].track_name;
    string res1_artist = finalList[0].artist;
    if (res1_track.size() > 40) {
        res1_track = res1_track.substr(0, 37) + "...";
    }
    if (res1_artist.size() > 40) {
        res1_artist = res1_artist.substr(0, 37) + "...";
    }
    res1Text.setFont(font2);
    res1Text.setString("1. " + res1_track + " - " + res1_artist);
    res1Text.setCharacterSize(20);
    res1Text.setFillColor(sf::Color(77,93,83));
    setText(res1Text, 400, 150);

    // creating result 2 text
    sf::Text res2Text;
    string res2_track = finalList[1].track_name;
    string res2_artist = finalList[1].artist;
    if (res2_track.size() > 40) {
        res2_track = res2_track.substr(0, 37) + "...";
    }
    if (res2_artist.size() > 40) {
        res2_artist = res2_artist.substr(0, 37) + "...";
    }
    res2Text.setFont(font2);
    res2Text.setString("2. " + res2_track + " - " + res2_artist);
    res2Text.setCharacterSize(20);
    res2Text.setFillColor(sf::Color(77,93,83));
    setText(res2Text, 400, 200);

    // creating result 3 text
    sf::Text res3Text;
    string res3_track = finalList[2].track_name;
    string res3_artist = finalList[2].artist;
    if (res3_track.size() > 40) {
        res3_track = res3_track.substr(0, 37) + "...";
    }
    if (res3_artist.size() > 40) {
        res3_artist = res3_artist.substr(0, 37) + "...";
    }
    res3Text.setFont(font2);
    res3Text.setString("3. " + res3_track + " - " + res3_artist);
    res3Text.setCharacterSize(20);
    res3Text.setFillColor(sf::Color(77,93,83));
    setText(res3Text, 400, 250);

    // creating result 4 text
    sf::Text res4Text;
    string res4_track = finalList[3].track_name;
    string res4_artist = finalList[3].artist;
    if (res4_track.size() > 40) {
        res4_track = res4_track.substr(0, 37) + "...";
    }
    if (res4_artist.size() > 40) {
        res4_artist = res4_artist.substr(0, 37) + "...";
    }
    res4Text.setFont(font2);
    res4Text.setString("4. " + res4_track + " - " + res4_artist);
    res4Text.setCharacterSize(20);
    res4Text.setFillColor(sf::Color(77,93,83));
    setText(res4Text, 400, 300);

    // creating result 5 text
    sf::Text res5Text;
    string res5_track = finalList[4].track_name;
    string res5_artist = finalList[4].artist;
    if (res5_track.size() > 40) {
        res5_track = res5_track.substr(0, 37) + "...";
    }
    if (res5_artist.size() > 40) {
        res5_artist = res5_artist.substr(0, 37) + "...";
    }
    res5Text.setFont(font2);
    res5Text.setString("5. " + res5_track + " - " + res5_artist);
    res5Text.setCharacterSize(20);
    res5Text.setFillColor(sf::Color(77,93,83));
    setText(res5Text, 400, 350);

    // creating message1 text
    sf::Text message1Text;
    message1Text.setFont(font2);
    message1Text.setString("Finding your perfect recommendations took");
    message1Text.setCharacterSize(20);
    message1Text.setFillColor(sf::Color::White);
    setText(message1Text, 400, 425);

    // creating message1 text
    sf::Text message2Text;
    message2Text.setFont(font2);
    message2Text.setString(time + " milliseconds using " + sortMethod);
    message2Text.setCharacterSize(20);
    message2Text.setFillColor(sf::Color::White);
    setText(message2Text, 400, 450);


    // creating thank you text
    sf::Text thankyouText;
    thankyouText.setFont(font2);
    thankyouText.setString("Thanks for using SongSage!");
    thankyouText.setCharacterSize(28);
    thankyouText.setFillColor(sf::Color(77,93,83));
    setText(thankyouText, 400, 550);

    while(resultsWindow.isOpen()){
        sf::Event event;

        while(resultsWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                resultsWindow.close();
            }
        }

        // draws green background for window
        resultsWindow.clear(sf::Color(143, 151, 121));
        // draws results text
        resultsWindow.draw(rectangle);
        resultsWindow.draw(topText);
        resultsWindow.draw(res1Text);
        resultsWindow.draw(res2Text);
        resultsWindow.draw(res3Text);
        resultsWindow.draw(res4Text);
        resultsWindow.draw(res5Text);
        resultsWindow.draw(message1Text);
        resultsWindow.draw(message2Text);
        resultsWindow.draw(thankyouText);

        resultsWindow.display();
    }

	return 0;
}
