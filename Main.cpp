#include <bits/stdc++.h>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <iomanip>
using namespace std;

bool checkRoll(string target){
	ifstream fin("students.txt");

	string line;

	while(getline(fin,line)){
		stringstream ss(line);
		string roll;
		getline(ss,roll,',');
		if(roll == target){ 
			return true;
		}
	}
	return false;
}

int main(){


// #ifndef ONLINE_JUDGE
// 	freopen("E:/sublime/input.txt","r",stdin);
// 	freopen("E:/sublime/output.txt","w",stdout);
// #endif
						//Code Starts Here
	int ch;
	bool flag = true;
	do{
		cout<<endl;
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
				string name, roll;
				string marks;

				cout<<"Enter Roll Number: ";
				cin>>roll;

				if(!checkRoll(roll)){
					ofstream fout("students.txt",ios::app);

					if (!fout) {
	    				cout << "\nError opening file!\n";
	    				break;
					}
					cout<<"\nEnter Name: ";
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					getline(cin,name);

					cout<<"\nEnter Marks: ";
					cin>>marks;
					fout<<roll<<","<<name<<","<<marks<<"\n";
					cout<<"\nStudent Added Successfully!";
					cout<<endl;
					fout.close();
					cout<<"\nPlease Enter to continue...";
					while(_getch()!=13){} //Waiting while the user enters the specified key...
				} else{
					cout<<"\nStudent already registered!";
				}
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
				fin.clear();
				fin.seekg(0);

				cout << "\n--- View All Students ---\n\n";

				cout
						<< left
						<< setw(maxRoll+2) << "Roll No."
						<<"| "
						<< setw(maxName+2) << "Name"
						<<"| "
						<< setw(maxMarks+2)<< "Marks"
						<< endl;

				cout << string(maxRoll + maxName + maxMarks + 10, '-') << '\n';
				
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
				fin.close();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout<<"\nPlease Enter to continue...";

				while(_getch()!=13){} //Waiting while the user enters the specified key...
				cout<<endl;
				break;
			}
			case 3:{
				cout << "\n--- Search Student ---\n\n";
				bool fl = false;
				string target;
				cout<<"Enter Roll Number: ";
				cin>>target;
				cout<<endl;
				ifstream fin("students.txt");
				string roll,name,marks;
				string line;
				while(getline(fin,line)){
					stringstream ss(line);
					getline(ss,roll,',');
					if(roll == target){
						fl = true;
						getline(ss,name,',');
						getline(ss,marks);

						int maxRoll = max((int)roll.size(),8);
						int maxName = max((int)name.size(),4);
						int maxMarks = max((int)marks.size(),5);

						cout
						<< left
						<< setw(maxRoll+2) << "Roll No."
						<<"| "
						<< setw(maxName+2) << "Name"
						<<"| "
						<< setw(maxMarks+2)<< "Marks" 
						<< endl;

						cout
						<< left
						<< setw(maxRoll+2) << roll
						<<"| "
						<< setw(maxName+2) << name
						<<"| "
						<< setw(maxMarks+2)<< marks
						<< endl;	
						break;
					}
				}
				fin.close();
				if(!fl) cout<<"Student not registered!"<<endl;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout<<"\nPlease Enter to continue...";
				while(_getch()!=13){} //Waiting while the user enters the specified key...
				break;
			}
			case 4: 
			{
				cout << "\n--- Update Student Details ---\n\n";
				string roll,Newname,Newmarks;
				cout<<"\n Enter Roll Number: ";
				cin>>roll;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				if(checkRoll(roll))
				{
					cout<<"\n Enter new name: ";
					getline(cin,Newname);
					cout<<"\nEnter new marks: ";
					cin>>Newmarks;				

					ifstream fin("students.txt");
					ofstream fout("temp.txt");

					string line;
					while(getline(fin,line)){
						stringstream ss(line);
						string name,marks,r;
						getline(ss,r,',');
						getline(ss,name,',');
						getline(ss,marks);

						if(r!=roll){
							fout<<line<<endl;
						}
						else{
							fout<<roll<<","<<Newname<<","<<Newmarks<<"\n";
						}

					}
						fin.close();
						fout.close();
						remove("students.txt");
						if(rename("temp.txt","students.txt")==0){
							cout<<"\nSuccesfully Updated!"<<endl;
						}
						else{
							cout << "\nError Updating Student!\n";
						}
				}
				else cout<<"Student Not Registered!"<<endl;
				
				
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout<<"\nPlease Enter to continue...";
				while(_getch()!=13){} //Waiting while the user enters the specified key...
				break;
			}
			case 5:
				{
				cout << "\n--- Delete Student Registration---\n\n";
				string roll,Newname,Newmarks;
				cout<<"\n Enter Roll Number: ";
				cin>>roll;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				if(checkRoll(roll))
				{	

					ifstream fin("students.txt");
					ofstream fout("temp.txt");

					string line;
					while(getline(fin,line)){
						stringstream ss(line);
						string r;
						getline(ss,r,',');
						

						if(r!=roll){
							fout<<line<<endl;
						}

					}
						fin.close();
						fout.close();
						remove("students.txt");
						if(rename("temp.txt","students.txt")==0){
							cout<<"\nSuccesfully Deleted!"<<endl;
						}
						else{
							cout << "\nError Deleting Student Registration!\n";
						}
				}
				else cout<<"Student Not Registered!"<<endl;
				
				
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout<<"\nPlease Enter to continue...";
				while(_getch()!=13){} //Waiting while the user enters the specified key...
				break;
			}
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