#include <windows.h>
#include <vector>
#include <iostream>
#include <string>

export module AddressOperator;

export
template <typename T>
class AddressOperator
{
private:
	uintptr_t* addr;
	std::vector<T> options;
	std::string name;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	int selected_option = 0;

	

public:
	//Constructor for static pointers or addresses without offsets
	AddressOperator(uintptr_t* addr, std::vector<T> options, std::string name) {
		this->addr = addr;
		this->options = options;
		this->name = name;

	}

	//General constructor for static opinters or addresses with offsets
	AddressOperator(uintptr_t* addr, std::vector<DWORD> offsets, std::vector<T> options, std::string name) {
		this->addr = this->findAddr(addr, offsets);
		this->options = options;
		this->name = name;

	}

	//Execute the classes task
	void execute() {
		if (selected_option != -1) *addr = options[selected_option];

	}

	//toggle next/prev option | true:next, false:prev
	void changeSelection(bool val) {
		switch (val) {
		case true:
			this->selected_option++;
			if (this->selected_option >= this->options.size()) 
				this->selected_option -= this->options.size();
			break;

		case false:
			this->selected_option--;
			if (this->selected_option < -1)
				this->selected_option += 1 + this->options.size();
			break;

		}

	}

	//Change the selected option (-1 to turn option off)
	void setOption(int option) {
		this->selected_option = option;

	}


	//Print the Object in a user-friendly way
	void print() {
		std::cout << "| " << this->name << " | <[";
		if (this->selected_option == -1) {
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
			std::cout << "OFF";

		}
		else {
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
			std::cout << this->options[this->selected_option];

		}
		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		std::cout << "]>" << std::endl;

	}

private:
	//find an address from another address with pointers
	uintptr_t* findAddr(uintptr_t* addr, std::vector<DWORD> offsets) {
		uintptr_t* addr_n = addr;
		for (int i = 0; i < offsets.size(); i++) {
			addr_n += *(DWORD*)addr_n;
			addr_n += offsets[i];
		
		}
		return addr_n;

	}
}; 

