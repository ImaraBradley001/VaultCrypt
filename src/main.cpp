#include <string>
#include <array>
#include <vector>
#include "additionalUtils.h"
#include "cryptographicUtils.h"
#include "consoleUI.h"
#include "help.h"
#include "progressBar.h"

using namespace CryptoPP;

int main(int argc, char** argv) {

    ConsoleUI ui;
    ui.operation = 0;
    ui.LoadInitialMenu();
    if (ui.operation == 3) {
        exit(1);
    }
    ui.LoadEnterPathScreen();
    ui.LoadCreatePasswordScreen();
    std::string DEFAULT_SALT = "abcdefghij123456";
    std::string DEFAULT_IV = "abcdefghij123456";
    SecByteBlock key = GenerateAESkey(ui.password, DEFAULT_SALT, 32);
    SecByteBlock iv = GenerateIV(DEFAULT_IV);
    std::cout << std::endl;
    std::cout << "Key:";
    PrintByteObject(key);
    std::cout << std::endl;
    std::vector<std::string> files = GenerateFileList(ui.path);
    if (ui.operation == 1) {
        for (auto& file : files) {
            std::cout << "Encrypting" << file << std::endl;
            // encrypt
            AesEncryptFile(key, iv, file);
        }
    }

    if (ui.operation == 2) {
        for (auto& file : files) {
            std::cout << "Decrypting" << file << std::endl;
            // encrypt
            AesDecryptFile(key, iv, file);
        }
    }
    
}
    

