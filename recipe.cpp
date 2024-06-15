#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <vector>
#include <cctype>

using namespace std;

// FUNCTION PROTOTYPES
void addRecipe();
void addRecipeItems();
void loadRecipe();
void saveRecipe();
void searchRecipe();
void checkExistingRecipe();
void clearScreen();
void updateRecipe();
void updateRecipeItems(int num, int count);
void viewRecipe(int recipeNumber);
void deleteRecipe();
void header();
string levelChecker();
string categoryChecker();
int ingredientQtyChecker();
int instructionQtyChecker();
struct Ingredient {
    string name;
    string unit;
};

struct Recipe {
    string name;
    vector<Ingredient> ingredients;
    vector<string> instruction;
    string cooking_time;
    string difficulty_level;
    string category;
};

Recipe recipes[100]; // ARRAY OF RECIPE STRUCT TO STORE MANY RECIPES 
int opt = 0, count = 0;

int main()
{    
    header();
    loadRecipe();
    clearScreen();
    while (true)
    {
        clearScreen();
        cout << ",------.              ,--.              ,------.         ,--. \n"
            "|  .--. ' ,---.  ,---.`--' ,---.  ,---. |  .--. ' ,--,--.|  | \n"
            "|  '--'.'| .-. :| .--',--.| .-. || .-. :|  '--' |' ,-.  ||  | \n"
            "|  |\\  \\ \\   --.\\ `--.|  || '-' '\\   --.|  | --' \\ '-'  ||  | \n"
            "`--' '--' `----' `---'`--'|  |-'  `----'`--'      `--`--'`--' \n"
            "                          `--'                                 \n";
        cout<<endl;
        cout << "\033[48;2;255;255;255m";
    
    // Set text color to black
        cout << "\033[30m";
        cout << "                                                           " << endl;
        cout << "                Welcome to RecipePal!                      " << endl;
        cout << "         Organize your Recipes in an Instant               " << endl;
        cout << "                                                           " << endl;
        cout << "  [1] Add a Recipe                                         " << endl;
        cout << "  [2] Search for a Recipe                                  " << endl;
        cout << "  [3] Update a Recipe                                      " << endl;
        cout << "  [4] Check Existing Recipe                                " << endl;
        cout << "  [5] Delete Recipe                                        " << endl;
        cout << "  [6] Exit                                                 " << endl;
        cout << "                                                           \033[0m" << endl;
        cout << endl;
        cout << "  Enter Option: ";
        cin>> opt;

        switch (opt)
        {
            case 1: 
                addRecipe(); 
                break;
            case 2: 
                searchRecipe(); 
                break;
            case 3: 
                updateRecipe(); 
                break;
            case 4: 
                checkExistingRecipe(); 
                break;
            case 5: 
                deleteRecipe();
                break;
            case 6: 
                cout<<"  Exiting the program..."<<endl;
                exit(0); // Exit the program
            default: 
                cout<<endl;
                cout<<"\033[97m"; 
                cout<<"\033[41m";
                cout<<"                                                           "<<endl;
                cout<<"                      Invalid Choice!                      "<<endl;
                cout<<"                                                           \033[0m"<<endl;
                cout<<endl;
                cout<<"  Exiting the program..."<<endl;
                exit(1);
        }
    }
}

void header()
{
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout << "\033[32m";
	cout << "                                                                    @@@@+     :=*%\n";
    cout << "                  @@@@@@@@@@@@@     @@@@@@@@@@.                    @@@@#  +@@@@@@@@@@@   @@@@@@@@@@+\n";
    cout << "                  @@@@@@@@@@@@@@    @@@@@@@@@@          @@@@@@@@          +@@@*   .@@@@  @@@@@@@@@@\n";
    cout << "                  @@@@+:::.@@@@@@   @@@@@%            @@@@@@@@@@   @@@@   *@@@-    @@@@  @@@@@@\n";
    cout << "                  @@@@      @@@@@   @@@@@#          +@@@@@@@@      @@@@*  *@@@=    @@@@  @@@@@@\n";
    cout << "                  @@@@     -@@@@-   @@@@@@@@@       @@@@@@         @@@@#  +@@@@.+@@@@@   @@@@@@@@@\n";
    cout << "                  @@@@  .@@@@@@     @@@@@@@@@#      @@@@@          @@@@%  +@@@@@@@@      @@@@@@@@@@\n";
    cout << "                  @@@@@@@@@@@@%     %@@@@@          @@@@           @@@@#  =@@@@+         @@@@@@\n";
    cout << "                  @@@@@@@@@@@@@     *@@@@@         =@@@@@          @@@@*  -@@@@          @@@@@@\n";
    cout << "                  @@@@@   @@@@@@    -@@@@@          @@@@@@@@@%-    @@@@*  :@@@%          @@@@@@\n";
    cout << "                  @@@@@     @@@@@     @@@@@@@@@@@%    +@@@@@@@@@:   @@@@*  :@@@*          @@@@@@@@@@*\n";
    cout << "                  @@@@@      @@@@@    @@@@@@@@@@%        @@@@@@@    @@@@*  .@@@+          *@@@@@@@@@\n";
    cout << "                             @@\n";
    cout << "\033[0m";
	cout<<endl;
	cout<<endl;
    cout << "                                      @@@@@@@@@\n";
    cout << "                                      @@@@@@@@@@@@      @@@@@@         @@@@@:\n";
    cout << "                                      @@@@     @@@-    +@@@@@@.        @@@@@\n";
    cout << "                                      @@@@     @@@@    @@@@@@@@        @@@@@\n";
    cout << "                                      @@@@    @@@@     @@@@ @@@@       @@@@@\n";
    cout << "                                      @@@@@@@@@@      @@@@@  @@@@      %@@@@\n";
    cout << "                                      @@@@@@@         @@@@@  @@@@@     *@@@@\n";
    cout << "                                      @@@@+          :@@@@@@@@@@@@-    +@@@@\n";
    cout << "                                      @@@@:          @@@@@@@@%*@@@@    +@@@@\n";
    cout << "                                      @@@@.          @@@@       @@@@   *@@@@@@@@@@@\n";
    cout << "                                      @@@@           @@@@       -@@@.  %@@@@@@@@@@@\n";
    cout << "                                       *@@           -+%               =@@@@@@@@@@@\n";

    cin.get();
}

void saveRecipe() 
{
    // OPEN FILE STREAM FOR WRITING
    ofstream write("recipes.txt");

    if (!write.is_open()) {
        cout << "Unable to open file!" << endl;
        return;
    }

    // WRITE THE TOTAL COUNT OF RECIPES
    write << count << endl;

    // LOOP THROUGH EACH RECIPE
    for (int i = 0; i < count; i++) 
    {
        // WRITE RECIPE NAME
        write << recipes[i].name << "|";

        // WRITE NUMBER OF INGREDIENTS
        write << recipes[i].ingredients.size() << "|";

        // WRITE EACH INGREDIENT
        for (size_t j = 0; j < recipes[i].ingredients.size(); j++) 
        {
            write << recipes[i].ingredients[j].name << "|";
            write << recipes[i].ingredients[j].unit << "|";
        }

        // WRITE NUMBER OF instruction STEPS
        write << recipes[i].instruction.size() << "|";

        // WRITE EACH instruction STEP
        for (size_t j = 0; j < recipes[i].instruction.size(); j++) 
        {
            write << recipes[i].instruction[j] << "|";
        }

        // WRITE COOKING TIME, DIFFICULTY LEVEL, AND CATEGORY
        write << recipes[i].cooking_time << "|";
        write << recipes[i].difficulty_level << "|";
        write << recipes[i].category << endl;
    }

    // CLOSE THE FILE STREAM
    write.close();
}

void loadRecipe() 
{
    // OPEN FILE STREAM FOR READING
    ifstream read("recipes.txt");

    if (!read.is_open()) {
        cout << "Unable to open file!" << endl;
        return;
    }

    // READ THE TOTAL COUNT OF RECIPES
    read >> count;
    read.ignore(); // Ignore the newline character left by '>>'

    // LOOP THROUGH EACH RECIPE
    for (int i = 0; i < count; i++) 
    {
        // READ RECIPE NAME
        getline(read, recipes[i].name, '|');

        // READ NUMBER OF INGREDIENTS
        int ingredients_qty;
        read >> ingredients_qty;
        read.ignore(); // Ignore the '|' character
        recipes[i].ingredients.resize(ingredients_qty);

        // READ EACH INGREDIENT
        for (int j = 0; j < ingredients_qty; j++) 
        {
            getline(read, recipes[i].ingredients[j].name, '|');
            getline(read, recipes[i].ingredients[j].unit, '|');
        }

        // READ NUMBER OF instruction STEPS
        int instruction_qty;
        read >> instruction_qty;
        read.ignore(); // Ignore the '|' character
        recipes[i].instruction.resize(instruction_qty);

        // READ EACH instruction STEP
        for (int j = 0; j < instruction_qty; j++) 
        {
            getline(read, recipes[i].instruction[j], '|');
        }

        // READ COOKING TIME, DIFFICULTY LEVEL, AND CATEGORY
        getline(read, recipes[i].cooking_time, '|');
        getline(read, recipes[i].difficulty_level, '|');
        getline(read, recipes[i].category);
    }

    // CLOSE THE FILE STREAM
    read.close();
}

int ingredientQtyChecker() 
{
    int ingredients_qty;
    bool validInput = false;

    while (!validInput) {
        cout << "  No. of Ingredients: ";
        cin >> ingredients_qty;
 
        if (cin.fail() || ingredients_qty <= 0) {
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "\033[97m\033[41m"; // White text, red background
            cout << "\n                                                           ";
            cout << "\n           Invalid input for Ingredients Quantity!         ";
            cout << "\n                                                           \033[0m";
            cout<<endl;
            cout<<endl;
        } else {
            validInput = true;
        }
    }

    cin.ignore(); // Clear the newline character left in the buffer
    return ingredients_qty;
}

int instructionQtyChecker() 
{
    int instruction_qty;
    bool validInput = false;

    while (!validInput) {
        cout << "  No. of Instruction Steps: ";
        cin >> instruction_qty;

        if (cin.fail() || instruction_qty <= 0) {
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "\033[97m\033[41m"; // White text, red background
            cout << "\n                                                           ";
            cout << "\n       Invalid input for Instruction Steps Quantity!       ";
            cout << "\n                                                           \033[0m";
            cout<<endl;
            cout<<endl;
        } else {
            validInput = true;
        }
    }

    cin.ignore(); // Clear the newline character left in the buffer
    return instruction_qty;
}

string levelChecker() 
{
    string difficulty;
    bool validInput = false;

    while (!validInput) {
        cout << "  Difficulty Level:" << endl;
        cout << "    [1] Easy" << endl;
        cout << "    [2] Medium" << endl;
        cout << "    [3] Hard" << endl;
        cout << "  Enter an Option (1, 2, 3): ";
        cin>>difficulty;

        // Check if the input matches valid choices
        if (difficulty == "1") {
            difficulty = "Easy";
            validInput = true;
        } else if (difficulty == "2") {
            difficulty = "Medium";
            validInput = true;
        } else if (difficulty == "3") {
            difficulty = "Hard";
            validInput = true;
        } else {
            cout << "\033[97m\033[41m"; // White text, red background
            cout << "\n                                                            ";
            cout << "\n           Invalid difficulty level! Please retry.          ";
            cout << "\n                                                            \033[0m";
            cout<<endl;
            cout<<endl;
        }
    }

    return difficulty;
}

string categoryChecker() 
{
    string category;
    bool validInput = false;

    while (!validInput) {
        cout << "  Category: "<<endl;
        cout << "    [1] Breakfast" << endl;
        cout << "    [2] Lunch" << endl;
        cout << "    [3] Dinner" << endl;
        cout << "  Enter an Option (1, 2, 3): ";
        cin>>category;

        // Check if the input matches valid choices
        if (category == "1") {
            category = "Breakfast";
            validInput = true;
        } else if (category == "2") {
            category = "Lunch";
            validInput = true;
        } else if (category == "3") {
            category = "Dinner";
            validInput = true;
        } else {
            cout<<"\033[97m\033[41m"; // White text, red background
            cout<<"\n                                                           ";
            cout<<"\n              Invalid category! Please retry.              ";
            cout<<"\n                                                           \033[0m";
            cout<<endl;
            cout<<endl;
        }
    }

    return category;
}

void addRecipe() 
{
    clearScreen();
    cout << "\033[46m"; // Set magenta background
    cout << "\033[97m"; // Set text color to white
    cout << "                                                           " << endl;
    cout<< "                        Add Recipe                         " << endl;
    cout << "                                                           \033[0m" << endl;
    cout << endl;

    // Call function to add recipe items
    addRecipeItems();

    cout << endl; 
    cout << "\033[97m\033[42m";
    cout << "                                                           " << endl;
    cout << "                Recipe Added Successfully!                 " << endl;
    cout << "                                                           \033[0m" << endl;
    cout<<endl;

    cout << "Press Enter to continue...\a";
    cin.ignore(); // Wait for user to press Enter to continue
    cin.get();

    // Show the added recipe details
    viewRecipe(count);
    
    cout << "\033[47m";
    cout << "\033[30m";
    cout << "                                                           " << endl;
    cout << "  [1] Add another Recipe                                   " << endl;
    cout << "  [2] Back to Homepage                                     " << endl;
    cout << "  [3] Exit the Program                                     " << endl;
    cout << "                                                           \033[0m" << endl;
    cout << endl;
    cout << "  Enter Option: ";
    int option;
    cin >> option;

    switch (option) {
        case 1:
            addRecipe();
            break;
        case 2:
            // Return to the main loop or homepage function
            return;
        case 3:
            cout << "  Exiting the program..." << endl;
            exit(0); // Exit the program
        default:
            cout << endl;
            cout << "\033[97m";
            cout << "\033[41m";
            cout << "                                                           " << endl;
            cout << "                      Invalid Choice!                      " << endl;
            cout << "                                                           \033[0m" << endl;
            cout << endl;
            cout << "  Exiting the program..." << endl;
            exit(1);
    }
}

void addRecipeItems() {
    cin.ignore(); // Clear the input buffer

    // Prompt for recipe name
    cout << "  Recipe Name: ";
    getline(cin, recipes[count].name);

    // Prompt for number of ingredients
    int ingredients_qty = ingredientQtyChecker();

    // Resize ingredients vector
    recipes[count].ingredients.resize(ingredients_qty);

    // Prompt for each ingredient
    for (int i = 0; i < ingredients_qty; ++i) {
        cout << "  Ingredient " << i + 1 << ":" << endl;
        cout << "    Name: ";
        getline(cin, recipes[count].ingredients[i].name);
        cout << "    Unit: ";
        getline(cin, recipes[count].ingredients[i].unit);
    }

    // Prompt for number of instruction steps
    int instruction_qty = instructionQtyChecker();

    // Resize instruction vector
    recipes[count].instruction.resize(instruction_qty);

    // Prompt for each instruction step
    for (int i = 0; i < instruction_qty; ++i) {
        cout << "    Step " << i + 1 << ": ";
        getline(cin, recipes[count].instruction[i]);
    }

    // Prompt for cooking time
    cout << "  Cooking Time: ";
    getline(cin, recipes[count].cooking_time);

    // Prompt for difficulty level
    recipes[count].difficulty_level = levelChecker();

    // Prompt for category
    recipes[count].category = categoryChecker();

    // Increment recipe count
    count++;
    // Save the recipe to file
    saveRecipe();

    // Reload recipes from file to update count variable
    loadRecipe();

}

void viewRecipe(int recipeNumber) 
{
    clearScreen();
    cout << "\033[46m";  // Set background color to cyan
    cout << "\033[97m";  // Set text color to white
    cout << "                                                           " << endl;
    cout << "                       View Recipe                         " << endl;
    cout << "                                                           \033[0m" << endl;
    cout << endl;

    // Open the file to read
    ifstream read("recipes.txt");

    // Check if the file is open
    if (read.is_open()) {
        // Read the total count of recipes
        int totalRecipes;
        read >> totalRecipes;
        read.ignore();  // Ignore the newline after the integer

        // Check if the recipeNumber is valid
        if (recipeNumber >= 1 && recipeNumber <= totalRecipes) {
            int index = recipeNumber - 1;

            // Skip to the selected recipe in the file
            for (int i = 0; i < index; i++) {
                string line;
                getline(read, line); // Read and discard lines until the desired recipe
            }

            // Display the details of the selected recipe
            cout << "  Recipe Name: " << recipes[index].name << endl;
            cout << "  Ingredients:" << endl;
            for (size_t j = 0; j < recipes[index].ingredients.size(); j++) {
                cout << "    - " << recipes[index].ingredients[j].name << " (" << recipes[index].ingredients[j].unit << ")" << endl;
            }
            cout << "  Instructions:" << endl;
            for (size_t j = 0; j < recipes[index].instruction.size(); j++) {
                cout << "    Step "<<j + 1<<": " << recipes[index].instruction[j] << endl;
            }
            cout << "  Cooking Time: " << recipes[index].cooking_time << endl;
            cout << "  Difficulty Level: " << recipes[index].difficulty_level << endl;
            cout << "  Category: " << recipes[index].category << endl;
        } else {
            // Display error message for invalid recipe ID
            cout << endl;
            cout << "\033[97m";
            cout << "\033[41m";
            cout << "                                                           " << endl;
            cout << "                    Invalid Recipe ID!                     " << endl;
            cout << "                                                           \033[0m" << endl;
        }

        // Close the file
        read.close();
    } else {
        // Display error message for unable to open file
        cout << endl;
        cout << "\033[97m";
        cout << "\033[41m";
        cout << "                                                           " << endl;
        cout << "                  Unable to open file!                     " << endl;
        cout << "                                                           " << endl;
    }

    cin.ignore(); // Wait for user input to continue
}

void checkExistingRecipe() 
{
    clearScreen();

    // Open the file to read
    ifstream file("recipes.txt");

    // Check if the file is open
    if (!file.is_open()) {
        // Display error message if file cannot be opened
        cout << endl;
        cout << "\033[97m";
        cout << "\033[41m";
        cout << "                                                           " << endl;
        cout << "                  Unable to open file!                     " << endl;
        cout << "               Please check the file path!                 " << endl;
        cout << "                                                           \033[0m" << endl;
        cout << endl;

        // Wait for user input
        cin.ignore();
        cin.get();

        // Return without attempting to load recipes
        return;
    }

    // Load recipes from the file
    loadRecipe();

    // Close the file after loading recipes
    file.close();

    // Clear the screen before displaying recipes
    clearScreen();

    cout << "\033[46m";
    cout << "\033[97m";
    cout << "                                                           " << endl;
    cout << "                   Check Existing Recipe                   " << endl;
    cout << "                                                           \033[0m" << endl;
    cout << endl;

    // Display details of existing recipes
    for (int i = 0; i < count; i++) {
        cout << "\033[47m";
        cout << "\033[30m";
        cout << "                                                           " << endl;
        cout << "                       " << "Recipe No. " << i + 1 << "                        " << endl;
        cout << "                                                           \033[0m" << endl;
        cout << endl;
        cout << "  Recipe Name: " << recipes[i].name << endl;
        cout << "  Ingredients:" << endl;
        for (size_t j = 0; j < recipes[i].ingredients.size(); j++) {
            cout << "    • " << recipes[i].ingredients[j].name << " (" << recipes[i].ingredients[j].unit << ")" << endl;
        }
        cout << "  Instructions:" << endl;
        for (size_t j = 0; j < recipes[i].instruction.size(); j++) {
            cout << "    • " << recipes[i].instruction[j] << endl;
        }
        cout << "  Cooking Time: " << recipes[i].cooking_time << endl;
        cout << "  Difficulty Level: " << recipes[i].difficulty_level << endl;
        cout << "  Category: " << recipes[i].category << endl;
        cout << endl;
    }

    // Wait for user input before returning to main menu
    cout << "  Press Enter to return to main menu...";
    cin.ignore();
    cin.get();
}

void searchRecipe() {
    clearScreen();
    
    ifstream file("recipes.txt");
    if (!file.is_open()) {
        cout << "\033[97m\033[41m";
        cout << "                                                           " << endl;
        cout << "                  Unable to open file!                     " << endl;
        cout << "               Please check the file path!                 " << endl;
        cout << "                                                           \033[0m" << endl;
        cin.ignore();
        cin.get();
        return;
    }

    cout << "\033[46m\033[97m";
    cout << "                                                           " << endl;
    cout << "                    Search Recipe                          " << endl;
    cout << "                                                           \033[0m" << endl;
    cout << endl;

    cout << "  Enter Recipe Name to Search: ";
    string searchName;
    cin.ignore();
    getline(cin, searchName);

    bool found = false;
    int totalRecipes;
    file >> totalRecipes;
    file.ignore();

    for (int i = 0; i < totalRecipes; i++) {
        getline(file, recipes[i].name, '|');

        int ingredients_qty;
        file >> ingredients_qty;
        file.ignore();
        recipes[i].ingredients.resize(ingredients_qty);
        for (int j = 0; j < ingredients_qty; j++) {
            getline(file, recipes[i].ingredients[j].name, '|');
            getline(file, recipes[i].ingredients[j].unit, '|');
        }

        int instruction_qty;
        file >> instruction_qty;
        file.ignore();
        recipes[i].instruction.resize(instruction_qty);
        for (int j = 0; j < instruction_qty; j++) {
            getline(file, recipes[i].instruction[j], '|');
        }

        getline(file, recipes[i].cooking_time, '|');
        getline(file, recipes[i].difficulty_level, '|');
        getline(file, recipes[i].category);

        if (recipes[i].name == searchName) {
            clearScreen();
            cout << "\033[97m\033[42m";
            cout << "                                                           " << endl;
            cout << "                Recipe Found Successfully!                 " << endl;
            cout << "                                                           \033[0m" << endl;
            cout << endl;
            cout << "  Recipe Name: " << recipes[i].name << endl;
            cout << "  Ingredients:" << endl;
            for (int j = 0; j < ingredients_qty; j++) {
                cout << "    - " << recipes[i].ingredients[j].name <<" ("<<recipes[i].ingredients[j].unit<<")"<< endl;
            }
            cout << "  Instructions:" << endl;
            for (int j = 0; j < instruction_qty; j++) {
                cout << "    Steps "<<j+1<<": " << recipes[i].instruction[j] << endl;
            }
            cout << "  Cooking Time: " << recipes[i].cooking_time << endl;
            cout << "  Difficulty Level: " << recipes[i].difficulty_level << endl;
            cout << "  Category: " << recipes[i].category << endl;
            cout << endl;
            found = true;
            break;
        }
    }

    file.close();

    if (!found) {
        cout << "\033[97m\033[41m";
        cout << "                                                           " << endl;
        cout << "                     Recipe Not Found!                     " << endl;
        cout << "                                                           " << endl;
        cout << "                                                           \033[0m" << endl;
        cout << endl;
    }

    cout << "\033[47m\033[30m";
    cout << "                                                           " << endl;
    cout << "  [1] Search another Recipe                                " << endl;
    cout << "  [2] Back to Homepage                                     " << endl;
    cout << "  [3] Exit the Program                                     " << endl;
    cout << "                                                           \033[0m" << endl;
    cout << endl;
    cout << "  Enter Option: ";
    int option;
    cin >> option;

    switch (option) {
        case 1:
            searchRecipe();
            break;
        case 2:
            return; // Return to the main loop
        case 3:
            cout << "  Exiting the program..." << endl;
            exit(0); // Exit the program
        default:
            cout << "\033[97m\033[41m";
            cout << "                                                           " << endl;
            cout << "                      Invalid Choice!                      " << endl;
            cout << "                                                           \033[0m" << endl;
            cout << "  Exiting the program..." << endl;
            exit(1);
    }
}
void clearScreen()
{
    cout<< "\033[2J\033[1;1H";
}

void updateRecipe()
{
    // Open the file to read
    ifstream file("recipes.txt");

    // Check if the file is open
    if (!file.is_open())
    {
        // Display error message if file cannot be opened
        cout << endl;
        cout << "\033[97m";
        cout << "\033[41m";
        cout << "                                                           " << endl;
        cout << "                  Unable to open file!                     " << endl;
        cout << "               Please check the file path!                 " << endl;
        cout << "                                                           \033[0m" << endl;
        cout << endl;

        // Wait for user input
        cin.ignore();
        cin.get();

        // Close the file (although it's not open)
        file.close();
        return;
    }

    clearScreen();
    // Load recipes from file
    loadRecipe();

    cout << "\033[46m";
    cout << "\033[97m";
    cout << "                                                           " << endl;
    cout << "                    Update Recipe                          " << endl;
    cout << "                                                           \033[0m" << endl;
    cout << endl;

    // Display existing recipes
    cout << "  Existing Recipes:" << endl;
    for (int i = 0; i < count; i++)
    {
        cout << "  " << i + 1 << ". " << recipes[i].name << endl;
    }

    int num = 0;
    cout << "\n  Enter Recipe Number to Update: ";
    cin >> num;

    // Validate user input for recipe number
    if (num < 1 || num > count)
    {
        cout << "\033[97m";
        cout << "\033[41m";
        cout << "                                                           " << endl;
        cout << "               Invalid Recipe Number!                      " << endl;
        cout << "               Please choose a valid number.               " << endl;
        cout << "                                                           \033[0m" << endl;
        cout << endl;
        cout << "  Exiting the program..." << endl;
        exit(1);
    }

    int index = num - 1;

    // Call function to update recipe items
    updateRecipeItems(index, num);

    cout << endl;
    cout << "\033[47m";
    cout << "\033[30m";
    cout << "                                                           " << endl;
    cout << "  [1] Update another Recipe                                " << endl;
    cout << "  [2] Back to Homepage                                     " << endl;
    cout << "  [3] Exit the Program                                     " << endl;
    cout << "                                                           \033[0m" << endl;
    cout << endl;
    cout << "  Enter Option: ";
    int option;
    cin >> option;

    switch (option)
    {
    case 1:
        updateRecipe();
        break;
    case 2:
        return;
    case 3:
        cout << "  Exiting the program..." << endl;
        exit(0);
    default:
        cout << endl;
        cout << "\033[97m";
        cout << "\033[41m";
        cout << "                                                           " << endl;
        cout << "                      Invalid Choice!                      " << endl;
        cout << "                                                           \033[0m" << endl;
        cout << endl;
        cout << "  Exiting the program..." << endl;
        exit(1);
    }
}

void updateRecipeItems(int index, int num) {
    clearScreen();

    cout << "\033[46m\033[97m"; // Set background to cyan and text to white
    cout << "                                                           " << endl;
    cout << "                    Update Recipe                          " << endl;
    cout << "                                                           \033[0m" << endl;
    cout << endl;

    // Display existing recipe details
    cout << "  Existing Recipe Details:" << endl;
    viewRecipe(num);
    cout << endl;

    string choice;
    cout << "  Confirm to Update Recipe No. " << num << "? [Y/N]: ";
    getline(cin, choice);

    if (choice == "Y" || choice == "y") {
        bool validInput = true;

        cout << endl;
        cout << "\033[97m\033[42m"; // Set text to white and background to green
        cout << "                                                           " << endl;
        cout << "             Starting Update of Recipe No." << num << "!               " << endl;
        cout << "                                                           \033[0m" << endl;
        cout << endl;

        // Update recipe name
        cout << "  Recipe Name: ";
        getline(cin, recipes[index].name);

        // Update ingredients
        int ingredients_qty;
        cout << "  No. of Ingredients: ";
        cin >> ingredients_qty;

        if (cin.fail() || ingredients_qty < 0) {
            validInput = false;
            cout << endl;
            cout << "\033[97m\033[41m"; // Set text to white and background to red
            cout << "                                                           " << endl;
            cout << "           Invalid input for Ingredients Quantity!         " << endl;
            cout << "                                                           \033[0m" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cin.ignore(); // Ignore newline character left in the buffer

        if (validInput) {
            // Resize ingredients vector and prompt to enter each ingredient
            recipes[index].ingredients.resize(ingredients_qty);
            for (int i = 0; i < ingredients_qty; ++i) {
                cout << "  Ingredient " << i + 1 << ":" << endl;
                cout << "    Name: ";
                getline(cin, recipes[index].ingredients[i].name);
                cout << "    Unit: ";
                getline(cin, recipes[index].ingredients[i].unit);
            }

            // Update instruction steps
            int instruction_qty;
            cout << "  No. of Instruction Steps: ";
            cin >> instruction_qty;

            if (cin.fail() || instruction_qty < 0) {
                validInput = false;
                cout << endl;
                cout << "\033[97m\033[41m"; // Set text to white and background to red
                cout << "                                                           " << endl;
                cout << "            Invalid input for instruction Quantity!          " << endl;
                cout << "                                                           \033[0m" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            cin.ignore(); // Ignore newline character left in the buffer

            if (validInput) {
                // Resize instruction vector and prompt to enter each instruction step
                recipes[index].instruction.resize(instruction_qty);
                for (int i = 0; i < instruction_qty; ++i) {
                    cout << "  Step " << i + 1 << ": ";
                    getline(cin, recipes[index].instruction[i]);
                }

                // Update cooking time, difficulty level, and category
                cout << "  Cooking Time: ";
                getline(cin, recipes[index].cooking_time);

                // Prompt for difficulty level
                recipes[index].difficulty_level = levelChecker();

                // Prompt for category
                recipes[index].category = categoryChecker();

                // Display success message for recipe update
                cout << endl;
                cout << "\033[97m\033[42m"; // Set text to white and background to green
                cout << "                                                           " << endl;
                cout << "               Recipe Updated Successfully!                " << endl;
                cout << "                                                           \033[0m" << endl;

                // Save recipe changes to file and reload recipes
                saveRecipe();
                loadRecipe();

                cout << "Press Enter to continue...";
                cin.ignore(); // Wait for user to press Enter to continue

                // Clear screen and display updated recipe details
                clearScreen();
                cout << "\033[46m\033[97m"; // Set background to cyan and text to white
                cout << "                                                           " << endl;
                cout << "                    Update Recipe                          " << endl;
                cout << "                                                           \033[0m" << endl;
                cout << endl;

                cout << "  Updated Recipe Details:" << endl;
                viewRecipe(num);
            }
        }
    } else {
        // Display message if update is cancelled
        cout << endl;
        cout << "\033[97m\033[41m"; // Set text to white and background to red
        cout << "                                                           " << endl;
        cout << "                     Update Cancelled!                     " << endl;
        cout << "                                                           \033[0m" << endl;
    }
}

void deleteRecipe() 
{
    ifstream file("recipes.txt");
    if (!file.is_open()) {
        cout << endl;
        cout << "\033[97m\033[41m";
        cout << "                                                           " << endl;
        cout << "                  Unable to open file!                     " << endl;
        cout << "               Please check the file path!                 " << endl;
        cout << "                                                           \033[0m" << endl;
        cout << endl;

        cin.ignore();
        cin.get();
        file.close();
        return;
    }

    clearScreen();
    cout << "\033[46m\033[97m";
    cout << "                                                           " << endl;
    cout << "                    Delete Recipe                          " << endl;
    cout << "                                                           \033[0m" << endl;
    cout << endl;

    cout << "  Existing Recipes:" << endl;
    for (int i = 0; i < count; i++) {
        cout << "  " << i + 1 << ". " << recipes[i].name << endl;
    }

    int num = 0;
    string choice;
    cout << endl;
    cout << "  Enter Recipe ID to Delete: ";
    cin >> num;
    cin.ignore();
    int index = num - 1;

    if (index < 0 || index >= count) {
        cout << endl;
        cout << "\033[97m\033[41m";
        cout << "                                                           " << endl;
        cout << "                    Invalid Recipe ID!                     " << endl;
        cout << "                                                           \033[0m" << endl;
        cout << endl;
        file.close();
        return;
    }

    cout << endl;
    cout << "\033[97m\033[42m";
    cout << "                                                           " << endl;
    cout << "                Recipe Found Successfully!                 " << endl;
    cout << "                                                           \033[0m" << endl;
    cout << endl;

    cout << "  Confirm to Delete Recipe No. " << num << "? [Y/N]: ";
    getline(cin, choice);

    if (choice == "Y" || choice == "y") {
        for (int i = index; i < count - 1; i++) {
            recipes[i] = recipes[i + 1];
        }
        count--;

        ofstream write("recipes.txt");
        if (write.is_open()) {
            write << count << endl;
            for (int i = 0; i < count; i++) {
                write << recipes[i].name << "|" << recipes[i].ingredients.size() << "|";
                for (size_t j = 0; j < recipes[i].ingredients.size(); j++) {
                    write << recipes[i].ingredients[j].name << "|" << recipes[i].ingredients[j].unit << "|";
                }
                write << recipes[i].instruction.size() << "|";
                for (size_t j = 0; j < recipes[i].instruction.size(); j++) {
                    write << recipes[i].instruction[j] << "|";
                }
                write << recipes[i].cooking_time << "|" << recipes[i].difficulty_level << "|" << recipes[i].category << endl;
            }
            write.close();

            cout << endl;
            cout << "\033[97m\033[42m";
            cout << "                                                           " << endl;
            cout << "               Recipe Deleted Successfully!                " << endl;
            cout << "                                                           \033[0m" << endl;
            cout << endl;
        } else {
            cout << endl;
            cout << "\033[97m\033[41m";
            cout << "                                                           " << endl;
            cout << "                    Unable to open file!                   " << endl;
            cout << "                                                           \033[0m" << endl;
            cout << endl;
        }
    } else {
        cout << endl;
        cout << "\033[97m\033[42m";
        cout << "                                                           " << endl;
        cout << "                   Deletion Cancelled!                     " << endl;
        cout << "                                                           \033[0m" << endl;
        cout << endl;
    }

    cout << endl;
    cout << "\033[47m\033[30m";
    cout << "                                                           " << endl;
    cout << "  [1] Delete another Recipe                                " << endl;
    cout << "  [2] Back to Homepage                                     " << endl;
    cout << "  [3] Exit the Program                                     " << endl;
    cout << "                                                           \033[0m" << endl;
    cout << endl;
    cout << "  Enter Option: ";
    int option;
    cin >> option;

    switch (option) {
        case 1:
            deleteRecipe();
            break;
        case 2:
            return;
        case 3:
            cout << "  Exiting the program..." << endl;
            exit(0);
        default:
            cout << endl;
            cout << "\033[97m\033[41m";
            cout << "                                                           " << endl;
            cout << "                      Invalid Choice!                      " << endl;
            cout << "                                                           \033[0m" << endl;
            cout << endl;
            cout << "  Exiting the program..." << endl;
            exit(1);
    }
}