#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include "Video.h"
#include "Serie.h"
#include "Movie.h"
#include "Episode.h"
#include "InvalidRatingException.h"

using namespace std;

// Function to find a series by ID in the vector
Serie* findSerieById(vector<Video*>& videos, int id) {
    for (Video* v : videos) {
        if (v->getType() == "series" && v->getId() == id) {
            return dynamic_cast<Serie*>(v);
        }
    }
    return nullptr;
}

void getVideos(vector<Video*>& videos) {
    ifstream archivo("values.csv");
    if (!archivo.is_open()) {
        cout << "Error: Could not open the file value_prueba.csv." << endl;
        return;
    }

    string linea;
    getline(archivo, linea); // skip header

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string type, name, genre, episode_title;
        string temp_val;
        int id = 0, length = 0, season = 0;
        float rating = 0.0f;

        // CSV Format: ID,Type,Name,Length,Genre,Rating,Season,EpisodeTitle
        getline(ss, temp_val, ',');
        if (temp_val.empty()) continue;
        id = stoi(temp_val);

        getline(ss, type, ',');
        getline(ss, name, ',');

        getline(ss, temp_val, ',');
        if (!temp_val.empty()) length = stoi(temp_val);

        getline(ss, genre, ',');

        getline(ss, temp_val, ',');
        if (!temp_val.empty()) rating = stof(temp_val);

        getline(ss, temp_val, ',');
        if (!temp_val.empty()) season = stoi(temp_val);

        getline(ss, episode_title, ',');

        Rating general_rate(rating);

        if (type == "series") {
            Serie* serie = new Serie(id, type, name, length, genre, general_rate);
            videos.push_back(serie);
        }
        else if (type == "movie") {
            Movie* movie = new Movie(id, type, name, length, genre, general_rate);
            videos.push_back(movie);
        }
        else if (type == "episode") {
            // Find the series and add the episode
            Serie* s = findSerieById(videos, id);
            if (s != nullptr) {
                Episode ep(episode_title, season, general_rate);
                s->addEpisode(ep);
            }
        }
    }

    archivo.close();
}

void clearConsole() {
#if defined _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pause() {
#if defined _WIN32
    system("pause");
#else
    cout << "Press ENTER to continue...";
    cin.get();
#endif
}

short transInputToShort(const string& input) {
    try {
        return stoi(input);
    }
    catch (...) {
        return -1;
    }
}

int main()
{
    vector<Video*> lista_videos;
    getVideos(lista_videos);

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

        res = transInputToShort(input);
        clearConsole();

        switch (res) {
        case 1:
            cout << "\n--- ALL VIDEOS ---\n";
            for (Video* v : lista_videos) {
                v->print();
                cout << "-----------------------------------\n";
            }
            pause();
            break;
        case 2:
            cout << "\n--- ALL MOVIES ---\n";
            for (Video* v : lista_videos) {
                if (v->getType() == "movie") {
                    v->print();
                }
            }
            pause();
            break;
        case 3: {
            string search_genre;
            cout << "Enter genre to search for movies: ";
            getline(cin, search_genre);
            cout << "\n--- MOVIES (" << search_genre << ") ---\n";
            for (Video* v : lista_videos) {
                if (v->getType() == "movie" && v->getGenre() == search_genre) {
                    v->print();
                }
            }
            pause();
            break;
        }
        case 4: {
            string search_genre;
            cout << "Enter genre to search for series: ";
            getline(cin, search_genre);
            cout << "\n--- SERIES (" << search_genre << ") ---\n";
            for (Video* v : lista_videos) {
                if (v->getType() == "series" && v->getGenre() == search_genre) {
                    v->print();
                }
            }
            pause();
            break;
        }
        case 5: {
            string min_rating_str;
            cout << "Enter minimum rating (1-5): ";
            getline(cin, min_rating_str);
            try {
                float min_rating = stof(min_rating_str);
                cout << "\n--- MOVIES (Rating >= " << min_rating << ") ---\n";
                for (Video* v : lista_videos) {
                    if (v->getType() == "movie" && v->getRating().getAverage() >= min_rating) {
                        v->print();
                    }
                }
            }
            catch (...) {
                cout << "Invalid rating format.\n";
            }
            pause();
            break;
        }
        case 6: {
            string video_title, new_rating_str;
            cout << "Enter the title of the video to rate: ";
            getline(cin, video_title);
            cout << "Enter your rating (1 to 5): ";
            getline(cin, new_rating_str);

            try {
                int new_rating = stoi(new_rating_str);
                bool found = false;

                for (Video* v : lista_videos) {
                    if (v->getName() == video_title) {
                        found = true;
                        try {
                            v->getRating() += new_rating;
                            cout << "Rating added successfully to " << v->getName() << "! New average: " << v->getRating().getAverage() << "\n";
                        }
                        // --- AQUÍ REEMPLAZAS Y AGREGAS TU EXCEPCIÓN ---
                        catch (const InvalidRatingException& e) {
                            cout << "Rating Exception: " << e.what() << "\n";
                        }
                        catch (const std::exception& e) {
                            cout << "Exception caught: " << e.what() << "\n";
                        }
                        // ----------------------------------------------
                        break;
                    }
                }
                if (!found) cout << "Video with title '" << video_title << "' not found.\n";
            }
            catch (...) {
                cout << "Invalid input format.\n";
            }
            pause();
            break;
        }
        case 7: {
            string series_title;
            string min_rating_str;
            cout << "Enter the series title: ";
            getline(cin, series_title);
            cout << "Enter minimum episode rating (1-5): ";
            getline(cin, min_rating_str);

            try {
                float min_rating = stof(min_rating_str);
                bool found_series = false;

                for (Video* v : lista_videos) {
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
            break;
        }
        case 0:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid option, try again\n";
            pause();
            break;
        }
        clearConsole();
    } while (res != 0);

    // Clean up memory to avoid leaks
    for (Video* v : lista_videos) {
        delete v;
    }
    lista_videos.clear();

    return 0;
}