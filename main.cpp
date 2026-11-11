#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <iomanip>
#include <limits>
#include "include/EmailNotification.h"
#include "include/SMSNotification.h"
#include "include/SoloRegistration.h"
#include "include/SquadRegistration.h"
#include "include/RegistrationManager.h"

// Helper function to trim leading and trailing whitespace
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

// Helper to safely read a non-empty string from user input
std::string readNonEmptyString(const std::string& prompt) {
    std::string input;
    while (true) {
        std::cout << prompt;
        if (!std::getline(std::cin, input)) {
            std::cin.clear();
            return "";
        }
        input = trim(input);
        if (!input.empty()) {
            return input;
        }
        std::cout << "[Error] Input cannot be empty. Please enter a valid name.\n";
    }
}

// Display the interactive menu
void displayMenu() {
    std::cout << "\n========================================\n";
    std::cout << "       CAMPUS ESPORTS TOURNAMENT        \n";
    std::cout << "========================================\n\n";
    std::cout << "1. Register Solo Player\n";
    std::cout << "2. Register Squad Team\n";
    std::cout << "3. View Registered Participants\n";
    std::cout << "4. View Registration Fee Details\n";
    std::cout << "5. Demonstrate Email Notification\n";
    std::cout << "6. Demonstrate SMS Notification\n";
    std::cout << "7. View Tournament Statistics\n";
    std::cout << "8. Exit\n\n";
    std::cout << "========================================\n";
    std::cout << "Enter your choice (1-8): ";
}

// Original case study batch demonstration (executed with --demo flag)
void runBatchDemo() {
    auto emailService = std::make_shared<EmailNotification>();
    auto smsService = std::make_shared<SMSNotification>();

    RegistrationManager manager(emailService);
    SoloRegistration solo;
    SquadRegistration squad;

    std::cout << "--- Campus Esports Registration ---\n";
    manager.registerTeam("Latheesh_Solo", solo);

    RegistrationManager managerSMS(smsService);
    managerSMS.registerTeam("VIT_Strikers", squad);
}

int main(int argc, char* argv[]) {
    // If launched with --demo or --batch, run the non-interactive case study demo
    if (argc > 1) {
        std::string arg = argv[1];
        if (arg == "--demo" || arg == "-d" || arg == "--batch") {
            runBatchDemo();
            return 0;
        }
    }

    // Concrete services (ISP & DIP)
    auto emailService = std::make_shared<EmailNotification>();
    auto smsService = std::make_shared<SMSNotification>();

    // Strategy instances for fee calculation (OCP & LSP)
    SoloRegistration soloFeeCalculator;
    SquadRegistration squadFeeCalculator;

    // High-level manager initialized with email notification abstraction (DIP)
    RegistrationManager manager(emailService);

    int choice = 0;
    while (true) {
        displayMenu();
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\n[Error] Invalid selection. Please enter a number between 1 and 8.\n";
            continue;
        }

        // Consume trailing newline
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: { // 1. Register Solo Player
                std::cout << "\n--- Solo Player Registration ---\n";
                std::string playerName = readNonEmptyString("Enter player name (e.g., Latheesh_Solo): ");
                
                // Inject email notification service (DIP)
                manager.setNotifier(emailService);
                
                std::cout << "\n[Processing Solo Registration]\n";
                // Pass SoloRegistration as const IFeeCalculator& (LSP)
                manager.registerTeam(playerName, "Solo", soloFeeCalculator);
                std::cout << "[Success] Solo registration completed successfully!\n";
                break;
            }

            case 2: { // 2. Register Squad Team
                std::cout << "\n--- Squad Team Registration ---\n";
                std::string squadName = readNonEmptyString("Enter squad/team name (e.g., VIT_Strikers): ");
                
                // Inject SMS notification service (OCP & DIP)
                manager.setNotifier(smsService);
                
                std::cout << "\n[Processing Squad Registration]\n";
                // Pass SquadRegistration as const IFeeCalculator& (LSP)
                manager.registerTeam(squadName, "Squad", squadFeeCalculator);
                std::cout << "[Success] Squad registration completed successfully!\n";
                break;
            }

            case 3: { // 3. View Registered Participants
                std::cout << "\n============================================================\n";
                std::cout << "                 REGISTERED PARTICIPANTS                    \n";
                std::cout << "============================================================\n";
                const auto& records = manager.getRecords();
                if (records.empty()) {
                    std::cout << "No participants registered in the current session yet.\n";
                } else {
                    std::cout << std::left 
                              << std::setw(5) << "#" 
                              << std::setw(28) << "Participant / Team Name" 
                              << std::setw(12) << "Type" 
                              << std::setw(15) << "Amount Paid" << "\n";
                    std::cout << "------------------------------------------------------------\n";
                    int idx = 1;
                    for (const auto& r : records) {
                        std::cout << std::left 
                                  << std::setw(5) << idx++
                                  << std::setw(28) << r.participantName 
                                  << std::setw(12) << r.registrationType 
                                  << "Rs." << std::fixed << std::setprecision(2) << r.feePaid << "\n";
                    }
                }
                std::cout << "============================================================\n";
                break;
            }

            case 4: { // 4. View Registration Fee Details
                std::cout << "\n============================================================\n";
                std::cout << "              REGISTRATION FEE STRUCTURE (SOLID)            \n";
                std::cout << "============================================================\n";
                std::cout << "- Solo Player Registration : Rs." << std::fixed << std::setprecision(2) 
                          << soloFeeCalculator.calculateFee() << " (SoloRegistration)\n";
                std::cout << "- Squad Team Registration  : Rs." << std::fixed << std::setprecision(2) 
                          << squadFeeCalculator.calculateFee() << " (SquadRegistration)\n";
                std::cout << "------------------------------------------------------------\n";
                std::cout << "[SOLID Architecture Note]:\n";
                std::cout << "Fee calculators implement the IFeeCalculator interface (ISP/LSP).\n";
                std::cout << "New formats (e.g., Duo, Trio) can be added as new subclasses\n";
                std::cout << "without modifying RegistrationManager or existing pricing (OCP).\n";
                std::cout << "============================================================\n";
                break;
            }

            case 5: { // 5. Demonstrate Email Notification
                std::cout << "\n============================================================\n";
                std::cout << "             DEMONSTRATE EMAIL NOTIFICATION (SRP)           \n";
                std::cout << "============================================================\n";
                std::cout << "Invoking EmailNotification::send():\n";
                emailService->send("Campus Esports brackets & schedules are now published!");
                std::cout << "------------------------------------------------------------\n";
                std::cout << "[SOLID Note]: EmailNotification handles only email protocol\n";
                std::cout << "formatting and delivery, strictly adhering to SRP.\n";
                std::cout << "============================================================\n";
                break;
            }

            case 6: { // 6. Demonstrate SMS Notification
                std::cout << "\n============================================================\n";
                std::cout << "             DEMONSTRATE SMS NOTIFICATION (OCP)             \n";
                std::cout << "============================================================\n";
                std::cout << "Invoking SMSNotification::send():\n";
                smsService->send("Your match starts in 15 minutes at Campus Esports Arena!");
                std::cout << "------------------------------------------------------------\n";
                std::cout << "[SOLID Note]: SMSNotification was added as a zero-touch\n";
                std::cout << "extension implementing INotificationService without modifying\n";
                std::cout << "RegistrationManager, demonstrating OCP.\n";
                std::cout << "============================================================\n";
                break;
            }

            case 7: { // 7. View Tournament Statistics
                std::cout << "\n============================================================\n";
                std::cout << "               TOURNAMENT SESSION STATISTICS                \n";
                std::cout << "============================================================\n";
                std::cout << "Total Participants Registered : " << manager.getTotalRegistrations() << "\n";
                std::cout << "Solo Player Registrations     : " << manager.getSoloCount() << "\n";
                std::cout << "Squad Team Registrations      : " << manager.getSquadCount() << "\n";
                std::cout << "Total Registration Fees Due   : Rs." << std::fixed << std::setprecision(2) 
                          << manager.getTotalFees() << "\n";
                std::cout << "============================================================\n";
                break;
            }

            case 8: { // 8. Exit
                std::cout << "\n============================================================\n";
                std::cout << "Thank you for using Campus Esports Tournament Registration!\n";
                std::cout << "Exiting application... Goodbye!\n";
                std::cout << "============================================================\n\n";
                return 0;
            }

            default: {
                std::cout << "\n[Error] Invalid choice '" << choice << "'. Please select a valid option (1-8).\n";
                break;
            }
        }
    }

    return 0;
}
