#include "SMSNotification.h"
#include <iostream>

void SMSNotification::send(const std::string& message) {
    std::cout << "Sending SMS text: " << message << "\n";
}

