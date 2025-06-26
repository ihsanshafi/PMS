// Pseudo-code for Patient Records Management System (Vector-based)

// ================== STRUCTS ==================
// Patient struct:
//     name: string
//     age: int
//     weight: float
//     gender: char
//     phoneNumber: string
//     bloodType: string
//     medicalHistory: string
//     progressLog: string
//     timestamp: time_t

// ================== GLOBAL VARIABLES ==================
// FILE_NAME: string (constant, "db")
// Db: vector of Patient structs

// ================== UTILITY FUNCTIONS (namespace utils) ==================

// Clear():
//     If Windows: execute "cls" command
//     Else If Linux or Apple: execute "clear" command

// holdc():
//     If Windows: wait for a key press using getch()
//     Else If Linux or Apple: wait for user input using cin.get()

// isValidPhoneNumber(phone: string): boolean
//     If phone is empty: return false
//     If phone length is not 10: return false
//     For each character in phone:
//         If character is not a digit, '+', '-', ' ', '(', or ')':
//             return false
//     return true

// isValidBloodType(bloodType: string): boolean
//     validTypes: array of valid blood types ("A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-")
//     For each type in validTypes:
//         If bloodType equals type: return true
//     return false

// isPatientExists(Db: vector of Patient, newPatient: Patient): boolean
//     For each patient in Db:
//         existingNameLower: lowercase version of patient.name
//         newNameLower: lowercase version of newPatient.name
//         If existingNameLower equals newNameLower AND patient.phoneNumber equals newPatient.phoneNumber:
//             return true
//     return false

// errMsg(msg: string):
//     Print msg to console in red color

// successMsg(msg: string):
//     Print msg to console in green color

// infoMsg(msg: string):
//     Print msg to console in blue color

// saveToDb(Db: vector of Patient):
//     Open file FILE_NAME + ".txt" for writing
//     If file cannot be opened:
//         Print error message
//         return
//     Write Db.size() to file
//     For each patient in Db:
//         Write patient.name, patient.age, patient.weight, patient.gender, patient.phoneNumber, patient.bloodType, patient.medicalHistory, patient.timestamp, patient.progressLog to file
//         Write "---" to file (record separator)
//     Close file
//     Print "System: database updated!"

// loadDb(Db: vector of Patient):
//     Open file FILE_NAME + ".txt" for reading
//     If file cannot be opened:
//         Print "System: No previous database found. Starting fresh!"
//         return
//     Read numpatients from file
//     Resize Db to numpatients
//     For each patient in Db:
//         Read patient.name, patient.age, patient.weight, patient.gender, patient.phoneNumber, patient.bloodType, patient.medicalHistory, patient.timestamp from file
//         Read patient.progressLog from file until "---" is encountered
//     Close file

// ================== SYSTEM FUNCTIONS (namespace System) ==================

// listAllPatients(Db: vector of Patient):
//     Clear screen
//     If Db is not empty:
//         Print header "=========== ALL PATIENTS (Db.size()) ===========\n"
//         For each patient in Db:
//             Print patient details (name, age, weight, gender, blood type, phone number, registry date)
//     Else:
//         Print "Database is empty."
//     Wait for key press
//     Clear screen

// addPatient(Db: vector of Patient):
//     Loop:
//         Clear screen
//         Create newPatient: Patient struct
//         Input patient details (name, age, weight, gender, blood type, phone number, medical history) with validation
//         If user enters '0' at any input, cancel registration and return
//         Add newPatient to Db
//         Save database to file
//         Print "New patient registered successfully."
//         Wait for key press
//         Clear screen
//         Break loop

// logPatientProgress(Db: vector of Patient, patientIndex: int):
//     Clear screen
//     Print header "LOG PATIENT PROGRESS"
//     If patientIndex is invalid:
//         Print "System Error: Invalid patient index."
//         Wait for key press
//         Clear screen
//         return
//     Input progress log (allow '0' to cancel)
//     Append current date and time to log
//     Append log to Db[patientIndex].progressLog
//     Save database to file
//     Print "Medical Progress logged successfully."
//     Wait for key press
//     Clear screen

// clearLogs(Db: vector of Patient, patientIndex: int):
//     Clear screen
//     If patientIndex is invalid:
//         Print "System Error: Invalid patient index."
//         Wait for key press
//         Clear screen
//         return
//     Confirm clear logs with user (Y/N)
//     If user enters 'Y':
//         Clear Db[patientIndex].progressLog
//         Save database to file
//         Print "All previous Medical Progress cleared successfully."
//     Else:
//         Print "Clearing logs canceled. No changes were made."
//     Wait for key press
//     Clear screen

// deletePatient(Db: vector of Patient, patientIndex: int):
//     Clear screen
//     If Db is empty:
//         Print "Database is empty. Cannot delete."
//         Wait for key press
//         Clear screen
//         return
//     If patientIndex is invalid:
//         Print "Invalid patient index."
//         Wait for key press
//         Clear screen
//         return
//     Confirm delete patient with user (Y/N)
//     If user enters 'Y':
//         Remove patient from Db
//         Save database to file
//         Print "Patient Record deleted successfully."
//     Else:
//         Print "Deletion canceled. No changes were made."
//     Wait for key press
//     Clear screen

// editPatient(Db: vector of Patient, patientIndex: int):
//     Clear screen
//     If patientIndex is invalid:
//         Print "System Error: Invalid patient index."
//         Wait for key press
//         Clear screen
//         return
//     Display current patient details
//     Ask user to select item to edit (1-7, 0 to cancel)
//     Switch based on user choice:
//         Case 1 (Name): Input new name, update Db[patientIndex].name
//         Case 2 (Age): Input new age, update Db[patientIndex].age
//         Case 3 (Gender): Input new gender, update Db[patientIndex].gender
//         Case 4 (Blood Type): Input new blood type, update Db[patientIndex].bloodType
//         Case 5 (Weight): Input new weight, update Db[patientIndex].weight
//         Case 6 (Phone Number): Input new phone number, update Db[patientIndex].phoneNumber
//         Case 7 (Medical History): Input new medical history, update Db[patientIndex].medicalHistory
//     Save database to file
//     Print "Patient record updated successfully."
//     Wait for key press
//     Clear screen

// displayPatientProfile(Db: vector of Patient, patientIndex: int):
//     Clear screen
//     If patientIndex is invalid:
//         Print "System Error: Invalid patient index."
//         Wait for key press
//         return
//     Display patient details (name, age, gender, blood type, weight, phone number, registry date, medical history, progress logs)
//     Display actions (log progress, clear logs, edit profile, delete profile, back to main menu)
//     Input user choice
//     Switch based on user choice:
//         Case 1: Call logPatientProgress(Db, patientIndex)
//         Case 2: Call clearLogs(Db, patientIndex)
//         Case 3: Call editPatient(Db, patientIndex)
//         Case 4: Call deletePatient(Db, patientIndex) and return
//         Case 0: Clear screen and break loop
//         Default: Print "Invalid input."
//     Return to previous menu

// findPatients(Db: vector of Patient):
//     Clear screen
//     Print header "SEARCH PATIENTS"
//     If Db is empty:
//         Print "Database is empty. Cannot search."
//         Wait for key press
//         Clear screen
//         return
//     Ask user to choose search type (1: Name, 2: Phone Number, 0: Back to Main Menu)
//     Input user choice
//     Switch based on user choice:
//         Case 1 (Name):
//             Input patient name to search
//             Search for patients with name containing search string
//             Display matching patient details
//         Case 2 (Phone Number):
//             Input patient phone number to search
//             Search for patients with phone number containing search string
//             Display matching patient details
//         Case 0:
//             Clear screen
//             Return

// clearDatabase(Db: vector of Patient):
//     Clear screen
//     Print header "CLEAR DATABASE"
//     If Db is empty:
//         Print "Database is already empty..."
//     Else:
//         Confirm clear database with user (Y/N)
//         If user enters 'Y':
//             Clear Db
//             Save database to file
//             Print "Database cleared successfully."
//         Else:
//             Print "Database clearing canceled."
//     Wait for key press
//     Clear screen

// dashboard():
//     Clear screen
//     Print system statistics (total patients registered, number of male/female patients, average age, average weight)
//     Wait for key press
//     Clear screen

// info():
//     Clear screen
//     Print system information (description, features, developers, version)
//     Wait for key press
//     Clear screen

// adminMenu():
//     Loop:
//         Clear screen
//         Display available actions (show system stats, clear database, back to main menu)
//         Input user choice
//         Switch based on user choice:
//             Case 1: Call System::dashboard()
//             Case 2: Call System::clearDatabase(Db)
//             Case 0: Clear screen and break loop
//             Default: Print "Invalid choice."
//         Wait for key press
//         Clear screen

// mainMenu():
//     Loop:
//         Clear screen
//         Display main menu options (search patient records, register a new patient, list all patient records, admin actions, info, exit)
//         Input user choice
//         Switch based on user choice:
//             Case 1: Call System::findPatients(Db)
//             Case 2: Call System::addPatient(Db)
//             Case 3: Call System::listAllPatients(Db)
//             Case 4: Call adminMenu()
//             Case 5: Call System::info()
//             Case 0: Clear screen, print "Program Closed... Goodbye!" and break loop
//             Default: Print "Invalid choice."
//         Wait for key press
//         Clear screen

// main():
//     Clear screen
//     Print "WELCOME TO THE PATIENT RECORDS MANAGEMENT SYSTEM!"
//     Call utils::loadDb(Db)
//     Call mainMenu()
//     Return 0