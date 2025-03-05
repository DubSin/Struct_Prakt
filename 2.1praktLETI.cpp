#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Profile
{
	string fullName; 
	char sex;         
	int group;        
	int id;           
	int grades[8];    
	char depart;        
};

void creatingRecord() {
	Profile student;   
	cout << "Name: ";       
	getline(cin, student.fullName); 
	cout << "Group id: ";  
	cin >> student.group;  
	cin.ignore();
	cout << "Pos in group: ";     
	cin >> student.id;     
	cin.ignore();
	cout << "Sex(m/f): ";     
	cin >> student.sex; 
	cin.ignore();
	cout << "Depart(b/c): ";        
	cin >> student.depart; 
	cin.ignore();
	cout << "Grades (8): ";     
	for (int i = 0; i < 8; i++){  
		cin >> student.grades[i];
	 	cin.ignore();
	}

    int temp = 0;
	for (int i = 0; i < 8; i++) 
	{
		if (student.grades[i] == 2) 
			temp++; 
	}
	if (temp == 0) 
	{
		ofstream database; 
		database.open("students.txt", ios::app); 
		if (!database.is_open()) 
			cout << '\n' << "Saving error!"; 
		else
		{
			database << "\n" << student.fullName << " ";
			database << student.group << " " << student.id << " ";
			database << student.sex << " " << student.depart << " ";
			for (int i = 0; i < 8; i++)
				database << student.grades[i] << " ";
			database.close();
			cout << '\n' << "Profile is saved in the database.";
		}
	}
	else 
         cout << '\n' << "This student will be expelled. The profile will not be saved in the database.";
}

int main() {
	char action = 's';cout << "Menu" << endl;
	while (action != 'e'){
		cout << "1)Update database" << endl;
		cout << "2)Change database" << endl;
		cout << "3)Show all students" << endl;
		cout << "4)Show students from group" << endl;
		cout << "5)Most valuable students" << endl;
		cout << "6)Male and female students" << endl;
		cout << "7)Students who dont get scholarship; 5 and 4; only 5" << endl;
		cout << "8)Information of students with 'k' id" << endl;
		cout << "Choose action(e - exit): ";
		cin >> action;
		switch (action){
			case '1': {
				cin.ignore();
				creatingRecord();
				break;
			}
		}
	}	
}