#include <bits/stdc++.h>
#include <fstream>
#include <conio.h>
#include <iomanip>
using namespace std;

int main(){

// #ifndef ONLINE_JUDGE
// 	freopen("E:/sublime/input.txt","r",stdin);
// 	freopen("E:/sublime/output.txt","w",stdout);
// #endif
						//Code Starts Here
	int ch;
	bool flag = true;
	do{
		cout << "****************************************\n";
		cout << "*      STUDENT MANAGEMENT SYSTEM       *\n";
		cout << "****************************************\n";

		cout<< "1. Add Student\n"<<
				"2. View All Students\n"<<
				"3. Search Student\n"<<
				"4. Update Student\n"<<
				"5. Delete Student\n"<<
				"6. Sort Students\n"<<
				"7. Exit\n"<<endl;
		cout<<"Enter your choice: ";
		cin>>ch;
		cout<<endl;
		switch(ch){
			case 1: 
			{
				ofstream fout("students.txt",ios::app);

				if (!fout) {
    				cout << "\nError opening file!\n";
    				break;
				}


				string name, roll;
				string marks;

				cout<<"Enter Roll Number: ";
				cin>>roll;

				cout<<"\nEnter Name: ";
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				getline(cin,name);

				cout<<"\nEnter Marks: ";
				cin>>marks;
				fout<<roll<<","<<name<<","<<marks<<"\n";
				cout<<"\nStudent Added Successfully!";
				cout<<endl;

				cout<<"\nPlease Enter to continue...";

				while(_getch()!=13){} //Waiting while the user enters the specified key...

				fout.close();
				cout<<endl;
				break;
			}
			case 2:
			{
				ifstream fin("students.txt");

				if (!fin) {
    				cout << "\nError opening file!\n";
    				break;
				}
				int maxRoll = strlen("Roll No.");
				int maxName = strlen("Name");
				int maxMarks = strlen("Marks");

				string line1;

				while(getline(fin, line1)){

					stringstream ss(line1);
					string name, roll, marks;
					getline(ss,roll,',');
					getline(ss,name,',');
					getline(ss,marks);

					maxRoll = max(maxRoll, (int)roll.size());
					maxName = max(maxName, (int)name.size());
					maxMarks = max(maxMarks, (int)marks.size());
				}
				fin.close();
				fin.open("students.txt");
				if(!fin){
				    cout << "Error reopening file!\n";
				    break;
 				}
				cout << "\n--- View All Students ---\n\n";

				cout
						<< left
						<< setw(maxRoll+2) << "Roll No."
						<<"| "
						<< setw(maxName+2) << "Name"
						<<"| "
						<< setw(maxMarks+2)<< "Marks"
						<< endl;

				cout << "-----------+---------------+--------\n";
				
				string line2;

				while(getline(fin,line2)){
					stringstream ss(line2);
					string name, roll;
					string marks;
					getline(ss,roll,',');
					getline(ss,name,',');
					getline(ss,marks);

					cout << left
					     << setw(maxRoll+2) << roll
					     << "| "
					     << setw(maxName+2) << name
					     << "| "
					     << setw(maxMarks+2) << marks
					     << endl;
				}

				cout<<"\nPlease Enter to continue...";

				while(_getch()!=13){} //Waiting while the user enters the specified key...

				fin.close();
				cout<<endl;
				break;
			}
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
				cout<<"Exiting"<<endl;
				flag = false;
				break;
			default:
				cout<<"Enter a valid choice!"<<endl;
		}

	}while(flag);
	return 0;
}