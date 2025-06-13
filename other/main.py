from datetime import datetime

patients=[]

#menu_input = input(":>")
menu = "1. Add Patient\n2. View Patients\n3. Edit Patient \n4. Remove Patient\n5. Exit\n"

running = True
while running:
    print(menu)
    menu_input = input(":> ")
    date = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    
    if menu_input == "1":
        name = input("Enter patient name: ")
        age = input("Enter patient age: ")
        weight = input("Enter patient weight(kg):")
        patients.append({"name": name, "age": age, "weight": weight+" kg", "registry-date": date})
        print(f"Patient {name} added.")
        
    elif menu_input == "2":
        if not patients:
            print("No patients found.")
            exit = input("press enter to return to main menu")
        else:
            for i, patient in enumerate(patients, start=1):
                print(f"{i}. Name: {patient['name']}, Age: {patient['age']}, weight:{patient['weight']}, registered date:{patient['registry-date']}")
            exit = input("press enter to return to main menu")
                
    elif menu_input == "3":
        index = int(input("Enter patient number to edit: ")) - 1
        if len(patients)> index >= 0:
            name = input("Enter new name: ")
            age = input("Enter new age: ")
            patients[index] = {"name": name, "age": age, "weight":weight}
            print(f"Patient {index + 1} updated.")
        else:
            print("Invalid patient number.")
    
    elif menu_input == "4":
        index = int(input("Enter patient number to delete:")) - 1
        if len(patients)> index >= 0:
            patients.remove(patients[index])
            print(f"Patient{index} deleted successfully")
            exit = input("Press enter to return to main menu")
            
    elif menu_input == "5":
        running = False
    else:
        print("Invalid option. Please try again.")