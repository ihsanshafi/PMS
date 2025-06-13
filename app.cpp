#include <iostream> // for input/output operations
#include <list> // for list operations
#include <string> // for string operations
#if defined _WIN32 
    #include <conio.h> // for getch()
#endif
#include <cctype> // for toupper()
#include <limits> // for numeric_limits
using namespace std;
//  Define the Patient structure
struct Patient {
    string name;
    int age;
    int weight;
    char gender;       // M/F/O (Male/Female/Other)
    string phoneNumber;
    string bloodType;
    string previousConditions; // List of previous conditions
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
    // This function waits for the user to press any key before continuing
    // It is useful for pausing the program to allow the user to read messages
    // It clears the input buffer to avoid any leftover characters affecting the next input
    // It uses std::numeric_limits to ensure it reads until the end of the line
    // It uses cin.get() to wait for a single key press
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

}

// FUNCTION PROTOTYPES
// LIST PATIENTS FUNCTION  Displays all patients, used in the other functions
void listPatients(const Patient Db[], int numpatients) {
    if (numpatients > 0) {
        cout << "ALL PATIENTS (" << numpatients << ")\n";
        cout << "==========================================\n";
        for (int i = 0; i < numpatients; ++i) {
            cout << "PATIENT #" << (i + 1) << "\n";
            cout << "Name:       " << Db[i].name << "\n";
            cout << "Age:        " << Db[i].age << " years\n";
            cout << "Weight:     " << Db[i].weight << " kg\n";
            cout << "Gender:     " << Db[i].gender << "\n";
            cout << "Blood Type: " << Db[i].bloodType << "\n";
            cout << "PhoneNum:   " << Db[i].phoneNumber << "\n";
            cout << "==========================================\n";
        }
    } else {
        cout << "Database is empty.\n";
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
    cout << "--------------------------------------------------\n";

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
    cout << "Enter gender (M/F/O): ";
    cin >> newPatient.gender;
    newPatient.gender = toupper(newPatient.gender);
    while (newPatient.gender != 'M' && newPatient.gender != 'F' && newPatient.gender != 'O') {
        cout << "Invalid gender. Please enter M, F, or O: ";
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
    
    // Add to database
    Db[numpatients++] = newPatient;

    utils::Clear();
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
    cout << "--------------------------------------------------\n";
    if (numpatients == 0) {
        cout << "Database is empty. Cannot edit.\n";
        cout << "press Enter to continue...";
        utils::holdc(); // Wait for user input before clearing the screen
        utils::Clear();
        return;
    }// Clear the console screen
    listPatients(Db, numpatients); // List all patients before editing
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
        cout << "Enter new gender (M/F/O): ";
        cin >> newGender; // Use cin to read
        newGender = toupper(newGender); // Convert to uppercase
        while (newGender != 'M' && newGender != 'F' && newGender != 'O') {
            cout << "Invalid input. Please enter M, F, or O: ";
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
    cout << "--------------------------------------------------\n";

    if (numpatients == 0) {
        cout << "Database is empty. Cannot log condition.\n";
        cout << "press Enter to continue...";
        utils::holdc(); // Wait for user input before clearing the screen
        utils::Clear();
        return;
    }

    listPatients(Db, numpatients);

    int patientId;
    cout << "Enter the ID of the patient to log condition (1 to " << numpatients << "): ";
    while (!(cin >> patientId) || patientId < 1 || patientId > numpatients) {
        cout << "Invalid ID. Please enter a number between 1 and " << numpatients << ": ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    utils::Clear(); // Clear the console screen before logging condition
    cout << "--------------------------------------------------\n";
    cout << "Logging condition for patient #" << patientId << ": ";
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

    listPatients(Db, numpatients);

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
                listPatients(Db,numpatients);
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
            case 0:
                utils::Clear();
                cout << "Exiting the program...\n";
                cout << "Thank you for using the Patient Management System!\n";
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