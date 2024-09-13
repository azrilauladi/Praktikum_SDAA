#include <iostream>

/* Fungsi rekursif untuk menyelesaikan masalah Menara Hanoi
n: jumlah piringan yang harus dipindahkan
asal: tiang asal tempat piringan berada
tujuan: tiang tujuan tempat piringan akan dipindahkan
sementara: tiang sementara yang digunakan dalam proses pemindahan */
void menaraHanoi(int n, char asal, char tujuan, char sementara) {

    // Jika hanya ada satu piringan, langsung pindahkan dari tiang asal ke tiang tujuan
    if (n == 1) {
        std::cout << "Pindahkan piringan 1 dari " << asal << " ke " << tujuan << std::endl;
        return;
    }

    // Memanggil fungsi rekursif untuk memindahkan n-1 piringan dari tiang asal ke tiang sementara
    menaraHanoi(n - 1, asal, sementara, tujuan);

    // Memindahkan piringan ke-n dari tiang asal ke tiang tujuan
    std::cout << "Pindahkan piringan " << n << " dari " << asal << " ke " << tujuan << std::endl;

    // Memanggil fungsi rekursif lagi untuk memindahkan n-1 piringan dari tiang sementara ke tiang tujuan
    menaraHanoi(n - 1, sementara, tujuan, asal);
}

int main() {
    int n = 3; // Jumlah piringan

    // Panggil fungsi menaraHanoi untuk memindahkan n piringan dari tiang 'A' ke tiang 'C' dengan bantuan tiang 'B'
    menaraHanoi(n, 'A', 'C', 'B');
    return 0;
}