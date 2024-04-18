#pragma once
#include <vector>
#include <string>
#include <sstream>
using namespace std;

/*
	TODO:
	1. Implement sorts for SongList
	2. Implement summing danceability and energy for sorting purposes
		a. This probably will work better than sorting each individually
		since there might be problems where even after pruning, the
		recommended songs might not be the actual best songs with 
		what the user wants in mind. It'll prioritize the second category
		sorted, rather than treating both equally. 
	
	NOTE: For explicit, there should be three options: yes, no, or
	both, since the user could just not care about whether a song is 
	explicit or not
*/

class SongList {
public:
	struct Song {
		string artist;
		string album_name;
		string track_name;
		int duration_ms;
		bool expl;
		float danceability;
		float energy;
	};
public: // Make private when done testing
	// NOTE: Track ID's are unique
	vector<Song> list;
	void qsorthelper(int low, int high);
	int partition(int low, int high);
	static string parseString(string data) {
		string s = "";
		bool quotes = false;
		int quotenum = 0;
		for (int i = 0; i < data.size(); i++) {
			if (data[i] == '"' && !quotes) {
				quotes = true;
			}
			if (data[i] == '"' && quotes) {
				quotenum++;
			}
			if (quotes && data[i] == '"' && data[i + 1] == ',' && quotenum % 2 == 0) {
				s += data[i];
				break;
			}
			if (!quotes && data[i] == ',') {
				break;
			}
			s += data[i];
		}
		return s;
	}
public:
	// expl = false -> No explicit, expl = true -> Both explicit and not explicit
	SongList(float maxDance, float maxEnergy, bool expl);
	vector<Song> topTen() const;
	void quicksort();
	void shellsort();
	
};