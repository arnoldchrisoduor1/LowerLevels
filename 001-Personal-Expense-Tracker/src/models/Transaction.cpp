#include "Transaction.h"

int Transaction::nextId = 1;

Transaction::Transaction(double amt, const std::string& cat, const std::string& desc) : id(nextId++), amount(amt), category(cat), description(desc), date(std::chrono::system_clock::now()) {}

Transaction::Transaction(double amt, const std::string& cat, const std::string& desc, const std::chrono::system_clock::time_point& dt) : id(nextId++), amount(amt), category(cat), description(desc), date(dt) {}

std::string Transaction::getDateString() const {
    auto time_t = std::chrono::system_clock::to_time_t(date);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M");
    return ss.str();
}

std::string Transaction::toString() const {
    std::stringstream ss;
    ss << "ID" << id << " | Amount: $" << std::fixed << std::setprecision(2) << amount << " | Category: " << category << " | Description: " << description << " | Date: " << getDateString();
    return ss.str();
}

bool Transaction::operator<(const Transaction& other) const {
    return date < other.date;
}

bool Transaction::operator>(const Transaction& other) const {
    return date > other.date;
}