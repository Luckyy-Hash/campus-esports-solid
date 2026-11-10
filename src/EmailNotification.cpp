#include "EmailNotification.h"
#include <iostream>

void EmailNotification::send(const std::string& message) {
    std::cout << "Sending Email: " << message << "\n";
}

