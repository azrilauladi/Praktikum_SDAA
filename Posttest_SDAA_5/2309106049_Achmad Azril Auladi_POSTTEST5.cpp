#include <iostream>
#include <string>
#include <vector>
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

// Quick Sort helper functions
int partition(vector<Reservasi*>& arr, int low, int high, bool ascending) {
    Reservasi* pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if ((ascending && arr[j]->idReservasi < pivot->idReservasi) || (!ascending && arr[j]->idReservasi > pivot->idReservasi)) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(vector<Reservasi*>& arr, int low, int high, bool ascending) {
    if (low < high) {
        int pi = partition(arr, low, high, ascending);
        quickSort(arr, low, pi - 1, ascending);
        quickSort(arr, pi + 1, high, ascending);
    }
}

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

    quickSort(reservasiList, 0, reservasiList.size() - 1, ascending);

    cout << "Daftar Reservasi di Stack (belum diproses):\n";
    for (auto& reservasi : reservasiList) {
        cout << "ID Reservasi: " << reservasi->idReservasi << "\n";
        cout << "Nama Tamu: " << reservasi->namaTamu << "\n";
        cout << "Tipe Kamar: " << reservasi->tipeKamar << "\n";
        cout << "Lama Menginap: " << reservasi->lamaMenginap << " hari\n";
        cout << "-----------------------------\n";
    }
}

// Shell Sort helper function
void shellSort(vector<Reservasi*>& arr, bool ascending) {
    int n = arr.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            Reservasi* temp = arr[i];
            int j;
            for (j = i; j >= gap && ((ascending && arr[j - gap]->idReservasi > temp->idReservasi) || (!ascending && arr[j - gap]->idReservasi < temp->idReservasi)); j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
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

    shellSort(reservasiList, ascending);

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
        cout << "6. Keluar\n";
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
            case 6:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 6);
}

// Fungsi utama
int main() {
    menu();
    return 0;
}
