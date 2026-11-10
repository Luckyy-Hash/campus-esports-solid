#include "RegistrationManager.h"
#include <iostream>

RegistrationManager::RegistrationManager(std::shared_ptr<INotificationService> n)
    : notifier(n) {}

void RegistrationManager::registerTeam(const std::string& teamName, const IFeeCalculator& feeType) {
    double fee = feeType.calculateFee();
    std::cout << "Registered " << teamName << ". Amount due: Rs." << fee << "\n";
    notifier->send("Registration successful for " + teamName);
}

