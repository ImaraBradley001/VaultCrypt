#pragma once

#include "cryptlib.h"
#include "rijndael.h"
#include <string>
#include <iostream>

using namespace CryptoPP;

SecByteBlock GenerateAESkey(std::string password, std::string salt, int size);
SecByteBlock GenerateRandomAESkey(int size);
SecByteBlock GenerateRandomSalt(int length);
SecByteBlock GenerateIV(std::string in_string);
void AesEncryptFile(SecByteBlock key, SecByteBlock iv, const std::string& filepath_in);
void AesDecryptFile(SecByteBlock key, SecByteBlock iv, const std::string& filepath_in);