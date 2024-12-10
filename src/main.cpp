#include <iostream>
#include <vector>
#include <ctime>
#include "User.h"
#include "Nutrition.h"
#include "Food.h"
#include "Exercise.h"
#include "LogManager.h"

using namespace std;

int main() {

    LogManager logManager;
    logManager.run();

    return 0;
}
