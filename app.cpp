// PATIENT RECORDS MANAGEMENT SYSTEM
// version 2.0
#include <iostream> // for input/output operations
#include <list> // for list operations
#include <string> // for string operations
#include <algorithm> // for transform function
#include <fstream> // for file operations
#if defined _WIN32 // condition to include the <conio.h> to use getch() if the user is on windows
    #include <conio.h> // for getch()
#endif
#include <cctype> // for toupper()
#include <limits> // for numeric_limits
#include <ctime> // for time usage
#include <vector> // for vector operations
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

// System-wide data
const string FILE_NAME = "patient_db"; // file name for the db
const int MAX_PATIENTS = 100; // Maximum number of patients in the database
int numpatients = 0; // initialize number of patients.
Patient Db[MAX_PATIENTS]; // create the Db to store the patients.

// Utility functions
namespace utils {
    // Function to clear the console screen
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
    //  Function to check if a patient already exists in the database
    bool isPatientExists(const Patient Db[], int numpatients, const Patient& newPatient) {
        for (int i = 0; i < numpatients; ++i) {
            // Case-insensitive name comparison
            string existingNameLower = Db[i].name;
            string newNameLower = newPatient.name;
            transform(existingNameLower.begin(), existingNameLower.end(), existingNameLower.begin(), ::tolower);
            transform(newNameLower.begin(), newNameLower.end(), newNameLower.begin(), ::tolower);
            // Check name and phone number (since these should be unique)
            if (existingNameLower == newNameLower && Db[i].phoneNumber == newPatient.phoneNumber) {
                return true;
            }
        }
        return false;
    }
    void errMsg(const string& msg) {
        cout << "\033[31m" << msg << "\033[0m\n"; // Print error message in red
    }
    void successMsg(const string& msg) {
        cout << "\033[32m" << msg << "\033[0m\n"; // Print success message in green
    }
    void infoMsg(const string& msg) {
        cout << "\033[34m" << msg << "\033[0m\n"; // Print info message in blue
    }
    void saveToDb(const Patient Db[], int numpatients) {
        ofstream outFile(FILE_NAME + ".txt");
        if (!outFile) {
            errMsg("Error: Unable to open file for saving.");
            return;
        }
        try {
            outFile << numpatients << "\n"; // Save the number of patients
            for (int i = 0; i < numpatients; ++i) {
                outFile << Db[i].name << "\n"
                        << Db[i].age << "\n"
                        << Db[i].weight << "\n"
                        << Db[i].gender << "\n"
                        << Db[i].phoneNumber << "\n"
                        << Db[i].bloodType << "\n"
                        << Db[i].previousConditions << "\n"
                        << Db[i].timestamp << "\n";
            }
        } catch (...){
            errMsg("Error: Corrupted database file.");
        }
        outFile.close();
        infoMsg("System: database updated!");
        return;
    }
    void loadDb(Patient Db[], int& numpatients) {
        ifstream inFile(FILE_NAME + ".txt");
        if (!inFile) {
            infoMsg("System: No previous database found. Starting fresh!");
            return;
        }
        try{
            inFile >> numpatients;// Load the number of patients
            inFile.ignore(); // Ignore newline after numpatients
            for (int i = 0; i < numpatients; ++i) {
                getline(inFile, Db[i].name);
                inFile >> Db[i].age >> Db[i].weight >> Db[i].gender;
                inFile.ignore(); // Ignore newline after gender
                getline(inFile, Db[i].phoneNumber);
                getline(inFile, Db[i].bloodType);
                getline(inFile, Db[i].previousConditions);
                inFile >> Db[i].timestamp;
                inFile.ignore(); // Ignore newline after timestamp
            }
        } catch (...){
            errMsg("Error: Corrupted database file.");
        }
        inFile.close();
    }
}
// System Functions
namespace System {
    // Function to list all patients in the database
    void listAllPatients(const Patient Db[], int numpatients) {
        utils::Clear();
        if (numpatients > 0) {
            cout << "=========== ALL PATIENTS (" << numpatients << ") ===========\n";
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
                cout << "==========================================\n";
                cout << "Database is empty.\n";
                cout << "==========================================\n";
            }
            cout << "press Enter to continue..."<<endl;
            utils::holdc(); // Wait for user input before clearing the screen
            utils::Clear(); // Clear the console screen after listing patients
        }

    // log patient condition
    void logpatientcondition(Patient Db[], int patientIndex) {
        utils::Clear();
        cout << "================= LOG PATIENT CONDITION ==================\n";

        if (patientIndex < 0 || patientIndex >= numpatients || Db[patientIndex].name.empty()) {
            utils::errMsg("System Error: Invalid patient index.");
            cout << "Press Enter to continue...";
            utils::holdc(); // Wait for user input before clearing the screen
            utils::Clear();
            return; // Return early if the index is invalid
        }


        utils::Clear(); // Clear the console screen before logging condition
        cout << "==================================================\n";
        cout << "Logging condition for patient #" << patientIndex << ": " << "\n";
        cout << "\033[35mName:          " << Db[patientIndex].name << "\033[0m\n";
        cout << "\033[35mAge:           " << Db[patientIndex].age << " years\033[0m\n";
        cout << "\033[35mWeight:        " << Db[patientIndex].weight << " kg\033[0m\n";
        cout << "\033[35mBlood Type:    " << Db[patientIndex].bloodType << "\033[0m\n";
        cout << "--------------------------------------------------\n";
        cout << Db[patientIndex].name << "'s previous conditions: \n";
        cout << "\033[33m"+(Db[patientIndex].previousConditions.empty() ? "None" : Db[patientIndex].previousConditions)
            << "\033[0m\n"; // Display previous conditions if any
        cout << "==================================================\n";

        string condition;
        string newConditions = "";//temporary variable to hold new conditions
        char choice;
        do{
            cout << "Enter the condition to log for " << Db[patientIndex].name << ": ";
            cin.ignore(); // Clear the input buffer before getline
            getline(cin, condition);
            while (condition.empty()) {
                utils::errMsg("Condition cannot be empty. Please enter a valid condition.");
                cin.ignore(); // Clear the input buffer before getline
                getline(cin, condition);
            }
            // Get the current date and time
            time_t now = time(nullptr);
            char buffer[80];
            tm* timeinfo = localtime(&now);
            strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

            // Append the condition with the log date
            string conditionWithDate = condition + " (Logged on: " + buffer + ")";
            newConditions += (newConditions.empty() ? std::string("") : std::string("\n")) + ">> " + conditionWithDate;
            cout << "---------------------------------------------------\n";
            utils::successMsg("log added successfully.");
            cout << "---------------------------------------------------\n";
            cout << "Do you want to add another condition? (Y/N): ";
            cin >> choice;
            choice = toupper(choice);
            while (choice != 'Y' && choice != 'N') {
                utils::errMsg("Invalid input. Please enter Y or N: ");
                cin >> choice;
                choice = toupper(choice); // Convert to uppercase for consistency
            }
        } while (choice == 'Y');

        cout << "Do you want to save the logged conditions? (Y/N): ";
        cin >> choice;
        choice = toupper(choice);
        while (choice != 'Y' && choice != 'N') {
            utils::errMsg("Invalid input. Please enter Y or N: ");
            cin >> choice;
            choice = toupper(choice); // Convert to uppercase for consistency
        }
        if (choice == 'Y') {
            utils::Clear(); // Clear the console screen after saving conditions
            Db[patientIndex].previousConditions += (Db[patientIndex].previousConditions.empty() ? "" : "\n") + newConditions;
            utils::saveToDb(Db,numpatients);//update Database
            cout << "==================================================\n";
            utils::successMsg("Conditions logged successfully for " + Db[patientIndex].name);
            cout << "--------------------------------------------------\n";
            cout << "Updated conditions for " << Db[patientIndex].name << ": \n";
            cout << "\033[33m" + Db[patientIndex].previousConditions << "\033[0m\n"; // Display updated conditions
            cout << "==================================================\n";
        } else {
            utils::Clear(); // Clear the console screen after canceling
            cout << "==================================================\n";
            cout << "Logging canceled. No changes were made.\n";
            cout << "==================================================\n";
        }

        cout << "press Enter to continue...";
        utils::holdc(); // Wait for user input before clearing the screen
        utils::Clear();
    }

    // Function to clear logs for a specific patient
    void clearLogs(Patient Db[], int& patientIndex) {
        utils::Clear(); // Clear the console screen before clearing logs
        if (patientIndex < 0 || patientIndex >= numpatients || Db[patientIndex].name.empty()) {
            utils::errMsg("System Error: Invalid patient index.");
            cout << "Press Enter to continue...";
            utils::holdc(); // Wait for user input before clearing the screen
            utils::Clear();
            return; // Return early if the index is invalid
        }
        cout << "============== CLEAR LOGS FOR " << Db[patientIndex].name << " ====================\n";
        cout << "Are you sure you want to clear all previous conditions for " << Db[patientIndex].name << "? (Y/N): ";
        char confirmClear;
        cin >> confirmClear;
        confirmClear = toupper(confirmClear); // Convert to uppercase for consistency
        if (confirmClear != 'Y') {
            utils::Clear(); // Clear the console screen before displaying the message
            cout << "==================================================\n";
            utils::infoMsg("Clearing logs canceled. No changes were made to the patient's record.");
            cout << "==================================================\n";
            cout << "Press Enter to continue...";
            utils::holdc(); // Wait for user input before clearing the screen
            utils::Clear(); // Clear the console screen after displaying the message
            return; // Return early if the user cancels
        }
        Db[patientIndex].previousConditions.clear(); // Clear the previous conditions
        utils::Clear(); // Clear the console screen after clearing logs
        utils::saveToDb(Db,numpatients); // update Database
        cout << "==================================================\n";
        utils::successMsg("All previous conditions for " + Db[patientIndex].name + " have been cleared successfully.");
        cout << "==================================================\n";
        cout << "Press Enter to continue...";
        utils::holdc(); // Wait for user input before clearing the screen
        utils::Clear(); // Clear the console screen after clearing logs
    }

    //  Function to delete a patient record from the database
    void deletePatient(Patient Db[], int& numpatients, int patientIndex) {
        utils::Clear(); // Clear the console screen before deleting a patient
        if (patientIndex < 0 || patientIndex >= numpatients) {
            cout << "Invalid patient index.\n";
            cout << "Press Enter to continue...";
            utils::holdc(); // Wait for user input before clearing the screen
            utils::Clear();
            return; // Return early if the index is invalid
        }
        cout << "================ DELETE PATIENT ===================\n";
        cout << "Are you sure you want to delete the record of " << Db[patientIndex].name << "? (Y/N): ";
        // cout << "This action cannot be undone.\n";
        char confirmDelete;
        cin >> confirmDelete;
        confirmDelete = toupper(confirmDelete); // Convert to uppercase for consistency
        if (confirmDelete != 'Y') {
            utils::Clear(); // Clear the console screen before displaying the message
            cout << "==================================================\n";
            utils::infoMsg("Deletion canceled. No changes were made to the database.");
            cout << "==================================================\n";
            cout << "Press Enter to continue...";
            utils::holdc(); // Wait for user input before clearing the screen
            utils::Clear(); // Clear the console screen after displaying the message
            return; // Return early if the user cancels
        }
        // Shift remaining patients down in the array
        for (int i = patientIndex; i < numpatients - 1; ++i) {
            Db[i] = Db[i + 1];
        }
        --numpatients; // Decrease the number of patients
        patientIndex = -1; // Reset patientIndex to -1 after deletion // Invalidate the patient index
        utils::Clear(); // Clear the console screen after deleting a patient
        utils::saveToDb(Db,numpatients);
        cout << "==================================================\n";
        utils::successMsg("Patient Record deleted successfully.");
        cout << "==================================================\n";
        cout << "Press Enter to continue...";
        utils::holdc(); // Wait for user input before clearing the screen
        utils::Clear(); // Clear the console screen after deleting a patient
    }

    // Function to add a new patient to the database
    void editPatient(Patient Db[], int& patientIndex) {
        utils::Clear(); // Clear the console screen before editing
        const Patient& patient = Db[patientIndex];
        int choice;
        do {
            cout << "================== EDIT PATIENT RECORD =================\n";
            cout << "=================== CURRENT DETAILS ==================\n";
            cout << "1. Name:         " << patient.name << "\n";
            cout << "2. Age:          " << patient.age << " years\n";
            cout << "3. Gender:       " << patient.gender << "\n";
            cout << "4. Blood Type:   " << patient.bloodType << "\n";
            cout << "5. Weight:       " << patient.weight << " kg\n";
            cout << "6. Phone Number: " << patient.phoneNumber << "\n";
            cout << "=====================================================\n";    
            utils::infoMsg("Select the item you want to edit (1-6), or enter 0 to cancel:> ");

            while (!(cin >> choice) || choice < 0 || choice > 6) {
                utils::errMsg("Invalid input. Please enter a number between 0 and 6: ");
                cin.clear();
                cin.ignore(10000, '\n');
            }

            if (choice == 0) {
                utils::Clear();
                return; // Cancel editing
            }

            switch (choice) {
                case 1: {
                    string new_name;
                    cout << "----------------------------------------------\n";
                    cout << "Editing Name:_\n";
                    utils::infoMsg("Current Name: " + patient.name);
                    cout << "Enter new patient name: ";
                    cin.ignore(); // Clear the input buffer
                    getline(cin, new_name);
                    Db[patientIndex].name = new_name;
                    break;
                }
                case 2: {
                    int new_age;
                    cout << "----------------------------------------------\n";
                    cout << "Editing Age:_\n";
                    utils::infoMsg("Current Age: " + to_string(patient.age) + " years");
                    cout << "Enter new age: ";
                    while (!(cin >> new_age) || new_age < 0) {
                        utils::errMsg("Invalid input. Please enter a positive number: ");
                        cin.clear();
                        cin.ignore(10000, '\n');
                    }
                    Db[patientIndex].age = new_age;
                    break;
                }
                case 3: {
                    char newGender;
                    cout << "----------------------------------------------\n";
                    cout << "Editing Gender:_\n";
                    utils::infoMsg("Current Gender: " + patient.gender);
                    cout << "Enter new gender (M/F): ";
                    cin >> newGender;
                    newGender = toupper(newGender);
                    while (newGender != 'M' && newGender != 'F') {
                        utils::errMsg("Invalid input. Please enter M or F: ");
                        cin >> newGender;
                        newGender = toupper(newGender);
                    }
                    Db[patientIndex].gender = newGender;
                    break;
                }
                case 4: {
                    string new_bloodType;
                    cout << "----------------------------------------------\n";
                    cout << "Editing Blood Type:_\n";
                    utils::infoMsg("Current Blood Type: " + patient.bloodType);
                    cout << "Enter new blood type (A+, A-, B+, B-, AB+, AB-, O+, O-): ";
                    cin.ignore(); // Clear the input buffer
                    getline(cin, new_bloodType);
                    for (char &c : new_bloodType) c = toupper(c); // Convert to uppercase
                    while (!utils::isValidBloodType(new_bloodType)) {
                        utils::errMsg("Invalid blood type. Please enter a valid type: ");
                        getline(cin, new_bloodType);
                        for (char &c : new_bloodType) c = toupper(c); // Convert to uppercase
                    }
                    Db[patientIndex].bloodType = new_bloodType;
                    break;
                }
                case 5: {
                    int new_weight;
                    cout << "----------------------------------------------\n";
                    cout << "Editing Weight:_\n";
                    utils::infoMsg("Current Weight: " + to_string(patient.weight) + " kg");
                    cout << "Enter new weight (kg): ";
                    while (!(cin >> new_weight) || new_weight < 0) {
                        utils::errMsg("Invalid input. Please enter a positive number: ");
                        cin.clear();
                        cin.ignore(10000, '\n');
                    }
                    Db[patientIndex].weight = new_weight;
                    break;
                }
                case 6: {
                    string new_phoneNumber;
                    cout << "----------------------------------------------\n";
                    cout << "Editing Phone Number:_\n";
                    utils::infoMsg("Current Phone Number: " + patient.phoneNumber);
                    cout << "Enter new phone number: ";
                    cin.ignore(); // Clear the input buffer
                    getline(cin, new_phoneNumber);
                    while (!utils::isValidPhoneNumber(new_phoneNumber)) {
                        utils::errMsg("Invalid phone number format. Please enter a valid phone number: ");
                        getline(cin, new_phoneNumber);
                    }
                    Db[patientIndex].phoneNumber = new_phoneNumber;
                    break;
                }
                default:
                    break;
            }
            utils::Clear(); // Clear the console screen after editing
            utils::saveToDb(Db,numpatients); // update Database
            cout << "===================================================\n";
            utils::successMsg(Db[patientIndex].name + "'s record was updated successfully.");
            cout << "===================================================\n";
            // cout << "Updated Patient Details:\n";
            // cout << "Name:         " << Db[patientIndex].name << "\n";
            // cout << "Age:          " << Db[patientIndex].age << " years\n";
            // cout << "Gender:       " << Db[patientIndex].gender << "\n";
            // cout << "Blood Type:   " << Db[patientIndex].bloodType << "\n";
            // cout << "Weight:       " << Db[patientIndex].weight << " kg\n";
            // cout << "Phone Number: " << Db[patientIndex].phoneNumber << "\n";
            // cout << "===================================================\n";
            cout << "Press Enter to continue...";
            utils::holdc(); // Wait for user input before clearing the screen
            utils::Clear();
        } while (choice != 0);
    }

    // Function to display patient details and manage actions
    void displayPatientDetails(Patient Db[], int& patientIndex) {
        utils::Clear(); // Clear the console screen before displaying patient details
        if (patientIndex < 0 || patientIndex >= numpatients) {// Check if the index is valid
            utils::errMsg("System Error: Invalid patient index."); 
            cout << "Press Enter to continue...";
            utils::holdc(); // Wait for user input before clearing the screen
            return;
        }
        const Patient& patient = Db[patientIndex];

        int choice;
        do {
            cout << "=================== PATIENT DETAILS ==================\n";
            cout << "\033[35mName:         " << patient.name << "\033[0m\n";
            cout << "\033[35mAge:          " << patient.age << " years\033[0m\n";
            cout << "\033[35mgender:       " << patient.gender << "\033[0m\n";
            cout << "\033[35mBlood Type:   " << patient.bloodType << "\033[0m\n";
            cout << "\033[35mWeight:       " << patient.weight << " kg\033[0m\n";
            cout << "\033[35mPhone Number: " << patient.phoneNumber << "\033[0m\n";
            // Convert timestamp to readable format
            char buffer[80];
            tm* timeinfo = localtime(&patient.timestamp);
            strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
            cout << "\033[35mRegistry Date: " << buffer << "\033[0m\n";
            cout << "=====================================================\n";
            // Display previous conditions if any
            if (!patient.previousConditions.empty()) {
                cout << "\033[33mPrevious Conditions: \n" << patient.previousConditions << "\033[0m\n";
            } else {
                cout << "\033[33mNo previous conditions recorded.\033[0m\n";
            }
            cout << "=====================================================\n";
            cout << "Actions:\n";
            cout <<"1. log conditions for "<<patient.name <<"\n";
            cout <<"2. Clear "<<patient.name<<"'s condition log"<<"\n";
            cout <<"3. Edit "<<patient.name<< "'s profile"<<"\n";
            cout <<"4. Delete "<<patient.name<<"'s profile from the system"<<"\n";
            cout <<"0. Back to Manage menu"<< "\n";
            cout <<"Enter your choice:> ";

            while (!(cin >> choice)) {
                utils::errMsg("Invalid input. Please enter a number: ");
                cin.clear();
                cin.ignore(10000, '\n');
            }

            switch (choice){
            case 1:
                // log conditions function
                logpatientcondition(Db, patientIndex);
                break;
            case 2:
                // clear logs func
                clearLogs(Db, patientIndex);
                break;
            case 3:
                // edit patient
                editPatient(Db,patientIndex);
                break;
            case 4:
                // delete patient function
                deletePatient(Db, numpatients, patientIndex);
                return;
            case 0:
                utils::Clear(); // Clear the console screen before returning to the previous menu
                break;
            default:
                utils::errMsg("Invalid input. Please enter a number: ");
                break;
            }

        } while (choice != 0);
        // cout << "Press Enter to continue...\n";
        // utils::holdc(); // Wait for user input before clearing the screen
        // utils::Clear(); // Clear the console screen after displaying patient details
        return; // Return to the previous menu
    }

    // Function to find patients by name or phone number
    void findPatients(Patient Db[], int numpatients, int searchType) {
        while (true) {
            utils::Clear(); // Clear the console screen before searching
            cout << "=============== SEARCH PATIENTS ================\n";
            if (numpatients == 0) {
                utils::infoMsg("Database is empty. Cannot search.");
                cout << "==================================================\n";
                cout << "Press Enter to continue...";
                utils::holdc(); // Wait for user input before clearing the screen
                utils::Clear();
                return; // Return early if no patients are present
            }

            string searchStr = ""; // Initialize searchStr to an empty string
            string normalizedSearch; // For phone number search, we will normalize the input
            vector<int> matchIndices; // Store the actual indices of matching patients
            int choice;
            int patientIndex;
            switch (searchType) {
                case 1: // Search by name
                    while (true) { // Loop to allow retrying the search
                        cout << "Enter patient name to search: ";
                        cin.ignore(); // Clear the input buffer properly
                        getline(cin, searchStr);
                        if (searchStr.empty()) {
                            utils::errMsg("Search string cannot be empty. Please enter a valid name.");
                            cout << "Press Enter to continue...\n";
                            utils::holdc(); // Wait for user input before clearing the screen
                            utils::Clear(); // Clear the console screen after displaying the message
                            cout << "=============== SEARCH PATIENTS ================\n";
                            continue; // Continue to the next iteration of the loop
                        }
                        // Convert searchStr to lowercase for case-insensitive comparison
                        for (char &c : searchStr) c = tolower(c);
                        utils::Clear(); // Clear the console screen before displaying results
                        cout << "================== SEARCH RESULTS ==================\n";
                        utils::infoMsg("Searching for patients with name containing: " + searchStr);
                        cout << "-----------------------------------------------------\n";
                        // Loop through the database to find matching patients
                        for (int i = 0; i < numpatients; ++i) {
                            string patientNameLower = Db[i].name;
                            // Convert patient name to lowercase for case-insensitive comparison
                            for (char &c : patientNameLower) c = tolower(c);
                            if (patientNameLower.find(searchStr) != string::npos) {
                                matchIndices.push_back(i); // Store the actual index of the match
                                // Display the matching patient details
                                cout << "MATCH #" << matchIndices.size() << " ";
                                cout << "\033[35mName: " << Db[i].name << "\033[0m\t";// Use magenta color for name
                                cout << "Age: " << Db[i].age << " years\t";
                                cout << "Gender: " << Db[i].gender << "\t";
                                cout << "Blood Type: " << Db[i].bloodType << "\t";
                                cout << "Phone: " << Db[i].phoneNumber << "   \n";
                                cout << "--------------------------------------------------\n";
                            }
                        }

                        if (matchIndices.empty()) {
                            cout << "==================================================\n";
                            utils::infoMsg("No patients found with the name containing: " + searchStr);
                            cout << "==================================================\n";
                            cout << "Press Enter to retry or type '0' to cancel: ";
                            string retryInput;
                            getline(cin, retryInput);
                            if (retryInput == "0") {
                                // utils::infoMsg("Search canceled. Returning to the previous menu...");
                                utils::Clear();
                                return; // Exit the function if the user cancels
                            }
                            utils::Clear();
                            cout << "=============== SEARCH PATIENTS ================\n";
                            continue; // Retry the search
                    }

                    // Prompt the user to select a patient from the search results
                    cout << "==================================================\n";
                    utils::infoMsg("Select Patient from the search results...");
                    utils::infoMsg("Enter the match number 1 to " + to_string(matchIndices.size()) + " to view details.");
                    utils::infoMsg("You can also enter '0' to cancel and return to the previous menu.");
                    cout << "Enter your choice:> ";

                    while (!(cin >> choice) || choice < 0 || choice > matchIndices.size()) {
                        utils::errMsg("Invalid input. Please enter a number between 1 and " + to_string(matchIndices.size()) + ": ");
                        cin.clear();
                        cin.ignore(10000, '\n');
                    }

                    if (choice == 0) {
                        utils::Clear();
                        return; // Return to the previous menu
                    }

                    patientIndex = matchIndices[choice - 1]; // Get the actual index of the selected patient
                    displayPatientDetails(Db, patientIndex); // Pass the actual index to the display function
                    return; // Return early after displaying patient details

                case 2: // Search by phone number
                    while (true) { // Loop to allow retrying the search
                        cout << "Enter phone number to search: ";
                        cin.ignore();
                        getline(cin, searchStr);
                        // Remove any non-digit characters for more flexible searching
                        for (char c : searchStr) {
                            if (isdigit(c)) {
                                normalizedSearch += c;
                            }
                        }
                        if (normalizedSearch.empty()) {
                            utils::errMsg("Invalid phone number. Please enter a valid phone number.");
                            cout << "Press Enter to continue...\n";
                            utils::holdc(); // Wait for user input before clearing the screen
                            utils::Clear(); // Clear the console screen after displaying the message
                            cout << "=============== SEARCH PATIENTS ================\n";
                            continue;
                        }
                        utils::Clear(); // Clear the console screen before displaying results
                        cout << "================== SEARCH RESULTS ==================\n";
                        utils::infoMsg("Searching for patients with phone number containing: " + searchStr);
                        cout << "====================================================\n";
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
                                matchIndices.push_back(i); // Store the actual index of the match
                                // Display the matching patient details
                                cout << "MATCH #" << matchIndices.size() << " ";
                                cout << "Name: " << Db[i].name << "\t";
                                cout << "Age: " << Db[i].age << " years\t";
                                cout << "Gender: " << Db[i].gender << "\t";
                                cout << "Blood Type: " << Db[i].bloodType << "\t";
                                cout << "\033[35mPhone: " << Db[i].phoneNumber << "\033[0m\n";// Use magenta color for phone number
                                cout << "--------------------------------------------------\n";
                            }
                        }

                        if (matchIndices.empty()) {
                            cout << "==================================================\n";
                            utils::infoMsg("No patients found with the name containing: " + searchStr);
                            cout << "==================================================\n";
                            cout << "Press Enter to retry or type '0' to cancel: ";
                            string retryInput;
                            getline(cin, retryInput);
                            if (retryInput == "0") {
                                // utils::infoMsg("Search canceled. Returning to the previous menu...");
                                utils::Clear();
                                return; // Exit the function if the user cancels
                            }
                            utils::Clear();
                            cout << "=============== SEARCH PATIENTS ================\n";
                            continue; // Retry the search
                        }
                    }
                    // Prompt the user to select a patient from the search results
                    cout << "==================================================\n";
                    utils::infoMsg("Select Patient from the search results...");
                    utils::infoMsg("Enter the match number 1 to " + to_string(matchIndices.size()) + " to view details.");
                    utils::infoMsg("You can also enter '0' to cancel and return to the previous menu.");
                    cout << "Enter your choice:> ";

                    while (!(cin >> choice) || choice < 0 || choice > matchIndices.size()) {
                        utils::errMsg("Invalid input. Please enter a number between 1 and " + to_string(matchIndices.size()) + ": ");
                        cin.clear();
                        cin.ignore(10000, '\n');
                    }

                    if (choice == 0) {
                        utils::Clear();
                        return; // Return to the previous menu
                    }

                    patientIndex = matchIndices[choice - 1]; // Get the actual index of the selected patient
                    displayPatientDetails(Db, patientIndex); // Pass the actual index to the display function
                    return;

                default:
                    utils::errMsg("System Error: Invalid search type selected.");
                    cout << "Press Enter to continue...\n";
                    utils::holdc(); // Wait for user input before clearing the screen
                    utils::Clear(); // Clear the console screen after displaying results
                    return;
            }
            }
        }
    }

    //  Function to add a new patient to the database
    void addPatient(Patient Db[], int& numpatients) {
        while (true){
            utils::Clear();
            if (numpatients >= MAX_PATIENTS) {
                cout << "==================================================\n";
                utils::errMsg("Database is full! Cannot add more patients.");
                cout << "==================================================\n";
                cout << "press Enter to continue...";
                utils::holdc(); // Wait for user input before clearing the screen
                utils::Clear();
                return;
            }

            Patient newPatient;

            cout << "=============== REGISTER NEW PATIENT ================\n";
            utils::infoMsg("Enter '0' at any point to cancel and go back to the main menu.");
            cout << "-----------------------------------------------------\n";
            cout << "please fill in the patient details below:\n";
            // Name input
            while (true) {
                cout << "Enter Patient name: ";
                cin.ignore(); // Clear the input buffer
                getline(cin, newPatient.name);
                if (newPatient.name == "0") {
                    utils::Clear(); 
                    return; // Cancel registration
                }
                if (!newPatient.name.empty()) break; // Valid input
                utils::errMsg("Name cannot be empty. Please try again.");
            }

            // Age input
            while (true) {
                cout << "Enter Patient age: ";
                if (!(cin >> newPatient.age) || newPatient.age < 0) {
                    cin.clear();
                    cin.ignore(10000, '\n'); // Clear the input buffer
                    utils::errMsg("Invalid age. Please enter a positive number or '0' to cancel.");
                    continue;
                }
                if (newPatient.age == 0){
                    utils::Clear(); 
                    return; // Cancel registration
                }
                break; // Valid input
            }

            // Weight input
            while (true) {
                cout << "Enter patient weight (kg): ";
                if (!(cin >> newPatient.weight) || newPatient.weight < 0) {
                    cin.clear();
                    cin.ignore(10000, '\n'); // Clear the input buffer
                    utils::errMsg("Invalid weight. Please enter a positive number or '0' to cancel.");
                    continue;
                }
                if (newPatient.weight == 0) {
                    utils::Clear(); 
                    return; // Cancel registration
                }
                break; // Valid input
            }
            // Gender input
            while (true) {
                cout << "Enter gender (M/F): ";
                cin >> newPatient.gender;
                newPatient.gender = toupper(newPatient.gender);
                if (newPatient.gender == '0') {
                    utils::Clear(); 
                    return; // Cancel registration
                }
                if (newPatient.gender == 'M' || newPatient.gender == 'F') break; // Valid input
                utils::errMsg("Invalid gender. Please enter M or F.");
            }

            // Blood Type input
            while (true) {
                cout << "Enter blood type (A+, A-, B+, B-, AB+, AB-, O+, O-): ";
                cin >> newPatient.bloodType;
                if (newPatient.bloodType == "0") {
                    utils::Clear(); 
                    return; // Cancel registration
                }
                for (char &c : newPatient.bloodType) c = toupper(c); // Convert to uppercase
                if (utils::isValidBloodType(newPatient.bloodType)) break; // Valid input
                // utils::errMsg("Invalid blood type. Please enter a valid type (A+, A-, B+, B-, AB+, AB-, O+, O-).");
                utils::errMsg("Invalid blood type. Please try again.");
            }

            // Phone Number input
            while (true) {
                cout << "Enter phone number: ";
                cin.ignore(); // Clear the input buffer
                getline(cin, newPatient.phoneNumber);
                if (newPatient.phoneNumber == "0") {
                    utils::Clear(); 
                    return; // Cancel registration
                }
                if (utils::isValidPhoneNumber(newPatient.phoneNumber)) break; // Valid input
                // utils::errMsg("Invalid phone number format. Please enter a valid phone number.");
                utils::errMsg("Invalid phone number. Please try again.");
            }

            // Initialize previous health conditions as empty
            newPatient.previousConditions = ""; // Initialize previous conditions as empty

            // Set the registration timestamp
            newPatient.timestamp = time(nullptr);

            // Check for duplicate before adding
            if (utils::isPatientExists(Db, numpatients, newPatient)) {
                utils::Clear();
                cout << "==================================================\n";
                utils::errMsg("Duplicate entry detected.");
                cout << "Patient already exists in the database!\n";
                cout << "Please check the name and phone number.\n";
                cout << "==================================================\n";
                cout << "press Enter to continue...";
                utils::holdc();
                utils::Clear();
                continue; //  Continue the loop to allow re-entry of patient details
            }
            utils::Clear(); // Clear the console screen after adding patient
            // Add to database
            Db[numpatients++] = newPatient;
            utils::saveToDb(Db,numpatients); // update Database

            cout << "==================================================\n";
            utils::successMsg("New patient: '" + newPatient.name + "' Registered successfully.");
            cout << "==================================================\n";
            cout << "press Enter to continue..."<<endl;
            utils::holdc(); // Wait for user input before clearing the screen
            utils::Clear();
            break; // Exit the loop after successful addition
        }
    }

    //  Function to clear the entire database
    void clearDatabase(Patient Db[], int& numpatients) {
        utils::Clear();
        cout << "================= CLEAR DATABASE =====================\n";
        if (numpatients == 0) {
            utils::infoMsg("Database is already empty...");
        } else {
            cout << "This action will clear all patient records from the database.\n";
            cout << "-----------------------------------------------------\n";
            cout << "Current number of patients: " << numpatients << "\n";
            cout << "-------------------------------------------------\n";
            utils::errMsg("Warning: This action cannot be undone.");
            cout << "Are you sure you want to clear the database? (Y/N): ";
            char confirmClear;
            cin >> confirmClear;
            utils::Clear(); // clear screen
            if (toupper(confirmClear) == 'Y') {
                for (int i = 0; i < numpatients; ++i) {
                    Db[i] = Patient(); // Reset each patient record
                }
                numpatients = 0; // Reset the number of patients
                utils::saveToDb(Db,numpatients); // update Database
                cout << "==================================================\n";
                utils::successMsg("Database cleared successfully.");
                cout << numpatients << " patients removed from the database.\n";
            } else {
        cout << "==================================================\n";
                utils::infoMsg("Database clearing canceled.");
                cout << "No changes were made to the database.\n";
            }
        }
        cout << "==================================================\n";
        cout << "press Enter to continue...";
        utils::holdc(); // Wait for user input before clearing the screen
        utils::Clear();
    }

    // Function to display system information
    void info(){
        utils::Clear(); // Clear the console screen before displaying info
        cout << "=============== ABOUT THE SYSTEM ================\n";
        cout << "This is a Patient Records Management System designed to help\n";
        cout << "healthcare professionals manage patient records efficiently.\n";
        cout << "Features include:\n";
        cout << "- Registering new patients\n";
        cout << "- Searching for patients by name or phone number\n";
        cout << "- Logging patient conditions\n";
        cout << "- Editing patient profiles\n";
        cout << "- Deleting patient records\n";
        cout << "- Viewing system statistics and dashboard\n";
        cout << "For more information, please refer to the documentation.\n";
        cout << "==================================================\n";
        cout << "Developed by: \n";
        cout << "- Brook Ayneabeba\n";
        cout << "- Ihsan Shafi\n";
        cout << "- Bisrat Aklilu\n";
        cout << "- Abenezer Asmare\n";
        cout << "- Biniyam Abera\n";
        cout << "- Soliyana Getachew\n";
        cout << "==================================================\n";
        cout << "Patient Records Management System.\n";
        cout << "Version: 1.0.0\n"; // Version of the system
        cout << "Written in C++14.\n";
        cout << "==================================================\n";
        cout << "Press Enter to return to the main menu...\n";
        utils::holdc(); // Wait for user input before clearing the screen
        utils::Clear(); // Clear the console screen after displaying info
    }
}
// MENUS
namespace Menu {
    void manageMenu(){
        utils::Clear(); // Clear the console screen before displaying the manage menu
        int choice;
        do {
            cout << "=============== MANAGE PATIENT RECORDS ================\n";
            cout << "1. List All Patients\n";
            cout << "2. Search Patient by Name\n";
            cout << "3. search Patient by Phone Number\n";
            cout << "0. Back to Main Menu\n";
            cout << "Enter your choice:> ";
    
            while (!(cin >> choice)) {
                utils::errMsg("Invalid input. Please enter a number: ");
                cin.clear();
                cin.ignore(10000, '\n');
            }
    
            switch (choice) {
                case 1:
                    // List all patients
                    System::listAllPatients(Db, numpatients); // Call the list patients function
                    break;
                case 2:
                    // Search patient by name
                    System::findPatients(Db,numpatients,1); // Call the find patients function
                    break;
                case 3:
                    // search patient by phone number
                    System::findPatients(Db,numpatients,2);
                    break;
                case 0:
                    utils::Clear();
                    break;
                default:
                    utils::errMsg("Invalid choice. Please try again.");
                    cout << "press Enter to continue...";
                    utils::holdc(); // Wait for user input before clearing the screen
                    utils::Clear();
            }
        } while (choice != 0);
    };
    void systemMenu() {
        utils::Clear(); // Clear the console screen before displaying the system menu
        int choice;
        do {
            cout << "=============== SYSTEM DATABASE MANAGEMENT ================\n";
            cout << "======================== DASHBOARD ========================\n";
            cout << "\033[35mMaximum Capacity: " << MAX_PATIENTS << "\033[0m\n";
            cout << "\033[35mAvailable Slots: " << (MAX_PATIENTS - numpatients) << "\033[0m\n";
            cout << "\033[35mTotal Patients Registered: " << numpatients << "\033[0m\n";
            int maleCount = 0, femaleCount = 0;
            for (int i = 0; i < numpatients; ++i) {
                if (Db[i].gender == 'M') ++maleCount;
                else if (Db[i].gender == 'F') ++femaleCount;
            }
            cout << "\033[35mNumber of Male Patients: " << maleCount << "\033[0m\n";
            cout << "\033[35mNumber of Female Patients: " << femaleCount << "\033[0m\n";
            cout << "============================================================\n";
            // if (numpatients > 0) {
            //     cout << "Average Age of Patients: ";
            //     int totalAge = 0;
            //     for (int i = 0; i < numpatients; ++i) {
            //         totalAge += Db[i].age;
            //         }
            //         cout << (totalAge / numpatients) << " years\n";
            //         cout << "==========================================================\n";
            //     }
            if (numpatients > 0) {
                cout << "Latest Patient Registered:\n";
                cout << "Name: " << Db[numpatients - 1].name << " ";
                cout << "("<<Db[numpatients - 1].age <<","<<Db[numpatients - 1].gender<<","<< Db[numpatients - 1].gender << ")";
                cout << " (";
                char buffer[80]; 
                tm* timeinfo = localtime(&Db[numpatients - 1].timestamp);
                strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
                cout << buffer << ")\n";
                cout << "===========================================================\n";
            } else {
                cout << "No patients registered yet.\n";
                cout << "============================================================\n";
            }
            // Display available actions
            cout<<"Available Actions:\n";
            cout << "1. Clear Database(delete all records)\n";
            cout << "2. Change Maximum Patient Capacity\n";
            cout << "0. Back to Main Menu\n";
            cout << "Enter your choice:> ";
    
            while (!(cin >> choice)) {
                cout << "Invalid input. Please enter a number: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
    
            switch (choice) {
                case 1:
                    // Clear database
                    System::clearDatabase(Db, numpatients); // Call the clear database function
                    break;
                case 2:
                    utils::Clear();
                    cout << "==========================================================\n";
                    utils::errMsg("Error: This feature is not implmented yet!");
                    cout << "==========================================================\n";
                    cout << "press Enter to continue...";
                    utils::holdc(); // Wait for user input before clearing the screen
                    utils::Clear();
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
            cout << "4. Info\n";
            cout << "0. Exit\n";
            cout << "Enter your choice:> ";
    
            while (!(cin >> choice)) {
                utils::errMsg("Invalid input. Please enter a number: ");
                cin.clear();
                cin.ignore(10000, '\n');
            }
    
            switch (choice) {
                case 1:
                    manageMenu(); // Call the manage menu function
                    break;
                case 2:
                    System::addPatient(Db, numpatients); // Call the add patient function
                    break;
                case 3:
                    systemMenu(); // Call the system menu function
                    break;
                case 4:
                    System::info(); // Call the info function to display system information
                    break;
                case 0:
                    utils::Clear();
                    cout << "==========================================\n";
                    utils::infoMsg("Program Closed... Goodbye!");
                    cout << "==========================================\n";
                    break;
                default:
                    utils::errMsg("Invalid choice. Please try again.");
                    cout << "press Enter to continue...";
                    utils::holdc(); // Wait for user input before clearing the screen
                    utils::Clear();
            }
        } while (choice != 0);
    
    };
}

//  MAIN FUNCTION
int main() {
    utils::Clear();
    utils::infoMsg("WELCOME TO THE PATIENT RECORDS MANAGEMENT SYSTEM!");
    utils::loadDb(Db, numpatients); //load the database to memory
    Menu::mainMenu(); // Call the main menu function
    return 0;
}
