#pragma once
#include "Video.h"

class Episode
{
private:

public:
	Episode(int id, string type, string name, int length, string genre, Rating rating);
	void show() override;
};


