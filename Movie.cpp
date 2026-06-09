#include "Movie.h"

Movie::Movie(int id, string type, string name, int length, string genre, Rating rating) : Video(id, type, name, length, genre, rating) {
}

void Movie::print() const {
    cout << "MOVIE [" << id << "] " << name
        << " | Genre: " << genre
        << " | Length: " << length << " min"
        << " | Rating: " << rating.getAverage() << "/5.0\n";
}