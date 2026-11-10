#ifndef EMAIL_NOTIFICATION_H
#define EMAIL_NOTIFICATION_H

#include "INotificationService.h"
#include <string>

// ============================================================================
// 2. Single Responsibility Principle (SRP)
// This class ONLY handles email formatting and dispatching.
// It implements INotificationService without taking on tournament/fee logic.
// ============================================================================
class EmailNotification : public INotificationService {
public:
    void send(const std::string& message) override;
};

#endif // EMAIL_NOTIFICATION_H

