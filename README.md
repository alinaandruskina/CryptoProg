Задание 1
запуск:
make 
echo "Hello CryptoProg" > test.txt
./hash_program
sha512sum test.txt


Задание 2
запуск:
make
echo "Секретное сообщение для проверки AES-CBC">original.txt
./cripher_program
Режим 1:
original.txt
encrypted.bin
med228

Режим 2:
encrypted.bin
decrypted.txt
med228
