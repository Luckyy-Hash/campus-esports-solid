#include <iostream>
#include <memory>
#include "include/EmailNotification.h"
#include "include/SMSNotification.h"
#include "include/SoloRegistration.h"
#include "include/SquadRegistration.h"
#include "include/RegistrationManager.h"

int main() {
    // Instantiate concrete notification services wrapped in shared_ptr
    auto emailService = std::make_shared<EmailNotification>();
    auto smsService = std::make_shared<SMSNotification>();

    // Dependency Injection: Pass EmailNotification into RegistrationManager
    RegistrationManager manager(emailService);
    SoloRegistration solo;
    SquadRegistration squad;

    std::cout << "--- Campus Esports Registration ---\n";
    // Register solo team with email notification
    manager.registerTeam("Latheesh_Solo", solo);

    // Dependency Injection: Swap to SMSNotification without modifying RegistrationManager (OCP / DIP)
    RegistrationManager managerSMS(smsService);
    // Register squad team with SMS notification
    managerSMS.registerTeam("VIT_Strikers", squad);

    return 0;
}

