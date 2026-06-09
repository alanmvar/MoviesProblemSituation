#include "Episode.h"

Episode::Episode(string title, int season, Rating rating) : rating(rating) {
    this->title = title;
    this->season = season;
}

string Episode::getTitle() const {
    return title;
}

int Episode::getSeason() const {
    return season;
}

Rating& Episode::getRating() {
    return rating;
}

void Episode::print() const {
    cout << "  -> EPISODE: S" << season << " - " << title
        << " | Rating: " << rating.getAverage() << "/5.0\n";
}