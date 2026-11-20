#include "DivSales.h"
#include <iostream>
#include <stdexcept>

using namespace std;

// Initialize static variable
double DivSales::corporateSales = 0.0;

// Constructor
DivSales::DivSales(int numberOfPeriods)
{
    if (numberOfPeriods <= 0)
    {
        throw invalid_argument("Number of periods must be greater than zero.");
    }

    this->numberOfPeriods = numberOfPeriods;

    sales = new double[numberOfPeriods];

    for (int i = 0; i < numberOfPeriods; i++)
    {
        sales[i] = 0.0;
    }
}

// Destructor
DivSales::~DivSales()
{
    delete[] sales;
}

// Copy constructor
DivSales::DivSales(const DivSales& other)
{
    numberOfPeriods = other.numberOfPeriods;

    sales = new double[numberOfPeriods];

    for (int i = 0; i < numberOfPeriods; i++)
    {
        sales[i] = other.sales[i];
    }
}

// Copy assignment operator
DivSales& DivSales::operator=(const DivSales& other)
{
    if (this != &other)
    {
        delete[] sales;

        numberOfPeriods = other.numberOfPeriods;

        sales = new double[numberOfPeriods];

        for (int i = 0; i < numberOfPeriods; i++)
        {
            sales[i] = other.sales[i];
        }
    }

    return *this;
}

// Non-const subscript operator
double& DivSales::operator[](int index)
{
    if (index < 0 || index >= numberOfPeriods)
    {
        throw out_of_range("Invalid sales index.");
    }

    return sales[index];
}

// Const subscript operator
const double& DivSales::operator[](int index) const
{
    if (index < 0 || index >= numberOfPeriods)
    {
        throw out_of_range("Invalid sales index.");
    }

    return sales[index];
}

// Return number of periods
int DivSales::getNumberOfPeriods() const
{
    return numberOfPeriods;
}

// Calculate total sales for one division
double DivSales::getTotalSales() const
{
    double total = 0.0;

    for (int i = 0; i < numberOfPeriods; i++)
    {
        total += sales[i];
    }

    return total;
}

// Return corporate sales total
double DivSales::getCorporateSales()
{
    return corporateSales;
}

// Reset corporate sales total
void DivSales::resetCorporateSales()
{
    corporateSales = 0.0;
}

// Add a division total to corporate sales
void DivSales::addToCorporateSales(double amount)
{
    corporateSales += amount;
}