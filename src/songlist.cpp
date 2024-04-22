#include <unordered_set>
#include <fstream>
#include <sstream>
#include <iostream> // delete later
#include "songlist.hpp"
using namespace std;

void SongList::qsorthelper(int low, int high) {
	if (low >= high) {
		return;
	}
	int p = partition(low, high);
	// If statements stop index errors
	if (p != 0) {
		qsorthelper(low, p - 1);
	}
	if (p != high) {
		qsorthelper(p + 1, high);
	}
}

int SongList::partition(int low, int high) {
	// Set pivot to first element
	Song pivot = list[low];
	int up = low, down = high;
	while (up < down) {
		// While up is to the left of down, increment up by comparing the current sum of energy and
		// danceability to the pivot sum
		for (int _ = up; _ < high; _++) {
			if (list[up].danceability + list[up].energy < pivot.danceability + pivot.energy) {
				break;
			}
			up++;
		}
		// Decrement down the same way
		for (int _ = down; _ > low; _--) {
			if (list[down].danceability + list[down].energy > pivot.danceability + pivot.energy) {
				break;
			}
			down--;
		}
		// If up is still to the left of down, swap up and down
		if (up < down) {
			Song temp = list[up];
			list[up] = list[down];
			list[down] = temp;
		}
	}
	// Swap low and down
	Song temp = list[low];
	list[low] = list[down];
	list[down] = temp;
	return down;
}

SongList::SongList(float maxDance, float maxEnergy, bool expl) {
	// Keep track of track ID's since they are unique
	unordered_set<string> track_ids;
	unordered_set<string> artist_track;
	string path = "data/dataset.csv";
	ifstream file(path);
	// Relative path shenanigans
	while (!file.is_open()) {
		path = "../" + path;
		file = ifstream(path);
	}
	string line;
	getline(file, line); // Skip first line
	while (getline(file, line)) {
		stringstream ss(line);
		Song song;
		string data;
		getline(ss, data, ',');
		getline(ss, data, ','); // Track id
		if (track_ids.find(data) != track_ids.end()) {
			continue;
		}
		track_ids.insert(data);
		getline(ss, data); // Get rest of line

		// Get artist
		string d = parseString(data);
		data = data.substr(d.size() + 1);
		song.artist = d;

		// Get album name
		d = parseString(data);
		data = data.substr(d.size() + 1);
		song.album_name = d;

		// Get track name
		d = parseString(data);
		data = data.substr(d.size() + 1);
		song.track_name = d;
		
		// Some songs are repeat even with unique IDs. Add the artist + track name
		// to an unordered set and if the current song's artist + track name is in
		// the set, then we have a unqique ID repeated song. 
		if (artist_track.find(song.artist + song.track_name) != artist_track.end()) {
			continue;
		}
		artist_track.insert(song.artist + song.track_name);

		// Skip popularity
		d = parseString(data);
		data = data.substr(d.size() + 1);
		
		// Get duration
		d = parseString(data);
		data = data.substr(d.size() + 1);
		song.duration_ms = stoi(d);

		// Get explicit
		d = parseString(data);
		data = data.substr(d.size() + 1);
		song.expl = (d == "True");
		if (song.expl && !expl) {
			continue;
		}

		// Get danceability
		d = parseString(data);
		data = data.substr(d.size() + 1);
		if (stof(d) > maxDance) {
			continue;
		}
		song.danceability = stof(d);

		// Get energy
		d = parseString(data);
		data = data.substr(d.size() + 1);
		if (stof(d) > maxEnergy) {
			continue;
		}
		song.energy = stof(d);

		// Push into song list
		list.push_back(song);
	}
}

vector<SongList::Song> SongList::topTen() const {
	// Create a list and allocate *up to* 10 songs
	// Assume list is already sorted as needed
	vector<SongList::Song> vec(10);
	for (int i = 0; i < list.size(); i++) {
		if (i == 10) break;
		vec[i] = list[i];
	}
	return vec;
}

// These sorts for some reason do give different resutls
// sometimes, probably due to sorting over the sum.
// Might need to address.

void SongList::quicksort() {
	qsorthelper(0, list.size() - 1);
}

void SongList::shellsort() {
	// Start gap at half the list size, divide by 2 each iteration
	for (int gap = list.size() / 2; gap > 0; gap /= 2) {
		// Start i at the gap, increment by 1 until last index
		for (int i = gap; i < list.size(); i++) {
			// Start temp for swapping
			Song temp = list[i];
			int j;
			// Start j at i and decrement by gap until either j is greater than or
			// equal to the gap or the current sum at j - gap is less than the temp sum
			for (j = i; j >= gap && (list[j - gap].danceability + list[j - gap].energy) < temp.danceability + temp.energy; j -= gap) {
				// Set j element to the j - gap element
				list[j] = list[j - gap];
			}
			// Complete swap
			list[j] = temp;
		}
	}
}
