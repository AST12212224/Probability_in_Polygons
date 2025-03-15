#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

// Function to calculate center probability based on the formula
// Ensure math constants are included
const long double PI = 3.141592653589793238462643383279502884L;

long double degreesToRadians(long double degrees) {
    return degrees * (PI / 180.0);
}

long double centerProbability(int n) {
    if (n < 3) return 0.0L; // Invalid for polygons with less than 3 sides

    long double tan_90_n = std::tan(degreesToRadians(90.0L / n));
    long double cot_180_n = 1.0L / std::tan(degreesToRadians(180.0L / n));

    // First Term
    long double term1_numerator = std::atan((4.0L * tan_90_n) / (4.0L - tan_90_n * tan_90_n)) * PI * cot_180_n * std::pow(4.0L + tan_90_n * tan_90_n, 2);
    long double term1_denominator = 2880.0L;
    long double term1 = term1_numerator / term1_denominator;

    // Second Term
    long double cos_180_n = std::cos(degreesToRadians(180.0L / n));
    long double cos_90_n = std::cos(degreesToRadians(90.0L / n));
    long double term2_numerator = cos_180_n * (5.0L * cos_90_n * cos_90_n - 1.0L);
    long double term2_denominator = 8.0L * std::pow(cos_90_n, 4);
    long double term2 = term2_numerator / term2_denominator;

    // Third Term
    long double term3_numerator = cos_180_n * cos_180_n;
    long double term3_denominator = 4.0L * std::pow(cos_90_n, 4);
    long double term3 = term3_numerator / term3_denominator;

    // Final calculation
    long double center_prob = (term1 - term2 + term3) * -1.0L;
    return center_prob;
}

int main() {
    int maxSides;
    std::cout << "Enter the maximum number of sides: ";
    std::cin >> maxSides;

    if (maxSides < 3) {
        std::cout << "Number of sides must be at least 3." << std::endl;
        return 1;
    }

    std::ofstream file("polygon_probabilities.csv");
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing." << std::endl;
        return 1;
    }

    // Write header row
    file << "Sides,Center Probability,Circumference Probability" << std::endl;

    // Calculate and write probabilities
    for (int n = 3; n <= maxSides; ++n) {
        long double centerProb = centerProbability(n);
        long double circumferenceProb = 1.0L - centerProb;
        file << n << "," << std::fixed << std::setprecision(4) << centerProb << "," << circumferenceProb << std::endl;
    }

    file.close();
    std::cout << "CSV file 'polygon_probabilities.csv' created successfully." << std::endl;

    return 0;
}
