#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "Video.h"
#include "Serie.h"
#include "Movie.h"
#include "Episode.h"

using namespace std;


void getVideos(vector<Video*>& Videos) {

    ifstream archivo("value_prueba.csv");
    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo." << endl;
        return;
    }

    string linea;
    getline(archivo, linea);

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string valor_temporal;
        string type, name, genre;
        int length, id;
        float rating;

        getline(ss, valor_temporal, ',');
        id = stoi(valor_temporal);
        getline(ss, type, ',');
        getline(ss, name, ',');
        getline(ss, valor_temporal, ',');
        length = stoi(valor_temporal);
        getline(ss, genre, ',');
        getline(ss, valor_temporal, ',');
        rating = stof(valor_temporal);

        Rating generalRate(rating);

        if (type == "series") {
            Serie* serie = new Serie(id, type, name, length, genre, generalRate);
            Videos.push_back(serie);
        }
        else {
            Movie* movie = new Movie(id, type, name, length, genre, generalRate);
            Videos.push_back(movie);
        }
    }

    archivo.close();
}

int main()
{
    vector<Video*> listaVideos;
    getVideos(listaVideos);

    for (Video* v : listaVideos) {
        cout << "ID: " << v->getId()
            << " | " << v->getType()
            << " | Title: " << v->getName()
            << " | Genre: " << v->getGenre()
            << " | Length: " << v->getLength() << " min" << endl;
    }

    cout << "-----------------------------------" << endl;

    for (Video* v : listaVideos) {
        delete v;
    }
    listaVideos.clear();

    return 0;
}

