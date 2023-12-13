//
// Created by ASUS on 11/14/2023.
//
#include <iostream>

void imageStackingMenu() {
    // Implementation of image stacking techniques
    std::cout << "1. Average Stacking\n";
    std::cout << "2. Median Stacking\n";
    // Add further options or functionality related to image stacking
}

void celestialCalculationsMenu() {
    // Implementation of celestial spherical calculations
    std::cout << "1. Convert celestial coordinates\n";
    std::cout << "2. Explore celestial objects from different perspectives\n";
    // Add further options or functionality related to celestial calculations
}

void multivariableRegressionMenu() {
    // Implementation of multivariable regression for astronomical data analysis
    std::cout << "1. Analyze data sets using multivariable regression\n";
    std::cout << "2. Gain insights into relationships among astronomical variables\n";
    // Add further options or functionality related to multivariable regression
}

int main() {
    int choice;

    do {
        std::cout << "------ Astronomical Engine Menu ------\n";
        std::cout << "1. Image Stacking\n";
        std::cout << "2. Celestial Spherical Calculations\n";
        std::cout << "3. Multivariable Regression for Astronomical Data Analysis\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                imageStackingMenu();
                break;
            case 2:
                celestialCalculationsMenu();
                break;
            case 3:
                multivariableRegressionMenu();
                break;
            case 4:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Please enter a valid option.\n";
        }
    } while (choice != 4);

    return 0;
}
