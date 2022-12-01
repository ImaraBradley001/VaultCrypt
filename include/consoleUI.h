#pragma once

class ConsoleUI {
public:
	std::string password;
	std::string password_confirmation;
	std::string path;
	int operation;
	void LoadInitialMenu();
	void LoadCreatePasswordScreen();
	void LoadEnterPasswordScreen();
	void LoadEnterPathScreen();
};
