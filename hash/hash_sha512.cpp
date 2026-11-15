#include <iostream>
#include <fstream>
#include <string>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>

using namespace std;
using namespace CryptoPP;

int main() {
    string filename;
    cout << "Введите имя файла для хэширования: ";
    cin >> filename;

    SHA512 hash;
    string digest;

    try {
        FileSource fs(filename.c_str(), true,
            new HashFilter(hash,
                new HexEncoder(
                    new StringSink(digest), true
                )
            )
        );
    } catch (const Exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }

    cout << "\nSHA-512 хеш файла '" << filename << "':\n";
    cout << digest << "\n\n";
    cout << "Информация:\n";
    cout << "Длина хеша: " << digest.length() << " символов\n";
    cout << "Размер блока: " << SHA512::BLOCKSIZE << " байт\n";
    cout << "Размер дайджеста: " << SHA512::DIGESTSIZE << " байт\n";

    return 0;
}
