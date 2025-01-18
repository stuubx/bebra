#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Movie {
public:
    string title;
    string director;
    int releaseYear;
    string genre;

    Movie(string t, string d, int r, string g = "")
        : title(t), director(d), releaseYear(r), genre(g) {
    }

    void print() const {
        cout << "�����: " << title << "\n"
            << "�������: " << director << "\n"
            << "г� �������: " << releaseYear << "\n"
            << "����: " << genre << "\n\n"; 
    }
};

void addMovie(vector<Movie>& films);
void searchMovies(const vector<Movie>& films);
void editMovie(vector<Movie>& films);
void deleteMovie(vector<Movie>& films);
void listMovies(const vector<Movie>& films);

int main() {
    setlocale(LC_ALL, "ukr");

    vector<Movie> films;

    int choice;
    do {
        cout << "1. ������ �����\n"
            << "2. ����� ������\n"
            << "3. ���������� �����\n"
            << "4. �������� �����\n"
            << "5. ������ ������\n"
            << "6. �����\n";

        cout << "������ ��� ����: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: addMovie(films); break;
        case 2: searchMovies(films); break;
        case 3: editMovie(films); break;
        case 4: deleteMovie(films); break;
        case 5: listMovies(films); break;
        case 6: cout << "�� ���������!" << endl; break;
        default: cout << "������������ ����. ��������� �� ���.\n";
        }
    } while (choice != 6);

    return 0;
}

void addMovie(vector<Movie>& films) {
    string title, director, genre;
    int releaseYear;

    cout << "������ ����� ������: ";
    getline(cin, title);
    cout << "������ ��������: ";
    getline(cin, director);
    cout << "������ �� �������: ";
    cin >> releaseYear;
    cin.ignore();

    cout << "������ ���� (�� ��������): ";
    getline(cin, genre);

    films.push_back(Movie(title, director, releaseYear, genre));
    cout << "Գ��� ������ �������.\n";
}

void searchMovies(const vector<Movie>& films) {
    string search;
    cout << "������ ����� ��� �������� ��� ������: ";
    getline(cin, search);

    bool found = false;
    for (const auto& movie : films) {
        if (movie.title.find(search) != string::npos || movie.director.find(search) != string::npos) {
            movie.print();
            found = true;
        }
    }
    if (!found) {
        cout << "Գ���� �� ��������.\n";
    }
}

void editMovie(vector<Movie>& films) {
    string title;
    cout << "������ ����� ������ ��� �����������: ";
    getline(cin, title);

    bool found = false;
    for (auto& movie : films) {
        if (movie.title == title) {
            found = true;
            cout << "����������� ������: " << movie.title << "\n";
            cout << "������ ����� ����: ";
            getline(cin, movie.genre);
            cout << "Գ��� ������ ��������.\n";
            break;
        }
    }
    if (!found) {
        cout << "Գ��� �� ��������.\n";
    }
}

void deleteMovie(vector<Movie>& films) {
    string title;
    cout << "������ ����� ������ ��� ���������: ";
    getline(cin, title);

    auto it = remove_if(films.begin(), films.end(), [&](const Movie& movie) {
        return movie.title == title;
        });

    if (it != films.end()) {
        films.erase(it, films.end());
        cout << "Գ��� ������ ��������.\n";
    }
    else {
        cout << "Գ��� �� ��������.\n";
    }
}

void listMovies(const vector<Movie>& films) {
    cout << "��������� ��:\n1. г�\n2. ��������� �������\n";
    int choice;
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        vector<Movie> sortedByYear = films;
        sort(sortedByYear.begin(), sortedByYear.end(), [](const Movie& a, const Movie& b) {
            return a.releaseYear < b.releaseYear;
            });

        for (const auto& movie : sortedByYear) {
            movie.print();
        }
    }
    else if (choice == 2) {
        vector<Movie> sortedByTitle = films;
        sort(sortedByTitle.begin(), sortedByTitle.end(), [](const Movie& a, const Movie& b) {
            return a.title < b.title;
            });

        for (const auto& movie : sortedByTitle) {
            movie.print();
        }
    }
    else {
        cout << "������������ ����.\n";
    }
}
