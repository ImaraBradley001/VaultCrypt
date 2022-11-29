#include <string>
#include <array>
#include <vector>
#include "additionalUtils.h"
#include "cryptographicUtils.h"

namespace fs = std::filesystem;

using namespace CryptoPP;

int main(int argc, char** argv) {

    //std::cout << CryptoPP::AES::BLOCKSIZE << std::endl;

    std::string filepath = argv[1];

    SecByteBlock key = GenerateAESkey("hello", "hello", 32);
    SecByteBlock iv = GenerateIV("0000000000000000");
    std::cout << "Key:";
    PrintByteObject(key);
    std::cout << std::endl;
    std::cout << "Iv:";
    PrintByteObject(iv);
    std::cout << std::endl;
    // encrypt
    AesEncryptFile(key, iv, filepath);
    // decrypt
    AesDecryptFile(key, iv, filepath);
       
}
    

