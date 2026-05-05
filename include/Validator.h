#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>
#include <regex>

class Validator {
public:
    static bool validateName(const std::string& name);
    static bool validateRollNo(int rollNo);
    static bool validateMarks(float marks);
    static bool validateEmail(const std::string& email);
    static bool validatePhone(const std::string& phone);
    static bool validateClassName(const std::string& className);
    
    static int getValidatedInt(const std::string& prompt, int min, int max);
    static float getValidatedFloat(const std::string& prompt, float min, float max);
    static std::string getValidatedString(const std::string& prompt);
    static std::string getValidatedEmail(const std::string& prompt);
    static std::string getValidatedPhone(const std::string& prompt);
};

#endif
