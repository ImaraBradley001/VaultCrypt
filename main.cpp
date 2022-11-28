#include "files.h"
#include "modes.h"
#include "osrng.h"
#include <array>
#include <fstream>
#include <iostream>
#include "cryptlib.h"
#include "rijndael.h"
#include "modes.h"
#include "files.h"
#include "osrng.h"
#include "hex.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <typeinfo>
#include <fstream>
#include <sys/stat.h>


using aes_key_t = std::array<CryptoPP::byte, CryptoPP::AES::DEFAULT_KEYLENGTH>;
using aes_iv_t = std::array<CryptoPP::byte, CryptoPP::AES::BLOCKSIZE>;

void encrypt(const aes_key_t& key, const aes_iv_t& iv,
    const std::string& filename_in, const std::string& filename_out) {
    CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption cipher{};
    cipher.SetKeyWithIV(key.data(), key.size(), iv.data());

    std::ifstream in{ filename_in, std::ios::binary };
    std::ofstream out{ filename_out, std::ios::binary };

    CryptoPP::FileSource{ in, /*pumpAll=*/true,
                         new CryptoPP::StreamTransformationFilter{
                             cipher, new CryptoPP::FileSink{out}} };
    out.close();
    in.close();
}

void decrypt(const aes_key_t& key, const aes_iv_t& iv,
    const std::string& filename_in, const std::string& filename_out) {
    CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption cipher{};
    cipher.SetKeyWithIV(key.data(), key.size(), iv.data());

    std::ifstream in{ filename_in, std::ios::binary };
    std::ofstream out{ filename_out, std::ios::binary };

    CryptoPP::FileSource{ in, /*pumpAll=*/true,
                         new CryptoPP::StreamTransformationFilter{
                             cipher, new CryptoPP::FileSink{out}} };
    out.close();
    in.close();
}

int main(int argc, char** argv) {

    std::cout << CryptoPP::AES::BLOCKSIZE << std::endl;

    CryptoPP::AutoSeededRandomPool rng{};

    // Generate a random key
    aes_key_t key{};
    rng.GenerateBlock(key.data(), key.size());

    // Generate a random IV
    aes_iv_t iv{};
    rng.GenerateBlock(iv.data(), iv.size());

    // encrypt
    encrypt(key, iv, "C:\\users\\2022\\desktop\\test.jpg", "C:\\users\\2022\\desktop\\test_encrypted.jpg");
    
    //overwrite and rename files
    std::ofstream out{ "C:\\users\\2022\\desktop\\test.jpg", std::ios::binary};
    out.close();
    system("del /f /q C:\\users\\2022\\desktop\\test.jpg && ren C:\\users\\2022\\desktop\\test_encrypted.jpg test.jpg");
    
    int x;
    std::cin >> x;

    // decrypt
    decrypt(key, iv, "C:\\users\\2022\\desktop\\test.jpg", "C:\\users\\2022\\desktop\\test_decrypted.jpg");

    //overwrite and rename files
    std::ofstream out2{ "C:\\users\\2022\\desktop\\test.jpg", std::ios::binary };
    out2.close();
    system("del /f /q C:\\users\\2022\\desktop\\test.jpg && ren C:\\users\\2022\\desktop\\test_decrypted.jpg test.jpg");

    return 0;
}
