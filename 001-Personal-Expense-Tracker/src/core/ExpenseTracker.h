#ifndef EXPENSE_TRACKER_H
#define EXPENSE_TRACKER_H

#include <vector>
#include <unordered_map>
#include <memory>
#include <stdexcept>

#include "Transaction.h"

class ExpenseTracker {
    private:
        std::vector<Transaction> transactions;
        std::unordered_map<std::string, double> categoryTotals;

        void updateCategoryTotals();

    public:
        // Transaction management.
        void addTransaction(const Transaction& transaction);
        void removeTransaction(int id);
        void updateTransaction(int id, double amount, const std::string& category, const std::string& description);

        // sorting methods
        enum class SortBy { DATE, AMOUNT, CATEGORY };
        enum class SortAlgorithm { QUICK_SORT, MERGE_SORT };

        void sortTransactions(SortBy criteria, bool ascending = true, SortAlgorithm algorithm = SortAlgorithm::QUICK_SORT);

        // search methods.
        std::vector<Transaction> findTransactionsByCategory(const std::string& category) const;
        std::vector<Transaction> findTransactionByAmountRange(double min, double max) const;
        Transaction* findTransactionById(int id);

        // Analysis methods
        double getTotalExpenses() const;
        double getCategoryTotal(const std::string& category) const;
        const std::unordered_map<std::string, double>& getCategoryTotals() const;
        std::vector<std::string> getCategories() const;

        //  Data access
        const std::vector<Transaction>& getTransactions() const { return transactions; }
        size_t getTransactionCount() const { return transactions.size(); }

        // utility
        void clear();
};

class ExpenseTrackerException : public std::exception {
    private: 
        std::string message;

    public:
        explicit ExpenseTrackerException(const std::string& msg) : message(msg) {}
        const char* what() const noexcept override { return message.c_str(); }
};

#endif