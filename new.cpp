// PATIENT RECORDS MANAGEMENT SYSTEM(this time using Vector as the database to hold patients)
// version 2.0
// - Patient registration, search, and editing
// - Logging and clearing patient progress
// - Dashboard for system statistics
// - Persistent database storage
#include <iostream> // for input/output operations
#include <string> // for string operations
#include <algorithm> // for transform function
#include <fstream> // for file operations
#include <cctype> // for toupper()
#include <limits> // for numeric_limits
#include <ctime> // for time usage
#include <vector> // for vector operations
#if defined _WIN32 // condition to include the <conio.h> to use getch() if the user is on windows
    #include <conio.h> // for getch()
#endif
using namespace std;

// Patient structure to store patient details
struct Patient {
    string name;         // Patient's name
    int age;            // Patient's age
    float weight;         // Patient's weight in kilograms
    char gender;        // Gender: 'M' for Male, 'F' for Female
    string phoneNumber;   // Contact phone number
    string bloodType;       // Blood type (e.g., A+, O-)
    string medicalHistory;      // Medical history and previous diagnoses
    string progressLog;     // List of previous conditions
    time_t timestamp;       // Registration timestamp
};

// System-wide data
const string FILE_NAME = "db"; // file name for the db
vector<Patient> Db;  // create the Db to store the patients.

// Utility functions
namespace utils {
    // Clears the console screen (platform-specific)
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
    // Pauses execution until a key is pressed (platform-specific)
    void holdc() {
        #if defined _WIN32
            getch(); // Wait for a key press in Windows
        #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.get();
        #endif
    }
    // Validates phone number format
    bool isValidPhoneNumber(const string& phone) {
        if (phone.empty()) return false;
        if (!(phone.length() == 10)) return false;
        for (char c : phone) {
            if (!isdigit(c)) {
                return false;
            }
        }
        return true;
    }
    // Validates blood type
    bool isValidBloodType(const string& bloodType) {
        const string validTypes[] = {"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"};
        for (const auto& type : validTypes) {
            if (bloodType == type) return true;
        }
        return false;
    }
    //  Function to check if a patient already exists in the database
    bool isPatientExists(const vector<Patient>& Db, const Patient& newPatient) {
        for (const auto& patient : Db) {
            // Case-insensitive name comparison
            string existingNameLower = patient.name;
            string newNameLower = newPatient.name;
            transform(existingNameLower.begin(), existingNameLower.end(), existingNameLower.begin(), ::tolower);
            transform(newNameLower.begin(), newNameLower.end(), newNameLower.begin(), ::tolower);
            // Check name and phone number (since these should be unique)
            if (existingNameLower == newNameLower && patient.phoneNumber == newPatient.phoneNumber) {
                return true;
            }
        }
        return false;
    }
    // error message in red
    void errMsg(const string& msg) {
        cout << "\033[31m" << msg << "\033[0m\n"; // Print error message in red
    }
    // success message in green
    void successMsg(const string& msg) {
        cout << "\033[32m" << msg << "\033[0m\n"; // Print success message in green
    }
    // info message in blue
    void infoMsg(const string& msg) {
        cout << "\033[34m" << msg << "\033[0m\n"; // Print info message in blue
    }
    // Saves patient data to a file
    void saveToDb(const vector<Patient>& Db) {
        ofstream outFile(FILE_NAME + ".txt");
        if (!outFile) {
            errMsg("Error: Unable to open file for saving.");
            return;
        }
        try {
            outFile << Db.size() << "\n"; // Save the number of patients
            for (const auto& patient : Db) {
                outFile << patient.name << "\n"
                    << patient.age << "\n"
                    << patient.weight << "\n"
                    << patient.gender << "\n"
                    << patient.phoneNumber << "\n"
                    << patient.bloodType << "\n"
                    << patient.medicalHistory << "\n"
                    << patient.timestamp << "\n"
                    << patient.progressLog << "\n";
                outFile << "---\n"; // use "---" to separate patient records
            }
        }
        catch (...) {
            errMsg("Error: Corrupted database file.");
        }
        outFile.close();
        infoMsg("System: database updated!");
        return;
    }
    // loads Patient Data from a file
    void loadDb(vector<Patient>& Db) {
        ifstream inFile(FILE_NAME + ".txt");
        if (!inFile) {
            infoMsg("System: No previous database found. Starting fresh!");
            return;
        }
        try {
            size_t numpatients;
            inFile >> numpatients;
            inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            Db.resize(numpatients);

            for (Patient& patient : Db) {
                getline(inFile, patient.name);
                inFile >> patient.age >> patient.weight >> patient.gender;
                inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                getline(inFile, patient.phoneNumber);
                getline(inFile, patient.bloodType);
                getline(inFile, patient.medicalHistory);
                inFile >> patient.timestamp;
                inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                string line, previousConditions;
                while (getline(inFile, line)) {
                    if (line == "---") break;
                    previousConditions += (previousConditions.empty() ? "" : "\n") + line;
                }
                patient.progressLog = previousConditions;
            }
        }
        catch (...) {
            errMsg("Error: Corrupted database file.");
        }
        inFile.close();
    }
}

// System Functions
namespace System {
    // Function to list all patients in the database
    void listAllPatients(const vector<Patient>& Db) {
        utils::Clear();
        if (!Db.empty()) {
            cout << "=========== ALL PATIENTS (" << Db.size() << ") ===========\n";
            size_t i = 1;
            for (const auto& patient : Db) {
                cout << "PATIENT #" << i++ << "\n";
                cout << "Name:         " << patient.name << "\n";
                cout << "Age:          " << patient.age << " years\n";
                cout << "Weight:       " << patient.weight << " kg\n";
                cout << "Gender:       " << patient.gender << "\n";
                cout << "Blood Type:   " << patient.bloodType << "\n";
                cout << "PhoneNum:     " << patient.phoneNumber << "\n";
                // Convert timestamp to readable format
                char buffer[80];
                tm* timeinfo = localtime(&patient.timestamp);
                strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
                cout << "Registry Date: " << buffer << "\n";
                cout << "==========================================\n";
            }
        }
        else {
            cout << "==========================================\n";
            utils::infoMsg("Database is empty.");
            cout << "==========================================\n";
        }
        cout << "press Enter to continue..." << endl;
        utils::holdc();
        utils::Clear();
    }

    //  Function to add a new patient to the database
    void addPatient(vector<Patient>& Db) {
        while (true) {
            utils::Clear();
            Patient newPatient;
            cout << "=============== REGISTER NEW PATIENT ================\n";
            utils::infoMsg("Enter '0' at any point to cancel and go back to the main menu.");
            cout << "-----------------------------------------------------\n";
            cout << "please fill in the patient details below:\n";

            // Name input
            while (true) {
                cout << "Enter Patient name: ";
                if (cin.peek() == '\n') cin.ignore(); // Clear the input buffer only if needed
                getline(cin, newPatient.name);
                if (newPatient.name == "0") {
                    utils::Clear();
                    return; // Cancel registration
                }
                if (!newPatient.name.empty()) break; // Valid input
                utils::errMsg("Name cannot be empty. Please try again.");
            }
            // Phone Number input
            while (true) {
                cout << "Enter phone number: ";
                if (cin.peek() == '\n') cin.ignore(); // Clear the input buffer only if needed
                getline(cin, newPatient.phoneNumber);
                if (newPatient.phoneNumber == "0") {
                    utils::Clear();
                    return; // Cancel registration
                }
                if (utils::isValidPhoneNumber(newPatient.phoneNumber)) break; // Valid input
                utils::errMsg("Invalid phone number. Please try again.");
            }
            // Check for duplicate before adding
            if (utils::isPatientExists(Db, newPatient)) {
                utils::Clear();
                cout << "==================================================\n";
                utils::errMsg("Duplicate entry detected.");
                cout << "Patient already exists in the database!\n";
                cout << "Please check the name and phone number.\n";
                cout << "==================================================\n";
                cout << "press Enter to continue...";
                utils::holdc();
                utils::Clear();
                continue; // Continue the loop to allow re-entry of patient details
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
                if (newPatient.age == 0) {
                    utils::Clear();
                    return; // Cancel registration
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Consume any remaining input
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
                for (char& c : newPatient.bloodType) c = toupper(c); // Convert to uppercase
                if (utils::isValidBloodType(newPatient.bloodType)) break; // Valid input
                utils::errMsg("Invalid blood type. Please try again.");
            }
            // input Medical History
            while (true) {
                cout << "Enter Medical History & Examination(Patient Symptoms or Previous Diagnosis): ";
                if (cin.peek() == '\n') cin.ignore(); // Clear the input buffer only if needed
                getline(cin, newPatient.medicalHistory);
                if (newPatient.medicalHistory == "0") {
                    utils::Clear();
                    return; // Cancel registration
                }
                if (!newPatient.medicalHistory.empty()) break; // Valid input
                utils::errMsg("Medical History cannot be empty. Please try again.");
            }
            // Initialize Progress logs as empty
            newPatient.progressLog = ""; 
            // Set the registration timestamp
            newPatient.timestamp = time(nullptr);

            utils::Clear(); // Clear the console screen after adding patient
            Db.push_back(newPatient); // add to db
            utils::saveToDb(Db); // update Database

            cout << "==================================================\n";
            utils::successMsg("New patient: '" + newPatient.name + "' Registered successfully.");
            cout << "==================================================\n";
            cout << "press Enter to continue..." << endl;
            utils::holdc(); // Wait for user input before clearing the screen
            utils::Clear();
            break; // Exit the loop after successful addition
        }
    }

    // log patient condition
    void logPatientProgress(vector<Patient>& Db, int patientIndex) {
        utils::Clear();
        cout << "================= LOG PATIENT PROGRESS ==================\n";
        if (patientIndex < 0 || patientIndex >= Db.size()) {
            utils::errMsg("System Error: Invalid patient index.");
            cout << "Press Enter to continue...";
            utils::holdc();
            utils::Clear();
            return;
        }
        utils::Clear();
        cout << "==================================================\n";
        cout << "Logging Progress for patient #" << patientIndex << ": " << "\n";
        cout << "\033[35mName: " << Db[patientIndex].name << "\033[0m\t";
        cout << "\033[35mAge: " << Db[patientIndex].age << " years\033[0m\t";
        cout << "\033[35mWeight: " << Db[patientIndex].weight << " kg\033[0m\t";
        cout << "\033[35mBlood Type: " << Db[patientIndex].bloodType << "\033[0m\n";
        cout << "--------------------------------------------------\n";
        cout << Db[patientIndex].name << "'s previous Medical Progress: \n";
        cout << "\033[33m"+(Db[patientIndex].progressLog.empty() ? "None" : Db[patientIndex].progressLog)
            << "\033[0m\n"; // Display previous Logs if any
        cout << "==================================================\n";

        string log;
        string newLogs = "";//temporary variable to hold new Logs
        char choice;
        do{
            cout << "Enter the Progress to log for " << Db[patientIndex].name << "(Enter 0 for cancel): ";
            cin.ignore(); // Clear the input buffer before getline
            getline(cin, log);
            while (log.empty()) {
                utils::errMsg("Log cannot be empty. Please enter a valid Progress Log.");
                cin.ignore(); // Clear the input buffer before getline
                getline(cin, log);
            }
            if (log == "0") {
                utils::Clear();
                return;
            }
            time_t now = time(nullptr);// Get the current date and time
            char buffer[80];
            tm* timeinfo = localtime(&now);
            strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

            string logWithDate = log + " (Logged on: " + buffer + ")"; // Append the log with the log date
            newLogs += (newLogs.empty() ? std::string("") : std::string("\n")) + ">> " + logWithDate;
            cout << "---------------------------------------------------\n";
            utils::successMsg("log added successfully.");
            cout << "---------------------------------------------------\n";
            cout << "Do you want to add another Log? (Y/N): ";
            cin >> choice;
            choice = toupper(choice); // Convert to uppercase for consistency
            while (choice != 'Y' && choice != 'N') {
                utils::errMsg("Invalid input. Please enter Y or N: ");
                cin >> choice;
                choice = toupper(choice); // Convert to uppercase for consistency
            }
        } while (choice == 'Y');

        cout << "Do you want to save the Logs? (Y/N): ";
        cin >> choice;
        choice = toupper(choice);
        while (choice != 'Y' && choice != 'N') {
            utils::errMsg("Invalid input. Please enter Y or N: ");
            cin >> choice;
            choice = toupper(choice); // Convert to uppercase for consistency
        }
        if (choice == 'Y') {
            utils::Clear(); // Clear the console screen after saving logs
            Db[patientIndex].progressLog += (Db[patientIndex].progressLog.empty() ? "" : "\n") + newLogs;
            utils::saveToDb(Db);//update Database
            cout << "==================================================\n";
            utils::successMsg("Medical Progress logged successfully for " + Db[patientIndex].name);
            cout << "--------------------------------------------------\n";
            cout << "Updated Medical Progress for " << Db[patientIndex].name << ": \n";
            cout << "\033[33m" + Db[patientIndex].progressLog << "\033[0m\n"; // Display updated logs
            cout << "==================================================\n";
        } else {
            utils::Clear();
            cout << "==================================================\n";
            cout << "Logging canceled. No changes were made.\n";
            cout << "==================================================\n";
        }
        cout << "press Enter to continue...";
        utils::holdc();
        utils::Clear();
    }

    // Function to clear logs for a specific patient
    void clearLogs(vector<Patient>& Db, int patientIndex) {
        utils::Clear();
        cout << "================= CLEAR PATIENT LOGS ==================\n";

        if (patientIndex < 0 || patientIndex >= Db.size()) {
            utils::errMsg("System Error: Invalid patient index.");
            cout << "Press Enter to continue...";
            utils::holdc();
            utils::Clear();
            return;
        }

        cout << "Are you sure you want to clear the logs for " << Db[patientIndex].name << "? (Y/N): ";
        char confirmClear;
        cin >> confirmClear;
        confirmClear = toupper(confirmClear);

        if (confirmClear != 'Y') {
            utils::Clear();
            cout << "==================================================\n";
            utils::infoMsg("Clear logs operation canceled.");
            cout << "==================================================\n";
            cout << "Press Enter to continue...";
            utils::holdc();
            utils::Clear();
            return;
        }

        Db[patientIndex].progressLog = ""; // Clear the progress log
        utils::saveToDb(Db); // Save the changes to the database

        utils::Clear();
        cout << "==================================================\n";
        utils::successMsg("Logs cleared successfully for " + Db[patientIndex].name);
        cout << "==================================================\n";
        cout << "Press Enter to continue...";
        utils::holdc();
        utils::Clear();
    }

    //  Function to delete a patient record from the database
    void deletePatient(vector<Patient>& Db, int patientIndex) {
        utils::Clear(); // Clear the console screen before deleting a patient

        if (Db.empty()) {
            utils::infoMsg("Database is empty. Cannot delete.");
            cout << "Press Enter to continue...";
            utils::holdc();
            utils::Clear();
            return;
        }

        if (patientIndex < 0 || patientIndex >= Db.size()) {
            utils::errMsg("Invalid patient index.");
            cout << "Press Enter to continue...";
            utils::holdc();
            utils::Clear();
            return;
        }

        cout << "================ DELETE PATIENT ===================\n";
        cout << "Are you sure you want to delete the record of " << Db[patientIndex].name << "? (Y/N): ";
        char confirmDelete;
        cin >> confirmDelete;
        confirmDelete = toupper(confirmDelete); // Convert to uppercase for consistency

        if (confirmDelete != 'Y') {
            utils::Clear();
            cout << "==================================================\n";
            utils::infoMsg("Deletion canceled. No changes were made to the database.");
            cout << "==================================================\n";
            cout << "Press Enter to continue...";
            utils::holdc();
            utils::Clear();
            return;
        }

        // Remove the patient from the vector
        Db.erase(Db.begin() + patientIndex);
        utils::saveToDb(Db);

        utils::Clear();
        cout << "==================================================\n";
        utils::successMsg("Patient Record deleted successfully.");
        cout << "==================================================\n";
        cout << "Press Enter to continue...";
        utils::holdc();
        utils::Clear();
    }

    // Function to edit an existing patient's record
    void editPatient(vector<Patient>& Db, int patientIndex) {
        utils::Clear();

        if (patientIndex < 0 || patientIndex >= Db.size()) {
            utils::errMsg("System Error: Invalid patient index.");
            cout << "Press Enter to continue...";
            utils::holdc();
            utils::Clear();
            return;
        }

        Patient& patient = Db[patientIndex]; // Get a reference to the patient object

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
            cout << "7. Medical History: \n";
            cout << ">>> " << patient.medicalHistory << "\n";
            cout << "=====================================================\n";
            utils::infoMsg("Select the item you want to edit (1-7), or enter 0 to cancel:> ");

            while (!(cin >> choice) || choice < 0 || choice > 7) {
                utils::errMsg("Invalid input. Please enter a number between 0 and 7: ");
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
                cin.ignore();
                getline(cin, new_name);
                patient.name = new_name;
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
                patient.age = new_age;
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
                patient.gender = newGender;
                break;
            }
            case 4: {
                string new_bloodType;
                cout << "----------------------------------------------\n";
                cout << "Editing Blood Type:_\n";
                utils::infoMsg("Current Blood Type: " + patient.bloodType);
                cout << "Enter new blood type (A+, A-, B+, B-, AB+, AB-, O+, O-): ";
                cin.ignore();
                getline(cin, new_bloodType);
                for (char& c : new_bloodType) c = toupper(c); // Convert to uppercase
                while (!utils::isValidBloodType(new_bloodType)) {
                    utils::errMsg("Invalid blood type. Please enter a valid type: ");
                    getline(cin, new_bloodType);
                    for (char& c : new_bloodType) c = toupper(c); // Convert to uppercase
                }
                patient.bloodType = new_bloodType;
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
                patient.weight = new_weight;
                break;
            }
            case 6: {
                string new_phoneNumber;
                cout << "----------------------------------------------\n";
                cout << "Editing Phone Number:_\n";
                utils::infoMsg("Current Phone Number: " + patient.phoneNumber);
                cout << "Enter new phone number: ";
                cin.ignore();
                getline(cin, new_phoneNumber);
                while (!utils::isValidPhoneNumber(new_phoneNumber)) {
                    utils::errMsg("Invalid phone number format. Please enter a valid phone number: ");
                    getline(cin, new_phoneNumber);
                }
                patient.phoneNumber = new_phoneNumber;
                break;
            }
            case 7: {
                string new_history;
                cout << "----------------------------------------------\n";
                cout << "Editing Medical History:_\n";
                cout << "----------------------------------------------\n";
                utils::infoMsg("Current Medical History: ");
                utils::infoMsg(">>> " + patient.medicalHistory);
                cout << "----------------------------------------------\n";
                cout << "Enter edited Medical History: ";
                cin.ignore(); // Clear the input buffer
                getline(cin, new_history);
                patient.medicalHistory = new_history;
                break;
            }
            default:
                break;
            }
            utils::Clear();
            utils::saveToDb(Db); // update Database
            cout << "===================================================\n";
            utils::successMsg(patient.name + "'s record was updated successfully.");
            cout << "===================================================\n";
            cout << "Press Enter to continue...";
            utils::holdc();
            utils::Clear();
        } while (choice != 0);
    }

    // Function to display patient details and manage actions
    void displayPatientProfile(vector<Patient>& Db, int patientIndex) {
        utils::Clear();
        if (patientIndex < 0 || patientIndex >= Db.size()) {// Check if the index is valid
            utils::errMsg("System Error: Invalid patient index.");
            cout << "Press Enter to continue...";
            utils::holdc();
            return;
        }
        Patient& patient = Db[patientIndex];

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
            cout << "-----------------------------------------------------\n";
            cout << "\033[35mMedical History:\033[0m\n";
            cout << "\033[35m>>> " << patient.medicalHistory << "\033[0m\n";
            cout << "=====================================================\n";
            // Display Progress logs if any
            if (!patient.progressLog.empty()) {
                cout << "\033[33mPatient Medical Progress Logs: \n" << patient.progressLog << "\033[0m\n";
            }
            else {
                cout << "\033[33mNo progress Logs recorded.\033[0m\n";
            }

            cout << "=====================================================\n";
            cout << "Actions:\n";
            cout << "1. log Medical progress for " << patient.name << "\n";
            cout << "2. Clear " << patient.name << "'s Medical progress logs" << "\n";
            cout << "3. Edit " << patient.name << "'s profile" << "\n";
            cout << "4. Delete " << patient.name << "'s profile from the system" << "\n";
            cout << "0. Back to Main Menu" << "\n";
            cout << "Enter your choice:> ";

            while (!(cin >> choice)) {
                utils::errMsg("Invalid input. Please enter a number: ");
                cin.clear();
                cin.ignore(10000, '\n');
            }

            switch (choice) {
            case 1:
                logPatientProgress(Db, patientIndex);
                break;
            case 2:
                clearLogs(Db, patientIndex);
                break;
            case 3:
                editPatient(Db, patientIndex);
                break;
            case 4:
                deletePatient(Db, patientIndex);
                return;
            case 0:
                utils::Clear();
                break;
            default:
                utils::errMsg("Invalid input. Please enter a number: ");
                break;
            }

        } while (choice != 0);
        return; // Return to the previous menu
    }

    // Function to find patients by name or phone number
    void findPatients(vector<Patient>& Db) {
        utils::Clear(); // Clear the console screen
        cout << "=============== SEARCH PATIENTS ================\n";
        if (Db.empty()) {
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
        int selected; // selected match from the search results
        int patientIndex; // index of selected patient to be passed to the display function
        // prompt search type
        cout << "--------------------------------------------------\n";
        cout << "SEARCH BY: \n";
        cout << "1. NAME\n";
        cout << "2. PHONE NUMBER\n";
        cout << "0. back to Main Menu\n";
        cout << "Enter your choice:> ";
        int choice;
        while (!(cin >> choice) || choice < 0 || choice > 2) {
            utils::errMsg("Invalid input. Please enter a number: ");
            cin.clear();
            cin.ignore(10000, '\n');
        }
        if (choice == 0) {
            utils::Clear();
            return;
        }
        if (choice == 1) { //search by name
            while (true) { // Loop to allow retrying the search
                utils::Clear();
                cout << "=============== SEARCH BY NAME ================\n";
                utils::infoMsg("You can also enter '0' to cancel and return to the previous menu.");
                cout << "Enter patient name to search: ";
                if (cin.peek() == '\n') cin.ignore(); // Clear the input buffer only if needed
                getline(cin, searchStr);
                if (searchStr.empty()) {
                    utils::errMsg("Search string cannot be empty. Please enter a valid name.");
                    continue; // Continue to the next iteration of the loop
                }
                if (searchStr == "0") {
                    utils::Clear();
                    return; // Return to the previous menu
                }
                // Convert searchStr to lowercase for case-insensitive comparison
                for (char& c : searchStr) c = tolower(c);
                utils::Clear(); // Clear the console screen before displaying results
                cout << "================== SEARCH RESULTS ==================\n";
                utils::infoMsg("Searching for patients with name containing: " + searchStr);
                cout << "-----------------------------------------------------\n";
                // Loop through the database to find matching patients
                for (size_t i = 0; i < Db.size(); ++i) {
                    string patientNameLower = Db[i].name;
                    // Convert patient name to lowercase for case-insensitive comparison
                    for (char& c : patientNameLower) c = tolower(c);
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
                        utils::Clear();
                        return; // Exit the function if the user cancels
                    }
                    utils::Clear();
                    continue; // Retry the search
                }
                break;
            }

            // Prompt the user to select a patient from the search results
            cout << "==================================================\n";
            utils::infoMsg("Select Patient from the search results...");
            utils::infoMsg("Enter the match number 1 to " + to_string(matchIndices.size()) + " to view details.");
            utils::infoMsg("You can also enter '0' to cancel and return to the previous menu.");
            cout << "Enter your choice:> ";

            while (!(cin >> selected) || selected < 0 || selected > matchIndices.size()) {
                utils::errMsg("Invalid input. Please enter a number between 1 and " + to_string(matchIndices.size()) + ": ");
                cin.clear();
                cin.ignore(10000, '\n');
            }

            if (selected == 0) {
                utils::Clear();
                return; // Return to the previous menu
            }

            patientIndex = matchIndices[selected - 1]; // Get the actual index of the selected patient
            displayPatientProfile(Db, patientIndex); // Pass the actual index to the display function
            return; // Return after displaying patient details
        }
        else if (choice == 2) { //search by phone number
            while (true) { // Loop to allow retrying the search
                utils::Clear();
                cout << "=============== SEARCH BY PHONE NUMBER ================\n";
                utils::infoMsg("You can also enter 'C' to cancel and return to the previous menu.");
                cout << "Enter phone number to search: ";
                if (cin.peek() == '\n') cin.ignore(); // Clear the input buffer only if needed
                getline(cin, searchStr);
                if (searchStr.empty()) {
                    utils::errMsg("Search string cannot be empty. Please enter a valid name.");
                    continue; // Continue to the next iteration of the loop
                }
                if (searchStr == "c" || searchStr == "C") {
                    utils::Clear();
                    return; // Return to the previous menu
                }
                // Remove any non-digit characters for more flexible searching(normalize)
                for (char c : searchStr) {
                    if (isdigit(c)) {
                        normalizedSearch += c;
                    }
                }
                if (normalizedSearch.empty()) {
                    utils::errMsg("Invalid phone number. Please enter a valid phone number.");
                    continue;
                }
                utils::Clear(); // Clear the console screen before displaying results
                cout << "================== SEARCH RESULTS ==================\n";
                utils::infoMsg("Searching for patients with phone number containing: " + searchStr);
                cout << "====================================================\n";
                for (size_t i = 0; i < Db.size(); ++i) {
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
                    utils::infoMsg("No patients found with the Phone number containing: " + searchStr);
                    cout << "==================================================\n";
                    cout << "Press Enter to retry or type '0' to cancel: ";
                    string retryInput;
                    getline(cin, retryInput);
                    if (retryInput == "0") {
                        utils::Clear();
                        return; // Exit the function if the user cancels
                    }
                    normalizedSearch.clear(); // Clear normalizedSearch before each retry
                    utils::Clear();
                    continue; // Retry the search
                }
                break;
            }
            // Prompt the user to select a patient from the search results
            cout << "==================================================\n";
            utils::infoMsg("Select Patient from the search results...");
            utils::infoMsg("Enter the match number 1 to " + to_string(matchIndices.size()) + " to view details.");
            utils::infoMsg("You can also enter '0' to cancel and return to the previous menu.");
            cout << "Enter your choice:> ";

            while (!(cin >> selected) || selected < 0 || selected > matchIndices.size()) {
                utils::errMsg("Invalid input. Please enter a number between 1 and " + to_string(matchIndices.size()) + ": ");
                cin.clear();
                cin.ignore(10000, '\n');
            }

            if (selected == 0) {
                utils::Clear();
                return; // Return to the previous menu
            }

            patientIndex = matchIndices[selected - 1]; // Get the actual index of the selected patient
            displayPatientProfile(Db, patientIndex); // Pass the actual index to the display function
            return;
        }
    }

    //  Function to clear the entire database
    void clearDatabase(vector<Patient>& Db) {
        utils::Clear();
        cout << "================= CLEAR DATABASE =====================\n";
        if (Db.empty()) {
            utils::infoMsg("Database is already empty...");
        } else {
            cout << "This action will clear all patient records from the database.\n";
            cout << "-----------------------------------------------------\n";
            cout << "Current number of patients: " << Db.size() << "\n";
            cout << "-------------------------------------------------\n";
            utils::errMsg("Warning: This action cannot be undone.");
            cout << "Are you sure you want to clear the database? (Y/N): ";
            char confirmClear;
            cin >> confirmClear;
            utils::Clear();
            if (toupper(confirmClear) == 'Y') {
                Db.clear(); // Clear all elements from the vector
                utils::saveToDb(Db); // update Database
                cout << "==================================================\n";
                utils::successMsg("Database cleared successfully.");
            } else {
                cout << "==================================================\n";
                utils::infoMsg("Database clearing canceled.");
                cout << "No changes were made to the database.\n";
            }
        }
        cout << "==================================================\n";
        cout << "Press Enter to continue...";
        utils::holdc();
        utils::Clear();
    }

    // System Dashboard
    void dashboard(){
        utils::Clear();
        cout << "======================= PRMS DASHBOARD ========================\n";
        cout << "\033[35mTotal Patients Registered: " << Db.size() << "\033[0m\n";

        int maleCount = 0, femaleCount = 0;
        double totalAge = 0.0, totalWeight = 0.0;

        for (const auto& patient : Db) {
            if (patient.gender == 'M') ++maleCount;
            else if (patient.gender == 'F') ++femaleCount;
            totalAge += patient.age;
            totalWeight += patient.weight;
        }

        cout << "\033[35mNumber of Male Patients: " << maleCount << "\033[0m\n";
        cout << "\033[35mNumber of Female Patients: " << femaleCount << "\033[0m\n";

        if (Db.size() > 0) {
            cout << "\033[35mAverage Age: " << (totalAge / Db.size()) << " years\033[0m\n";
            cout << "\033[35mAverage Weight: " << (totalWeight / Db.size()) << " kg\033[0m\n";
        } else {
            cout << "\033[33mNo patients in the database to calculate averages.\033[0m\n";
        }

        cout << "============================================================\n";
        cout << "Press Enter to continue...\n";
        utils::holdc();
        utils::Clear();
    }

    // Function to display system information
    void info(){
        utils::Clear();
        cout << "=============== ABOUT THE SYSTEM ================\n";
        cout << "This is a Patient Records Management System designed to help\n";
        cout << "healthcare professionals manage patient records efficiently.\n";
        cout << "Features include:\n";
        cout << "- Registering new patients\n";
        cout << "- Searching for patients by name or phone number\n";
        cout << "- Logging patient Progress\n";
        cout << "- Editing patient profiles\n";
        cout << "- Deleting patient records\n";
        cout << "- Viewing system statistics\n";
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
        cout << "Version: 2.0.0\n";
        cout << "Written in C++.\n";
        cout << "==================================================\n";
        cout << "Press Enter to return to the main menu...\n";
        utils::holdc();
        utils::Clear();
    }
}

// System Actions Menu Function
void adminMenu() {
    utils::Clear();
    int choice;
    do {
        cout << "=============== ADMIN ACTIONS ================\n";
        cout << "Available Actions:\n";
        cout << "1. Show System Stats\n";
        cout << "2. Clear Database (delete all records)\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter your choice:> ";

        while (!(cin >> choice)|| choice > 2) {
            cout << "Invalid input. Please enter a number from 1 - 2: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }

        switch (choice) {
            case 1:
                System::dashboard();
                break;
            case 2:
                System::clearDatabase(Db);
                break;
            case 0:
                utils::Clear();
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                cout << "Press Enter to continue...";
                utils::holdc(); 
                utils::Clear();
        }
    } while (choice != 0);
}

// Main Menu Function
void mainMenu(){
    int choice;
    do {
        cout << "=============== MAIN MENU =======V3=======\n";
        cout << "1. Search Patient Records\n";
        cout << "2. Register a New Patient\n";
        cout << "3. list All Patient Records\n";
        cout << "4. Admin Actions\n";
        cout << "5. Info\n";
        cout << "0. Exit\n";
        cout << "Enter your choice:> ";

        while (!(cin >> choice) || choice > 5) {
            utils::errMsg("Invalid input. Please enter a number from 1 - 5 ");
            cin.clear();
            cin.ignore(10000, '\n');
        }

        switch (choice) {
            case 1:
                System::findPatients(Db);
                break;
            case 2:
                System::addPatient(Db);
                break;
            case 3:
                System::listAllPatients(Db);
                break;
            case 4:
                adminMenu();
                break;
            case 5:
                System::info();
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
                utils::holdc();
                utils::Clear();
        }
    } while (choice != 0);

};

//  MAIN FUNCTION
int main() {
    utils::Clear();
    utils::infoMsg("WELCOME TO THE PATIENT RECORDS MANAGEMENT SYSTEM!");
    utils::loadDb(Db); //load the database to memory
    mainMenu(); // Call the main menu function
    return 0;
}
