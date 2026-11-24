// Challenge 7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <limits>
#include <cctype>

using namespace std;

// Weapon structure
struct Weapon
{
    string Name;
    int Price;
    int Damage;
    string Role;
    bool Purchased;
};

// Player structure
struct Player
{
    string Name;
    int WeaponIndex = -1;
};

// Function to get valid integer input
int GetNumber()
{
    int number;

    while (!(cin >> number))
    {
        cout << "[!] ERROR: Please enter a valid number: ";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return number;
}

// Function to display the shop
void DisplayShop(const vector<Weapon>& weapons, int coins)
{
    cout << "\n>> You currently have " << coins
        << " coins. You can buy the following items:\n";

    for (int i = 0; i < weapons.size(); i++)
    {
        cout << ">> " << i + 1 << ". "
            << weapons[i].Name
            << " [" << weapons[i].Price
            << " coins, " << weapons[i].Damage
            << " damage]\n";
    }
}

// Function to purchase a weapon
void PurchaseWeapon(
    Player& player,
    int playerNumber,
    vector<Weapon>& weapons,
    int& coins)
{
    while (true)
    {
        cout << "\n- Player " << playerNumber
            << ", Please enter a weapon to buy: ";

        int choice = GetNumber();

        // Check whether the selection is valid
        if (choice < 1 || choice > weapons.size())
        {
            cout << "[!] ERROR: Please choose a valid item number.\n";
            continue;
        }

        // Convert menu selection into vector index
        int index = choice - 1;

        // Check whether the weapon has already been purchased
        if (weapons[index].Purchased)
        {
            cout << "[!] ERROR: This weapon is unavailable "
                << "as it has already been purchased.\n";
            continue;
        }

        // Check whether the party has enough coins
        if (coins < weapons[index].Price)
        {
            cout << "[!] ERROR: Not enough coins. The "
                << weapons[index].Name << " is "
                << weapons[index].Price
                << " coins and there are only "
                << coins << " available!\n";

            continue;
        }

        // Complete the purchase
        coins -= weapons[index].Price;

        weapons[index].Purchased = true;

        player.WeaponIndex = index;

        cout << ">> " << player.Name
            << " bought a " << weapons[index].Name
            << " for " << weapons[index].Price
            << " coins. The party now has "
            << coins << " coins.\n";

        break;
    }
}

// Function to ask whether the players are happy
bool ConfirmSelection()
{
    string answer;

    while (true)
    {
        cout << "\n>> Are you happy with your selection "
            << "of weapons? (yes/no): ";

        cin >> answer;

        // Convert answer to lowercase
        for (char& c : answer)
        {
            c = static_cast<char>(
                tolower(static_cast<unsigned char>(c))
                );
        }

        if (answer == "yes")
        {
            return true;
        }
        else if (answer == "no")
        {
            return false;
        }

        cout << "[!] ERROR: Please enter yes or no.\n";
    }
}

// Function to display the final party
void DisplayParty(
    const array<Player, 3>& players,
    const vector<Weapon>& weapons)
{
    cout << "\n>> The party:\n";

    for (int i = 0; i < players.size(); i++)
    {
        const Weapon& weapon =
            weapons[players[i].WeaponIndex];

        cout << ">> - Player " << i + 1
            << " (" << players[i].Name << ")"
            << ", Role: " << weapon.Role
            << ", Weapon: " << weapon.Name
            << ", Damage: " << weapon.Damage
            << ".\n";
    }
}

// Main program
int main()
{
    // Create the three players
    array<Player, 3> players;

    // Ask players for their names
    for (int i = 0; i < players.size(); i++)
    {
        cout << "- Enter player #" << i + 1
            << "'s name: ";

        getline(cin, players[i].Name);
    }

    // Create the weapon catalogue
    vector<Weapon> weapons =
    {
        {"Great Sword", 40, 100, "Knight", false},
        {"Scimitar", 35, 75, "Knight", false},
        {"Dagger", 10, 35, "Knight", false},
        {"Longbow", 20, 55, "Archer", false},
        {"Crossbow", 40, 100, "Archer", false},
        {"Rusty spear", 10, 35, "Spearman", false},
        {"Iron spear", 20, 65, "Spearman", false}
    };

    bool finalSelection = false;

    // Repeat the shopping process until confirmed
    while (!finalSelection)
    {
        // Reset party currency
        int coins = 100;

        // Reset weapons and player selections
        for (Weapon& weapon : weapons)
        {
            weapon.Purchased = false;
        }

        for (Player& player : players)
        {
            player.WeaponIndex = -1;
        }

        // Welcome message
        cout << "\n>> Welcome "
            << players[0].Name << ", "
            << players[1].Name << " and "
            << players[2].Name
            << " to the shop!\n";

        // Display the shop
        DisplayShop(weapons, coins);

        // Allow each player to purchase a weapon
        for (int i = 0; i < players.size(); i++)
        {
            PurchaseWeapon(
                players[i],
                i + 1,
                weapons,
                coins
            );
        }

        // Confirm the party's selection
        finalSelection = ConfirmSelection();

        if (!finalSelection)
        {
            cout << "\n-----------------------------------\n";
        }
    }

    // Display the final party
    DisplayParty(players, weapons);

    // Opening game message
    cout << "\n>> You are situated in a forest. "
        << "A monster appears...\n";

    return 0;
}