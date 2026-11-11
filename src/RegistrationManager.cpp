#include "RegistrationManager.h"
#include <iostream>

RegistrationManager::RegistrationManager(std::shared_ptr<INotificationService> n)
    : notifier(n) {}

void RegistrationManager::setNotifier(std::shared_ptr<INotificationService> n) {
    notifier = n;
}

std::shared_ptr<INotificationService> RegistrationManager::getNotifier() const {
    return notifier;
}

void RegistrationManager::registerTeam(const std::string& teamName, const IFeeCalculator& feeType) {
    double fee = feeType.calculateFee();
    std::string category = (fee == 150.0) ? "Solo" : ((fee == 500.0) ? "Squad" : "Standard");
    registerTeam(teamName, category, feeType);
}

void RegistrationManager::registerTeam(const std::string& teamName, const std::string& categoryName, const IFeeCalculator& feeType) {
    double fee = feeType.calculateFee();
    records.push_back({teamName, categoryName, fee});
    std::cout << "Registered " << teamName << ". Amount due: Rs." << fee << "\n";
    if (notifier) {
        notifier->send("Registration successful for " + teamName);
    }
}

const std::vector<RegistrationRecord>& RegistrationManager::getRecords() const {
    return records;
}

size_t RegistrationManager::getTotalRegistrations() const {
    return records.size();
}

size_t RegistrationManager::getSoloCount() const {
    size_t count = 0;
    for (const auto& r : records) {
        if (r.registrationType == "Solo") {
            count++;
        }
    }
    return count;
}

size_t RegistrationManager::getSquadCount() const {
    size_t count = 0;
    for (const auto& r : records) {
        if (r.registrationType == "Squad") {
            count++;
        }
    }
    return count;
}

double RegistrationManager::getTotalFees() const {
    double total = 0.0;
    for (const auto& r : records) {
        total += r.feePaid;
    }
    return total;
}

void RegistrationManager::clearRecords() {
    records.clear();
}
