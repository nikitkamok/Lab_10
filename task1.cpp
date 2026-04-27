#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int SIZE = 20;

struct mountain {
    char name[85];
    double height;
    char country[45];
    char type[13];
};

void swal(mountain& m1, mountain& m2) {
    mountain tmp = m1;
    m1 = m2;
    m2 = tmp;
}

double avg_height(mountain mountains[]) {
    double avg = 0;
    for (int i = 0; i < SIZE; i++) {
        avg += mountains[i].height;
    }
    return avg / SIZE;
}

bool height_sort(mountain a, mountain b) {
    return a.height < b.height;
}

bool heigh_filter(mountain m) {
    return m.height >= 8000;
}

mountain* srt(mountain mountains[], bool (*f) (mountain, mountain)) {
    for (int i = 0; i < SIZE; i++)
        for (int j = SIZE - 1; j >= i; j--)
            if (f(mountains[i], mountains[j]))
                swal(mountains[i], mountains[j]);
    return mountains;
}

void infoForHeigh(mountain mountains[], bool (*f) (mountain)) {
    for (int i = 0; i < SIZE; ++i) {
        if (f(mountains[i])) {
            cout << "Гора " << mountains[i].name << " имеет высоту "
            << mountains[i].height << "м и находится в " << mountains[i].country << '\n';
        }
    }
}

// ну а что кроме высоты мы еще можем изменить у горы?
void changeInfoForName(mountain mountains[], char name[], double new_height) {
    for (int i = 0; i < SIZE; ++i) {
        if (strcmp(mountains[i].name, name) == 0) {
            mountains[i].height = new_height;
            cout << "Высота горы " << mountains[i].name
            << " изменена на " << new_height << "м\n";
            return;
        }
    }
    cout << "Гора не найдена\n";
}

int* indx(mountain mountains[], char country[], int& count) {
    static int indices[SIZE];
    count = 0;
    for (int i = 0; i < SIZE; ++i) {
        if (strstr(mountains[i].country, country) != nullptr) {
            indices[count] = i;
            count++;
        }
    }
    return indices;
}

mountain* mountainsOfOneCounty(mountain mountains[], int& count) {
    cout << "Введите страну для объединения гор\n";
    char country[45];
    cin.getline(country, 45);
    int *indices = indx(mountains, country, count);
    mountain *new_m = new mountain[count];
    if (count == 0) {
        cout << "Гор из страны \"" << country << "\" не найдено\n";
        return new_m;
    }
    for (int k = 0; k < count; ++k) {
        int i = indices[k];
        strcpy(new_m[k].name, mountains[i].name);
        new_m[k].height = mountains[i].height;
        strcpy(new_m[k].country, mountains[i].country);
        strcpy(new_m[k].type, mountains[i].type);
    }
    return new_m;
}

void print_mountain(mountain mountains[]) {
    for (int i = 0; i < SIZE; ++i) {
        cout << i << ": " << mountains[i].name << " "
        << mountains[i].height << " "
        << mountains[i].country << " "
        << mountains[i].type <<'\n';
    }
}

void print_mountain(mountain mountains[], int size) {
    for (int i = 0; i < size; ++i) {
        cout << i << ": " << mountains[i].name << " "
        << mountains[i].height << " "
        << mountains[i].country << " "
        << mountains[i].type <<'\n';
    }
}

void print_mountain(mountain mountains[], string name) {
    for (int i = 0; i < SIZE; ++i) {
        if (mountains[i].name == name) {
            cout << i << ": " << mountains[i].name << " "
            << mountains[i].height << " "
            << mountains[i].country << " "
            << mountains[i].type <<'\n';
            return;
        }
    }
    cout << "Гора не найдена\n";
}

mountain* init() {
    mountain* mountains = new mountain[SIZE];
    mountains[0] = {"Fuji", 3776, "Japan", "volcanic"};
    mountains[1] = {"Elbert", 4401, "USA", "folded"};
    mountains[2] = {"Roraima", 2810, "Venezuela", "plateau-like"};
    mountains[3] = {"Etna", 3357, "Italy", "volcanic"};
    mountains[4] = {"Everest", 8849, "Nepal/China", "folded"};
    mountains[5] = {"K2", 8611, "Pakistan/China", "folded"};
    mountains[6] = {"Kangchenjunga", 8586, "Nepal/India", "folded"};
    mountains[7] = {"Lhotse", 8516, "Nepal/China", "folded"};
    mountains[8] = {"Kilimanjaro", 5895, "Tanzania", "plateau-like"};
    mountains[9] = {"Klyuchevskaya", 4754, "Russia", "volcanic"};
    mountains[10] = {"Logan", 5959, "Canada", "folded"};
    mountains[11] = {"Aspiring", 3033, "New Zealand", "folded"};
    mountains[12] = {"Nyiragongo", 3470, "DRCongo", "volcanic"};
    mountains[13] = {"Auyan", 2530, "Venezuela", "plateau-like"};
    mountains[14] = {"Hubbard", 4557, "Canada", "folded"};
    mountains[15] = {"Cameroon", 4040, "Cameroon", "volcanic"};
    mountains[16] = {"Erebus", 3794, "Antarctica", "volcanic"};
    mountains[17] = {"Kailash", 6638, "China", "plateau-like"};
    mountains[18] = {"Snowdon", 1085, "UK", "folded"};
    mountains[19] = {"Shasta", 4322, "USA", "volcanic"};
    return mountains;
}

void readHeightFromTextFile(mountain mountains[], char filename[]) {
    ifstream fin;
    fin.open(filename);
    char mountain_name[85];
    double new_height;
    while (fin >> mountain_name >> new_height) {
        for (int i = 0; i < SIZE; ++i) {
            if (strcmp(mountains[i].name, mountain_name) == 0) {
                mountains[i].height = new_height;
                break;
            }
        }
    }
    fin.close();
}

void writeBinFile(mountain mountains[], const char filename[]) {
    ofstream fout;
    fout.open(filename);
    if (fout.is_open()) {
        for (int i = 0; i < SIZE; i++) {
            fout.write((char*)&mountains[i], sizeof(mountains[i]));
        }
    }
    fout.close();
}

void readBinFile(mountain mountains[], const char filename[]) {
    ifstream fin;
    fin.open(filename);
    if (fin.is_open()) {
        int i = 0;
        while (!fin.eof()) {
            fin.read((char*)&mountains[i], sizeof(mountains[i]));
            i++;
        }
    }
    fin.read((char*)mountains, sizeof(mountain) * SIZE);
    fin.close();
}

int main() {
    setlocale(LC_ALL, "");

    mountain *mountains = init();
    cout << "\n==========ВЫВОД МАССИВА ДАННЫХ===========================\n";
    print_mountain(mountains);
    cout << "\n==========ВЫВОД СРЕДНЕЙ ВЫСОТЫ ВЕРШИН====================\n";
    cout << avg_height(mountains);
    cout << "\n==========ВЫВОД ОТСОРТИРОВАННОГО МАССИВА ДАННЫХ==========\n";
    srt(mountains, height_sort);
    print_mountain(mountains);
    cout << "\n==========ВЫВОД 4x ВОСЬМИТЫСЯЧНИКОВ======================\n";
    infoForHeigh(mountains, heigh_filter);
    cout << "\n==========ИЗМЕНЕНИЕ ДАННЫХ ВЫСОТЫ ВЕРШИНЫ ГОРЫ===========\n";
    changeInfoForName(mountains, "Snowdon", 4315);
    print_mountain(mountains, "Snowdon");
    cout << "\n==========ИЗМЕНЕНИЕ ДАННЫХ ВЫСОТЫ ВЕРШИНЫ ГОРЫ===========\n";
    int size = 0;
    mountain *new_m = mountainsOfOneCounty(mountains, size);
    print_mountain(new_m, size);
    cout << "\n==========ЧТЕНИЕ ВЫСОТ ИЗ ТЕКСТОВОГО ФАЙЛА===============\n";
    readHeightFromTextFile(mountains, "heights.txt");
    print_mountain(mountains);
    cout << "\n==========ЗАПИСЬ В БИНАРНЫЙ ФАЙЛ=========================\n";
    writeBinFile(mountains, "mountains_example.dat");
    cout << "\n==========ЧТЕНИЕ ИЗ БИНАРНОГО ФАЙЛА======================\n";
    mountain* loaded = new mountain[SIZE];
    readBinFile(loaded, "mountains_example.dat");
    print_mountain(loaded);

    delete[] mountains;
    delete[] new_m;
    delete[] loaded;
}
