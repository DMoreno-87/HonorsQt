#ifndef FOOD_H
#define FOOD_H

#include <string>
#include <QFile>
#include <QTextStream>
#include <QDebug>
using namespace std;

class Food {
public:
    string name;
    float protein;  // in grams
    float carbs;    // in grams
    float fat;      // in grams

    Food(string name, float protein, float carbs, float fat);
    float getCalories() const;  // Calculate total calories from protein, carbs, and fat
    void writeFoodsToFile(QTextStream& out) const;
};

#endif
