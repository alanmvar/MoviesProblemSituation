#pragma once
#include "Video.h"

class Serie : public Video
{
private:

public:
	Serie(int id, string type, string name, int length, string genre, Rating rating);
	//void show() override;
};
