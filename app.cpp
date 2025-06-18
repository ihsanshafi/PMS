// PATIENT RECORDS MANAGEMENT SYSTEM

#include <iostream> // for input/output operations
#include <list> // for list operations
#include <string> // for string operations
#include <algorithm> // for transform function
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

// System-wide data
const int MAX_PATIENTS = 100; // Maximum number of patients in the database
int numpatients = 0;
Patient Db[MAX_PATIENTS];


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
    // Function to list all patients in the database
    void listPatients(const Patient Db[], int numpatients) {
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
}

// log patient condition
void logpatientcondition(Patient Db[], int patientIndex) {
    utils::Clear();
    cout << "================= LOG PATIENT CONDITION ==================\n";

    if (patientIndex < 0 || patientIndex >= numpatients || Db[patientIndex].name.empty()) {
        cout << "Invalid patient index.\n";
        cout << "Press Enter to continue...";
        utils::holdc(); // Wait for user input before clearing the screen
        utils::Clear();
        return; // Return early if the index is invalid
    }


    utils::Clear(); // Clear the console screen before logging condition
    cout << "==================================================\n";
    cout << "Logging condition for patient #" << patientIndex << ": " << "\n";
    cout << "Name:          " << Db[patientIndex].name << "\n";
    cout << "Age:           " << Db[patientIndex].age << " years\n";
    cout << "Weight:        " << Db[patientIndex].weight << " kg\n";
    cout << "Blood Type:    " << Db[patientIndex].bloodType << "\n\n";
    cout << "--------------------------------------------------\n";
    cout << Db[patientIndex].name << "'s previous conditions: \n";
    cout << (Db[patientIndex].previousConditions.empty() ? "None" : Db[patientIndex].previousConditions) << "\n"; // Display previous conditions if any
    cout << "==================================================\n";

    string condition;
    cout << "Enter the condition to log for " << Db[patientIndex].name << ": ";
    cin.ignore(); // Clear the input buffer before getline
    getline(cin, condition);
    while (condition.empty()) {
        cout << "Condition cannot be empty. Please enter a valid condition: ";
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
    Db[patientIndex].previousConditions += (Db[patientIndex].previousConditions.empty() ? std::string("") : std::string("\n")) + ">> " + conditionWithDate;
    
    utils::Clear(); // Clear the console screen after logging condition
    cout << "==================================================\n";
    cout << "Condition logged successfully for " << Db[patientIndex].name<< ".\n";
    cout << "--------------------------------------------------\n";
    cout << "Updated conditions for " << Db[patientIndex].name << ": \n";
    cout << Db[patientIndex].previousConditions << "\n"; // Display updated conditions
    cout << "==================================================\n";
    cout << "press Enter to continue...";
    utils::holdc(); // Wait for user input before clearing the screen
    utils::Clear();
}

// Function to clear logs for a specific patient
void clearLogs(Patient Db[], int& patientIndex) {
    utils::Clear(); // Clear the console screen before clearing logs
    if (patientIndex < 0 || patientIndex >= numpatients || Db[patientIndex].name.empty()) {
        cout << "Invalid patient index.\n";
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
        cout << "Clearing logs canceled.\n";
        cout << "==================================================\n";
        cout << "Press Enter to continue...";
        utils::holdc(); // Wait for user input before clearing the screen
        utils::Clear(); // Clear the console screen after displaying the message
        return; // Return early if the user cancels
    }
    Db[patientIndex].previousConditions.clear(); // Clear the previous conditions
    utils::Clear(); // Clear the console screen after clearing logs
    cout << "==================================================\n";
    cout << "All previous conditions for " << Db[patientIndex].name << " have been cleared.\n";
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
    char confirmDelete;
    cin >> confirmDelete;
    confirmDelete = toupper(confirmDelete); // Convert to uppercase for consistency
    if (confirmDelete != 'Y') {
        utils::Clear(); // Clear the console screen before displaying the message
        cout << "==================================================\n";
        cout << "Deletion canceled.\n";
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
    cout << "==================================================\n";
    cout << "Patient record deleted successfully.\n";
    cout << "==================================================\n";
    cout << "Press Enter to continue...";
    utils::holdc(); // Wait for user input before clearing the screen
    utils::Clear(); // Clear the console screen after deleting a patient
}

// Function to add a new patient to the database
void editPatient(Patient Db[], int& patientIndex) {
    utils::Clear(); // Clear the console screen before editing
    cout << "EDIT PATIENT RECORD\n";
    cout << "==================================================\n";
    const Patient& patient = Db[patientIndex];
    cout << "=================== PREVIOUS DETAILS ==================\n";
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
    cout << "Enter new details for the patient:\n";
    // Prompt for new details
    string new_name, new_bloodType, new_phoneNumber;
    float new_age, new_weight;
    char newGender;

    // name
    cout << "Enter new patient name: ";
    cin.ignore(); // Clear the newline character from the input buffer
    getline(cin, new_name); // Use getline to allow spaces in the name
    Db[patientIndex].name = new_name;

    // age
    cout << "Enter new age: ";
    cin.ignore(); // Clear the newline character from the input buffer
    cin >> new_age; // Use cin to read the age
    Db[patientIndex].age = new_age;

    // weight
    cout << "Enter new weight: ";
    cin.ignore(); // Clear the newline character from the input buffer
    cin >> new_weight; // Use cin to read the weight
    Db[patientIndex].weight = new_weight;

    // gender
    cout << "Enter new gender (M/F): ";
    cin >> newGender; // Use cin to read
    newGender = toupper(newGender); // Convert to uppercase
    while (newGender != 'M' && newGender != 'F') {
        cout << "Invalid input. Please enter M or F : ";
        cin >> newGender; // Read again
        newGender = toupper(newGender); // Convert to uppercase
    }
    Db[patientIndex].gender = newGender; // Update

    // blood type
    cout << "Enter new blood type (A+, A-, B+, B-, AB+, AB-, O+, O-): ";
    cin.ignore(); // Clear the newline character from the input buffer
    getline(cin, new_bloodType); // Use getline to allow spaces in the blood type and convert to uppercase
    for (char &c : new_bloodType) c = toupper(c); // Convert to uppercase
    while (!utils::isValidBloodType(new_bloodType)) {
        cout << "Invalid blood type. Please enter a valid type: ";
        getline(cin, new_bloodType);
        for (char &c : new_bloodType) c = toupper(c); // Convert to uppercase
    }
    Db[patientIndex].bloodType = new_bloodType; // Update the blood type

    // phone number
    cout << "Enter new phone number: ";
    cin.ignore(); // Clear the newline character from the input buffer
    getline(cin, new_phoneNumber); // Use getline to allow spaces in the phone number
    while (!utils::isValidPhoneNumber(new_phoneNumber)) {
        cout << "Invalid phone number. Please enter a valid number: ";
        getline(cin, new_phoneNumber);
    }
    Db[patientIndex].phoneNumber = new_phoneNumber; // Update the phone number
    // Display the updated patient record
    cout << "-------------------------\n";
    utils::Clear(); // Clear the console screen after editing
    cout << "===================================================\n";
    cout << "patient "<<Db[patientIndex].name<<"'s record updated successfully.\n";
    cout << "===================================================\n";
    cout << "Updated Patient Details:\n";
    cout << "Name:         " << Db[patientIndex].name << "\n";
    cout << "Age:          " << Db[patientIndex].age << " years\n";
    cout << "weight:       " << Db[patientIndex].weight << " kg\n";
    cout << "gender:       " << Db[patientIndex].gender << "\n";
    cout << "Blood Type:   " << Db[patientIndex].bloodType << "\n";
    cout << "Phone Number: " << Db[patientIndex].phoneNumber << "\n";
    cout << "===================================================\n";
    cout << "Press Enter to continue...";
    utils::holdc(); // Wait for user input before clearing the screen   
    utils::Clear(); // Clear the console screen after displaying the updated record
    return; // Return to the previous menu
}

// Function to display patient details and manage actions
void displayPatientDetails(Patient Db[], int& patientIndex) {
    utils::Clear(); // Clear the console screen before displaying patient details
    if (patientIndex < 0 || patientIndex >= numpatients) {// Check if the index is valid
        cout << "Invalid patient index.\n";
        cout << "Press Enter to continue...";
        utils::holdc(); // Wait for user input before clearing the screen
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
        cout <<"1. log conditions for "<<patient.name <<"\n";
        cout <<"2. Clear "<<patient.name<<"'s condition log"<<"\n";
        cout <<"3. Edit "<<patient.name<< "'s profile"<<"\n";
        cout <<"4. Delete "<<patient.name<<"'s profile from the system"<<"\n";
        cout <<"0. Back to Manage menu"<< "\n";
        cout <<"Enter your choice:> ";

        while (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number: ";
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
    while (true){
        utils::Clear(); // Clear the console screen before searching
        cout << "=============== SEARCH PATIENTS ================\n";
        bool found = false;
        if (numpatients == 0) {
            cout << "Database is empty. Cannot search.\n";
            cout << "==================================================\n";
            cout << "Press Enter to continue...";
            utils::holdc(); // Wait for user input before clearing the screen
            utils::Clear();
            return; // Return early if no patients are present
        }
        string searchStr = ""; // Initialize searchStr to an empty string
        string normalizedSearch;// For phone number search, we will normalize the input
        int choice;
        int patientIndex;
        int matchingPatients = 0; // Count the number of matching patients
        switch (searchType) {
            case 1: // Search by name
                cout << "Enter patient name to search: ";
                cin.ignore(); // Clear the newline character from the input buffer
                getline(cin, searchStr);
                if (searchStr.empty()) {
                    cout << "Search string cannot be empty. Please enter a valid name.\n";
                    cout << "Press Enter to continue...\n";
                    utils::holdc(); // Wait for user input before clearing the screen
                    utils::Clear(); // Clear the console screen after displaying the message
                    continue; // Continue to the next iteration of the loop
                }
                // Convert searchStr to lowercase for case-insensitive comparison
                for (char &c : searchStr) c = tolower(c);
                utils::Clear(); // Clear the console screen before displaying results
                cout << "================== SEARCH RESULTS ==================\n";
                cout << "Searching for patients with name containing: " << searchStr << "\n";

                // Loop through the database to find matching patients
                for (int i = 0; i < numpatients; ++i) {
                    string patientNameLower = Db[i].name;
                    // Convert patient name to lowercase for case-insensitive comparison
                    for (char &c : patientNameLower) c = tolower(c);
                    if (patientNameLower.find(searchStr) != string::npos) {
                        found = true; // Set found to true if a match is found
                        cout << "--------------------------------------------------\n";
                        cout << "PATIENT #" << (i + 1) << "  ";
                        cout << "Name: " << Db[i].name << "   ";
                        cout << "Age: " << Db[i].age << " years  ";
                        cout << "Gender: " << Db[i].gender << "  ";
                        cout << "Blood Type: " << Db[i].bloodType << "  ";
                        cout << "Phone: " << Db[i].phoneNumber << "   \n";
                        cout << "--------------------------------------------------\n";
                        ++matchingPatients; // Increment the count of matching patients
                    }
                }
                if (!found) {
                    cout << "==================================================\n";
                    cout << "No patients found with the name containing: " << searchStr << "\n";
                    cout << "==================================================\n";
                    cout << "Press Enter to continue...\n";
                    utils::holdc(); // Wait for user input before clearing the screen
                    utils::Clear(); // Clear the console screen after displaying results
                    return; // Return early if no patients found
                }
                // Prompt the user to select a patient from the search results
                cout << "==================================================\n";
                cout << "Select Patient from the search results...\n"; // Prompt the user to select a patient from the search results
                cout << "Enter the patient number (1 to " << matchingPatients << ") to view details.\n";
                cout << "Enter '0' to cancel and return to the previous menu.\n"; // Allow user to cancel selection
                cout << "Enter your choice:> ";
                // Input validation for patient selection
                
                while (!(cin >> choice) || choice < 0 || choice > matchingPatients) {
                    cout << "\n Invalid input. Please enter a number between 1 and " << matchingPatients << ": ";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
                if (choice == 0) {
                    utils::Clear();
                    return; // Return to the previous menu
                }
                patientIndex = choice - 1; // Convert to zero-based index
                // Display the details of the selected patient
                displayPatientDetails(Db,patientIndex);

                return; // Return early after displaying patient details
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
                if (normalizedSearch.empty()) {
                    cout<< "Invalid phone number format. Please enter a valid phone number.\n";
                    cout << "Press Enter to continue...\n";
                    utils::holdc(); // Wait for user input before clearing the screen
                    utils::Clear(); // Clear the console screen after displaying the message
                    continue;
                }
                utils::Clear(); // Clear the console screen before displaying results
                cout << "================== SEARCH RESULTS ==================\n";
                cout << "Searching for patients with phone number containing: " << searchStr << "\n";
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
                        found = true; // Set found to true if a match is found
                        cout << "--------------------------------------------------\n";
                        cout << "PATIENT #" << (i + 1) << "  ";
                        cout << "Name: " << Db[i].name << "   ";
                        cout << "Age: " << Db[i].age << " years  ";
                        cout << "Gender: " << Db[i].gender << "  ";
                        cout << "Blood Type: " << Db[i].bloodType << "  ";
                        cout << "Phone: " << Db[i].phoneNumber << "   \n";
                        cout << "--------------------------------------------------\n";
                        ++matchingPatients; // Increment the count of matching patients
                    }
                }
                if (!found) {
                    cout << "==================================================\n";
                    cout << "No patients found with the phone number containing: " << searchStr << "\n";
                    cout << "==================================================\n";
                    cout << "Press Enter to continue...\n";
                    utils::holdc(); // Wait for user input before clearing the screen
                    utils::Clear(); // Clear the console screen after displaying 
                    return; // Return early if no patients found
                }
                // Prompt the user to select a patient from the search results
                cout << "==================================================\n";
                cout << "Select Patient from the search results...\n"; // Prompt the user to select a patient from the search results
                cout << "Enter the patient number (1 to " << matchingPatients << ") to view details.\n";
                cout << "Enter '0' to cancel and return to the previous menu.\n"; // Allow user to cancel selection
                cout << "Enter your choice:> ";
                // Input validation for patient selection

                while (!(cin >> choice) || choice < 0 || choice > matchingPatients) {
                    cout << "\n Invalid input. Please enter a number between 1 and " << matchingPatients << ": ";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
                if (choice == 0) {
                    utils::Clear();
                    return; // Return to the previous menu
                }
                patientIndex = choice - 1; // Convert to zero-based index
                // Display the details of the selected patient
                displayPatientDetails(Db,patientIndex);

                return;
            default:
                cout << "Invalid search type selected.\n";
                cout << "Press Enter to continue...\n";
                utils::holdc(); // Wait for user input before clearing the screen
                utils::Clear(); // Clear the console screen after displaying results
                return ;
        }
    }
}

//  Function to add a new patient to the database
void addPatient(Patient Db[], int& numpatients) {
    while (true){
        utils::Clear();
        if (numpatients >= MAX_PATIENTS) {
            cout << "==================================================\n";
            cout << "Database is full! Cannot add more patients.\n";
            cout << "==================================================\n";
            cout << "press Enter to continue...";
            utils::holdc(); // Wait for user input before clearing the screen
            utils::Clear();
            return;
        }

        Patient newPatient;

        cout << "=============== REGISTER NEW PATIENT ================\n";
        cout << "Enter '0' at any point to cancel and go back to the main menu.\n";
        cout << "-----------------------------------------------------\n";
        
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
            cout << "Name cannot be empty. Please try again.\n";
        }

        // Age input
        while (true) {
            cout << "Enter Patient age: ";
            if (!(cin >> newPatient.age) || newPatient.age < 0) {
                cin.clear();
                cin.ignore(10000, '\n'); // Clear the input buffer
                cout << "Invalid age. Please enter a positive number or '0' to cancel.\n";
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
                cout << "Invalid weight. Please enter a positive number or '0' to cancel.\n";
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
            cout << "Invalid gender. Please enter M or F.\n";
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
            cout << "Invalid blood type. Please try again.\n";
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
            cout << "Invalid phone number. Please try again.\n";
        }

        // Initialize previous health conditions as empty
        newPatient.previousConditions = ""; // Initialize previous conditions as empty

        // Set the registration timestamp
        newPatient.timestamp = time(nullptr);

        // Check for duplicate before adding
        if (utils::isPatientExists(Db, numpatients, newPatient)) {
            utils::Clear();
            cout << "==================================================\n";
            cout << "Patient already exists in the database!\n";
            cout << "Please check the name and phone number.\n";
            cout << "==================================================\n";
            cout << "press Enter to continue...";
            utils::holdc();
            utils::Clear();
            continue; //  Continue the loop to allow re-entry of patient details
        }

        // Add to database
        Db[numpatients++] = newPatient;

        utils::Clear(); // Clear the console screen after adding patient
        cout << "==================================================\n";
        cout << "Patient '" << newPatient.name  << "' Registered successfully.\n";// Display success message
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
    cout << "==================================================\n";
    cout << "press Enter to continue...";
    utils::holdc(); // Wait for user input before clearing the screen
    utils::Clear();
}

// Function to display system information
void info(){
    utils::Clear(); // Clear the console screen before displaying info
    cout << "=============== ABOUT THE SYSTEM ================\n";
    cout << "This is a Patient Management System designed to help\n";
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
    cout << "- Biniyam ------\n";
    cout << "- Soliyana ------\n";
    cout << "==================================================\n";
    cout << "Patient Records Management System.\n";
    cout << "Version: 1.0.0\n"; // Version of the system
    cout << "Written in C++14.\n";
    cout << "==================================================\n";
    cout << "Press Enter to return to the main menu...\n";
    utils::holdc(); // Wait for user input before clearing the screen
    utils::Clear(); // Clear the console screen after displaying info
}

// MENUS
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
            cout << "Invalid input. Please enter a number: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }

        switch (choice) {
            case 1:
                // List all patients
                utils::Clear();
                utils::listPatients(Db, numpatients); // Call the list patients function
                cout << "press Enter to continue..."<<endl;
                utils::holdc(); // Wait for user input before clearing the screen
                utils::Clear(); // Clear the console screen after listing patients
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
// Function to display the system menu and manage database actions
void systemMenu() {
    utils::Clear(); // Clear the console screen before displaying the system menu
    int choice;
    do {
        cout << "=============== SYSTEM DATABASE MANAGEMENT ================\n";
        cout << "======================== DASHBOARD ========================\n";
        cout << "Maximum Capacity: " << MAX_PATIENTS << "\n";
        cout << "Available Slots: " << (MAX_PATIENTS - numpatients) << "\n";
        cout << "Total Patients Registered: " << numpatients << "\n";
        int maleCount = 0, femaleCount = 0;
        for (int i = 0; i < numpatients; ++i) {
            if (Db[i].gender == 'M') ++maleCount;
            else if (Db[i].gender == 'F') ++femaleCount;
        }
        cout << "Number of Male Patients: " << maleCount << "\n";
        cout << "Number of Female Patients: " << femaleCount << "\n";
        cout << "============================================================\n";
        if (numpatients > 0) {
            cout << "Average Age of Patients: ";
            int totalAge = 0;
            for (int i = 0; i < numpatients; ++i) {
                totalAge += Db[i].age;
                }
                cout << (totalAge / numpatients) << " years\n";
                cout << "==========================================================\n";
            }
        if (numpatients > 0) {
            cout << "Latest Patient Registered:\n";
            cout << "Name: " << Db[numpatients - 1].name << "\n";
            cout << "Age: " << Db[numpatients - 1].age << "\n";
            cout << "Gender: " << Db[numpatients - 1].gender << "\n";
            cout << "Blood Type: " << Db[numpatients - 1].bloodType << "\n";
            cout << "Phone Number: " << Db[numpatients - 1].phoneNumber << "\n";
            cout << "Registry Date: ";
            char buffer[80]; 
            tm* timeinfo = localtime(&Db[numpatients - 1].timestamp);
            strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
            cout << buffer << "\n";
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
                clearDatabase(Db, numpatients); // Call the clear database function
                break;
            case 2:
                utils::Clear(); // Clear the console screen before changing capacity
                cout << "=============== CHANGE MAXIMUM PATIENT CAPACITY ================\n";
                cout << "Current Maximum Capacity: " << MAX_PATIENTS << "\n";
                cout << "Enter new maximum capacity (must be greater than current number of patients): ";
                int newCapacity;
                while (!(cin >> newCapacity) || newCapacity <= numpatients) {
                cout << "Invalid input. Please enter a number greater than " << numpatients << ": ";
                cin.clear();
                cin.ignore(10000, '\n');
                }
                cout << "=============================================================\n";
                cout << "Maximum patient capacity updated successfully to " << newCapacity << ".\n";
                cout << "=============================================================\n";
                cout << "Press Enter to continue...";
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
// Function to display the main menu and manage patient records
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
            cout << "Invalid input. Please enter a number: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }

        switch (choice) {
            case 1:
                manageMenu(); // Call the manage menu function
                break;
            case 2:
                addPatient(Db, numpatients); // Call the add patient function
                break;
            case 3:
                systemMenu(); // Call the system menu function
                break;
            case 4:
                info(); // Call the info function to display system information
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

};

//  MAIN FUNCTION
int main() {
    utils::Clear();
    // Display welcome message
    cout << "WELCOME TO THE PATIENT RECORDS MANAGEMENT SYSTEM!\n";
    cout << "\n";
    mainMenu(); // Call the main menu function
    return 0;
}