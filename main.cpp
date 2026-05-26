#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <limits>
#include <string>

using namespace std;

const int MAX_CITIES = 100;
vector<string> cities;
int roadMatrix[MAX_CITIES][MAX_CITIES] = {0};
double budgetMatrix[MAX_CITIES][MAX_CITIES] = {0.0};

int getCityIndex(const string& name) {
    for (int i = 0; i < static_cast<int>(cities.size()); i++) {
        if (cities[i] == name) {
            return i;
        }
    }
    return -1;
}

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void addCities() {
    int n;
    cout << "Enter the number of cities to add: ";
    if (!(cin >> n) || n <= 0) {
        cout << "Invalid number. Please enter a positive integer.\n";
        clearInput();
        return;
    }
    clearInput();

    for (int i = 0; i < n; i++) {
        string name;
        cout << "Enter the name for city " << (cities.size() + 1) << ": ";
        getline(cin, name);
        if (name.empty()) {
            cout << "City name cannot be empty. Try again.\n";
            i--;
            continue;
        }
        if (getCityIndex(name) == -1) {
            cities.push_back(name);
            cout << "City added: " << name << "\n";
        } else {
            cout << "City '" << name << "' already exists. Skipping.\n";
        }
    }
}

void addRoad() {
    if (cities.size() < 2) {
        cout << "At least two cities are required to add a road.\n";
        return;
    }
    string c1, c2;
    cout << "Enter the name of the first city: ";
    getline(cin, c1);
    cout << "Enter the name of the second city: ";
    getline(cin, c2);

    int i = getCityIndex(c1);
    int j = getCityIndex(c2);
    if (i == -1 || j == -1) {
        cout << "One or both cities are invalid.\n";
        return;
    }
    if (i == j) {
        cout << "A city cannot have a road to itself.\n";
        return;
    }

    roadMatrix[i][j] = roadMatrix[j][i] = 1;
    cout << "Road added successfully between " << c1 << " and " << c2 << "\n";
}

void addBudget() {
    if (cities.size() < 2) {
        cout << "At least two cities are required to add a budget.\n";
        return;
    }
    string c1, c2;
    double budget;
    cout << "Enter the name of the first city: ";
    getline(cin, c1);
    cout << "Enter the name of the second city: ";
    getline(cin, c2);

    int i = getCityIndex(c1);
    int j = getCityIndex(c2);
    if (i == -1 || j == -1) {
        cout << "One or both cities are invalid.\n";
        return;
    }
    if (i == j) {
        cout << "A city cannot have a road budget to itself.\n";
        return;
    }
    if (roadMatrix[i][j] != 1) {
        cout << "No road exists between the given cities. Budget cannot be added.\n";
        return;
    }

    cout << "Enter the budget for the road: ";
    if (!(cin >> budget) || budget < 0.0) {
        cout << "Invalid budget. Please enter a non-negative number.\n";
        clearInput();
        return;
    }
    clearInput();

    budgetMatrix[i][j] = budgetMatrix[j][i] = budget;
    cout << "Budget added successfully for the road between " << c1 << " and " << c2 << "\n";
}

void editCity() {
    if (cities.empty()) {
        cout << "No cities recorded yet.\n";
        return;
    }
    int idx;
    cout << "Enter the index of the city to edit: ";
    if (!(cin >> idx)) {
        cout << "Invalid index.\n";
        clearInput();
        return;
    }
    clearInput();

    if (idx < 1 || idx > static_cast<int>(cities.size())) {
        cout << "Invalid index.\n";
        return;
    }
    string newName;
    cout << "Enter the new name for city: ";
    getline(cin, newName);
    if (newName.empty()) {
        cout << "City name cannot be empty.\n";
        return;
    }
    if (getCityIndex(newName) != -1) {
        cout << "A city with that name already exists.\n";
        return;
    }

    cities[idx - 1] = newName;
    cout << "City updated successfully.\n";
}

void searchCity() {
    if (cities.empty()) {
        cout << "No cities recorded yet.\n";
        return;
    }
    int idx;
    cout << "Enter the index of the city: ";
    if (!(cin >> idx)) {
        cout << "Invalid index.\n";
        clearInput();
        return;
    }
    clearInput();

    if (idx >= 1 && idx <= static_cast<int>(cities.size())) {
        cout << "City " << idx << ": " << cities[idx - 1] << "\n";
    } else {
        cout << "City not found.\n";
    }
}

void displayCities() {
    if (cities.empty()) {
        cout << "No cities recorded yet.\n";
        return;
    }
    cout << "Cities:\n";
    for (int i = 0; i < static_cast<int>(cities.size()); i++) {
        cout << (i + 1) << ". " << cities[i] << "\n";
    }
}

void displayRoads() {
    if (cities.empty()) {
        cout << "No cities recorded yet.\n";
        return;
    }
    displayCities();
    cout << "Roads adjacency matrix:\n";
    for (int i = 0; i < static_cast<int>(cities.size()); i++) {
        for (int j = 0; j < static_cast<int>(cities.size()); j++) {
            cout << roadMatrix[i][j];
            if (j < static_cast<int>(cities.size()) - 1) cout << " ";
        }
        cout << "\n";
    }
}

void displayAllData() {
    if (cities.empty()) {
        cout << "No cities recorded yet.\n";
        return;
    }
    displayCities();
    cout << "\nRoad adjacency matrix:\n";
    for (int i = 0; i < static_cast<int>(cities.size()); i++) {
        for (int j = 0; j < static_cast<int>(cities.size()); j++) {
            cout << roadMatrix[i][j];
            if (j < static_cast<int>(cities.size()) - 1) cout << " ";
        }
        cout << "\n";
    }
    cout << "\nBudget adjacency matrix:\n";
    cout << fixed << setprecision(2);
    for (int i = 0; i < static_cast<int>(cities.size()); i++) {
        for (int j = 0; j < static_cast<int>(cities.size()); j++) {
            cout << budgetMatrix[i][j];
            if (j < static_cast<int>(cities.size()) - 1) cout << "  ";
        }
        cout << "\n";
    }
}

void saveToFile() {
    ofstream citiesFile("cities.txt");
    if (citiesFile.is_open()) {
        citiesFile << "Index  City_Name\n";
        for (int i = 0; i < static_cast<int>(cities.size()); i++) {
            citiesFile << (i + 1) << "   " << cities[i] << "\n";
        }
        citiesFile.close();
    }

    ofstream roadsFile("roads.txt");
    if (roadsFile.is_open()) {
        roadsFile << "Nbr  Road" << string(12, ' ') << "Budget\n";
        int count = 1;
        for (int i = 0; i < static_cast<int>(cities.size()); i++) {
            for (int j = i + 1; j < static_cast<int>(cities.size()); j++) {
                if (roadMatrix[i][j] == 1) {
                    string roadLabel = cities[i] + "-" + cities[j];
                    roadsFile << count << ".  " << left << setw(20) << roadLabel
                              << fixed << setprecision(2) << budgetMatrix[i][j] << "\n";
                    count++;
                }
            }
        }
        roadsFile.close();
    }
}

int main() {
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add new city(ies)\n";
        cout << "2. Add roads between cities\n";
        cout << "3. Add the budget for roads\n";
        cout << "4. Edit city\n";
        cout << "5. Search for a city using its index\n";
        cout << "6. Display cities\n";
        cout << "7. Display roads\n";
        cout << "8. Display recorded data on console\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        if (!(cin >> choice)) {
            cout << "Invalid choice. Please enter a number between 1 and 9.\n";
            clearInput();
            continue;
        }
        clearInput();

        switch (choice) {
            case 1:
                addCities();
                break;
            case 2:
                addRoad();
                break;
            case 3:
                addBudget();
                break;
            case 4:
                editCity();
                break;
            case 5:
                searchCity();
                break;
            case 6:
                displayCities();
                break;
            case 7:
                displayRoads();
                break;
            case 8:
                displayAllData();
                break;
            case 9:
                saveToFile();
                cout << "Exiting program... Data saved to cities.txt and roads.txt.\n";
                return 0;
            default:
                cout << "Invalid choice! Please select a valid menu option.\n";
                break;
        }
    }

    return 0;
}
