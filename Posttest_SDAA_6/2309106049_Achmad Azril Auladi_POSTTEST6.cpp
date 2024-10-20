#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

// Struct untuk menyimpan data reservasi tamu hotel
struct Reservasi {
    int idReservasi;
    string namaTamu;
    string tipeKamar;
    int lamaMenginap;  // Lama menginap dalam hari
    Reservasi* next;  // Pointer to the next node
};

// Stack menggunakan pointer
Reservasi* top = nullptr;
int jumlahReservasi = 0;

// Queue menggunakan pointer
struct Queue {
    Reservasi* front = nullptr;
    Reservasi* rear = nullptr;
} antreanReservasi;

// Fungsi untuk menambah reservasi baru ke stack
void tambahReservasi() {
    Reservasi* reservasiBaru = new Reservasi();
    reservasiBaru->idReservasi = jumlahReservasi + 1; // ID otomatis
    cout << "Masukkan Nama Tamu: ";
    cin.ignore();
    getline(cin, reservasiBaru->namaTamu);
    cout << "Masukkan Tipe Kamar (Single/Double/Suite): ";
    getline(cin, reservasiBaru->tipeKamar);
    cout << "Masukkan Lama Menginap (hari): ";
    cin >> reservasiBaru->lamaMenginap;

    // Tambah reservasi ke stack (LIFO)
    reservasiBaru->next = top;
    top = reservasiBaru;

    jumlahReservasi++;
    cout << "Reservasi berhasil ditambahkan ke stack!\n";
}

// Fungsi untuk menampilkan semua reservasi dari stack
// Fungsi untuk menampilkan semua reservasi dari stack
void tampilkanReservasiStack() {
    if (top == nullptr) {
        cout << "Belum ada reservasi di stack.\n";
        return;
    }

    vector<Reservasi*> reservasiList;
    Reservasi* current = top;
    while (current != nullptr) {
        reservasiList.push_back(current);
        current = current->next;
    }

    int order;
    cout << "Pilih urutan tampilan (1. Ascending, 2. Descending): ";
    cin >> order;
    bool ascending = (order == 1);

    // Sorting logic here (omitted for brevity)

    cout << "Daftar Reservasi di Stack (belum diproses):\n";
    for (auto& reservasi : reservasiList) {
        cout << "ID Reservasi: " << reservasi->idReservasi << "\n";
        cout << "Nama Tamu: " << reservasi->namaTamu << "\n";
        cout << "Tipe Kamar: " << reservasi->tipeKamar << "\n";
        cout << "Lama Menginap: " << reservasi->lamaMenginap << " hari\n"; // Perbaikan di sini
        cout << "-----------------------------\n";
    }
}

// Fungsi untuk menampilkan semua reservasi di queue
void tampilkanReservasiQueue() {
    if (antreanReservasi.front == nullptr) {
        cout << "Antrean reservasi kosong.\n";
        return;
    }

    vector<Reservasi*> reservasiList;
    Reservasi* current = antreanReservasi.front;
    while (current != nullptr) {
        reservasiList.push_back(current);
        current = current->next;
    }

    int order;
    cout << "Pilih urutan tampilan (1. Ascending, 2. Descending): ";
    cin >> order;
    bool ascending = (order == 1);

    // Sorting logic here (omitted for brevity)

    cout << "Daftar Reservasi di Queue (antrean):\n";
    for (auto& reservasi : reservasiList) {
        cout << "ID Reservasi: " << reservasi->idReservasi << "\n";
        cout << "Nama Tamu: " << reservasi->namaTamu << "\n";
        cout << "Tipe Kamar: " << reservasi->tipeKamar << "\n";
        cout << "Lama Menginap: " << reservasi->lamaMenginap << " hari\n";
        cout << "-----------------------------\n";
    }
}

// Fungsi untuk memindahkan reservasi berdasarkan ID dari stack ke queue
void prosesKeQueue() {
    if (top == nullptr) {
        cout << "Tidak ada reservasi di stack untuk diproses ke queue.\n";
        return;
    }

    int id;
    cout << "Masukkan ID Reservasi yang ingin diproses ke queue: ";
    cin >> id;

    Reservasi* current = top;
    Reservasi* previous = nullptr;

    // Cari reservasi dengan ID yang dimasukkan
    while (current != nullptr && current->idReservasi != id) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) {
        cout << "ID Reservasi tidak ditemukan di stack.\n";
        return;
    }

    // Jika ditemukan, pindahkan dari stack ke queue
    if (previous == nullptr) {
        top = current->next;  // Jika item terletak di top
    } else {
        previous->next = current->next;  // Jika item ada di tengah atau akhir stack
    }

    // Tambahkan reservasi ke dalam antrean (queue)
    if (antreanReservasi.rear == nullptr) {
        antreanReservasi.front = current;
        antreanReservasi.rear = current;
    } else {
        antreanReservasi.rear->next = current;
        antreanReservasi.rear = current;
    }
    current->next = nullptr;  // Set null karena sudah pindah ke queue

    jumlahReservasi--;
    cout << "Reservasi dengan ID " << id << " berhasil dipindahkan ke queue.\n";
}

// Fungsi untuk menghapus reservasi paling depan dari queue
void hapusReservasiQueue() {
    if (antreanReservasi.front == nullptr) {
        cout << "Antrean reservasi kosong, tidak ada yang bisa dihapus.\n";
        return;
    }

    Reservasi* temp = antreanReservasi.front;
    antreanReservasi.front = antreanReservasi.front->next;

    if (antreanReservasi.front == nullptr) {
        antreanReservasi.rear = nullptr;
    }

    delete temp;
    cout << "Reservasi paling depan di queue berhasil dihapus.\n";
}

// Implementasi Fibonacci Search
int fibonacci_search(vector<int>& arr, int x) {
    int n = arr.size();
    int fibMMm2 = 0;  // (m-2)'th Fibonacci No.
    int fibMMm1 = 1;  // (m-1)'th Fibonacci No.
    int fibM = fibMMm2 + fibMMm1;  // m'th Fibonacci

    while (fibM < n) {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }

    int offset = -1;

    while (fibM > 1) {
        int i = min(offset + fibMMm2, n - 1);

        if (arr[i] < x) {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        } else if (arr[i] > x) {
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        } else {
            return i;
        }
    }

    if (fibMMm1 && arr[offset + 1] == x) {
        return offset + 1;
    }

    return -1;
}

// Implementasi Jump Search
int jump_search(vector<int>& arr, int x) {
    int n = arr.size();
    int step = sqrt(n);
    int prev = 0;

    while (arr[min(step, n) - 1] < x) {
        prev = step;
        step += sqrt(n);
        if (prev >= n) {
            return -1;
        }
    }

    while (arr[prev] < x) {
        prev++;
        if (prev == min(step, n)) {
            return -1;
        }
    }

    if (arr[prev] == x) {
        return prev;
    }

    return -1;
}

// Implementasi Boyer-Moore Search
vector<int> boyer_moore_search(string text, string pattern) {
    vector<int> result;
    int m = pattern.size();
    int n = text.size();

    if (m > n) {
        return result;
    }

    vector<int> badChar(256, -1);

    for (int i = 0; i < m; i++) {
        badChar[(int)pattern[i]] = i;
    }

    int s = 0;
    while (s <= (n - m)) {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[s + j]) {
            j--;
        }

        if (j < 0) {
            result.push_back(s);
            s += (s + m < n) ? m - badChar[text[s + m]] : 1;
        } else {
            s += max(1, j - badChar[text[s + j]]);
        }
    }

    return result;
}

// Menu utama sistem reservasi hotel
void menu() {
    int pilihan;
    do {
        cout << "\nSistem Reservasi Hotel (Stack & Queue)\n";
        cout << "1. Tambah Reservasi\n"; //stack
        cout << "2. Tampilkan Semua Reservasi\n"; //stack
        cout << "3. Proses Konfirmasi Reservasi \n"; //Stack ke Queue
        cout << "4. Tampilkan Semua Reservasi Terkonfirmasi\n"; //QUEUE 
        cout << "5. Hapus Reservasi\n"; //Queue (FIFO)
        cout << "6. Cari Reservasi\n"; // Search
        cout << "7. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahReservasi();
                break;
            case 2:
                tampilkanReservasiStack();
                break;
            case 3:
                prosesKeQueue();
                break;
            case 4:
                tampilkanReservasiQueue();
                break;
            case 5:
                hapusReservasiQueue();
                break;
            case 6: {
                int searchType;
                cout << "Pilih metode pencarian (1. Fibonacci, 2. Jump, 3. Boyer-Moore): ";
                cin >> searchType;

                if (searchType == 1 || searchType == 2) {
                    int id;
                    cout << "Masukkan ID Reservasi yang dicari: ";
                    cin >> id;

                    vector<int> ids;
                    Reservasi* current = antreanReservasi.front;
                    while (current != nullptr) {
                        ids.push_back(current->idReservasi);
                        current = current->next;
                    }

                    int index = (searchType == 1) ? fibonacci_search(ids, id) : jump_search(ids, id);
                    if (index != -1) {
                        cout << "Reservasi ditemukan dengan ID: " << id << "\n";
                    } else {
                        cout << "Data tidak ditemukan.\n";
                    }
                } else if (searchType == 3) {
                    string nama;
                    cout << "Masukkan Nama Tamu yang dicari: ";
                    cin.ignore();
                    getline(cin, nama);

                    string allNames;
                    Reservasi* current = antreanReservasi.front;
                    while (current != nullptr) {
                        allNames += current->namaTamu + " ";
                        current = current->next;
                    }

                    vector<int> positions = boyer_moore_search(allNames, nama);
                    if (!positions.empty()) {
                        cout << "Nama tamu ditemukan pada posisi: ";
                        for (int pos : positions) {
                            cout << pos << " ";
                        }
                        cout << "\n";
                    } else {
                        cout << "Data tidak ditemukan.\n";
                    }
                } else {
                    cout << "Metode pencarian tidak valid.\n";
                }
                break;
            }
            case 7:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 7);
}

// Fungsi utama
int main() {
    menu();
    return 0;
}