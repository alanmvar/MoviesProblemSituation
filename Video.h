#pragma once
#include "Rating.h"
#include <string>
#include <iostream>

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
	virtual ~Video() = default; // Virtual destructor

	int getId() const;
	string getName() const;
	void setName(string name);
	string getType() const;
	int getLength() const;
	string getGenre() const;
	Rating& getRating();

	virtual void print() const = 0; // Pure virtual function
};