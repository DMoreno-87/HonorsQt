#include "Exercise.h"

// Constructor to initialize the exercise item with given values
Exercise::Exercise(string name, float duration, float caloriesBurned)
    : name(name), duration(duration), caloriesBurned(caloriesBurned) {}
    
void Exercise::setExerciseName(string n){
    name = n;
}
    
void Exercise::setExerciseDuration(float d){
    duration = d;
}

void Exercise::setExeciseCaloriesBurned(float c){
    caloriesBurned = c;
}

void Exercise::getExerciseSummary(){
    cout << "Exercise Name: " << name << endl;
    cout << "Duration of Exercise: " << duration << " mins" << endl;
    cout << "Calories Burned: " << caloriesBurned << " calories" << endl;
}
