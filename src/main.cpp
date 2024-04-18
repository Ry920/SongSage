#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
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
	SongList s(0.25, 0.25, true);
	cout << s.list[88731].track_name << " " << s.list[88731].energy << endl;
	cout << "-----------------------------\n";
	s.quicksort();
	cout << s.list[0].energy << " " << s.list[0].danceability << endl;
	return 0;
}
