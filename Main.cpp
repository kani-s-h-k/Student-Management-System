#include <bits/stdc++.h>
#include <fstream>
#include <conio.h>
#include <iomanip>
using namespace std;

struct Student{
	string roll;
	string name;
	double marks;
};

struct Widths{
    int roll;
    int name;
    int marks;
};

Student parseStudent(const string& line){
    Student s;
    stringstream ss(line);
    string strmarks;
    getline(ss,s.roll,',');
    getline(ss,s.name,',');
    getline(ss,strmarks);
    s.marks = stod(strmarks);

    return s;
}


bool checkRoll(const string &target){
	ifstream fin("students.txt");

	string line;

	while(getline(fin,line)){
		Student s = parseStudent(line);
		if(s.roll == target){ 
			return true;
		}
	}
	return false;
}

Widths maxNumbers(){
	ifstream fin("students.txt");
	int maxRoll = strlen("Roll No.");
	int maxName = strlen("Name");
	int maxMarks = strlen("Marks");

	string line;

	while(getline(fin, line)){

		Student s = parseStudent(line);

		maxRoll = max(maxRoll, (int)s.roll.size());
		maxName = max(maxName, (int)s.name.size());
		ostringstream out;
		out << fixed << setprecision(2) << s.marks;
		maxMarks = max(maxMarks, (int)out.str().size());
	}
	fin.close();
	return {maxRoll,maxName,maxMarks};
}

Student searchStudent(const string& target){
    ifstream fin("students.txt");

    string line;

    while(getline(fin,line)){
        Student s =parseStudent(line);

        if(s.roll == target)
            return s;
    }

    return {"","",0};
}

void printTemplate(const Widths &w){
	cout
		<< left
		<< setw(w.roll+2) << "Roll No."
		<<"| "
		<< setw(w.name+2) << "Name"
		<<"| "
		<< setw(w.marks+2)<< "Marks"
		<< endl;

		cout << string(w.roll + w.name + w.marks + 10, '-') << '\n';

}


void printStudent(const Student& s){
	ostringstream out;
	out << fixed << setprecision(2) << s.marks;
    Widths w{
        max((int)s.roll.size(), (int)strlen("Roll No.")),
        max((int)s.name.size(), (int)strlen("Name")),
        max((int)out.str().size(),(int)strlen("Marks"))
    };

    printTemplate(w);

    cout << left
         << setw(w.roll+2) << s.roll
         << "| "
         << setw(w.name+2) << s.name
         << "| "
         << setw(w.marks+2) << 
         fixed << setprecision(2)
		 << s.marks
         << '\n';
}


vector<Student> loadStudents(){
	ifstream fin("students.txt");
	vector<Student> students;
	string line;
	while(getline(fin,line)){
		students.emplace_back(parseStudent(line));
	}
	return students;
}

void printSortedOrder( const vector<Student> &students){
	Widths w = maxNumbers();
	printTemplate(w);
	for(auto &s : students){
		cout << left
			<< setw(w.roll+2) << s.roll
			<< "| "
			<< setw(w.name+2) << s.name
			<< "| "
			<< setw(w.marks+2)
			<< fixed << setprecision(2)
			<< s.marks
		<< endl;
	}
}

void pauseScreen(){
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout<<"\nPlease Enter to continue...";
	while(_getch()!=13){} //Waiting while the user enters the specified key...
}

int main(){
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
				double marks;

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
					pauseScreen();
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
				Widths w= maxNumbers();

				cout << "\n--- View All Students ---\n\n";

				printTemplate(w);
				
				string line;

				while(getline(fin,line)){
					Student s = parseStudent(line);

					cout << left
					     << setw(w.roll+2) << s.roll
					     << "| "
					     << setw(w.name+2) << s.name
					     << "| "
					     << setw(w.marks+2) 
					     << fixed << setprecision(2)
					     << s.marks << endl;
				}
				fin.close();
				pauseScreen();
				cout<<endl;
				break;
			}
			case 3:{
				cout << "\n--- Search Student ---\n\n";
				string target;
				cout<<"Enter Roll Number: ";
				cin>>target;
				cout<<endl;
				Student s = searchStudent(target);		

				if(s.roll.empty()) cout<<"Student not registered!"<<endl;
				else{
					 printStudent(s);
				}		
				pauseScreen();
				break;
			}
			case 4: 
			{
				cout << "\n--- Update Student Details ---\n\n";
				string roll,Newname;
				double Newmarks;
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
						Student s = parseStudent(line);

						if(s.roll!=roll){
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
				pauseScreen();
				break;
			}
			case 5:
				{
				cout << "\n--- Delete Student Registration---\n\n";
				string roll;
				cout<<"\n Enter Roll Number: ";
				cin>>roll;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				if(checkRoll(roll))
				{	

					ifstream fin("students.txt");
					ofstream fout("temp.txt");

					string line;
					while(getline(fin,line)){
						Student s = parseStudent(line);
		
						if(s.roll!=roll){
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
				pauseScreen();
				break;
			}
			case 6:{
				cout << "\n--- Sort Students ---\n\n";
				cout<<"1. Sort by Name\n2. Sort by Marks\n";
				int choice;
				cout<<"Enter choice: ";
				cin>>choice;

				switch(choice){
					case 1:{
						vector<Student> students = loadStudents();
						sort(students.begin(),students.end(),
							[](const Student &a, const Student &b)
							{
								return a.name>b.name;
							});
						printSortedOrder(students);
						break;
					}
					case 2:{
						vector<Student> students = loadStudents();
						sort(students.begin(),students.end(),
							[](const Student &a, const Student &b)
							{
								return a.marks>b.marks;
							});
						printSortedOrder(students);
						break;
					}
					default:
						cout<<"Invalid Input!\n";
						break;
				}
				pauseScreen();
				break;
			}
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