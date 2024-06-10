#include <iostream>
#include <fstream>
#include <string>
#include <limits>
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
void addIngredients();
void loadRecipe();
void saveRecipe();
void searchRecipe();
void checkExistingRecipe();
void clearScreen();
void updateRecipe();
void updateRecipeItems(int num, int count);
void viewRecipe(int recipeNumber);
void deleteRecipe();

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
        cout<<"\033[47m"; 
        cout<<"\033[30m";
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

void saveRecipe() 
{
    // OPEN FILE STREAM FOR WRITING
    ofstream write("recipes.txt");

    // WRITE THE TOTAL COUNT OF RECIPE
    write<<count<<endl;

    // LOOP THROUGH EACH RECIPE
    for(int i = 0; i < count; i++) 
    {
        // WRITE RECIPE NAME, NUMBER OF INGREDIENTS, AND INGREDIENTS 
        write<<recipes[i].name<<"|"<<recipes[i].ingredients.size()<<"|"; // .size RETURNS NUMBER OF ELEMENTS STORED IN VECTOR 
        for(size_t j = 0; j < recipes[i].ingredients.size(); j++) 
        {
            write<<recipes[i].ingredients[j]<<"|";
        }

        // WRITE NUMBER OF PROCEDURE STEPS AND PROCEDURE 
        write<<recipes[i].procedure.size()<<"|";
        for(size_t j = 0; j < recipes[i].procedure.size(); j++) 
        {
            write<<recipes[i].procedure[j]<<"|";
        }

        // WRITE COOKING TIME, DIFFICULTY LEVEL, AND CATEGORY 
        write<<recipes[i].cooking_time<<"|"<<recipes[i].difficulty_level<<"|"<<recipes[i].category<<endl;
    }
    // CLOSE THE FILE STREAM
    write.close();
}

void loadRecipe() 
{
    // OPEN FILE STREAM FOR READING
    ifstream read("recipes.txt");

    // CHECK IF FILE IS OPEN 
    if(read.is_open()) 
    {
        // READ THE TOTAL COUNT OF RECIPES 
        read >> count; // 4
        read.ignore();

        // LOOP THROUGH EACH RECIPES
        for(int i = 0; i < count; i++) 
        {
            // READ RECIPE NAME
            getline(read, recipes[i].name, '|');

            int ingredients_qty;
            read>>ingredients_qty;
            read.ignore();
            // RESIZE INGREDIENTS QTY VECTOR
            recipes[i].ingredients.resize(ingredients_qty);

            // READ INGREDIENTS
            for(int j = 0; j < ingredients_qty; j++) 
            {
                getline(read, recipes[i].ingredients[j], '|');
            }

            int procedure_qty;
            read>>procedure_qty;
            read.ignore(); // IGNORE ANY REMAINING CHARACTERS 
            // RESIZE PROCEDURE QTY VECTOR
            recipes[i].procedure.resize(procedure_qty);

            for(int j = 0; j < procedure_qty; j++) 
            { // READ PROCEDURE
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
    std::ifstream file("recipes.txt");
    if(!file.is_open())
    {
        // File doesn't exist, inform the user and wait for input before returning
        cout<<endl;
        cout<<"\033[97m"; 
        cout<<"\033[41m";
        cout<<"                                                           "<<endl;
        cout<<"                  Unable to open file!                     "<<endl;
        cout<<"               Please check the file path!                 "<<endl;
        cout<<"                                                           \033[0m"<<endl;
        cout<<endl;
        
        // Wait for user input
        cin.ignore();
        cin.get();
        
        file.close(); // Close the file stream
        return;
    }

    
    // File exists, proceed with adding recipe

    clearScreen();
    cout<<"\033[46m"; // Set magenta background
    cout<<"\033[97m"; // Set text color to white
    cout<<"                                                           "<<endl;
    cout<<"                        Add Recipe                         "<<endl;
    cout<<"                                                           \033[0m"<<endl;
    cout<<endl;

    addIngredients();

    cout<<endl;
    cout<<"\033[47m"; 
    cout<<"\033[30m";
    cout<<"                                                           "<<endl; // Start of line with white background
    cout<<"  [1] Add another Recipe                                   "<<endl; // Rest of the line
    cout<<"  [2] Back to Homepage                                     "<<endl;
    cout<<"  [3] Exit the Program                                     "<<endl;
    cout<<"                                                           \033[0m"<<endl;
    cout<<endl;
    cout<<"  Enter Option: ";
    int option;
    cin>>option;

    switch(option)
    {
        case 1:
            addRecipe();
            break;
        case 2:
            return; // Return to the main loop
        case 3:
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

void addIngredients()
{
    cin.ignore();
    cout<<"  Enter Recipe Name: ";
    getline(cin, recipes[count].name);

    int ingredients_qty;
    cout<<"  Enter Quantity of Ingredients: ";
    cin>>ingredients_qty;
    if(cin.fail() || ingredients_qty < 0) 
    {
        cout<<endl;
        cout<<"\033[97m"; 
        cout<<"\033[41m";
        cout<<"                                                           "<<endl;
        cout<<"           Invalid input for Ingredients Quantity!         "<<endl;
        cout<<"                                                           \033[0m"<<endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    cin.ignore();
    // RESIZE THE INGREDIENTS VECTOR
    recipes[count].ingredients.resize(ingredients_qty); // .resize changes size of the vector
    // PROMPT USER TO ENTER EACH INGREDIENT
    for(int i = 0; i < ingredients_qty; i++)
    {
        cout<<"  Enter Ingredient "<<i + 1<<": ";
        getline(cin, recipes[count].ingredients[i]);
    }

    int procedure_qty;
    cout<<"  Enter Number of Steps in Procedure: ";
    cin>>procedure_qty;
    if(cin.fail() || procedure_qty < 0) 
    {
        cout<<endl;
        cout<<"\033[97m"; 
        cout<<"\033[41m";
        cout<<"                                                           "<<endl;
        cout<<"            Invalid input for Procedure Quantity!          "<<endl;
        cout<<"                                                           "<<endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return; // Return from the function instead of calling addRecipe()
    }

    cin.ignore();
    // RESIZE THE PROCEDURE VECTOR
    recipes[count].procedure.resize(procedure_qty);
    // PROMPT USER TO ENTER EACH PROCEDURE STEP
    for(int i = 0; i < procedure_qty; i++)
    {
        cout<<"  Enter Procedure Step "<<i + 1<<": ";
        getline(cin, recipes[count].procedure[i]);
    }

    cout<<"  Enter Cooking Time: ";
    getline(cin, recipes[count].cooking_time);
    cout<<"  Enter Difficulty Level: ";
    getline(cin, recipes[count].difficulty_level);
    cout<<"  Enter Category: ";
    getline(cin, recipes[count].category);

    // Increment count after successfully adding a recipe
    count++;

    cout<<endl;
    cout<<"\033[97m"; 
    cout<<"\033[42m";
    cout<<"                                                           "<<endl;
    cout<<"                Recipe Added Successfully!                 "<<endl;
    cout<<"                                                           \033[0m"<<endl;
    saveRecipe();

    // Reload the recipes from the file to update count
    loadRecipe();

    // View the recipe you just added
    viewRecipe(count);
}

void viewRecipe(int recipeNumber)
{
    clearScreen();
    cout<<"\033[46m"; // Set magenta background
    cout<<"\033[97m"; // Set text color to white
    cout<<"                                                           "<<endl;
    cout<<"                       View Recipe                         "<<endl;
    cout<<"                                                           \033[0m"<<endl;
    cout<<endl;

    // Open the file for reading
    ifstream read("recipes.txt");

    // Check if the file is open
    if(read.is_open())
    {
        // Read the total count of recipes
        int totalRecipes;
        read>>totalRecipes;
        read.ignore();

        // Check if the recipe number is valid
        if(recipeNumber >= 1 && recipeNumber <= totalRecipes)
        {
            int index = recipeNumber - 1;

            // Skip to the selected recipe
            for(int i = 0; i < index; i++)
            {
                string line;
                // Skip recipe name
                getline(read, line, '|');
                // Read number of ingredients
                int ingredients_qty;
                read>>ingredients_qty;
                read.ignore();
                // Skip ingredients
                for(int j = 0; j < ingredients_qty; j++)
                {
                    getline(read, line, '|');
                }
                // Read number of procedure steps
                int procedure_qty;
                read>>procedure_qty;
                read.ignore();
                // Skip procedure
                for(int j = 0; j < procedure_qty; j++)
                {
                    getline(read, line, '|');
                }
                // Skip cooking time, difficulty level, and category
                getline(read, line); // Read until the end of the line
            }

            // Display the details of the selected recipe
            cout<<"  Recipe Name: "<<recipes[index].name<<endl;
            cout<<"  Ingredients:"<<endl;
            for(size_t j = 0; j < recipes[index].ingredients.size(); j++)
            {
                cout<<"    • "<<recipes[index].ingredients[j]<<endl;
            }
            cout<<"  Instructions:"<<endl;
            for(size_t j = 0; j < recipes[index].procedure.size(); j++)
            {
                cout<<"    • "<<recipes[index].procedure[j]<<endl;
            }
            cout<<"  Cooking Time: "<<recipes[index].cooking_time<<endl;
            cout<<"  Difficulty Level: "<<recipes[index].difficulty_level<<endl;
            cout<<"  Category: "<<recipes[index].category;
        } else
        {
            cout<<endl;
            cout<<"\033[97m"; 
            cout<<"\033[41m";
            cout<<"                                                           "<<endl;
            cout<<"                    Invalid Recipe ID!                     "<<endl;
            cout<<"                                                           \033[0m"<<endl;
        }
        read.close();
    } else
    {
        cout<<endl;
        cout<<"\033[97m"; 
        cout<<"\033[41m";
        cout<<"                                                           "<<endl;
        cout<<"                  Unable to open file!                     "<<endl;
        cout<<"                                                           "<<endl;
    }
    cin.ignore();
}

void checkExistingRecipe()
{
    std::ifstream file("recipes.txt");
    if(!file.is_open())
    {
        // File doesn't exist, inform the user and wait for input before returning
        cout<<endl;
        cout<<"\033[97m"; 
        cout<<"\033[41m";
        cout<<"                                                           "<<endl;
        cout<<"                  Unable to open file!                     "<<endl;
        cout<<"               Please check the file path!                 "<<endl;
        cout<<"                                                           \033[0m"<<endl;
        cout<<endl;
        
        // Wait for user input
        cin.ignore();
        cin.get();
        
        file.close(); // Close the file stream
        return;
    }
    loadRecipe();
    clearScreen();

    cout<<"\033[46m"; // Set magenta background
    cout<<"\033[97m"; // Set text color to white
    cout<<"                                                           "<<endl;
    cout<<"                   Check Existing Recipe                   "<<endl;
    cout<<"                                                           \033[0m"<<endl;
    cout<<endl;
    
    for(int i = 0; i < count; i++)
    {
        cout<<"\033[47m"; 
        cout<<"\033[30m";
        cout<<"                                                           "<<endl;
        cout<<"                       "<<"Recipe No. "<<i + 1<<"                        "<<endl;
        cout<<"                                                           \033[0m"<<endl;
        cout<<endl;
        cout<<"  Recipe Name: "<<recipes[i].name<<endl;
        cout<<"  Ingredients:"<<endl;
        for(size_t j = 0; j < recipes[i].ingredients.size(); j++)
        {
            cout<<"    • "<<recipes[i].ingredients[j]<<endl;
        }
        cout<<"  Instructions:"<<endl;
        for(size_t j = 0; j < recipes[i].procedure.size(); j++)
        {
            cout<<"    • "<<recipes[i].procedure[j]<<endl;
        }
        cout<<"  Cooking Time: "<<recipes[i].cooking_time<<endl;
        cout<<"  Difficulty Level: "<<recipes[i].difficulty_level<<endl;
        cout<<"  Category: "<<recipes[i].category<<endl;
        cout<<endl;
    }
    cin.ignore();
    cin.get(); // Wait for user input
}

void searchRecipe()
{
    std::ifstream file("recipes.txt");
    if(!file.is_open())
    {
        // File doesn't exist, inform the user and wait for input before returning
        cout<<endl;
        cout<<"\033[97m"; 
        cout<<"\033[41m";
        cout<<"                                                           "<<endl;
        cout<<"                  Unable to open file!                     "<<endl;
        cout<<"               Please check the file path!                 "<<endl;
        cout<<"                                                           \033[0m"<<endl;
        cout<<endl;
        
        // Wait for user input
        cin.ignore();
        cin.get();
        
        file.close(); // Close the file stream
        return;
    }

    cin.ignore();
    clearScreen();
    cout<<"\033[46m"; // Set magenta background
    cout<<"\033[97m"; // Set text color to white
    cout<<"                                                           "<<endl;
    cout<<"                    Search Recipe                          "<<endl;
    cout<<"                                                           \033[0m"<<endl;
    cout<<endl;
    cout<<"  Enter Recipe Name to Search: ";
    string searchName;
    getline(cin, searchName);
    
    // VARIABLE TO TRACK IF THE RECIPE IS FOUND
    bool found = false;
    // OPEN FILE STREAM FOR READING
    ifstream read("recipes.txt");
    if(read.is_open()) 
    {
        // READ THE TOTAL COUNT OF RECIPES 
        int totalRecipes;
        read>>totalRecipes;
        read.ignore();

        // LOOP THROUGH EACH RECIPE
        for(int i = 0; i < totalRecipes; i++) 
        {
            // READ RECIPE NAME
            getline(read, recipes[i].name, '|');

            int ingredients_qty;
            read>>ingredients_qty;
            read.ignore();
            // RESIZE INGREDIENTS QTY VECTOR
            recipes[i].ingredients.resize(ingredients_qty);

            // READ INGREDIENTS
            for(int j = 0; j < ingredients_qty; j++)
            {
                getline(read, recipes[i].ingredients[j], '|');
            }

            int procedure_qty;
            read>>procedure_qty;
            read.ignore(); // IGNORE ANY REMAINING CHARACTERS 
            // RESIZE PROCEDURE QTY VECTOR
            recipes[i].procedure.resize(procedure_qty);

            for(int j = 0; j < procedure_qty; j++) 
            { // READ PROCEDURE
                getline(read, recipes[i].procedure[j], '|');
            }

            // READ COOKING TIME, DIFFICULTY LEVEL AND CATEGORY
            getline(read, recipes[i].cooking_time, '|');
            getline(read, recipes[i].difficulty_level, '|');
            getline(read, recipes[i].category);

            // IF RECIPE NAME MATCHES THE SEARCH NAME
            if(recipes[i].name == searchName)
            {
                cout<<endl;
                cout<<"\033[97m"; 
                cout<<"\033[42m";
                cout<<"                                                           "<<endl;
                cout<<"                Recipe Found Successfully!                 "<<endl;
                cout<<"                                                           \033[0m"<<endl;
                cout<<endl;
                cout<<"  Recipe Name: "<<recipes[i].name<<endl;
                cout<<"  Ingredients:"<<endl;
                for(size_t j = 0; j < recipes[i].ingredients.size(); j++)
                {
                    cout<<"    • "<<recipes[i].ingredients[j]<<endl;
                }
                cout<<"  Instructions:"<<endl;
                for(size_t j = 0; j < recipes[i].procedure.size(); j++)
                {
                    cout<<"    • "<<recipes[i].procedure[j]<<endl;
                }
                cout<<"  Cooking Time: "<<recipes[i].cooking_time<<endl;
                cout<<"  Difficulty Level: "<<recipes[i].difficulty_level<<endl;
                cout<<"  Category: "<<recipes[i].category<<endl;
                cout<<endl;
                found = true;
                // EXIT LOOP SINCE RECIPE IS FOUND
                break;
            }
        }
        // CLOSE THE FILE STREAM
        read.close();
    } else 
    {
        cout<<endl;
        cout<<"\033[97m"; 
        cout<<"\033[41m";
        cout<<"                                                           "<<endl;
        cout<<"                  Unable to open file!                     "<<endl;
        cout<<"                                                           "<<endl;
    }
    
    // IF RECIPE NOT FOUND
    if(!found)
    {
        cout<<endl;
        cout<<"\033[97m"; 
        cout<<"\033[41m";
        cout<<"                                                           "<<endl;
        cout<<"                     Recipe Not Found!                     "<<endl;
        cout<<"                                                           "<<endl;
    }

    cout<<endl;
    cout<<"\033[47m"; 
    cout<<"\033[30m";
    cout<<"                                                           "<<endl; // Start of line with white background
    cout<<"  [1] Search another Recipe                                "<<endl; // Rest of the line
    cout<<"  [2] Back to Homepage                                     "<<endl;
    cout<<"  [3] Exit the Program                                     "<<endl;
    cout<<"                                                           \033[0m"<<endl;
    cout<<endl;
    cout<<"  Enter Option: ";
    int option;
    cin>>option;

    switch(option)
    {
        case 1:
            searchRecipe();
            break;
        case 2:
            return; // Return to the main loop
        case 3:
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

void clearScreen()
{
    cout<< "\033[2J\033[1;1H";
}

void updateRecipe() 
{
    std::ifstream file("recipes.txt");
    if(!file.is_open())
    {
        // File doesn't exist, inform the user and wait for input before returning
        cout<<endl;
        cout<<"\033[97m"; 
        cout<<"\033[41m";
        cout<<"                                                           "<<endl;
        cout<<"                  Unable to open file!                     "<<endl;
        cout<<"               Please check the file path!                 "<<endl;
        cout<<"                                                           \033[0m"<<endl;
        cout<<endl;
        
        // Wait for user input
        cin.ignore();
        cin.get();
        
        file.close(); // Close the file stream
        return;
    }

    clearScreen();
    loadRecipe();
    cout<<"\033[46m"; // Set magenta background
    cout<<"\033[97m"; // Set text color to white
    cout<<"                                                           "<<endl;
    cout<<"                    Update Recipe                          "<<endl;
    cout<<"                                                           \033[0m"<<endl;
    cout<<endl;

    // Display existing recipes with their numbers
    cout<<"  Existing Recipes:"<<endl;
    for(int i = 0; i < count; i++) 
    {
        cout<<"  "<<i + 1<<". "<<recipes[i].name<<endl;
    }
    
    int num = 0;
    cout<<"\n  Enter Recipe Number to Update: ";
    cin>>num;
    int index = num - 1;

    updateRecipeItems(index, num);

    cout<<endl;
    cout<<"\033[47m"; 
    cout<<"\033[30m";
    cout<<"                                                           "<<endl; // Start of line with white background
    cout<<"  [1] Update another Recipe                                "<<endl; // Rest of the line
    cout<<"  [2] Back to Homepage                                     "<<endl;
    cout<<"  [3] Exit the Program                                     "<<endl;
    cout<<"                                                           \033[0m"<<endl;
    cout<<endl;
    cout<<"  Enter Option: ";
    int option;
    cin>>option;

    switch(option)
    {
    case 1:
        updateRecipe();
        break;
    case 2:
        return; // Return to the main loop
    case 3:
        cout << "  Exiting the program..." << endl;
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

void updateRecipeItems(int index, int num)
{
    if(index >= 0 && index < count)
    {
        cin.ignore();
        cout<<endl;
        cout<<"\033[97m"; 
        cout<<"\033[42m";
        cout<<"                                                           "<<endl;
        cout<<"                Recipe Found Successfully!                 "<<endl;
        cout<<"                                                           \033[0m"<<endl;
        cout<<endl;
        string choice;
        cout<<"  Confirm to Update Recipe No. "<<num<< "? [Y/N]: ";
        getline(cin, choice);

        if(choice == "Y" || choice == "y")
        {
            bool validInput = true; // Flag to track input validation status

            cout<<endl;
            cout << "\033[97m"; 
            cout << "\033[42m";
            cout << "                                                           " << endl;
            cout << "             Starting Update of Recipe No." <<1<< "!               " << endl;
            cout << "                                                           \033[0m" << endl;
            cout<<endl;
            cout<<"  Enter Recipe Name: ";
            getline(cin, recipes[index].name);

            int ingredients_qty;
            cout<<"  Enter Quantity of Ingredients: ";
            cin>>ingredients_qty;

            if(cin.fail() || ingredients_qty < 0) 
            {
                validInput = false; // Set flag to false if input is invalid
                cout<<endl;
                cout<<"\033[97m"; 
                cout<<"\033[41m";
                cout<<"                                                           "<<endl;
                cout<<"           Invalid input for Ingredients Quantity!         "<<endl;
                cout<<"                                                           \033[0m"<<endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            cin.ignore(); // Ignore newline character left in the buffer

            if (validInput) // Proceed with further input only if all previous input is valid
            {
                recipes[index].ingredients.resize(ingredients_qty);
                for(int i = 0; i < ingredients_qty; i++)
                {
                    cout<< "  Enter Ingredient "<<i + 1<<": ";
                    getline(cin, recipes[index].ingredients[i]);
                }

                int procedure_qty;
                cout<<"  Enter Number of Steps in Procedure: ";
                cin>>procedure_qty;

                if(cin.fail() || procedure_qty < 0) 
                {
                    validInput = false; // Set flag to false if input is invalid
                    cout<<endl;
                    cout<<"\033[97m"; 
                    cout<<"\033[41m";
                    cout<<"                                                           "<<endl;
                    cout<<"            Invalid input for Procedure Quantity!          "<<endl;
                    cout<<"                                                           "<<endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                cin.ignore(); // Ignore newline character left in the buffer

                if (validInput) // Proceed only if all input is valid
                {
                    recipes[index].procedure.resize(procedure_qty);
                    for(int i = 0; i < procedure_qty; i++)
                    {
                        cout<<"  Enter Procedure Step " <<i + 1<<": ";
                        getline(cin, recipes[index].procedure[i]);
                    }

                    cout<<"  Enter Cooking Time: ";
                    getline(cin, recipes[index].cooking_time);
                    cout<<"  Enter Difficulty Level: ";
                    getline(cin, recipes[index].difficulty_level);
                    cout<<"  Enter Category: ";
                    getline(cin, recipes[index].category);

                    cout<<endl;
                    cout<<"\033[97m"; 
                    cout<<"\033[42m";
                    cout<<"                                                           "<<endl;
                    cout<<"               Recipe Updated Successfully!                "<<endl;
                    cout<<"                                                           \033[0m"<<endl;
                    saveRecipe(); // Corrected function call

                    loadRecipe();

                    cout<<endl;
                    viewRecipe(num);
                }
            }
        } else
        {
            cout<<endl;
            cout<<"\033[97m"; 
            cout<<"\033[41m";
            cout<<"                                                           "<<endl;
            cout<<"                     Update Cancelled!                     "<<endl;
            cout<<"                                                           \033[0m"<<endl;
        }
    } else
    {
        cout<<endl;
        cout<<"\033[97m"; 
        cout<<"\033[41m";
        cout<<"                                                           "<<endl;
        cout<<"                    Invalid Recipe ID!                     "<<endl;
        cout<<"                                                           \033[0m"<<endl;
    }
}

void deleteRecipe()
{
    std::ifstream file("recipes.txt");
    if(!file.is_open())
    {
        // File doesn't exist, inform the user and wait for input before returning
        cout<<endl;
        cout<<"\033[97m"; 
        cout<<"\033[41m";
        cout<<"                                                           "<<endl;
        cout<<"                  Unable to open file!                     "<<endl;
        cout<<"               Please check the file path!                 "<<endl;
        cout<<"                                                           \033[0m"<<endl;
        cout<<endl;
        
        // Wait for user input
        cin.ignore();
        cin.get();
        
        file.close(); // Close the file stream
        return;
    }

    clearScreen();
    cout<<"\033[46m"; // Set magenta background
    cout<<"\033[97m"; // Set text color to white
    cout<<"                                                           "<<endl;
    cout<<"                    Delete Recipe                          "<<endl;
    cout<<"                                                           \033[0m"<<endl;
    cout<<endl;

    cout<<"  Existing Recipes:"<<endl;
    for(int i = 0; i < count; i++)
    {
        cout<<"  "<<i + 1<<". "<<recipes[i].name<<endl;
    }

    int num = 0;
    string choice;
    cout<<endl;    
    cout<<"  Enter Recipe ID to Delete: ";
    cin>>num;
    cin.ignore(); // Clear the input buffer
    int index = num - 1;
 
    if(index >= 0 && index < count)
    {
        cout<<endl;
        cout<<endl;
        cout<<"\033[97m"; 
        cout<<"\033[42m";
        cout<<"                                                           "<<endl;
        cout<<"                Recipe Found Successfully!                 "<<endl;
        cout<<"                                                           \033[0m"<<endl;

        cout<<endl;
        cout<<"  Confirm to Delete Recipe No. " << num << "? [Y/N]: ";
        getline(cin, choice);

        if(choice == "Y" || choice == "y")
        {
            for(int i = index; i < count - 1; i++) // Shift recipes up to fill the gap
            {
                recipes[i] = recipes[i + 1];    
            }
            count--;

            // Save the updated recipes to the file
            ofstream write("recipes.txt");

            if(write.is_open())
            {
                // Write the total count of recipes
                write<<count<<endl;

                // Write each recipe to the file
                for(int i = 0; i < count; i++)
                {
                    // Write recipe data here
                    write<<recipes[i].name<< "|" <<recipes[i].ingredients.size()<<"|";
                    for(size_t j = 0; j < recipes[i].ingredients.size(); j++)
                    {
                        write<<recipes[i].ingredients[j]<<"|";
                    }
                    write<<recipes[i].procedure.size()<<"|";
                    for(size_t j = 0; j < recipes[i].procedure.size(); j++)
                    {
                        write<<recipes[i].procedure[j]<<"|";
                    }
                    write<<recipes[i].cooking_time<<"|"<<recipes[i].difficulty_level<<"|"<<recipes[i].category<<endl;
                }
                // Close the file stream
                write.close();
            } else
            {
                cout<<endl;
                cout<<"\033[97m"; 
                cout<<"\033[41m";
                cout<<"                                                           "<<endl;
                cout<<"                    Unable to open file                    "<<endl;
                cout<<"                                                           \033[0m"<<endl;
            }
            cout<<endl;
            cout<<"\033[97m"; 
            cout<<"\033[42m";
            cout<<"                                                           "<<endl;
            cout<<"               Recipe Deleted Successfully!                "<<endl;
            cout<<"                                                           \033[0m"<<endl;
        } else
        {
            cout<<endl;
            cout<<"\033[97m"; 
            cout<<"\033[42m";
            cout<<"                                                           "<<endl;
            cout<<"                   Deletion Cancelled!                     "<<endl;
            cout<<"                                                           \033[0m"<<endl;
        }
    } else
    {
        cout<<endl;
        cout<<"\033[97m"; 
        cout<<"\033[41m";
        cout<<"                                                           "<<endl;
        cout<<"                    Invalid Recipe ID!                     "<<endl;
        cout<<"                                                           \033[0m"<<endl;
    }
    cout<<endl;
    cout<<"\033[47m"; 
    cout<<"\033[30m";
    cout<<"                                                           "<<endl; // Start of line with white background
    cout<<"  [1] Delete another Recipe                                "<<endl; // Rest of the line
    cout<<"  [2] Back to Homepage                                     "<<endl;
    cout<<"  [3] Exit the Program                                     "<<endl;
    cout<<"                                                           \033[0m"<<endl;
    cout<<endl;
    cout<<"  Enter Option: ";
    int option;
    cin>>option;

    switch(option)
    {
        case 1:
            deleteRecipe();
            break;
        case 2:
            return; // Return to the main loop
        case 3:
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
