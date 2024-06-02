#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Recipe
{
    string name;
    vector<string> ingredients;
    vector<string> procedure;
    string cooking_time;
    string difficulty_level;
    string category;
};

Recipe recipes[100]; // Array of Recipe struct to store multiple recipes
int opt = 0, count = 0;

void saveRecipes();
void loadRecipes();
void clearScreen();
void viewRecipes();

int main()
{
    cout << ",------.              ,--.              ,------.         ,--. \n"
            "|  .--. ' ,---.  ,---.`--' ,---.  ,---. |  .--. ' ,--,--.|  | \n"
            "|  '--'.'| .-. :| .--',--.| .-. || .-. :|  '--' |' ,-.  ||  | \n"
            "|  |\\  \\ \\   --.\\ `--.|  || '-' '\\   --.|  | --' \\ '-'  ||  | \n"
            "`--' '--' `----' `---'`--'|  |-'  `----'`--'      `--`--'`--' \n"
            "                          `--'                                 \n";

    loadRecipes();
    while (true)
    {
        clearScreen();
        cout << "+---------------------------------------------------------+" << endl;
        cout << "|               Welcome to RecipePal!                     |" << endl;
        cout << "|        Organize your Recipes in an Instant              |" << endl;
        cout << "+---------------------------------------------------------+" << endl;
        cout << "| [1] Add a Recipe                                        |" << endl;
        cout << "| [2] Update a Recipe                                     |" << endl;
        cout << "| [3] Search for a Recipe                                 |" << endl;
        cout << "| [4] Delete a Recipe                                     |" << endl;
        cout << "| [5] Check the Existing Recipes                          |" << endl;
        cout << "| [6] Exit                                                |" << endl;
        cout << "+---------------------------------------------------------+" << endl;
        cout << endl;
        cout << "  Enter Option: ";
        cin >> opt;

        switch (opt)
        {
            case 1: addRecipe(); break;
            case 2: updateRecipe(); break;
            case 3: searchRecipe(); break;
            case 4: deleteRecipe(); break;
            case 5: viewRecipes(); break;
            case 6: exit(0); break;
            default: cout << "Invalid Input" << endl; break;
        }
    }
}

void saveRecipes()
{
    ofstream write("recipes.txt");
    write << count << endl;
    for (int i = 0; i < count; i++)
    {
        write << recipes[i].name << "," << recipes[i].ingredients.size() << ",";
        for (size_t j = 0; j < recipes[i].ingredients.size(); j++)
        {
            write << recipes[i].ingredients[j] << ",";
        }
        write << recipes[i].procedure.size() << ",";
        for (size_t j = 0; j < recipes[i].procedure.size(); j++)
        {
            write << recipes[i].procedure[j] << ",";
        }
        write << recipes[i].cooking_time << "," << recipes[i].difficulty_level << "," << recipes[i].category << endl;
    }
    write.close();
}

// LOAD RECIPES FROM FILE
void loadRecipe() {
    // OPEN FILE STREAM FOR READING
    ifstream read("recipes.txt");

    // CHECK IF FILE IS OPEN 
    if (read.is_open()) {
        // READ THE TOTAL COUNT OF RECIPES 
        read >> count;
        read.ignore();

        // LOOP THROUGH EACH RECIPES
        for (int i = 0; i < count; i++) {
            // READ RECIPE NAME
            getline(read, recipes[i].name, '|');

            int ingredients_qty;
            read >> ingredients_qty;
            read.ignore();
            // RESIZE INGREDIENTS QTY VECTOR
            recipes[i].ingredients.resize(ingredients_qty);

            // READ INGREDIENTS
            for (int j = 0; j < ingredients_qty; j++) {
                getline(read, recipes[i].ingredients[j], '|');
            }

            int procedure_qty;
            read >> procedure_qty;
            read.ignore(); // IGNORE ANY REMAINING CHARACTERS 
            // RESIZE PROCEDURE QTY VECTOR
            recipes[i].procedure.resize(procedure_qty);

            for (int j = 0; j < procedure_qty; j++) { // READ PROCEDURE
                getline(read, recipes[i].procedure[j], '|');
            }

            // READ COOKING TIME, DIFFICULTY LEVEL AND CATEGORY
            getline(read, recipes[i].cooking_time, '|');
            getline(read, recipes[i].difficulty_level, '|');
            getline(read, recipes[i].category);
        }

        // CLOSE THE FILE STREAM
        read.close();
    }
}

void clearScreen(){
    cout << "\033[2J\033[1;1H";
}

void viewRecipes()
{
    loadRecipes();
    clearScreen();

    for (int i = 0; i < count; i++)
    {
        cout << "+---------------------------------------------------------+" << endl;
        cout << "|                       View Recipe                       |" << endl;
        cout << "+---------------------------------------------------------+" << endl;
        cout << "| Recipe Name: " << recipes[i].name;
        cout << string(49 - recipes[i].name.length(), ' ') << "|" << endl;
        cout << "|---------------------------------------------------------|" << endl;
        cout << "| Ingredients:                                            |" << endl;
        for (size_t j = 0; j < recipes[i].ingredients.size(); j++)
        {
            cout << "| • " << recipes[i].ingredients[j];
            cout << string(55 - recipes[i].ingredients[j].length(), ' ') << "|" << endl;
        }
        cout << "|---------------------------------------------------------|" << endl;
        cout << "| Instructions:                                           |" << endl;
        for (size_t j = 0; j < recipes[i].procedure.size(); j++)
        {
            cout << "| • " << recipes[i].procedure[j];
            cout << string(55 - recipes[i].procedure[j].length(), ' ') << "|" << endl;
        }
        cout << "|---------------------------------------------------------|" << endl;
        cout << "| Cooking Time: " << recipes[i].cooking_time;
        cout << string(49 - recipes[i].cooking_time.length(), ' ') << "|" << endl;
        cout << "| Difficulty Level: " << recipes[i].difficulty_level;
        cout << string(41 - recipes[i].difficulty_level.length(), ' ') << "|" << endl;
        cout << "| Category: " << recipes[i].category;
        cout << string(49 - recipes[i].category.length(), ' ') << "|" << endl;
        cout << "+---------------------------------------------------------+" << endl;
        cout << endl;
    }
    
    cin.ignore();
    cin.get(); // Wait for user  input
}
