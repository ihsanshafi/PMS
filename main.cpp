#include <iostream>
#include <list>
#include <string>

using namespace std;

int main() {
    list <int> patients = {};
    bool running = true;
    // class Person {
    //     public: 
    //         string Name;
    //         int Age;
    //         float Weight;
    //     // void fetch(){
    //     //     cout<<"Age";
    //     // }
    //   };
    struct Person {
        string name;
        int age;
        int weight;
    };

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
            Person patients;
            patients.Name = name;
            patients.Age = age;
            patients.Weight = weight;
            cout<<"patient "<<name<<" added!"<<endl;
        }
    }
    return 0;
}