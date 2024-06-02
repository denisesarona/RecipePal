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

Recipe recipes[100]; // ARRAY OF RECIPE STUCT TO STORE MANY RECIPES 
int opt = 0, count = 0;

// FUNCTION PROTOTYPES
void addRecipe();
void loadRecipe();
void saveRecipe();
void viewRecipe();
void searchRecipe();
void checkExistingRecipe();
void clearScreen();

int main()
{
    cout << ",------.              ,--.              ,------.         ,--. \n"
            "|  .--. ' ,---.  ,---.`--' ,---.  ,---. |  .--. ' ,--,--.|  | \n"
            "|  '--'.'| .-. :| .--',--.| .-. || .-. :|  '--' |' ,-.  ||  | \n"
            "|  |\\  \\ \\   --.\\ `--.|  || '-' '\\   --.|  | --' \\ '-'  ||  | \n"
            "`--' '--' `----' `---'`--'|  |-'  `----'`--'      `--`--'`--' \n"
            "                          `--'                                 \n";

    loadRecipe();
    while (true)
    {
        clearScreen();
        cout << "+---------------------------------------------------------+" << endl;
        cout << "|               Welcome to RecipePal!                     |" << endl;
        cout << "|        Organize your Recipes in an Instant              |" << endl;
        cout << "+---------------------------------------------------------+" << endl;
        cout << "| [1] Add a Recipe                                        |" << endl;
        cout << "| [2] Search for a Recipe                                 |" << endl;
        cout << "| [3] Check Existing Recipe                               |" << endl;
        cout << "| [4] Exit                                                |" << endl;
        cout << "+---------------------------------------------------------+" << endl;
        cout << endl;
        cout << "  Enter Option: ";
        cin >> opt;

        switch (opt)
        {
            case 1: addRecipe(); break;
            case 2: searchRecipe(); break;
            case 3: checkExistingRecipe(); break;
            case 4: exit(0); break;
            default: cout << "Invalid Input" << endl; break;
        }
    }
}

// SAVE RECIPES TO FILE
void saveRecipe() {
    // OPEN FILE STREAM FOR WRITING
    ofstream write("recipes.txt");

    // WRITE THE TOTAL COUNT OF RECIPE
    write << count << endl;

    // LOOP THROUGH EACH RECIPE
    for (int i = 0; i < count; i++) {
        // WRITE RECIPE NAME, NUMBER OF INGREDIENTS, AND INGREDIENTS 
        write << recipes[i].name << "|" << recipes[i].ingredients.size() << "|"; // .size RETURNS NUMBER OF ELEMENTS STORED IN VECTOR 
        for (size_t j = 0; j < recipes[i].ingredients.size(); j++) {
            write << recipes[i].ingredients[j] << "|";
        }

        // WRITE NUMBER OF PROCEDURE STEPS AND PROCEDURE 
        write << recipes[i].procedure.size() << "|";
        for (size_t j = 0; j < recipes[i].procedure.size(); j++) {
            write << recipes[i].procedure[j] << "|";
        }

        // WRITE COOKING TIME, DIFFICULTY LEVEL, AND CATEGORY 
        write << recipes[i].cooking_time << "|" << recipes[i].difficulty_level << "|" << recipes[i].category << endl;
    }

    // CLOSE THE FILE STREAM
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

void addRecipe()
{
    // IGNORE ANY PREVIOUS INPUT
    cin.ignore();
    clearScreen();
    cout << "+---------------------------------------------------------+" << endl;
    cout << "|                       Add Recipe                        |" << endl;
    cout << "+---------------------------------------------------------+" << endl;
    cout << endl;
    cout << "Enter Recipe Name: ";
    getline(cin, recipes[count].name);

    int ingredients_qty;
    cout << "Enter Quantity of Ingredients: ";
    cin >> ingredients_qty;
    cin.ignore();
    // RESIZE THE INGREDIENTS VECTOR
    recipes[count].ingredients.resize(ingredients_qty); // .resize changes size of the vector
    // PROMPT USER TO ENTER EACH INGREDIENT
    for (int i = 0; i < ingredients_qty; i++)
    {
        cout << "Enter Ingredient " << i + 1 << ": ";
        getline(cin, recipes[count].ingredients[i]);
    }

    int procedure_qty;
    cout << "Enter Number of Steps in Procedure: ";
    cin >> procedure_qty;
    cin.ignore();
    // RESIZE THE PROCEDURE VECTOR
    recipes[count].procedure.resize(procedure_qty);
    // PROMPT USER TO ENTER EACH PROCEDURE STEP
    for (int i = 0; i < procedure_qty; i++)
    {
        cout << "Enter Procedure Step " << i + 1 << ": ";
        getline(cin, recipes[count].procedure[i]);
    }

    cout << "Enter Cooking Time: ";
    getline(cin, recipes[count].cooking_time);
    cout << "Enter Difficulty Level: ";
    getline(cin, recipes[count].difficulty_level);
    cout << "Enter Category: ";
    getline(cin, recipes[count].category);

    // Increment count after successfully adding a recipe
    count++;

    cout << "\nRecipe Added Successfully!\n" << endl;
    saveRecipe();

    // Display the recently added recipe only
    cout << "+---------------------------------------------------------+" << endl;
    cout << "|                   View Recipe                           |" << endl;
    cout << "+---------------------------------------------------------+" << endl;
    cout << "Recipe Name: " << recipes[count - 1].name << endl; // Access the most recently added recipe
    cout << "Ingredients:" << endl;
    for (size_t j = 0; j < recipes[count - 1].ingredients.size(); j++)
    {
        cout << "  • " << recipes[count - 1].ingredients[j] << endl;
    }
    cout << "Instructions:" << endl;
    for (size_t j = 0; j < recipes[count - 1].procedure.size(); j++)
    {
        cout << "  • " << recipes[count - 1].procedure[j] << endl;
    }
    cout << "Cooking Time: " << recipes[count - 1].cooking_time << endl;
    cout << "Difficulty Level: " << recipes[count - 1].difficulty_level << endl;
    cout << "Category: " << recipes[count - 1].category << endl;
    cout << endl;

    cin.ignore();
    cin.get(); // Wait for user input
}



void checkExistingRecipe()
{
    loadRecipe();
    clearScreen();


	cout << "+---------------------------------------------------------+" << endl;
   	cout << "|                   Check Existing Recipe                 |" << endl;
    cout << "+---------------------------------------------------------+" << endl;
    
    cout<< endl;
    
    for (int i = 0; i < count; i++)
    {
    	cout << "---------- " << "Recipe No. " << i +1 << " ----------" <<endl;
        cout << "  Recipe Name: " << recipes[i].name << endl;
        cout << "  Ingredients:" << endl;
        for (size_t j = 0; j < recipes[i].ingredients.size(); j++)
        {
            cout << "    • " << recipes[i].ingredients[j] << endl;
        }
        cout << "  Instructions:" << endl;
        for (size_t j = 0; j < recipes[i].procedure.size(); j++)
        {
            cout << "    • " << recipes[i].procedure[j] << endl;
        }
        cout << "  Cooking Time: " << recipes[i].cooking_time << endl;
        cout << "  Difficulty Level: " << recipes[i].difficulty_level << endl;
        cout << "  Category: " << recipes[i].category << endl;
        cout << endl;
    }

    cin.ignore();
    cin.get(); // Wait for user input
}


// Search for a recipe by name
void searchRecipe()
{
    cin.ignore();
    clearScreen();
    cout << "+---------------------------------------------------------+" << endl;
    cout << "|                      Search Recipe                      |" << endl;
    cout << "+---------------------------------------------------------+" << endl;
    cout << endl;
    cout << "Enter Recipe Name to Search: ";
    string searchName;
    getline(cin, searchName);
    
    // VARIABLE TO TRACK IF THE RECIPE IS FOUND
    bool found = false;
    // LOOP THROUGH EACH RECIPE
    for (int i = 0; i < count; i++)
    {
    	// IF RECIPE NAME MATCHES THE SEARCH NAME
        if (recipes[i].name == searchName)
        {
        	// DISPLAY RECIPE DETAILS
            cout << "Recipe Found:\n";
            cout << "Name: " << recipes[i].name << endl;
            cout << "Ingredients: ";
            for (size_t j = 0; j < recipes[i].ingredients.size(); j++)
            {
                cout << recipes[i].ingredients[j] << (j < recipes[i].ingredients.size() - 1 ? ", " : "\n");
            }
            cout << "Procedure: ";
            for (size_t j = 0; j < recipes[i].procedure.size(); j++)
            {
                cout << recipes[i].procedure[j] << (j < recipes[i].procedure.size() - 1 ? ", " : "\n");
            }
            cout << "Cooking Time: " << recipes[i].cooking_time << endl;
            cout << "Difficulty Level: " << recipes[i].difficulty_level << endl;
            cout << "Category: " << recipes[i].category << endl;
            found = true;
            // EXIT LOOP SINCE RECIPE IS FOUND
            break;
        }
    }
    // IF RECIPE NOT FOUND
    if (!found)
    {
        cout << "Recipe not found!\n";
    }

    cin.get(); // Wait for user input
}

// Clear the console screen
void clearScreen()
{
    cout << "\033[2J\033[1;1H";
}
