// this  program reads a file containing student test and assignment scores and outputs a letter grade for each student, in order of last name.
#include "std_lib_facilities.h"

// create data type 'Student'
struct Student
{
	string lastName;
	string firstName;
	string gradeType;
	double grade;
};

// function prototypes
bool sortFunction(const Student& a, const Student& b);
vector<double> totalForStudent(vector<Student>& students, vector<double>& totals);
double highestScore(vector<double> scores);


int main()
{
	// ask the user for the file to read 
	cout << "Enter the file to read: ";
	string filename;
	getline(cin, filename);
	
	// open file for reading
	ifstream fin;
	fin.open(filename);
	
	vector<Student> student_data;
	
	// reads file line by line and adds the lines to the vector of structs
	Student next_student;
	fin >> next_student.lastName >> next_student.firstName >> next_student.gradeType >> next_student.grade;
	
	while (fin)
	{
		student_data.push_back(next_student);   // adds each struct to a vector of structs
		fin >> next_student.lastName >> next_student.firstName >> next_student.gradeType >> next_student.grade;  // reads the next line
	}
	
	// close the file
	fin.close();
	
	// sorts the vector of structs using the function 'sort' that passes in the function 'sortFunction'
	sort(student_data.begin(), student_data.end(), sortFunction);
	
	// uses the function 'totalForStudent' to add the points for all assignments of each student and adds the total scores to vector 'totalScores'
	vector<double> totalScores = {};
	totalForStudent(student_data, totalScores);
	
	// finds the grade average for each student by dividing the student's score by the highest score multiplied by 100 and adds the values to
	// vector 'averages'
	vector<double> averages = {};
	for (int i = 0; i < totalScores.size(); i++)
	{
		double average = (totalScores[i] / highestScore(totalScores)) * 100;
		averages.push_back(average);
	}

	// finds the letter grade for each average and adds the letter grade to vector 'letterGrades'
	vector<char> letterGrades = {};
	char gradeLetter;
	
	for (int i = 0; i < averages.size(); i++)
	{
		if (averages[i] >= 90)
		{
			gradeLetter = 'A';
			letterGrades.push_back(gradeLetter);
		}
		else if (averages[i] >= 80)
		{
			gradeLetter = 'B';
			letterGrades.push_back(gradeLetter);
		}
		else if (averages[i] >= 70)
		{
			gradeLetter = 'C';
			letterGrades.push_back(gradeLetter);
		}
		else if (averages[i] >= 60)
		{
			gradeLetter = 'D';
			letterGrades.push_back(gradeLetter);
		}
		else
		{
			gradeLetter = 'F';
			letterGrades.push_back(gradeLetter);
		}
	}

	// combines the student's first and last names of the struct into their full name as a single string and adds those strings to vector 'fullNames'
	vector<string> fullNames;
	for (int i = 0; i < student_data.size(); i++)
	{
		string fullName = student_data[i].firstName + " " + student_data[i].lastName;
		fullNames.push_back(fullName);
	}
	
	// erases the duplicate full names in vector 'fullNames'
	fullNames.erase(unique(fullNames.begin(), fullNames.end()), fullNames.end());
	
	// ask the user for the file to write to
	cout << "Enter the file to write to: ";
	string second_filename;
	getline(cin, second_filename);
	
	// open the file for writing
	ofstream fout;
	fout.open(second_filename);	
	
	// outputs the student's name with their corresponding grade to the output file
	for (int i = 0; i < fullNames.size(); i++)
	{
		fout << fullNames[i] << " " << letterGrades[i] << "\n";
	}
	
	fout.close();
}

// define functions
// bool function that is passed into the standard 'sort' function to sort the vector of structs
bool sortFunction(const Student& a, const Student& b)
{
	return a.lastName < b.lastName;
}

// adds up the scores of all assignments for each student and adds the totals to vector 'totals'
vector<double> totalForStudent(vector<Student>& students, vector<double>& totals)
{
	double total = 0.0;
	double saveTotal = total;
	string name = students[0].lastName;
	
	for (int i = 0; i < students.size(); i++)
	{
		if (name == students[i].lastName)
		{
			total += students[i].grade;
		}
		
		if (name != students[i].lastName)
		{
			totals.push_back(total);
			total = saveTotal;
			name = students[i].lastName;
			total = students[i].grade;
		}
		
	}
	totals.push_back(total);
	
	return totals;
}

// finds the highest total score between the students 
double highestScore(vector<double> scores)
{
	double highScore = scores[0];
	for (int i = 0; i < scores.size(); i++)
	{
		if (scores[i] > highScore)
		{
			highScore = scores[i];
		}
	}
	return highScore;
}
