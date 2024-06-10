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

Recipe recipes[100]; // ARRAY OF RECIPE STRUCT TO STORE MANY RECIPES 
int opt = 0, count = 0;

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
    // OPEN THE FILE
    ifstream file("recipes.txt");
    // IF FILE DOESN'T EXIST, RETURN
    if(!file.is_open())
    {
        // DISPLAY ERROR MESSAGE
        cout<<endl;
        cout<<"\033[97m"; 
        cout<<"\033[41m";
        cout<<"                                                           "<<endl;
        cout<<"                  Unable to open file!                     "<<endl;
        cout<<"               Please check the file path!                 "<<endl;
        cout<<"                                                           \033[0m"<<endl;
        cout<<endl;
        
        // WAIT FOR USER INPUT
        cin.ignore();
        cin.get();
        
        // CLOSE THE FILE STREAM
        file.close(); 
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

    // CALL FUNCTION TO ADD RECIPE ITEMS
    addRecipeItems();

    cout<<endl;
    cout<<"\033[47m"; 
    cout<<"\033[30m";
    cout<<"                                                           "<<endl;
    cout<<"  [1] Add another Recipe                                   "<<endl;
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

void addRecipeItems()
{
    cin.ignore();
    cout<<"  Enter Recipe Name: ";
    getline(cin, recipes[count].name);

    int ingredients_qty;
    cout<<"  Enter Quantity of Ingredients: ";
    cin>>ingredients_qty;
    // CHECK IF INPUT IS INVALID
    if(cin.fail() || ingredients_qty < 0) 
    {
        // DISPLAY ERROR MESSAGE
        cout<<endl;
        cout<<"\033[97m"; 
        cout<<"\033[41m";
        cout<<"                                                           "<<endl;
        cout<<"           Invalid input for Ingredients Quantity!         "<<endl;
        cout<<"                                                           \033[0m"<<endl;
        // CLEAR ERROR FLAGS AND IGNORE THE REMAINING INPUT
        cin.clear();
        // IGNORES CHARACTERS IN THE INPUT BUFFER UP TO AND INCLUDING THE NEXT NEWLINE CHARACTER
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    cin.ignore();
    // RESIZE THE INGREDIENTS VECTOR
    recipes[count].ingredients.resize(ingredients_qty); // .resize CHANGE VECTOR SIZE
    // PROMPT USER TO ENTER EACH INGREDIENT
    for(int i = 0; i < ingredients_qty; i++)
    {
        cout<<"  Enter Ingredient "<<i + 1<<": ";
        getline(cin, recipes[count].ingredients[i]);
    }

    int procedure_qty;
    cout<<"  Enter Number of Steps in Procedure: ";
    cin>>procedure_qty;
    // CHECK IF INPUT IS INVALID
    if(cin.fail() || procedure_qty < 0) 
    {
        cout<<endl;
        cout<<"\033[97m"; 
        cout<<"\033[41m";
        cout<<"                                                           "<<endl;
        cout<<"            Invalid input for Procedure Quantity!          "<<endl;
        cout<<"                                                           "<<endl;
        // CLEAR ERROR FLAGS AND IGNORE THE REMAINING INPUT
        cin.clear();
        // IGNORES CHARACTERS IN THE INPUT BUFFER UP TO AND INCLUDING THE NEXT NEWLINE CHARACTER
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cin.ignore();
    // RESIZE THE PROCEDURE VECTOR
    recipes[count].procedure.resize(procedure_qty); // .resize CHANGE VECTOR SIZE
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

    // INCREMENT COUNT AFTER RECIPE SUCCESSFULLY ADDED
    count++;

    cout<<endl;
    cout<<"\033[97m"; 
    cout<<"\033[42m";
    cout<<"                                                           "<<endl;
    cout<<"                Recipe Added Successfully!                 "<<endl;
    cout<<"                                                           \033[0m"<<endl;
    // SAVE THE RECIPE TO THE FILE
    saveRecipe();

    // RELOAD THE RECIPES FROM THE FILE TO UPDATE COUNT VARIABLE
    loadRecipe();

    // VIEW THE RECENT ADDED RECIPE
    viewRecipe(count);
}

void viewRecipe(int recipeNumber)
{
    clearScreen();
    cout<<"\033[46m"; 
    cout<<"\033[97m"; 
    cout<<"                                                           "<<endl;
    cout<<"                       View Recipe                         "<<endl;
    cout<<"                                                           \033[0m"<<endl;
    cout<<endl;

    // OPEN THE FILE TO READ
    ifstream read("recipes.txt");

    // CHECK IF THE FILE IS OPEN
    if(read.is_open())
    {
        // READ THE TOTAL COUNT OF RECIPES
        int totalRecipes;
        read>>totalRecipes;
        read.ignore();

        // CHECK IF THE RECIPE NUMBER IS VALID
        if(recipeNumber >= 1 && recipeNumber <= totalRecipes)
        {
            int index = recipeNumber - 1;

            // SKIP TO THE SELECTED RECIPE
            for(int i = 0; i < index; i++)
            {
                string line;
                // SKIP RECIPE NAME
                getline(read, line, '|');
                 // READ NUMBER OF INGREDIENTS
                int ingredients_qty;
                read>>ingredients_qty;
                read.ignore();
                // READ NUMBER OF INGREDIENTS
                for(int j = 0; j < ingredients_qty; j++)
                {
                    getline(read, line, '|');
                }
                // READ NUMBER OF PROCEDURE STEPS
                int procedure_qty;
                read>>procedure_qty;
                read.ignore();
                // SKIP PROCEDURE
                for(int j = 0; j < procedure_qty; j++)
                {
                    getline(read, line, '|');
                }
                // SKIP COOKING TIME, DIFFICULTY LEVEL, AND CATEGORY
                getline(read, line); // READ UNTIL THE END OF THE LINE
            }

            // DISPLAY THE DETAILS OF THE SELECTED RECIPE
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
            // DISPLAY ERROR MESSAGE
            cout<<endl;
            cout<<"\033[97m"; 
            cout<<"\033[41m";
            cout<<"                                                           "<<endl;
            cout<<"                    Invalid Recipe ID!                     "<<endl;
            cout<<"                                                           \033[0m"<<endl;
        }
        // CLOSE FILE
        read.close();
    } else
    {
        // DISPLAY ERROR MESSAGE
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
    // OPEN THE FILE TO READ
    ifstream file("recipes.txt");
    // CHECK IF THE FILE IS OPEN
    if(!file.is_open())
    {
        // FILE DOESN'T EXIST, DISPLAY ERROR AND RETURN TO MAIN
        cout<<endl;
        cout<<"\033[97m"; 
        cout<<"\033[41m";
        cout<<"                                                           "<<endl;
        cout<<"                  Unable to open file!                     "<<endl;
        cout<<"               Please check the file path!                 "<<endl;
        cout<<"                                                           \033[0m"<<endl;
        cout<<endl;
        
        // WAIT FOR USER INPUT
        cin.ignore();
        cin.get();
        
        // CLOSE FILE 
        file.close(); 
        return;
    }
    // LOAD RECIPES FROM THE FILE
    loadRecipe();
    clearScreen();

    cout<<"\033[46m"; 
    cout<<"\033[97m";
    cout<<"                                                           "<<endl;
    cout<<"                   Check Existing Recipe                   "<<endl;
    cout<<"                                                           \033[0m"<<endl;
    cout<<endl;
    
    // DISPLAY DETAILS OF EXISTING RECIPES
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
    // WAIT FOR USER INPUT
    cin.ignore();
    cin.get(); 
}

void searchRecipe()
{
    // OPEN THE FILE TO READ
    ifstream file("recipes.txt");
    // CHECK IF THE FILE IS OPEN
    if(!file.is_open())
    {
        // FILE DOESN'T EXIST, DISPLAY ERROR AND RETURN TO MAIN
        cout<<endl;
        cout<<"\033[97m"; 
        cout<<"\033[41m";
        cout<<"                                                           "<<endl;
        cout<<"                  Unable to open file!                     "<<endl;
        cout<<"               Please check the file path!                 "<<endl;
        cout<<"                                                           \033[0m"<<endl;
        cout<<endl;
        
        // WAIT FOR USER INPUT
        cin.ignore();
        cin.get();
        
        // CLOSE THE FILE
        file.close();
        return;
    }

    cin.ignore();
    clearScreen();
    cout<<"\033[46m"; 
    cout<<"\033[97m"; 
    cout<<"                                                           "<<endl;
    cout<<"                    Search Recipe                          "<<endl;
    cout<<"                                                           \033[0m"<<endl;
    cout<<endl;
    cout<<"  Enter Recipe Name to Search: ";
    string searchName;
    getline(cin, searchName);
    
    // VARIABLE TO TRACK IF THE RECIPE IS FOUND
    bool found = false;
    // OPEN FILE STREAM TO READ
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
        // DISPLAY ERROR MESSAGE
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
        // DISPLAY ERROR MESSAGE
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
    cout<<"                                                           "<<endl; 
    cout<<"  [1] Search another Recipe                                "<<endl; 
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
    // OPEN THE FILE TO READ
    ifstream file("recipes.txt");
    // CHECK IF THE FILE IS OPEN
    if(!file.is_open())
    {
        // FILE DOESN'T EXIST, DISPLAY ERROR AND RETURN TO MAIN
        cout<<endl;
        cout<<"\033[97m"; 
        cout<<"\033[41m";
        cout<<"                                                           "<<endl;
        cout<<"                  Unable to open file!                     "<<endl;
        cout<<"               Please check the file path!                 "<<endl;
        cout<<"                                                           \033[0m"<<endl;
        cout<<endl;
        
        //WAIT FOR USER INPUT
        cin.ignore();
        cin.get();
        
        // CLOSE THE FILE STREAM
        file.close(); 
        return;
    }

    clearScreen();
    // LOAD RECIPES FROM FILE
    loadRecipe();
    cout<<"\033[46m"; 
    cout<<"\033[97m"; 
    cout<<"                                                           "<<endl;
    cout<<"                    Update Recipe                          "<<endl;
    cout<<"                                                           \033[0m"<<endl;
    cout<<endl;

    // DISPLAY EXISTING RECIPES
    cout<<"  Existing Recipes:"<<endl;
    for(int i = 0; i < count; i++) 
    {
        cout<<"  "<<i + 1<<". "<<recipes[i].name<<endl;
    }
    
    int num = 0;
    cout<<"\n  Enter Recipe Number to Update: ";
    cin>>num;
    int index = num - 1;

    // CALL FUNCTION TO UPDATE RECIPE ITEMS
    updateRecipeItems(index, num);

    cout<<endl;
    cout<<"\033[47m"; 
    cout<<"\033[30m";
    cout<<"                                                           "<<endl;
    cout<<"  [1] Update another Recipe                                "<<endl; 
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
        return;
    case 3:
        cout << "  Exiting the program..." << endl;
        exit(0); 
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
    // CHECK IF THE INDEX IS VALID
    if(index >= 0 && index < count)
    {
        // CLEAR BUFFER AND DISPLAY SUCCESS MESSAGE
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
            // FLAG TO TRACK INPUT VALIDATION STATUS
            bool validInput = true; 

            cout<<endl;
            cout << "\033[97m"; 
            cout << "\033[42m";
            cout << "                                                           " << endl;
            cout << "             Starting Update of Recipe No." <<1<< "!               " << endl;
            cout << "                                                           \033[0m" << endl;
            cout<<endl;
            // UPDATE RECIPE NAME
            cout<<"  Enter Recipe Name: ";
            getline(cin, recipes[index].name);

            // GET QUANTITY OF INGREDIENTS
            int ingredients_qty;
            cout<<"  Enter Quantity of Ingredients: ";
            cin>>ingredients_qty;

            if(cin.fail() || ingredients_qty < 0) 
            {
                // SET FLAG TO FALSE IF INPUT IS INVALID
                validInput = false; 
                cout<<endl;
                cout<<"\033[97m"; 
                cout<<"\033[41m";
                cout<<"                                                           "<<endl;
                cout<<"           Invalid input for Ingredients Quantity!         "<<endl;
                cout<<"                                                           \033[0m"<<endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            // IGNORE NEWLINE CHARACTER LEFT IN THE BUFFER
            cin.ignore(); 

            // PROCEED WITH FURTHER INPUT ONLY IF ALL PREVIOUS INPUT IS VALID OR TRUE
            if (validInput) 
            {
                // RESIZE INGREDIENTS VECTOR AND PROMPT TO ENTER EACH INGREDIENTS
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
                    // SET FLAG TO FALSE IF INPUT IS INVALID
                    validInput = false; 
                    cout<<endl;
                    cout<<"\033[97m"; 
                    cout<<"\033[41m";
                    cout<<"                                                           "<<endl;
                    cout<<"            Invalid input for Procedure Quantity!          "<<endl;
                    cout<<"                                                           "<<endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                // IGNORE NEWLINE CHARACTER LEFT IN THE BUFFER
                cin.ignore(); 

                // PROCEED WITH FURTHER INPUT ONLY IF ALL PREVIOUS INPUT IS VALID OR TRUE
                if (validInput) 
                {
                    // RESIZE PROCEDURE VECTOR AND PROMPT TO ENTER EACH PROCEDURE STEP
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

                    // SAVE RECIPE
                    saveRecipe(); 
                    // LOAD RECIPE
                    loadRecipe();

                    cout<<endl;
                    viewRecipe(num);
                }
            }
        } else
        { 
            // DISPLAY MESSAGE IF UPDATE CANCELLED
            cout<<endl;
            cout<<"\033[97m"; 
            cout<<"\033[41m";
            cout<<"                                                           "<<endl;
            cout<<"                     Update Cancelled!                     "<<endl;
            cout<<"                                                           \033[0m"<<endl;
        }
    } else
    {
        // DISPLAY ERROR MESSAGE
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
    // OPEN THE FILE TO READ
    ifstream file("recipes.txt");
    // CHECK IF THE FILE IS OPEN
    if(!file.is_open())
    {
        // FILE DOESN'T EXIST, DISPLAY ERROR AND RETURN TO MAIN
        cout<<endl;
        cout<<"\033[97m"; 
        cout<<"\033[41m";
        cout<<"                                                           "<<endl;
        cout<<"                  Unable to open file!                     "<<endl;
        cout<<"               Please check the file path!                 "<<endl;
        cout<<"                                                           \033[0m"<<endl;
        cout<<endl;
        
        // WAIT FOR USER INPUT
        cin.ignore();
        cin.get();
        
        // CLOSE FILE
        file.close();
        return;
    }

    clearScreen();
    cout<<"\033[46m"; 
    cout<<"\033[97m";
    cout<<"                                                           "<<endl;
    cout<<"                    Delete Recipe                          "<<endl;
    cout<<"                                                           \033[0m"<<endl;
    cout<<endl;

    // DISPLAY EXISTING RECIPE IN FILE
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
    cin.ignore();
    int index = num - 1;

    // CHECK IF INDEX IS VALID
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
            // SHIFT RECIPES UP TO FILL THE GAP
            for(int i = index; i < count - 1; i++)
            {
                recipes[i] = recipes[i + 1];    
            }
            count--;

            // SAVE UPDATED RECIPES TO THE FILE
            ofstream write("recipes.txt");

            if(write.is_open())
            {
                // WRITE THE TOTAL COUNT OF RECIPES
                write<<count<<endl;

                // WRITE EACH RECIPE TO THE FILE
                for(int i = 0; i < count; i++)
                {
                    // WRITE RECIPE DATA HERE
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

                // CLOSE FILE STREAM
                write.close();
            } else
            {
                // DISPLAY ERROR MESSAGE
                cout<<endl;
                cout<<"\033[97m"; 
                cout<<"\033[41m";
                cout<<"                                                           "<<endl;
                cout<<"                    Unable to open file                    "<<endl;
                cout<<"                                                           \033[0m"<<endl;
            }
            // DISPLAY SUCCESS MESSAGE
            cout<<endl;
            cout<<"\033[97m"; 
            cout<<"\033[42m";
            cout<<"                                                           "<<endl;
            cout<<"               Recipe Deleted Successfully!                "<<endl;
            cout<<"                                                           \033[0m"<<endl;
        } else
        {
            // DISPLAY IF DELETION IS CANCELLED
            cout<<endl;
            cout<<"\033[97m"; 
            cout<<"\033[42m";
            cout<<"                                                           "<<endl;
            cout<<"                   Deletion Cancelled!                     "<<endl;
            cout<<"                                                           \033[0m"<<endl;
        }
    } else
    {
        // DISPLAY ERROR MESSAGE
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
    cout<<"                                                           "<<endl; 
    cout<<"  [1] Delete another Recipe                                "<<endl; 
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
            return;
        case 3:
            cout<<"  Exiting the program..."<<endl;
            exit(0); 
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
