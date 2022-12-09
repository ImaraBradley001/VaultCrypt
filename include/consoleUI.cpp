#include <iostream>
#include "consoleUI.h"
#include <string.h>
#include <limits>

void ConsoleUI::LoadInitialMenu() {
		system("cls");
		std::cout << "Welcome to the user menu";
		std::cout << "Choose an operation.\n1. Encrypt\n2. Decrypt\n3. Exit\n>>";
		std::cin >> operation;
}

void ConsoleUI::LoadCreatePasswordScreen() {
		system("cls");
		do {
			std::cout << "Enter your password:";
			std::cin >> password;
			std::cout << "Confirm your password:";
			std::cin >> password_confirmation;
			if (password != password_confirmation) {
				std::cout << "The passwords entered do not match\n";
			}
		} while (password != password_confirmation);
	}

void ConsoleUI::LoadEnterPasswordScreen() {
		system("cls");
		std::cout << "Enter your password:";
		std::cin >> password;
	}

void ConsoleUI::LoadEnterPathScreen() {
		system("cls");
		std::cout << "Enter the path to recursively encrypt/decrypt:";
		std::cin >> path;
	}
