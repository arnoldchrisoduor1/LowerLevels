#ifndef CONSOLE_INTERFACE_H
#define CONSOLE_INTERFACE_H

#include <memory>
#include <ExpenseTracker.h>

class ConsoleInterface {
    private:
        std::unique_ptr<ExpenseTracker> tracker;

        void showMenu();
        void handleAddTransaction();
        void handleRemoveTransaction();
        void handleUpdateTransaction();
        void handleViewTransactions();
        void handleSortTransactions();
        void handleSearchTransactions();
        void handleViewAnalysis();
        void handleClearData();

        // Utility methods.
        double getValidAmount(const std::string& prompt);
        std::string getValidString(const std::string& prompt);
        int getValidInteger(const std::string& prompt);
        void pressEnterToContinue();
        void clearScreen();

    public:
        ConsoleInterface();
        ~ConsoleInterface() = default;

        void run();
};

#endif