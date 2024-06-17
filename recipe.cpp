#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <limits>
#include <vector>
#include <cctype>

using namespace std;

enum DifficultyLevel 
{
    Beginner,
    Intermediate,
    Advanced
};

enum Category 
{
    Appetizer,
    MainCourse,
    Dessert,
    Drink,
    Soup,
    Salad,
    Snack,
    Breakfast,
    SideDish,
    Other
};
struct Ingredient 
{
    string name;
    string unit;
};

struct Recipe 
{
    string name;
    vector<Ingredient> ingredients;
    vector<string> instruction;
    string cooking_time;
    bool isFavorite;
    DifficultyLevel difficulty_level;
    Category category; // Enum to denote category
};

// FUNCTION PROTOTYPES
void header();
void saveRecipe();
void loadRecipe();
int ingredientQtyChecker();
int instructionQtyChecker();
void addRecipe();
void addRecipeItems();
void updateRecipe();
void updateRecipeItems(int num, int count);
void searchRecipe();
void deleteRecipe();
void checkExistingRecipe();
void viewRecipe(int recipeNumber);
void viewRecipeDetails(int index);
void chooseCategory();
void chooseDifficulty();
void displayFavoriteRecipes();
void displayByCategory(Category category);
void displayByDifficulty(DifficultyLevel level);
void addToFavorites(int index);
void removeFromFavorites(int index);
void printTabs(int tabNum);
void clearScreen();

string difficultyLevelToString(DifficultyLevel level) 
{
    switch (level) 
    {
        case Beginner:
            return "Beginner Level";
        case Intermediate:
            return "Intermediate Level";
        case Advanced:
            return "Advanced Level";
        default:
            return "Unknown";
    }
}

string categoryToString(Category category) 
{
    switch (category) 
    {
        case Appetizer:
            return "Appetizer";
        case MainCourse:
            return "Main Course";
        case Dessert:
            return "Dessert";
        case Drink:
            return "Drink";
        case Soup:
            return "Soup";
        case Snack:
            return "Snack";
        case Breakfast:
            return "Breakfast";
        case SideDish:
            return "Side Dish";
        case Other:
            return "Other";
        default:
            return "Unknown";
    }
}

Recipe recipes[100]; // ARRAY OF RECIPE STRUCT TO STORE MANY RECIPES 
int opt = 0, count = 0;

int main() 
{    
    header();
    loadRecipe();
    clearScreen();

    int option;

    while (true) 
    {
        clearScreen();
        printTabs(5); cout<<",------.              ,--.              ,------.         ,--. \n";
        printTabs(5); cout<<"|  .--. ' ,---.  ,---.`--' ,---.  ,---. |  .--. ' ,--,--.|  | \n";
        printTabs(5); cout<<"|  '--'.'| .-. :| .--',--.| .-. || .-. :|  '--' |' ,-.  ||  | \n";
        printTabs(5); cout<<"|  |\\  \\ \\   --.\\ `--.|  || '-' '\\   --.|  | --' \\ '-'  ||  | \n";
        printTabs(5); cout<<"`--' '--' `----' `---'`--'|  |-'  `----'`--'      `--`--'`--' \n";
        printTabs(5); cout<<"                          `--'                                 \n";
        cout<<endl;
        cout<<"\033[48;2;255;255;255m";
        cout<<"\033[30m";
        printTabs(5); cout<<"                                                           "<<endl; 
        printTabs(5); cout<<"                  Welcome to RecipePal!                    "<<endl; 
        printTabs(5); cout<<"           Organize your Recipes in an Instant             "<<endl; 
        printTabs(5); cout<<"                                                           "<<endl;
        printTabs(5); cout<<"  [1] Recipes Menu                                         "<<endl; 
        printTabs(5); cout<<"  [2] Favorite Recipes                                     "<<endl; 
        printTabs(5); cout<<"  [3] View Recipes by Category                             "<<endl; 
        printTabs(5); cout<<"  [4] View Recipes by Difficulty                           "<<endl;
        printTabs(5); cout<<"  [5] Exit                                                 "<<endl;
        printTabs(5); cout<<"                                                           \033[0m"<<endl;
        cout<<endl; 
        printTabs(5); cout<<"  Enter Option: ";
        cin>>option;

        switch (option) 
        {
            case 1: 
            {
                while (true) 
                {
                    clearScreen();
                    printTabs(5); cout<<",------.              ,--.              ,------.         ,--. \n";
                    printTabs(5); cout<<"|  .--. ' ,---.  ,---.`--' ,---.  ,---. |  .--. ' ,--,--.|  | \n";
                    printTabs(5); cout<<"|  '--'.'| .-. :| .--',--.| .-. || .-. :|  '--' |' ,-.  ||  | \n";
                    printTabs(5); cout<<"|  |\\  \\ \\   --.\\ `--.|  || '-' '\\   --.|  | --' \\ '-'  ||  | \n";
                    printTabs(5); cout<<"`--' '--' `----' `---'`--'|  |-'  `----'`--'      `--`--'`--' \n";
                    printTabs(5); cout<<"                          `--'                                 \n";
                    cout<<endl;

                    cout<<"\033[48;2;255;255;255m";
                    cout<<"\033[30m";
                    printTabs(5); cout<<"                                                           "<<endl; 
                    printTabs(5); cout<<"                  Welcome to RecipePal!                    "<<endl; 
                    printTabs(5); cout<<"           Organize your Recipes in an Instant             "<<endl; 
                    printTabs(5); cout<<"                                                           "<<endl;
                    printTabs(5); cout<<"  [1] Check Existing Recipes                               "<<endl; 
                    printTabs(5); cout<<"  [2] Add Recipes                                          "<<endl; 
                    printTabs(5); cout<<"  [3] Search Recipes                                       "<<endl; 
                    printTabs(5); cout<<"  [4] Update Recipes                                       "<<endl; 
                    printTabs(5); cout<<"  [5] Delete Recipes                                       "<<endl; 
                    printTabs(5); cout<<"  [6] Return to Home Page                                  "<<endl; 
                    printTabs(5); cout<<"  [7] Exit                                                 "<<endl; 
                    printTabs(5); cout<<"                                                           \033[0m" << endl;
                    cout<<endl; 

                    printTabs(5); cout<<"  Enter Option: ";
                    int opt;
                    cin>>opt;

                    switch(opt) 
                    {
                        case 1: 
                            checkExistingRecipe(); 
                            break;
                        case 2: 
                            addRecipe(); 
                            break;
                        case 3: 
                            searchRecipe(); 
                            break;
                        case 4: 
                            updateRecipe();
                            break;
                        case 5: 
                            deleteRecipe();
                            break;
                        case 6: 
                            break; // Return to outer menu
                        case 7: 
                            printTabs(5); cout<<"  Exiting the program..."<<endl;
                            exit(0); // Exit the program
                        default: 
                            cout<<endl;
                            cout<<"\033[97m"; 
                            cout<<"\033[41m";
                            printTabs(5); cout<<"                                                           "<<endl;
                            printTabs(5); cout<<"                      Invalid Option!                      "<<endl;
                            printTabs(5); cout<<"                                                           \033[0m"<<endl;
                            cout<<endl;
                            printTabs(5); cout<<"  Exiting the program..."<<endl;
                            exit(1);
                    }
                    if (opt == 6) 
                    {
                        break; // Exit the inner while loop
                    }
                }
                break;
            }
            case 2: 
                displayFavoriteRecipes(); 
                break;
            case 3: 
                chooseCategory();
                break;
            case 4: 
                chooseDifficulty();
            case 5: 
                printTabs(5); cout<<"  Exiting the program..."<<endl;
                exit(0); // Exit the program
            default: 
                cout<<endl;
                cout<<"\033[97m"; 
                cout<<"\033[41m";
                printTabs(5); cout<<"                                                           "<<endl;
                printTabs(5); cout<<"                      Invalid Option!                      "<<endl;
                printTabs(5); cout<<"                                                           \033[0m"<<endl;
                cout<<endl;
                printTabs(5); cout<<"  Exiting the program..."<<endl;
                exit(1);
        }
    }
}

void header()
{
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"\033[32m";
	cout<<"                                                                    @@@@+     :=*%\n";
    cout<<"                  @@@@@@@@@@@@@     @@@@@@@@@@.                    @@@@#  +@@@@@@@@@@@   @@@@@@@@@@+\n";
    cout<<"                  @@@@@@@@@@@@@@    @@@@@@@@@@          @@@@@@@@          +@@@*   .@@@@  @@@@@@@@@@\n";
    cout<<"                  @@@@+:::.@@@@@@   @@@@@%            @@@@@@@@@@   @@@@   *@@@-    @@@@  @@@@@@\n";
    cout<<"                  @@@@      @@@@@   @@@@@#          +@@@@@@@@      @@@@*  *@@@=    @@@@  @@@@@@\n";
    cout<<"                  @@@@     -@@@@-   @@@@@@@@@       @@@@@@         @@@@#  +@@@@.+@@@@@   @@@@@@@@@\n";
    cout<<"                  @@@@  .@@@@@@     @@@@@@@@@#      @@@@@          @@@@%  +@@@@@@@@      @@@@@@@@@@\n";
    cout<<"                  @@@@@@@@@@@@%     %@@@@@          @@@@           @@@@#  =@@@@+         @@@@@@\n";
    cout<<"                  @@@@@@@@@@@@@     *@@@@@         =@@@@@          @@@@*  -@@@@          @@@@@@\n";
    cout<<"                  @@@@@   @@@@@@    -@@@@@          @@@@@@@@@%-    @@@@*  :@@@%          @@@@@@\n";
    cout<<"                  @@@@@     @@@@@     @@@@@@@@@@@%    +@@@@@@@@@:   @@@@*  :@@@*          @@@@@@@@@@*\n";
    cout<<"                  @@@@@      @@@@@    @@@@@@@@@@%        @@@@@@@    @@@@*  .@@@+          *@@@@@@@@@\n";
    cout<<"                             @@\n";
    cout<<"\033[0m";
	cout<<endl;
	cout<<endl;
    cout<<"                                      @@@@@@@@@\n";
    cout<<"                                      @@@@@@@@@@@@      @@@@@@         @@@@@:\n";
    cout<<"                                      @@@@     @@@-    +@@@@@@.        @@@@@\n";
    cout<<"                                      @@@@     @@@@    @@@@@@@@        @@@@@\n";
    cout<<"                                      @@@@    @@@@     @@@@ @@@@       @@@@@\n";
    cout<<"                                      @@@@@@@@@@      @@@@@  @@@@      %@@@@\n";
    cout<<"                                      @@@@@@@         @@@@@  @@@@@     *@@@@\n";
    cout<<"                                      @@@@+          :@@@@@@@@@@@@-    +@@@@\n";
    cout<<"                                      @@@@:          @@@@@@@@%*@@@@    +@@@@\n";
    cout<<"                                      @@@@.          @@@@       @@@@   *@@@@@@@@@@@\n";
    cout<<"                                      @@@@           @@@@       -@@@.  %@@@@@@@@@@@\n";
    cout<<"                                       *@@           -+%               =@@@@@@@@@@@\n";

    cout<<endl;
    printTabs(6); cout<<"Press Enter to continue...";
    cin.get();
}

void saveRecipe() 
{
    // OPEN FILE STREAM FOR WRITING
    ofstream write("recipes.txt");

    if (!write.is_open()) 
    {
        cout<<endl;
        cout<<"\033[97m";
        cout<<"\033[41m";
        printTabs(5); cout<<"                                                           "<<endl;
        printTabs(5); cout<<"                  Unable to open file!                     "<<endl;
        printTabs(5); cout<<"                                                           \033[0m"<<endl;
        return;
    }

    // WRITE THE TOTAL COUNT OF RECIPES
    write<<count<<endl;

    // LOOP THROUGH EACH RECIPE
    for (int i = 0; i < count; i++) 
    {
        // WRITE RECIPE NAME
        write<<recipes[i].name<<"|";

        // WRITE NUMBER OF INGREDIENTS
        write<<recipes[i].ingredients.size()<<"|";

        // WRITE EACH INGREDIENT
        for (size_t j = 0; j < recipes[i].ingredients.size(); j++) 
        {
            write<<recipes[i].ingredients[j].name<<"|";
            write<<recipes[i].ingredients[j].unit<<"|";
        }

        // WRITE NUMBER OF INSTRUCTION STEPS
        write<<recipes[i].instruction.size()<<"|";

        // WRITE EACH INSTRUCTION STEP
        for (size_t j = 0; j < recipes[i].instruction.size(); j++) 
        {
            write<<recipes[i].instruction[j]<<"|";
        }

        // WRITE COOKING TIME, DIFFICULTY LEVEL, CATEGORY, AND FAVORITE STATUS
        write<<recipes[i].cooking_time<<"|";
        write<<static_cast<int>(recipes[i].difficulty_level)<<"|";
        write<<static_cast<int>(recipes[i].category)<<"|";
        write<<(recipes[i].isFavorite ? 1 : 0)<<endl;
    }

    // CLOSE THE FILE STREAM
    write.close();
}

void loadRecipe() 
{
    // OPEN FILE STREAM FOR READING
    ifstream read("recipes.txt");

    if (!read.is_open()) 
    {
        cout<<endl;
        cout<<"\033[97m";
        cout<<"\033[41m";
        printTabs(5); cout<<"                                                           "<<endl;
        printTabs(5); cout<<"                  Unable to open file!                     "<<endl;
        printTabs(5); cout<<"                                                           \033[0m"<<endl;
        return;
    }

    // READ THE TOTAL COUNT OF RECIPES
    read>>count;
    read.ignore(); // Ignore the newline character left by '>>'

    // LOOP THROUGH EACH RECIPE
    for (int i = 0; i < count; i++) 
    {
        // READ RECIPE NAME
        getline(read, recipes[i].name, '|');

        // READ NUMBER OF INGREDIENTS
        int ingredients_qty;
        read>>ingredients_qty;
        read.ignore(); // Ignore the '|' character

        recipes[i].ingredients.resize(ingredients_qty);

        // READ EACH INGREDIENT
        for (int j = 0; j < ingredients_qty; j++) 
        {
            getline(read, recipes[i].ingredients[j].name, '|');
            getline(read, recipes[i].ingredients[j].unit, '|');
        }

        // READ NUMBER OF INSTRUCTION STEPS
        int instruction_qty;
        read>>instruction_qty;
        read.ignore(); // Ignore the '|' character

        recipes[i].instruction.resize(instruction_qty);

        // READ EACH INSTRUCTION STEP
        for (int j = 0; j < instruction_qty; j++) 
        {
            getline(read, recipes[i].instruction[j], '|');
        }

        // READ COOKING TIME, DIFFICULTY LEVEL, AND CATEGORY
        getline(read, recipes[i].cooking_time, '|');
        
        int difficultyLevel;
        read >> difficultyLevel; // Read the difficulty level as integer
        read.ignore(); // Consume the newline left by '>>'

        recipes[i].difficulty_level = static_cast<DifficultyLevel>(difficultyLevel);

        int category;
        read >> category; // Read the category as integer
        read.ignore(); // Ignore the '|' character

        recipes[i].category = static_cast<Category>(category);

        int isFavoriteInt;
        read >> isFavoriteInt;
        read.ignore(); // Ignore the newline character

        recipes[i].isFavorite = (isFavoriteInt == 1);
    }
    // CLOSE THE FILE STREAM
    read.close();
}

int ingredientQtyChecker() 
{
    int ingredients_qty;
    bool validInput = false;

    while (!validInput) 
    {
        printTabs(5); cout<<"  No. of Ingredients: ";
        cin>>ingredients_qty;
 
        if (cin.fail() || ingredients_qty <= 0) 
        {
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input

            cout<<endl;
            cout<<"\033[97m";
            cout<<"\033[41m"; 
            printTabs(5); cout<<"                                                           "<<endl;
            printTabs(5); cout<<"           Invalid input for Ingredients Quantity!         "<<endl;
            printTabs(5); cout<<"                                                           \033[0m"<<endl;
            cout<<endl;
        } 
        else
        {
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

    while (!validInput) 
    {
        printTabs(5); cout<<"  No. of Instruction Steps: ";
        cin >> instruction_qty;

        if (cin.fail() || instruction_qty <= 0) 
        {
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input

            cout<<endl;
            cout<<"\033[97m";
            cout<<"\033[41m"; 
            printTabs(5); cout << "                                                           "<<endl;
            printTabs(5); cout << "       Invalid input for Instruction Steps Quantity!       "<<endl;
            printTabs(5); cout << "                                                           \033[0m"<<endl;
            cout<<endl;
        } 
        else 
        {
            validInput = true;
        }
    }
    cin.ignore(); // Clear the newline character left in the buffer
    return instruction_qty;
}

void addRecipe() 
{
    clearScreen();
    cout<<"\033[46m"; 
    cout<<"\033[97m";
    printTabs(5); cout<<"                                                           "<<endl;
    printTabs(5); cout<<"                        Add Recipe                         "<<endl;
    printTabs(5); cout<<"                                                           \033[0m"<<endl;
    cout<<endl;

    // Call function to add recipe items
    addRecipeItems();

    cout<<endl; 
    cout<<"\033[97m";
    cout<<"\033[42m";
    printTabs(5); cout<<"                                                           "<<endl;
    printTabs(5); cout<<"                Recipe Added Successfully!                 "<<endl;
    printTabs(5); cout<<"                                                           \033[0m"<<endl;
    cout<<endl;

    printTabs(6); cout << "        Press Enter to continue...";
    cin.ignore(); // Wait for user to press Enter to continue
    cin.get();

    // Show the added recipe details
    viewRecipe(count);
    addToFavorites(count - 1);
    
    cout<<endl;
    cout<<"\033[47m";
    cout<<"\033[30m";
    printTabs(5); cout<<"                                                           "<<endl;
    printTabs(5); cout<<"  [1] Add another Recipe                                   "<<endl;
    printTabs(5); cout<<"  [2] Back to Homepage                                     "<<endl;
    printTabs(5); cout<<"  [3] Exit the Program                                     "<<endl;
    printTabs(5); cout<<"                                                           \033[0m"<<endl;
    cout<<endl;

    printTabs(5); cout<<"  Enter Option: ";
    int option;
    cin>>option;

    switch (option) 
    {
        case 1:
            addRecipe();
            break;
        case 2:
            // Return to the main loop or homepage function
            return;
        case 3:
            printTabs(5); cout<<"  Exiting the program..."<<endl;
            exit(0); // Exit the program
        default:
            cout<<endl;
            cout<<"\033[97m";
            cout<<"\033[41m";
            printTabs(5); cout<<"                                                           "<<endl;
            printTabs(5); cout<<"                      Invalid Option!                      "<<endl;
            printTabs(5); cout<<"                                                           \033[0m"<<endl;
            cout<<endl;
            printTabs(5); cout<<"  Exiting the program..."<<endl;
            exit(1);
    }
}

void addRecipeItems() 
{
    cin.ignore(); // Clear the input buffer

    // Prompt for recipe name
    printTabs(5); cout<<"  Recipe Name: ";
    getline(cin, recipes[count].name);

    // Prompt for number of ingredients
    int ingredients_qty = ingredientQtyChecker();

    // Resize ingredients vector
    recipes[count].ingredients.resize(ingredients_qty);

    // Prompt for each ingredient
    for (int i = 0; i < ingredients_qty; ++i) 
    {
        printTabs(5); cout<<"  Ingredient "<< i + 1 <<":"<<endl;
        printTabs(5); cout<<"     Name: ";
        getline(cin, recipes[count].ingredients[i].name);
        printTabs(5); cout<<"     Unit: ";
        getline(cin, recipes[count].ingredients[i].unit);
    }

    // Prompt for number of instruction steps
    int instruction_qty = instructionQtyChecker();

    // Resize instruction vector
    recipes[count].instruction.resize(instruction_qty);

    // Prompt for each instruction step
    for (int i = 0; i < instruction_qty; ++i) 
    {
        printTabs(5); cout<< "     Step "<< i + 1 <<": ";
        getline(cin, recipes[count].instruction[i]);
    }

    // Prompt for cooking time
    printTabs(5); cout<<"  Cooking Time: ";
    getline(cin, recipes[count].cooking_time);

    cout<<endl;
    printTabs(5); cout<<"  Select Cooking Difficulty Level:"<<endl;
    printTabs(5); cout<<"     [1] Beginner Level"<<endl;
    printTabs(5); cout<<"     [2] Intermediate Level"<<endl;
    printTabs(5); cout<<"     [3] Advanced Level"<<endl;
    printTabs(5); cout<<"  Enter Option: ";

    int difficultyOption;
    cin>>difficultyOption;
    cin.ignore(); // Consume the newline left by cin

    switch (difficultyOption) 
    {
        case 1:
            recipes[count].difficulty_level = Beginner;
            break;
        case 2:
            recipes[count].difficulty_level = Intermediate;
            break;
        case 3:
            recipes[count].difficulty_level = Advanced;
            break;
        default:
            cout<<endl;
            cout<<"\033[97m";
            cout<<"\033[41m";
            printTabs(5); cout<<"                                                           "<<endl;
            printTabs(5); cout<<"                      Invalid Option!                      "<<endl;
            printTabs(5); cout<<"         Setting difficulty to Beginner by default.         "<<endl;
            printTabs(5); cout<<"                                                           \033[0m"<<endl;
            cout<<endl;

            recipes[count].difficulty_level = Beginner;
            break;
    }

    cout<<endl;
    printTabs(5); cout<<"  Select Category:"<<endl;
    printTabs(5); cout<<"     [1] Appetizer     [4] Drink    [7] Breakfast"<<endl;
    printTabs(5); cout<<"     [2] Main Course   [5] Soup     [8] Side Dish"<<endl;
    printTabs(5); cout<<"     [3] Dessert       [6] Snack    [9] Other"<<endl;
    printTabs(5); cout<<"  Enter Option: ";

    int categoryOption;
    cin>>categoryOption;
    cin.ignore(); // Consume the newline left by cin

    switch (categoryOption) 
    {
        case 1:
            recipes[count].category = Appetizer;
            break;
        case 2:
            recipes[count].category = MainCourse;
            break;
        case 3:
            recipes[count].category = Dessert;
            break;
        case 4:
            recipes[count].category = Drink;
            break;
        case 5:
            recipes[count].category = Soup;
            break;
        case 6:
            recipes[count].category = Snack;
            break;
        case 7:
            recipes[count].category = Breakfast;
            break;
        case 8:
            recipes[count].category = SideDish;
            break;
        case 9:
            recipes[count].category = Other;
            break;
        default:
            cout<<endl;
            cout<<"\033[97m";
            cout<<"\033[41m";
            printTabs(5); cout<<"                                                           "<<endl;
            printTabs(5); cout<<"                      Invalid Option!                      "<<endl;
            printTabs(5); cout<<"          Setting category to Other by default.            "<<endl;
            printTabs(5); cout<<"                                                           \033[0m"<<endl;
            cout<<endl;

            recipes[count].category = Other;
            break;
    }
    // Increment recipe count
    count++;
    // Save the recipe to file
    saveRecipe();
    // Reload recipes from file to update count variable
    loadRecipe();
}

void updateRecipe()
{
    // Open the file to read
    ifstream file("recipes.txt");

    // Check if the file is open
    if (!file.is_open())
    {
        // Display error message if file cannot be opened
        cout<<endl;
        cout<<"\033[97m";
        cout<<"\033[41m";
        printTabs(5); cout<<"                                                           "<<endl;
        printTabs(5); cout<<"                  Unable to open file!                     "<<endl;
        printTabs(5); cout<<"               Please check the file path!                 "<<endl;
        printTabs(5); cout<<"                                                           \033[0m"<<endl;
        cout<<endl;

        // Wait for user input
        printTabs(6); cout<<"        Press Enter to continue..."; 
        cin.ignore();
        cin.get();

        // Close the file (although it's not open)
        file.close();
        return;
    }

    clearScreen();
    // Load recipes from file
    loadRecipe();

    cout<<"\033[46m";
    cout<<"\033[97m";
    printTabs(5); cout<<"                                                           "<<endl;
    printTabs(5); cout<<"                    Update Recipe                          "<<endl;
    printTabs(5); cout<<"                                                           \033[0m"<<endl;
    cout<<endl;

    // Display existing recipes
    printTabs(5); cout<<"  Existing Recipes:"<<endl;

    for (int i = 0; i < count; i++)
    {
        printTabs(5); cout<<"  "<< i + 1 <<". "<<recipes[i].name<<endl;
    }

    int num = 0;

    cout<<endl;
    printTabs(5); cout<<"  Enter Recipe Number to Update: ";
    cin>>num;

    // Validate user input for recipe number
    if (num < 1 || num > count)
    {
        cout<<endl;
        cout<<"\033[97m";
        cout<<"\033[41m";
        printTabs(5); cout<<"                                                           "<<endl;
        printTabs(5); cout<<"               Invalid Recipe Number!                      "<<endl;
        printTabs(5); cout<<"                                                           \033[0m"<<endl;
        cout<<endl;

        printTabs(6); cout<<"        Press Enter to continue..."<<endl;
        cin.ignore();
        cin.get();
        return;
    }

    int index = num - 1;

    // Call function to update recipe items
    updateRecipeItems(index, num);

    cout<<endl;
    cout<<"\033[47m";
    cout<<"\033[30m";
    printTabs(5); cout<<"                                                           "<<endl;
    printTabs(5); cout<<"  [1] Update another Recipe                                "<<endl;
    printTabs(5); cout<<"  [2] Back to Homepage                                     "<<endl;
    printTabs(5); cout<<"  [3] Exit the Program                                     "<<endl;
    printTabs(5); cout<<"                                                           \033[0m"<<endl;
    cout<<endl;

    int option;

    printTabs(5); cout<<"  Enter Option: ";
    cin>>option;

    switch (option)
    {
        case 1:
            updateRecipe();
            break;
        case 2:
            return;
        case 3:
            printTabs(5); cout<<"  Exiting the program..."<<endl;
            exit(0);
        default:
            cout<<endl;
            cout<<"\033[97m";
            cout<<"\033[41m";
            printTabs(5); cout<<"                                                           "<<endl;
            printTabs(5); cout<<"                      Invalid Choice!                      "<<endl;
            printTabs(5); cout<<"                                                           \033[0m"<<endl;
            cout<<endl;
            printTabs(5); cout<<"  Exiting the program..."<<endl;
            exit(1);
    }
}

void updateRecipeItems(int index, int num) 
{
    clearScreen();

    cout<<"\033[46m";
    cout<<"\033[97m"; // Set background to cyan and text to white
    printTabs(5); cout<<"                                                           "<<endl;
    printTabs(5); cout<<"                    Update Recipe                          "<<endl;
    printTabs(5); cout<<"                                                           \033[0m"<<endl;
    cout<<endl;

    // Display existing recipe details
    printTabs(5); cout<<"  Existing Recipe Details:"<<endl;

    viewRecipe(num);

    cout<<endl;

    string choice;

    printTabs(5); cout<<"  Confirm to Update Recipe No. "<<num<<"? [Y/N]: ";
    getline(cin, choice);

    if (choice == "Y" || choice == "y")
    {
        clearScreen();

        bool validInput = true;

        cout<<"\033[97m";
        cout<<"\033[42m"; // Set text to white and background to green
        printTabs(5); cout<<"                                                           "<<endl;
        printTabs(5); cout<<"             Starting Update of Recipe No." << num << "!               "<<endl;
        printTabs(5); cout<<"                                                           \033[0m"<<endl;
        cout<<endl;

        // Update recipe name
        printTabs(5); cout<<"  Recipe Name: ";
        getline(cin, recipes[index].name);

        int ingredients_qty = ingredientQtyChecker();

        // Resize ingredients vector
        recipes[index].ingredients.resize(ingredients_qty);

        // Prompt for each ingredient
        for (int i = 0; i < ingredients_qty; ++i) 
        {
            printTabs(5); cout<<"  Ingredient "<< i + 1 <<":"<<endl;
            printTabs(5); cout<<"     Name: ";
            getline(cin, recipes[index].ingredients[i].name);
            printTabs(5); cout<<"     Unit: ";
            getline(cin, recipes[index].ingredients[i].unit);
        }

        // Prompt for number of instruction steps
        int instruction_qty = instructionQtyChecker();

        // Resize instruction vector
        recipes[index].instruction.resize(instruction_qty);

        // Prompt for each instruction step
        for (int i = 0; i < instruction_qty; ++i) 
        {
            printTabs(5); cout<< "     Step "<< i + 1 <<": ";
            getline(cin, recipes[index].instruction[i]);
        }

        // Update cooking time, difficulty level, and category
        printTabs(5); cout<<"  Cooking Time: ";
        getline(cin, recipes[index].cooking_time);

        // Prompt for difficulty level
        cout<<endl;
        printTabs(5); cout<<"  Select Cooking Difficulty Level:"<<endl;
        printTabs(5); cout<<"     [1] Beginner Level"<<endl;
        printTabs(5); cout<<"     [2] Intermediate Level"<<endl;
        printTabs(5); cout<<"     [3] Advanced Level"<<endl;
        printTabs(5); cout<<"  Enter Option: ";

        int difficultyOption;

        cin>>difficultyOption;
        cin.ignore(); // Consume the newline left by cin

        switch (difficultyOption) 
        {
            case 1:
                recipes[index].difficulty_level = Beginner;
                break;
            case 2:
                recipes[index].difficulty_level = Intermediate;
                break;
            case 3:
                recipes[index].difficulty_level = Advanced;
                break;
            default:
                cout<<endl;
                cout<<"\033[97m";
                cout<<"\033[41m";
                printTabs(5); cout<<"                                                           "<<endl;
                printTabs(5); cout<<"                      Invalid Option!                      "<<endl;
                printTabs(5); cout<<"         Setting difficulty to Beginner by default.         "<<endl;
                printTabs(5); cout<<"                                                           \033[0m"<<endl;
                cout<<endl;

                recipes[index].difficulty_level = Beginner;
                break;
            }

            cout<<endl;
            printTabs(5); cout<<"  Select Category:"<<endl;
            printTabs(5); cout<<"     [1] Appetizer     [4] Drink    [7] Breakfast"<<endl;
            printTabs(5); cout<<"     [2] Main Course   [5] Soup     [8] Side Dish"<<endl;
            printTabs(5); cout<<"     [3] Dessert       [6] Snack    [9] Other"<<endl;
            printTabs(5); cout<<"  Enter Option: ";
                
            int categoryOption;

            cin>>categoryOption;
            cin.ignore(); // Consume the newline left by cinm

            switch (categoryOption) 
            {
                case 1:
                    recipes[index].category = Appetizer;
                    break;
                case 2:
                    recipes[index].category = MainCourse;
                    break;
                case 3:
                    recipes[index].category = Dessert;
                    break;
                case 4:
                    recipes[index].category = Drink;
                    break;
                case 5:
                    recipes[index].category = Soup;
                    break;
                case 6:
                    recipes[index].category = Snack;
                    break;
                case 7:
                    recipes[index].category = Breakfast;
                    break;
                case 8:
                    recipes[index].category = SideDish;
                    break;
                case 9:
                    recipes[index].category = Other;
                    break;
                default:
                    cout<<endl;
                    cout<<"\033[97m";
                    cout<<"\033[41m";
                    printTabs(5); cout<<"                                                           "<<endl;
                    printTabs(5); cout<<"                      Invalid Option!                      "<<endl;
                    printTabs(5); cout<<"          Setting category to Other by default.            "<<endl;
                    printTabs(5); cout<<"                                                           \033[0m"<<endl;
                    cout<<endl;
                        
                    recipes[index].category = Other;
                    break;
            }

            // Display success message for recipe update
            cout<<endl;
            cout<<"\033[97m";
            cout<<"\033[42m"; // Set text to white and background to green
            printTabs(5); cout<<"                                                           "<<endl;
            printTabs(5); cout<<"               Recipe Updated Successfully!                "<<endl;
            printTabs(5); cout<<"                                                           \033[0m"<<endl;
            cout<<endl;
            
            // Save recipe changes to file and reload recipes
            saveRecipe();
            loadRecipe();

            printTabs(6); cout<<"        Press Enter to continue...";
            cin.ignore(); // Wait for user to press Enter to continue

            // Clear screen and display updated recipe details
            clearScreen();

            cout<<"\033[46m";
            cout<<"\033[97m"; // Set background to cyan and text to white
            printTabs(5); cout<<"                                                           "<<endl;
            printTabs(5); cout<<"                    Update Recipe                          "<<endl;
            printTabs(5); cout<<"                                                           \033[0m"<<endl;
            cout<<endl;

            printTabs(5); cout<<"  Updated Recipe Details:"<<endl;

            viewRecipe(num);

            if (recipes[index].isFavorite == 0)
            {
                printTabs(5); cout<<"  This recipe is not added to favorites"<<endl;
                addToFavorites(index);
            } 
            else if (recipes[index].isFavorite == 1)
            {
                printTabs(5); cout<<"  This recipe is in favorites"<<endl;
                removeFromFavorites(index);
            }
        }
    else 
    {
        // Display message if update is cancelled
        cout<<endl;
        cout<<"\033[97m";
        cout<<"\033[41m"; // Set text to white and background to red
        printTabs(5); cout<<"                                                           "<<endl;
        printTabs(5); cout<<"                     Update Cancelled!                     "<<endl;
        printTabs(5); cout<<"                                                           \033[0m"<<endl;
        cout<<endl;

        printTabs(6); cout<<"        Press Enter to continue...";
        cin.ignore();
        cin.get();
        return;
    }
}

void searchRecipe() 
{
    clearScreen();

    ifstream read("recipes.txt");

    if (!read.is_open()) 
    {
        cout<<"\033[97m\033[41m";
        printTabs(5); cout<<"                                                           "<<endl;
        printTabs(5); cout<<"                  Unable to open file!                     "<<endl;
        printTabs(5); cout<<"                                                           \033[0m"<<endl;

        // Prompt user to continue
        cout<<endl;
        printTabs(6); cout<< "        Press Enter to continue...";
        cin.ignore();
        cin.get();

        return;
    }

    loadRecipe(); // Assuming loadRecipe() function loads all recipes into memory

    cout<<"\033[46m";
    cout<<"\033[97m";
    printTabs(5); cout<<"                                                           "<<endl;
    printTabs(5); cout<<"                    Search Recipe                          "<<endl;
    printTabs(5); cout<<"                                                           \033[0m"<<endl;
    cout<<endl;

    cin.ignore(); // Clear input buffer
    printTabs(5); cout<<"  Enter Recipe Name to Search: ";
    string searchName;
    getline(cin, searchName);

    bool found = false;
    int totalRecipes;

    read>>totalRecipes;
    read.ignore();  // Ignore the newline after the integer

    for (int i = 0; i < totalRecipes; i++) 
    {
        // Read recipe name from file
        getline(read, recipes[i].name, '|');

        int ingredients_qty;

        read>>ingredients_qty;
        read.ignore();
        recipes[i].ingredients.resize(ingredients_qty);
        
        for (int j = 0; j < ingredients_qty; ++j) 
        {
            getline(read, recipes[i].ingredients[j].name, '|');
            getline(read, recipes[i].ingredients[j].unit, '|');
        }

        int instruction_qty;
        read>>instruction_qty;
        read.ignore();
        recipes[i].instruction.resize(instruction_qty);

        for (int j = 0; j < instruction_qty; ++j) 
        { 
            getline(read, recipes[i].instruction[j], '|');
        }

        getline(read, recipes[i].cooking_time, '|');

        int difficultyLevel;
        read>>difficultyLevel;
        read.ignore();

        int category;
        read>>category;
        read.ignore();

        int isFavoriteInt;
        read>>isFavoriteInt;
        read.ignore();

        recipes[i].difficulty_level = static_cast<DifficultyLevel>(difficultyLevel);
        recipes[i].category = static_cast<Category>(category);
        recipes[i].isFavorite = (isFavoriteInt == 1);

        if (recipes[i].name == searchName) 
        {
            found = true;

            clearScreen();
            cout<<"\033[97m";
            cout<<"\033[42m";
            printTabs(5); cout<<"                                                           "<<endl;
            printTabs(5); cout<<"                Recipe Found Successfully!                 "<<endl;
            printTabs(5); cout<<"                                                           \033[0m"<<endl;
            cout<<endl;

            printTabs(5); cout<<"  Recipe Name: "<<recipes[i].name<<endl;
            printTabs(5); cout<<"  Ingredients:"<<endl;

            for (int j = 0; j < ingredients_qty; ++j) 
            {
                printTabs(5); cout<<"    - "<<recipes[i].ingredients[j].name<<" ("<<recipes[i].ingredients[j].unit<<")"<<endl;
            }

            printTabs(5); cout<<"  Instructions:"<<endl;

            for (int j = 0; j < instruction_qty; ++j) 
            {
                printTabs(5); cout<< "    Step "<< j + 1 <<": "<<recipes[i].instruction[j]<<endl;
            }

            printTabs(5); cout<<"  Cooking Time: "<<recipes[i].cooking_time<<endl;
            printTabs(5); cout<<"  Difficulty Level: "<<difficultyLevelToString(recipes[i].difficulty_level)<<endl;
            printTabs(5); cout<<"  Category: "<<categoryToString(recipes[i].category)<<endl;
            cout << endl;

            break; // Exit the loop once recipe is found
        }
    }

    read.close();

    if (!found) 
    {
        cout<<"\033[97m";
        cout<<"\033[41m";
        printTabs(5); cout<<"                                                           "<<endl;
        printTabs(5); cout<<"                     Recipe Not Found!                     "<<endl;
        printTabs(5); cout<<"                                                           \033[0m"<<endl;
        cout<<endl;
    }

    cout<<"\033[47m\033[30m";
    printTabs(5); cout<<"                                                           "<<endl;
    printTabs(5); cout<<"  [1] Search another Recipe                                "<<endl;
    printTabs(5); cout<<"  [2] Back to Homepage                                     "<<endl;
    printTabs(5); cout<<"  [3] Exit the Program                                     "<<endl;
    printTabs(5); cout<<"                                                           \033[0m"<<endl;
    cout<<endl;
    printTabs(5); cout<<"  Enter Option: ";
    int option;
    cin>>option;

    switch (option) 
    {
        case 1:
            searchRecipe(); // Recursive call to search another recipe
            break;
        case 2:
            return; // Return to the main loop
        case 3:
            printTabs(5); cout<<"  Exiting the program..." << endl;
            exit(0); // Exit the program
        default:
            cout<<"\033[97m\033[41m";
            printTabs(5); cout<<"                                                           "<<endl;
            printTabs(5); cout<<"                      Invalid Choice!                      "<<endl;
            printTabs(5); cout<<"                                                           \033[0m"<<endl;
            printTabs(5); cout<<"  Exiting the program..."<<endl;
            exit(1);
    }
}

void deleteRecipe() 
{
    ifstream file("recipes.txt");

    if (!file.is_open()) 
    {
        cout<<endl;
        cout<<"\033[97m";
        cout<<"\033[41m";
        printTabs(5); cout<<"                                                           "<<endl;
        printTabs(5); cout<<"                  Unable to open file!                     "<<endl;
        printTabs(5); cout<<"                                                           \033[0m"<<endl;
        cout<<endl;

        printTabs(6); cout<<"        Press Enter to continue...";
        cin.ignore();
        cin.get();
        file.close();
        return;
    }

    clearScreen();

    cout<<"\033[46m";
    cout<<"\033[97m";
    printTabs(5); cout<<"                                                           "<<endl;
    printTabs(5); cout<<"                    Delete Recipe                          "<<endl;
    printTabs(5); cout<<"                                                           \033[0m"<<endl;
    cout<<endl;

    printTabs(5); cout<<"  Existing Recipes:"<<endl;

    for (int i = 0; i < count; i++) 
    {
        printTabs(5); cout<<"  "<< i + 1 <<". "<<recipes[i].name<<endl;
    }

    int num = 0;
    string choice;

    cout<<endl;
    printTabs(5); cout<<"  Enter Recipe ID to Delete: ";
    cin>>num;
    cin.ignore();

    int index = num - 1;

    if (index < 0 || index >= count) 
    {
        cout<<endl;
        cout<<"\033[97m";
        cout<<"\033[41m";
        printTabs(5); cout<<"                                                           "<<endl;
        printTabs(5); cout<<"                    Invalid Recipe ID!                     "<<endl;
        printTabs(5); cout<<"                                                           \033[0m"<<endl;
        cout<<endl;

        file.close();
        return;
    }

    cout<<endl;
    cout<<"\033[97m";
    cout<<"\033[42m";
    printTabs(5); cout<<"                                                           "<<endl;
    printTabs(5); cout<<"                Recipe Found Successfully!                 "<<endl;
    printTabs(5); cout<<"                                                           \033[0m"<<endl;
    cout<<endl;

    printTabs(5); cout<<"  Confirm to Delete Recipe No. "<<num<<"? [Y/N]: ";
    getline(cin, choice);

    if (choice == "Y" || choice == "y") 
    {
        for (int i = index; i < count - 1; i++) 
        {
            recipes[i] = recipes[i + 1];
        }
        count--;

        ofstream write("recipes.txt");

        if (write.is_open()) 
        {
            write<<count<<endl;

            for (int i = 0; i < count; i++) 
            {
                write<<recipes[i].name<<"|"<<recipes[i].ingredients.size()<<"|";

                for (size_t j = 0; j < recipes[i].ingredients.size(); j++) 
                {
                    write<<recipes[i].ingredients[j].name<<"|"<<recipes[i].ingredients[j].unit<<"|";
                }
                write<<recipes[i].instruction.size()<<"|";

                for (size_t j = 0; j < recipes[i].instruction.size(); j++) 
                {
                    write<<recipes[i].instruction[j]<<"|";
                }
                write<<recipes[i].cooking_time<<"|"<<difficultyLevelToString(recipes[i].difficulty_level)<<"|"<<categoryToString(recipes[i].category)<<endl;
            }
            write.close();

            cout<<endl;
            cout<<"\033[97m";
            cout<<"\033[42m";
            printTabs(5); cout<<"                                                           "<<endl;
            printTabs(5); cout<<"               Recipe Deleted Successfully!                "<<endl;
            printTabs(5); cout<<"                                                           \033[0m"<<endl;
        } 
        else 
        {
            cout<<endl;
            cout<<"\033[97m";
            cout<<"\033[41m";
            printTabs(5); cout<<"                                                           "<<endl;
            printTabs(5); cout<<"                    Unable to open file!                   "<<endl;
            printTabs(5); cout<<"                                                           \033[0m"<<endl;
            cout<<endl;
        }
    } 
    else 
    {
        cout<<endl;
        cout<<"\033[97m";
        cout<<"\033[42m";
        printTabs(5); cout<<"                                                           "<<endl;
        printTabs(5); cout<<"                   Deletion Cancelled!                     "<<endl;
        printTabs(5); cout<<"                                                           \033[0m"<<endl;
    }

    cout<<endl;
    cout<<"\033[47m";
    cout<<"\033[30m";
    printTabs(5); cout<<"                                                           "<<endl;
    printTabs(5); cout<<"  [1] Delete another Recipe                                "<<endl;
    printTabs(5); cout<<"  [2] Back to Homepage                                     "<<endl;
    printTabs(5); cout<<"  [3] Exit the Program                                     "<<endl;
    printTabs(5); cout<<"                                                           \033[0m"<<endl;
    cout<<endl;
    printTabs(5); cout<<"  Enter Option: ";

    int option;
    cin>>option;

    switch (option) 
    {
        case 1:
            deleteRecipe();
            break;
        case 2:
            return;
        case 3:
            printTabs(5); cout<<"  Exiting the program..."<<endl;
            exit(0);
        default:
            cout<<endl;
            cout<<"\033[97m";
            cout<<"\033[41m";
            printTabs(5); cout<<"                                                           "<<endl;
            printTabs(5); cout<<"                      Invalid Choice!                      "<<endl;
            printTabs(5); cout<<"                                                           \033[0m"<<endl;
            cout<<endl;
            cout<<"  Exiting the program..."<<endl;
            exit(1);
    }
}

void checkExistingRecipe() 
{
    clearScreen();
    // Open the file to read
    ifstream file("recipes.txt");

    if (!file.is_open()) 
    {
        cout<<endl;
        cout<<"\033[97m";
        cout<<"\033[41m";
        printTabs(5); cout<<"                                                           "<<endl;
        printTabs(5); cout<<"                  Unable to open file!                     "<<endl;
        printTabs(5); cout<<"                                                           \033[0m"<<endl;

        // Prompt user to continue
        cout<<endl;
        printTabs(6); cout<<"        Press Enter to continue...";
        cin.ignore();
        cin.get();

        return;
    }

    clearScreen();

    if(file.is_open())
    {
        loadRecipe();
        cout<<"\033[46m";
        cout<<"\033[97m";
        printTabs(5); cout<<"                                                           "<<endl;
        printTabs(5); cout<<"                   Check Existing Recipe                   "<<endl;
        printTabs(5); cout<<"                                                           \033[0m"<<endl;
        cout<<endl;

        printTabs(3); cout<<" "<<setw(15)<<left<<"Recipe No."<<setw(25)<<left<<"Recipe Name"<<setw(25)<<left<<"Category"<<setw(20)<<left<<"Difficulty Level"<<endl;
        printTabs(3); cout<<" -----------------------------------------------------------------------------------"<<endl;

        for (int i = 0; i < count; i++) 
        {
            printTabs(3);
            cout<<"    "<<setw(15)<<left<< i + 1;
            cout<<setw(25)<<left<<recipes[i].name;
            cout<<setw(25)<<left<<categoryToString(recipes[i].category);
            cout<<setw(20)<<left<<difficultyLevelToString(recipes[i].difficulty_level)<<endl;
        }

        cout<<endl;
        cout<<"\033[47m";
        cout<<"\033[30m";
        printTabs(5); cout<<"                                                           "<<endl;
        printTabs(5); cout<<"  [1] View Recipe Details                                  "<<endl;
        printTabs(5); cout<<"  [2] Back to Homepage                                     "<<endl;
        printTabs(5); cout<<"  [3] Exit the Program                                     "<<endl;
        printTabs(5); cout<<"                                                           \033[0m"<<endl;
        cout<<endl;
        printTabs(5); cout<<"  Enter Option: ";
        int option;
        cin>>option;

        switch (option) 
        {
            case 1: 
            {
                int recipeNumber;
                printTabs(5); cout<<"  Enter Recipe Number: ";
                cin>>recipeNumber;

                // Validate the recipe number
                if (recipeNumber >= 1 && recipeNumber <= count) 
                {
                    viewRecipe(recipeNumber);

                    cout<<endl;
                    printTabs(6); cout<<"  Press Enter to return to the main menu...";

                    cin.ignore();
                    cin.get();
                } 
                else 
                {
                    cout<<endl;
                    cout<<"\033[97m";
                    cout<<"\033[41m";
                    printTabs(5); cout<<"                                                           "<<endl;
                    printTabs(5); cout<<"                    Invalid Recipe Number!                 "<<endl;
                    printTabs(5); cout<<"                                                           \033[0m"<<endl;
                    cout<<endl;
                    printTabs(6); cout<<"  Press Enter to return to the main menu...";

                    cin.ignore();
                    cin.get();
                }
                // After viewing recipe details, stay on existing recipe page
                checkExistingRecipe();
                return;
            }
            case 2:
                // Return to the main loop or homepage function
                return;
            case 3:
                printTabs(5); cout<< "  Exiting the program..."<<endl;
                exit(0); // Exit the program
            default:
                cout<<endl;
                cout<<"\033[97m";
                cout<<"\033[41m";
                printTabs(5); cout<<"                                                           "<<endl;
                printTabs(5); cout<<"                      Invalid Choice!                      "<<endl;
                printTabs(5); cout<<"                                                           \033[0m"<<endl;
                cout<<endl;
                printTabs(5); cout<<"  Exiting the program..."<<endl;
                exit(1);
        }
    }
}

void viewRecipe(int recipeNumber) 
{
    clearScreen();

    cout<<"\033[46m";  // Set background color to cyan
    cout<<"\033[97m";  // Set text color to white
    printTabs(5); cout<<"                                                           "<<endl;
    printTabs(5); cout<<"                       View Recipe                         "<<endl;
    printTabs(5); cout<<"                                                           \033[0m"<<endl;
    cout<<endl;

    // Open the file to read
    ifstream read("recipes.txt");

    // Check if the file is open
    if (read.is_open()) 
    {
        // Read the total count of recipes
        int totalRecipes;
        read>>totalRecipes;
        read.ignore();  // Ignore the newline after the integer

        // Check if the recipeNumber is valid
        if (recipeNumber >= 1 && recipeNumber <= totalRecipes)
        {
            int index = recipeNumber - 1;

            // Skip to the selected recipe in the file
            for (int i = 0; i < index; i++) 
            {
                string line;
                getline(read, line); // Read and discard lines until the desired recipe
            }

            // Display the details of the selected recipe
            printTabs(5); cout<< "  Recipe Name: "<<recipes[index].name<<endl;
            printTabs(5); cout<< "  Ingredients:"<<endl;

            for (size_t j = 0; j < recipes[index].ingredients.size(); j++) 
            {
                printTabs(5); cout << "    - " <<recipes[index].ingredients[j].name<<" ("<<recipes[index].ingredients[j].unit<<")"<<endl;
            }

            printTabs(5); cout<<"  Instructions:"<<endl;

            for (size_t j = 0; j < recipes[index].instruction.size(); j++) 
            {
                printTabs(5); cout<<"    Step "<< j + 1 <<": "<<recipes[index].instruction[j]<<endl;
            }

            printTabs(5); cout<<"  Cooking Time: "<<recipes[index].cooking_time<<endl;
            printTabs(5); cout<<"  Difficulty Level: "<<difficultyLevelToString(recipes[index].difficulty_level)<<endl;
            printTabs(5); cout<<"  Category: "<<categoryToString(recipes[index].category)<<endl;
            cout<<endl;
        }
        else 
        {
            // Display error message for invalid recipe ID
            cout<<endl;
            cout<<"\033[97m";
            cout<<"\033[41m";
            printTabs(5); cout<<"                                                           "<<endl;
            printTabs(5); cout<<"                    Invalid Recipe ID!                     "<<endl;
            printTabs(5); cout<<"                                                           \033[0m"<<endl;
        }
        // Close the file
        read.close();
    }
    else 
    {
        // Display error message for unable to open file
        cout<<endl;
        cout<<"\033[97m";
        cout<<"\033[41m";
        printTabs(5); cout<<"                                                           "<<endl;
        printTabs(5); cout<<"                  Unable to open file!                     "<<endl;
        printTabs(5); cout<<"                                                           \033[0m"<<endl;
    }
    cin.ignore(); // Wait for user input to continue
}

void viewRecipeDetails(int index) 
{
    clearScreen();
    cout<<"\033[46m";  // Set background color to cyan
    cout<<"\033[97m";  // Set text color to white
    printTabs(5); cout<<"                                                           "<<endl;
    printTabs(5); cout<<"                   Recipe Details                          "<<endl;
    printTabs(5); cout<<"                                                           \033[0m"<<endl;
    cout<<endl;

    // Display details of the recipe at the given index
    printTabs(5); cout<<"  Recipe Name: "<<recipes[index].name<<endl;
    printTabs(5); cout<<"  Ingredients:"<<endl;

    for (size_t i = 0; i < recipes[index].ingredients.size(); ++i) 
    {
        printTabs(5); cout<<"     - "<<recipes[index].ingredients[i].name<<" ("<<recipes[index].ingredients[i].unit<<")"<<endl;
    }
    printTabs(5); cout<<"  Instructions:"<<endl;

    for (size_t i = 0; i < recipes[index].instruction.size(); ++i) 
    {
        printTabs(5); cout<< " "<<"    Step "<< i + 1 <<": "<<recipes[index].instruction[i]<<endl;
    }
    printTabs(5); cout<<"  Cooking Time: "<<recipes[index].cooking_time<<endl;
    printTabs(5); cout<<"  Difficulty Level: "<<difficultyLevelToString(recipes[index].difficulty_level)<<endl;
    printTabs(5); cout<<"  Category: "<<categoryToString(recipes[index].category)<<endl;

}

void chooseCategory() 
{
    clearScreen();
    cout<<"\033[48;2;255;255;255m";
    cout<<"\033[30m";
    printTabs(5); cout<<"                                                           "<<endl; 
    printTabs(5); cout<<"                   Select a Category!                      "<<endl; 
    printTabs(5); cout<<"                                                           "<<endl;
    printTabs(5); cout<<"  [1] Appetizer                                            "<<endl; 
    printTabs(5); cout<<"  [2] Main Course                                          "<<endl; 
    printTabs(5); cout<<"  [3] Dessert                                              "<<endl; 
    printTabs(5); cout<<"  [4] Drink                                                "<<endl; 
    printTabs(5); cout<<"  [5] Soup                                                 "<<endl; 
    printTabs(5); cout<<"  [6] Snack                                                "<<endl; 
    printTabs(5); cout<<"  [7] Breakfast                                            "<<endl; 
    printTabs(5); cout<<"  [8] Side Dish                                            "<<endl;
    printTabs(5); cout<<"  [9] Other                                                "<<endl; 
    printTabs(5); cout<<"                                                           \033[0m"<<endl;
    cout<<endl;

    printTabs(5); cout<<"  Enter your choice: ";
    
    int categoryOption;
    cin>>categoryOption;
    cin.ignore(); // Consume the newline left by cin

    Category category;
 
    switch (categoryOption) 
    {
        case 1:
            category = Appetizer;
            break;
        case 2:
            category = MainCourse;
            break;
        case 3:
            category = Dessert;
            break;
        case 4:
            category = Drink;
            break;
        case 5:
            category = Soup;
            break;
        case 6:
            category = Snack;
            break;
        case 7:
            category = Breakfast;
            break;
        case 8:
            category = SideDish;
            break;
        case 9:
            category = Other;
            break;
        default:
            cout<<endl;
            cout<<"\033[97m";
            cout<<"\033[41m";
            printTabs(5); cout<<"                                                           "<<endl;
            printTabs(5); cout<<"                      Invalid Option!                      "<<endl;
            printTabs(5); cout<<"          Setting category to Other by default.            "<<endl;
            printTabs(5); cout<<"                                                           \033[0m"<<endl;
            cout<<endl;

            category = Other;
            break;
    }
    displayByCategory(category);
}

void chooseDifficulty()
{
    clearScreen();

    cout<<"\033[48;2;255;255;255m";
    cout<<"\033[30m";
    printTabs(5); cout<<"                                                           "<<endl; 
    printTabs(5); cout<<"                Select a Cooking Difficulty!               "<<endl; 
    printTabs(5); cout<<"                                                           "<<endl;
    printTabs(5); cout<<"  [1] Beginner Level                                       "<<endl; 
    printTabs(5); cout<<"  [2] Intermediate Level                                   "<<endl; 
    printTabs(5); cout<<"  [3] Advanced Level                                       "<<endl; 
    printTabs(5); cout<<"                                                           \033[0m"<<endl;
    cout<<endl;

    printTabs(5); cout<<"  Enter your choice: ";

    int levelOption;
    cin>>levelOption;
    cin.ignore(); // Consume the newline left by cin
    
    DifficultyLevel level;

    switch (levelOption) 
    {
        case 1:
            level = Beginner;
            break;
        case 2:
            level = Intermediate;
            break;
        case 3:
            level = Advanced;
            break;
        default:
            cout<<endl;
            cout<<"\033[97m";
            cout<<"\033[41m";
            printTabs(5); cout<<"                                                           "<<endl;
            printTabs(5); cout<<"                      Invalid Option!                      "<<endl;
            printTabs(5); cout<<"         Setting difficulty to Beginner by default.         "<<endl;
            printTabs(5); cout<<"                                                           \033[0m"<<endl;
            cout<<endl;

            level = Beginner;
            break;
    }
    displayByDifficulty(level);
}

void displayFavoriteRecipes() 
{
    clearScreen();

    cout<<"\033[46m";  // Set background color to cyan
    cout<<"\033[97m";  // Set text color to white
    printTabs(5); cout<<"                                                           "<<endl;
    printTabs(5); cout<<"                   Favorite Recipes                        "<<endl;
    printTabs(5); cout<<"                                                           \033[0m"<<endl;
    cout<<endl;

    // Display header for the table
    printTabs(3); cout<<" "<<setw(15)<<left<<"Recipe No."<<setw(25)<<left<<"Recipe Name"<<setw(25)<<left<<"Category"<<setw(20)<<left<<"Difficulty Level"<<endl;
    printTabs(3); cout<<" -----------------------------------------------------------------------------------"<<endl;

    vector<int> favoriteIndexes;

    // Iterate through recipes to display favorites
    int favoriteCount = 0;

    for (int i = 0; i < count; i++) 
    {
        if (recipes[i].isFavorite) 
        {
            printTabs(3);
            cout<<"    "<<setw(12)<<left<< favoriteCount + 1;
            cout<<setw(25)<<left<<recipes[i].name;
            cout<<setw(24)<<left<<categoryToString(recipes[i].category);
            cout<<setw(20)<<left<<difficultyLevelToString(recipes[i].difficulty_level)<<endl;
            favoriteIndexes.push_back(i); // Store index of the favorite recipe
            favoriteCount++;
        }
    }

    // If no favorites found, display message
    if (favoriteCount == 0) 
    {
        cout<<endl;
        printTabs(7); cout<<"No favorite recipes found."<<endl;
        cout<<endl;
    }

    cout<<"\033[47m";
    cout<<"\033[30m";
    cout<<endl;
    printTabs(5); cout<<"                                                           "<<endl;
    printTabs(5); cout<<"  [1] View Recipe Details                                  "<<endl;
    printTabs(5); cout<<"  [2] Remove a Recipe from Favorites                       "<<endl;
    printTabs(5); cout<<"  [3] Back to Homepage                                     "<<endl;
    printTabs(5); cout<<"  [4] Exit the Program                                     "<<endl;
    printTabs(5); cout<<"                                                           \033[0m"<<endl;
    cout<<endl;

    printTabs(5); cout<<"  Enter Option: ";
    int option;
    cin>>option;

    switch (option) 
    {
        case 1: 
        {
            int recipeNumber;

            printTabs(5); cout<<"  Enter Recipe Number: ";
            cin>>recipeNumber;

            // Validate the recipe number against favorites count
            if (recipeNumber >= 1 && recipeNumber <= favoriteCount) 
            {
                int index = favoriteIndexes[recipeNumber - 1]; // Get index of the selected favorite recipe
                viewRecipeDetails(index);
                 // View recipe details
                cout<<endl;
                cout<<"\033[47m";
                cout<<"\033[30m";
                printTabs(5); cout<<"                                                           "<<endl;
                printTabs(5); cout<<"  [1] Back to Homepage                                     "<<endl;
                printTabs(5); cout<<"  [2] Exit the Program                                     "<<endl;
                printTabs(5); cout<<"                                                           \033[0m"<<endl;
                cout<<endl;

                printTabs(5); cout<<"  Enter Option: ";
                int option;
                cin>>option;

                switch (option) 
                {
                    case 1:
                        // Return to homepage
                        return;
                    case 2:
                        // Exit the program
                        printTabs(5); cout<<"  Exiting the program..."<<endl;
                        exit(0);
                    default:
                        cout<<endl;
                        cout<<"\033[97m";
                        cout<<"\033[41m";
                        printTabs(5); cout<<"                                                           "<<endl;
                        printTabs(5); cout<<"                      Invalid Choice!                      "<<endl;
                        printTabs(5); cout<<"                                                           \033[0m"<<endl;
                        cout<<endl;
                        printTabs(5); cout<<"  Exiting the program..."<<endl;
                        exit(1);
                    }
            } 
            else 
            {
                cout<<endl;
                cout<<"\033[97m";
                cout<<"\033[41m";
                printTabs(5); cout<<"                                                           "<<endl;
                printTabs(5); cout<<"                    Invalid Recipe Number!                 "<<endl;
                printTabs(5); cout<<"                                                           \033[0m"<<endl;
                cout<<endl;

                printTabs(6); cout<< "        Press Enter to continue...";
                cin.ignore();
                cin.get();
            }
            // After viewing recipe details, stay on favorite recipes page
            displayFavoriteRecipes();
            return;
        }
        case 2:
        {
            int recipeNumber;
            printTabs(5); cout<<"  Enter Recipe Number: ";
            cin>>recipeNumber;

            // Validate the recipe number against favorites count
            if (recipeNumber >= 1 && recipeNumber <= favoriteCount) 
            {
                int index = favoriteIndexes[recipeNumber - 1]; // Get index of the selected favorite recipe
                removeFromFavorites(index); // View recipe details

                cout<<endl;
                printTabs(6); cout<< "        Press Enter to continue...";
                cin.ignore();
                cin.get();
            } 
            else 
            {
                cout<<endl;
                cout<<"\033[97m";
                cout<<"\033[41m";
                printTabs(5); cout<<"                                                           "<<endl;
                printTabs(5); cout<<"                    Invalid Recipe Number!                 "<<endl;
                printTabs(5); cout<<"                                                           \033[0m"<<endl;
                cout<<endl;

                printTabs(6); cout<< "        Press Enter to continue...";
                cin.ignore();
                cin.get();
            }
            // After viewing recipe details, stay on favorite recipes page
            displayFavoriteRecipes();
            return;
        }
        case 3:
            // Return to the main loop or homepage function
            return;
        case 4:
            printTabs(5); cout<<"  Exiting the program..."<<endl;
            exit(0); // Exit the program
        default:
            cout<<endl;
            cout<<"\033[97m";
            cout<<"\033[41m";
            printTabs(5); cout<<"                                                           "<<endl;
            printTabs(5); cout<<"                      Invalid Choice!                      "<<endl;
            printTabs(5); cout<<"                                                           \033[0m"<<endl;
            cout<<endl;
            printTabs(5); cout<<"  Exiting the program..."<<endl;
            exit(1);
        }
}

void displayByCategory(Category category) 
{
    clearScreen();
    printTabs(5); cout<<"                                                                    "<<endl;
    printTabs(5); cout<<"             Recipes in Category: " << categoryToString(category)<<endl;
    printTabs(5); cout<<"                                                                    \033[0m"<<endl;
    cout<<endl;
   
    printTabs(6); cout<<"      "<<setw(20)<<left<<"Recipe No."<<setw(25)<<left<<"Recipe Name"<<endl;
    printTabs(6); cout<<"-----------------------------------------"<<endl;

    // Find recipes in the specified category
    vector<int> categIndexes; // Store indexes of recipes in the current category
    int categCount = 0;

    for (int i = 0; i < count; ++i) 
    {
        if (recipes[i].category == category) 
        {
            printTabs(7);
            cout<<" "<<setw(17)<<categCount + 1; // Recipe number
            cout<<setw(25)<<recipes[i].name<<endl; // Recipe name

            categIndexes.push_back(i); // Store index of the recipe
            categCount++;
        }
    }

    if (categCount == 0) 
    {
        cout<<"\033[97m";
        cout<<"\033[41m";
        printTabs(5); cout << "                                                           "<<endl;
        printTabs(5); cout << "            No recipes found in this category!             "<<endl;
        printTabs(5); cout << "                                                           \033[0m"<<endl;
        cout<<endl;

        cout<<"\033[47m";
        cout<<"\033[30m";
        printTabs(5); cout<<"                                                           "<<endl;
        printTabs(5); cout<<"  [1] Choose another Category                              "<<endl;
        printTabs(5); cout<<"  [2] Back to Homepage                                     "<<endl;
        printTabs(5); cout<<"  [3] Exit the Program                                     "<<endl;
        printTabs(5); cout<<"                                                           \033[0m"<<endl;
        cout<<endl;

        printTabs(5); cout<<"  Enter Option: ";
        int option;
        cin>>option;

        switch (option) 
        {
            case 1:
                chooseCategory();
                break;
            case 2:
                return; // Return to the main menu or homepage
            case 3:
                printTabs(5); cout<<"  Exiting the program..."<<endl;
                exit(0); // Exit the program
            default:
                cout<<endl;
                cout<<"\033[97m";
                cout<<"\033[41m";
                printTabs(5); cout<<"                                                           "<<endl;
                printTabs(5); cout<<"                      Invalid Option!                      "<<endl;
                printTabs(5); cout<<"                                                           \033[0m"<<endl;
                cout<<endl;
                printTabs(5); cout<<"  Exiting the program..."<<endl;
                exit(1);
        }
    } 
    else 
    {
        cout<<endl;
        cout<<"\033[47m";
        cout<<"\033[30m";
        printTabs(5); cout<<"                                                           "<<endl;
        printTabs(5); cout<<"  [1] View Recipe Details                                  "<<endl;
        printTabs(5); cout<<"  [2] Choose another Category                              "<<endl;
        printTabs(5); cout<<"  [3] Back to Homepage                                     "<<endl;
        printTabs(5); cout<<"  [4] Exit the Program                                     "<<endl;
        printTabs(5); cout<<"                                                           \033[0m"<<endl;
        cout<<endl;

        printTabs(5); cout<<"  Enter Option: ";
        int option;
        cin>>option;

        switch (option) 
        {
            case 1: 
            {
                int recipeNumber;
                
                printTabs(5); cout<<"  Enter Recipe Number: ";
                cin>>recipeNumber;

                // Validate the recipe number against the recipes in the category
                if (recipeNumber >= 1 && recipeNumber <= categCount) 
                {
                    int index = categIndexes[recipeNumber - 1]; // Get index of the selected recipe

                    viewRecipeDetails(index); // View recipe details

                    // After viewing recipe details, show menu again
                    cout<<endl;
                    cout<<"\033[47m";
                    cout<<"\033[30m";
                    printTabs(5); cout<<"                                                           "<<endl;
                    printTabs(5); cout<<"  [1] Choose another Category                              "<<endl;
                    printTabs(5); cout<<"  [2] Back to Homepage                                     "<<endl;
                    printTabs(5); cout<<"  [3] Exit the Program                                     "<<endl;
                    printTabs(5); cout<<"                                                           \033[0m"<<endl;
                    cout<<endl;

                    printTabs(5); cout<<"  Enter Option: ";
                    int option;
                    cin>>option;

                    switch (option) 
                    {
                        case 1:
                            chooseCategory();
                            break;
                        case 2:
                            return; // Return to the main menu or homepage
                        case 3:
                            printTabs(5); cout<<"  Exiting the program..."<<endl;
                            exit(0); // Exit the program
                        default:
                            cout<<endl;
                            cout<<"\033[97m";
                            cout<<"\033[41m";
                            printTabs(5); cout<<"                                                           "<<endl;
                            printTabs(5); cout<<"                      Invalid Option!                      "<<endl;
                            printTabs(5); cout<<"                                                           \033[0m"<<endl;
                            cout<<endl;
                            printTabs(5); cout<<"  Exiting the program..." << endl;
                            exit(1);
                    }
                } 
                else 
                {
                    cout<<endl;
                    cout<<"\033[97m";
                    cout<<"\033[41m";
                    printTabs(5); cout<<"                                                           "<<endl;
                    printTabs(5); cout<<"                    Invalid Recipe Number!                 "<<endl;
                    printTabs(5); cout<<"                                                           \033[0m"<<endl;
                    cout<<endl;

                    printTabs(6); cout<<"        Press Enter to continue...";
                    cin.ignore(); // Clear input buffer
                    cin.get(); // Wait for user to press Enter

                    chooseCategory();
                }
                break;
            }
            case 2:
                chooseCategory();
                break;
            case 3:
                return; // Return to the main menu or homepage
            case 4:
                printTabs(5); cout<<"  Exiting the program..."<<endl;
                exit(0); // Exit the program
            default:
                cout<<endl;
                cout<<"\033[97m";
                cout<<"\033[41m";
                printTabs(5); cout<<"                                                           "<<endl;
                printTabs(5); cout<<"                      Invalid Option!                      "<<endl;
                printTabs(5); cout<<"                                                           \033[0m"<<endl;
                cout<<endl;
                printTabs(5); cout<<"  Exiting the program..."<<endl;
                exit(1);
        }
    }
}



void addToFavorites(int index) 
{
    if (index < 0 || index >= count) 
    {
        cout<<"\033[97m";
        cout<<"\033[41m";
        printTabs(5); cout<<"                                                           "<<endl;
        printTabs(5); cout<<"                  Invalid recipe index!                    "<<endl;
        printTabs(5); cout<<"                                                           \033[0m"<<endl;
        cout<<endl;
        return;
    }

    string opt;

    printTabs(5); cout<<"  Add this recipe to favorites? [Y/N]: ";
    cin>>opt;

    if (opt == "Y" || opt == "y") 
    {
        recipes[index].isFavorite = true;
        cout<<endl;
        cout<<"\033[97m";
        cout<<"\033[42m";
        printTabs(5); cout<<"                                                           "<<endl;
        printTabs(5); cout<<"                Recipe added to Favorites!                 "<<endl;
        printTabs(5); cout<<"                                                           \033[0m"<<endl;
    } 
    else if (opt == "N" || opt == "n") 
    {
        recipes[index].isFavorite = false;
        cout<<endl;
        cout<<"\033[97m";
        cout<<"\033[42m";
        printTabs(5); cout<<"                                                           "<<endl;
        printTabs(5); cout<<"               Recipe not added to favorites!              "<<endl;
        printTabs(5); cout<<"                                                           \033[0m"<<endl;
    } 
    else 
    {
        cout<<endl;
        cout<<"\033[97m";
        cout<<"\033[41m";
        printTabs(5); cout<<"                                                           "<<endl;
        printTabs(5); cout<<"                     Invalid Input!                        "<<endl;
        printTabs(5); cout<<"              Recipe not added to Favorites!               "<<endl;
        printTabs(5); cout<<"                                                           \033[0m"<<endl;
    }

    // Save favorites to file after modification
    saveRecipe();
}

void removeFromFavorites(int index) 
{
    // Load recipes from file to update in-memory data
    loadRecipe();

    // Check if the index is valid
    if (index < 0 || index >= count) 
    {
        cout<<"\033[97m";
        cout<<"\033[41m";
        printTabs(5); cout<<"                                                           "<<endl;
        printTabs(5); cout<<"                  Invalid recipe index!                    "<<endl;
        printTabs(5); cout<<"                                                           \033[0m"<<endl;
        cout<<endl;
        return;
    }

    string opt;

    printTabs(5); cout<<"  Remove this recipe from favorites? [Y/N]: ";
    cin>>opt;

    if (opt == "Y" || opt == "y") 
    {
        recipes[index].isFavorite = false;
        cout<<endl;
        cout<<"\033[97m";
        cout<<"\033[42m";
        printTabs(5); cout<<"                                                           "<<endl;
        printTabs(5); cout<<"              Recipe removed from Favorites!               "<<endl;
        printTabs(5); cout<<"                                                           \033[0m"<<endl;

        // Save updated favorites to file after modification
        saveRecipe();
    } 
    else if (opt == "N" || opt == "n") 
    {
        cout<<endl;
        cout<<"\033[97m";
        cout<<"\033[42m";
        printTabs(5); cout<<"                                                           "<<endl;
        printTabs(5); cout<<"               Recipe remains in Favorites!                "<<endl;
        printTabs(5); cout<<"                                                           \033[0m"<<endl;
    } 
    else 
    {
        cout<<"\033[97m";
        cout<<"\033[41m";
        printTabs(5); cout<<"                                                           "<<endl;
        printTabs(5); cout<<"                     Invalid Input!                        "<<endl;
        printTabs(5); cout<<"            Recipe not removed from Favorites!             "<<endl;
        printTabs(5); cout<<"                                                           \033[0m"<<endl;
        cout<<endl;
        return;
    }
}

void printTabs(int tabNum) 
{
    for (int i = 0; i < tabNum; ++i) 
    {
        cout<<"\t";
    }
}

void clearScreen()
{
    cout<<"\033[2J\033[1;1H";
}

void displayByDifficulty(DifficultyLevel level) 
{
    clearScreen();

    printTabs(5); cout<<"                                                                    "<<endl;
    printTabs(5); cout<<"             Recipes in Difficulty Level: " << difficultyLevelToString(level)<<endl;
    printTabs(5); cout<<"                                                                    "<<endl;
    cout<<endl;

    // Find recipes in the specified category
    vector<int> levelIndexes; // Store indexes of recipes in the current category
    int levelCount = 0;

    for (int i = 0; i < count; ++i) 
    {
        if (recipes[i].difficulty_level == level) 
        {
            printTabs(6);
            cout<<setw(10)<<levelCount + 1; // Recipe number
            cout<<setw(22)<<recipes[i].name<<endl; // Recipe name
            levelIndexes.push_back(i); // Store index of the recipe
            levelCount++;
        }
    }

    cout<<endl;

    if (levelCount == 0) 
    {
        printTabs(7); cout<<" No recipes found in this difficulty level."<<endl;
        cout<< endl;
        cout<<"\033[47m";
        cout<<"\033[30m";
        printTabs(5); cout<<"                                                           "<<endl;
        printTabs(5); cout<<"  [1] Choose another Difficulty Level                      "<<endl;
        printTabs(5); cout<<"  [2] Back to Homepage                                     "<<endl;
        printTabs(5); cout<<"  [3] Exit the Program                                     "<<endl;
        printTabs(5); cout<<"                                                           \033[0m"<<endl;
        cout<<endl;

        printTabs(5); cout<<"  Enter Option: ";
        int option;
        cin>>option;

        switch (option) 
        {
            case 1:
                chooseDifficulty();
                break;
            case 2:
                return; // Return to the main menu or homepage
            case 3:
                printTabs(5); cout<<"  Exiting the program..."<<endl;
                exit(0); // Exit the program
            default:
                cout<<endl;
                cout<<"\033[97m";
                cout<<"\033[41m";
                printTabs(5); cout<<"                                                           "<<endl;
                printTabs(5); cout<<"                      Invalid Choice!                      "<<endl;
                printTabs(5); cout<<"                                                           \033[0m"<<endl;
                cout<<endl;
                printTabs(5); cout<<"  Exiting the program..."<<endl;
                exit(1);
        }
    } 
    else 
    {
        cout<<"\033[47m";
        cout<<"\033[30m";
        printTabs(5); cout<<"                                                           "<<endl;
        printTabs(5); cout<<"  [1] View Recipe Details                                  "<<endl;
        printTabs(5); cout<<"  [2] Choose another Difficulty Level                      "<<endl;
        printTabs(5); cout<<"  [3] Back to Homepage                                     "<<endl;
        printTabs(5); cout<<"  [4] Exit the Program                                     "<<endl;
        printTabs(5); cout<<"                                                           \033[0m"<<endl;
        cout<<endl;

        printTabs(5); cout<<"  Enter Option: ";
        int option;
        cin>>option;

        switch (option) 
        {
            case 1: 
            {
                int recipeNumber;

                printTabs(5); cout<<"  Enter Recipe Number: ";
                cin>>recipeNumber;

                // Validate the recipe number against the recipes in the category
                if (recipeNumber >= 1 && recipeNumber <= levelCount) 
                {
                    int index = levelIndexes[recipeNumber - 1]; // Get index of the selected recipe
                    viewRecipeDetails(index); // View recipe details

                    // After viewing recipe details, show menu again
                    cout<<endl;
                    cout<<"\033[47m";
                    cout<<"\033[30m";
                    printTabs(5); cout<<"                                                           "<<endl;
                    printTabs(5); cout<<"  [1] Choose another Difficulty Level                      "<<endl;
                    printTabs(5); cout<<"  [2] Back to Homepage                                     "<<endl;
                    printTabs(5); cout<<"  [3] Exit the Program                                     "<<endl;
                    printTabs(5); cout<<"                                                           \033[0m"<<endl;
                    cout<<endl;

                    printTabs(5); cout<<"  Enter Option: ";
                    int option;
                    cin>>option;

                    switch (option) 
                    {
                        case 1:
                            chooseDifficulty();
                            break;
                        case 2:
                            return; // Return to the main menu or homepage
                        case 3:
                            printTabs(5); cout<<"  Exiting the program..."<<endl;
                            exit(0); // Exit the program
                        default:
                            cout<<endl;
                            cout<<"\033[97m";
                            cout<<"\033[41m";
                            printTabs(5); cout<<"                                                           "<<endl;
                            printTabs(5); cout<<"                      Invalid Choice!                      "<<endl;
                            printTabs(5); cout<<"                                                           \033[0m"<<endl;
                            cout<<endl;
                            printTabs(5); cout<<"  Exiting the program..."<<endl;
                            exit(1);
                    }
                } 
                else 
                {
                    cout<<endl;
                    cout<<"\033[97m";
                    cout<<"\033[41m";
                    printTabs(5); cout<<"                                                           "<<endl;
                    printTabs(5); cout<<"                    Invalid Recipe Number!                 "<<endl;
                    printTabs(5); cout<<"                                                           \033[0m"<<endl;
                    cout<<endl;

                    printTabs(6); cout<< "        Press Enter to continue...";
                    cin.ignore(); // Clear input buffer
                    cin.get(); // Wait for user to press Enter

                    chooseDifficulty();
                }
                break;
            }
            case 2:
                chooseDifficulty();
                break;
            case 3:
                return; // Return to the main menu or homepage
            case 4:
                printTabs(5); cout<<"  Exiting the program..."<<endl;
                exit(0); // Exit the program
            default:
                cout<<endl;
                cout<<"\033[97m";
                cout<<"\033[41m";
                printTabs(5); cout<<"                                                           "<<endl;
                printTabs(5); cout<<"                      Invalid Choice!                      "<<endl;
                printTabs(5); cout<<"                                                           \033[0m"<<endl;
                cout<<endl;
                printTabs(5); cout<<"  Exiting the program..." << endl;
                exit(1);
        }
    }
}
