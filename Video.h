#pragma once
#include "Rating.h"
#include <string> 

using namespace std;

class Video
{
protected:
	int id;
	string type;
	string name;
	int length;
	string genre;
	Rating rating;
public:
	Video(int id, string type, string name, int length, string genre, Rating rating);
	int getId();
	string getName();
	void setName(string name);
	string getType();
	int getLength();
	string getGenre();
	//virtual void show();
};

