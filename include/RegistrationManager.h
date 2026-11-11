#ifndef REGISTRATION_MANAGER_H
#define REGISTRATION_MANAGER_H

#include "INotificationService.h"
#include "IFeeCalculator.h"
#include <string>
#include <memory>
#include <vector>

// Structure to store registration records for session management
struct RegistrationRecord {
    std::string participantName;
    std::string registrationType; // "Solo" or "Squad"
    double feePaid;
};

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
    std::vector<RegistrationRecord> records;

public:
    explicit RegistrationManager(std::shared_ptr<INotificationService> n);

    // Dynamic setter/getter for notification service (OCP & DIP runtime flexibility)
    void setNotifier(std::shared_ptr<INotificationService> n);
    std::shared_ptr<INotificationService> getNotifier() const;

    // Original registerTeam method (100% backward compatible with original case study)
    void registerTeam(const std::string& teamName, const IFeeCalculator& feeType);

    // Extended registerTeam with explicit category name
    void registerTeam(const std::string& teamName, const std::string& categoryName, const IFeeCalculator& feeType);

    // Query and session statistics methods (SRP)
    const std::vector<RegistrationRecord>& getRecords() const;
    size_t getTotalRegistrations() const;
    size_t getSoloCount() const;
    size_t getSquadCount() const;
    double getTotalFees() const;
    void clearRecords();
};

#endif // REGISTRATION_MANAGER_H
