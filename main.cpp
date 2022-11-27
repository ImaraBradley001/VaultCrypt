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

using namespace CryptoPP;

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

std::string encrytPlainText(char * &plainText, SecByteBlock key, SecByteBlock iv) {
    std::string cipherText;
    for (int i = 0; i < 100000000; i++) std::cout << plainText[i] << std::endl;

    try
    {
        CBC_Mode< AES >::Encryption e;
        e.SetKeyWithIV(key, key.size(), iv);

        StringSource s(plainText, true,
           new StreamTransformationFilter(e,
                new StringSink(cipherText)
            ) // StreamTransformationFilter
        ); // StringSource
        return cipherText;
    }
    catch (const Exception& e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
}

std::string decrytCipherText(std::string cipherText, SecByteBlock key, SecByteBlock salt) {
    std::string plainText;


    try
    {
        CBC_Mode< AES >::Decryption d;
        d.SetKeyWithIV(key, key.size(), salt);

        StringSource s(cipherText, true,
            new StreamTransformationFilter(d,
                new StringSink(plainText),
                CryptoPP::BlockPaddingSchemeDef::BlockPaddingScheme::PKCS_PADDING
            ) // StreamTransformationFilter
        ); // StringSource
       // std::cout << typeid(plainText) << std::endl;

        return plainText;
    }
    catch (const Exception& e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << "decryption failed" << std::endl;
        exit(1);
    }
}

int getFileSize(std::string filename) {
    struct stat results;

    if (stat(filename.c_str(), &results) == 0)
        // The size of the file in bytes is in
        return results.st_size;
    else {
        // An error occurred
        return 0;
    }
}
char * readFileData(std::string filename, int filesize) {
    char* fileData = new char[filesize];
    std::ifstream f(filename, std::fstream::binary);
    if (f) {
        f.read(fileData, filesize);
        return fileData;
    }
}

int main(int argc, char * argv[]) {
    /*
    std::string password = argv[1], salt = argv[2];
    HexEncoder encoder(new FileSink(std::cout));
    SecByteBlock key = generateKey(password, salt);
    SecByteBlock iv = generateByteBlock("hoesinthesouth02");
    std::string plainText = "An encryption algo", cipherText = encrytPlainText(plainText, key, iv);
    std::string decryptedCipherText = decrytCipherText(cipherText, key, iv);
    bool decryptionWasSuccessful = decryptedCipherText == plainText;
    std::cout << "Key:";
    encoder.Put(key, key.size());
    std::cout << std::endl;
    std::cout << "Iv:";
    encoder.Put(iv, iv.size());
    std::cout << std::endl;
    std::cout << "Plain Text: " << plainText << ":" << std::endl;
    std::cout << "Cipher Text: " << cipherText << std::endl;
    std::cout << "Decryption was successful: " << std::boolalpha << decryptionWasSuccessful << std::endl;
    */
    std::string filename = argv[1];
    int filesize = getFileSize(filename);
    char* data = readFileData(filename, filesize);
    SecByteBlock key = generateRandomKey(), iv=generateByteBlock("Helloworld123456");
    //std::cout << encrytPlainText(data, key, iv);
    //for (int i = 0; i < filesize; i++) std::cout << data[i] << std::endl;
}