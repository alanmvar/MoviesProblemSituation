#pragma once
#include "Video.h"

class Movie: public Video
{
private:

public:
	Movie(int id, string type, string name, int length, string genre, Rating rating);
	void show() override;
};

