#include "Utils.h"
#include <iostream>
#include <limits>
#include <algorithm>

namespace Utils {
    static int currentId = 1000;

    int generateId() {
        return currentId++;
    }

    std::string getCurrentDate() {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        char buffer[11];
        sprintf(buffer, "%04d-%02d-%02d", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday);
        return std::string(buffer);
    }

    std::string formatPrice(double price) {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << price << " €";
        return oss.str();
    }

    std::vector<std::string> split(const std::string& str, char delimiter) {
        std::vector<std::string> tokens;
        std::stringstream ss(str);
        std::string token;
        while (std::getline(ss, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }

    std::string trim(const std::string& str) {
        size_t first = str.find_first_not_of(' ');
        if (first == std::string::npos) return "";
        size_t last = str.find_last_not_of(' ');
        return str.substr(first, (last - first + 1));
    }

    int readInt(const std::string& prompt, int min, int max) {
        int value;
        while (true) {
            std::cout << prompt;
            if (std::cin >> value && value >= min && value <= max) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrée invalide. Veuillez entrer un nombre entre " 
                      << min << " et " << max << "." << std::endl;
        }
    }

    double readDouble(const std::string& prompt, double min, double max) {
        double value;
        while (true) {
            std::cout << prompt;
            if (std::cin >> value && value >= min && value <= max) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrée invalide. Veuillez entrer un nombre entre " 
                      << min << " et " << max << "." << std::endl;
        }
    }

    std::string readString(const std::string& prompt) {
        std::string value;
        while (true) {
            std::cout << prompt;
            std::getline(std::cin, value);
            value = trim(value);
            if (!value.empty()) {
                return value;
            }
            std::cout << "Entrée invalide. Le champ ne peut pas être vide." << std::endl;
        }
    }
}
