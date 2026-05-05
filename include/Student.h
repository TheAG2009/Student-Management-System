#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <iomanip>

class Student {
private:
    int rollNo;
    std::string name;
    std::string className;
    float marks;
    std::string email;
    std::string phone;

public:
    // Constructors
    Student();
    Student(int roll, std::string name, std::string className, float marks, std::string email, std::string phone);
    
    // Getters
    int getRollNo() const;
    std::string getName() const;
    std::string getClassName() const;
    float getMarks() const;
    std::string getEmail() const;
    std::string getPhone() const;
    
    // Setters
    void setRollNo(int roll);
    void setName(std::string name);
    void setClassName(std::string className);
    void setMarks(float marks);
    void setEmail(std::string email);
    void setPhone(std::string phone);
    
    // Utility methods
    char getGrade() const;
    void display() const;
    std::string toString() const;
    static Student fromString(const std::string& data);
};

#endif
