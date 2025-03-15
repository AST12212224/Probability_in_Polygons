#include <stdio.h>
#include <math.h>

#define PI 3.141592653589793238462643383279502884L

// Convert degrees to radians
double degreesToRadians(double degrees) {
    return degrees * (PI / 180.0);
}

// Function to calculate the center probability
double center_probability(int n) {
    if (n < 3) return 0.0;

    double tan_90_n = tan(degreesToRadians(90.0 / n));
    double cot_180_n = 1.0 / tan(degreesToRadians(180.0 / n));

    // First Term
    double term1_numerator = atan((4.0 * tan_90_n) / (4.0 - tan_90_n * tan_90_n)) * PI * cot_180_n * pow(4.0 + tan_90_n * tan_90_n, 2);
    double term1_denominator = 2880.0;
    double term1 = term1_numerator / term1_denominator;

    // Second Term
    double cos_180_n = cos(degreesToRadians(180.0 / n));
    double cos_90_n = cos(degreesToRadians(90.0 / n));
    double term2_numerator = cos_180_n * (5.0 * cos_90_n * cos_90_n - 1.0);
    double term2_denominator = 8.0 * pow(cos_90_n, 4);
    double term2 = term2_numerator / term2_denominator;

    // Third Term
    double term3_numerator = cos_180_n * cos_180_n;
    double term3_denominator = 4.0 * pow(cos_90_n, 4);
    double term3 = term3_numerator / term3_denominator;

    // Final calculation
    double center_prob = (term1 - term2 + term3) * -1.0;
    return center_prob;
}

// Function to calculate the circumference probability
double circumference_probability(int n) {
    return 1.0 - center_probability(n);
}

int main() {
    int n;
    printf("Enter number of sides polygon has: ");
    scanf("%d", &n);

    if (n < 3) {
        printf("Number of sides must be at least 3.\n");
        return 1;
    }

    double p_center = center_probability(n);
    double p_circumference = circumference_probability(n);

    printf("%.6lf\n", p_center);
    printf("%.6lf\n", p_circumference);

    return 0;
}
