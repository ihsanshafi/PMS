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
//         Set i = 1
//         For each patient in Db:
//             Print "PATIENT #" + i
//             Increment i
//             Print patient details (name, age, weight, gender, blood type, phone number, registry date)
//     Else:
//         Print "Database is empty."
//     Wait for key press
//     Clear screen

// registerPatient(Db: vector of Patient):
//     Loop:
//         Clear screen
//         Create newPatient: Patient struct
//         Print header "=============== REGISTER NEW PATIENT ================\n"
//         Print info message "Enter '0' at any point to cancel and go back to the main menu."
//         Print "please fill in the patient details below:\n"
//
//         Name input---------------------------------------------------------------------------------
//         Loop:
//             Print "Enter Patient name: "
//             If there's a newline character in the input buffer:
//                 Consume it
//             Read name using getline
//             If name is "0":
//                 Clear screen
//                 Return
//             If name is not empty:
//                 Break loop
//             Print error message "Name cannot be empty. Please try again."
//         newPatient.name = name
//
//         Phone Number input-------------------------------------------------------------------------
//         Loop:
//             Print "Enter phone number: "
//             If there's a newline character in the input buffer:
//                 Consume it
//             Read phoneNumber using getline
//             If phoneNumber is "0":
//                 Clear screen
//                 Return
//             If isValidPhoneNumber(phoneNumber) is true:
//                 Break loop
//             Print error message "Invalid phone number. Please try again."
//         newPatient.phoneNumber = phoneNumber
//
//         Check for duplicate before adding-----------------------------------------------------------
//         If isPatientExists(Db, newPatient) is true:
//             Clear screen
//             Print "==================================================\n";
//             Print error message "Duplicate entry detected."
//             Print "Patient already exists in the database!\n";
//             Print "Please check the name and phone number.\n";
//             Print "==================================================\n";
//             Print "press Enter to continue...";
//             Wait for key press
//             Clear screen
//             Continue loop
//
//         Age input-----------------------------------------------------------------------------------
//         Loop:
//             Print "Enter Patient age: "
//             Read age
//             If reading age fails OR age is less than 0:
//                 Clear error flags on cin
//                 Discard the remaining input in the line
//                 Print error message "Invalid age. Please enter a positive number or '0' to cancel."
//                 Continue loop
//             If age is 0:
//                 Clear screen
//                 Return
//             Consume any remaining input in the line
//             Break loop
//         newPatient.age = age
//
//         Weight input---------------------------------------------------------------------------------
//         Loop:
//             Print "Enter patient weight (kg): "
//             Read weight
//             If reading weight fails OR weight is less than 0:
//                 Clear error flags on cin
//                 Discard the remaining input in the line
//                 Print error message "Invalid weight. Please enter a positive number or '0' to cancel."
//                 Continue loop
//             If weight is 0:
//                 Clear screen
//                 Return
//             Consume any remaining input in the line
//             Break loop
//         newPatient.weight = weight
//
//         Gender input---------------------------------------------------------------------------------
//         Loop:
//             Print "Enter gender (M/F): "
//             Read gender
//             Convert gender to uppercase
//             If gender is "0":
//                 Clear screen
//                 Return
//             If gender is 'M' or gender is 'F':
//                 Break loop
//             Print error message "Invalid gender. Please enter M or F."
//         newPatient.gender = gender
//
//         Blood Type input------------------------------------------------------------------------------
//         Loop:
//             Print "Enter blood type (A+, A-, B+, B-, AB+, AB-, O+, O-): "
//             Read bloodType
//             Convert bloodType to uppercase
//             If bloodType is "0":
//                 Clear screen
//                 Return
//             If isValidBloodType(bloodType) is true:
//                 Break loop
//             Print error message "Invalid blood type. Please try again."
//         newPatient.bloodType = bloodType
//
//         Medical History input-------------------------------------------------------------------------
//         Loop:
//             Print "Enter Medical History & Examination(Patient Symptoms or Previous Diagnosis): "
//             If there's a newline character in the input buffer:
//                 Consume it
//             Read medicalHistory using getline
//             If medicalHistory is "0":
//                 Clear screen
//                 Return
//             If medicalHistory is not empty:
//                 Break loop
//             Print error message "Medical History cannot be empty. Please try again."
//         newPatient.medicalHistory = medicalHistory
//
//         newPatient.progressLog = ""   -- Initialize Progress logs as empty
//
//         newPatient.timestamp = current time -- Set the registration timestamp
//
//         Clear screen
//         Add newPatient to Db (Db.push_back(newPatient))
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
//     Display patient details
//     Loop:
//         Input progress log (allow '0' to cancel)
//         If input is '0':
//             Clear screen
//             return
//         Append current date and time to log
//         Append log to Db[patientIndex].progressLog
//         Ask if user wants to add another log (Y/N)
//         If user enters 'N':
//             Break loop
//     Ask if user wants to save logs (Y/N)
//     If user enters 'Y':
//         Save database to file
//         Print "Medical Progress logged successfully."
//     Else:
//         Print "Logging canceled. No changes were made."
//     Wait for key press
//     Clear screen

// clearLogs(Db: vector of Patient, patientIndex: int):
//     Clear screen
//     Print header "CLEAR PATIENT LOGS"
//     If patientIndex is invalid:
//         Print "System Error: Invalid patient index."
//         Wait for key press
//         Clear screen
//         return
//     Confirm clear logs with user (Y/N)
//     If user enters 'Y':
//         Clear Db[patientIndex].progressLog (Db[patientIndex].progressLog = "")
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
//         Remove patient from Db (Db.erase(Db.begin() + patientIndex))
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
//     Loop:
//         Display current patient details
//         Ask user to select item to edit (1-7, 0 to cancel)
//         If user enters '0':
//             Clear screen
//             return
//         Switch based on user choice:
//             Case 1 (Name): Input new name, update Db[patientIndex].name
//             Case 2 (Age): Input new age, update Db[patientIndex].age
//             Case 3 (Gender): Input new gender, update Db[patientIndex].gender
//             Case 4 (Blood Type): Input new blood type, update Db[patientIndex].bloodType
//             Case 5 (Weight): Input new weight, update Db[patientIndex].weight
//             Case 6 (Phone Number): Input new phone number, update Db[patientIndex].phoneNumber
//             Case 7 (Medical History): Input new medical history, update Db[patientIndex].medicalHistory
//         Save database to file
//         Print "Patient record updated successfully."
//         Wait for key press
//         Clear screen

// displayPatientProfile(Db: vector of Patient, patientIndex: int):
//     Clear screen
//     If patientIndex is invalid:
//         Print "System Error: Invalid patient index."
//         Wait for key press
//         return
//     Loop:
//         Display patient details (name, age, gender, blood type, weight, phone number, registry date, medical history, progress logs)
//         Display actions (log progress, clear logs, edit profile, delete profile, back to main menu)
//         Input user choice
//         Switch based on user choice:
//             Case 1: Call logPatientProgress(Db, patientIndex)
//             Case 2: Call clearLogs(Db, patientIndex)
//             Case 3: Call editPatient(Db, patientIndex)
//             Case 4: Call deletePatient(Db, patientIndex) and return
//             Case 0: Clear screen and break loop
//             Default: Print "Invalid input."
//     Return to previous menu

// searchPatients(Db: vector of Patient):
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
//             Loop:
//                 Clear screen
//                 Input patient name to search
//                 If input is empty:
//                     Print "Search string cannot be empty."
//                     Continue loop
//                 If input is "0":
//                     Clear screen
//                     return
//                 Convert search string to lowercase
//                 Create matchIndices: vector to store indices of matching patients
//                 For each patient in Db:
//                     Convert patient.name to lowercase
//                     If patient.name contains search string:
//                         Add patient's index to matchIndices
//                         Display matching patient details
//                 If matchIndices is empty:
//                     Print "No patients found with the name containing search string."
//                     Ask user to retry or cancel
//                     If user cancels:
//                         Clear screen
//                         return
//                     Continue loop
//                 Break loop
//             Ask user to select a patient from search results
//             Input user choice
//             If user cancels:
//                 Clear screen
//                 return
//             Call displayPatientProfile(Db, matchIndices[selected - 1])
//             Return
//         Case 2 (Phone Number):
//             Similar logic as search by name, but search by phone number after normalizing it
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
//             Clear Db (Db.clear())
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

// ================== SYSTEM ACTIONS MENU FUNCTION ==================
// systemActions():
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

// ================== MAIN MENU FUNCTION ==================
// mainMenu():
//     Loop:
//         Display main menu options (search patient records, register a new patient, list all patient records, system actions, info, exit)
//         Input user choice
//         Switch based on user choice:
//             Case 1: Call System::searchPatients(Db)
//             Case 2: Call System::registerPatient(Db)
//             Case 3: Call System::listAllPatients(Db)
//             Case 4: Call systemActions()
//             Case 5: Call System::info()
//             Case 0: Clear screen, print "Program Closed... Goodbye!" and break loop
//             Default: Print "Invalid choice."
//         Wait for key press
//         Clear screen

// ================== MAIN FUNCTION ==================
// main():
//     Clear screen
//     Print "WELCOME TO THE PATIENT RECORDS MANAGEMENT SYSTEM!"
//     Call utils::loadDb(Db)
//     Call mainMenu()
//     Return 0