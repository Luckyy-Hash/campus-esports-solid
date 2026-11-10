#ifndef SOLO_REGISTRATION_H
#define SOLO_REGISTRATION_H

#include "IFeeCalculator.h"

// ============================================================================
// 3. Open/Closed Principle (OCP) & Liskov Substitution Principle (LSP)
// SoloRegistration cleanly implements IFeeCalculator and can substitute it safely.
// Fee for Solo is Rs. 150.0.
// ============================================================================
class SoloRegistration : public IFeeCalculator {
public:
    double calculateFee() const override;
};

#endif // SOLO_REGISTRATION_H

