#ifndef SMS_NOTIFICATION_H
#define SMS_NOTIFICATION_H

#include "INotificationService.h"
#include <string>

// ============================================================================
// Open/Closed Principle (OCP) - Extension Requirement
// Adding SMS notification does not require modifying existing notification classes
// or the RegistrationManager class.
// ============================================================================
class SMSNotification : public INotificationService {
public:
    void send(const std::string& message) override;
};

#endif // SMS_NOTIFICATION_H

