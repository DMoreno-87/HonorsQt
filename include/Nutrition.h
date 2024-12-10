#ifndef NUTRITION_H
#define NUTRITION_H

#include <string>
#include <vector>
#include "Food.h"
#include "Exercise.h"
#include "User.h"
using namespace std;

class Nutrition {
private:
    vector<Food> foods;
    vector<Exercise> exercises;
    int month;
    int day;
    int year;

public:
    Nutrition(int month, int day, int year);
    void addFood(const Food& food);
    void addExercise(const Exercise& exercise);
    float getTotalCaloriesConsumed() const;
    float getTotalCaloriesBurned() const;
    void displaySummary() const;
    int getMonth();
    int getDay();
    int getYear();
};

#endif
