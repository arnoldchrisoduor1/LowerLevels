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

    double amount = getValidAmount("Enter amount: ");
    std::string category = getValidString("Enter category: ");
    std::string description = getValidString("Enter description: ");

    Transaction transaction(amount, category, description);
    tracker->addTransaction(transaction);

    std::cout << "Transaction added successfully!" << std::endl;
    std::cout << "Added: " << transaction.toString() << std::endl;
}

void ConsoleInterface::handleRemoveTransaction() {
    if (tracker->getTransactionCount() == 0) {
        std::cout << "No transactions to remove." << std::endl;
        return;
    }

    std::cout << "\n--- Remove Transaction ---" << std::endl;
    handleViewTransactions();

    int id = getValidInteger("Enter transaction ID to remove: ");
    tracker->removeTransaction(id);
    std::cout << "Transaction removed succesfully!" <<std::endl;
}

void ConsoleInterface::handleUpdateTransaction() {
    if (tracker->getTransactionCount() == 0) {
        std::cout << "No transaction to update" << std::endl;
        return;
    }

    std::cout << "\n--- Update Transaction ---" << std::endl;
    handleViewTransactions();

    int id = getValidInteger("Enter transaction ID to update:");

    Transaction* existing = tracker->findTransactionById(id);
    if (!existing) {
        throw ExpenseTrackerException("Transaction not found");
    }

    std::cout << 'Current transaction: ' << existing->toString() << std::endl;

    double amount = getValidAmount("Enter amount: ");
    std::string category = getValidString("Enter new category: ");
    std::string description = getValidString("Enter new description: ");

    tracker->updateTransaction(id, amount, category, description);
    std::cout << "Transaction updates sucessfully!" << std::endl;
}

void ConsoleInterface::handleViewTransactions() {
    std::cout << "\n--- All Transactions ---" << std::endl;

    const auto& transactions = tracker->getTransactions();
    if (transactions.empty()) {
        std::cout << "No transactions found." << std::endl;
        return;
    }

    std::cout << "Total transactions: " << transactions.size() << std::endl;
    std::cout << "Total amount: $" << std::fixed << std::setprecision(2) <<tracker->getTotalExpenses() << std::endl << std::endl;

    for (const auto& transaction : transactions) {
        std::cout << transaction.toString() << std::endl;
    }
}

void ConsoleInterface::handleSortTransactions() {
    if (tracker->getTransactionCount() == 0) {
        std::cout << "No transactions to sort." << std::endl;
        return;
    }

    std::cout << "\n--- Sort Transactions ---" << std::endl;
    std::cout << "1. Sort by Date" << std::endl;
    std::cout << "2. Sort by Amount" << std::endl;
    std::cout << "3. Sort by Category" << std::endl;

    int sortChoice = getValidInteger("Choose sorting criteria: ");

    std::cout << "1. Ascending" << std::endl;
    std::cout << "2. Descending" << std::endl;
    int orderChoice = getValidInteger("Choose order: ");

    std::cout << "1. Quick Sort" << std::endl;
    std::cout << "2. Merge Sort" << std::endl;
    int algorithmChoice = getValidInteger("Choose algorithm: ");

    ExpenseTracker::SortBy criteria;
    switch (sortChoice) {
        case 1: criteria = ExpenseTracker::SortBy::DATE; break;
        case 2: criteria = ExpenseTracker::SortBy::AMOUNT; break;
        case 3: criteria = ExpenseTracker::SortBy::CATEGORY; break;
        default:
            std::cout << "Invalid choice." << std::endl;
            return;
    }

    bool ascending = (orderChoice == 1);
    ExpenseTracker::SortAlgorithm algorithm = (algorithmChoice == 1) ? ExpenseTracker::SortAlgorithm::QUICK_SORT : ExpenseTracker::SortAlgorithm::MERGE_SORT;

    tracker->sortTransactions(criteria, ascending, algorithm);
    std::cout << "Transactions sorted successfully!" << std::endl;

    handleViewTransactions();
}

void ConsoleInterface::handleSearchTransactions() {
    if (tracker->getTransactionCount() == 0) {
        std::cout << "No transactions to search." << std::endl;
        return;
    }

    std::cout << "\n--- Search Transactions ---" << std::endl;
    std::cout << "1. Search by Category" << std::endl;
    std::cout << "2. Search by Amount Range" << std::endl;
    
    int searchChoice = getValidInteger("Choose search type: ");

    std::vector<Transaction> results;

    switch (searchChoice) {
        case 1: {
            std::string category = getValidString("Enter category to search: ");
            results = tracker->findTransactionsByCategory(category);
            break;
        }
        case 2: {
            double minAmount = getValidAmount("Enter minimum amount: ");
            double maxAmount = getValidAmount("Enter maximum amount: ");
            results = tracker->findTransactionsByAmountRange(minAmount, maxAmount);
            break;
        }
        default:
            std::cout << "Invalid choice." << std::endl;
            return;
    }

    std::cout << "\n--- Search Results ---" << std::endl;
    if (results.empty()) {
        std::cout << "No transactions found matching your criteria." << std::endl;
    } else {
        std::cout << "Found " << results.size() << " transaction(s):" << std::endl;
        for (const auto& transaction : results) {
            std::cout << transaction.toString() << std::endl;
        }
    }
}

void ConsoleInterface::handleViewAnalysis() {
    std::cout << "\n--- Expense Analysis ---" << std::endl;

    if (tracker->getTransactionCount() == 0) {
        std::cout << "No transactions to analyze." << std::endl;
        return;
    }

    std::cout << "Total Expenses: $" << std::fixed << std::setprecision(2) << tracker->getTotalExpenses() << std::endl;
    std::cout << "Total Transactions: " << tracker->getTransactionCount() << std::endl;
    std::cout << "Average Transaction: $" << std::fixed << std::setprecision(2) << (tracker->getTotalExpenses() / tracker->getTransactionCount()) << std::endl;

    std::cout << "\n--- Category Breakdown ---" << std::endl;
    const auto& categoryTotals = tracker->getCategoryTotals();

    for (const auto& pair : categoryTotals) {
        double percentage = (pair.second / tracker->getTotalExpenses()) * 100;
        std::cout << pair.first << ": $" << std::fixed << std::setprecision(2) 
                  << pair.second << " (" << std::fixed << std::setprecision(1) 
                  << percentage << "%)" << std::endl;
    }
}

void ConsoleInterface::handleClearData() {
    std::cout << "\n--- Clear All Data ---" << std::endl;
    std::cout << "This will delete all transactions. Are you sure? (N/Y): ";

    std::string confirmation;
    std::getline(std::cin, confirmation);

    if (confirmation == "y" || confirmation == "Y") {
        tracker->clear();
        std::cout << "All data cleared successfully!" << std::endl;
    } else {
        std::cout << "Operation cancelled." << std::endl;
    }
}

double ConsoleInterface::getValidAmount(const std::string& prompt) {
    double amount;
    std::cout << (prompt.empty() ? "Enter amount: $" : prompt);

    while(!(std::cin >> amount) || amount < 0) {
        std::cout << "Please enter a vald positive amount: $";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return amount;
}

std::string ConsoleInterface::getValidString(const std::string& prompt) {
    std::string input;
    std::cout << prompt;

    while(true) {
        std::getline(std::cin, input);
        if(!input.empty()) {
            break;
        }
        std::cout << "Please enter a non-empty string: ";
    }
    return input;
}