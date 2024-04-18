#include <unordered_set>
#include <fstream>
#include <sstream>
#include <iostream> // delete later
#include "songlist.hpp"
using namespace std;

SongList::SongList() {
	// Keep track of track ID's since they are unique
	unordered_set<string> track_ids;
	// TODO: Continue implementation with file reading

}

vector<SongList::Song>& SongList::topTen() const {
	// Create a list and allocate *up to* 10 songs
	// Assume list is already sorted as needed
	vector<SongList::Song> vec(10);
	for (int i = 0; i < list.size(); i++) {
		if (i == 10) break;
		vec[i] = list[i];
	}
	return vec;
}

void SongList::quicksort() {
	
}

void SongList::shellsort() {
}
