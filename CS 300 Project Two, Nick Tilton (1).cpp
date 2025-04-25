//============================================================================
// Name        : CS 300 ABCU_Advising_Program_Input.cpp
// Author      : Nick Tilton 
// Date		   : 04/19/2025
// Version     : 1.0
// Description : Advising Assistance Program for ABCU Advisors and Fellow Staff
//============================================================================

// include
#include <stdlib.h> // standard library
#include <iostream> // input and output handling
#include <fstream> // file handling
#include <sstream> // string streams
#include <string> 
#include <vector> // dynamic arrays
#include <algorithm>

using namespace std;

// Define the Course structure
struct Course
{
	string courseId;                        // unique name identifier for the course
	string courseName;                      // name of course
	vector<string> coursePrerequisites;     // list of course prerequisites 
};

// vector to store all courses
vector<Course> courses;

// Method to load course data via CS 300 ABCU_Advising_Program_Input.csv
void LoadCourseData()
{

	// Define the variable csvFilePath which will then store the file path
	string csvFilePath;

	// Pass through CSV file path 
	csvFilePath = "CS 300 ABCU_Advising_Program_Input.csv";

	// Open the file for reading
	ifstream inputFile;
	inputFile.open(csvFilePath);

	// Check if the file was successfully opened
	if (inputFile.is_open())
	{
		string line;

		// Read the file partitioning the lines
		while (getline(inputFile, line))
		{
			vector <string> tokens;
			string token;
			stringstream lineStream(line);

			// Tokenize the line by using commas
			while (getline(lineStream, token, ','))
			{
				tokens.push_back(token);
			}

			// Create a new course object and assign data via the CSV
			Course newCourse = Course();
			newCourse.courseId = tokens[0];
			newCourse.courseName = tokens[1];

			// If prerequisites exist, add them to the course list
			if (tokens.size() > 2)
			{
				for (int i = 2; i < tokens.size(); i++)
				{
					newCourse.coursePrerequisites.push_back(tokens[i]);
				}
			}

			// Add the newly created course to the courses vector
			courses.push_back(newCourse);
		}

		cout << "Course data has been loaded successfully!!" << endl;
	}
	// else file not found, print error message
	else
	{
		cout << "Input file was not found. Please check the file path entered." << endl;
	}

	// make sure to close the file after reading
	inputFile.close();
}

// Method that will print all courses from the file
void PrintCourseList()
{

	// Make sure that there are courses in the list
	if (courses.size() > 0)
	{

		// Sorts the courses in the list alphanumerically
		for (int i = 0; i < courses.size() - 1; i++)
		{
			for (int j = 0; j < courses.size() - i - 1; j++)
			{
				if (courses[j].courseId > courses[j + 1].courseId)
				{
					swap(courses[j + 1], courses[j]);
				}
			}
		}

		// Print courseId and courseName
		cout << "Here the course list:" << endl;
		cout << endl;
		for (int i = 0; i < courses.size(); i++)
		{
			cout << courses[i].courseId << ", ";
			cout << courses[i].courseName << endl;
		}
		cout << endl;
	}
	// Throw an error if course data has not been loaded before searching
	else
	{
		cout << "Course data has not yet been loaded. Make sure to load course data prior to searching." << endl;

	}
}

// Method that will print the course information for the course that the user chooses
void PrintCourse()
{

	// Make sure there is data in courses
	if (courses.size() > 0)
	{
		string courseInput;
		// initialize courseFound to true
		bool courseFound = false;

		cout << "Please enter desired course ID for more information: ";
		cin >> courseInput;

		// Converts user input from lowercase to uppercase to prevent any casing issues down the line
		transform(courseInput.begin(), courseInput.end(), courseInput.begin(), ::toupper);

		// Loop through the list and check to see if anything matches the users course input
		for (int i = 0; i < courses.size(); i++)
		{
			if (courses[i].courseId == courseInput)
			{
				// If user input matches a course in the list, set courseFound to true
				courseFound = true;

				// Print the information for the found course
				cout << endl;
				cout << "Course Information" << endl;
				cout << endl;
				cout << courses[i].courseId << ", ";
				cout << courses[i].courseName << endl;
				cout << "Prerequisites: ";
				if (courses[i].coursePrerequisites.size() > 0)
				{
					int prereqSize = courses[i].coursePrerequisites.size();

					// Loop through all course prerequisites in the list
					for (int j = 0; j < prereqSize - 1; j++)
					{
						cout << courses[i].coursePrerequisites[j] << ", ";
					}
					// Remove comma from the last entry in the list
					cout << courses[i].coursePrerequisites[prereqSize - 1];
					cout << endl;


				}
				// if there are no prerequisites for the desired course, print "No information found :("
				else
				{
					cout << "No information found :(" << endl;
				}

			}

		}

		// Check to make sure the course was found
		// If course is not found in the list, throw an error
		if (courseFound == false)
		{
			cout << "Invalid Course ID. Please enter the ID of a valid course for more information." << endl;
		}

	}

	// Throw an error if the CSV file data has not yet been loaded before making a request
	else
	{
		cout << "Course data has not been loaded. Make sure to load course data first." << endl;
	}
}

// Main method, used for user input such as the menu
int main()
{

	// initialize variable quit and set it to false
	bool quit = false;

	// prints the title
	cout << endl;
	cout << "Welcome to the ABCU Course Planner!" << endl;

	do
	{
		string userInput;

		// Print Menu
		cout << endl;
		cout << "  1. Load Course Data" << endl;
		cout << "  2. Print Course List" << endl;
		cout << "  3. Print Course" << endl;
		cout << "  9. Exit" << endl;
		cout << endl;
		cout << "Please choose an option: ";
		cin >> userInput;
		cout << endl;

		// While loop that validates user input
		// If user input is anything other than the options listed, throw an error and have the user try another entry
		while ((userInput != "1") && (userInput != "2") && (userInput != "3") && (userInput != "9"))
		{
			cout << userInput << " is not a valid option. Please choose from the given options." << endl;

			cout << endl;
			cout << "  1. Load Course Data" << endl;
			cout << "  2. Print Course List" << endl;
			cout << "  3. Print Course" << endl;
			cout << "  9. Exit" << endl;
			cout << endl;
			cout << "Please choose an option: ";
			cin >> userInput;
			cout << endl;
		}

		// Calling methods using user input
		if (userInput == "1") {
			LoadCourseData();
		}
		if (userInput == "2") {
			PrintCourseList();
		}
		if (userInput == "3") {
			PrintCourse();
		}
		if (userInput == "9") {
			cout << endl;
			cout << "Thank you for using the course planner, Have a great day!! :)" << endl;
			exit(quit);
		}
	} while (!quit);

	return 0;
}