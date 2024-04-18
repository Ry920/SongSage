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
	qsorthelper(low, p - 1);
	qsorthelper(p + 1, high);
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
	qsorthelper(0, list.size());
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
