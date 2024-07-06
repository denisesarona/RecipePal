# RecipePal

## Overview

RecipePal is a recipe management system developed in C++ using Dev C++. It allows users to create, read, update, and delete (CRUD) recipes, as well as stream recipe data to and from files. This system provides a simple and efficient way to manage your favorite recipes, making it easy to organize and access them as needed.

## Features

- **Recipe Management**: Add, view, update, and delete recipes.
- **File Streaming**: Save and load recipes from files to ensure data persistence.
- **Add to Favorites**: Mark recipes as favorites for easy access.
- **View by Category**: Filter and view recipes by different categories (e.g., appetizers, main courses, desserts).
- **View by Difficulty**: Filter and view recipes by difficulty level (e.g., beginner, intermediate, advanced).
- **View by Cooking Method**: Filter and view recipes by cooking methods (e.g., baking, grilling, frying).
- **Search Functionality**: Quickly find recipes by name or ingredient.

## Technology Stack

- **Programming Language**: C++
- **Development Environment**: Dev C++

## Installation

### Prerequisites

- Dev C++ (or any compatible C++ IDE)
- Basic knowledge of C++ programming

### Steps

1. **Clone the Repository**

   ```bash
   git clone https://github.com/denisesarona/recipepal.git
   cd recipepal
   ```

2. **Open the Project in Dev C++**

   - Launch Dev C++.
   - Open the `recipepal.cpp` project file.

3. **Build and Run**

   - Build the project by selecting `Execute -> Compile & Run` in the menu.

## Usage

1. **Main Menu**

   Upon running the application, you will be presented with a main menu with the following options:

   - Add a new recipe
   - View all recipes
   - Update an existing recipe
   - Delete a recipe
   - Add to favorites
   - View by category
   - View by difficulty
   - View by cooking method
   - Save recipes to file
   - Load recipes from file
   - Search for a recipe
   - Exit

2. **Adding a Recipe**

   - Select the option to add a new recipe.
   - Enter the recipe name, ingredients, instructions, category, difficulty, and cooking method as prompted.

3. **Viewing Recipes**

   - Select the option to view all recipes.
   - Browse through the list of recipes displayed.

4. **Updating a Recipe**

   - Select the option to update a recipe.
   - Enter the recipe name to update and follow the prompts to modify the details.

5. **Deleting a Recipe**

   - Select the option to delete a recipe.
   - Enter the recipe name to delete.

6. **Adding to Favorites**

   - Select the option to add a recipe to favorites.
   - Enter the recipe name to mark as favorite.

7. **Viewing by Category**

   - Select the option to view recipes by category.
   - Enter the desired category to filter recipes.

8. **Viewing by Difficulty**

   - Select the option to view recipes by difficulty.
   - Enter the desired difficulty level to filter recipes.

9. **Viewing by Cooking Method**

   - Select the option to view recipes by cooking method.
   - Enter the desired cooking method to filter recipes.

10. **Saving and Loading Recipes**

    - Save recipes to a file by selecting the save option. Enter the file name when prompted.
    - Load recipes from a file by selecting the load option. Enter the file name when prompted.

11. **Searching for a Recipe**

    - Select the option to search for a recipe.
    - Enter the recipe name or ingredient to search.

## File Structure

- **recipepal.cpp**: Main source file containing the implementation of RecipePal.
- **recipes.txt**: Default file used for saving and loading recipes.
