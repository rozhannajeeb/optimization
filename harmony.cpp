#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;
// Define the optimization problem (minimization)
double objectiveFunction(const vector<double>& solution) {
// Example objective function: Sphere function
double sum = 0.0;
for (double value : solution) {
sum += value * value;
}
return sum;
}
// Harmony Search parameters
const int numOfHarmonies = 10;
const int numOfVariables = 5;
const int maxIterations = 1000;
const double harmonyMemoryConsiderationRate = 0.95;
const double pitchAdjustingRate = 0.7;
// Harmony Search algorithm
vector<double> harmonySearch() {
// Initialize random number generator
srand(static_cast<unsigned>(time(nullptr)));
// Initialize harmony memory
vector<vector<double>> harmonyMemory(numOfHarmonies, vector<double>(numOfVariables));
for (int i = 0; i < numOfHarmonies; ++i) {
for (int j = 0; j < numOfVariables; ++j) {
harmonyMemory[i][j] = (rand() % 2000 - 1000) / 100.0; // Random values between -10 and 10
}
}
// Main loop
for (int iteration = 0; iteration < maxIterations; ++iteration) {
// Generate new harmony
vector<double> newHarmony(numOfVariables);
for (int i = 0; i < numOfVariables; ++i) {
double randValue = static_cast<double>(rand()) / RAND_MAX;
if (randValue < harmonyMemoryConsiderationRate) {
// Memory consideration
int index = rand() % numOfHarmonies;
newHarmony[i] = harmonyMemory[index][i];
} else {
// Random selection
newHarmony[i] = (rand() % 2000 - 1000) / 100.0;
}
// Pitch adjusting
randValue = static_cast<double>(rand()) / RAND_MAX;
if (randValue < pitchAdjustingRate) {
double pitchAdjustment = (rand() % 2000 - 1000) / 100.0;
newHarmony[i] += pitchAdjustment;
}
}
// Update harmony memory
double newHarmonyValue = objectiveFunction(newHarmony);
for (int i = 0; i < numOfHarmonies; ++i) {
double currentValue = objectiveFunction(harmonyMemory[i]);
if (newHarmonyValue < currentValue) {
harmonyMemory[i] = newHarmony;
break; // Only update one harmony per iteration
}
}
}
// Find the best solution in the final harmony memory
double bestValue = numeric_limits<double>::max();
vector<double> bestSolution(numOfVariables);
for (int i = 0; i < numOfHarmonies; ++i) {
double currentValue = objectiveFunction(harmonyMemory[i]);
if (currentValue < bestValue) {
bestValue = currentValue;
bestSolution = harmonyMemory[i];
}
}
return bestSolution;
}
int main() {
// Run Harmony Search algorithm
vector<double> result = harmonySearch();
// Print the result
cout << "Optimal Solution: ";
for (double value : result) {
cout << value << " ";
}
cout << endl;
cout << "Objective Function Value: " << objectiveFunction(result) << endl;
return 0;
}
