#include <iostream>
#include <string>
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
void tampilkanReservasiStack() {
    if (top == nullptr) {
        cout << "Belum ada reservasi di stack.\n";
        return;
    }

    cout << "Daftar Reservasi di Stack (belum diproses):\n";
    Reservasi* current = top;
    while (current != nullptr) {
        cout << "ID Reservasi: " << current->idReservasi << "\n";
        cout << "Nama Tamu: " << current->namaTamu << "\n";
        cout << "Tipe Kamar: " << current->tipeKamar << "\n";
        cout << "Lama Menginap: " << current->lamaMenginap << " hari\n";
        cout << "-----------------------------\n";
        current = current->next;
    }
}

// Fungsi untuk menambah reservasi dari stack ke queue (FIFO)
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

// Fungsi untuk menampilkan semua reservasi di queue
void tampilkanReservasiQueue() {
    if (antreanReservasi.front == nullptr) {
        cout << "Antrean reservasi kosong.\n";
        return;
    }

    cout << "Daftar Reservasi di Queue (antrean):\n";
    Reservasi* current = antreanReservasi.front;
    while (current != nullptr) {
        cout << "ID Reservasi: " << current->idReservasi << "\n";
        cout << "Nama Tamu: " << current->namaTamu << "\n";
        cout << "Tipe Kamar: " << current->tipeKamar << "\n";
        cout << "Lama Menginap: " << current->lamaMenginap << " hari\n";
        cout << "-----------------------------\n";
        current = current->next;
    }
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
