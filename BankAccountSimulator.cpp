#include <iostream>
#include <stdio.h>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <string>

using namespace std;

class BankAccount {

public:
	string accountName;
	int accountBalance;

	BankAccount(string accountName, int accountBalance) {
		this->accountName = accountName;
		this->accountBalance = accountBalance;
	}

	void withdrawMoney(int amount) {
		if (amount >= accountBalance)
			amount = accountBalance;

		accountBalance -= amount;
	}

	void depositMoney(int amount) {
		accountBalance += amount;
	}

};

BankAccount loadAccount(string accountName) {
	ifstream file(accountName + ".txt");
	string opt;

	string actName;
	int actBal = 0;

	if (file.is_open()) {

		getline(file, opt);
		actName = opt;
		getline(file, opt);
		actBal = stoi(opt);

		file.close();
	}

	return BankAccount(actName, actBal);
}

void saveAccount(BankAccount account) {
	ofstream file(account.accountName + ".txt");

	if (file.is_open()) {

		file << account.accountName << endl;
		file << account.accountBalance << endl;
			
		file.close();
	}
}

// Stolen from Google lmao, Why doesn't C++ have an easy String.toLowerCase() lol
std::string toLowerCase(const std::string& str) {
	std::string lowerStr = str;
	std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
		[](unsigned char c) { return std::tolower(c); });
	return lowerStr;
}

int main() {
	bool run = true;
	BankAccount currentAccount = BankAccount("", 0);
	
	while (run) {
		string answer;

		if (currentAccount.accountName == "") {
			cout << "Welcome to Spire Banking\n";
			cout << "Are you returning (return) or new (new)?\n";

			cin >> answer;

			if (toLowerCase(answer) == "return") {
				
				cout << "What's your name?\n";

				cin >> answer;

				currentAccount = loadAccount(answer);

			}
			else if (toLowerCase(answer) == "new") {
				cout << "What's your name?\n";

				cin >> answer;

				currentAccount = BankAccount(answer, 1000);
				saveAccount(currentAccount);
			}

		}
		else {
			cout << "Welcome to Spire Banking " << currentAccount.accountName << "!\n";
			cout << "Your current balance is: " << currentAccount.accountBalance << "\n";
			cout << "What would you like to do?\nWithdraw (W)\nDeposit (D)\nExit(Q)\n";

			cin >> answer;

			if (toLowerCase(answer) == "w") {
				cout << "How much would you like to withdraw? MAX = " << currentAccount.accountBalance << endl;

				cin >> answer;
				currentAccount.withdrawMoney(stoi(answer));
			}
			else if (toLowerCase(answer) == "d") {
				cout << "How much would you like to deposit?" << endl;

				cin >> answer;
				currentAccount.depositMoney(stoi(answer));
			}
			else if (toLowerCase(answer) == "q") {
				saveAccount(currentAccount);
				run = false;
			}

		}

	}


	return 0;
}
