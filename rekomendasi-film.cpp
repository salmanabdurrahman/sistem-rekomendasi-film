#include <iostream>
#include <iomanip>
#include <string>
#include <queue>
#include <set>
using namespace std;

struct Film {
    string judul;
    double rating;
    string komentar[10];
    int jumlahKomentar = 0;
    bool favorit = false;
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
        if (film.jumlahKomentar > 0) {
            cout << "Komentar:\n";
            for (int i = 0; i < film.jumlahKomentar; ++i) {
                cout << "- " << film.komentar[i] << "\n";
            }
        }
        cout << "Favorit: " << (film.favorit ? "Ya" : "Tidak") << "\n";
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
            if (film.jumlahKomentar < 10) {
                string komentar;
                cout << "Masukkan komentar: ";
                getline(cin, komentar);
                film.komentar[film.jumlahKomentar++] = komentar;
                ditemukan = true;
            } else {
                cout << "Komentar penuh. Tidak dapat menambahkan komentar baru.\n";
            }
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

void tambahFavorit(queue<Film>& daftarFilm) {
    tampilkanHeader("Tambah ke Favorit");
    if (daftarFilm.empty()) {
        cout << "Belum ada film yang ditambahkan.\n";
        return;
    }

    string judul;
    cout << "Masukkan judul film yang ingin ditandai sebagai favorit: ";
    cin.ignore();
    getline(cin, judul);

    queue<Film> temp;
    bool ditemukan = false;

    while (!daftarFilm.empty()) {
        Film film = daftarFilm.front();
        daftarFilm.pop();
        if (film.judul == judul) {
            film.favorit = true;
            ditemukan = true;
        }
        temp.push(film);
    }
    daftarFilm = temp;
    if (ditemukan) {
        cout << "Film berhasil ditandai sebagai favorit.\n";
    } else {
        cout << "Film tidak ditemukan.\n";
    }
}

void lihatFavorit(queue<Film> daftarFilm) {
    tampilkanHeader("Daftar Film Favorit");
    bool adaFavorit = false;
    while (!daftarFilm.empty()) {
        Film film = daftarFilm.front();
        daftarFilm.pop();
        if (film.favorit) {
            cout << "Judul: " << film.judul << "\nRating: " << fixed << setprecision(1) << film.rating << "\n";
            adaFavorit = true;
        }
    }
    if (!adaFavorit) {
        cout << "Belum ada film favorit.\n";
    }
}

void editRating(queue<Film>& daftarFilm) {
    tampilkanHeader("Edit Rating Film");
    if (daftarFilm.empty()) {
        cout << "Belum ada film yang ditambahkan.\n";
        return;
    }

    string judul;
    cout << "Masukkan judul film yang ingin diubah ratingnya: ";
    cin.ignore();
    getline(cin, judul);

    queue<Film> temp;
    bool ditemukan = false;

    while (!daftarFilm.empty()) {
        Film film = daftarFilm.front();
        daftarFilm.pop();
        if (film.judul == judul) {
            double ratingBaru;
            do {
                cout << "Masukkan rating baru (0-10): ";
                cin >> ratingBaru;
                if (ratingBaru < 0 || ratingBaru > 10) {
                    cout << "Rating harus antara 0 hingga 10. Silakan coba lagi.\n";
                }
            } while (ratingBaru < 0 || ratingBaru > 10);
            film.rating = ratingBaru;
            ditemukan = true;
        }
        temp.push(film);
    }
    daftarFilm = temp;
    if (ditemukan) {
        cout << "Rating film berhasil diubah.\n";
    } else {
        cout << "Film tidak ditemukan.\n";
    }
}

void hapusFilm(queue<Film>& daftarFilm) {
    tampilkanHeader("Hapus Film Berdasarkan Judul");
    if (daftarFilm.empty()) {
        cout << "Belum ada film yang ditambahkan.\n";
        return;
    }

    string judul;
    cout << "Masukkan judul film yang ingin dihapus: ";
    cin.ignore();
    getline(cin, judul);

    queue<Film> temp;
    bool ditemukan = false;

    while (!daftarFilm.empty()) {
        Film film = daftarFilm.front();
        daftarFilm.pop();
        if (film.judul != judul) {
            temp.push(film);
        } else {
            ditemukan = true;
        }
    }
    daftarFilm = temp;
    if (ditemukan) {
        cout << "Film berhasil dihapus.\n";
    } else {
        cout << "Film tidak ditemukan.\n";
    }
}

void urutkanFilm(queue<Film> daftarFilm) {
    tampilkanHeader("Film Berdasarkan Urutan Judul");
    set<string> judulSet;
    queue<Film> temp;

    while (!daftarFilm.empty()) {
        Film film = daftarFilm.front();
        daftarFilm.pop();
        judulSet.insert(film.judul);
        temp.push(film);
    }

    daftarFilm = temp;
    for (const auto& judul : judulSet) {
        queue<Film> temp2;
        while (!daftarFilm.empty()) {
            Film film = daftarFilm.front();
            daftarFilm.pop();
            if (film.judul == judul) {
                cout << "Judul: " << film.judul << "\nRating: " << fixed << setprecision(1) << film.rating << "\nFavorit: " << (film.favorit ? "Ya" : "Tidak") << "\n";
            }
            temp2.push(film);
        }
        daftarFilm = temp2;
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
        cout << "4. Tambah ke Favorit\n";
        cout << "5. Lihat Film Favorit\n";
        cout << "6. Edit Rating Film\n";
        cout << "7. Hapus Film Berdasarkan Judul\n";
        cout << "8. Urutkan Film Berdasarkan Judul\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: tambahFilm(daftarFilm); break;
            case 2: tampilkanFilm(daftarFilm); break;
            case 3: tambahKomentar(daftarFilm); break;
            case 4: tambahFavorit(daftarFilm); break;
            case 5: lihatFavorit(daftarFilm); break;
            case 6: editRating(daftarFilm); break;
            case 7: hapusFilm(daftarFilm); break;
            case 8: urutkanFilm(daftarFilm); break;
            case 0: cout << "Keluar dari program.\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 0);
    return 0;
}

