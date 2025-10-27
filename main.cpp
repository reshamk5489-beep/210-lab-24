#include <iostream>
#include <fstream>
#include <iomanip>
#include <set>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20; // Comment #1: Define constants for array sizes and max age.

// Comment #2: Function prototypes
int select_goat(set<Goat> trip);
void delete_goat(set<Goat> &trip);
void add_goat(set<Goat> &trip, string [], string []);
void display_trip(set<Goat> trip);
int main_menu();

int main() {
    srand(time(0));
    bool again;
    int choice;
    bool exit = false;
    set<Goat> trip; // Comment #3: List to hold Goat objects.
    
    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // Comment #4: Main loop for user interaction.
    while (exit == false)
    {
        choice = main_menu();
        switch(choice)
        {
            // Comment #5: Handle user choices.
            case 1:
                add_goat(trip, names, colors);
                break;
            case 2:
                delete_goat(trip);
                break;
            case 3:
                display_trip(trip);
                break;
            case 4:
                exit = true;
                break;
        }
    }

    return 0;
}

int main_menu()
{
    int choice;

    cout << "*** GOAT MANAGER 3001 ***" << endl;
    cout << "[1] Add a goat" << endl;
    cout << "[2] Delete a goat" << endl;
    cout << "[3] List goats" << endl;
    cout << "[4] Quit" << endl;
    cout << "Choice --> ";

    while(true)
    {
        cin >> choice;

        if (choice > 4 || choice < 1) // Comment #6: Validate user input.
        {
            cout << "Please enter a valid choice (between 1-4): ";
        }
        else
        {
            return choice;
        }
    }
    
    cout << endl;
}

void add_goat(set<Goat> &trip, string names[], string colors[])
{
    // Comment #7: Generate random name, color, and age.
    string name = names[rand() % SZ_NAMES];
    string color = colors[rand() % SZ_COLORS];
    int age = rand() % MAX_AGE;

    // Comment #8: Create a new Goat object and add it to the list.
    Goat goat(name, age, color);

    // Comment #9: Display added goat details.
    trip.insert(goat);
}

void display_trip(set<Goat> trip)
{
    int count = 1;
    for (auto goat : trip) // Comment #10: Iterate through the list and display each goat's details.
    {
        cout << "\t[" << count << "] " << goat.get_name() 
            << " (" << goat.get_age() << ", " << goat.get_color() 
            << ")" << endl;
        count++;
    }

    cout << endl;
}

int select_goat(set<Goat> trip)
{
    int choice;
    display_trip(trip); // Comment #11: Show the list of goats to choose from.

    if (trip.size() == 0) // Comment #12: Handle empty list case.
    {
        cout << "The goat list is empty. Nothing to select." << endl;
        return 0;
    }

    while(true)
    {
        cout << "Please choose a number to select a goat: ";

        cin >> choice;

        if (choice > trip.size() || choice < 1) // Comment #13: Validate selection.
        {
            cout << "Please enter a valid choice" << endl;
        }
        else
        {
            return choice;
        }
    } 
}

void delete_goat(set<Goat> &trip)
{
    int choice;
    int count = 1;
    choice = select_goat(trip); // Comment #14: Get the user's choice of goat to delete.
    auto it = trip.begin();
    while (it != trip.end()) // Comment #15: Iterate to find and remove the selected goat.
    {
        if (count == choice)
        {
            it = trip.erase(it); // Comment #16: Remove the goat from the list.
            return;
        }
        ++it;
        ++count;
    }
}
