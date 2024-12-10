#include "User.h"
#include <QInputDialog>
#include <QMessageBox>
using namespace std;

User::User()
    : weight(0), height(0), age(0), 
      dailyCaloricGoal(0), dailyProteinGoal(0), dailyCarbGoal(0), dailyFatGoal(0) {}

// Constructor to initialize the user profile
User::User(float weight, float height, int age)
    : weight(weight), height(height), age(age), 
      dailyCaloricGoal(0), dailyProteinGoal(0), dailyCarbGoal(0), dailyFatGoal(0) {}

// Calculate Basal Metabolic Rate (BMR) using the Mifflin-St Jeor equation
float User::calculateBMR() const {
    if (gender == 'M') {
        return 4.536 * weight + 15.88 * height - 5 * age + 5;
    } 
        else if (gender == 'F') {
            return 4.536 * weight + 15.88 * height - 5 * age - 161;
        }
}

// Calculate the daily caloric goal based on BMR and activity level
void User::calculateMacroGoals() {
    float proteinpercentage;
    float carbspercentage;
    float fatpercentage;
    bool ok;

    // Distribute the calories into macronutrients (example: 40% protein, 40% carbs, 20% fat)
    do {
        proteinpercentage = QInputDialog::getDouble(nullptr, "Protein Percentage",
                                                    "Enter the percentage of your caloric goal you want to dedicate to protein:",
                                                    0, 0, 100, 1, &ok);
        if (!ok) return;

        carbspercentage = QInputDialog::getDouble(nullptr, "Carb Percentage",
                                                  "Enter the percentage of your caloric goal you want to dedicate to carbs:",
                                                  0, 0, 100, 1, &ok);
        if (!ok) return;

        fatpercentage = 100 - (proteinpercentage + carbspercentage);

        if ((proteinpercentage + carbspercentage + fatpercentage) > 100) {
            QMessageBox::warning(nullptr, "Input Error", "You've exceeded your total percentage of your caloric goal. Please try again.");
        }
    } while ((proteinpercentage + carbspercentage + fatpercentage) > 100);
    
    dailyProteinGoal = (dailyCaloricGoal * (proteinpercentage/100)) / 4;  // 1g protein = 4 kcal
    dailyCarbGoal = (dailyCaloricGoal * (carbspercentage/100)) / 4;     // 1g carb = 4 kcal
    dailyFatGoal = (dailyCaloricGoal * (fatpercentage/100)) / 9;      // 1g fat = 9 kcal
}

void User::setGender() {
    bool ok;
    QString genderInput = QInputDialog::getItem(nullptr, "Gender",
                                                "Choose the gender you most identify with:",
                                                {"Male", "Female", "Non-binary"}, 0, false, &ok);
    if (ok) {
        if (genderInput == "Male") {
            gender = 'M';
        } else if (genderInput == "Female") {
            gender = 'F';
        } else if (genderInput == "Non-binary") {
            gender = 'N';
        }
    }
}

// Set a specific caloric goal for the user
void User::setCaloricGoal() {
    bool ok;
    dailyCaloricGoal = QInputDialog::getInt(nullptr, "Daily Caloric Goal",
                                            "Set your desired daily caloric goal:",
                                            2000, 100, 5000, 50, &ok);
    if (!ok) return;
}

void User::setSpecificCaloricGoal() {
    if ((gender == 'M') || (gender == 'F')) {    
        float bmr = calculateBMR();
        bool ok;
        
        QMessageBox::information(nullptr, "Reminder", "Make sure to fill out the rest of your profile to get an accurate calculation.");

        QString activityChoiceStr = QInputDialog::getItem(nullptr, "Activity Level",
                                                          "Choose your activity level from the choices below:",
                                                          {"Sedentary", "Lightly active", "Moderately active", "Very active", "Extremely active"},
                                                          0, false, &ok);

        if (ok) {
            if (activityChoiceStr == "Sedentary") {
                activityLevel = 1.2;
            } else if (activityChoiceStr == "Lightly active") {
                activityLevel = 1.375;
            } else if (activityChoiceStr == "Moderately active") {
                activityLevel = 1.55;
            } else if (activityChoiceStr == "Very active") {
                activityLevel = 1.725;
            } else if (activityChoiceStr == "Extremely active") {
                activityLevel = 1.9;
            }
        }
        dailyCaloricGoal = bmr * activityLevel;
    }
    else if (gender == 'N'){
        QMessageBox::information(nullptr, "Consultation",
                                 "For a more personalized caloric goal calculation, please consult with your physician or dietician to determine your individual needs.");
    }
        else {
        QMessageBox::information(nullptr, "Profile Reminder",
                                 "Please fill out your profile to set your caloric and macronutrient goals using BMR.");
    }
    return;
}

void User::setWeight(){
    bool ok;
    weight = QInputDialog::getDouble(nullptr, "Weight Input", "Enter your current weight:", 0, 0, 1000, 1, &ok);
    if (!ok) return;
}

void User::setHeight(){
    bool ok;
    height = QInputDialog::getDouble(nullptr, "Height Input", "Enter your current height:", 0, 0, 300, 1, &ok);
    if (!ok) return;
}

void User::setAge(){
    bool ok;
    age = QInputDialog::getInt(nullptr, "Age Input", "Enter your current age:", 18, 0, 120, 1, &ok);
    if (!ok) return;
}

// Display the user's profile and goals
void User::displayProfile() const {
    QString genderStr;
    if (gender == 'M') genderStr = "Male";
    else if (gender == 'F') genderStr = "Female";
    else if (gender == 'N') genderStr = "Non-binary";

    QString profile = QString("User Profile:\n"
                              "Weight: %1 lbs\nHeight: %2 in\nAge: %3\n"
                              "Gender: %4\nActivity Level: %5\n"
                              "Daily Caloric Goal: %6 kcal\n"
                              "Daily Macronutrient Goals:\n"
                              "  Protein: %7 g\n  Carbs: %8 g\n  Fat: %9 g")
                          .arg(weight).arg(height).arg(age).arg(genderStr)
                          .arg(activityLevel).arg(dailyCaloricGoal)
                          .arg(dailyProteinGoal).arg(dailyCarbGoal).arg(dailyFatGoal);

    QMessageBox::information(nullptr, "User Profile", profile);
}

float User::getDailyCaloricGoal() const {
    return dailyCaloricGoal;
}

float User::getDailyProteinGoal() const {
    return dailyProteinGoal;
}

float User::getDailyCarbGoal() const {
    return dailyCarbGoal;
}

float User::getDailyFatGoal() const {
    return dailyFatGoal;
}
