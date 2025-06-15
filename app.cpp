// PATIENT DATABASE MANAGEMENT SYSTEM

#include <iostream> // for input/output operations
#include <list> // for list operations
#include <string> // for string operations
#if defined _WIN32
    #include <conio.h> // for getch()
#endif
#include <cctype> // for toupper()
#include <limits> // for numeric_limits
#include <ctime>

using namespace std;
//  Define the Patient structure
struct Patient {
    string name;
    int age;
    int weight;
    char gender;       // M/F (Male/Female)
    string phoneNumber;
    string bloodType;
    string previousConditions; // List of previous conditions
    time_t timestamp;
};

const int MAX_PATIENTS = 100; // Maximum number of patients in the database

// Utility functions
namespace utils {
    // CONSOLE CLEAR FUNCTION
    void Clear(){
        #if defined _WIN32
            system("cls");
        #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
            system("clear");
            //std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences
        #elif defined (__APPLE__)
            system("clear");
        #endif
    }
    // Function to hold the console until a key is pressed
    void holdc() {
        #if defined _WIN32
            getch(); // Wait for a key press in Windows
        #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get();
        #endif
    }
    // Function to validate phone number (basic validation)
    bool isValidPhoneNumber(const string& phone) {
        if (phone.empty()) return false;
        for (char c : phone) {
            if (!isdigit(c) && c != '+' && c != '-' && c != ' ' && c != '(' && c != ')') {
                return false;
            }
        }
        return true;
    }
    // Function to validate blood type
    bool isValidBloodType(const string& bloodType) {
        const string validTypes[] = {"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"};
        for (const auto& type : validTypes) {
            if (bloodType == type) return true;
        }
        return false;
    }
    // Function to list all patients in the database
    void listPatients(const Patient Db[], int numpatients) {
        if (numpatients > 0) {
            cout << "ALL PATIENTS (" << numpatients << ")\n";
            cout << "==========================================\n";
            for (int i = 0; i < numpatients; ++i) {
                cout << "PATIENT #" << (i + 1) << "\n";
                cout << "Name:         " << Db[i].name << "\n";
                cout << "Age:          " << Db[i].age << " years\n";
                cout << "Weight:       " << Db[i].weight << " kg\n";
                cout << "Gender:       " << Db[i].gender << "\n";
                cout << "Blood Type:   " << Db[i].bloodType << "\n";
                cout << "PhoneNum:     " << Db[i].phoneNumber << "\n";
                // Convert timestamp to readable format
                char buffer[80];
                tm* timeinfo = localtime(&Db[i].timestamp);
                strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
                cout << "Registry Date: " << buffer << "\n";
                cout << "==========================================\n";
            }
        } else {
            cout << "Database is empty.\n";
        }
    }
    //  Function to check if a patient already exists in the database
    bool isPatientExists(const Patient Db[], int numpatients, const Patient& newPatient) {
        for (int i = 0; i < numpatients; ++i) {
            // Case-insensitive name comparison
            bool nameMatch = true;
            if (Db[i].name.length() != newPatient.name.length()) {
                nameMatch = false;
            } else {
                for (size_t j = 0; j < Db[i].name.length(); ++j) {
                    if (tolower(Db[i].name[j]) != tolower(newPatient.name[j])) {
                        nameMatch = false;
                        break;
                    }
                }
            }
            
            // Check name and phone number (since these should be unique)
            if (nameMatch && Db[i].phoneNumber == newPatient.phoneNumber) {
                return true;
            }
        }
        return false;
    }
}

void findPatients(const Patient Db[], int numpatients, int searchType) {
    bool found = false;
    if (numpatients == 0) {
        cout << "Database is empty. Cannot search.\n";
        cout << "Press Enter to continue...";
        utils::holdc(); // Wait for user input before clearing the screen
        utils::Clear();
        return; // Return early if no patients are present
    }
    string searchStr = ""; // Initialize searchStr to an empty string
    string normalizedSearch;// For phone number search, we will normalize the input
    int choice;
    switch (searchType) {
        case 1: // Search by name
            cout << "Enter patient name to search: ";
            cin.ignore();
            getline(cin, searchStr);
            // Convert searchStr to lowercase for case-insensitive comparison
            for (char &c : searchStr) c = tolower(c);
            utils::Clear(); // Clear the console screen before displaying results
            cout << "SEARCH RESULTS\n";
            cout << "==================================================\n";
            cout << "Searching for patients with name containing: " << searchStr << "\n";
            for (int i = 0; i < numpatients; ++i) {
                string patientNameLower = Db[i].name;
                // Convert patient name to lowercase for case-insensitive comparison
                for (char &c : patientNameLower) c = tolower(c);
                if (patientNameLower.find(searchStr) != string::npos) {
                    cout << "--------------------------------------------------\n";
                    cout << "PATIENT #" << (i + 1) << "\n";
                    cout << "Name:       " << Db[i].name << "\n";
                    cout << "Age:        " << Db[i].age << " years\n";
                    cout << "Gender:     " << Db[i].gender << "\n";
                    cout << "Blood Type: " << Db[i].bloodType << "\n";
                    cout << "Phone:      " << Db[i].phoneNumber << "\n";
                    cout << "--------------------------------------------------\n";
                    found = true;
                    cout << "==================================================\n";
                    cout << "Select Patient from the search results...\n";
                    cout << "Enter the patient number (1 to " << numpatients << ") to view details: ";
                    
                    int choice;
                    while (!(cin >> choice) || choice < 1 || choice > numpatients) {
                        cout << "Invalid input. Please enter a number between 1 and " << numpatients << ": ";
                        cin.clear();
                        cin.ignore(10000, '\n');
                    }
                    int patientIndex = choice - 1; // Convert to zero-based index

                    displayPatientDetails(Db,patientIndex);

                }
            }
            if (!found) {
                cout << "No patients found with the name containing: " << searchStr << "\n";
            }
            break;

        case 2:// search by phone number
            cout << "Enter phone number to search: ";
            cin.ignore();
            getline(cin, searchStr);
            // Remove any non-digit characters for more flexible searching
            for (char c : searchStr) {
                if (isdigit(c)) {
                    normalizedSearch += c;
                }
            }
            for (int i = 0; i < numpatients; ++i) {
                // Normalize the stored phone number for comparison
                string normalizedDbPhone;
                for (char c : Db[i].phoneNumber) {
                    if (isdigit(c)) {
                        normalizedDbPhone += c;
                    }
                }
                // Check if the search string is contained within the phone number
                if (normalizedDbPhone.find(normalizedSearch) != string::npos) {
                    cout << "PATIENT #" << (i + 1) << "\n";
                    cout << "Name:       " << Db[i].name << "\n";
                    cout << "Age:        " << Db[i].age << " years\n";
                    cout << "Gender:     " << Db[i].gender << "\n";
                    cout << "Blood Type: " << Db[i].bloodType << "\n";
                    cout << "Phone:      " << Db[i].phoneNumber << "\n";
                    cout << "--------------------------------------------------\n";
                    found = true;
                    cout << "==================================================\n";
                    cout << "Select Patient from the search results...\n";
                    cout << "Enter the patient number (1 to " << numpatients << ") to view details: ";
                    int choice;
                    while (!(cin >> choice) || choice < 1 || choice > numpatients) {
                        cout << "Invalid input. Please enter a number between 1 and " << numpatients << ": ";
                        cin.clear();
                        cin.ignore(10000, '\n');
                    }
                    int patientIndex = choice - 1; // Convert to zero-based index

                    utils::Clear();
                    displayPatientDetails(Db,patientIndex);
                    return ; // Return the index of the selected patient
                }
            }
            if (!found) {
                cout << "No patients found with the phone number containing: " << searchStr << "\n";
            }
            return;
        default:
            return ; // Return 0 if no valid search type is provided
        }
}

void displayPatientDetails(const Patient Db[], int patientIndex) {
    if (patientIndex <= 0 || patientIndex >= MAX_PATIENTS) {// Check if the index is valid
        cout << "Invalid patient index.\n";
        return;
    }
    const Patient& patient = Db[patientIndex];
    cout << "=================== PATIENT DETAILS ==================\n";
    cout << "Name:         " << patient.name << "\n";
    cout << "Age:          " << patient.age << " years\n";
    cout << "gender:       " << patient.gender << "\n";
    cout << "Blood Type:   " << patient.bloodType << "\n";
    cout << "Weight:       " << patient.weight << " kg\n";
    cout << "Phone Number: " << patient.phoneNumber << "\n";
    // Convert timestamp to readable format
    char buffer[80];
    tm* timeinfo = localtime(&patient.timestamp);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    cout << "Registry Date: " << buffer << "\n";
    cout << "=====================================================\n";
    // Display previous conditions if any
    if (!patient.previousConditions.empty()) {
        cout << "Previous Conditions: \n" << patient.previousConditions << "\n";
    } else {
        cout << "No previous conditions recorded.\n";
    }
    cout << "=====================================================\n";
    int choice;
    do {
        cout << "Actions:\n";
        cout <<"1. log conditions for "<<patient.name;
        cout <<"2. clear "<<patient.name<<"'s condition log";
        cout <<"3. edit "<<patient.name<< "'s profile";
        cout <<"4. delete "<<patient.name<<"'s profile from the system";
        cout <<"0. exit and go back to Manage";
        cout <<"Enter your choice:> ";

        while (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }

        switch (choice){
        case 1:
            // log conditions function
            break;
        case 2:
            // clear logs func
            break;
        case 3:
            // edit patient function
            break;
        case 4:
            // delete patient function
            break;
        case 0:
            break;
        default:
            break;
        }

    } while (choice != 0);
    cout << "Press Enter to continue...\n";
    utils::holdc(); // Wait for user input before clearing the screen

}
// menus
void manageMenu(){
    int choice;
    do {
        cout << "=============== MANAGE PATIENT RECORDS ================\n";
        cout << "1. List All Patients\n";
        cout << "2. Search Patient by Name\n";
        cout << "3. search Patient by Phone Number\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter your choice:> ";

        while (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }

        switch (choice) {
            case 1:
                // List all patients
                break;
            case 2:
                // Search patient by name
                findPatients(Db,numpatients,1);
                break;
            case 3:
                // search patient by phone number
                findPatients(Db,numpatients,2);
                break;
            case 0:
                utils::Clear();
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                cout << "press Enter to continue...";
                utils::holdc(); // Wait for user input before clearing the screen
                utils::Clear();
        }
    } while (choice != 0);
};

void mainMenu(){
    int choice;
    do {
        cout << "=============== MAIN MENU ================\n";
        cout << "1. Manage Patient Records\n";
        cout << "2. Register a New Patient\n";
        cout << "3. Manage System Database\n";
        cout << "0. Exit\n";
        cout << "Enter your choice:> ";

        while (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }

        switch (choice) {
            case 1:
                manageMenu(); // Call the manage menu function
                break;
            case 2:
                break;
            case 3:
                break;
            case 0:
                utils::Clear();
                cout << "==========================================\n";
                cout << "Program Closed... Goodbye!\n";
                cout << "==========================================\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                cout << "press Enter to continue...";
                utils::holdc(); // Wait for user input before clearing the screen
                utils::Clear();
        }
    } while (choice != 0);
}; // Forward declaration of main menu function

//  MAIN FUNCTION
int main() {
    utils::Clear();
    int numpatients = 0;
    Patient Db[MAX_PATIENTS];
    cout << "WELCOME TO THE PATIENT MANAGEMENT SYSTEM!\n";
    cout << "==========================================\n";
    mainMenu(); // Call the main menu function
    // utils::Clear(); // Clear the console screen before exiting
    return 0;
}