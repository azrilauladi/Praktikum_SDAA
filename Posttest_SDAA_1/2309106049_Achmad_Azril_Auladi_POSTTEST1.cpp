#include <iostream>

void menaraHanoi(int n, char asal, char tujuan, char sementara) {
    if (n == 1) {
        std::cout << "Pindahkan piringan 1 dari " << asal << " ke " << tujuan << std::endl;
        return;
    }
    menaraHanoi(n - 1, asal, sementara, tujuan);
    std::cout << "Pindahkan piringan " << n << " dari " << asal << " ke " << tujuan << std::endl;
    menaraHanoi(n - 1, sementara, tujuan, asal);
}

int main() {
    int n = 3; // Jumlah piringan
    menaraHanoi(n, 'A', 'C', 'B');
    return 0;
}