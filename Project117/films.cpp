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
        cout << "Назва: " << title << "\n"
            << "Режисер: " << director << "\n"
            << "Рік випуску: " << releaseYear << "\n"
            << "Жанр: " << genre << "\n\n"; 
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
        cout << "1. Додати фільм\n"
            << "2. Пошук фільмів\n"
            << "3. Редагувати фільм\n"
            << "4. Видалити фільм\n"
            << "5. Список фільмів\n"
            << "6. Вихід\n";

        cout << "Введіть свій вибір: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: addMovie(films); break;
        case 2: searchMovies(films); break;
        case 3: editMovie(films); break;
        case 4: deleteMovie(films); break;
        case 5: listMovies(films); break;
        case 6: cout << "До побачення!" << endl; break;
        default: cout << "Неправильний вибір. Спробуйте ще раз.\n";
        }
    } while (choice != 6);

    return 0;
}

void addMovie(vector<Movie>& films) {
    string title, director, genre;
    int releaseYear;

    cout << "Введіть назву фільму: ";
    getline(cin, title);
    cout << "Введіть режисера: ";
    getline(cin, director);
    cout << "Введіть рік випуску: ";
    cin >> releaseYear;
    cin.ignore();

    cout << "Введіть жанр (за бажанням): ";
    getline(cin, genre);

    films.push_back(Movie(title, director, releaseYear, genre));
    cout << "Фільм успішно доданий.\n";
}

void searchMovies(const vector<Movie>& films) {
    string search;
    cout << "Введіть назву або режисера для пошуку: ";
    getline(cin, search);

    bool found = false;
    for (const auto& movie : films) {
        if (movie.title.find(search) != string::npos || movie.director.find(search) != string::npos) {
            movie.print();
            found = true;
        }
    }
    if (!found) {
        cout << "Фільми не знайдено.\n";
    }
}

void editMovie(vector<Movie>& films) {
    string title;
    cout << "Введіть назву фільму для редагування: ";
    getline(cin, title);

    bool found = false;
    for (auto& movie : films) {
        if (movie.title == title) {
            found = true;
            cout << "Редагування фільму: " << movie.title << "\n";
            cout << "Введіть новий жанр: ";
            getline(cin, movie.genre);
            cout << "Фільм успішно оновлено.\n";
            break;
        }
    }
    if (!found) {
        cout << "Фільм не знайдено.\n";
    }
}

void deleteMovie(vector<Movie>& films) {
    string title;
    cout << "Введіть назву фільму для видалення: ";
    getline(cin, title);

    auto it = remove_if(films.begin(), films.end(), [&](const Movie& movie) {
        return movie.title == title;
        });

    if (it != films.end()) {
        films.erase(it, films.end());
        cout << "Фільм успішно видалено.\n";
    }
    else {
        cout << "Фільм не знайдено.\n";
    }
}

void listMovies(const vector<Movie>& films) {
    cout << "Сортувати за:\n1. Рік\n2. Алфавітний порядок\n";
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
        cout << "Неправильний вибір.\n";
    }
}
