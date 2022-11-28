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


int getFileSize(std::string filename) {
    struct stat results;

    if (stat(filename.c_str(), &results) == 0) return results.st_size;
    return 0;
}
char* readFileData(std::string filename, int filesize) {
    char* fileData = new char[filesize];
    std::ifstream f(filename, std::fstream::binary);
    if (f) {
        f.read(fileData, filesize);
        return fileData;
    }
}

void encrypt(const aes_key_t& key, const aes_iv_t& iv,
    const std::string& filename) {
    CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption cipher{};
    cipher.SetKeyWithIV(key.data(), key.size(), iv.data());
    int filesize = getFileSize(filename);
    std::cout << "FILESIZE:" << filesize << std::endl;
    char* filedata = readFileData(filename, filesize);

    //std::ifstream in{ filename_in, std::ios::binary };
    std::ofstream out{ filename, std::ios::binary };

    CryptoPP::ArraySource{ filedata, /*pumpAll=*/true,
                         new CryptoPP::StreamTransformationFilter{
                             cipher, new CryptoPP::FileSink{out}} };
    out.close();
}

void decrypt(const aes_key_t& key, const aes_iv_t& iv,
    const std::string& filename) {
    CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption cipher{};
    cipher.SetKeyWithIV(key.data(), key.size(), iv.data());
    int filesize = getFileSize(filename);
    std::cout << "FILESIZE:" << filesize << std::endl;
    char* filedata = readFileData(filename, filesize);

    //std::ifstream in{ filename_in, std::ios::binary };
    std::ofstream out{ filename, std::ios::binary };

    CryptoPP::ArraySource{ filedata, /*pumpAll=*/true,
                         new CryptoPP::StreamTransformationFilter{
                             cipher, new CryptoPP::FileSink{out}} };
    out.close();
}



int main(int argc, char** argv) {

    //std::cout << CryptoPP::AES::BLOCKSIZE << std::endl;

    std::string filename = argv[1];

    CryptoPP::AutoSeededRandomPool rng{};

    // Generate a random key
    aes_key_t key{};
    rng.GenerateBlock(key.data(), key.size());

    // Generate a random IV
    aes_iv_t iv{};
    rng.GenerateBlock(iv.data(), iv.size());

    // encrypt
    encrypt(key, iv, filename);
    // decrypt
    decrypt(key, iv, filename);


    return 0;
}
