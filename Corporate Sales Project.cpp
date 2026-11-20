#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <stdexcept>
#include "DivSales.h"

using namespace std;

int main()
{
    const int NUM_DIVISIONS = 6;

    string fileName;
    int choice;
    int numberOfPeriods;

    cout << "Corporate Sales Project" << endl;
    cout << "-----------------------" << endl;

    cout << "Choose the sales data file:" << endl;
    cout << "1. Quarterly Sales" << endl;
    cout << "2. Monthly Sales" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1)
    {
        fileName = "Corporate_Sales_Quarterly_Test_Data.txt";
    }
    else if (choice == 2)
    {
        fileName = "Corporate_Sales_Monthly_Test_Data.txt";
    }
    else
    {
        cout << "Invalid choice." << endl;
        return 1;
    }

    // Open input file
    ifstream inputFile(fileName);

    if (!inputFile)
    {
        cout << "Error: Could not open the input file." << endl;
        cout << "Please check the file location." << endl;
        return 1;
    }

    // Read number of periods
    if (!(inputFile >> numberOfPeriods) || numberOfPeriods <= 0)
    {
        cout << "Error: Invalid number of periods." << endl;
        return 1;
    }

    try
    {
        // Create six DivSales objects
        DivSales divisions[NUM_DIVISIONS] =
        {
            DivSales(numberOfPeriods),
            DivSales(numberOfPeriods),
            DivSales(numberOfPeriods),
            DivSales(numberOfPeriods),
            DivSales(numberOfPeriods),
            DivSales(numberOfPeriods)
        };

        // Reset corporate sales
        DivSales::resetCorporateSales();

        // Read sales data from the file
        for (int division = 0; division < NUM_DIVISIONS; division++)
        {
            cout << "Reading Division " << division + 1 << "..." << endl;

            for (int period = 0; period < numberOfPeriods; period++)
            {
                if (!(inputFile >> divisions[division][period]))
                {
                    cout << "Error: Not enough valid sales data." << endl;
                    return 1;
                }

                if (divisions[division][period] <= 0)
                {
                    cout << "Error: Sales values must be positive." << endl;
                    return 1;
                }
            }
        }

        // Add division totals after all data is valid
        for (int division = 0; division < NUM_DIVISIONS; division++)
        {
            DivSales::addToCorporateSales(
                divisions[division].getTotalSales()
            );
        }

        inputFile.close();

        // Display sales report
        cout << fixed << setprecision(2);

        cout << "\nCORPORATE SALES REPORT" << endl;
        cout << "----------------------" << endl;

        cout << setw(12) << "Division";

        for (int period = 0; period < numberOfPeriods; period++)
        {
            cout << setw(13) << ("Period " + to_string(period + 1));
        }

        cout << setw(16) << "Total Sales" << endl;

        for (int division = 0; division < NUM_DIVISIONS; division++)
        {
            cout << setw(12) << division + 1;

            for (int period = 0; period < numberOfPeriods; period++)
            {
                cout << setw(13) << divisions[division][period];
            }

            cout << setw(16)
                << divisions[division].getTotalSales() << endl;
        }

        cout << "\nCorporate Sales Total: $"
            << DivSales::getCorporateSales() << endl;

        // Copy constructor test
        cout << "\nCOPY CONSTRUCTOR TEST" << endl;

        DivSales copiedDivision(divisions[0]);

        cout << "Original first value: "
            << divisions[0][0] << endl;

        cout << "Copied first value: "
            << copiedDivision[0] << endl;

        copiedDivision[0] = 999.99;

        cout << "After changing the copy:" << endl;

        cout << "Original first value: "
            << divisions[0][0] << endl;

        cout << "Copied first value: "
            << copiedDivision[0] << endl;

        // Copy assignment test
        cout << "\nCOPY ASSIGNMENT TEST" << endl;

        DivSales assignedDivision(2);

        assignedDivision = divisions[1];

        cout << "Source number of periods: "
            << divisions[1].getNumberOfPeriods() << endl;

        cout << "Assigned number of periods: "
            << assignedDivision.getNumberOfPeriods() << endl;

        assignedDivision[0] = 888.88;

        cout << "After changing the assigned object:" << endl;

        cout << "Original first value: "
            << divisions[1][0] << endl;

        cout << "Assigned first value: "
            << assignedDivision[0] << endl;

        // Self-assignment test
        cout << "\nSELF-ASSIGNMENT TEST" << endl;

        assignedDivision = assignedDivision;

        cout << "Object is still valid." << endl;

        cout << "First value: "
            << assignedDivision[0] << endl;

        // Bounds checking test
        cout << "\nBOUNDS CHECKING TEST" << endl;

        try
        {
            cout << divisions[0][numberOfPeriods] << endl;
        }
        catch (const out_of_range& error)
        {
            cout << "Error caught: " << error.what() << endl;
        }

        cout << "\nProgram completed successfully." << endl;
    }
    catch (const exception& error)
    {
        cout << "Error: " << error.what() << endl;
        return 1;
    }

    return 0;
}