#pragma once
#include "Video.h"

class Movie : public Video
{
public:
	Movie(int id, string type, string name, int length, string genre, Rating rating);
	void print() const override;
};

#pragma once