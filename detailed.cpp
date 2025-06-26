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

// addPatient(Db: vector of Patient):
//     Loop:
//         Clear screen
//         Create newPatient: Patient struct
//         Print header "=============== REGISTER NEW PATIENT ================\n"
//         Print info message "Enter '0' at any point to cancel and go back to the main menu."
//         Print "please fill in the patient details below:\n"
//
//         Loop: // Name input
//             Print "Enter Patient name: "
//             If there are remaining characters in the input buffer:
//                 Clear the input buffer
//             Read name
//             If name is "0":
//                 Clear screen
//                 Return
//             If name is not empty:
//                 Break loop
//             Print error message "Name cannot be empty. Please try again."
//         newPatient.name = name
//         Loop: // Phone Number input
//             Print "Enter phone number: "
//             If there are remaining characters in the input buffer:
//                 Clear the input buffer
//             Read phoneNumber
//             If phoneNumber is "0":
//                 Clear screen
//                 Return
//             If isValidPhoneNumber(phoneNumber) is true:
//                 Break loop
//             Print error message "Invalid phone number. Please try again."
//         newPatient.phoneNumber = phoneNumber
//         If isPatientExists(Db, newPatient) is true:
//             Print "Duplicate entry detected."
//             Wait for key press
//             Clear screen
//             Continue loop
//         Loop: // Age input
//             Print "Enter Patient age: "
//             Read age
//             If age is not a number or age < 0:
//                 Clear input buffer
//                 Print error message "Invalid age. Please enter a positive number or '0' to cancel."
//                 Continue loop
//             If age is 0:
//                 Clear screen
//                 Return
//             Clear the input buffer
//             Break loop
//         newPatient.age = age
//         Loop: // Weight input
//             Print "Enter patient weight (kg): "
//             Read weight
//             If weight is not a number or weight < 0:
//                 Clear input buffer
//                 Print error message "Invalid weight. Please enter a positive number or '0' to cancel."
//                 Continue loop
//             If weight is 0:
//                 Clear screen
//                 Return
//             Clear the input buffer
//             Break loop
//         newPatient.weight = weight
//         Loop: // Gender input
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
//         Loop: // Blood Type input
//             Print "Enter blood type (A+, A-, B+, B-, AB+, AB-, O+, O-): "
//             Read bloodType
//             If bloodType is "0":
//                 Clear screen
//                 Return
//             Convert bloodType to uppercase
//             If isValidBloodType(bloodType) is true:
//                 Break loop
//             Print error message "Invalid blood type. Please try again."
//         newPatient.bloodType = bloodType
//         Loop: // Medical History input
//             Print "Enter Medical History & Examination(Patient Symptoms or Previous Diagnosis): "
//             If there are remaining characters in the input buffer:
//                 Clear the input buffer
//             Read medicalHistory
//             If medicalHistory is "0":
//                 Clear screen
//                 Return
//             If medicalHistory is not empty:
//                 Break loop
//             Print error message "Medical History cannot be empty. Please try again."
//         newPatient.medicalHistory = medicalHistory
//         newPatient.progressLog = ""
//         newPatient.timestamp = current time
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
//     Clear screen
//     Print "Logging Progress for patient #" + patientIndex
//     Print patient details (name, age, weight, blood type)
//     Print "Previous Medical Progress: " + patient.progressLog
//     Loop:
//         Print "Enter the Progress to log for " + patient.name + "(Enter 0 for cancel): "
//         If there are remaining characters in the input buffer:
//             Clear the input buffer
//         Read log
// 	   If log is empty:
// 		  Print error message "Log cannot be empty. Please enter a valid Progress Log."
// 		  Continue loop
//         If log is '0':
//             Clear screen
//             return
//         Get the current date and time
//         Append the log with the log date
//         Append log to newLogs
//         Print "log added successfully."
//         Print "Do you want to add another Log? (Y/N): "
//         Read choice
//         Convert choice to uppercase
//         If choice is not 'Y' and choice is not 'N':
//             Print error message "Invalid input. Please enter Y or N: "
//             Continue loop
//         If choice is not 'Y':
//             Break loop
//     Print "Do you want to save the Logs? (Y/N): "
//     Read choice
//     Convert choice to uppercase
//     If choice is not 'Y' and choice is not 'N':
//         Print error message "Invalid input. Please enter Y or N: "
//     If choice is 'Y':
//         Clear screen
//         Append newLogs to Db[patientIndex].progressLog
//         Save database to file
//         Print "Medical Progress logged successfully for " + patient.name
//         Print "Updated Medical Progress for " + patient.name + ": " + Db[patientIndex].progressLog
//     Else:
//         Clear screen
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
//     Print "Are you sure you want to clear the logs for " + Db[patientIndex].name + "? (Y/N): "
//     Read confirmClear
//     Convert confirmClear to uppercase
//     If confirmClear is not 'Y':
//         Clear screen
//         Print "Clear logs operation canceled."
//         Wait for key press
//         Clear screen
//         return
//     Clear Db[patientIndex].progressLog (Db[patientIndex].progressLog = "")
//     Save database to file
//     Print "Logs cleared successfully for " + patient.name
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
//     Print "Are you sure you want to delete the record of " + Db[patientIndex].name + "? (Y/N): "
//     Read confirmDelete
//     Convert confirmDelete to uppercase
//     If confirmDelete is not 'Y':
//         Clear screen
//         Print "Deletion canceled. No changes were made to the database."
//         Wait for key press
//         Clear screen
//         return
//     Remove patient from Db (Db.erase(Db.begin() + patientIndex))
//     Save database to file
//     Print "Patient Record deleted successfully."
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
//         Ask user to select item to edit (1-7), or enter 0 to cancel)
//         Read choice
//         If choice is not a number or choice < 0 or choice > 7:
//             Print error message "Invalid input. Please enter a number between 0 and 7: "
//             Clear input buffer
//             Continue loop
//         If choice is 0:
//             Clear screen
//             return
//         Switch based on user choice:
//             Case 1 (Name):
//                 Print "Editing Name:_"
//                 Print "Current Name: " + patient.name
//                 Print "Enter new patient name: "
//                 If there are remaining characters in the input buffer:
//                     Clear the input buffer
//                 Read new_name
//                 patient.name = new_name
//                 Break
//             Case 2 (Age):
//                 Print "Editing Age:_"
//                 Print "Current Age: " + patient.age + " years"
//                 Print "Enter new age: "
//                 Loop:
//                     Read new_age
//                     If new_age is not a number or new_age < 0:
//                         Print error message "Invalid input. Please enter a positive number: "
//                         Clear input buffer
//                         Continue loop
//                     Break
//                 patient.age = new_age
//                 Break
//             Case 3 (Gender):
//                 Print "Editing Gender:_"
//                 Print "Current Gender: " + patient.gender
//                 Print "Enter new gender (M/F): "
//                 Read newGender
//                 Convert newGender to uppercase
//                 Loop:
//                     If newGender is not 'M' and newGender is not 'F':
//                         Print error message "Invalid input. Please enter M or F: "
//                         Read newGender
//                         Convert newGender to uppercase
//                         Continue loop
//                     Break
//                 patient.gender = newGender
//                 Break
//             Case 4 (Blood Type):
//                 Print "Editing Blood Type:_"
//                 Print "Current Blood Type: " + patient.bloodType
//                 Print "Enter new blood type (A+, A-, B+, B-, AB+, AB-, O+, O-): "
//                 If there are remaining characters in the input buffer:
//                     Clear the input buffer
//                 Read new_bloodType
//                 Convert new_bloodType to uppercase
//                 Loop:
//                     If isValidBloodType(new_bloodType) is false:
//                         Print error message "Invalid blood type. Please enter a valid type: "
//                         Read new_bloodType
//                         Convert new_bloodType to uppercase
//                         Continue loop
//                     Break
//                 patient.bloodType = new_bloodType
//                 Break
//             Case 5 (Weight):
//                 Print "Editing Weight:_"
//                 Print "Current Weight: " + patient.weight + " kg"
//                 Print "Enter new weight (kg): "
//                 Loop:
//                     Read new_weight
//                     If new_weight is not a number or new_weight < 0:
//                         Print error message "Invalid input. Please enter a positive number: "
//                         Clear input buffer
//                         Continue loop
//                     Break
//                 patient.weight = new_weight
//                 Break
//             Case 6 (Phone Number):
//                 Print "Editing Phone Number:_"
//                 Print "Current Phone Number: " + patient.phoneNumber
//                 Print "Enter new phone number: "
//                 If there are remaining characters in the input buffer:
//                     Clear the input buffer
//                 Read new_phoneNumber
//                 Loop:
//                     If isValidPhoneNumber(new_phoneNumber) is false:
//                         Print error message "Invalid phone number format. Please enter a valid phone number: "
//                         Read new_phoneNumber
//                         Continue loop
//                     Break
//                 patient.phoneNumber = new_phoneNumber
//                 Break
//             Case 7 (Medical History):
//                 Print "Editing Medical History:_"
//                 Print "Current Medical History: " + patient.medicalHistory
//                 Print "Enter edited Medical History: "
//                 If there are remaining characters in the input buffer:
//                     Clear the input buffer
//                 Read new_history
//                 patient.medicalHistory = new_history
//                 Break
//         Clear screen
//         Save database to file
//         Print patient.name + "'s record was updated successfully."
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
//         If input is not a number:
//             Print error message "Invalid input. Please enter a number: "
//             Clear input buffer
//             Continue loop
//         Switch based on user choice:
//             Case 1: Call logPatientProgress(Db, patientIndex)
//             Case 2: Call clearLogs(Db, patientIndex)
//             Case 3: Call editPatient(Db, patientIndex)
//             Case 4: Call deletePatient(Db, patientIndex) and return
//             Case 0: Clear screen and break loop
//             Default: Print "Invalid input."
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
//             Loop:
//                 Clear screen
//                 Print "Enter patient name to search: "
//                 If there are remaining characters in the input buffer:
//                     Clear the input buffer
//                 Read searchStr
//                 If searchStr is empty:
//                     Print "Search string cannot be empty."
//                     Continue loop
//                 If searchStr is "0":
//                     Clear screen
//                     return
//                 Convert search string to lowercase
//                 Clear screen
//                 Print "Searching for patients with name containing: " + searchStr
//                 Create matchIndices: vector to store indices of matching patients
//                 For each patient in Db:
//                     Convert patient.name to lowercase
//                     If patient.name contains searchStr:
//                         Add patient's index to matchIndices
//                         Print patient details (name, age, gender, blood type, phone number)
//         Case 2 (Phone Number):
//             Loop:
//                 Clear screen
//                 Print "Enter phone number to search: "
//                 If there are remaining characters in the input buffer:
//                     Clear the input buffer
//                 Read searchStr
//                 If searchStr is empty:
//                     Print "Search string cannot be empty."
//                     Continue loop
//                 If searchStr is "c" or searchStr is "C":
//                     Clear screen
//                     Return
//                 Normalize the phone number by removing non-digit characters
//                 Clear screen
//                 Print "Searching for patients with phone number containing: " + searchStr
//                 Create matchIndices: vector to store indices of matching patients
//                 For each patient in Db:
//                     Normalize the patient's phone number by removing non-digit characters
//                     If the normalized patient's phone number contains the normalized search string:
//                         Add patient's index to matchIndices
//                         Print patient details (name, age, gender, blood type, phone number)
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
//     Print header "PRMS DASHBOARD"
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
//         Print main menu options (search patient records, register a new patient, list all patient records, admin actions, info, exit)
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