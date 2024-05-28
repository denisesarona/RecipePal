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