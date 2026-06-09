#include "Video.h"

Video::Video(int id, string type, string name, int length, string genre, Rating general_rate) : rating(general_rate) {
	this->id = id;
	this->type = type;
	this->name = name;
	this->length = length;
	this->genre = genre;
}

int Video::getId() const {
	return id;
}

string Video::getName() const {
	return name;
}

void Video::setName(string name) {
	this->name = name;
}

string Video::getType() const {
	return type;
}

int Video::getLength() const {
	return length;
}

string Video::getGenre() const {
	return genre;
}

Rating& Video::getRating() {
	return rating;
}