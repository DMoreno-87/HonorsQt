#include "Nutrition.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QString>

// Constructor to initialize with a specific date
Nutrition::Nutrition(int month, int day, int year) : month(month), day(day), year(year) {}

int Nutrition::getMonth(){
    return month;
}

int Nutrition::getDay(){
    return day;
}

int Nutrition::getYear(){
    return year;
}

// Add food to the list
void Nutrition::addFood(const Food& food) {
    foods.push_back(food);
}

// Add exercise to the list
void Nutrition::addExercise(const Exercise& exercise) {
    exercises.push_back(exercise);
}

// Calculate the total calories consumed for the day
float Nutrition::getTotalCaloriesConsumed() const {
    float totalCalories = 0;
    for (const Food& food : foods) {
        totalCalories += food.getCalories();
    }
    return totalCalories;
}

// Calculate the total calories burned for the day
float Nutrition::getTotalCaloriesBurned() const {
    float totalCalories = 0;
    for (const Exercise& exercise : exercises) {
        totalCalories += exercise.caloriesBurned;
    }
    return totalCalories;
}

// Display the summary of the day's food and exercises
void Nutrition::displaySummary() const {
    QString summary = QString("Date: %1/%2/%3\n")
        .arg(month)
        .arg(day)
        .arg(year);

    summary += "Foods consumed: \n";
    for (const Food& food : foods) {
        summary += QString("  %1 | Protein: %2g, Carbs: %3g, Fat: %4g, Calories: %5 kcal\n")
                    .arg(QString::fromStdString(food.name))
                    .arg(QString::number(food.protein, 'f', 2))
                    .arg(QString::number(food.carbs, 'f', 2))
                    .arg(QString::number(food.fat, 'f', 2))
                    .arg(QString::number(food.getCalories(), 'f', 2));
    }

    summary += "Exercises: \n";
    for (const Exercise& exercise : exercises) {
        summary += QString("  %1 | Duration: %2 min, Calories burned: %3 kcal\n")
                    .arg(QString::fromStdString(exercise.name))
                    .arg(QString::number(exercise.duration, 'f', 2))
                    .arg(QString::number(exercise.caloriesBurned, 'f', 2));
    }

    summary += QString("Total Calories Consumed: %1 kcal\n").arg(getTotalCaloriesConsumed());
    summary += QString("Total Calories Burned: %1 kcal\n").arg(getTotalCaloriesBurned());

    QMessageBox::information(nullptr, "Nutrition Summary", summary);
}
