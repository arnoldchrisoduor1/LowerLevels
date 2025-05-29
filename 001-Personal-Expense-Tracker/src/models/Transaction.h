#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <chrono>
#include <iostream>
#include <sstream>
#include <iomanip>

class Transaction {
    private:
        static int nextId;
        int id;
        double amount;
        std::string category;
        std::string description;
        std::chrono::system_clock::time_point date;

    public:
        // constructors.
        Transaction(double amt, const std::string& cat, const std::string& desc);
        Transaction(double amt, const std::string& cat, const std::string& desc, const std::chrono::system_clock::time_point& dt);

        // Getters.
        int getInt() const { return id; }
        double getAmount() const { return amount; }
        const std::string& getCategory() const { return category; }
        const std::string& getDescription() const { return description; }
        const std::chrono::system_clock::time_point& getDate() const { return date; }

        // Setters.
        void setAmount(double amt) { amount = amt; }
        void setCategory(const std::string& cat) { category = cat; }
        void setDescription(const std::string& desc) { description = desc; }

        // Utility methods.
        std::string getDateString() const;
        std::string toString() const;

        // Comparison operators for sorting
        bool operator<(const Transaction& other) const;
        bool operator>(const Transaction& other) const;
};

#endif