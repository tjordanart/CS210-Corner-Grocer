
/*
 * Author: Tyler Jordan
 * Course: CS-210
 * Project: Project Three - Corner Grocer
 * Description: A C++ program that tracks grocery item
 *              purchase frequencies and creates a backup file.
 * Date: October 10, 2026
 */

#include <iostream>  // Allows us to display text and get user input.
#include <fstream>   // Allows us to read and write files.
#include <string>    // Allows us to work with text.
#include <map>       // Stores each grocery item and its frequency.

using namespace std;

// The Grocer class manages grocery items and their frequencies.
class Grocer {
private:
    // Stores each grocery item and how many times it appears.
    map<string, int> itemFrequencies;

public:
    // Read the grocery file and count each item's occurrences.
    void LoadData(string fileName);

    // Display every grocery item and its purchase frequency.
    void PrintFrequencies();

    // Display each grocery item as a histogram.
    void PrintHistogram();

    // Return the frequency of a specific item.
    int GetFrequency(string itemName);

    // Save grocery item frequencies to a backup file.
    void SaveData(string fileName);
};

// Read the grocery file and count each item's occurrences.
void Grocer::LoadData(string fileName) {
    // Open the grocery input file.
    ifstream inputFile(fileName);

    // Stop if the file could not be opened.
    if (!inputFile.is_open()) {
        cout << "Error: Could not open " << fileName << endl;
        return;
    }

    string item;

    // Read one grocery item at a time until the file ends.
    while (getline(inputFile, item)) {
        // Increase the count for this item.
        itemFrequencies[item]++;
    }

    // Close the file after reading all items.
    inputFile.close();
}

// Display every grocery item and its purchase frequency.
void Grocer::PrintFrequencies() {
    // Go through each item stored in the map.
    for (const auto& item : itemFrequencies) {
        // Display the item name and its count.
        cout << item.first << " " << item.second << endl;
    }
}

// Display each grocery item as a histogram.
void Grocer::PrintHistogram() {
    // Go through every grocery item.
    for (const auto& item : itemFrequencies) {
        // Print the item name.
        cout << item.first << " ";

        // Print one asterisk for each purchase.
        for (int i = 0; i < item.second; i++) {
            cout << "*";
        }

        // Move to the next line.
        cout << endl;
    }
}

// Return how many times a grocery item appears.
int Grocer::GetFrequency(string itemName) {
    // Search for the item in the map.
    auto item = itemFrequencies.find(itemName);

    // Return its frequency if the item exists.
    if (item != itemFrequencies.end()) {
        return item->second;
    }

    // Return zero if the item was not found.
    return 0;
}

// Save grocery item frequencies to a backup file.
void Grocer::SaveData(string fileName) {
    // Create the backup file for writing.
    ofstream outputFile(fileName);

    // Stop if the backup file cannot be created.
    if (!outputFile.is_open()) {
        cout << "Error: Could not create " << fileName << endl;
        return;
    }

    // Write each grocery item and its frequency to the file.
    for (const auto& item : itemFrequencies) {
        outputFile << item.first << " " << item.second << endl;
    }

    // Close the backup file.
    outputFile.close();
}

int main() {
    // Create the grocery tracker.
    Grocer myGrocer;

    // Load the grocery data.
    myGrocer.LoadData("CS210_Project_Three_Input_File.txt");

    // Automatically create the backup file.
    myGrocer.SaveData("frequency.dat");

    string itemName;
    int choice;

    // Repeat the menu until the user selects Exit.
    do {
        cout << "\nCorner Grocer Inventory Tracker" << endl;
        cout << "1. Search for an item" << endl;
        cout << "2. Display all item frequencies" << endl;
        cout << "3. Display histogram" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";

        // Read and validate the user's menu choice.
        if (!(cin >> choice)) {
            // Clear the input error.
            cin.clear();

            // Remove invalid input from the input buffer.
            cin.ignore(10000, '\n');

            // Set an invalid choice so the menu repeats.
            choice = 0;
        }

        // Handle Menu Option 1.
        if (choice == 1) {
            cout << "Enter the item to search for: ";

            // Read the item name, including any spaces.
            getline(cin >> ws, itemName);

            // Display the item's purchase frequency.
            cout << itemName << " was purchased "
                << myGrocer.GetFrequency(itemName)
                << " time(s)." << endl;
        }
        // Handle Menu Option 2.
        else if (choice == 2) {
            myGrocer.PrintFrequencies();
        }
        // Handle Menu Option 3.
        else if (choice == 3) {
            myGrocer.PrintHistogram();
        }
        // Handle Menu Option 4.
        else if (choice == 4) {
            cout << "Goodbye!" << endl;
        }
        // Handle invalid menu choices.
        else {
            cout << "Invalid choice. Please select 1-4." << endl;
        }

    } while (choice != 4);

    return 0;
}
