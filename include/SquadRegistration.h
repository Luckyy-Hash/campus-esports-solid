#ifndef SQUAD_REGISTRATION_H
#define SQUAD_REGISTRATION_H

#include "IFeeCalculator.h"

// ============================================================================
// 3. Open/Closed Principle (OCP) & Liskov Substitution Principle (LSP)
// SquadRegistration cleanly implements IFeeCalculator and can substitute it safely.
// Fee for Squad is Rs. 500.0.
// ============================================================================
class SquadRegistration : public IFeeCalculator {
public:
    double calculateFee() const override;
};

#endif // SQUAD_REGISTRATION_H

