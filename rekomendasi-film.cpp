#include <iostream>
#include <iomanip>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

struct Film {
    string judul;
    double rating;
    vector<string> komentar;
};

void tampilkanHeader(const string& judul) {
    cout << "\n===============================\n";
    cout << "  " << judul << "\n";
    cout << "===============================\n";
}

void tambahFilm(queue<Film>& daftarFilm) {
    if (daftarFilm.size() >= 50) {
        cout << "Daftar film sudah penuh (maksimal 50 film). Tidak dapat menambahkan film baru.\n";
        return;
    }
    tampilkanHeader("Tambah Film");
    Film film;

    cout << "Masukkan judul film: ";
    cin.ignore();
    getline(cin, film.judul);

    do {
        cout << "Masukkan rating film (0-10): ";
        cin >> film.rating;
        if (film.rating < 0 || film.rating > 10) {
            cout << "Rating harus antara 0 hingga 10. Silakan coba lagi.\n";
        }
    } while (film.rating < 0 || film.rating > 10);

    daftarFilm.push(film);
    cout << "\nFilm berhasil ditambahkan!\n";
}

void tampilkanFilm(queue<Film> daftarFilm) {
    tampilkanHeader("Daftar Film");
    if (daftarFilm.empty()) {
        cout << "Belum ada film yang ditambahkan.\n";
        return;
    }
    while (!daftarFilm.empty()) {
        Film film = daftarFilm.front();
        cout << "Judul: " << film.judul << "\nRating: " << fixed << setprecision(1) << film.rating << "\n";
        if (!film.komentar.empty()) {
            cout << "Komentar:\n";
            for (const auto& komentar : film.komentar) {
                cout << "- " << komentar << "\n";
            }
        }
        daftarFilm.pop();
    }
}

void tambahKomentar(queue<Film>& daftarFilm) {
    tampilkanHeader("Tambah Komentar");
    if (daftarFilm.empty()) {
        cout << "Belum ada film yang ditambahkan.\n";
        return;
    }

    string judul;
    cout << "Masukkan judul film yang ingin dikomentari: ";
    cin.ignore();
    getline(cin, judul);

    queue<Film> temp;
    bool ditemukan = false;

    while (!daftarFilm.empty()) {
        Film film = daftarFilm.front();
        daftarFilm.pop();
        if (film.judul == judul) {
            string komentar;
            cout << "Masukkan komentar: ";
            getline(cin, komentar);
            film.komentar.push_back(komentar);
            ditemukan = true;
        }
        temp.push(film);
    }
    daftarFilm = temp;
    if (ditemukan) {
        cout << "Komentar berhasil ditambahkan.\n";
    } else {
        cout << "Film tidak ditemukan.\n";
    }
}

void cariFilm(queue<Film> daftarFilm) {
    tampilkanHeader("Cari Film");
    string keyword;
    cout << "Masukkan keyword: ";
    cin.ignore();
    getline(cin, keyword);

    bool ditemukan = false;
    while (!daftarFilm.empty()) {
        Film film = daftarFilm.front();
        daftarFilm.pop();
        if (film.judul.find(keyword) != string::npos) {
            cout << "Judul: " << film.judul << "\nRating: " << fixed << setprecision(1) << film.rating << "\n";
            ditemukan = true;
        }
    }
    if (!ditemukan) {
        cout << "Film dengan keyword '" << keyword << "' tidak ditemukan.\n";
    }
}

void hapusFilmTerbaru(queue<Film>& daftarFilm) {
    tampilkanHeader("Hapus Film Terbaru");
    if (daftarFilm.empty()) {
        cout << "Tidak ada film untuk dihapus.\n";
        return;
    }

    queue<Film> temp;
    while (daftarFilm.size() > 1) {
        temp.push(daftarFilm.front());
        daftarFilm.pop();
    }
    daftarFilm.pop();
    daftarFilm = temp;
    cout << "Film terbaru berhasil dihapus.\n";
}

void tampilkanFilmTerbaik(queue<Film> daftarFilm) {
    tampilkanHeader("Film Berdasarkan Rating Tertinggi");
    vector<Film> filmList;
    while (!daftarFilm.empty()) {
        filmList.push_back(daftarFilm.front());
        daftarFilm.pop();
    }
    sort(filmList.begin(), filmList.end(), [](const Film& a, const Film& b) {
        return a.rating > b.rating;
    });
    for (const auto& film : filmList) {
        cout << "Judul: " << film.judul << "\nRating: " << fixed << setprecision(1) << film.rating << "\n";
    }
}

int main() {
    queue<Film> daftarFilm;
    int pilihan;
    do {
        tampilkanHeader("Sistem Manajemen Film");
        cout << "1. Tambah Film\n";
        cout << "2. Tampilkan Semua Film\n";
        cout << "3. Tambah Komentar\n";
        cout << "4. Cari Film\n";
        cout << "5. Hapus Film Terbaru\n";
        cout << "6. Tampilkan Film Terbaik\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: tambahFilm(daftarFilm); break;
            case 2: tampilkanFilm(daftarFilm); break;
            case 3: tambahKomentar(daftarFilm); break;
            case 4: cariFilm(daftarFilm); break;
            case 5: hapusFilmTerbaru(daftarFilm); break;
            case 6: tampilkanFilmTerbaik(daftarFilm); break;
            case 0: cout << "Keluar dari program.\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 0);
    return 0;
}
