Quadigi Interactive Calculator
This project is an interactive calculator built in C++ using CMake for build configuration and GoogleTest for unit testing.

Prerequisites
CMake (version 3.10 or later) installed in C:\Program Files\CMake
Visual Studio 17 2022 (or a compatible C++ compiler/generator)
A C++ development environment (e.g., Visual Studio Code, Command Prompt, etc.)
Building and Running the Interactive Calculator
Clone or Download the Repository
Ensure that you have the repository on your local machine. The project structure should look like:

Quadigi-main/
├── CMakeLists.txt
├── src/
│   └── main.cpp
└── tests/
    ├── CMakeLists.txt
    └── TestCalculator.cpp
Open a Command Prompt and Navigate to the Project Root
For example:

cd C:\Users\Tomas\Desktop\Quadigi-main
Create a Clean Build Directory
It’s best to perform an out-of-source build. Create a new folder and navigate into it:

mkdir build_new
cd build_new
Configure the Project with CMake
Run:

"C:\Program Files\CMake\bin\cmake.exe" -G "Visual Studio 17 2022" ..
This command tells CMake to use the parent folder (which contains CMakeLists.txt) as the source.

Build the Project
Once configuration is complete, build the project:

"C:\Program Files\CMake\bin\cmake.exe" --build . --config Debug
Run the Calculator
Navigate to the Debug folder and launch the executable:

cd Debug
Calculator.exe
You should see the prompt:

Enter expression:
Now you can type your arithmetic expression to test the calculator.

Running Unit Tests
Navigate to the Tests Folder
Open a command prompt and go to the tests directory:

cd C:\Users\Tomas\Desktop\Quadigi-main\tests
Create a Build Directory for Tests
For example:

mkdir build
cd build
Configure the Tests with CMake
Run:

"C:\Program Files\CMake\bin\cmake.exe" -G "Visual Studio 17 2022" ..
Build the Tests
Then build the tests:

"C:\Program Files\CMake\bin\cmake.exe" --build . --config Debug
Run the Test Executable
Navigate to the Debug folder and run:

cd Debug
TestCalculator.exe
This will run all your unit tests and display the results.

Troubleshooting
CMake Cache Issues:
If you get errors about mismatched source directories or cache issues, delete your build directory (or its contents) and start a fresh build.
Environment Setup:
Make sure all prerequisites are installed in their default locations, as specified.
This documentation will help any reviewer or tester understand how to build, run, and test your project.