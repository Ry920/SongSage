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
	if (p != 0) {
		qsorthelper(low, p - 1);
	}
	if (p != high) {
		qsorthelper(p + 1, high);
	}
}

int SongList::partition(int low, int high) {
	Song pivot = list[low];
	int up = low, down = high;
	while (up < down) {
		for (int _ = up; _ < high; _++) {
			if (list[up].danceability + list[up].energy < pivot.danceability + pivot.energy) {
				break;
			}
			up++;
		}
		for (int _ = down; _ > low; _--) {
			if (list[down].danceability + list[down].energy > pivot.danceability + pivot.energy) {
				break;
			}
			down--;
		}
		if (up < down) {
			Song temp = list[up];
			list[up] = list[down];
			list[down] = temp;
		}
	}
	Song temp = list[low];
	list[low] = list[down];
	list[down] = temp;
	return down;
}

SongList::SongList(float maxDance, float maxEnergy, bool expl) {
	// Keep track of track ID's since they are unique
	unordered_set<string> track_ids;
	// TODO: Continue implementation with file reading
	//			a. Implement with limits here so that 
	//			the songs are loaded after the user's
	//			choice is already made
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

// These sorts for some reason do give different results
// sometimes, probably due to sorting over the sum.
// Might need to address.

void SongList::quicksort() {
	qsorthelper(0, list.size() - 1);
}

void SongList::shellsort() {
	for (int gap = list.size() / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < list.size(); i++) {
			Song temp = list[i];
			int j;
			for (j = i; j >= gap && (list[j - gap].danceability + list[j - gap].energy) < temp.danceability + temp.energy; j -= gap) {
				list[j] = list[j - gap];
			}
			list[j] = temp;
		}
	}
}
