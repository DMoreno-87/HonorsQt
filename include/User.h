#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    float weight;  // in lbs
    float height;  // in in
    int age;
    char gender;
    float activityLevel = 0;  // Activity level factor (1.2, 1.375, 1.55, 1.725, etc.)
    float dailyCaloricGoal;
    float dailyProteinGoal;
    float dailyCarbGoal;
    float dailyFatGoal;

public:
    User();
    User(float weight, float height, int age);
    void calculateMacroGoals();
    void setCaloricGoal();
    void setSpecificCaloricGoal();
    void displayProfile() const;
    void setWeight();
    void setHeight();
    void setAge();
    void setGender();
    float getDailyCaloricGoal() const;
    float getDailyProteinGoal() const;
    float getDailyCarbGoal() const;
    float getDailyFatGoal() const;
    float calculateBMR() const;
};

#endif
