# Patient Records Management System - Version 2.0

## Table of Contents
1. [System Overview](#system-overview)
2. [Data Structures](#data-structures)
3. [Utility Functions](#utility-functions)
4. [System Functions](#system-functions)
5. [Menu System](#menu-system)
6. [Main Function](#main-function)
7. [File Operations](#file-operations)
8. [Error Handling](#error-handling)
9. [Platform Compatibility](#platform-compatibility)
10. [Usage Examples](#usage-examples)

## System Overview <a name="system-overview"></a>

The Patient Records Management System is a console-based application designed to help healthcare professionals manage patient records efficiently. Key features include:

- Patient registration and profile management
- Comprehensive patient search functionality
- Medical condition logging
- Database management
- Cross-platform compatibility

The system uses a file-based database to persist patient records between sessions and provides a color-coded interface for better user experience.

## Data Structures <a name="data-structures"></a>

### Patient Structure
```cpp
struct Patient {
    string name;                // Patient's full name
    int age;                    // Patient's age in years
    int weight;                 // Patient's weight in kg
    char gender;                // M/F (Male/Female)
    string phoneNumber;         // Contact number
    string bloodType;           // Blood type (A+, A-, etc.)
    string previousConditions;  // List of previous medical conditions
    time_t timestamp;           // Registration date/time
};
```

### Global Variables
- `FILE_NAME`: Constant string for database filename ("patient_db.txt")
- `MAX_PATIENTS`: Maximum capacity of the system (1000 patients)
- `numpatients`: Current number of registered patients
- `Db`: Array of Patient structures serving as the main database

## Utility Functions <a name="utility-functions"></a>

### Screen Management
- `Clear()`: Clears the console screen (platform-specific implementation)
- `holdc()`: Pauses execution until user presses a key

### Validation Functions
- `isValidPhoneNumber()`: Validates phone number format
- `isValidBloodType()`: Checks if blood type is valid (A+, A-, etc.)
- `isPatientExists()`: Checks for duplicate patient entries

### Messaging Functions
- `errMsg()`: Displays error messages in red
- `successMsg()`: Displays success messages in green
- `infoMsg()`: Displays informational messages in blue

### File Operations
- `saveToDb()`: Saves patient records to file
- `loadDb()`: Loads patient records from file

## System Functions <a name="system-functions"></a>

### Patient Management
- `listAllPatients()`: Displays all registered patients
- `addPatient()`: Registers a new patient
- `editPatient()`: Modifies existing patient records
- `deletePatient()`: Removes a patient from the system
- `findPatients()`: Searches patients by name or phone number

### Medical Records
- `logpatientcondition()`: Logs medical conditions for a patient
- `clearLogs()`: Clears all medical logs for a patient

### System Operations
- `clearDatabase()`: Resets the entire database
- `info()`: Displays system information and credits

## Menu System <a name="menu-system"></a>

### Main Menu
1. Manage Patient Records
2. Register a New Patient
3. Manage System Database
4. Info
0. Exit

### Manage Patient Records Submenu
1. List All Patients
2. Search Patient by Name
3. Search Patient by Phone Number
0. Back to Main Menu

### System Database Submenu
1. Clear Database
2. Change Maximum Patient Capacity (not implemented)
0. Back to Main Menu

## Main Function <a name="main-function"></a>

The program entry point:
1. Displays welcome message
2. Loads existing database
3. Enters main menu loop
4. Handles program termination

## File Operations <a name="file-operations"></a>

### Database File Format
The system uses a text file (`patient_db.txt`) with the following structure:
1. First line: Number of patients
2. Subsequent lines: Patient records separated by "---" delimiters

Each patient record contains:
- Name
- Age
- Weight
- Gender
- Phone number
- Blood type
- Timestamp
- Previous conditions (may span multiple lines)

## Error Handling <a name="error-handling"></a>

The system includes comprehensive error handling for:
- Invalid user input
- File operations
- Duplicate patient entries
- Database corruption
- Array bounds checking

## Platform Compatibility <a name="platform-compatibility"></a>

The system detects the operating system and uses appropriate:
- Screen clearing commands
- Key press detection methods
- Path separators

Supported platforms:
- Windows
- Linux
- macOS

## Usage Examples <a name="usage-examples"></a>

### Registering a New Patient
1. Select "Register a New Patient" from main menu
2. Enter patient details (name, age, gender, etc.)
3. System validates inputs and confirms registration

### Searching for a Patient
1. Select "Manage Patient Records" from main menu
2. Choose search method (by name or phone number)
3. Enter search term
4. Select patient from results to view/edit details

### Logging Medical Conditions
1. Find and select a patient
2. Choose "Log conditions" option
3. Enter condition details
4. Confirm to save

### Database Maintenance
1. Select "Manage System Database" from main menu
2. View system statistics
3. Choose "Clear Database" to reset (with confirmation)

## Conclusion

This Patient Records Management System provides a comprehensive solution for managing healthcare records with robust data validation, intuitive menus, and persistent storage. The modular design allows for future expansion and the platform-independent implementation ensures wide compatibility.
