#include <iostream>
#include <fstream>
#include <string>
#include <array>

using namespace std;

struct Employee{
   string name;
   int nKeysPossessed;
   string keys[5];
};

bool reader(string input_filename, Employee employees[], int& nEmployees);
void writer(string output_filename, Employee employees[], int nEmployees);
bool addKeyForEmployee(Employee employees[], int nEmployees, string emp_name, string newKey);
bool returnAKey(Employee employees[], int nEmployees, string emp_name, string returnKey);


int main(){
  cout << "Please enter key file name to start: " ;
  string filename;
  cin >> filename;
  int nEmployees,choice = 0;
  Employee employees[10];
  bool x = reader(filename, employees, nEmployees);
  if(x == false){
    cout << "File not found, exiting the program..." << endl;
    exit(1);
  }
  else{
    while (choice != 7){
      cout << "Please select from the following options: " << endl;
      cout << "  1. show all employees and their keys" << endl;
      cout << "  2. show the keys an employee possesses" << endl;
      cout << "  3. show which employees possess a specific key" << endl;
      cout << "  4. add a key to an employee" << endl;
      cout << "  5. return a key by an employee" << endl;
      cout << "  6. save the current key status" << endl;
      cout << "  7. exit the program" << endl;
      cin >> choice;
      cin.ignore();
      if ((choice > 7) || (choice < 1)){
        cout << "Not a valid option. Please try again." << endl << endl;
        cin.clear();
    
      }
      if (choice == 1){
        for (int i = 0; i < nEmployees; i++){
          cout << "Name: " << employees[i].name << endl;
          cout << "Keys possessed: ";
          for (int j = 0; j < employees[i].nKeysPossessed; j++){
            cout << employees[i].keys[j] << " ";
          }
          cout << endl;
        }
        cout << endl;
      }
      if (choice == 2){
        int count = 0;
        string emp_name;
        cout << "Please enter employee's name: ";
        getline (cin, emp_name);
        for (int i = 0; i < nEmployees; i++){
          if (employees[i].name == emp_name){
            count++;
            cout << employees[i].name << " possess the following keys: ";
            for (int j = 0; j < employees[i].nKeysPossessed; j++){
              cout << employees[i].keys[j] << " ";  
            }
          }
        }
        if (count == 0){
          cout << "Cannot find the specified employee!" ;
        }
        cout << endl << endl;
      }
      if (choice == 3){
        int count = 0;
        string key;
        cout << "Please enter a key: ";
        cin >> key;
        for (int i = 0; i < nEmployees; i++){
          for (int j = 0; j < employees[i].nKeysPossessed; j++){
            if (employees[i].keys[j] == key){
              count++;
              cout << employees[i].name << ", ";
            }
          }
        }
        if (count == 0){
          cout << "No one possesses this key." << endl << endl;
        }
        else{
          cout << "possess this key." << endl << endl;
        }
      }
      if (choice == 4){
        cout << "Please enter employee's name: ";
        string emp_name, newKey;
        getline (cin, emp_name);
        cout << "Please enter a new key: " ;
        cin >> newKey;
        bool x = addKeyForEmployee(employees, nEmployees, emp_name, newKey);
        if (x == true){
          cout << "Key added successfully." << endl << endl;
        }
      }
      if (choice == 5){
        string emp_name, returnKey;
        cout << "Please enter employee's name: " ;
        getline (cin, emp_name);
        cout << "Please enter the returned key: " ;
        cin >> returnKey;
        bool x = returnAKey(employees, nEmployees, emp_name, returnKey);
        if (x == true){
          cout << "Key returned successfully." << endl << endl;
        }
      }
      if (choice == 6){
        string filename;
        cout << "Please enter output file name: " << endl;
        cin >> filename;
        writer(filename, employees, nEmployees);
      }
      if (choice == 7){
        writer("keys_updated.txt", employees, nEmployees);
        cout << "Thank you for using the system! Goodbye!" << endl;
      }
    }
  }
  return 0;
}  

bool reader(string input_filename, Employee employees[], int& nEmployees){
  ifstream keys;
  keys.open(input_filename);
  if (!keys.is_open()){
    return false;
  }

  keys >> nEmployees;
  keys.ignore();
 for (int i = 0; i < nEmployees; i++){
   getline(keys, employees[i].name);
   keys >> employees[i].nKeysPossessed;
   for (int j = 0; j < employees[i].nKeysPossessed; j++){
     keys >> employees[i].keys[j];
   }
   keys.ignore();
 }
  return true;
}
bool addKeyForEmployee(Employee employees[], int nEmployees, string emp_name, string newKey){
  int count = 0;
  for (int i = 0; i < nEmployees; i++){
    if (employees[i].name == emp_name){
      count++;
      if (employees[i].nKeysPossessed == 5){
        cout << "This employee already has 5 keys!" << endl << endl;
        return false;
      }
      for (int j = 0; j < employees[i].nKeysPossessed; j++){
        if (employees[i].keys[j] == newKey){
          cout << "This employee already has this key!" << endl << endl;
          return false;
        }
      }
      employees[i].nKeysPossessed++;
      employees[i].keys[employees[i].nKeysPossessed - 1] = newKey;
      return true;
    }
  }
  if(count == 0){
  cout << "Cannot find the specified employee!" << endl;
  return false;
  }
  return true;
}
bool returnAKey(Employee employees[], int nEmployees, string emp_name, string returnKey){
  int count,count1 = 0;
  for (int i = 0; i < nEmployees; i++){
    if (employees[i].name == emp_name){
      count++;
      for (int j = 0; j < employees[i].nKeysPossessed; j++){
        if (employees[i].keys[j] == returnKey){
          count1++;
          employees[i].nKeysPossessed--;
          for (int k = j; k < employees[i].nKeysPossessed; k++){
             employees[i].keys[j] = employees[i].keys[k+1];
            return true;
          }
        }
      }
    } 
  }
  if (count == 0){
    cout << "Cannot find the specified employee!" << endl << endl;
    return false;
  }
  if (count1 == 0){
    cout << "This employee does not have the specified key!" << endl << endl;
    return false;
  }
  return true;
}
void writer(string output_filename, Employee employees[], int nEmployees){
  ofstream ouput (output_filename);
  ouput << nEmployees << endl;
  for (int i = 0; i < nEmployees; i++){
    ouput << employees[i].name << endl;
    ouput << employees[i].nKeysPossessed ;
    if (employees[i].nKeysPossessed != 0){
      for (int j = 0; j < employees[i].nKeysPossessed; j++){
        ouput << " "<< employees[i].keys[j] ;
      }
    }
    ouput << endl;
  }
}