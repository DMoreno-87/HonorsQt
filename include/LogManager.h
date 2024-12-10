#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <vector>
#include <ctime>
#include <QTextEdit>
#include "Nutrition.h"
#include "User.h"


class LogManager {
public:
    User user;
    LogManager(QTextEdit *textEdit);
    QTextEdit *textEdit;
    int thisYear = 0;
    vector<Nutrition> lastYearLog;
    vector<Nutrition> thisYearLog;
    vector<Nutrition> nextYearLog;

    bool isLeapYear(int year);
    bool isValidDayForMonth(int month, int day, int year);
    vector<Nutrition> createYearlyLog(int year);
    int accessSpecificDayOfYear(int month, int day, int year);
    void assignDate(int& month, int& day, int& year, int thisYear);
    void setCaloricGoals();
    void logFoodIntake();
    void logExercise();
    void displaySummary();
    void displayProfile();
    void editProfile();
    void exitApp();
    //void run();
};

#endif //LOGMANAGER_H
