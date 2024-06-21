#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <limits>
#include <vector>
#include <cctype>

using namespace std;

// ENUMERATION FOR DIFFICULTY LEVELS
enum DifficultyLevel 
{
    Beginner,        
    Intermediate,    
    Advanced         
};

// ENUMERATION FOR RECIPE CATEGORIES
enum Category 
{
    Appetizer,    
    MainCourse,  
    Dessert,           
    Soup,         
    Salad,        
    Snack,       
    Breakfast,   
    SideDish,     
    Other         
};

enum Method
{
    Sauteeing,
    Boiling,
    Blanching,
    Broiling,
    Stewing,
    Grilling,
    Baking,
    Barbeque,
    OvenRoasting,
    Braising,
    PressureCooking,
    SkilletCooking,
    DeepFrying,
    Steaming,
    StirFrying,
    Others
};

// STRUCTURE TO DEFINE INGREDIENT DETAILS
struct Ingredient 
{
    string name;    
    string unit;  
};

// STRUCTURE TO DEFINE RECIPE DETAILS
struct Recipe 
{
    string name;                 
    vector<Ingredient> ingredients; 
    vector<string> instruction;   
    string cooking_time;           
    bool isFavorite;              
    DifficultyLevel difficulty_level; 
    Category category;       
    Method method;
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

string difficultyLevelToString(DifficultyLevel level) // FUNCTION TO CONVERT DIFFICULTY LEVEL ENUM TO STRING
{
    // SWITCH STATEMENT TO HANDLE DIFFERENT LEVELS OF DIFFICULTY
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

string categoryToString(Category category) // FUNCTION TO CONVERT CATEGORY ENUM TO STRING
{
    // SWITCH STATEMENT TO HANDLE DIFFERENT CATEGORIES
    switch (category) 
    {
        case Appetizer:
            return "Appetizer";  
        case MainCourse:
            return "Main Course"; 
        case Dessert:
            return "Dessert";       
        case Soup:
            return "Soup";      
        case Salad:
            return "Salad";      
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

string methodToString(Method method) // FUNCTION TO CONVERT COOKING METHODS ENUM TO STRING
{
    // SWITCH STATEMENT TO HANDLE COOKING METHODS
    switch (method) 
    {
        case Sauteeing:
            return "Sauteeing";   
        case Boiling:
            return "Boiling";    
        case Blanching:
            return "Blanching"; 
        case Broiling:
            return "Broiling"; 
        case Grilling:
            return "Grilling"; 
        case Baking:
            return "Baking"; 
        case Barbeque:
            return "Barbeque"; 
        case OvenRoasting:
            return "Oven Roasting"; 
        case Braising:
            return "Braising"; 
        case PressureCooking:
            return "Pressure Cooking"; 
        case SkilletCooking:
            return "Skillet Cooking"; 
        case DeepFrying:
            return "Deep Frying"; 
        case Steaming:
            return "Steaming"; 
        case StirFrying:
            return "Stir Frying"; 
        case Others:
            return "Other"; 
        default:
            return "Unknown";         
    }
}

Recipe recipes[100]; // ARRAY OF RECIPE STRUCT TO STORE MANY RECIPES 
int opt = 0, count = 0;

int main() 
{    
    header();          // FUNCTION CALL TO DISPLAY HEADER
    loadRecipe();      // FUNCTION CALL TO LOAD RECIPES
    clearScreen();     // FUNCTION CALL TO CLEAR SCREEN

    int option;        // VARIABLE TO STORE USER OPTION

    while (true)       // MAIN LOOP FOR MENU INTERACTION
    {
        clearScreen(); // FUNCTION CALL TO CLEAR SCREEN

        printTabs(5); cout<<",------.              ,--.              ,------.         ,--. \n";
        printTabs(5); cout<<"|  .--. ' ,---.  ,---.`--' ,---.  ,---. |  .--. ' ,--,--.|  | \n";
        printTabs(5); cout<<"|  '--'.'| .-. :| .--',--.| .-. || .-. :|  '--' |' ,-.  ||  | \n";
        printTabs(5); cout<<"|  |\\  \\ \\   --.\\ `--.|  || '-' '\\   --.|  | --' \\ '-'  ||  | \n";
        printTabs(5); cout<<"`--' '--' `----' `---'`--'|  |-'  `----'`--'      `--`--'`--' \n";
        printTabs(5); cout<<"                          `--'                                 \n";
        cout<<endl;

        // RECIPE HOMEPAGE 
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
                while (true) // INNER LOOP FOR RECIPES MENU
                {
                    clearScreen(); // FUNCTION CALL TO CLEAR SCREEN

                    printTabs(5); cout<<",------.              ,--.              ,------.         ,--. \n";
                    printTabs(5); cout<<"|  .--. ' ,---.  ,---.`--' ,---.  ,---. |  .--. ' ,--,--.|  | \n";
                    printTabs(5); cout<<"|  '--'.'| .-. :| .--',--.| .-. || .-. :|  '--' |' ,-.  ||  | \n";
                    printTabs(5); cout<<"|  |\\  \\ \\   --.\\ `--.|  || '-' '\\   --.|  | --' \\ '-'  ||  | \n";
                    printTabs(5); cout<<"`--' '--' `----' `---'`--'|  |-'  `----'`--'      `--`--'`--' \n";
                    printTabs(5); cout<<"                          `--'                                 \n";
                    cout<<endl;

                    // RECIPE MENU
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
                            break; // RETURN TO OUTER MENU
                        case 7: 
                            printTabs(5); cout<<"  Exiting the program..."<<endl;
                            exit(0); 
                        default: 
                            // INVALID OPTION HANDLING
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
                        break; // EXIT THE INNER WHILE LOOP
                    }
                }
                break;
            }
            case 2: 
                displayFavoriteRecipes(); 
                break;
            case 3: 
                chooseCategory(); // FUNCTION CALL TO VIEW RECIPES BY CATEGORY
                break;
            case 4: 
                chooseDifficulty(); // FUNCTION CALL TO VIEW RECIPES BY DIFFICULTY
                break;
            case 5: 
                printTabs(5); cout<<"  Exiting the program..."<<endl;
                exit(0); 
            default: 
                // INVALID OPTION HANDLING
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
    return 0;
}

void header()
{
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"\033[32m";
	printTabs(1); cout<<"                                                                    @@@@+     :=*%\n";
    printTabs(1); cout<<"                  @@@@@@@@@@@@@     @@@@@@@@@@.                    @@@@#  +@@@@@@@@@@@   @@@@@@@@@@+\n";
    printTabs(1); cout<<"                  @@@@@@@@@@@@@@    @@@@@@@@@@          @@@@@@@@          +@@@*   .@@@@  @@@@@@@@@@\n";
    printTabs(1); cout<<"                  @@@@+:::.@@@@@@   @@@@@%            @@@@@@@@@@   @@@@   *@@@-    @@@@  @@@@@@\n";
    printTabs(1); cout<<"                  @@@@      @@@@@   @@@@@#          +@@@@@@@@      @@@@*  *@@@=    @@@@  @@@@@@\n";
    printTabs(1); cout<<"                  @@@@     -@@@@-   @@@@@@@@@       @@@@@@         @@@@#  +@@@@.+@@@@@   @@@@@@@@@\n";
    printTabs(1); cout<<"                  @@@@  .@@@@@@     @@@@@@@@@#      @@@@@          @@@@%  +@@@@@@@@      @@@@@@@@@@\n";
    printTabs(1); cout<<"                  @@@@@@@@@@@@%     %@@@@@          @@@@           @@@@#  =@@@@+         @@@@@@\n";
    printTabs(1); cout<<"                  @@@@@@@@@@@@@     *@@@@@         =@@@@@          @@@@*  -@@@@          @@@@@@\n";
    printTabs(1); cout<<"                  @@@@@   @@@@@@    -@@@@@          @@@@@@@@@%-    @@@@*  :@@@%          @@@@@@\n";
    printTabs(1); cout<<"                  @@@@@     @@@@@     @@@@@@@@@@@%    +@@@@@@@@@:   @@@@*  :@@@*          @@@@@@@@@@*\n";
    printTabs(1); cout<<"                  @@@@@      @@@@@    @@@@@@@@@@%        @@@@@@@    @@@@*  .@@@+          *@@@@@@@@@\n";
    printTabs(1); cout<<"                             @@\n";
    cout<<"\033[0m";
	cout<<endl;
	cout<<endl;
    printTabs(1); cout<<"                                      @@@@@@@@@\n";
    printTabs(1); cout<<"                                      @@@@@@@@@@@@      @@@@@@         @@@@@:\n";
    printTabs(1); cout<<"                                      @@@@     @@@-    +@@@@@@.        @@@@@\n";
    printTabs(1); cout<<"                                      @@@@     @@@@    @@@@@@@@        @@@@@\n";
    printTabs(1); cout<<"                                      @@@@    @@@@     @@@@ @@@@       @@@@@\n";
    printTabs(1); cout<<"                                      @@@@@@@@@@      @@@@@  @@@@      %@@@@\n";
    printTabs(1); cout<<"                                      @@@@@@@         @@@@@  @@@@@     *@@@@\n";
    printTabs(1); cout<<"                                      @@@@+          :@@@@@@@@@@@@-    +@@@@\n";
    printTabs(1); cout<<"                                      @@@@:          @@@@@@@@%*@@@@    +@@@@\n";
    printTabs(1); cout<<"                                      @@@@.          @@@@       @@@@   *@@@@@@@@@@@\n";
    printTabs(1); cout<<"                                      @@@@           @@@@       -@@@.  %@@@@@@@@@@@\n";
    printTabs(1); cout<<"                                       *@@           -+%               =@@@@@@@@@@@\n";

    cout<<endl;
    printTabs(7); cout<<"Press Enter to continue...";
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
        write<<static_cast<int>(recipes[i].method)<<"|";
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

        int method;
        read >> method; // Read the category as integer
        read.ignore(); // Ignore the '|' character

        recipes[i].method = static_cast<Method>(method);

        int isFavoriteInt;
        read >> isFavoriteInt;
        read.ignore(); // Ignore the newline character

        recipes[i].isFavorite = (isFavoriteInt == 1);
    }
    // CLOSE THE FILE STREAM
    read.close();
}

int ingredientQtyChecker() // FUNCTION VALIDATES AMD RETRIEVES NUMBER OF INGREDIENTS ENSURING IT IS POSITIVE
{
    int ingredients_qty;
    bool validInput = false;

    // LOOP UNTIL VALID INPUT IS RECEIVED
    while (!validInput) 
    {
        printTabs(5); cout<<"  No. of Ingredients: ";
        cin>>ingredients_qty;

        // CHECK FOR INVALID INPUT (NON-INTEGER OR NEGATIVE VALUE)
        if (cin.fail() || ingredients_qty <= 0) 
        {
            cin.clear(); // CLEAR ERROR FLAG
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // DISCARD INVALID INPUT

            // DISPLAY ERROR MESSAGE
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
            validInput = true; // SET FLAG TO EXIT LOOP
        }
    }

    cin.ignore(); // CLEAR THE NEWLINE CHARACTER LEFT IN THE BUFFER
    return ingredients_qty; // RETURN VALID INPUT
}

int instructionQtyChecker() // FUNCTION VALIDATES AMD RETRIEVES NUMBER OF INSTRUCTIONS ENSURING IT IS POSITIVE
{
    int instruction_qty;
    bool validInput = false;

    // LOOP UNTIL VALID INPUT IS RECEIVED
    while (!validInput) 
    {
        printTabs(5); cout<<"  No. of Instruction Steps: ";
        cin >> instruction_qty;

        // CHECK FOR INVALID INPUT (NON-INTEGER OR NEGATIVE VALUE)
        if (cin.fail() || instruction_qty <= 0) 
        {
            cin.clear(); // CLEAR ERROR FLAG
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // DISCARD INVALID INPUT

            // DISPLAY ERROR MESSAGE
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
            validInput = true; // SET FLAG TO EXIT LOOP
        }
    }
    cin.ignore(); // CLEAR THE NEWLINE CHARACTER LEFT IN THE BUFFER
    return instruction_qty; // RETURN VALID INPUT
}

void addRecipe() // FUNCTION TO ALLOW USERS TO ADD RECIPE
{
    clearScreen(); // CLEAR THE SCREEN FOR A CLEAN INTERFACE
    cout<<"\033[46m"; 
    cout<<"\033[97m"; 
    printTabs(5); cout<<"                                                           "<<endl;
    printTabs(5); cout<<"                        Add Recipe                         "<<endl; 
    printTabs(5); cout<<"                                                           \033[0m"<<endl; 
    cout<<endl;

    addRecipeItems(); // CALL FUNCTION TO ADD RECIPE ITEMS

    // CONFIRMATION MESSAGE
    cout<<endl; 
    cout<<"\033[97m";
    cout<<"\033[42m"; 
    printTabs(5); cout<<"                                                           "<<endl;
    printTabs(5); cout<<"                Recipe Added Successfully!                 "<<endl; 
    printTabs(5); cout<<"                                                           \033[0m"<<endl;
    cout<<endl;

    printTabs(6); cout << "        Press Enter to continue...";
    cin.ignore(); // WAIT FOR USER TO PRESS ENTER TO CONTINUE
    cin.get();

    viewRecipe(count); // DISPLAY THE RECIPE DETAILS (COUNT INDICATES INDEX OF THE NEWLY ADDED RECIPE)
    addToFavorites(count - 1); // ADD THE NEWLY ADDED RECIPE TO FAVORITES

    // OPTIONS FOR USER
    cout<<endl;
    cout<<"\033[47m";
    cout<<"\033[30m";
    printTabs(5); cout<<"                                                           "<<endl;
    printTabs(5); cout<<"  [1] Add another Recipe                                   "<<endl; 
    printTabs(5); cout<<"  [2] Back to Recipe Menu                                  "<<endl;
    printTabs(5); cout<<"  [3] Exit the Program                                     "<<endl;
    printTabs(5); cout<<"                                                           \033[0m"<<endl;
    cout<<endl;

    printTabs(5); cout<<"  Enter Option: ";
    int option;
    cin>>option;

    switch (option) 
    {
        case 1:
            addRecipe(); // RECURSIVELY CALL THIS FUNCTION TO ADD ANOTHER RECIPE
            break;
        case 2:
            return; // RETURN TO THE CALLING FUNCTION OR LOOP
        case 3:
            printTabs(5); cout<<"  Exiting the program..."<<endl;
            exit(0); // EXIT THE PROGRAM 
        default:
            cout<<endl;
            cout<<"\033[97m";
            cout<<"\033[41m";
            printTabs(5); cout<<"                                                           "<<endl;
            printTabs(5); cout<<"                      Invalid Option!                      "<<endl; // DISPLAY ERROR MESSAGE FOR INVALID OPTION
            printTabs(5); cout<<"                                                           \033[0m"<<endl;
            cout<<endl;
            printTabs(5); cout<<"  Exiting the program..."<<endl;
            exit(1); // EXIT THE PROGRAM 
    }
}

void addRecipeItems() // FUNCTION GUIDES THE USER THROUGH ENTERING DETAILS FOR NEW RECIPE
{
    cin.ignore(); // CLEAR THE INPUT BUFFER

    printTabs(5); cout<<"  Recipe Name: ";
    getline(cin, recipes[count].name); 

    int ingredients_qty = ingredientQtyChecker(); // CALL FUNCTION TO GET NUMBER OF INGREDIENTS

    recipes[count].ingredients.resize(ingredients_qty); // RESIZE TO ACCOMMODATE ingredients_qty

    // PROMPT FOR EACH INGREDIENT
    for (int i = 0; i < ingredients_qty; ++i) 
    {
        printTabs(5); cout<<"  Ingredient "<< i + 1 <<":"<<endl;
        printTabs(5); cout<<"     Name: ";
        getline(cin, recipes[count].ingredients[i].name); 
        printTabs(5); cout<<"     Unit: ";
        getline(cin, recipes[count].ingredients[i].unit); 
    }

    int instruction_qty = instructionQtyChecker(); // CALL FUNCTION TO GET NUMBER OF INSTRUCTION STEPS

    recipes[count].instruction.resize(instruction_qty); // RESIZE TO ACCOMMODATE instruction_qty

    // PROMPT FOR EACH INSTRUCTION STEP
    for (int i = 0; i < instruction_qty; ++i) 
    {
        printTabs(5); cout<< "     Step "<< i + 1 <<": ";
        getline(cin, recipes[count].instruction[i]); 
    }

    printTabs(5); cout<<"  Cooking Time: ";
    getline(cin, recipes[count].cooking_time); 

    cout<<endl;
    printTabs(5); cout<<"  Select Cooking Difficulty Level:"<<endl;
    printTabs(5); cout<<"     [1] Beginner Level   [2] Intermediate Level   [3] Advanced Level"<<endl;
    printTabs(5); cout<<"  Enter Option: ";

    int difficultyOption;
    cin>>difficultyOption;
    cin.ignore(); 

    // ASSIGN COOKING DIFFICULTY BASED ON USER INPUT
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

            recipes[count].difficulty_level = Beginner; // SET DEFAULT TO BEGINNER LEVEL
            break;
    }

    // PROMPT FOR RECIPE CATEGORY
    cout<<endl;
    printTabs(5); cout<<"  Select Category:"<<endl;
    printTabs(5); cout<<"     [1] Appetizer     [3] Dessert   [5] Snack       [7] SideDish"<<endl;
    printTabs(5); cout<<"     [2] Main Course   [4] Soup      [6] Breakfast   [8] Other"<<endl;
    printTabs(5); cout<<"  Enter Option: ";

    int categoryOption;
    cin>>categoryOption;
    cin.ignore(); // CONSUME NEWLINE LEFT BY cin

    // ASSIGN RECIPE CATEGORY BASED ON USER INPUT
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
            recipes[count].category = Soup;
            break;
        case 5:
            recipes[count].category = Snack;
            break;
        case 6:
            recipes[count].category = Breakfast;
            break;
        case 7:
            recipes[count].category = SideDish;
            break;
        case 8:
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

            recipes[count].category = Other; // SET DEFAULT TO OTHER CATEGORY
            break;
    }

    // PROMPT FOR RECIPE COOKING METHOD
    cout<<endl;
    printTabs(5); cout<<"  Select Cooking Method:"<<endl;
    printTabs(5); cout<<"     [1] Sauteeing   [5] Stewing    [9] Oven Roasting       [13] Deep Frying"<<endl;
    printTabs(5); cout<<"     [2] Boiling     [6] Grilling   [10] Braising           [14] Steaming"<<endl;
    printTabs(5); cout<<"     [3] Blanching   [7] Baking     [11] Pressure Cooking   [15] Stir Frying"<<endl;
    printTabs(5); cout<<"     [4] Broiling    [8] Barbeque   [12] Skillet Cooking    [16] Other"<<endl;
    printTabs(5); cout<<"  Enter Option: ";

    int methodOption;
    cin>>methodOption;
    cin.ignore(); // CONSUME NEWLINE LEFT BY cin

    // ASSIGN RECIPE CATEGORY BASED ON USER INPUT
    switch (methodOption) 
    {
        case 1:
            recipes[count].method = Sauteeing;
            break;
        case 2:
            recipes[count].method = Boiling;
            break;
        case 3:
            recipes[count].method = Blanching;
            break;
        case 4:
            recipes[count].method = Broiling;
            break;
        case 5:
            recipes[count].method = Stewing;
            break;
        case 6:
            recipes[count].method = Grilling;
            break;
        case 7:
            recipes[count].method = Baking;
            break;
        case 8:
            recipes[count].method = Barbeque;
            break;
        case 9:
            recipes[count].method = OvenRoasting;
            break;
        case 10:
            recipes[count].method = Braising;
            break;
        case 11:
            recipes[count].method = PressureCooking;
            break;
        case 12:
            recipes[count].method = SkilletCooking;
            break;
        case 13:
            recipes[count].method = DeepFrying;
            break;
        case 14:
            recipes[count].method = Steaming;
            break;
        case 15:
            recipes[count].method = StirFrying;
            break;
        case 16:
            recipes[count].method = Others;
            break;
        default:
            cout<<endl;
            cout<<"\033[97m";
            cout<<"\033[41m";
            printTabs(5); cout<<"                                                           "<<endl;
            printTabs(5); cout<<"                      Invalid Option!                      "<<endl;
            printTabs(5); cout<<"        Setting cooking method to Other by default.        "<<endl;
            printTabs(5); cout<<"                                                           \033[0m"<<endl;
            cout<<endl;

            recipes[count].method = Others; // SET DEFAULT TO OTHER CATEGORY
            break;
    }

    count++; // INCREMENT RECIPE COUNT
    saveRecipe(); // SAVE THE RECIPE TO FILE
    loadRecipe(); // RELOAD RECIPES TO UPDATE count VARIABLE
}

void updateRecipe() // FUNCTION TO ALLOW USER TO UPDATE RECIPE
{
    // OPEN THE FILE TO READ
    ifstream file("recipes.txt");

    // CHECK IF THE FILE IS OPEN
    if (!file.is_open())
    {
        // DISPLAY ERROR MESSAGE IF FILE CANNOT BE OPENED
        cout<<endl;
        cout<<"\033[97m";
        cout<<"\033[41m";
        printTabs(5); cout<<"                                                           "<<endl;
        printTabs(5); cout<<"                  Unable to open file!                     "<<endl;
        printTabs(5); cout<<"               Please check the file path!                 "<<endl;
        printTabs(5); cout<<"                                                           \033[0m"<<endl;
        cout<<endl;

        // WAIT FOR USER INPUT
        printTabs(6); cout<<"        Press Enter to continue..."; 
        cin.ignore();
        cin.get();

        // CLOSE THE FILE (ALTHOUGH IT'S NOT OPEN)
        file.close();
        return;
    }

    // CLEAR THE SCREEN AND LOAD RECIPES FROM FILE
    clearScreen();
    loadRecipe();

    // DISPLAY UPDATE INTERFACE HEADER
    cout<<"\033[46m";
    cout<<"\033[97m";
    printTabs(5); cout<<"                                                           "<<endl;
    printTabs(5); cout<<"                    Update Recipe                          "<<endl;
    printTabs(5); cout<<"                                                           \033[0m"<<endl;
    cout<<endl;

    // DISPLAY EXISTING RECIPES
    printTabs(5); cout<<"  Existing Recipes:"<<endl;

    for (int i = 0; i < count; i++)
    {
        printTabs(5); cout<<"  "<< i + 1 <<". "<<recipes[i].name<<endl;
    }

    int num = 0;

    cout<<endl;
    printTabs(5); cout<<"  Enter Recipe Number to Update: ";
    cin>>num;

    // VALIDATE USER INPUT FOR RECIPE NUMBER
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

    // CALL FUNCTION TO UPDATE RECIPE ITEMS
    updateRecipeItems(index, num);

    cout<<endl;
    cout<<"\033[47m";
    cout<<"\033[30m";
    printTabs(5); cout<<"                                                           "<<endl;
    printTabs(5); cout<<"  [1] Update another Recipe                                "<<endl;
    printTabs(5); cout<<"  [2] Back to Recipe Menu                                  "<<endl;
    printTabs(5); cout<<"  [3] Exit the Program                                     "<<endl;
    printTabs(5); cout<<"                                                           \033[0m"<<endl;
    cout<<endl;

    int option;

    printTabs(5); cout<<"  Enter Option: ";
    cin>>option;

    switch (option)
    {
        case 1:
            // UPDATE ANOTHER RECIPE
            updateRecipe();
            break;
        case 2:
            // RETURN TO RECIPE MENU
            return;
        case 3:
            // EXIT THE PROGRAM
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
            // EXIT THE PROGRAM WITH ERROR
            printTabs(5); cout<<"  Exiting the program..."<<endl;
            exit(1);
    }
}

void updateRecipeItems(int index, int num) // FUNCTION GUIDES THE USER THROUGH ENTERING DETAILS FOR UPDATED RECIPE
{
    clearScreen();

    cout<<"\033[46m";
    cout<<"\033[97m";
    printTabs(5); cout<<"                                                           "<<endl;
    printTabs(5); cout<<"                    Update Recipe                          "<<endl;
    printTabs(5); cout<<"                                                           \033[0m"<<endl;
    cout<<endl;

    // DISPLAY EXISTING RECIPE DETAILS
    printTabs(5); cout<<"  Existing Recipe Details:"<<endl;

    // VIEW CURRENT RECIPE
    viewRecipe(num);

    cout<<endl;

    string choice;

    // CONFIRMATION PROMPT FOR UPDATING RECIPE
    printTabs(5); cout<<"  Confirm to Update Recipe No. "<<num<<"? [Y/N]: ";
    getline(cin, choice);

    if (choice == "Y" || choice == "y")
    {
        clearScreen();

        bool validInput = true;

        cout<<"\033[97m";
        cout<<"\033[42m";
        printTabs(5); cout<<"                                                           "<<endl;
        printTabs(5); cout<<"             Starting Update of Recipe No." << num << "!               "<<endl;
        printTabs(5); cout<<"                                                           \033[0m"<<endl;
        cout<<endl;

        // UPDATE RECIPE NAME
        printTabs(5); cout<<"  Recipe Name: ";
        getline(cin, recipes[index].name);

        // PROMPT FOR NUMBER OF INGREDIENTS AND RESIZE VECTOR
        int ingredients_qty = ingredientQtyChecker();
        recipes[index].ingredients.resize(ingredients_qty);

        // PROMPT FOR EACH INGREDIENT
        for (int i = 0; i < ingredients_qty; ++i) 
        {
            printTabs(5); cout<<"  Ingredient "<< i + 1 <<":"<<endl;
            printTabs(5); cout<<"     Name: ";
            getline(cin, recipes[index].ingredients[i].name);
            printTabs(5); cout<<"     Unit: ";
            getline(cin, recipes[index].ingredients[i].unit);
        }

        // PROMPT FOR NUMBER OF INSTRUCTION STEPS AND RESIZE VECTOR
        int instruction_qty = instructionQtyChecker();
        recipes[index].instruction.resize(instruction_qty);

        // PROMPT FOR EACH INSTRUCTION STEP
        for (int i = 0; i < instruction_qty; ++i) 
        {
            printTabs(5); cout<< "     Step "<< i + 1 <<": ";
            getline(cin, recipes[index].instruction[i]);
        }

        // UPDATE COOKING TIME
        printTabs(5); cout<<"  Cooking Time: ";
        getline(cin, recipes[index].cooking_time);

        // PROMPT FOR DIFFICULTY LEVEL
        cout<<endl;
        printTabs(5); cout<<"  Select Cooking Difficulty Level:"<<endl;
        printTabs(5); cout<<"     [1] Beginner Level   [2] Intermediate Level   [3] Advanced Level"<<endl;
        printTabs(5); cout<<"  Enter Option: ";

        int difficultyOption;

        cin>>difficultyOption;
        cin.ignore(); // CONSUME NEWLINE LEFT BY cin

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
                // DISPLAY ERROR FOR INVALID OPTION AND SET DEFAULT TO BEGINNER
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

        // PROMPT FOR CATEGORY
        cout<<endl;
        printTabs(5); cout<<"  Select Category:"<<endl;
        printTabs(5); cout<<"     [1] Appetizer     [3] Dessert   [5] Snack       [7] SideDish"<<endl;
        printTabs(5); cout<<"     [2] Main Course   [4] Soup      [6] Breakfast   [8] Other"<<endl;
        printTabs(5); cout<<"  Enter Option: ";
            
        int categoryOption;

        cin>>categoryOption;
        cin.ignore(); // CONSUME NEWLINE LEFT BY cin

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
                recipes[index].category = Soup;
                break;
            case 5:
                recipes[index].category = Snack;
                break;
            case 6:
                recipes[index].category = Breakfast;
                break;
            case 7:
                recipes[index].category = SideDish;
                break;
            case 8:
                recipes[index].category = Other;
                break;
            default:
                // DISPLAY ERROR FOR INVALID OPTION AND SET DEFAULT TO OTHER
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

        // PROMPT FOR RECIPE COOKING METHOD
        cout<<endl;
        printTabs(5); cout<<"  Select Cooking Method:"<<endl;
        printTabs(5); cout<<"     [1] Sauteeing   [5] Stewing    [9] Oven Roasting       [13] Deep Frying"<<endl;
        printTabs(5); cout<<"     [2] Boiling     [6] Grilling   [10] Braising           [14] Steaming"<<endl;
        printTabs(5); cout<<"     [3] Blanching   [7] Baking     [11] Pressure Cooking   [15] Stir Frying"<<endl;
        printTabs(5); cout<<"     [4] Broiling    [8] Barbeque   [12] Skillet Cooking    [16] Other"<<endl;
        printTabs(5); cout<<"  Enter Option: ";

        int methodOption;
        cin>>methodOption;
        cin.ignore(); // CONSUME NEWLINE LEFT BY cin

        // ASSIGN RECIPE CATEGORY BASED ON USER INPUT
        switch (methodOption) 
        {
            case 1:
                recipes[index].method = Sauteeing;
                break;
            case 2:
                recipes[index].method = Boiling;
                break;
            case 3:
                recipes[index].method = Blanching;
                break;
            case 4:
                recipes[index].method = Broiling;
                break;
            case 5:
                recipes[index].method = Stewing;
                break;
            case 6:
                recipes[index].method = Grilling;
                break;
            case 7:
                recipes[index].method = Baking;
                break;
            case 8:
                recipes[index].method = Barbeque;
                break;
            case 9:
                recipes[index].method = OvenRoasting;
                break;
            case 10:
                recipes[index].method = Braising;
                break;
            case 11:
                recipes[index].method = PressureCooking;
                break;
            case 12:
                recipes[index].method = SkilletCooking;
                break;
            case 13:
                recipes[index].method = DeepFrying;
                break;
            case 14:
                recipes[index].method = Steaming;
                break;
            case 15:
                recipes[index].method = StirFrying;
                break;
            case 16:
                recipes[index].method = Others;
                break;
            default:
                cout<<endl;
                cout<<"\033[97m";
                cout<<"\033[41m";
                printTabs(5); cout<<"                                                           "<<endl;
                printTabs(5); cout<<"                      Invalid Option!                      "<<endl;
                printTabs(5); cout<<"        Setting cooking method to Other by default.        "<<endl;
                printTabs(5); cout<<"                                                           \033[0m"<<endl;
                cout<<endl;

                recipes[index].method = Others; // SET DEFAULT TO OTHER CATEGORY
                break;
        }

        // DISPLAY SUCCESS MESSAGE FOR RECIPE UPDATE
        cout<<endl;
        cout<<"\033[97m";
        cout<<"\033[42m";
        printTabs(5); cout<<"                                                           "<<endl;
        printTabs(5); cout<<"               Recipe Updated Successfully!                "<<endl;
        printTabs(5); cout<<"                                                           \033[0m"<<endl;
        cout<<endl;
        
        // SAVE AND RELOAD RECIPES
        saveRecipe();
        loadRecipe();

        printTabs(6); cout<<"        Press Enter to continue...";
        cin.ignore(); // WAIT FOR USER TO PRESS ENTER

        // CLEAR SCREEN AND DISPLAY UPDATED RECIPE DETAILS
        clearScreen();

        cout<<"\033[46m";
        cout<<"\033[97m";
        printTabs(5); cout<<"                                                           "<<endl;
        printTabs(5); cout<<"                    Update Recipe                          "<<endl;
        printTabs(5); cout<<"                                                           \033[0m"<<endl;
        cout<<endl;

        printTabs(5); cout<<"  Updated Recipe Details:"<<endl;

        viewRecipe(num); // VIEW UPDATED RECIPE

        // CHECK IF RECIPE IS A FAVORITE AND ADD/REMOVE ACCORDINGLY
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
        // DISPLAY MESSAGE IF UPDATE IS CANCELLED
        cout<<endl;
        cout<<"\033[97m";
        cout<<"\033[41m";
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

void searchRecipe() // FUNCTION TO ALLOW USER TO SEARCH A RECIPE
{
    clearScreen(); // CLEAR THE SCREEN

    ifstream read("recipes.txt"); // OPEN THE RECIPES FILE FOR READING

    if (!read.is_open()) 
    {
        // DISPLAY ERROR MESSAGE IF FILE OPENING FAILED
        cout<<"\033[97m\033[41m";
        printTabs(5); cout<<"                                                           "<<endl;
        printTabs(5); cout<<"                  Unable to open file!                     "<<endl;
        printTabs(5); cout<<"                                                           \033[0m"<<endl;

        // PROMPT USER TO CONTINUE
        cout<<endl;
        printTabs(6); cout<< "        Press Enter to continue...";
        cin.ignore();
        cin.get();

        return; // EXIT FUNCTION
    }

    loadRecipe(); // LOAD RECIPES INTO MEMORY (ASSUMED FUNCTION)

    // DISPLAY SEARCH HEADER
    cout<<"\033[46m";
    cout<<"\033[97m";
    printTabs(5); cout<<"                                                           "<<endl;
    printTabs(5); cout<<"                    Search Recipe                          "<<endl;
    printTabs(5); cout<<"                                                           \033[0m"<<endl;
    cout<<endl;

    cin.ignore(); // CLEAR INPUT BUFFER
    printTabs(5); cout<<"  Enter Recipe Name to Search: ";
    string searchName;
    getline(cin, searchName);

    bool found = false; // FLAG TO TRACK IF RECIPE IS FOUND
    int totalRecipes;

    read>>totalRecipes; // READ TOTAL NUMBER OF RECIPES FROM FILE
    read.ignore();  // IGNORE NEWLINE CHARACTER AFTER THE INTEGER

    for (int i = 0; i < totalRecipes; i++) 
    {
        // READ RECIPE DETAILS FROM FILE
        getline(read, recipes[i].name, '|');

        int ingredients_qty;
        read>>ingredients_qty;
        read.ignore();
        recipes[i].ingredients.resize(ingredients_qty);
        
        // READ INGREDIENTS DETAILS
        for (int j = 0; j < ingredients_qty; ++j) 
        {
            getline(read, recipes[i].ingredients[j].name, '|');
            getline(read, recipes[i].ingredients[j].unit, '|');
        }

        int instruction_qty;
        read>>instruction_qty;
        read.ignore();
        recipes[i].instruction.resize(instruction_qty);

        // READ INSTRUCTION STEPS
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

        int method;
        read>>method;
        read.ignore();

        int isFavoriteInt;
        read>>isFavoriteInt;
        read.ignore();

        // ASSIGN DIFFICULTY, CATEGORY, AND FAVORITE STATUS
        recipes[i].difficulty_level = static_cast<DifficultyLevel>(difficultyLevel);
        recipes[i].category = static_cast<Category>(category);
        recipes[i].method = static_cast<Method>(method);
        recipes[i].isFavorite = (isFavoriteInt == 1);

        // CHECK IF CURRENT RECIPE MATCHES SEARCH NAME
        if (recipes[i].name == searchName) 
        {
            found = true;

            // DISPLAY SUCCESS MESSAGE IF RECIPE IS FOUND
            cout<<endl;
            cout<<"\033[97m";
            cout<<"\033[42m";
            printTabs(5); cout<<"                                                           "<<endl;
            printTabs(5); cout<<"                Recipe Found Successfully!                 "<<endl;
            printTabs(5); cout<<"                                                           \033[0m"<<endl;
            cout<<endl;

            // DISPLAY RECIPE DETAILS
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
            printTabs(5); cout<<"  Cooking Method: "<<methodToString(recipes[i].method)<<endl;
            cout << endl;

            break; // EXIT LOOP SINCE RECIPE IS FOUND
        }
    }

    read.close(); // CLOSE THE FILE AFTER READING

    if (!found) 
    {
        // DISPLAY MESSAGE IF RECIPE IS NOT FOUND
        cout<<endl;
        cout<<"\033[97m";
        cout<<"\033[41m";
        printTabs(5); cout<<"                                                           "<<endl;
        printTabs(5); cout<<"                     Recipe Not Found!                     "<<endl;
        printTabs(5); cout<<"                                                           \033[0m"<<endl;
        cout<<endl;
    }

    // DISPLAY MENU FOR FURTHER ACTIONS
    cout<<"\033[47m\033[30m";
    printTabs(5); cout<<"                                                           "<<endl;
    printTabs(5); cout<<"  [1] Search another Recipe                                "<<endl;
    printTabs(5); cout<<"  [2] Back to Recipe Menu                                  "<<endl;
    printTabs(5); cout<<"  [3] Exit the Program                                     "<<endl;
    printTabs(5); cout<<"                                                           \033[0m"<<endl;
    cout<<endl;
    printTabs(5); cout<<"  Enter Option: ";
    int option;
    cin>>option;

    switch (option) 
    {
        case 1:
            searchRecipe(); // RECURSIVE CALL TO SEARCH ANOTHER RECIPE
            break;
        case 2:
            return; // RETURN TO THE MAIN LOOP
        case 3:
            printTabs(5); cout<<"  Exiting the program..." << endl;
            exit(0); // EXIT THE PROGRAM
        default:
            // HANDLE INVALID OPTION AND EXIT
            cout<<"\033[97m\033[41m";
            printTabs(5); cout<<"                                                           "<<endl;
            printTabs(5); cout<<"                      Invalid Choice!                      "<<endl;
            printTabs(5); cout<<"                                                           \033[0m"<<endl;
            printTabs(5); cout<<"  Exiting the program..."<<endl;
            exit(1);
    }
}

void deleteRecipe() // FUNCTION TO ALLOW USER TO DELETE A RECIPE
{
    ifstream file("recipes.txt"); // OPEN THE RECIPES FILE FOR READING

    if (!file.is_open()) 
    {
        // DISPLAY ERROR MESSAGE IF FILE OPENING FAILED
        cout<<endl;
        cout<<"\033[97m";
        cout<<"\033[41m";
        printTabs(5); cout<<"                                                           "<<endl;
        printTabs(5); cout<<"                  Unable to open file!                     "<<endl;
        printTabs(5); cout<<"                                                           \033[0m"<<endl;
        cout<<endl;

        // PROMPT USER TO CONTINUE
        printTabs(6); cout<<"        Press Enter to continue...";
        cin.ignore();
        cin.get();
        file.close();
        return; // EXIT FUNCTION
    }

    clearScreen(); // CLEAR THE SCREEN

    // DISPLAY HEADER FOR DELETE OPERATION
    cout<<"\033[46m";
    cout<<"\033[97m";
    printTabs(5); cout<<"                                                           "<<endl;
    printTabs(5); cout<<"                    Delete Recipe                          "<<endl;
    printTabs(5); cout<<"                                                           \033[0m"<<endl;
    cout<<endl;

    printTabs(5); cout<<"  Existing Recipes:"<<endl;

    // DISPLAY LIST OF EXISTING RECIPES
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
        // HANDLE INVALID RECIPE ID
        cout<<endl;
        cout<<"\033[97m";
        cout<<"\033[41m";
        printTabs(5); cout<<"                                                           "<<endl;
        printTabs(5); cout<<"                    Invalid Recipe ID!                     "<<endl;
        printTabs(5); cout<<"                                                           \033[0m"<<endl;
        cout<<endl;

        // PROMPT USER TO CONTINUE
        printTabs(6); cout<< "        Press Enter to continue...";
        cin.ignore();
        cin.get();

        file.close();
        return; // EXIT FUNCTION
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
        // SHIFT RECIPES ARRAY TO REMOVE DELETED RECIPE
        for (int i = index; i < count - 1; i++) 
        {
            recipes[i] = recipes[i + 1];
        }
        count--;

        ofstream write("recipes.txt"); // OPEN FILE FOR WRITING

        if (write.is_open()) 
        {
            // WRITE UPDATED NUMBER OF RECIPES
            write<<count<<endl;

            // WRITE EACH RECIPE'S DETAILS TO FILE
            for (int i = 0; i < count; i++) 
            {
                write<<recipes[i].name<<"|"<<recipes[i].ingredients.size()<<"|";

                // WRITE INGREDIENTS DETAILS
                for (size_t j = 0; j < recipes[i].ingredients.size(); j++) 
                {
                    write<<recipes[i].ingredients[j].name<<"|"<<recipes[i].ingredients[j].unit<<"|";
                }
                write<<recipes[i].instruction.size()<<"|";

                // WRITE INSTRUCTION STEPS
                for (size_t j = 0; j < recipes[i].instruction.size(); j++) 
                {
                    write<<recipes[i].instruction[j]<<"|";
                }
                write<<recipes[i].cooking_time<<"|"<<static_cast<DifficultyLevel>(recipes[i].difficulty_level)<<"|"<<static_cast<Category>(recipes[i].category)<<"|"<<static_cast<Method>(recipes[i].method)<<endl;
            }
            write.close();

            // DISPLAY SUCCESS MESSAGE FOR DELETION
            cout<<endl;
            cout<<"\033[97m";
            cout<<"\033[42m";
            printTabs(5); cout<<"                                                           "<<endl;
            printTabs(5); cout<<"               Recipe Deleted Successfully!                "<<endl;
            printTabs(5); cout<<"                                                           \033[0m"<<endl;
        } 
        else 
        {
            // HANDLE ERROR IF UNABLE TO OPEN FILE FOR WRITING
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
        // DISPLAY CANCEL MESSAGE IF DELETION IS ABORTED
        cout<<endl;
        cout<<"\033[97m";
        cout<<"\033[42m";
        printTabs(5); cout<<"                                                           "<<endl;
        printTabs(5); cout<<"                   Deletion Cancelled!                     "<<endl;
        printTabs(5); cout<<"                                                           \033[0m"<<endl;
    }

    // DISPLAY MENU FOR FURTHER ACTIONS
    cout<<endl;
    cout<<"\033[47m";
    cout<<"\033[30m";
    printTabs(5); cout<<"                                                           "<<endl;
    printTabs(5); cout<<"  [1] Delete another Recipe                                "<<endl;
    printTabs(5); cout<<"  [2] Back to Recipe Menu                                  "<<endl;
    printTabs(5); cout<<"  [3] Exit the Program                                     "<<endl;
    printTabs(5); cout<<"                                                           \033[0m"<<endl;
    cout<<endl;
    printTabs(5); cout<<"  Enter Option: ";

    int option;
    cin>>option;

    switch (option) 
    {
        case 1:
            deleteRecipe(); // RECURSIVE CALL TO DELETE ANOTHER RECIPE
            break;
        case 2:
            return; // RETURN TO THE MAIN LOOP
        case 3:
            printTabs(5); cout<<"  Exiting the program..."<<endl;
            exit(0); // EXIT THE PROGRAM
        default:
            // HANDLE INVALID OPTION AND EXIT
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

void checkExistingRecipe() // FUNCTION TO ALLOW USER TO CHECK EXISTING RECIPE
{
    clearScreen(); // CLEAR THE SCREEN BEFORE DISPLAYING CONTENTS

    ifstream file("recipes.txt"); // OPEN THE RECIPES FILE FOR READING

    if (!file.is_open()) 
    {
        // DISPLAY ERROR MESSAGE IF FILE OPENING FAILED
        cout<<endl;
        cout<<"\033[97m";
        cout<<"\033[41m";
        printTabs(5); cout<<"                                                           "<<endl;
        printTabs(5); cout<<"                  Unable to open file!                     "<<endl;
        printTabs(5); cout<<"                                                           \033[0m"<<endl;

        // PROMPT USER TO CONTINUE
        cout<<endl;
        printTabs(6); cout<<"        Press Enter to continue...";
        cin.ignore();
        cin.get();

        return; // EXIT FUNCTION
    }

    clearScreen(); // CLEAR THE SCREEN AGAIN BEFORE DISPLAYING RECIPES

    if(file.is_open())
    {
        loadRecipe(); // LOAD RECIPES INTO MEMORY

        // DISPLAY HEADER FOR CHECKING EXISTING RECIPES
        cout<<"\033[46m";
        cout<<"\033[97m";
        printTabs(5); cout<<"                                                           "<<endl;
        printTabs(5); cout<<"                   Check Existing Recipe                   "<<endl;
        printTabs(5); cout<<"                                                           \033[0m"<<endl;
        cout<<endl;

        // DISPLAY TABLE HEADER FOR RECIPES
        printTabs(3); cout<<" "<<setw(15)<<left<<"Recipe No."<<setw(25)<<left<<"Recipe Name"<<setw(25)<<left<<"Category"<<setw(20)<<left<<"Difficulty Level"<<endl;
        printTabs(3); cout<<" -----------------------------------------------------------------------------------"<<endl;

        // DISPLAY EACH RECIPE WITH ITS DETAILS
        for (int i = 0; i < count; i++) 
        {
            printTabs(3);
            cout<<"    "<<setw(15)<<left<< i + 1;
            cout<<setw(25)<<left<<recipes[i].name;
            cout<<setw(25)<<left<<categoryToString(recipes[i].category);
            cout<<setw(20)<<left<<difficultyLevelToString(recipes[i].difficulty_level)<<endl;
        }
    
        cout<<endl;

        // DISPLAY MENU FOR FURTHER ACTIONS
        cout<<"\033[47m";
        cout<<"\033[30m";
        printTabs(5); cout<<"                                                           "<<endl;
        printTabs(5); cout<<"  [1] View Recipe Details                                  "<<endl;
        printTabs(5); cout<<"  [2] Add a Recipe to Favorites                            "<<endl;
        printTabs(5); cout<<"  [3] Back to Recipe Menu                                  "<<endl;
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

                // VALIDATE THE RECIPE NUMBER
                if (recipeNumber >= 1 && recipeNumber <= count) 
                {
                    viewRecipe(recipeNumber); // DISPLAY DETAILS OF THE SELECTED RECIPE
                    
                    cout<<endl;
                    printTabs(6); cout<<"  Press Enter to return to the main menu...";

                    cin.ignore();
                    cin.get();
                } 
                else 
                {
                    // HANDLE INVALID RECIPE NUMBER
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
                // STAY ON EXISTING RECIPE PAGE AFTER VIEWING DETAILS
                checkExistingRecipe();
                return;
            }
            case 2:
            {
                int recipeNumber;
                printTabs(5); cout<<"  Enter Recipe Number: ";
                cin>>recipeNumber;

                // VALIDATE THE RECIPE NUMBER
                if (recipeNumber >= 1 && recipeNumber <= count) 
                {
                    if (recipes[recipeNumber - 1].isFavorite)
                    {
                        // DISPLAY MESSAGE IF RECIPE ALREADY IN FAVORITES
                        cout<<endl;
                        cout<<"\033[97m";
                        cout<<"\033[41m";
                        printTabs(5); cout<<"                                                           "<<endl;
                        printTabs(5); cout<<"               Recipe already in favorites!                "<<endl;
                        printTabs(5); cout<<"                                                           \033[0m"<<endl;
                    } 
                    else 
                    {
                        addToFavorites(recipeNumber - 1); // ADD RECIPE TO FAVORITES
                    }
                    
                    cout<<endl;
                    printTabs(6); cout<<"  Press Enter to return to menu...";

                    cin.ignore();
                    cin.get();
                } 
                else 
                {
                    // HANDLE INVALID RECIPE NUMBER
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
                // STAY ON EXISTING RECIPE PAGE AFTER ADDING TO FAVORITES
                checkExistingRecipe();
                return;
            }
            case 3:
                return; // RETURN TO THE MAIN LOOP OR HOMEPAGE FUNCTION
            case 4:
                printTabs(5); cout<< "  Exiting the program..."<<endl;
                exit(0); // EXIT THE PROGRAM
            default:
                // HANDLE INVALID OPTION AND EXIT
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

void viewRecipe(int recipeNumber) // FUNCTION DESIGNED TO DISPLAY INFORMATION ON RECENTLY ADDED/UPDATED RECIPE
{
    clearScreen(); // CLEAR THE SCREEN BEFORE DISPLAYING RECIPE DETAILS

    cout<<"\033[46m"; 
    cout<<"\033[97m"; 
    printTabs(5); cout<<"                                                           "<<endl;
    printTabs(5); cout<<"                       View Recipe                         "<<endl;
    printTabs(5); cout<<"                                                           \033[0m"<<endl;
    cout<<endl;

    // OPEN THE RECIPES FILE FOR READING
    ifstream read("recipes.txt");

    // CHECK IF THE FILE IS OPEN
    if (read.is_open()) 
    {
        // READ THE TOTAL COUNT OF RECIPES FROM THE FILE
        int totalRecipes;
        read >> totalRecipes;
        read.ignore();  // IGNORE THE NEWLINE AFTER READING THE INTEGER

        // CHECK IF THE recipeNumber IS WITHIN VALID RANGE
        if (recipeNumber >= 1 && recipeNumber <= totalRecipes)
        {
            int index = recipeNumber - 1;

            // SKIP TO THE SELECTED RECIPE IN THE FILE
            for (int i = 0; i < index; i++) 
            {
                string line;
                getline(read, line); // READ AND DISCARD LINES UNTIL THE DESIRED RECIPE
            }

            // DISPLAY THE DETAILS OF THE SELECTED RECIPE
            printTabs(5); cout << "  Recipe Name: " << recipes[index].name << endl;
            printTabs(5); cout << "  Ingredients:" << endl;

            for (size_t j = 0; j < recipes[index].ingredients.size(); j++) 
            {
                printTabs(5); cout << "    - " << recipes[index].ingredients[j].name << " (" << recipes[index].ingredients[j].unit << ")" << endl;
            }

            printTabs(5); cout << "  Instructions:" << endl;

            for (size_t j = 0; j < recipes[index].instruction.size(); j++) 
            {
                printTabs(5); cout << "    Step " << j + 1 << ": " << recipes[index].instruction[j] << endl;
            }

            printTabs(5); cout << "  Cooking Time: " << recipes[index].cooking_time << endl;
            printTabs(5); cout << "  Difficulty Level: " << difficultyLevelToString(recipes[index].difficulty_level) << endl;
            printTabs(5); cout << "  Category: " << categoryToString(recipes[index].category) << endl;
            printTabs(5); cout << "  Cooking Method: " << methodToString(recipes[index].method) << endl;
            cout << endl;
        }
        else 
        {
            // DISPLAY ERROR MESSAGE FOR INVALID RECIPE NUMBER
            cout << endl;
            cout << "\033[97m";
            cout << "\033[41m";
            printTabs(5); cout << "                                                           " << endl;
            printTabs(5); cout << "                    Invalid Recipe ID!                     " << endl;
            printTabs(5); cout << "                                                           \033[0m" << endl;
        }
        // CLOSE THE FILE AFTER READING
        read.close();
    }
    else 
    {
        // DISPLAY ERROR MESSAGE FOR UNABLE TO OPEN FILE
        cout << endl;
        cout << "\033[97m";
        cout << "\033[41m";
        printTabs(5); cout << "                                                           " << endl;
        printTabs(5); cout << "                  Unable to open file!                     " << endl;
        printTabs(5); cout << "                                                           \033[0m" << endl;
    }

    cin.ignore(); // WAIT FOR USER INPUT TO CONTINUE
}

void viewRecipeDetails(int index) // FUNCTION DESIGNED TO DISPLAY DETAILS INFORMATION ON RECENTLY ADDED/UPDATED RECIPE
{
    clearScreen();
    
    cout<<"\033[46m";
    cout<<"\033[97m";
    
    // PRINT TOP BANNER
    printTabs(5); cout<<"                                                           "<<endl;
    printTabs(5); cout<<"                   Recipe Details                          "<<endl;
    printTabs(5); cout<<"                                                           \033[0m"<<endl;
    cout<<endl;

    // DISPLAY DETAILS OF THE RECIPE
    printTabs(5); cout<<"  Recipe Name: "<<recipes[index].name<<endl;
    printTabs(5); cout<<"  Ingredients:"<<endl;

    // DISPLAY LIST OF INGREDIENTS
    for (size_t i = 0; i < recipes[index].ingredients.size(); ++i) 
    {
        printTabs(5); cout<<"     - "<<recipes[index].ingredients[i].name<<" ("<<recipes[index].ingredients[i].unit<<")"<<endl;
    }

    // DISPLAY INSTRUCTIONS
    printTabs(5); cout<<"  Instructions:"<<endl;
    for (size_t i = 0; i < recipes[index].instruction.size(); ++i) 
    {
        printTabs(5); cout<<"     Step "<< i + 1 <<": "<<recipes[index].instruction[i]<<endl;
    }

    // DISPLAY COOKING TIME
    printTabs(5); cout<<"  Cooking Time: "<<recipes[index].cooking_time<<endl;

    // DISPLAY DIFFICULTY LEVEL
    printTabs(5); cout<<"  Difficulty Level: "<<difficultyLevelToString(recipes[index].difficulty_level)<<endl;

    // DISPLAY RECIPE CATEGORY
    printTabs(5); cout<<"  Category: "<<categoryToString(recipes[index].category)<<endl;
    printTabs(5); cout<<"  Cooking Method: "<<methodToString(recipes[index].method)<<endl;
}

void chooseCategory() // FUNCTION ALLOWS USER TO SELECT A CATEGORY FROM A PREDEFINED LIST
{
    clearScreen();
    
    cout<<"\033[48;2;255;255;255m";
    cout<<"\033[30m";
    
    // PRINT HEADER
    printTabs(5); cout<<"                                                           "<<endl; 
    printTabs(5); cout<<"                   Select a Category!                      "<<endl; 
    printTabs(5); cout<<"                                                           "<<endl;
    printTabs(5); cout<<"  [1] Appetizer                                            "<<endl; 
    printTabs(5); cout<<"  [2] Main Course                                          "<<endl; 
    printTabs(5); cout<<"  [3] Dessert                                              "<<endl; 
    printTabs(5); cout<<"  [4] Soup                                                 "<<endl; 
    printTabs(5); cout<<"  [5] Snack                                                "<<endl; 
    printTabs(5); cout<<"  [6] Breakfast                                            "<<endl; 
    printTabs(5); cout<<"  [7] Side Dish                                            "<<endl;
    printTabs(5); cout<<"  [8] Other                                                "<<endl; 
    printTabs(5); cout<<"                                                           \033[0m"<<endl;
    cout<<endl;

    // PROMPT USER FOR INPUT
    printTabs(5); cout<<"  Enter your choice: ";
    
    int categoryOption;
    cin >> categoryOption;
    cin.ignore(); // Consume the newline left by cin

    Category category;
 
    // MAP USER INPUT TO CATEGORY ENUM
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
            category = Soup;
            break;
        case 5:
            category = Snack;
            break;
        case 6:
            category = Breakfast;
            break;
        case 7:
            category = SideDish;
            break;
        case 8:
            category = Other;
            break;
        default:
            // HANDLE INVALID OPTION
            cout<<endl;
            cout<<"\033[97m";
            cout<<"\033[41m"; 
            printTabs(5); cout<<"                                                           "<<endl;
            printTabs(5); cout<<"                      Invalid Option!                      "<<endl;
            printTabs(5); cout<<"                                                           \033[0m"<<endl;
            cout<<endl;

            printTabs(6); cout<< "        Press Enter to continue...";
            cin.ignore(); // Clear input buffer
            cin.get(); // Wait for user to press Enter

            return;
    }

    // DISPLAY RECIPES BY SELECTED CATEGORY
    displayByCategory(category);
}

void chooseDifficulty() // FUNCTION ALLOWS USER TO SELECT A DIFFICULTY FROM A PREDEFINED LIST
{
    clearScreen(); // CLEAR THE SCREEN
    
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

    // PROMPT USER FOR INPUT
    printTabs(5); cout<<"  Enter your choice: ";

    int levelOption;
    cin >> levelOption;
    cin.ignore(); // Consume the newline left by cin
    
    DifficultyLevel level;

    // MAP USER INPUT TO DIFFICULTY ENUM
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
            // HANDLE INVALID OPTION
            cout<<endl;
            cout<<"\033[97m"; 
            cout<<"\033[41m"; 
            printTabs(5); cout<<"                                                           "<<endl;
            printTabs(5); cout<<"                      Invalid Option!                      "<<endl;
            printTabs(5); cout<<"                                                           \033[0m"<<endl;
            cout<<endl;

            printTabs(6); cout<< "        Press Enter to continue...";
            cin.ignore(); // Clear input buffer
            cin.get(); // Wait for user to press Enter
            return;
    }

    // DISPLAY RECIPES BY SELECTED DIFFICULTY LEVEL
    displayByDifficulty(level);
}

void displayFavoriteRecipes() // FUNCTION TO DISPLAY RECIPES BY FAVORITES
{
    clearScreen(); // CLEAR THE SCREEN

    // SET BACKGROUND COLOR TO CYAN
    cout<<"\033[46m";
    
    // SET TEXT COLOR TO WHITE
    cout<<"\033[97m";
    
    // PRINT HEADER FOR FAVORITE RECIPES
    printTabs(5); cout<<"                                                           "<<endl;
    printTabs(5); cout<<"                   Favorite Recipes                        "<<endl;
    printTabs(5); cout<<"                                                           \033[0m"<<endl;
    cout<<endl;

    // DISPLAY TABLE HEADER
    printTabs(3); cout<<" "<<setw(15)<<left<<"Recipe No."<<setw(25)<<left<<"Recipe Name"<<setw(25)<<left<<"Category"<<setw(20)<<left<<"Difficulty Level"<<endl;
    printTabs(3); cout<<" -----------------------------------------------------------------------------------"<<endl;

    vector<int> favoriteIndexes; // STORES INDEXES OF FAVORITE RECIPES

    int favoriteCount = 0; // COUNTER FOR FAVORITE RECIPES

    // ITERATE THROUGH RECIPES TO DISPLAY FAVORITES
    for (int i = 0; i < count; i++) 
    {
        if (recipes[i].isFavorite) 
        {
            // DISPLAY EACH FAVORITE RECIPE
            printTabs(3);
            cout<<"    "<<setw(12)<<left<< favoriteCount + 1;
            cout<<setw(25)<<left<<recipes[i].name;
            cout<<setw(24)<<left<<categoryToString(recipes[i].category);
            cout<<setw(20)<<left<<difficultyLevelToString(recipes[i].difficulty_level)<<endl;
            
            favoriteIndexes.push_back(i); // STORE INDEX OF THE FAVORITE RECIPE
            favoriteCount++;
        }
    }

    // IF NO FAVORITE RECIPES FOUND, DISPLAY MESSAGE
    if (favoriteCount == 0) 
    {
        cout<<endl;
        printTabs(7); cout<<"No favorite recipes found."<<endl;
        cout<<endl;
    }

    // SET BACKGROUND COLOR TO GRAY
    cout<<"\033[47m";
    
    // SET TEXT COLOR TO BLACK
    cout<<"\033[30m";
    
    cout<<endl;
    printTabs(5); cout<<"                                                           "<<endl;
    printTabs(5); cout<<"  [1] View Recipe Details                                  "<<endl;
    printTabs(5); cout<<"  [2] Remove a Recipe from Favorites                       "<<endl;
    printTabs(5); cout<<"  [3] Back to Homepage                                     "<<endl;
    printTabs(5); cout<<"  [4] Exit the Program                                     "<<endl;
    printTabs(5); cout<<"                                                           \033[0m"<<endl;
    cout<<endl;

    // PROMPT USER FOR OPTION
    printTabs(5); cout<<"  Enter Option: ";
    int option;
    cin >> option;

    switch (option) 
    {
        case 1: 
        {
            int recipeNumber;

            // PROMPT USER FOR RECIPE NUMBER TO VIEW DETAILS
            printTabs(5); cout<<"  Enter Recipe Number: ";
            cin >> recipeNumber;

            // VALIDATE THE RECIPE NUMBER AGAINST FAVORITES COUNT
            if (recipeNumber >= 1 && recipeNumber <= favoriteCount) 
            {
                int index = favoriteIndexes[recipeNumber - 1]; // GET INDEX OF THE SELECTED FAVORITE RECIPE
                viewRecipeDetails(index); // VIEW RECIPE DETAILS

                // DISPLAY OPTIONS AFTER VIEWING RECIPE DETAILS
                cout<<endl;
                cout<<"\033[47m";
                cout<<"\033[30m";
                printTabs(5); cout<<"                                                           "<<endl;
                printTabs(5); cout<<"  [1] Back to Homepage                                     "<<endl;
                printTabs(5); cout<<"  [2] Exit the Program                                     "<<endl;
                printTabs(5); cout<<"                                                           \033[0m"<<endl;
                cout<<endl;

                // PROMPT USER FOR OPTION AFTER VIEWING DETAILS
                printTabs(5); cout<<"  Enter Option: ";
                int option;
                cin >> option;

                switch (option) 
                {
                    case 1:
                        // RETURN TO HOMEPAGE
                        return;
                    case 2:
                        // EXIT THE PROGRAM
                        printTabs(5); cout<<"  Exiting the program..."<<endl;
                        exit(0);
                    default:
                        // HANDLE INVALID CHOICE
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
                // INVALID RECIPE NUMBER
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
            
            // AFTER VIEWING RECIPE DETAILS, STAY ON FAVORITE RECIPES PAGE
            displayFavoriteRecipes();
            return;
        }
        case 2:
        {
            int recipeNumber;

            // PROMPT USER FOR RECIPE NUMBER TO REMOVE FROM FAVORITES
            printTabs(5); cout<<"  Enter Recipe Number: ";
            cin >> recipeNumber;

            // VALIDATE THE RECIPE NUMBER AGAINST FAVORITES COUNT
            if (recipeNumber >= 1 && recipeNumber <= favoriteCount) 
            {
                int index = favoriteIndexes[recipeNumber - 1]; // GET INDEX OF THE SELECTED FAVORITE RECIPE
                removeFromFavorites(index); // REMOVE RECIPE FROM FAVORITES

                cout<<endl;
                printTabs(6); cout<< "        Press Enter to continue...";
                cin.ignore();
                cin.get();
            } 
            else 
            {
                // INVALID RECIPE NUMBER
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
            
            // AFTER REMOVING RECIPE FROM FAVORITES, STAY ON FAVORITE RECIPES PAGE
            displayFavoriteRecipes();
            return;
        }
        case 3:
            // RETURN TO HOMEPAGE
            return;
        case 4:
            printTabs(5); cout<<"  Exiting the program..."<<endl;
            exit(0); // EXIT THE PROGRAM
        default:
            // HANDLE INVALID CHOICE
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

void displayByCategory(Category category) // FUNCTION TO DISPLAY RECIPES BY CATEGORY
{
    clearScreen(); // CLEAR THE SCREEN BEFORE DISPLAYING RESULTS

    // DISPLAY HEADER WITH CATEGORY NAME
    printTabs(5); cout<<"                                                                    "<<endl;
    printTabs(5); cout<<"             Recipes in Category: " << categoryToString(category)<<endl;
    printTabs(5); cout<<"                                                                    \033[0m"<<endl;
    cout<<endl;
    printTabs(6); cout<<"      "<<setw(20)<<left<<"Recipe No."<<setw(25)<<left<<"Recipe Name"<<endl;
    printTabs(6); cout<<"-----------------------------------------"<<endl;

    // FIND AND DISPLAY RECIPES IN THE SPECIFIED CATEGORY
    vector<int> categIndexes; // Store indexes of recipes in the current category
    int categCount = 0;

    for (int i = 0; i < count; ++i) 
    {
        if (recipes[i].category == category) 
        {
            // DISPLAY RECIPE NUMBER AND NAME
            printTabs(7);
            cout<<" "<<setw(17)<<categCount + 1; // Recipe number
            cout<<setw(25)<<recipes[i].name<<endl; // Recipe name

            categIndexes.push_back(i); // Store index of the recipe
            categCount++;
        }
    }

    if (categCount == 0) 
    {
        // IF NO RECIPES FOUND IN THE CATEGORY, DISPLAY ERROR MESSAGE AND OPTIONS
        cout<<"\033[97m";
        cout<<"\033[41m";
        printTabs(5); cout << "                                                           "<<endl;
        printTabs(5); cout << "            No recipes found in this category!             "<<endl;
        printTabs(5); cout << "                                                           \033[0m"<<endl;
        cout<<endl;

        // DISPLAY MENU OPTIONS FOR NO RECIPES FOUND
        cout<<"\033[47m";
        cout<<"\033[30m";
        printTabs(5); cout<<"                                                           "<<endl;
        printTabs(5); cout<<"  [1] Choose another Category                              "<<endl;
        printTabs(5); cout<<"  [2] Back to Homepage                                     "<<endl;
        printTabs(5); cout<<"  [3] Exit the Program                                     "<<endl;
        printTabs(5); cout<<"                                                           \033[0m"<<endl;
        cout<<endl;

        // PROMPT USER FOR OPTION AND PROCESS BASED ON CHOICE
        printTabs(5); cout<<"  Enter Option: ";
        int option;
        cin>>option;

        switch (option) 
        {
            case 1:
                chooseCategory(); // REDIRECT TO CHOOSE ANOTHER CATEGORY
                break;
            case 2:
                return; // RETURN TO HOMEPAGE OR MAIN MENU
            case 3:
                printTabs(5); cout<<"  Exiting the program..."<<endl;
                exit(0); // EXIT THE PROGRAM
            default:
                // HANDLE INVALID OPTION AND EXIT
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
        // IF RECIPES ARE FOUND, DISPLAY MENU OPTIONS
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

        // PROMPT USER FOR OPTION AND PROCESS BASED ON CHOICE
        printTabs(5); cout<<"  Enter Option: ";
        int option;
        cin>>option;

        switch (option) 
        {
            case 1: 
            {
                // VIEW DETAILS OF A SPECIFIC RECIPE
                int recipeNumber;
                
                printTabs(5); cout<<"  Enter Recipe Number: ";
                cin>>recipeNumber;

                // VALIDATE RECIPE NUMBER
                if (recipeNumber >= 1 && recipeNumber <= categCount) 
                {
                    int index = categIndexes[recipeNumber - 1]; // Get index of the selected recipe

                    viewRecipeDetails(index); // View recipe details

                    // AFTER VIEWING DETAILS, DISPLAY MENU OPTIONS AGAIN
                    cout<<endl;
                    cout<<"\033[47m";
                    cout<<"\033[30m";
                    printTabs(5); cout<<"                                                           "<<endl;
                    printTabs(5); cout<<"  [1] Choose another Category                              "<<endl;
                    printTabs(5); cout<<"  [2] Back to Homepage                                     "<<endl;
                    printTabs(5); cout<<"  [3] Exit the Program                                     "<<endl;
                    printTabs(5); cout<<"                                                           \033[0m"<<endl;
                    cout<<endl;

                    // PROMPT USER FOR OPTION AND PROCESS BASED ON CHOICE
                    printTabs(5); cout<<"  Enter Option: ";
                    int option;
                    cin>>option;

                    switch (option) 
                    {
                        case 1:
                            chooseCategory(); // REDIRECT TO CHOOSE ANOTHER CATEGORY
                            break;
                        case 2:
                            return; // RETURN TO HOMEPAGE OR MAIN MENU
                        case 3:
                            printTabs(5); cout<<"  Exiting the program..."<<endl;
                            exit(0); // EXIT THE PROGRAM
                        default:
                            // HANDLE INVALID OPTION AND EXIT
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
                    // HANDLE INVALID RECIPE NUMBER
                    cout<<endl;
                    cout<<"\033[97m";
                    cout<<"\033[41m";
                    printTabs(5); cout<<"                                                           "<<endl;
                    printTabs(5); cout<<"                    Invalid Recipe Number!                 "<<endl;
                    printTabs(5); cout<<"                                                           \033[0m"<<endl;
                    cout<<endl;

                    // WAIT FOR USER INPUT TO CONTINUE
                    printTabs(6); cout<<"        Press Enter to continue...";
                    cin.ignore(); // Clear input buffer
                    cin.get(); // Wait for user to press Enter

                    chooseCategory(); // REDIRECT TO CHOOSE ANOTHER CATEGORY
                }
                break;
            }
            case 2:
                chooseCategory(); // REDIRECT TO CHOOSE ANOTHER CATEGORY
                break;
            case 3:
                return; // RETURN TO HOMEPAGE OR MAIN MENU
            case 4:
                printTabs(5); cout<<"  Exiting the program..."<<endl;
                exit(0); // EXIT THE PROGRAM
            default:
                // HANDLE INVALID OPTION AND EXIT
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

void displayByDifficulty(DifficultyLevel level) // FUNCTION TO DISPLAY RECIPES BY DIFFICULTY
{
    clearScreen();  // CLEAR THE SCREEN BEFORE DISPLAYING THE RECIPES

    printTabs(5); cout<<"                                                                    "<<endl;
    printTabs(5); cout<<"      Recipes in Difficulty Level: " << difficultyLevelToString(level)<<endl;
    printTabs(5); cout<<"                                                                    "<<endl;
    cout<<endl;
    printTabs(6); cout<<"      "<<setw(20)<<left<<"Recipe No."<<setw(25)<<left<<"Recipe Name"<<endl;
    printTabs(6); cout<<"-----------------------------------------"<<endl;

    vector<int> levelIndexes; // STORE INDEXES OF CURRENT RECIPE LEVELS
    int levelCount = 0;

    for (int i = 0; i < count; ++i) 
    {
        if (recipes[i].difficulty_level == level) 
        {
            printTabs(7);
            cout<<setw(21)<<levelCount + 1; // RECIPE NUMBER
            cout<<setw(25)<<recipes[i].name<<endl; 
            levelIndexes.push_back(i); 
            levelCount++;
        }
    }

    cout<<endl;

    if (levelCount == 0) 
    {
        // IF NO RECIPES FOUND, PROMPT USER WITH OPTIONS
        printTabs(6); cout<<" No recipes found in this difficulty level."<<endl;
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
                return;
            case 3:
                printTabs(5); cout<<"  Exiting the program..."<<endl;
                exit(0);
            default:
                // IF INVALID OPTION, NOTIFY USER AND EXIT
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
        // IF RECIPES FOUND, DISPLAY OPTIONS TO USER
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
                // VIEW DETAILS OF SELECTED RECIPE
                int recipeNumber;

                printTabs(5); cout<<"  Enter Recipe Number: ";
                cin>>recipeNumber;

                if (recipeNumber >= 1 && recipeNumber <= levelCount) 
                {
                    int index = levelIndexes[recipeNumber - 1]; // GET INDEX
                    viewRecipeDetails(index); 

                    // AFTER VIEWING RECIPE DETAILS, SHOW MENU AGAIN
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
                            return; 
                        case 3:
                            printTabs(5); cout<<"  Exiting the program..."<<endl;
                            exit(0); 
                        default:
                            // IF INVALID OPTION, NOTIFY USER AND EXIT
                            cout<<endl;
                            cout<<"\033[97m";  
                            cout<<"\033[41m";  
                            printTabs(5); cout<<"                                                           "<<endl;
                            printTabs(5); cout<<"                      Invalid Choice!                      "<<endl;
                            printTabs(5); cout<<"                                                           \033[0m"<<endl;
                            cout<<endl;

                            printTabs(5); cout<<"  Exiting the program..."<<endl;
                            cin.ignore();
                            cin.get();
                            return;
                    }
                } 
                else 
                {
                    // IF INVALID RECIPE NUMBER, NOTIFY USER AND REDIRECT TO CHOOSE DIFFICULTY LEVEL
                    cout<<endl;
                    cout<<"\033[97m";  
                    cout<<"\033[41m";  
                    printTabs(5); cout<<"                                                           "<<endl;
                    printTabs(5); cout<<"                    Invalid Recipe Number!                 "<<endl;
                    printTabs(5); cout<<"                                                           \033[0m"<<endl;
                    cout<<endl;

                    printTabs(6); cout<< "        Press Enter to continue...";
                    cin.ignore(); // CLEAR INPUT BUFFER
                    cin.get(); 

                    chooseDifficulty();
                }
                break;
            }
            case 2:
                chooseDifficulty();
                break;
            case 3:
                return;
            case 4:
                printTabs(5); cout<<"  Exiting the program..."<<endl;
                exit(0); 
            default:
                // IF INVALID OPTION, NOTIFY USER AND EXIT
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

void addToFavorites(int index) // FUNCTION TO LET USER ADD RECIPE TO FAVORITES
{
    // CHECK IF INDEX IS VALID
    if (index < 0 || index >= count) 
    {
        // IF INVALID INDEX, NOTIFY USER AND RETURN
        cout<<"\033[97m";  
        cout<<"\033[41m";  
        printTabs(5); cout<<"                                                           "<<endl;
        printTabs(5); cout<<"                  Invalid recipe index!                    "<<endl;
        printTabs(5); cout<<"                                                           \033[0m"<<endl;
        cout<<endl;
        return;
    }

    string opt;

    // PROMPT USER TO ADD RECIPE TO FAVORITES
    printTabs(5); cout<<"  Add this recipe to favorites? [Y/N]: ";
    cin>>opt;

    if (opt == "Y" || opt == "y") 
    {
        // IF USER CHOOSES YES (Y), MARK RECIPE AS FAVORITE
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
        // IF USER CHOOSES NO (N), MARK RECIPE AS NOT FAVORITE
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
        // IF INVALID INPUT, NOTIFY USER
        cout<<endl;
        cout<<"\033[97m";  
        cout<<"\033[41m";  
        printTabs(5); cout<<"                                                           "<<endl;
        printTabs(5); cout<<"                     Invalid Input!                        "<<endl;
        printTabs(5); cout<<"              Recipe not added to Favorites!               "<<endl;
        printTabs(5); cout<<"                                                           \033[0m"<<endl;
    }

    // SAVE MODIFICATIONS TO FAVORITES TO FILE
    saveRecipe();
}

void removeFromFavorites(int index) 
{
    loadRecipe();

    // CHECK INDEX IF VALID
    if (index < 0 || index >= count) 
    {
        // IF INVALID INDEX, NOTIFY USER AND RETURN
        cout<<"\033[97m"; 
        cout<<"\033[41m";  
        printTabs(5); cout<<"                                                           "<<endl;
        printTabs(5); cout<<"                  Invalid recipe index!                    "<<endl;
        printTabs(5); cout<<"                                                           \033[0m"<<endl;
        cout<<endl;
        return;
    }

    string opt;

    // PROMPT USER TO REMOVE RECIPE FROM FAVORITES
    printTabs(5); cout<<"  Remove this recipe from favorites? [Y/N]: ";
    cin>>opt;

    if (opt == "Y" || opt == "y") 
    {
        // IF USER CHOOSES YES (Y), MARK RECIPE AS NOT FAVORITE
        recipes[index].isFavorite = false;
        cout<<endl;
        cout<<"\033[97m";  
        cout<<"\033[42m";  
        printTabs(5); cout<<"                                                           "<<endl;
        printTabs(5); cout<<"              Recipe removed from Favorites!               "<<endl;
        printTabs(5); cout<<"                                                           \033[0m"<<endl;

        // SAVE UPDATED FAVORITES TO FILE AFTER MODIFICATION
        saveRecipe();
    } 
    else if (opt == "N" || opt == "n") 
    {
        // IF USER CHOOSES NO (N), NOTIFY USER
        cout<<endl;
        cout<<"\033[97m";  
        cout<<"\033[42m"; 
        printTabs(5); cout<<"                                                           "<<endl;
        printTabs(5); cout<<"               Recipe remains in Favorites!                "<<endl;
        printTabs(5); cout<<"                                                           \033[0m"<<endl;
    } 
    else 
    {
        // IF INVALID INPUT, NOTIFY USER
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

void printTabs(int tabNum) // FUNCTION TO ADD TABS
{
    for (int i = 0; i < tabNum; ++i) 
    {
        cout<<"\t";
    }
}

void clearScreen() // FUNCTION TO CLEAR SCREEN
{
    cout<<"\033[2J\033[1;1H";
}
