#include "ExpenseTracker.h"
#include <algorithm>
#include <SortingAlgorithms.h>

void ExpenseTracker::addTransaction(const Transaction& transaction) {
    transactions.push_back(transaction);
    updateCategoryTotals();
}

void ExpenseTracker::removeTransaction(int id) {
    auto it = std::find_if(transactions.begin(), transactions.end(),[id](const Transaction& t) { return t.getId() == id; });
    
    if (it != transactions.end()) {
        transactions.erase(it);
        updateCategoryTotals();
    } else {
        throw ExpenseTrackerException("Transaction with ID " + std::to_string(id) + " not found");
    }
}

void ExpenseTracker::updateTransaction(int id, double amount, const std::string& category, const std::string& description) {
    Transaction* transaction = findTransactionById(id);
    if (transaction) {
        transaction->setAmount(amount);
        transaction->setCategory(category);
        transaction->setDescription(description);
        updateCategoryTotals();
    } else {
        throw ExpenseTrackerException("Transaction with ID " + std::to_string(id) + "not found");
    }
}

void ExpenseTracker::sortTransactions(SortBy criteria, bool ascending, SortAlgorithm algorithm) {
    std::function<bool(const Transaction&, const Transaction&)> compare;
    
    switch (criteria) {
        case SortBy::DATE:
            compare = ascending ? 
                [](const Transaction& a, const Transaction& b) { return a.getDate() < b.getDate(); } :
                [](const Transaction& a, const Transaction& b) { return a.getDate() > b.getDate(); };
            break;
        case SortBy::AMOUNT:
            compare = ascending ?
                [](const Transaction& a, const Transaction& b) { return a.getAmount() < b.getAmount(); } :
                [](const Transaction& a, const Transaction& b) { return a.getAmount() > b.getAmount(); };
            break;
        case SortBy::CATEGORY:
            compare = ascending ?
                [](const Transaction& a, const Transaction& b) { return a.getCategory() < b.getCategory(); } :
                [](const Transaction& a, const Transaction& b) { return a.getCategory() > b.getCategory(); };
            break;
    }
    switch (algorithm) {
        case SortAlgorithm::QUICK_SORT:
            SortingAlgorithms::quickSort(transactions, compare);
        break;
        case SortAlgorithm::MERGE_SORT:
            SortingAlgorithms::mergeSort(transactions, compare);
            break;
    }
}

std::vector<Transaction> ExpenseTracker::findTransactionsByCategory(const std::string& category) const {
    std::vector<Transaction> result;
    for (const auto& transaction : transactions) {
        if (transaction.getCategory() == category) {
            result.push_back(transaction);
        }
    }
    return result;
}

std::vector<Transaction> ExpenseTracker::findTransactionsByAmountRange(double min, double max) const {
    std::vector<Transaction> result;
    for (const auto& transaction : transactions) {
        double amount = transaction.getAmount();
        if (amount >= min && amount <= max) {
            result.push_back(transaction);
        }
    }
}

Transaction* ExpenseTracker::findTransactionById(int id) {
    auto it = std::find_if(transactions.begin(), transactions.end(), [id](const Transaction& t) { return t.getId() == id; });
    return (it != transactions.end()) ? &(*it) : nullptr;
}

double ExpenseTracker::getTotalExpenses() const {
    double total = 0.0;
    for (const auto& transaction : transactions) {
        total += transaction.getAmount();
    }
    return total;
}

double ExpenseTracker::getCategoryTotal(const std::string& category) const {
    auto it = categoryTotals.find(category);
    return (it != categoryTotals.end()) ? it->second : 0.0;
}

const std::unordered_map<std::string, double>& ExpenseTracker::getCategoryTotals() const {
    return categoryTotals;
}

std::vector<std::string> ExpenseTracker::getCategories() const {
    std::vector<std::string> categories;
    for (const auto& pair : categoryTotals) {
        categories.push_back(pair.first);
    }
    return categories;
}

void ExpenseTracker::updateCategoryTotals() {
    categoryTotals.clear();
    for (const auto& transaction : transactions) {
        categoryTotals[transaction.getCategory()] += transaction.getAmount();
    }
}

void ExpenseTracker::clear() {
    transactions.clear();
    categoryTotals.clear();
}