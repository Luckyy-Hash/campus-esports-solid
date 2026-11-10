#ifndef INOTIFICATION_SERVICE_H
#define INOTIFICATION_SERVICE_H

#include <string>

// ============================================================================
// 1. Interface Segregation Principle (ISP)
// Small, segregated interface for notifications. Clients only depend on
// sending notifications, without unrelated methods.
// ============================================================================
class INotificationService {
public:
    virtual void send(const std::string& message) = 0;
    virtual ~INotificationService() = default;
};

#endif // INOTIFICATION_SERVICE_H

