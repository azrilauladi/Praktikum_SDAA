#include <iostream>
#include <string>
using namespace std;

// Struct untuk menyimpan data reservasi tamu hotel
struct Reservasi {
    int idReservasi;
    string namaTamu;
    string tipeKamar;
    int lamaMenginap;  // Lama menginap dalam hari
    Reservasi* next;  // Pointer to the next node in the linked list
};

// Node untuk menyimpan daftar reservasi
Reservasi* head = nullptr;
int jumlahReservasi = 0;

// Fungsi untuk menambah reservasi baru
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

    if (head == nullptr) {
        head = reservasiBaru;
    } else {
        Reservasi* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = reservasiBaru;
    }

    jumlahReservasi++;
    cout << "Reservasi berhasil ditambahkan!\n";
}

// Fungsi untuk menampilkan semua reservasi
void tampilkanReservasi() {
    if (head == nullptr) {
        cout << "Belum ada reservasi.\n";
        return;
    }

    cout << "Daftar Reservasi:\n";
    Reservasi* current = head;
    while (current != nullptr) {
        cout << "ID Reservasi: " << current->idReservasi << "\n";
        cout << "Nama Tamu: " << current->namaTamu << "\n";
        cout << "Tipe Kamar: " << current->tipeKamar << "\n";
        cout << "Lama Menginap: " << current->lamaMenginap << " hari\n";
        cout << "-----------------------------\n";
        current = current->next;
    }
}

// Fungsi untuk memperbarui data reservasi berdasarkan ID
void updateReservasi() {
    int id;
    cout << "Masukkan ID Reservasi yang ingin diubah: ";
    cin >> id;

    Reservasi* current = head;
    while (current != nullptr) {
        if (current->idReservasi == id) {
            cout << "Masukkan Nama Tamu Baru: ";
            cin.ignore();
            getline(cin, current->namaTamu);
            cout << "Masukkan Tipe Kamar Baru (Single/Double/Suite): ";
            getline(cin, current->tipeKamar);
            cout << "Masukkan Lama Menginap Baru (hari): ";
            cin >> current->lamaMenginap;

            cout << "Reservasi berhasil diperbarui!\n";
            return;
        }
        current = current->next;
    }

    cout << "ID Reservasi tidak ditemukan.\n";
}

// Fungsi untuk menghapus reservasi berdasarkan ID
void hapusReservasi() {
    int id;
    cout << "Masukkan ID Reservasi yang ingin dihapus: ";
    cin >> id;

    Reservasi* current = head;
    Reservasi* previous = nullptr;
    while (current != nullptr) {
        if (current->idReservasi == id) {
            if (previous == nullptr) {
                head = current->next;
            } else {
                previous->next = current->next;
            }
            delete current;
            jumlahReservasi--;

            cout << "Reservasi berhasil dihapus!\n";
            return;
        }
        previous = current;
        current = current->next;
    }

    cout << "ID Reservasi tidak ditemukan.\n";
}

void cariReservasi() {
    string nama;
    cout << "Masukkan nama penyewa yang ingin dicari: ";
    cin.ignore();
    getline(cin, nama);

    bool ditemukan = false;
    Reservasi* current = head;
    while (current != nullptr) {
        if (current->namaTamu.find(nama) != string::npos) {
            if (!ditemukan) {
                cout << "Hasil pencarian:\n";
                ditemukan = true;
            }
            cout << "ID Reservasi: " << current->idReservasi << "\n";
            cout << "Nama Tamu: " << current->namaTamu << "\n";
            cout << "Tipe Kamar: " << current->tipeKamar << "\n";
            cout << "Lama Menginap: " << current->lamaMenginap << " hari\n";
            cout << "-----------------------------\n";
        }
        current = current->next;
    }

    if (!ditemukan) {
        cout << "Tidak ada reservasi dengan nama penyewa tersebut.\n";
    }
}

// Menu utama sistem reservasi hotel
void menu() {
    int pilihan;
    do {
        cout << "\nSistem Reservasi Hotel\n";
        cout << "1. Tambah Reservasi\n";
        cout << "2. Tampilkan Semua Reservasi\n";
        cout << "3. Update Reservasi\n";
        cout << "4. Hapus Reservasi\n";
        cout << "5. Cari Reservasi\n";
        cout << "6. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahReservasi();
                break;
            case 2:
                tampilkanReservasi();
                break;
            case 3:
                updateReservasi();
                break;
            case 4:
                hapusReservasi();
                break;
            case 5:
                cariReservasi();
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