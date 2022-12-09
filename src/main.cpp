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
    std::vector<std::string> files = GenerateFileList(ui.path);
    system("cls");
    std::string ProgressBarSign = "#";
    showcursor(FALSE);
    changeColor(15);
    std::cout << "Progress:";
    gotoxy(100, 1);
    std::cout << "| Encrypting/Decrypting... (****)";
    gotoxy(2, 1);
    changeColor(119);
    int total = files.size();
    int increment = round(1.0 / 100.0 * total);
    if (increment == 0) {
        increment = 1;
    }
    if (ui.operation == 1) {
        for (int i = 0; i < total; i++) {
            AesEncryptFile(key, iv, files[i]);
            if (i % increment == 0) {
                Sleep(25);
                std::cout << ProgressBarSign;
            }
        }
    }

    if (ui.operation == 2) {
        for (int i = 0; i < total; i++) {
            AesDecryptFile(key, iv, files[i]);
            if (i % increment == 0) {
                Sleep(25);
                std::cout << ProgressBarSign;
            }
        }
    }
    system("cls");
    gotoxy(0, 0);
    std::cout << "\n\nEncrypting/Decrypting... (!DONE!)\n\n";
    showcursor(TRUE); 
}
    

