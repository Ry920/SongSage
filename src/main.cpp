﻿#include <iostream>
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
	return 0;
}
