// ============================================================================
// Campus Esports Tournament Registration System
// Course: BCSE102L - Structured and Object-Oriented Programming
// Student: P. Latheesh Reddy (23BCE0329)
// Institution: VIT Vellore
//
// SOLID Principles Implementation:
// - SRP: EmailNotification only handles email formatting/sending
// - OCP: Adding SMSNotification and SquadRegistration extends functionality without modifying existing code
// - LSP: Subclasses safely substitute their base interfaces (INotificationService, IFeeCalculator)
// - ISP: Segregated small interfaces (INotificationService, IFeeCalculator)
// - DIP: RegistrationManager depends on abstractions: receives INotificationService
//        through constructor injection (std::shared_ptr), while IFeeCalculator is passed
//        to registerTeam() as a const reference.
// ============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <memory>

// ----------------------------------------------------------------------------
// Part 1: Interfaces and Basic Implementations
// ----------------------------------------------------------------------------

// 1. ISP: Small, segregated interfaces
class INotificationService {
public:
    virtual void send(const std::string& message) = 0;
    virtual ~INotificationService() = default;
};

class IFeeCalculator {
public:
    virtual double calculateFee() const = 0;
    virtual ~IFeeCalculator() = default;
};

// 2. SRP: This class ONLY handles email formatting/sending
class EmailNotification : public INotificationService {
public:
    void send(const std::string& message) override {
        std::cout << "Sending Email: " << message << "\n";
    }
};

// Extension (Part B requirement): Adding SMS doesn't change existing code (OCP)
class SMSNotification : public INotificationService {
public:
    void send(const std::string& message) override {
        std::cout << "Sending SMS text: " << message << "\n";
    }
};

// ----------------------------------------------------------------------------
// Part 2: OCP, LSP, and DIP Implementation
// ----------------------------------------------------------------------------

// 3. OCP & LSP: Subclasses can replace IFeeCalculator safely
class SoloRegistration : public IFeeCalculator {
public:
    double calculateFee() const override { return 150.0; }
};

class SquadRegistration : public IFeeCalculator {
public:
    double calculateFee() const override { return 500.0; }
};

// 4. DIP: RegistrationManager depends on abstractions.
// Receives INotificationService through constructor injection, while
// IFeeCalculator is passed to registerTeam() as a const reference.
class RegistrationManager {
private:
    std::shared_ptr<INotificationService> notifier;
public:
    RegistrationManager(std::shared_ptr<INotificationService> n) : notifier(n) {}

    void registerTeam(const std::string& teamName, const IFeeCalculator& feeType) {
        double fee = feeType.calculateFee();
        std::cout << "Registered " << teamName << ". Amount due: Rs." << fee << "\n";
        notifier->send("Registration successful for " + teamName);
    }
};

// ----------------------------------------------------------------------------
// Part 3: Main Function Execution
// ----------------------------------------------------------------------------

int main() {
    auto emailService = std::make_shared<EmailNotification>();
    auto smsService = std::make_shared<SMSNotification>();

    RegistrationManager manager(emailService);
    SoloRegistration solo;
    SquadRegistration squad;

    std::cout << "--- Campus Esports Registration ---\n";
    manager.registerTeam("Latheesh_Solo", solo);

    RegistrationManager managerSMS(smsService);
    managerSMS.registerTeam("VIT_Strikers", squad);

    return 0;
}
