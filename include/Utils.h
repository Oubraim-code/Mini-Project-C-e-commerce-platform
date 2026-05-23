#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <ctime>

namespace Utils {
    // Generate unique ID
    int generateId();

    // Get current date as string
    std::string getCurrentDate();

    // Format price with currency
    std::string formatPrice(double price);

    // Split string by delimiter
    std::vector<std::string> split(const std::string& str, char delimiter);

    // Trim whitespace
    std::string trim(const std::string& str);

    // Read integer with validation
    int readInt(const std::string& prompt, int min, int max);

    // Read double with validation
    double readDouble(const std::string& prompt, double min, double max);

    // Read string non-empty
    std::string readString(const std::string& prompt);
}

#endif // UTILS_H
