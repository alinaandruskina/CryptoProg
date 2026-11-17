#include <iostream>
#include <fstream>
#include <string>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <cryptopp/osrng.h>
#include <cryptopp/sha.h>
#include <cryptopp/files.h>
#include <cryptopp/hex.h>

using namespace std;
using namespace CryptoPP;

// Получение 32-байтного ключа из пароля через SHA-256
SecByteBlock deriveKey(const string& password) {
    SecByteBlock key(AES::MAX_KEYLENGTH);
    SHA256 hash;
    hash.CalculateDigest(key, reinterpret_cast<const unsigned char*>(password.data()),password.size());
    return key;
}

int main() {
    int mode;
    string inFile, outFile, password;

    cout << "Выберите режим (1 - шифрование, 2 - расшифрование): ";
    cin >> mode;
    cout << "Введите файл с исходными данными: ";
    cin >> inFile;
    cout << "Введите файл для записи результата: ";
    cin >> outFile;
    cout << "Введите пароль: ";
    cin >> password;

    SecByteBlock key = deriveKey(password);

    try {
        if (mode == 1) {
            // Шифрование
            AutoSeededRandomPool prng;
            SecByteBlock iv(AES::BLOCKSIZE);
            prng.GenerateBlock(iv, iv.size());

            CBC_Mode<AES>::Encryption enc;
            enc.SetKeyWithIV(key, key.size(), iv);

            // Сохраняем IV в начало файла
            ofstream out(outFile, ios::binary);
            out.write((char*)iv.data(), iv.size());

            FileSource fs(inFile.c_str(), true,
                new StreamTransformationFilter(enc,
                    new FileSink(out)
                )
            );
            out.close();
            cout << "Файл успешно зашифрован.\n";
        } else if (mode == 2) {
            // Расшифрование
            ifstream in(inFile, ios::binary);
            SecByteBlock iv(AES::BLOCKSIZE);
            in.read((char*)iv.data(), iv.size());

            CBC_Mode<AES>::Decryption dec;
            dec.SetKeyWithIV(key, key.size(), iv);

            FileSource fs(in, true,
                new StreamTransformationFilter(dec,
                    new FileSink(outFile.c_str())
                )
            );
            in.close();
            cout << "Файл успешно расшифрован.\n";
        } else {
            cerr << "Неверный режим.\n";
            return 1;
        }
    } catch (const Exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }
    return 0;
}
