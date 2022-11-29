#include <string>
#include <stdexcept>
#include <memory>
#include <array>
#include <vector>
#include "cryptlib.h"
#include "rijndael.h"
#include "hex.h"
#include "files.h"
#include <filesystem>
#include "additionalUtils.h"

using namespace CryptoPP;


std::string ExecuteCommand(const char* cmd) {
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


std::vector<std::string> GenerateFileList(const std::filesystem::path& path) {
    std::vector<std::string> allfiles;
    for (const auto& p : std::filesystem::recursive_directory_iterator(path)) {
        if (!std::filesystem::is_directory(p)) {
            allfiles.push_back(p.path().u8string());
        }
    }
    return allfiles;
}

void PrintByteObject(SecByteBlock obj) {
    HexEncoder encoder(new FileSink(std::cout));
    encoder.Put(obj, obj.size());
}
