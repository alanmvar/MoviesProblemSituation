#include "StreamingService.h"
#include "Serie.h"
#include "Movie.h"
#include "Episode.h"
#include "InvalidRatingException.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

using namespace std;

StreamingService::StreamingService() {}

StreamingService::~StreamingService() {
    for (Video* v : video_list) {
        delete v;
    }
    video_list.clear();
}

Serie* StreamingService::find_serie_by_id(int id) {
    for (Video* v : video_list) {
        if (v->getType() == "series" && v->getId() == id) {
            return dynamic_cast<Serie*>(v);
        }
    }
    return nullptr;
}

void StreamingService::load_data(const string& filename) {
    ifstream file_stream(filename);
    if (!file_stream.is_open()) {
        cout << "Error: Could not open the file " << filename << "." << endl;
        return;
    }

    string line;
    getline(file_stream, line); // skip header

    while (getline(file_stream, line)) {
        stringstream string_stream(line);
        string type, name, genre, episode_title;
        string temp_val;
        int id = 0, length = 0, season = 0;
        float rating = 0.0f;

        getline(string_stream, temp_val, ',');
        if (temp_val.empty()) continue;
        id = stoi(temp_val);

        getline(string_stream, type, ',');
        getline(string_stream, name, ',');

        getline(string_stream, temp_val, ',');
        if (!temp_val.empty()) length = stoi(temp_val);

        getline(string_stream, genre, ',');

        getline(string_stream, temp_val, ',');
        if (!temp_val.empty()) rating = stof(temp_val);

        getline(string_stream, temp_val, ',');
        if (!temp_val.empty()) season = stoi(temp_val);

        getline(string_stream, episode_title, ',');

        Rating general_rate(rating);

        if (type == "series") {
            Serie* serie_ptr = new Serie(id, type, name, length, genre, general_rate);
            video_list.push_back(serie_ptr);
        }
        else if (type == "movie") {
            Movie* movie_ptr = new Movie(id, type, name, length, genre, general_rate);
            video_list.push_back(movie_ptr);
        }
        else if (type == "episode") {
            Serie* s = find_serie_by_id(id);
            if (s != nullptr) {
                Episode ep(episode_title, season, general_rate);
                s->addEpisode(ep);
            }
        }
    }

    file_stream.close();
}

void StreamingService::clear_console() const {
#if defined _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void StreamingService::pause() const {
#if defined _WIN32
    system("pause");
#else
    cout << "Press ENTER to continue...";
    cin.get();
#endif
}

short StreamingService::parse_input(const string& input) const {
    try {
        return stoi(input);
    }
    catch (...) {
        return -1;
    }
}

void StreamingService::show_all_videos() const {
    cout << "\n--- ALL VIDEOS ---\n";
    for (Video* v : video_list) {
        v->print();
        cout << "-----------------------------------\n";
    }
    pause();
}

void StreamingService::show_all_movies() const {
    cout << "\n--- ALL MOVIES ---\n";
    for (Video* v : video_list) {
        if (v->getType() == "movie") {
            v->print();
        }
    }
    pause();
}

void StreamingService::filter_movies_by_genre() const {
    string search_genre;
    cout << "Enter genre to search for movies: ";
    getline(cin, search_genre);
    cout << "\n--- MOVIES (" << search_genre << ") ---\n";
    for (Video* v : video_list) {
        if (v->getType() == "movie" && v->getGenre() == search_genre) {
            v->print();
        }
    }
    pause();
}

void StreamingService::filter_series_by_genre() const {
    string search_genre;
    cout << "Enter genre to search for series: ";
    getline(cin, search_genre);
    cout << "\n--- SERIES (" << search_genre << ") ---\n";
    for (Video* v : video_list) {
        if (v->getType() == "series" && v->getGenre() == search_genre) {
            v->print();
        }
    }
    pause();
}

void StreamingService::filter_movies_by_rating() const {
    string min_rating_str;
    cout << "Enter minimum rating (1-5): ";
    getline(cin, min_rating_str);
    try {
        float min_rating = stof(min_rating_str);
        cout << "\n--- MOVIES (Rating >= " << min_rating << ") ---\n";
        for (Video* v : video_list) {
            if (v->getType() == "movie" && v->getRating().getAverage() >= min_rating) {
                v->print();
            }
        }
    }
    catch (...) {
        cout << "Invalid rating format.\n";
    }
    pause();
}

void StreamingService::rate_video() {
    string video_title, new_rating_str;
    cout << "Enter the title of the video to rate: ";
    getline(cin, video_title);
    cout << "Enter your rating (1 to 5): ";
    getline(cin, new_rating_str);

    try {
        int new_rating = stoi(new_rating_str);
        bool found = false;

        for (Video* v : video_list) {
            if (v->getName() == video_title) {
                found = true;
                try {
                    v->getRating() += new_rating;
                    cout << "Rating added successfully to " << v->getName() << "! New average: " << v->getRating().getAverage() << "\n";
                }
                catch (const InvalidRatingException& e) {
                    cout << "Rating Exception: " << e.what() << "\n";
                }
                catch (const std::exception& e) {
                    cout << "Exception caught: " << e.what() << "\n";
                }
                break;
            }
        }
        if (!found) cout << "Video with title '" << video_title << "' not found.\n";
    }
    catch (...) {
        cout << "Invalid input format.\n";
    }
    pause();
}

void StreamingService::filter_episodes_by_series_and_rating() const {
    string series_title;
    string min_rating_str;
    cout << "Enter the series title: ";
    getline(cin, series_title);
    cout << "Enter minimum episode rating (1-5): ";
    getline(cin, min_rating_str);

    try {
        float min_rating = stof(min_rating_str);
        bool found_series = false;

        for (Video* v : video_list) {
            if (v->getType() == "series" && v->getName() == series_title) {
                found_series = true;
                Serie* s = dynamic_cast<Serie*>(v);
                cout << "\n--- EPISODES OF " << series_title << " (Rating >= " << min_rating << ") ---\n";

                bool has_episodes = false;
                for (Episode& ep : s->getEpisodes()) {
                    if (ep.getRating().getAverage() >= min_rating) {
                        ep.print();
                        has_episodes = true;
                    }
                }
                if (!has_episodes) cout << "No episodes found with that rating.\n";
            }
        }
        if (!found_series) cout << "Series not found.\n";
    }
    catch (...) {
        cout << "Invalid rating format.\n";
    }
    pause();
}

void StreamingService::start() {
    load_data("values.csv");

    const string menu =
        "\n======== STREAMING SERVICE ========\n"
        "[1] Show all videos\n"
        "[2] Show all movies\n"
        "[3] Filter movies by genre\n"
        "[4] Filter series by genre\n"
        "[5] Filter movies by min rating\n"
        "[6] Add a rating to a video\n"
        "[7] Filter episodes by series and rating\n"
        "[0] Exit\n"
        "===================================\n";

    short res = 0;

    do {
        cout << menu;
        cout << "Option > ";
        string input;
        getline(cin, input);

        res = parse_input(input);
        clear_console();

        switch (res) {
        case 1:
            show_all_videos();
            break;
        case 2:
            show_all_movies();
            break;
        case 3:
            filter_movies_by_genre();
            break;
        case 4:
            filter_series_by_genre();
            break;
        case 5:
            filter_movies_by_rating();
            break;
        case 6:
            rate_video();
            break;
        case 7:
            filter_episodes_by_series_and_rating();
            break;
        case 0:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid option, try again\n";
            pause();
            break;
        }
        if (res != 0) {
            clear_console();
        }
    } while (res != 0);
}