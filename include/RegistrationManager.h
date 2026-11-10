#ifndef REGISTRATION_MANAGER_H
#define REGISTRATION_MANAGER_H

#include "INotificationService.h"
#include "IFeeCalculator.h"
#include <string>
#include <memory>

// ============================================================================
// 4. Dependency Inversion Principle (DIP) & Single Responsibility Principle (SRP)
// High-level module RegistrationManager depends on abstractions:
// - INotificationService is received through constructor injection (std::shared_ptr)
// - IFeeCalculator is passed to registerTeam() as a const reference (const IFeeCalculator&)
// This decouples RegistrationManager from concrete notification protocols and fee models.
// ============================================================================
class RegistrationManager {
private:
    std::shared_ptr<INotificationService> notifier;
public:
    explicit RegistrationManager(std::shared_ptr<INotificationService> n);
    void registerTeam(const std::string& teamName, const IFeeCalculator& feeType);
};

#endif // REGISTRATION_MANAGER_H
