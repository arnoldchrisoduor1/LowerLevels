#include <iostream>
#include <limits>
#include <iomanip>

#include "ConsoleInterface.h"

ConsoleInterface::ConsoleInterface() : tracker(std::make_unique<ExpenseTracker>()) {}

void ConsoleInterface::run() {
    std::cout << "=== Personal Expense Tracker ===" << std::endl;
    std::cout << "Welcome to your expense tracking application!" << std::endl << std::endl;

    int choice;
    do {
        showMenu();
        choice = getValidInteger("Enter your choice: ");

        try {
            switch(choice) {
                case 1: handleAddTransaction(); break;
                case 2: handleRemoveTransaction(); break;
                case 3: handleUpdateTransaction(); break;
                case 4: handleViewTransactions(); break;
                case 5: handleSortTransactions(); break;
                case 6: handleSearchTransactions(); break;
                case 7: handleViewAnalysis(); break;
                case 8: handleClearData(); break;
                case 0: std::cout << "Thank you for using Expense Tracker!" << std::endl;
                default: std::cout << "Invalid choice. Please try again." << std::endl;
            }
        } catch (const ExpenseTrackerException& e) {
            std::cout << "Error: " << e.what() << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Unexpected error: " << e.what() << std::endl;
        }

        if (choice != 0) {
            pressEnterToContinue();
        }
    } while (choice != 0);
}

void ConsoleInterface::showMenu() {
    clearScreen();
    std::cout << "\n=== EXPENSE TRACKER MENU ===" << std::endl;
    std::cout << "1. Add Transaction" << std::endl;
    std::cout << "2. Remove Transaction" << std::endl;
    std::cout << "3. Update Transaction" << std::endl;
    std::cout << "4. View All Transactions" << std::endl;
    std::cout << "5. Sort Transaction" << std::endl;
    std::cout << "6. Search Transactions" << std::endl;
    std::cout << "7. View Analysis" << std::endl;
    std::cout << "8. Clear All Data" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "======================" <<std::endl;
}

void ConsoleInterface::handleAddTransaction() {
    std::cout << "\n--- Add new Transaction ----" << std::endl;

    double amount = getValidAmount();
    std::string category = getValidString("Enter category: ");
    std::string description = getValidString("Enter description: ");

    Transaction transaction(amount, category, description);
    tracker->addTransaction(transaction);

    std::cout << "Transaction added successfully!" << std::endl;
    std::cout << "Added: " << transaction.toString() << std::endl;
}