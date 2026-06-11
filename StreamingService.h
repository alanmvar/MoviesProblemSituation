#pragma once
#include <vector>
#include <string>
#include "Video.h"

class StreamingService {
private:
    std::vector<Video*> video_list;

    class Serie* find_serie_by_id(int id);
    void clear_console() const;
    void pause() const;
    short parse_input(const std::string& input) const;

    void show_all_videos() const;
    void show_all_movies() const;
    void filter_movies_by_genre() const;
    void filter_series_by_genre() const;
    void filter_movies_by_rating() const;
    void rate_video();
    void filter_episodes_by_series_and_rating() const;

public:
    StreamingService();
    ~StreamingService();

    void load_data(const std::string& filename);
    void start();
};