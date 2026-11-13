// Danyal Asfar
// 552124
// Section D

#include <iostream>
#include <stack>
#include <string>
using namespace std;

struct Student{
    int rollNumber;
    string name;
};

struct record{
    Student* thisStudent;
    record* left;
    record* right;
};

class StudentManager{
    public:
        void AddStudent(int rollNumber, string name){
            Student* newStudent = new Student(rollNumber,name);
            root = AddNode(root, newStudent);
        }

        void DisplayAll(){
            cout << "   Name    " << "RollNumber\n";
            DisplayTree(root);
        }

        void SearchRollNumber(int rollNumber){
            Search(root, rollNumber);
            SearchHistory.push(rollNumber);
        }

        void DisplayMostRecentSearch(){
            cout << "Most Recent Roll Number Searched:\n" << SearchHistory.top() << endl;
        }

        void DeleteMostRecentSearch(){
            SearchHistory.pop();
            cout << "Deleted!!!\n";
        }

        void Clear(){
            ClearAll(root);
            root = nullptr;
        }
    private:
        record* root = nullptr;
        stack<int> SearchHistory;

        record* AddNode(record* root, Student* newStudent){
            if ( root == nullptr) return new record{ newStudent, nullptr, nullptr };
            if ( newStudent -> rollNumber < root -> thisStudent -> rollNumber )
                root -> left = AddNode( root -> left, newStudent);
            else if ( newStudent -> rollNumber > root -> thisStudent -> rollNumber )
                root -> right = AddNode( root -> right, newStudent);
            return root;
        }

        void DisplayTree(record* root){
            if ( root == nullptr ) return;

            DisplayTree(root -> left);
            cout << root->thisStudent -> name << "          " << root->thisStudent -> rollNumber << endl;
            DisplayTree(root -> right);
        }

        void Search(record* root, int rollNumber){
            if (root == nullptr)
                cout << "Not Found\n";

            else if ( rollNumber < root -> thisStudent -> rollNumber)
                Search(root -> left, rollNumber);
            else if ( rollNumber > root -> thisStudent -> rollNumber)
                Search(root -> right, rollNumber);
            else
                cout << "Name: " << root -> thisStudent -> name << endl;
        }

        void ClearAll(record* root){
            if ( root == nullptr ) return;
            ClearAll(root -> left);
            ClearAll(root -> right);
            delete root -> thisStudent;
            delete root;
        }
};

int main(){
    StudentManager manager;
    int rollNumber;
    string name;
    int option = -1;

    while ( option != 6){
        cout << "*****************************************************\n";
        cout << "1.Add Student\n2.Search Roll Number\n3.Display Students\n4.Most Recent Search\n"
            << "5.Delete Most Recent Search\n6.Exit\n";
        cout << "Enter Option:\n";
        cin >> option;

        switch (option){
            case 1:
                cout << "Enter Name of Student\n";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Roll Number:\n";
                cin >> rollNumber;

                manager.AddStudent(rollNumber, name);
                break;
            case 2:
                cout << "Enter Roll Number to Search:\n";
                cin >> rollNumber;
                manager.SearchRollNumber(rollNumber);
                break;
            case 3:
                manager.DisplayAll();
                break;
            case 4:
                manager.DisplayMostRecentSearch();
                break;
            case 5:
                manager.DeleteMostRecentSearch();
                break;
            case 6:
                cout << "Exiting....\n";
                manager.Clear();
                break;
            default:
                cout << "Incorrect Option Selected!!!\nPlease Try Again!!!\n";
        }
    }
    return 0;
}