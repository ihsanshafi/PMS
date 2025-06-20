#include <iostream> // For input/output operations
#if defined _WIN32
    #include <conio.h> // For getch() function to wait for key press in Windows
#endif

using namespace std;

// Function to hold the console until a key is pressed
void holdc() {
    #if defined _WIN32
        getch(); // Wait for a key press in Windows
    #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore remaining input
        cin.get(); // Wait for user input in Linux
    #endif
}

int main() {
    // Print placeholder text for the main function
    cout << "This is a placeholder for the main function.\n";
    cout << "You can implement your main logic here.\n";

    // Print colored text using ANSI escape codes with cout
    cout << "\n"; // Print a newline
    cout << "\x1B[31merror. try again \033[0m\t\t"; // Print red-colored text
    cout << "\x1B[32mTexting\033[0m\t\t"; // Print green-colored text
    cout << "\x1B[33mTexting\033[0m\t\t"; // Print yellow-colored text
    cout << "\x1B[34mTexting\033[0m\t\t"; // Print blue-colored text
    cout << "\x1B[35mTexting\033[0m\n"; // Print magenta-colored text followed by a newline

    // Print cyan-colored text multiple times
    cout << "\x1B[36mTexting\033[0m\t\t"; // Cyan text
    cout << "\x1B[36mTexting\033[0m\t\t"; // Cyan text
    cout << "\x1B[36mTexting\033[0m\t\t"; // Cyan text
    cout << "\x1B[37mTexting\033[0m\t\t"; // White text
    cout << "\x1B[93mTexting\033[0m\n"; // Bright yellow text followed by a newline

    // Print text with background colors using ANSI escape codes
    cout << "\033[3;42;30mTexting\033[0m\t\t"; // Green background, black text
    cout << "\033[3;43;30mTexting\033[0m\t\t"; // Yellow background, black text
    cout << "\033[3;44;30mTexting\033[0m\t\t"; // Blue background, black text
    cout << "\033[3;104;30mTexting\033[0m\t\t"; // Light blue background, black text
    cout << "\033[3;100;30mTexting\033[0m\n"; // Gray background, black text followed by a newline

    // Print text with magenta foreground and white background, using different styles
    cout << "\033[3;47;35mTexting\033[0m\t\t"; // Italic magenta text on white background
    cout << "\033[2;47;35mTexting\033[0m\t\t"; // Dim magenta text on white background
    cout << "\033[1;47;35mTexting\033[0m\t\t"; // Bold magenta text on white background
    cout << "\t\t"; // Print tab spaces
    cout << "\n"; // Print a newline

    holdc(); // Wait for user input before exiting
    return 0; // Exit the program
}