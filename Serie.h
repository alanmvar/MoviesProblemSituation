#pragma once
#include "Video.h"
#include "Episode.h"
#include <vector>

class Serie : public Video
{
private:
    vector<Episode> episodes;
public:
    Serie(int id, string type, string name, int length, string genre, Rating rating);

    void addEpisode(const Episode& ep);
    vector<Episode>& getEpisodes();

    void print() const override;
};