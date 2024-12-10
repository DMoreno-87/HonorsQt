#include "LogManager.h"
#include <iostream>
#include <vector>
#include <QTextEdit>
#include <QInputDialog>
#include <QMessageBox>
#include <QDate>
#include "User.h"
#include "Nutrition.h"
#include "Food.h"
#include "Exercise.h"
#include "qapplication.h"

LogManager::LogManager(QTextEdit *textEdit){
    this->textEdit = textEdit;
    QDate currentDate = QDate::currentDate();
    thisYear = currentDate.year();

    lastYearLog = createYearlyLog(thisYear - 1);
    thisYearLog = createYearlyLog(thisYear);
    nextYearLog = createYearlyLog(thisYear + 1);
}

bool LogManager::isLeapYear(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

vector<Nutrition> LogManager::createYearlyLog(int year) {
    vector<int> monthsDays = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (isLeapYear(year)) {
        monthsDays[1] = 29;
    }

    vector<Nutrition> yearlyLog;
    for (int month = 0; month < 12; ++month) {
        for (int day = 1; day <= monthsDays[month]; ++day) {
            yearlyLog.push_back(Nutrition(month + 1, day, year));
        }
    }

    return yearlyLog;
}

int LogManager::accessSpecificDayOfYear(int month, int day, int year) {
    int yearIndex = 0;
    for (int m = 1; m < month; m++) {
        if ((m == 1) || (m == 3) || (m == 5) || (m == 7) || (m == 8) || (m == 10) || (m == 12)) {
            yearIndex = yearIndex + 31;
        }
        else if ((m == 4) || (m == 6) || (m == 9) || (m == 11)) {
            yearIndex = yearIndex + 30;
        }
        else if (isLeapYear(year)) {
            yearIndex = yearIndex + 29;
        }
        else {
            yearIndex = yearIndex + 28;
        }
    }
    yearIndex = yearIndex + day - 1;

    return yearIndex;
}

void LogManager::assignDate(int& month, int& day, int& year, int thisYear) {
    bool ok;

    year = QInputDialog::getInt(nullptr, "Enter Year", "Year (last year, this year, or next year):", thisYear, thisYear - 1, thisYear + 1, 1, &ok);
    while (!ok || (year < thisYear - 1) || (year > thisYear + 1)){
        QMessageBox::warning(nullptr, "Invalid Input", "Please choose a year between last year, this year, or next year.");
        year = QInputDialog::getInt(nullptr, "Enter Year", "Year (last year, this year, or next year):", thisYear, thisYear - 1, thisYear + 1, 1, &ok);
    }
    month = QInputDialog::getInt(nullptr, "Enter Month", "Month (1-12):", 1, 1, 12, 1, &ok);
    while (!ok || (month < 1) || (month > 12)){
        QMessageBox::warning(nullptr, "Invalid Input", "Please enter a valid month (1-12).");
        month = QInputDialog::getInt(nullptr, "Enter Month", "Month (1-12):", 1, 1, 12, 1, &ok);
    }
    day = QInputDialog::getInt(nullptr, "Enter Day", "Day:", 1, 1, 31, 1, &ok);
    while (!ok || (day < 1) || (day > 31) || !isValidDayForMonth(month, day, year)) {
        QMessageBox::warning(nullptr, "Invalid Input", "Please enter a valid day for the selected month.");
        day = QInputDialog::getInt(nullptr, "Enter Day", "Day:", 1, 1, 31, 1, &ok);
    }
}

bool LogManager::isValidDayForMonth(int month, int day, int year) {
    if ((month == 1) || (month == 3) || (month == 5) || (month == 7) || (month == 8) || (month == 10) || (month == 12)) {
        return (day <= 31);
    } else if ((month == 4) || (month == 6) || (month == 9) || (month == 11)) {
        return (day <= 30);
    } else if (isLeapYear(year)) {
        return (day <= 29);
    } else {
        return (day <= 28);
    }
}

void LogManager::setCaloricGoals() {
    textEdit->append("Setting caloric and macronutrient goals...");
    user.setCaloricGoal();
    user.calculateMacroGoals();
    textEdit->append("Goals set successfully.");
}

void LogManager::logFoodIntake() {
    textEdit->append("Logging food intake...");

    int month, day, year;
    assignDate(month, day, year, thisYear);

    int specificIndex = accessSpecificDayOfYear(month, day, year);
    Nutrition today(month, day, year);

    if (year == thisYear) {
        today = thisYearLog[specificIndex];
    } else if (year == thisYear - 1) {
        today = lastYearLog[specificIndex];
    } else {
        today = nextYearLog[specificIndex];
    }

    bool ok;
    int foodCount = QInputDialog::getInt(nullptr, "Food Intake", "How many food items do you want to log?", 1, 1, 100, 1, &ok);

    for (int i = 0; i < foodCount; ++i) {
        QString name = QInputDialog::getText(nullptr, "Enter Food", "Enter food name:", QLineEdit::Normal, "", &ok);
        float protein = QInputDialog::getDouble(nullptr, "Enter Protein", "Enter protein (g):", 0.0, 0.0, 1000.0, 2, &ok);
        float carbs = QInputDialog::getDouble(nullptr, "Enter Carbs", "Enter carbs (g):", 0.0, 0.0, 1000.0, 2, &ok);
        float fat = QInputDialog::getDouble(nullptr, "Enter Fat", "Enter fat (g):", 0.0, 0.0, 1000.0, 2, &ok);

        today.addFood(Food(name.toStdString(), protein, carbs, fat));
    }

    if (year == thisYear) {
        thisYearLog[specificIndex] = today;
    } else if (year == thisYear - 1) {
        lastYearLog[specificIndex] = today;
    } else {
        nextYearLog[specificIndex] = today;
    }


    textEdit->append("Food intake logged successfully.");
}

void LogManager::logExercise() {
    textEdit->append("Logging exercise...");

    int month;
    int day;
    int year;
    assignDate(month, day, year, thisYear);

    int specificIndex = accessSpecificDayOfYear(month, day, year);
    Nutrition today(month, day, year);

    if (year == thisYear - 1) {
        today = lastYearLog[specificIndex];
    }
    else if (year == thisYear) {
        today = thisYearLog[specificIndex];
    }
    else if (year == thisYear + 1) {
        today = nextYearLog[specificIndex];
    }

    bool ok;
    int exerciseCount = QInputDialog::getInt(nullptr, "Exercise Log", "How many exercises do you want to log?", 1, 1, 100, 1, &ok);

    for (int i = 0; i < exerciseCount; ++i) {
        QString name = QInputDialog::getText(nullptr, "Enter Exercise", "Enter exercise name:", QLineEdit::Normal, "", &ok);
        float duration = QInputDialog::getDouble(nullptr, "Enter Duration", "Enter duration (min):", 0.0, 0.0, 1000.0, 2, &ok);
        float caloriesBurned = QInputDialog::getDouble(nullptr, "Enter Calories Burned", "Enter calories burned:", 0.0, 0.0, 1000.0, 2, &ok);
        today.addExercise(Exercise(name.toStdString(), duration, caloriesBurned));
    }

    if (year == thisYear - 1) {
        lastYearLog[specificIndex] = today;
    } else if (year == thisYear) {
        thisYearLog[specificIndex] = today;
    } else if (year == thisYear + 1) {
        nextYearLog[specificIndex] = today;
    }

    textEdit->append("Exercise logged successfully.");
}

void LogManager::displaySummary() {
    textEdit->append("Viewing food and exercise summary...");

    int month;
    int day;
    int year;
    assignDate(month, day, year, thisYear);
    int specificIndex = accessSpecificDayOfYear(month, day, year);

    if (year == thisYear - 1) {
        lastYearLog[specificIndex].displaySummary();
    }
    else if (year == thisYear) {
        thisYearLog[specificIndex].displaySummary();
    }
    else if (year == thisYear + 1) {
        nextYearLog[specificIndex].displaySummary();
    }
}

void LogManager::displayProfile() {
    textEdit->append("Viewing user profile...");
    user.displayProfile();
}

void LogManager::editProfile() {
    textEdit->append("Editing user profile...");

    bool ok;
    int UserOption = QInputDialog::getInt(nullptr, "Edit Profile", "What part of your profile would you like to update?\n1. Weight\n2. Height\n3. Age\n4. Gender", 1, 1, 4, 1, &ok);

    if (!ok || (UserOption < 1) || (UserOption > 4)) {
        QMessageBox::warning(nullptr, "Invalid Input", "Please choose a valid option.");
        return;
    }

    switch (UserOption) {
    case 1:
        user.setWeight();
        break;
    case 2:
        user.setHeight();
        break;
    case 3:
        user.setAge();
        break;
    case 4:
        user.setGender();
        break;
    }

    textEdit->append("Profile edited successfully.");
}

void LogManager::exitApp() {
    textEdit->append("Exiting application...");
    QApplication::quit();
}



/*void LogManager::run() {
    time_t now = time(0);
    tm* tm_now = localtime(&now);
    thisYear = (tm_now->tm_year + 1900);

    vector<Nutrition> lastYearLog = createYearlyLog(thisYear - 1);
    vector<Nutrition> thisYearLog = createYearlyLog(thisYear);
    vector<Nutrition> nextYearLog = createYearlyLog(thisYear + 1);

    cout << "Welcome to the Fitness and Nutrition App!" << endl;
    cout << "This program will help you log your food intake and exercise." << endl;

    bool running = true;
    while (running) {
        cout << "\nMain Menu: " << endl;
        cout << "1. Set Caloric and Macronutrient Goals" << endl;
        cout << "2. Log Food Intake for a Specific Day" << endl;
        cout << "3. Log Exercise for a Specific Day" << endl;
        cout << "4. View Food and Exercise for a Specific Day" << endl;
        cout << "5. View User Profile" << endl;
        cout << "6. Edit User Profile" << endl;
        cout << "7. Exit" << endl;
        cout << "Choose an option: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                int caloricOption;
                cout << "Choose how to set your nutrition goals: " << endl;
                cout << "1. Set Caloric Goals Manually" << endl;
                cout << "2. Set Caloric Goals using BMR" << endl;
                cin >> caloricOption;

                do {
                    if (caloricOption == 1) {
                        user.setCaloricGoal();
                        user.calculateMacroGoals();
                        break;
                    }
                        else if (caloricOption == 2) {
                            user.setSpecificCaloricGoal();
                            user.calculateMacroGoals();
                            break;
                        }
                            else {
                                cout << "Invalid choice! Please try again." << endl;
                            }
                } while ((caloricOption != 1) && (caloricOption != 2));

                break;
            }
            case 2: {
                int month;
                int day;
                int year;
                assignDate(month, day, year, thisYear);

                int specificIndex = accessSpecificDayOfYear(month, day, year);
                Nutrition today(month, day, year);

                if (year == thisYear - 1) {
                    today = lastYearLog[specificIndex];
                    }
                        else if (year == thisYear) {
                            today = thisYearLog[specificIndex];
                        }
                            else if (year == thisYear + 1) {
                                today = nextYearLog[specificIndex];
                            }

                int foodCount;
                cout << "How many food items do you want to log? ";
                cin >> foodCount;
                for (int i = 0; i < foodCount; ++i) {
                    string name;
                    float protein, carbs, fat;
                    cout << "Enter food name: ";
                    cin >> name;
                    cout << "Enter protein (g): ";
                    cin >> protein;
                    cout << "Enter carbs (g): ";
                    cin >> carbs;
                    cout << "Enter fat (g): ";
                    cin >> fat;
                    today.addFood(Food(name, protein, carbs, fat));
                }

                if (year == thisYear - 1) {
                    lastYearLog[specificIndex] = today;
                    }
                        else if (year == thisYear) {
                            thisYearLog[specificIndex] = today;
                        }
                            else if (year == thisYear + 1) {
                                nextYearLog[specificIndex] = today;
                            }
                break;
            }
            case 3: {
                int month;
                int day;
                int year;
                assignDate(month, day, year, thisYear);

                int specificIndex = accessSpecificDayOfYear(month, day, year);
                Nutrition today(month, day, year);

                if (year == thisYear - 1) {
                    today = lastYearLog[specificIndex];
                    }
                        else if (year == thisYear) {
                            today = thisYearLog[specificIndex];
                        }
                            else if (year == thisYear + 1) {
                                today = nextYearLog[specificIndex];
                            }

                int exerciseCount;
                cout << "How many exercises do you want to log? ";
                cin >> exerciseCount;
                for (int i = 0; i < exerciseCount; ++i) {
                    string name;
                    float duration, caloriesBurned;
                    cout << "Enter exercise name: ";
                    cin >> name;
                    cout << "Enter duration (min): ";
                    cin >> duration;
                    cout << "Enter calories burned: ";
                    cin >> caloriesBurned;
                    today.addExercise(Exercise(name, duration, caloriesBurned));
                }

                 if (year == thisYear - 1) {
                    lastYearLog[specificIndex] = today;
                    }
                        else if (year == thisYear) {
                            thisYearLog[specificIndex] = today;
                        }
                            else if (year == thisYear + 1) {
                                nextYearLog[specificIndex] = today;
                            }
                break;
            }
            case 4:{
                int month;
                int day;
                int year;
                assignDate(month, day, year, thisYear);
                int specificIndex = accessSpecificDayOfYear(month, day, year);

                if (year == thisYear - 1) {
                    lastYearLog[specificIndex].displaySummary();
                    }
                        else if (year == thisYear) {
                            thisYearLog[specificIndex].displaySummary();
                        }
                            else if (year == thisYear + 1) {
                                nextYearLog[specificIndex].displaySummary();
                            }

                break;
            }
            case 5:{
                user.displayProfile();
                break;
            }
            case 6:{
                int UserOption;
                cout << "What part of your profile would you like to update? Enter the corresponding number: "<< endl;
                cout << "1. Weight" << endl;
                cout << "2. Height" << endl;
                cout << "3. Age" << endl;
                cout << "4. Gender" << endl;
                cin >> UserOption;

                do {
                    if (UserOption == 1) {
                            user.setWeight();
                            break;
                    }
                        else if (UserOption == 2) {
                            user.setHeight();
                            break;
                        }
                            else if (UserOption == 3) {
                                user.setAge();
                                break;
                            }
                                else if (UserOption == 4) {
                                    user.setGender();
                                    break;
                                }
                                    else {
                                        cout << "Invalid choice! Please try again." << endl;
                                    }
                } while ((UserOption < 1) || (UserOption > 5));
            }
            case 7:{
                running = false;
                break;
            }
            default:{
                cout << "Invalid choice! Please try again." << endl;
            }
        }
    }
}*/
