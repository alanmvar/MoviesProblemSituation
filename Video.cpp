#include "Video.h"
Video::Video(int id, string type, string name, int length, string genre, Rating generalRate) : rating(generalRate){
	this-> id = id;
	this->type = type;
	this->name = name;
	this->length = length;
	this->genre = genre;
};
int Video::getId() {
	return id;
};
string Video::getName() {
	return name;
};
string Video::getType() {
	return type;
};
int Video::getLength() {
	return length;
};
string Video::getGenre() {
	return genre;
};
/*
void Video::show() {

};
*/