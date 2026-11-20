#ifndef DIVSALES_H
#define DIVSALES_H

class DivSales
{
private:
    double* sales;
    int numberOfPeriods;

    static double corporateSales;

public:
    // Constructor
    DivSales(int numberOfPeriods);

    // Destructor
    ~DivSales();

    // Copy constructor
    DivSales(const DivSales& other);

    // Copy assignment operator
    DivSales& operator=(const DivSales& other);

    // Overloaded subscript operators
    double& operator[](int index);
    const double& operator[](int index) const;

    // Supporting functions
    int getNumberOfPeriods() const;
    double getTotalSales() const;

    // Static functions
    static double getCorporateSales();
    static void resetCorporateSales();
    static void addToCorporateSales(double amount);
};

#endif#pragma once
