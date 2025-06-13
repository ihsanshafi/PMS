#include <iostream>
#include <list>
#include <string>
#include <conio.h>

using namespace std;
//  Define the Patient structure
struct Patient {
    string name;
    int age;
    int weight;
    // int height; // Uncomment if height is needed
    // string diagnosis; // Uncomment if diagnosis is needed
    // string phone_number; // Uncomment if phone number is needed
};

const int MAX_PATIENTS = 100; // Maximum number of patients in the database

// console clear function
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
// list patients function
void listPatients(const Patient Db[],int numpatients){
    Clear(); // Clear the console screen
    if (numpatients > 0) {
        cout << "All Patients:\n";
        cout << numpatients<<endl;
        for (int i = 0; i < numpatients; ++i) {
            cout << "patient " << (i + 1) << ":\n";
            cout << "Name: " << Db[i].name << "\n";
            cout << "age: " << Db[i].age << "\n";
            cout << "weight: " << Db[i].weight << "\n";
        }
    } else {
        cout << numpatients<<endl;
        cout << "Database is empty.\n";
    }
}
//  ADD PATIENT FUNCTION
void addPatient(Patient Db[], int& numpatients){
    Clear(); // Clear the console screen
    Patient newpatient; // Create a new patient object
    string name;
    float age, weight;
    cout << "Add a new patient:\n";
    cout << "-------------------------\n";
    cout << "Enter patient name: ";
    cin.ignore(); // Clear the newline character from the input buffer
    getline(cin, name); // Use getline to allow spaces in the name
    cout << "Enter patient age: ";
    cin >> age;
    cout << "Enter patient weight (kg): ";
    cin.ignore(); // Clear the newline character from the input buffer
    cin >> weight; // Use cin to read the weight
    // Check if the input is valid
    // if (age < 0 || weight < 0) {
    //     cout << "Invalid input. Age and weight must be non-negative.\n";
    //     return; // Exit the function if input is invalid
    // }
    newpatient.name = name;
    newpatient.age = age;
    newpatient.weight = weight;
    Db[numpatients++] = newpatient;


    Clear(); // Clear the console screen after adding the patient
    cout << "patient " << name << " added successfully.\n";
};


// EDIT PATIENT FUNCTION
void editpatient(Patient Db[],int numpatients){
    Clear(); // Clear the console screen
    cout << "Patients in system:\n";
    for (int i = 0; i < numpatients; ++i) {
        cout << "patient " << (i + 1) << ":\n";
        cout << "   Name: " << Db[i].name << "\n";
        cout << "   Age: " << Db[i].age << "\n";
        cout << "   Weight: " << Db[i].weight << "\n";
        cout << "-------------------------\n";
    }
    if (numpatients > 0) {
        int patientId;
        cout << "Enter the id of the patient to edit (1 to " << numpatients << "): ";
        cin >> patientId;
        Clear(); // Clear the console screen before editing
        string new_name;
        float new_age, new_weight;
        if (patientId >= 1 && patientId <= numpatients) {
            cout << "-------------------------\n";
            cout << "Editing patient " << patientId << ":\n"; 
            cout << "       previous_Name: " << Db[patientId - 1].name << "\n";
            cout << "       Previous age: " << Db[patientId - 1].age << "\n";
            cout << "       previous weight: " << Db[patientId - 1].weight << "\n";

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
    Clear(); // Clear the console screen
    if (numpatients > 0) {
        int patientId;
        cout << "Enter the index of the patient to delete (1 to " << numpatients << "): ";
        cin >> patientId;

        if (patientId >= 1 && patientId <= numpatients) {
            for (int i = patientId - 1; i < numpatients - 1; ++i) {
                Db[i] = Db[i + 1];
            }
            --numpatients;
            cout << "patient deleted successfully.\n";
        } else {
            cout << "Invalid patient id.\n";
        }
    } else {
        cout << "Database is empty. Cannot delete.\n";
    }
}


int main() {
    Clear();
    int numpatients = 0; // Number of patients currently in the database
    Patient Db[MAX_PATIENTS]; // Array to store patient records
    int choice;
    cout << "WELCOME TO THE PATIENT MANAGEMENT SYSTEM!\n";
    cout << "You can add, view, edit, and delete patient records.\n";
    cout << "Please follow the prompts to manage patient records.\n";
    // Main menu loop
    do {
        cout << "\nPatient Management System MENU:\n";
        cout << "1. Add a patient\n";
        cout << "2. Display All Patients\n";
        cout << "3. Edit a patient record\n";
        cout << "4. Delete a patient record\n";
        cout << "0. Exit\n";
        cout<<":>";
        cin >> choice;

        switch (choice) {
            case 1:
                addPatient(Db,numpatients);
                break;
            case 2:
                listPatients (Db,numpatients);
                break;
            case 3:
                editpatient(Db,numpatients);
                break;
            case 4:
                deletepatient(Db, numpatients);
                break;
            case 0:
                Clear(); // Clear the console screen before exiting
                cout << "Program closed. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
        }
    } while (choice != 0);

    return 0;
}