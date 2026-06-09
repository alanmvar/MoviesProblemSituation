#pragma once
#include <string>
#include <iostream>
#include "Rating.h"

using namespace std;

class Episode
{
private:
    string title;
    int season;
    Rating rating;
public:
    Episode(string title, int season, Rating rating);

    string getTitle() const;
    int getSeason() const;
    Rating& getRating();

    void print() const;
};