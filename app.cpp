#include <iostream> // for input/output operations
#include <list> // for list operations
#include <string> // for string operations
#include <limits> // for std::numeric_limits
#include <cctype> // for toupper()
using namespace std;
//  Define the Patient structure
struct Patient {
    string name;
    int age;
    int weight;
    char gender;       // M/F/O (Male/Female/Other)
    string phoneNumber;
};

const int MAX_PATIENTS = 100; // Maximum number of patients in the database

void holdc() {
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get();
}

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
            cout << "PhoneNum:   " << Db[i].phoneNumber << "\n";
            cout << "==========================================\n";
        }
    } else {
        cout << "Database is empty.\n";
    }
}

// ADD PATIENT FUNCTION
void addPatient(Patient Db[], int& numpatients) {
    Clear();
    if (numpatients >= MAX_PATIENTS) {
        cout << "Database is full! Cannot add more patients.\n";
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

    // Phone Number
    cout << "Enter phone number: ";
    cin.ignore();
    getline(cin, newPatient.phoneNumber);
    while (!isValidPhoneNumber(newPatient.phoneNumber)) {
        cout << "Invalid phone number. Please enter a valid number: ";
        getline(cin, newPatient.phoneNumber);
    }

    // Add to database
    Db[numpatients++] = newPatient;
    
    Clear();
    cout << "Patient " << newPatient.name  << " added successfully.\n";
    cout << "Press any key to continue..."<<endl;
    holdc();
}

// EDIT PATIENT FUNCTION
void editpatient(Patient Db[],int numpatients){
    Clear(); // Clear the console screen
    cout << "EDIT PATIENT RECORD\n";
    cout << "--------------------------------------------------\n";
    listPatients(Db, numpatients); // List all patients before editing
    if (numpatients > 0) {
        int patientId;
        cout << "Enter the id of the patient to edit (1 to " << numpatients << "): ";
        cin >> patientId;
        Clear(); // Clear the console screen before editing
        string new_name;
        float new_age, new_weight;
        char newGender;
        if (patientId >= 1 && patientId <= numpatients) {
            cout << "-------------------------\n";
            cout << "Editing patient " << patientId << ":\n"; 
            cout << "       previous_Name: " << Db[patientId - 1].name << "\n";
            cout << "       Previous age: " << Db[patientId - 1].age << "\n";
            cout << "       previous weight: " << Db[patientId - 1].weight << "\n";
            cout << "       previous gender: " << Db[patientId - 1].gender << "\n";
            cout << "       previous phone number: " << Db[patientId - 1].phoneNumber << "\n";
            cout << "-------------------------\n";

            cout << "Enter new patient name: ";
            cin.ignore(); // Clear the newline character from the input buffer
            getline(cin, new_name); // Use getline to allow spaces in the name
            Db[patientId - 1].name = new_name;

            cout << "Enter new age: ";
            cin.ignore(); // Clear the newline character from the input buffer
            cin >> new_age; // Use cin to read the age
            Db[patientId - 1].age = new_age;

            cout << "Enter new weight: ";
            cin.ignore(); // Clear the newline character from the input buffer
            cin >> new_weight; // Use cin to read the weight
            Db[patientId - 1].weight = new_weight;

            cout << "Enter new gender (M/F/O): ";
            cin >> newGender; // Use cin to read
            newGender = toupper(newGender); // Convert to uppercase
            while (newGender != 'M' && newGender != 'F' && newGender != 'O') {
                cout << "Invalid input. Please enter M, F, or O: ";
                cin >> newGender; // Read again
                newGender = toupper(newGender); // Convert to uppercase
            }
            Db[patientId - 1].gender = newGender; // Update

            Clear(); // Clear the console screen after editing
            cout << "patient "<<patientId<<" edited successfully.\n";
        } else {
            cout << "Invalid patient id.\n";
        }
    } else {
        cout << "Db is empty. Cannot edit.\n";
        // cin>>"enter for menu";
    }

}

// DELETE PATIENT FUNCTION
void deletepatient(Patient Db[], int& numpatients) {
    Clear();

    cout << "DELETE A PATIENT RECORD\n";
    cout << "--------------------------------------------------\n";

    if (numpatients == 0) {
        cout << "/nDatabase is empty. Cannot delete.\n";
        cout << "Press any key to continue...";
        holdc();
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
    Clear();
    cout << "CONFIRM DELETION OF PATIENT #" << patientId << "\n";
    cout << "Name: " << Db[patientId - 1].name << "\n";
    cout << "Are you sure? (Y/N): ";
    char confirm;
    cin >> confirm;
    
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
    cout << "Press any key to continue...";
    holdc();
}

//  MAIN FUNCTION
int main() {
    Clear();
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
        cout << "4. Delete patient record\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";

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
                Clear();
                listPatients(Db,numpatients);
                cout << "Press any key to continue..."<<endl;
                holdc();
                break;
            case 3:
                editpatient(Db,numpatients);
                break;
            case 4:
                deletepatient(Db,numpatients);
                break;
            case 0:
                Clear();
                cout << "Exiting program... Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                cout << "Press any key to continue...";
                holdc();
        }
    } while (choice != 0);

    return 0;
}