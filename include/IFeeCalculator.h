#ifndef IFEE_CALCULATOR_H
#define IFEE_CALCULATOR_H

// ============================================================================
// 1. Interface Segregation Principle (ISP) & Open/Closed Principle (OCP)
// Segregated interface dedicated strictly to calculating tournament registration fees.
// ============================================================================
class IFeeCalculator {
public:
    virtual double calculateFee() const = 0;
    virtual ~IFeeCalculator() = default;
};

#endif // IFEE_CALCULATOR_H

