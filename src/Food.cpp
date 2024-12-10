#include "Food.h"

// Constructor to initialize the food item with given values
Food::Food(string name, float protein, float carbs, float fat)
    : name(name), protein(protein), carbs(carbs), fat(fat) {}

// Calculate the total calories based on macronutrient values
float Food::getCalories() const {
    return (protein * 4) + (carbs * 4) + (fat * 9);  // 4 kcal/g for protein and carbs, 9 kcal/g for fat
}
