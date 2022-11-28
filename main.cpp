#include "files.h"
#include "modes.h"
#include "osrng.h"
#include <array>
#include <fstream>
#include <iostream>
#include "cryptlib.h"
#include "rijndael.h"
#include "osrng.h"
#include "hex.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <sys/stat.h>
#include <filesystem>
#include <vector>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

namespace fs = std::filesystem;

using namespace CryptoPP;
using aes_key_t = std::array<CryptoPP::byte, CryptoPP::AES::DEFAULT_KEYLENGTH>;
using aes_iv_t = std::array<CryptoPP::byte, CryptoPP::AES::BLOCKSIZE>;

SecByteBlock generateRandomKey(int size = 32) {
    AutoSeededRandomPool prng;
    SecByteBlock key(size);
    prng.GenerateBlock(key, key.size());
    return key;
}

SecByteBlock generateRandomSalt(int length = 32) {
    AutoSeededRandomPool prng;
    SecByteBlock salt(length);
    prng.GenerateBlock(salt, salt.size());
    return salt;
}

SecByteBlock generateKey(std::string password, std::string salt) {
    SecByteBlock key(32);
    HKDF<SHA256> hkdf;
    hkdf.DeriveKey(key, key.size(), (const byte*)password.data(), password.size(), (const byte*)salt.data(), salt.size(), NULL, 0);
    return key;
}

SecByteBlock generateByteBlock(std::string in_string) {
    std::string s1(in_string);
    SecByteBlock byteblock((const byte*)s1.data(), s1.size());
    return byteblock;
}

void encrypt(SecByteBlock key, SecByteBlock iv,
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

void decrypt(SecByteBlock key, SecByteBlock iv,
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

std::vector<std::string> generate_file_list(const std::filesystem::path& path) {
    std::vector<std::string> allfiles;
    for (const auto& p : std::filesystem::recursive_directory_iterator(path)) {
        if (!std::filesystem::is_directory(p)) {
            allfiles.push_back(p.path().u8string());
        }
    }
    return allfiles;
}

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd, "r"), _pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}


int main(int argc, char** argv) {

    //std::cout << CryptoPP::AES::BLOCKSIZE << std::endl;


    std::string filepath = argv[1];

    std::string base_filepath = filepath.substr(filepath.find_last_of("/\\") + 1);

    SecByteBlock key = generateKey("hello", "hello");
    SecByteBlock iv = generateByteBlock("1234567890abcdef");

    HexEncoder encoder(new FileSink(std::cout));
    std::cout << "Key:";
    encoder.Put(key, key.size());
    std::cout << std::endl;
    std::cout << "Iv:";
    encoder.Put(iv, iv.size());
    std::cout << std::endl;
    SecByteBlock key = generateKey("hello", "hello");
    SecByteBlock iv = generateByteBlock("1234567890abcdef");
    // encrypt
    encrypt(key, iv, filepath, filepath+"_encrypted");    
    //overwrite and rename files
    std::ofstream out{ filepath, std::ios::binary};
    out.close();
    std::string command;
    command += "del /f /q " + filepath + " &&  ren " + filepath + "_encrypted " + base_filepath;
    exec(command.c_str());
    command = "";
    // decrypt
    decrypt(key, iv, filepath, filepath + "_decrypted");
    //overwrite and rename files
    std::ofstream out2{ filepath, std::ios::binary };
    out2.close();
    command += "del /f /q " + filepath + " &&  ren " + filepath + "_decrypted " + base_filepath;
    exec(command.c_str());
    return 0;
    system(command.c_str());
    return 0;

    /*
    std::vector<std::string> files = generate_file_list("./");
    for (auto& f : files) {
        std::cout << f << std::endl;
    }*/
    
}
    

