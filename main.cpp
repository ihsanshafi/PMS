#include <iostream>
#include <list>
#include <string>

using namespace std;

int main() {
    list <int> patients = {};
    bool running = true;

    while(running){
        cout <<"1. Add Patient\n2. View Patients\n3. Edit Patient \n4. Remove Patient\n5. Exit\n" ;

        int menu_input;
        cout<<":>";
        cin >> menu_input;

        if(menu_input == 1){
            string name;
            float age, weight;

            cout<<"Enter patient name:";
            cin>> name;

            cout <<"Enter patient age:";
            cin>> age;

            cout <<"Enter patient weight(kg):";
            cin>> weight;

            patients.

        }
    }

    return 0;
}