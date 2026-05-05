#include "../include/Validator.h"
#include <iostream>
#include <algorithm>
#include <cctype>

bool Validator::validateName(const std::string& name) {
    if (name.empty() || name.length() < 2 || name.length() > 50) return false;
    for (char c : name) {
        if (!std::isalpha(c) && c != ' ') return false;
    }
    return true;
}

bool Validator::validateRollNo(int rollNo) {
    return rollNo > 0 && rollNo <= 999999;
}

bool Validator::validateMarks(float marks) {
    return marks >= 0 && marks <= 100;
}

bool Validator::validateEmail(const std::string& email) {
    std::regex pattern(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    return std::regex_match(email, pattern);
}

bool Validator::validatePhone(const std::string& phone) {
    std::regex pattern(R"(^[0-9]{10}$)");
    return std::regex_match(phone, pattern);
}

bool Validator::validateClassName(const std::string& className) {
    return !className.empty() && className.length() <= 20;
}

int Validator::getValidatedInt(const std::string& prompt, int min, int max) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail() || value < min || value > max) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "❌ Invalid input! Please enter a number between " << min << " and " << max << ": ";
        } else {
            std::cin.ignore(10000, '\n');
            return value;
        }
    }
}

float Validator::getValidatedFloat(const std::string& prompt, float min, float max) {
    float value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail() || value < min || value > max) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "❌ Invalid input! Please enter a number between " << min << " and " << max << ": ";
        } else {
            std::cin.ignore(10000, '\n');
            return value;
        }
    }
}

std::string Validator::getValidatedString(const std::string& prompt) {
    std::string value;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, value);
        if (!value.empty()) return value;
        std::cout << "❌ Input cannot be empty! ";
    }
}

std::string Validator::getValidatedEmail(const std::string& prompt) {
    std::string email;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, email);
        if (validateEmail(email)) return email;
        std::cout << "❌ Invalid email format! (example: name@domain.com)\n";
    }
}

std::string Validator::getValidatedPhone(const std::string& prompt) {
    std::string phone;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, phone);
        if (validatePhone(phone)) return phone;
        std::cout << "❌ Invalid phone number! (10 digits only)\n";
    }
}
