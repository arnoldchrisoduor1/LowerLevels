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