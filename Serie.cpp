#include "Serie.h"

Serie::Serie(int id, string type, string name, int length, string genre, Rating rating) : Video(id, type, name, length, genre, rating) {
}

void Serie::addEpisode(const Episode& ep) {
    episodes.push_back(ep);
}

vector<Episode>& Serie::getEpisodes() {
    return episodes;
}

void Serie::print() const {
    cout << "SERIES [" << id << "] " << name
        << " | Genre: " << genre
        << " | Total Episodes: " << episodes.size()
        << " | Rating: " << rating.getAverage() << "/5.0\n";
    for (const auto& ep : episodes) {
        ep.print();
    }
}