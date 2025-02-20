#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <limits>

// Class Error Handling
class BankingException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Banking exception occured.";
    }
    
};

class InsufficienFundsException : public BankingException {
public:
    const char* what() const noexcept override {
        return "Insufficient funds.";
    }
};

class InvalidAmountException : public BankingException {
public:
    const char* what() const noexcept override {
        return "Invalid amount. Must be greater than 0";
    }
};

// Banking System
class BankingSystem {
private:
    double balance;
    std::vector<std::string> transactionHistory;

public:
    BankingSystem() : balance(0.0) {}

    void deposit(double amount) {
        if (amount <= 0) {
            throw InvalidAmountException();
        }
        balance += amount;
        transactionHistory.push_back("Deposit: $" + std::to_string(amount));
        std::cout << "Successfully deposited $" << amount << ". New balance: $" << balance << std::endl;
    }

    void withdraw(double amount) {
        if (amount <= 0 ) {
            throw InvalidAmountException();
        }
        if (amount > balance) {
            throw InsufficienFundsException();
        }
        balance -= amount;
        transactionHistory.push_back("Withdrawal: $" + std::to_string(amount));
        std::cout << "Successfully withdrew $" << amount << ". New balance: $" << balance << std::endl;
    }

    double checkBalance() const {
        return balance;
    }

    void printTransactionHistory() const {
        std::cout << "Transaction History:\n";
        for (const auto& transaction : transactionHistory) {
            std::cout << transaction << "\n";
        }
    }
};

void clearInputBuffer() {
    std::cin.clear(); 
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    BankingSystem bankingSystem;
    int option;
    double amount;

    while (true) {
        std::cout << "=== Banking System ===\n";
        std::cout << "1. Deposit money\n";
        std::cout << "2. Withdraw money\n";
        std::cout << "3. Check balance\n";
        std::cout << "4. Show transaction history\n";
        std::cout << "5. Exit\n";
        std::cout << "Select an option: ";
        std::cin >> option;

        if (std::cin.fail()) {
            clearInputBuffer();
            std::cout << "Error: Invalid input. Enter a numeric value.\n";
            continue;
        }

        switch (option) {
            case 1:
                std::cout << "Enter amount to deposit: ";
                std::cin >> amount;
                try {
                    bankingSystem.deposit(amount);
                } catch (const BankingException& e) {
                    std::cout << "Error: " << e.what() << "\n";
                }
                break;

                case 2:
                std::cout << "Enter amount to withdraw: ";
                std::cin >> amount;
                try {
                    bankingSystem.withdraw(amount);
                } catch (const BankingException& e) {
                    std::cout << "Error: " << e.what() << "\n";
                }
                break;

            case 3:
                std::cout << "Current balance: $" << bankingSystem.checkBalance() << "\n";
                break;

            case 4:
                bankingSystem.printTransactionHistory();
                break;

            case 5:
                std::cout << "Exiting the banking system. Goodbye!\n";
                return 0;

            default:
                std::cout << "Error: Invalid option! Please select a valid option.\n";
        }
    }

    return 0;
}

