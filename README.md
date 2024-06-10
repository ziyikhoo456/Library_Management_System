# Library_Management_System

In this project, a program that will store and manage FICT student information and the books they borrow from library is developed using linked list. Three classes have been created which are **LibStudent class, LibBook class and Date class**. LibStudent class is used to store student information and the book they borrow from library. LibBook class is used to store information for a library book. Lastly, the Date struct is used to store date information.


Main() Tasks:

1.	Write a function **bool ReadFile(string filename, List \*list)** to read from a file that store student information in a linked list. Ensure there is no duplicate record of student stored in the list. The function will return true if successfully read and false otherwise. A sample of the textfile is in “student.txt”.

2.	Write a function **bool DeleteRecord(List \*list, char \*id)** to delete a student from the linked list based on student id. The function will return true if successfully delete and false if student cannot be found in the list.

3.	Write a function **bool SearchStudent(List \*list, char \*id, LibStudent &stu)** that will search for a student in the linked list based on id. If found return true and return the student information using stu and print the student information after return. If not found, return false.  

4.	Write a function **bool InsertBook(string filename, List \*list)** to insert book borrowed for a student to the linked list book. Open the file with filename and read every record and find the student to insert the book based on their id. A sample of the text file is in “book.txt”.  Read every record in the file and put the book info in a LibBook object. Then find the correct student based on id read to insert the read book info to the array book for that particular student. You need to calculate the fine for the book first before you insert to the student book array. You need to find out how many days the book is due and for every day, the fine is RM0.50. Assume that when you check for fine amount, the current date is 29/3/2020. (Note: You can use julian day to find the number of days the book is due). After you insert the book to the student’s book array, then call the calculateTotalFine function in the LibStudent struct to update the total fine for this student.    

5.	Write a function **bool Display(List \*list, int source, int detail)** to display the list list. The variable source is used to determine where to print the output and the variable detail is used to determine what to print as shown below:

- source = 1 (display to file)
- source = 2 (display to screen)
- detail = 1 (display student info and book info)
- detail = 2 (display student info only)


6.	Write a function **bool computeAndDisplayStatistics(List \*list**) that will compute and print the statistics of the numbers of students, total of books borrow, total overdue books and total overdue fine for all students according to course in the table below. The function will return false for empty list and true otherwise. Your output should be in table format as shown below (Note: You don’t have to show the line in the table).


7.	Write a function **bool printStuWithSameBook(List \*list, char \*callNum)** to find all the student in list list that borrow the same book according to call number of the book. Print out all the students that borrow this book and also the borrow date and due date for this book for each student. Refer to sample output below. The function will return false if list is empty or true otherwise. 

8.	Write a function **bool displayWarnedStudent(List \*list, List \*type1, List \*type2)** to identify students to be warned according to 2 types of misdemeanors. If a student has more than 2 books that are overdue for >= 10 days then copy this student to list type1. Copy the student to list type2 if the total fine for a student is more than RM50.00 and every book in the student’s book list are overdue. Assume the date is 29/3/2020 when you calculate for overdue. List type1 and type2 are empty when pass to function and content of list list will not be changed after function call. Display list type1 and type2 to screen after function call. You need to display student info together with the book list. The function will return false for empty list and true otherwise.

9.	Write a **int menu()** function that contain menu with choice from 1 to 9 as shown below to let user choose the task. Function will return the choice chosen. Make sure user can continuously choose for the menu until exit choice is chosen.
