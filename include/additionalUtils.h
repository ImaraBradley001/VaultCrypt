#pragma once 

#include <array>
#include <vector>
#include <string>
#include "cryptlib.h"
#include "rijndael.h"
#include "hex.h"
#include "filesystem"

using namespace CryptoPP;

std::string ExecuteCommand(const char* cmd);
std::vector<std::string> GenerateFileList(const std::filesystem::path& path);
void PrintByteObject(SecByteBlock obj);