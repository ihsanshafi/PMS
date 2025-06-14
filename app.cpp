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
    // Checks if the phone number contains only digits, spaces, and common symbols
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


// ADD PATIENT FUNCTION
void addPatient(Patient Db[], int& numpatients) {
    utils::Clear();
    if (numpatients >= MAX_PATIENTS) {
        cout << "Database is full! Cannot add more patients.\n";
        cout << "press Enter to continue...";
        utils::holdc(); // Wait for user input before clearing the screen
        utils::Clear();
        return;
    }

    Patient newPatient;

    cout << "ADD NEW PATIENT\n";
    cout << "==================================================\n";


    // Name
    cout << "Enter patient name: ";
    cin.ignore();
    getline(cin, newPatient.name);

    // Age
    cout << "Enter patient age: ";
    while (!(cin >> newPatient.age) || newPatient.age <= 0) {
        cout << "Invalid age. Please enter a positive number: ";
        cin.clear();
        cin.ignore(10000, '\n'); // Clear the input buffer
    }

    // Weight
    cout << "Enter patient weight (kg): ";
    while (!(cin >> newPatient.weight) || newPatient.weight <= 0) {
        cout << "Invalid weight. Please enter a positive number: ";
        cin.clear();
        cin.ignore(10000, '\n'); // Clear the input buffer
    }

    // Gender
    cout << "Enter gender (M/F): ";
    cin >> newPatient.gender;
    newPatient.gender = toupper(newPatient.gender);
    while (newPatient.gender != 'M' && newPatient.gender != 'F') {
        cout << "Invalid gender. Please enter M or F : ";
        cin >> newPatient.gender;
        newPatient.gender = toupper(newPatient.gender);
    }

    // Blood Type
    cout << "Enter blood type (A+, A-, B+, B-, AB+, AB-, O+, O-): ";
    cin >> newPatient.bloodType;

    for (char &c : newPatient.bloodType) c = toupper(c); // Convert to uppercase
    while (!utils::isValidBloodType(newPatient.bloodType)) {
        cout << "Invalid blood type. Please enter a valid type: "; // Prompt for valid blood type
        cin >> newPatient.bloodType;// Read the input
        for (char &c : newPatient.bloodType) c = toupper(c);// Convert to uppeercase
    }

    // Phone Number
    cout << "Enter phone number: ";
    cin.ignore();
    getline(cin, newPatient.phoneNumber);
    while (!utils::isValidPhoneNumber(newPatient.phoneNumber)) {
        cout << "Invalid phone number. Please enter a valid number: ";
        getline(cin, newPatient.phoneNumber);
    }

    // Initialize previous health conditions as empty
    newPatient.previousConditions = ""; // Initialize previous conditions as empty

    // Set the registration timestamp
    newPatient.timestamp = time(nullptr);
    
    // Check for duplicate before adding
    if (utils::isPatientExists(Db, numpatients, newPatient)) {
        utils::Clear();
        cout << "Patient already exists in the database!\n";
        cout << "--------------------------------------------------\n";
        cout << "press Enter to continue...";
        utils::holdc();
        utils::Clear();
        return;
    }

    // Add to database
    Db[numpatients++] = newPatient;
    cout << "Patient " << newPatient.name  << " added successfully.\n";
    cout << "--------------------------------------------------\n";

    cout << "press Enter to continue..."<<endl;

    utils::holdc(); // Wait for user input before clearing the screen
    utils::Clear();
}

// EDIT PATIENT FUNCTION
void editpatient(Patient Db[],int numpatients){
    utils::Clear();
    cout << "EDIT PATIENT RECORD\n";
    cout << "==================================================\n";

    if (numpatients == 0) {
        cout << "Database is empty. Cannot edit.\n";
        cout << "press Enter to continue...";
        utils::holdc(); // Wait for user input before clearing the screen
        utils::Clear();
        return;
    }// Clear the console screen
    utils::listPatients(Db, numpatients); // List all patients before editing
    int patientId;
    cout << "Enter the id of the patient to edit (1 to " << numpatients << "): ";
    cin >> patientId;
    utils::Clear(); // Clear the console screen before editing
    string new_name, new_bloodType, new_phoneNumber;
    float new_age, new_weight;
    char newGender;
    if (patientId >= 1 && patientId <= numpatients) {
        cout << "-------------------------\n";
        cout << "Editing patient " << patientId << ":\n"; 
        cout << "       previous Name: " << Db[patientId - 1].name << "\n";
        cout << "       Previous Age: " << Db[patientId - 1].age << "\n";
        cout << "       previous Weight: " << Db[patientId - 1].weight << "\n";
        cout << "       previous Gender: " << Db[patientId - 1].gender << "\n";
        cout << "       previous Blood type: " << Db[patientId - 1].bloodType << "\n";
        cout << "       previous Phone number: " << new_phoneNumber << "\n";
        cout << "-------------------------\n";
        // name
        cout << "Enter new patient name: ";
        cin.ignore(); // Clear the newline character from the input buffer
        getline(cin, new_name); // Use getline to allow spaces in the name
        Db[patientId - 1].name = new_name;

        // age
        cout << "Enter new age: ";
        cin.ignore(); // Clear the newline character from the input buffer
        cin >> new_age; // Use cin to read the age
        Db[patientId - 1].age = new_age;

        // weight
        cout << "Enter new weight: ";
        cin.ignore(); // Clear the newline character from the input buffer
        cin >> new_weight; // Use cin to read the weight
        Db[patientId - 1].weight = new_weight;

        // gender
        cout << "Enter new gender (M/F): ";
        cin >> newGender; // Use cin to read
        newGender = toupper(newGender); // Convert to uppercase
        while (newGender != 'M' && newGender != 'F') {
            cout << "Invalid input. Please enter M or F : ";
            cin >> newGender; // Read again
            newGender = toupper(newGender); // Convert to uppercase
        }
        
        Db[patientId - 1].gender = newGender; // Update
        // blood type
        cout << "Enter new blood type (A+, A-, B+, B-, AB+, AB-, O+, O-): ";
        cin.ignore(); // Clear the newline character from the input buffer
        getline(cin, new_bloodType); // Use getline to allow spaces in the blood type and 
        while (!utils::isValidBloodType(new_bloodType)) {
            cout << "Invalid blood type. Please enter a valid type: ";
            getline(cin, new_bloodType);
            for (char &c : new_bloodType) c = toupper(c); // Convert to uppercase
        }
        Db[patientId - 1].bloodType = new_bloodType; // Update the blood type

        // phone number
        cout << "Enter new phone number: ";
        cin.ignore(); // Clear the newline character from the input buffer 
        getline(cin, new_phoneNumber); // Use getline to allow spaces in the phone number
        while (!utils::isValidPhoneNumber(new_phoneNumber)) {
            cout << "Invalid phone number. Please enter a valid number: ";
            getline(cin, new_phoneNumber);
        }
        Db[patientId - 1].phoneNumber = new_phoneNumber; // Update the phone number
        // Display the updated patient record
        cout << "-------------------------\n";
        utils::Clear(); // Clear the console screen after editing
        cout << "patient "<<patientId<<"'s record updated successfully.\n";
    } else {
        cout << "Invalid patient id.\n";
    }
    cout << "--------------------------------------------------\n";

    cout << "press Enter to continue...";
    utils::holdc(); // Wait for user input before clearing the screen
    utils::Clear();
}

//  LOG PATIENT CONDITION FUNCTION
void logpatientcondition(Patient Db[], int numpatients) {
    utils::Clear();
    cout << "LOG PATIENT CONDITION\n";
    cout << "==================================================\n";

    if (numpatients == 0) {
        cout << "Database is empty. Cannot log condition.\n";
        cout << "press Enter to continue...";
        utils::holdc(); // Wait for user input before clearing the screen
        utils::Clear();
        return;
    }

    utils::listPatients(Db, numpatients);

    int patientId;
    cout << "Enter the ID of the patient to log condition (1 to " << numpatients << "): ";
    while (!(cin >> patientId) || patientId < 1 || patientId > numpatients) {
        cout << "Invalid ID. Please enter a number between 1 and " << numpatients << ": ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    utils::Clear(); // Clear the console screen before logging condition
    cout << "--------------------------------------------------\n";
    cout << "Logging condition for patient #" << patientId << ": "<<"\n";
    cout<< Db[patientId - 1].name 
    << ", Age: " << Db[patientId - 1].age 
    << ", Weight: " << Db[patientId - 1].weight 
    << ",blood type: " << Db[patientId - 1].bloodType << "\n"<<"\n";
    cout << Db[patientId - 1].name << "'s previous conditions: " 
         << (Db[patientId - 1].previousConditions.empty() ? "None" : Db[patientId - 1].previousConditions) << "\n"; // Display previous conditions if any
    cout << "--------------------------------------------------\n";

    string condition;
    cout << "Enter the condition to log for patient #" << patientId << ": ";
    cin.ignore();
    getline(cin, condition);

    Db[patientId - 1].previousConditions += (Db[patientId - 1].previousConditions.empty() ? "" : ", ") + condition; // Append the new condition to the existing conditions
    utils::Clear(); // Clear the console screen after logging condition
    cout << "--------------------------------------------------\n";
    cout << "Condition logged successfully for patient #" << patientId << ".\n";
    
    cout << "Updated conditions for " << Db[patientId - 1].name << ": "
         << Db[patientId - 1].previousConditions << "\n"; // Display updated conditions
    cout << "--------------------------------------------------\n";
    cout << "press Enter to continue...";
    utils::holdc(); // Wait for user input before clearing the screen
    utils::Clear();
}

// DELETE PATIENT FUNCTION
void deletepatient(Patient Db[], int& numpatients) {
    utils::Clear();

    cout << "DELETE A PATIENT RECORD\n";
    cout << "--------------------------------------------------\n";

    if (numpatients == 0) {
        cout << "Database is empty. Cannot delete.\n";
        cout << "press Enter to continue...";
        utils::holdc(); // Wait for user input before clearing the screen
        utils::Clear(); 
        return;
    }

    utils::listPatients(Db, numpatients);

    int patientId;
    cout << "Enter the ID of the patient to delete (1 to " << numpatients << "): ";
    while (!(cin >> patientId) || patientId < 1 || patientId > numpatients) {
        cout << "Invalid ID. Please enter a number between 1 and " << numpatients << ": ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    
    // Confirm deletion
    utils::Clear();
    cout << "CONFIRM DELETION OF PATIENT #" << patientId << "\n";
    cout << "Name: " << Db[patientId - 1].name << "\n";
    cout << "Are you sure? (Y/N): ";
    char confirm;
    cin >> confirm;
    utils::Clear(); // Clear the console screen before confirming deletion
    cout << "--------------------------------------------------\n";
    if (toupper(confirm) == 'Y') {
        // Shift all elements after the deleted patient
        for (int i = patientId - 1; i < numpatients - 1; i++) {
            Db[i] = Db[i + 1];
        }
        numpatients--;
        cout << "Patient deleted successfully.\n";
    } else {
        cout << "Deletion canceled.\n";
    }
    cout << "--------------------------------------------------\n";
    cout << "press Enter to continue...";
    utils::holdc(); // Wait for user input before clearing the screen
    utils::Clear();
}

// CLEAR DATABASE FUNCTION
void clearDatabase(Patient Db[], int& numpatients) {
    utils::Clear();
    cout << "CLEAR DATABASE\n";
    cout << "==================================================\n";
    if (numpatients == 0) {
        cout << "Database is already empty.\n";
    } else {
        cout << "Are you sure you want to clear the database? (Y/N): ";
        char confirmClear;
        cin >> confirmClear;
        if (toupper(confirmClear) == 'Y') {
            numpatients = 0; // Reset the number of patients
            cout << "Database cleared successfully.\n";
        } else {
            cout << "Database clearing canceled.\n";
        }
    }
    cout << "--------------------------------------------------\n";
    cout << "press Enter to continue...";
    utils::holdc(); // Wait for user input before clearing the screen
    utils::Clear();
}

// SEARCH PATIENTS FUNCTION
void searchPatients(const Patient Db[], int numpatients) {
    utils::Clear();
    cout << "SEARCH PATIENTS\n";
    cout << "==================================================\n";

    if (numpatients == 0) {
        cout << "Database is empty. No patients to search.\n";
        cout << "press Enter to continue...";
        utils::holdc();
        utils::Clear();
        return;
    }

    int searchChoice;
    cout << "Search by:\n";
    cout << "1. Name\n";
    cout << "2. Age\n";
    cout << "3. Blood Type\n";
    cout << "4. Gender\n";
    cout << "Enter your choice: ";
    
    while (!(cin >> searchChoice) || searchChoice < 1 || searchChoice > 4) {
        cout << "Invalid choice. Please enter 1-4: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    utils::Clear(); // Clear the console screen before displaying results
    bool found = false;
    string searchStr;
    int minAge, maxAge;
    char searchGender;

    switch (searchChoice) {
        case 1: // Search by name
            cout << "Enter patient name to search: ";
            cin.ignore();
            getline(cin, searchStr);
            utils::Clear(); // Clear the console screen before displaying results
            cout << "SEARCH RESULTS\n";
            cout << "==================================================\n";
            cout << "Searching for patients with name containing: " << searchStr << "\n";
            for (int i = 0; i < numpatients; ++i) {
                if (Db[i].name.find(searchStr) != string::npos) {
                    cout << "--------------------------------------------------\n";
                    cout << "PATIENT #" << (i + 1) << "\n";
                    cout << "Name:       " << Db[i].name << "\n";
                    cout << "Age:        " << Db[i].age << " years\n";
                    cout << "Gender:     " << Db[i].gender << "\n";
                    cout << "Blood Type: " << Db[i].bloodType << "\n";
                    cout << "Phone:      " << Db[i].phoneNumber << "\n";
                    if (!Db[i].previousConditions.empty()) {
                        cout << "Conditions: " << Db[i].previousConditions << "\n";
                    }
                    cout << "--------------------------------------------------\n";
                    found = true;
                }
            }
            break;

        case 2: // Search by exact age
            cout << "Enter age to search: ";
            while (!(cin >> minAge) || minAge < 0) {  // We can reuse minAge variable for single age
                cout << "Invalid age. Please enter a positive number: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
            utils::Clear(); // Clear the console screen before displaying results
            cout << "SEARCH RESULTS\n";
            cout << "==================================================\n";
            cout << "Searching for patients with age: " << minAge << "\n";
            for (int i = 0; i < numpatients; ++i) {
                if (Db[i].age == minAge) { 
                    cout << "--------------------------------------------------\n";
                    cout << "PATIENT #" << (i + 1) << "\n";
                    cout << "Name:       " << Db[i].name << "\n";
                    cout << "Age:        " << Db[i].age << " years\n";
                    cout << "Gender:     " << Db[i].gender << "\n";
                    cout << "Blood Type: " << Db[i].bloodType << "\n";
                    cout << "Phone:      " << Db[i].phoneNumber << "\n";
                    if (!Db[i].previousConditions.empty()) {
                        cout << "Conditions: " << Db[i].previousConditions << "\n";
                    }
                    cout << "--------------------------------------------------\n";
                    found = true;
                }
            }
            break;

        case 3: // Search by blood type
            cout << "Enter blood type to search (A+, A-, B+, B-, AB+, AB-, O+, O-): ";
            cin >> searchStr;
            for (char &c : searchStr) c = toupper(c);
            while (!utils::isValidBloodType(searchStr)) {
                cout << "Invalid blood type. Please enter a valid type: ";
                cin >> searchStr;
                for (char &c : searchStr) c = toupper(c);
            }
            utils::Clear(); // Clear the console screen before displaying results
            cout << "SEARCH RESULTS\n";
            cout << "==================================================\n";
            cout << "Searching for patients with blood type: " << searchStr << "\n";
            for (int i = 0; i < numpatients; ++i) {
                if (Db[i].bloodType == searchStr) {
                    cout << "--------------------------------------------------\n";
                    cout << "PATIENT #" << (i + 1) << "\n";
                    cout << "Name:       " << Db[i].name << "\n";
                    cout << "Age:        " << Db[i].age << " years\n";
                    cout << "Gender:     " << Db[i].gender << "\n";
                    cout << "Blood Type: " << Db[i].bloodType << "\n";
                    cout << "Phone:      " << Db[i].phoneNumber << "\n";
                    if (!Db[i].previousConditions.empty()) {
                        cout << "Conditions: " << Db[i].previousConditions << "\n";
                    }
                    cout << "--------------------------------------------------\n";
                    found = true;
                }
            }
            break;

        case 4: // Search by gender
            cout << "Enter gender to search (M/F): ";
            cin >> searchGender;
            searchGender = toupper(searchGender);
            while (searchGender != 'M' && searchGender != 'F') {
                cout << "Invalid gender. Please enter M or F: ";
                cin >> searchGender;
                searchGender = toupper(searchGender);
            }
            utils::Clear(); // Clear the console screen before displaying results
            cout << "SEARCH RESULTS\n";
            cout << "==================================================\n";
            cout << "Searching "<<searchGender<< " patients:";
            for (int i = 0; i < numpatients; ++i) {
                if (Db[i].gender == searchGender) {
                    cout << "--------------------------------------------------\n";
                    cout << "PATIENT #" << (i + 1) << "\n";
                    cout << "Name:       " << Db[i].name << "\n";
                    cout << "Age:        " << Db[i].age << " years\n";
                    cout << "Gender:     " << Db[i].gender << "\n";
                    cout << "Blood Type: " << Db[i].bloodType << "\n";
                    cout << "Phone:      " << Db[i].phoneNumber << "\n";
                    if (!Db[i].previousConditions.empty()) {
                        cout << "Conditions: " << Db[i].previousConditions << "\n";
                    }
                    cout << "--------------------------------------------------\n";
                    found = true;
                }
            }
            break;
    }

    if (!found) {

        cout << "No patients found matching your criteria.\n";
    }

    cout << "==================================================\n";
    cout << "press Enter to continue...";
    utils::holdc();
    utils::Clear();
}

//  MAIN FUNCTION
int main() {
    utils::Clear();
    int numpatients = 0;
    Patient Db[MAX_PATIENTS];

    cout << "WELCOME TO THE PATIENT MANAGEMENT SYSTEM!\n";
    cout << "==========================================\n";

    int choice;
    do {
        // Clear();
        cout << "MAIN MENU\n";
        cout << "1. Add a new patient\n";
        cout << "2. View all patients\n";
        cout << "3. Edit patient record\n";
        cout << "4. log patient condition\n";
        cout << "5. Delete patient record\n";
        cout << "6. clear database\n";
        cout << "7. Search patients\n";
        cout << "0. Exit\n";
        cout << "Enter your choice:> ";

        while (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }

        switch (choice) {
            case 1:
                addPatient(Db,numpatients);
                break;
            case 2:
                utils::Clear();
                utils::listPatients(Db,numpatients);
                cout << "press Enter to continue..."<<endl;
                utils::holdc(); // Wait for user input before clearing the screen
                utils::Clear();
                break;
            case 3:
                editpatient(Db,numpatients);
                break;
            case 4:
                logpatientcondition(Db,numpatients);
                break;
            case 5:
                deletepatient(Db,numpatients);
                break;
            case 6:
                clearDatabase(Db,numpatients);
                break;
            case 7:
                searchPatients(Db, numpatients);
                break;
            case 0:
                utils::Clear();
                cout << "Program Closed... Goodbye!\n";
                cout << "--------------------------------------------------\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                cout << "press Enter to continue...";
                utils::holdc(); // Wait for user input before clearing the screen
        }
    } while (choice != 0);

    return 0;
}