#include "cryptographicUtils.h"
#include "cryptlib.h"
#include "rijndael.h"
#include <string>
#include <iostream>
#include "files.h"
#include "modes.h"
#include "osrng.h"
#include "additionalUtils.h"

using namespace CryptoPP;

SecByteBlock GenerateRandomAESkey(int size) {
    AutoSeededRandomPool prng;
    SecByteBlock key(size);
    prng.GenerateBlock(key, key.size());
    return key;
}

SecByteBlock GenerateRandomSalt(int length) {
    AutoSeededRandomPool prng;
    SecByteBlock salt(length);
    prng.GenerateBlock(salt, salt.size());
    return salt;
}

SecByteBlock GenerateAESkey(std::string password, std::string salt, int length) {
    SecByteBlock key(32);
    HKDF<SHA256> hkdf;
    hkdf.DeriveKey(key, key.size(), (const byte*)password.data(), password.size(), (const byte*)salt.data(), salt.size(), NULL, 0);
    return key;
}

SecByteBlock GenerateIV(std::string in_string) {
    std::string s1(in_string);
    SecByteBlock byteblock((const byte*)s1.data(), s1.size());
    return byteblock;
}

void AesEncryptFile(SecByteBlock key, SecByteBlock iv, const std::string& filepath_in) {
    std::string base_filepath = filepath_in.substr(filepath_in.find_last_of("/\\") + 1);
    std::string filepath_out = filepath_in + "_encrypted";
    CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption cipher{};
    cipher.SetKeyWithIV(key.data(), key.size(), iv.data());
    std::ifstream in{ filepath_in, std::ios::binary };
    std::ofstream out{ filepath_out, std::ios::binary };
    CryptoPP::FileSource{ in, true, new CryptoPP::StreamTransformationFilter{cipher, new CryptoPP::FileSink{out}} };
    out.close();
    in.close();
    std::string command;
    command += "del /f /q " + filepath_in + " &&  ren " + filepath_out + " " + base_filepath;
    ExecuteCommand(command.c_str());
}

void AesDecryptFile(SecByteBlock key, SecByteBlock iv, const std::string& filepath_in) {
    std::string base_filepath = filepath_in.substr(filepath_in.find_last_of("/\\") + 1);
    std::string filepath_out = filepath_in + "_decrypted";
    CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption cipher{};
    cipher.SetKeyWithIV(key.data(), key.size(), iv.data());
    std::ifstream in{ filepath_in, std::ios::binary };
    std::ofstream out{ filepath_out, std::ios::binary };
    CryptoPP::FileSource{ in, true, new CryptoPP::StreamTransformationFilter{cipher, new CryptoPP::FileSink{out}} };
    out.close();
    in.close();
    std::string command;
    command += "del /f /q " + filepath_in + " &&  ren " + filepath_out + " " + base_filepath;
    ExecuteCommand(command.c_str());
}