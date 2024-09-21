#include <iostream>
#include <string>
using namespace std;

#define MAX_RESERVASI 100

// Struct untuk menyimpan data reservasi tamu hotel
struct Reservasi {
    int idReservasi;
    string namaTamu;
    string tipeKamar;
    int lamaMenginap;  // Lama menginap dalam hari
};

// Array untuk menyimpan daftar reservasi
Reservasi daftarReservasi[MAX_RESERVASI];
int jumlahReservasi = 0;

// Fungsi untuk menambah reservasi baru
void tambahReservasi() {
    if (jumlahReservasi < MAX_RESERVASI) {
        Reservasi* reservasiBaru = &daftarReservasi[jumlahReservasi];

        reservasiBaru->idReservasi = jumlahReservasi + 1; // ID otomatis
        cout << "Masukkan Nama Tamu: ";
        cin.ignore();
        getline(cin, reservasiBaru->namaTamu);
        cout << "Masukkan Tipe Kamar (Single/Double/Suite): ";
        getline(cin, reservasiBaru->tipeKamar);
        cout << "Masukkan Lama Menginap (hari): ";
        cin >> reservasiBaru->lamaMenginap;

        jumlahReservasi++;
        cout << "Reservasi berhasil ditambahkan!\n";
    } else {
        cout << "Kapasitas reservasi penuh!\n";
    }
}

// Fungsi untuk menampilkan semua reservasi
void tampilkanReservasi() {
    if (jumlahReservasi == 0) {
        cout << "Belum ada reservasi.\n";
        return;
    }

    cout << "Daftar Reservasi:\n";
    for (int i = 0; i < jumlahReservasi; i++) {
        cout << "ID Reservasi: " << daftarReservasi[i].idReservasi << "\n";
        cout << "Nama Tamu: " << daftarReservasi[i].namaTamu << "\n";
        cout << "Tipe Kamar: " << daftarReservasi[i].tipeKamar << "\n";
        cout << "Lama Menginap: " << daftarReservasi[i].lamaMenginap << " hari\n";
        cout << "-----------------------------\n";
    }
}

// Fungsi untuk memperbarui data reservasi berdasarkan ID
void updateReservasi() {
    int id;
    cout << "Masukkan ID Reservasi yang ingin diubah: ";
    cin >> id;

    if (id > 0 && id <= jumlahReservasi) {
        Reservasi* reservasi = &daftarReservasi[id - 1];
        cout << "Masukkan Nama Tamu Baru: ";
        cin.ignore();
        getline(cin, reservasi->namaTamu);
        cout << "Masukkan Tipe Kamar Baru (Single/Double/Suite): ";
        getline(cin, reservasi->tipeKamar);
        cout << "Masukkan Lama Menginap Baru (hari): ";
        cin >> reservasi->lamaMenginap;

        cout << "Reservasi berhasil diperbarui!\n";
    } else {
        cout << "ID Reservasi tidak ditemukan.\n";
    }
}

// Fungsi untuk menghapus reservasi berdasarkan ID
void hapusReservasi() {
    int id;
    cout << "Masukkan ID Reservasi yang ingin dihapus: ";
    cin >> id;

    if (id > 0 && id <= jumlahReservasi) {
        // Menggeser data setelah ID yang dihapus
        for (int i = id - 1; i < jumlahReservasi - 1; i++) {
            daftarReservasi[i] = daftarReservasi[i + 1];
        }
        jumlahReservasi--;

        cout << "Reservasi berhasil dihapus!\n";
    } else {
        cout << "ID Reservasi tidak ditemukan.\n";
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
        cout << "5. Keluar\n";
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
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 5);
}

// Fungsi utama
int main() {
    menu();
    return 0;
}
