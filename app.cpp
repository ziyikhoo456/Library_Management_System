
#include	<iostream>
#include	<cstdlib>
#include	<cstdio>
#include    <fstream>
#include    <string>
#include    <sstream>
#include	<iomanip>
#include    <unordered_set>
#include	"List.h"
#include    "LibStudent.h"
#include    "LibBook.h"

using namespace std;
char authors[50][10][20];

bool ReadFile(string, List*);
bool DeleteRecord(List *, char *);
bool Display(List*, int, int);
bool InsertBook(string, List *);
bool SearchStudent(List *, char *id, LibStudent &);
bool computeAndDisplayStatistics(List *);
bool printStuWithSameBook(List *, char *);
bool displayWarnedStudent(List *, List *, List *);
int menu();
bool EmptyList(List *);
bool EmptyFile(ifstream&);


int main() {
	bool loop = true;
	List* list, *type1, *type2; //Create pointers that will be passed into function.

	list = new List();
	type1 = new List();
	type2 = new List();

	LibStudent result;
	char studentID[10];
	char* id;
	int choice;

	//Loop the main menu forever
	while (loop){
		system("cls");

		//Display the main menu and return the choice
		choice = menu();
		system("cls");

		//Read File
		if (choice == 1) {

			//if ReadFile return false, print error statement
			if (!ReadFile("student.txt", list))
				cout << "Error! The operation is not successful!!\n\n" << endl; 

			system("pause");
		}

		//Delete record
		else if (choice == 2) {

			//Check if the list is empty, if not, proceed
			if (!EmptyList(list)){

				//Ask user to input ID that will be deleted
				cout << "Enter student ID: ";
				cin.get(studentID, 10);
				id = studentID;

				//Execute the function and print error if wrong student ID is input.
				if (!(DeleteRecord(list, id))) {
					cout << "The ID " << id << " is not found.\n\n" << endl;
				}


				system("pause");
			}
		}

		//Search Student
		else if (choice == 3) {
		
			LibStudent stu;
			
			//Check if the list is empty, if not, proceed
			if (!EmptyList(list)) {

				//Ask user to input ID to be searched
				cout << "Enter student ID: ";
				cin.get(studentID, 10);
				id = &studentID[0];

				//if the function return false, print error statement.
				if (!(SearchStudent(list, id, stu))) {
					cout << "Error! Cannot found the student with ID " << studentID << ".\n\n" << endl;
					system("pause");
				}

				//if the function return true, print out the info of searched student.
				else {
					cout << endl;
					cout << stu.id << endl;
					cout << stu.name << endl;
					cout << stu.course << endl;
					cout << stu.phone_no << endl << endl;
					system("pause");
				}
			}
		}

		//Insert Book
		else if (choice == 4) {

			//Check if the list is empty, if not, proceed
			if (!EmptyList(list)) {

				//if InsertBook return false, print error statement.
				if (!InsertBook("book.txt", list))
					cout << "Error! The operation is not successful!!\n\n" << endl;

				system("pause");
			}
		}

		//Display output
		else if (choice == 5) {
			int source, detail;
			
			//Check if the list is empty, if not, proceed
			if (!EmptyList(list)) {

				//Ask user how to display the file
				cout << "1.Display to file" << endl;
				cout << "2.Display to screen\n" << endl;
				cout << "Enter your choice:";
				cin >> source;
				cout << endl;
				
				cout << "1.Display student info and book info" << endl;
				cout << "2.Display student info only\n" << endl;
				cout << "Enter your choice:";
				cin >> detail;
				system("cls");

				//if Display return false, print error statement
				if (!(Display(list, source, detail)))
					cout << "Error! The operation is not successful!!\n\n" << endl;
			}
		}

		//Compute and display statistics
		else if (choice == 6) {

			//Check if the list is empty, if not, proceed
			if (!EmptyList(list)) {

				//if false is returned, print error statement.
				if (!computeAndDisplayStatistics(list)) {
					cout << "Error! The operation is not successful!!\n\n" << endl;
				}
				system("pause");
			}
		}

		//Display student with same book
		else if (choice == 7) {

			//Check if the list is empty, if not, proceed
			if (!EmptyList(list)) {
				char* PtrCallNum;
				char callNum[20];

				//Ask user to input call number
				cout << "\nPlease enter call number of the book:";
				cin >> callNum;
				PtrCallNum = callNum;

				//If function returns false, print error statement.
				if (!printStuWithSameBook(list, PtrCallNum))
					cout << "Incorrect call number! Please check again!!\n\n";

				cout << endl;
				system("pause");
			}
		}

		//Display Warned Student
		else if (choice == 8) {

			//Check if the list is empty, if not, proceed
			if (!EmptyList(list)) {

				//if function return false, print error statement
				if (!displayWarnedStudent(list, type1, type2)) {
					cout << "Error! This operation is not successfull!" << endl;
				}

				else {

					//if type1 list is not empty
					if (!(type1->empty())) {

						//print out student info and the book info
						cout << "\nType1 List:";
						for (int i = 1; i <= type1->count; i++) {
							type1->get(i, result);
							result.print(cout);
							for (int j = 0; j < result.totalbook; j++) {
								result.book[j].print(cout);
							}
							cout << "\n*****************************************************************" << endl;
						}
					}

					else
						cout << "\nType1 List is empty.\n\n\n";

					//if type2 list is not empty
					if (!(type2->empty())) {

						//print out student info and the book info
						cout << "\nType2 List:";
						for (int i = 1; i <= type2->count; i++){
							type2->get(i, result);
							result.print(cout);
							cout << "Book(s) :";
							for (int j = 0; j < result.totalbook; j++) {
								result.book[j].print(cout);
							}
							cout << "\n*****************************************************************" << endl;
						}
					}

					else
						cout << "\nType2 List is empty.\n\n\n";

				}
				system("pause");
			}
		}

		//Exit
		else if (choice == 9)
			return 0;

	}
}

bool ReadFile(string filename, List* list) {

	LibStudent student;
	bool duplicate;

	// Open the file
	ifstream infile(filename);

	// If the file cannot be opened, print the error
	if (!infile) {
		cout << "The file " << filename << " cannot be opened.\n\n" << endl;
		return false;
	}

	// If the file is empty, print error also
	infile.seekg(0, ios::end);
	if (infile.tellg() == 0) {
		cout << "The file " << filename << " is empty.\n\n" << endl;
		return false;
	}
	infile.seekg(0, ios::beg);

	// If the list is not found, print error
	if (!list) {
		cout << "The list " << list << " is not found!." << endl;
		return false;
	}

	while (!infile.eof()) {
		//No duplicate data at first
		duplicate = false;

		//Skip 13 characters then get the id
		infile.ignore(13);
		infile >> student.id;

		//Skip 8 characters then get the name
		infile.ignore(8);
		infile.get(student.name, 30);

		//Skip 10 characters then get the course
		infile.ignore(10);
		infile.get(student.course, 3);

		//Skip 16 characters then get the phone_no
		infile.ignore(16);
		infile.get(student.phone_no, 10);

		//Skip two empty lines
		infile.ignore(2);

		//Check if student id is duplicated.
		LibStudent result;
		for (int i = 1; i <= list->size(); i++) {
			list->get(i, result);
			if (strcmp(result.id, student.id) == 0) {
				cout << "Error! Duplicate record is found! ID " << student.id << " is repeated." << endl;
				cout << "The repeated information is skipped!" << endl << endl;
				duplicate = true;
			}
		}

		//If no duplicated data, add the student into studentList
		if (!duplicate) {
			list->insert(student);
		}

	}

	infile.close();
	cout << list->count << " records have been successfully read.\n\n" << endl;

	return true;
}

bool DeleteRecord(List* list, char* id) {

	LibStudent result;

	//Traverse each node to compare the student id
	for (int i = 1; i <= list->size(); i++) {
		list->get(i, result);

		//If matching student id is found, remove the node in list.
		if (strcmp(result.id, id) == 0){
			list->remove(i);
			cout << "Record of ID " << id << " is successfully deleted.\n\n" << endl;
			return true;
		}
	}
	
	//Return false if no matching student id is found.
	return false;

}

bool SearchStudent(List* list, char* id, LibStudent& stu) {
	LibStudent result;

	//Traverse each node to compare the student id
	for (int i = 1; i <= list->size(); i++) {
		list->get(i, result);

		//If matching student id is found, store it in stu.
		if (strcmp(result.id, id) == 0) {
			stu = result;
			return true;
		}
	}

	//Return false if no matching student id is found.
	return false;
}

int menu() {

	int choice;
	cout << "MENU" << endl << endl;
	cout << "1. Read file." << endl;
	cout << "2. Delete record." << endl;
	cout << "3. Search student." << endl;
	cout << "4. Insert book." << endl;
	cout << "5. Display output." << endl;
	cout << "6. Compute and Display Statistics." << endl;
	cout << "7. Student with Same Book." << endl;
	cout << "8. Display Warned Student." << endl;
	cout << "9. Exit." << endl << endl;

	//Ask user to enter their choice
	cout << "Enter your choice: ";
	cin >> choice;
	cin.ignore();
	return choice;
}

bool InsertBook(string filename, List* list) {
	LibBook book;
	char ID[10];
	string line;
	int num = 0, NumOfAuthor;
	int NumOfChar[10] = {0}, j, k;
	int PosChar[10] = {0};
	string author[5];
	char C_author[5][20];
	LibStudent result;
	Node* ptr;

	//Open the file
	ifstream infile;
	infile.open(filename);

	//If the file cannot be opened, print the error.
	if (infile.fail()) {
		cout << "The file" << filename << "cannot be opened." << endl;
		return false;
	}

	//If the file is empty, print the error.
	if (EmptyFile(infile)) {
		cout << "The file" << filename << "has empty content." << endl;
		return false;
	}

	//If the list is not found, print the error.
	else if (!list) {
		cout << "The list " << list << "is not found!." << endl;
		return false;
	}


	else {
		while (!infile.eof()) {
			book.fine = 0;
			infile >> ID;

			infile >> line;

			//To check how many authors, the first alphabet and how many characters for each author.
			NumOfAuthor= 1;
			j = 0; //index for NumOfChar
			PosChar[0] = 0; //the first pos character is always 0.
			k = 1; //index for PosChar
			int SumOfChar = 0;
			char slash[5]; //to store the position of '/' in a line.
			int count = 0;

			for (int i = 0; i < line.length(); i++) {
				//Check if there is any '/' in line
				if (line[i] == '/') {
					slash[count] = i;
					count++;

					//If the first '/' is found
					if (j == 0) {
						PosChar[k] = i + 1;
						k++;
						NumOfAuthor++;
						NumOfChar[j] = i;
						SumOfChar += NumOfChar[j];
						j++;
					}

					//If the '/' found is not the first one.
					else {
						PosChar[k] = i + 1;
						k++;
						NumOfChar[j] = i - NumOfChar[j - 1] - 1;
						j++;
						NumOfAuthor++;
					}
				}

				//If [i] is the last character of the line
				else if (i == (line.length() - 1)) {
					NumOfChar[j] = i - slash[num-1];
				}
			}

			for (int i = 0; i < NumOfAuthor; i++) {
				// To substring the author name,
				author[i] = line.substr(PosChar[i], NumOfChar[i]);
				
				//Store author name in C_string
				for (int j = 0; j < author[i].length() + 1; j++) {
					C_author[i][j] = author[i][j];
				}
				strcpy(authors[num][i],C_author[i]);
			}


			//Insert the rest into LibBook object.
			infile >> book.title;

			infile >> book.publisher;

			infile >> book.ISBN;

			infile >> book.yearPublished;

			infile >> book.callNum;

			infile >> book.borrow.day;
			infile.ignore();
			infile >> book.borrow.month;
			infile.ignore();
			infile >> book.borrow.year;
			infile.ignore();

			infile >> book.due.day;
			infile.ignore();
			infile >> book.due.month;
			infile.ignore();
			infile >> book.due.year;
			infile.ignore();

			//Calculate fine
			int Dueday = (book.due.day + ((book.due.month - 1) * 30));
			int Currentday = 29 + (2 * 30);
			int Fineday = 0;

			//Check if the book is overdue
			if (Dueday < Currentday) {
				book.fine = (Currentday - Dueday) * 0.50;
			}
			
			
			//Check student ID
			for (int i = 1; i <= list->count; i++) {
				list->get(i, result);

				//if the matching student ID is found, insert the LibBook object into that particular student
				if (strcmp(result.id, ID) == 0) {
					ptr = list->find(i);

					for (int j = 0; j < NumOfAuthor; j++) {
						ptr->item.book[ptr->item.totalbook].author[j] = authors[num][j];
					}

					strcpy(ptr->item.book[ptr->item.totalbook].title, book.title);
					strcpy(ptr->item.book[ptr->item.totalbook].publisher, book.publisher);
					strcpy(ptr->item.book[ptr->item.totalbook].ISBN, book.ISBN);
					ptr->item.book[ptr->item.totalbook].yearPublished = book.yearPublished;
					strcpy(ptr->item.book[ptr->item.totalbook].callNum, book.callNum);
					strcpy(ptr->item.book[ptr->item.totalbook].title, book.title);
					ptr->item.book[ptr->item.totalbook].borrow.day = book.borrow.day;
					ptr->item.book[ptr->item.totalbook].borrow.month = book.borrow.month;
					ptr->item.book[ptr->item.totalbook].borrow.year = book.borrow.year;
					ptr->item.book[ptr->item.totalbook].due.day = book.due.day;
					ptr->item.book[ptr->item.totalbook].due.month = book.due.month;
					ptr->item.book[ptr->item.totalbook].due.year = book.due.year;
					ptr->item.book[ptr->item.totalbook].fine = book.fine;

					ptr->item.totalbook += 1;
					
					//To calculate how many books have been inserted.
					num++;
				}
			}
			
		}

		
		//To update the total fine for each student
		for (int i = 1; i <= list->count; i++) {
			ptr = list->find(i);
			ptr->item.calculateTotalFine();
		}


		cout << num << " books have been inserted successfully to student list.\n\n" << endl;
		return true;
	}	
}

bool Display(List *list, int source, int detail) {

	//If the list is not found, print error.
	if (!list) {
		cout << "The list " << list << "is not found!." << endl;
		return false;
	}

	if (source == 1) {//print to file
		ofstream outfile;

		if (detail == 1) {
			outfile.open("student_booklist.txt");
			for (int i = 1; i <= list->count; i++) {// Print student info and book info in the file
				LibStudent result;
				list->get(i, result);
				outfile << "STUDENT " << i;
				result.print(outfile);//print student details
				outfile << "\n";
				if (result.totalbook != 0)
					outfile << "BOOK LIST:\n";

				for (int j = 0; j < result.totalbook; j++) {//print all the books
					outfile << "\nBOOK " << j + 1 << endl;
					result.book[j].print(outfile);
				}
				outfile << "\n*****************************************************************************\n" << endl;

			}
			cout << "Successfully display output to student_booklist.txt. Please check for it!!\n\n" << endl;
			system("pause");
		}

		else if (detail == 2) {
			outfile.open("student_info.txt");
			for (int i = 1; i <= list->count; i++) {// print student info into the file
				LibStudent result;
				list->get(i, result);
				outfile << "STUDENT " << i;
				result.print(outfile);
				outfile << "\n*****************************************************************************\n" << endl;
			}
			cout << "Successfully display output to student_info.txt. Please check for it!!\n\n" << endl;
			system("pause");
		}
		outfile.close();
	}

	else if (source == 2) {//cout to screen
		if (detail == 1) {
			for (int i = 1; i <= list->count; i++) {// Print student info and book info on the screen
				LibStudent result;
				list->get(i, result);
				cout << "STUDENT " << i;
				result.print(cout);//print student info
				if (result.totalbook != 0)
					cout << "BOOK LIST:\n";
				for (int j = 0; j < result.totalbook; j++) {//print all the books
					cout << "\nBOOK " << j + 1 << endl;
					result.book[j].print(cout);
				}
				cout << "\n*****************************************************************************\n" << endl;
			}
		}
		else if (detail == 2) {
			for (int i = 1; i <= list->count; i++) {// Print student info on the screen
				LibStudent result;
				list->get(i, result);
				cout << "STUDENT " << i;
				result.print(cout);
				cout << "\n*****************************************************************************\n" << endl;
			}
		}
		system("pause");
		return true;
	}
}

bool computeAndDisplayStatistics(List* list) {
	LibStudent result;
	int CS_count = 0, IA_count = 0, IB_count = 0, CN_count = 0, CT_count = 0;
	int CS_Books = 0, IA_Books = 0, IB_Books = 0, CN_Books = 0, CT_Books = 0;
	int CS_overdue = 0, IA_overdue = 0, IB_overdue = 0, CN_overdue = 0, CT_overdue = 0;
	int CS_fine = 0, IA_fine = 0, IB_fine = 0, CN_fine = 0, CT_fine = 0;
	int Dueday, Currentday;

	//If the list is not found, print error.
	if (!list) {
		cout << "The list " << list << "is not found!." << endl;
		return false;
	}

	//Trverse each node
	for (int i = 1; i <= list->count; i++) {
		list->get(i,result);
		
		//Check what is the course for each student

		if (strcmp(result.course, "CS") == 0) {
			CS_count++;
			CS_Books += result.totalbook;
			CS_fine += result.total_fine;

			//To calculate total overdue books
			for (int j = 0; j < result.totalbook; j++) {
				Dueday = result.book[j].due.day + (result.book[j].due.month * 30);
				Currentday = 29 + (3 * 30);
				if (Dueday < Currentday) {
					CS_overdue++;
				}
			}
		}

		else if (strcmp(result.course, "IA") == 0) {
			IA_count++;
			IA_Books += result.totalbook;
			IA_fine += result.total_fine;

			//To calculate total overdue books
			for (int j = 0; j < result.totalbook; j++) {
				Dueday = result.book[j].due.day + (result.book[j].due.month * 30);
				Currentday = 29 + (3 * 30);
				if (Dueday < Currentday) {
					IA_overdue++;
				}
			}
		}

		else if (strcmp(result.course, "IB") == 0) {
			IB_count++;
			IB_Books += result.totalbook;
			IB_fine += result.total_fine;

			//To calculate total overdue books
			for (int j = 0; j < result.totalbook; j++) {
				Dueday = result.book[j].due.day + (result.book[j].due.month * 30);
				Currentday = 29 + (3 * 30);
				if (Dueday < Currentday) {
					IB_overdue++;
				}
			}
		}

		else if (strcmp(result.course, "CN") == 0) {
			CN_count++;
			CN_Books += result.totalbook;
			CN_fine += result.total_fine;

			//To calculate total overdue books
			for (int j = 0; j < result.totalbook; j++) {
				Dueday = result.book[j].due.day + (result.book[j].due.month * 30);
				Currentday = 29 + (3 * 30);
				if (Dueday < Currentday) {
					CN_overdue++;
				}
			}
		}

		else if (strcmp(result.course, "CT") == 0) {
			CT_count++;
			CT_Books += result.totalbook;
			CT_fine += result.total_fine;

			//To calculate total overdue books
			for (int j = 0; j < result.totalbook; j++) {
				Dueday = result.book[j].due.day + (result.book[j].due.month * 30);
				Currentday = 29 + (2 * 30);
				if (Dueday < Currentday) {
					CT_overdue++;
				}
			}
		}
	}

	//Display all output.
	cout << "Course\t Number of Students\tTotal Books Borrowed\tTotal Overdue Books\tTotal Overdue Fine (RM)\t" << endl;
	cout << "  CS\t" << setw(10) << CS_count << "\t\t\t" << CS_Books << "\t\t\t" << CS_overdue << "\t\t\t" << CS_fine << "\t\t\t" << endl;
	cout << "  IA\t" << setw(10) << IA_count << "\t\t\t" << IA_Books << "\t\t\t" << IA_overdue << "\t\t\t" << IA_fine << "\t\t\t" << endl;
	cout << "  IB\t" << setw(10) << IB_count << "\t\t\t" << IB_Books << "\t\t\t" << IB_overdue << "\t\t\t" << IB_fine << "\t\t\t" << endl;
	cout << "  CN\t" << setw(10) << CN_count << "\t\t\t" << CN_Books << "\t\t\t" << CN_overdue << "\t\t\t" << CN_fine << "\t\t\t" << endl;
	cout << "  CT\t" << setw(10) << CT_count << "\t\t\t" << CT_Books << "\t\t\t" << CT_overdue << "\t\t\t" << CT_fine << "\t\t\t" << endl;
	cout << "\n\n" << endl;
	return true;
}

bool printStuWithSameBook(List *list, char *callNum) {
	LibBook book;
	LibStudent result;
	int studarray[20], studnum = 0, bookarray[20];

	//If the list is not found, print error.
	if (!list) {
		cout << "The list is not found!" << endl;
		return false;
	}

	strcpy(book.callNum, callNum);//copy call Number to a empty struct
	for (int i = 1; i <= list->count; i++) {//retrieve student details
		list->get(i, result);
		for (int j = 0; j < result.totalbook; j++) {//compare with all the book
			if (result.book[j].compareCallNum(book)) {// if match the call Number
				studarray[studnum] = i; //save the student location
				bookarray[studnum] = j;//save book location
				studnum++;

			}
		}
	}
	if (studnum == 0)//check if there is any student with that book
		return false;
	cout << "There are " << studnum << " students that borrow the book with call number " << callNum << " as shown below:\n";
	for (int k = 0; k < studnum; k++) {// print out the result
		list->get(studarray[k], result);
		cout << "\nStudent Id = " << result.id << endl;
		cout << "Name = " << result.name << endl;
		cout << "Course = " << result.course << endl;
		cout << "Phone Number = " << result.phone_no << endl;
		cout << "Borrow Date: ";
		result.book[bookarray[k]].borrow.print(cout);
		cout << "\nDue Date: ";
		result.book[bookarray[k]].due.print(cout);
		cout << "\n" << endl;
	}
	return true;
}

bool displayWarnedStudent(List *list, List *type1, List *type2) {
	LibStudent result;
	int Dueday, Currentday, due_count1, due_count2;

	//If the list is not found, return false
	if (!list)
		return false;

	for (int i = 1; i < list->count; i++) {// retrieve list of student 
		due_count1 = 0;
		due_count2 = 0;
		list->get(i, result);
		
			for (int j = 0; j < result.totalbook; j++) { //check for each book
				
				Dueday = (result.book[j].due.day + ((result.book[j].due.month - 1) * 30));
				Currentday = 29 + (2 * 30);

				if (Dueday < Currentday) {//check for due books
					due_count2++;
					if (Dueday + 10 <= Currentday)//check for condition type1
						due_count1++;
				}
				
			}
			
		
		if (due_count1 > 2) //final check for eligibilty of type1
			type1->insert(result);
		
		if (result.total_fine > 50 and due_count2 == result.totalbook)//final check for eligibilty of type2
			type2->insert(result);
	}
	return true;
}

bool EmptyList(List* list) {
	//Check if the list is empty
	if (list->empty()) {
		cout << "Error! The list is empty." << endl;
		cout << "Please insert information into the list before proceed.\n\n" << endl;
		system("pause");
		return true;
	}

	else
		return false;
}

bool EmptyFile(ifstream& infile) {
	//Move the cursor at the end of file
	infile.seekg(0, infile.end);

	//Return true if the position < 1
	if (infile.tellg() < 1) {
		return true;
	}

	//Clear and move the cursor back to the first position
	else {
		infile.clear();
		infile.seekg(0, infile.beg);
		return false;
	}
}