/*
Boyer-Moore Algorithm Implementation (C++)
By: Saim Raza Gondal
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


# define TOTAL_CHARACTERS 2056					// Global Variable.

/* --------------------------------------- Creating Class Project -------------------------------------- */
class Project {

	// Public data fields
public:
	int occurance[2000];						// Array used to store number of shifts occured in text with respect to some pattern.
	int counter = 0;							// Counter variable. 
	string text1;								// Random text. 
	int difference;								// Differenc between the text found and the text you want to replace with.
	int condition = 0;							// Variable used in order to keep in check whether the pattern is matched or not.



												// Creating Maximum Function which returns the maximum number of out two
	int maximum(int number1, int number2)
	{
		if (number1 > number2)
			return number1;
		else
			return number2;
	}
	// Ending Maximum function.



	// Creating function badCharInt which saves the integer form of a pattern in badCharArray.
	void badCharInt(string string1, int size, int badCharArray[])
	{
		// Initializing all values of badCharArray to -1.
		for (int i = 0; i < TOTAL_CHARACTERS; i++)
			badCharArray[i] = -1;


		// Storing the integer value of each characters of the required pattern in badCharArray.
		for (int i = 0; i < size; i++)
			badCharArray[(int)string1[i]] = i;
	}
	// Ending badCharInt function.



	// Creating a search function which finds the pattern in the given text.
	void search(string text, string pattern)
	{
		int patternSize = pattern.size();					// Length of the pattern to be detected.
		int textSize = text.size();							// Length of text in the file.
		int spaces = 0;										// Variable used to count spaces(or words) in text.


		int badCharArray[TOTAL_CHARACTERS];					// Creating a badCharArray which has a size of TOTAL_CHARACTERS.


		badCharInt(pattern, patternSize, badCharArray);		// Calling badCharInt function to store integer values of the required pattern.


		int shift = 0;										// Variable used for "shifting" according to Bad Character approach.


															// Using while loop for shifting approach.
		while (shift <= (textSize - patternSize))
		{
			int j = patternSize - 1;						// Subtracting 1 from patternSize  for correct pattern index.


															// Inner while loop which compares the integer value of each character of pattern with the loop.
			while (j >= 0 && pattern[j] == text[shift + j])
				j--;										// Decrement j when a character is matched.


															// If j = -1 (Which means whole pattern is matched.)
			if (j < 0)
			{
				condition = 1;


				// Counting spaces.
				for (int x = 0; x < shift; x++)
				{
					if (text[x] == 32)						// If space is found, increment "spaces" variable.
						spaces++;

					if (text[x] == '\n')					// If next line is found, increment "spaces" variable.
						spaces++;
				}


				// Displaying results.
				cout << "\nThe pattern occurs at word number :- " << spaces + 1 << "\n\n";
				spaces = 0;


				cout << "\nThe pattern occurs at index :- " << shift << "\n\n";


				occurance[counter] = shift;					// Storing the index(or shift), at which the pattern occured, in occurance array.
				counter++;									// Incrementing counter.


															// Shifting the pattern to the index after the matched characters of the text (Bad Character approach).
				if (shift + patternSize < textSize)
					shift += (patternSize - badCharArray[text[shift + patternSize]]);
				else
					shift += 1;
			}

			else											// If pattern is not matched. Shift according to Bad Character approach.
				shift += maximum(1, j - badCharArray[text[shift + j]]);
		}
	}
	// Ending search function



	// Creating replace function in case user wants to replace the text. (Application)
	void replace(string text, string pattern, string replace)
	{
		int patternSize = pattern.size();					// Length of the pattern to be detected.
		int textSize = text.size();							// Length of text in file.
		int replaceSize = replace.size();					// Length of the text you want to replace with.
		int counter1 = 0;									// Counter variable.
		difference = replaceSize - patternSize;				// Differenc between the found text and text you want to replace with


															// Using for loop to traverse through the whole text.
		for (int x = 0; x < textSize; x++)
		{
			// When "x" reaches at the index where pattern was matched. 
			if (x == occurance[counter1] && counter1 < counter)
			{
				text1 += replace;							// Replace the previous word with the new one
				counter1++;									// Increment Counter1 variable.
				x = x + patternSize - 1;					// Setting the x to the index after the word was replace, to traverse ahead.
			}
			else
				text1 += text[x];							// Simply add the text characters to new text file.
		}


		// Displayin result.
		cout << "\n\nNew Text after replacing :- \n\n\n";

		cout << text1 << "\n\n";
	}
};
/* --------------------------------------- Ending Class Project -------------------------------------- */





/* --------------------------------------- Creating Main Function -------------------------------------- */
void main()
{
	// Initializing variables.
	ifstream file;									// File to be used as input.
	string text;									// Text in the file.
	string pattern;									// Pattern which has to be detected.
	string replace;									// Word if user want to replace the found pattern in the text.
	string input;									// User input.

	Project obj;									// Creating obj of class "Project".
	string text2;									// String variable.


	cout << "Enter the file name :- \n";
	cin >> input;


	// Opening the file.
	file.open(input);


	// if the file is successfully opened then take input from the file else display error message
	if (file.is_open())
	{
		cout << "\n\nFile has been opened successfully !\n\n\n";


		// Using while loop to traverse through the file and reaches End of File.
		while (!file.eof())
		{
			// Reading the entire file into string variable text. 
			getline(file, text2);					// Reading the text.
			text.append(text2);						// Storing the text.
			text.append("\n");						// Using new line. 
		}
	}
	else
	{
		cout << "\n\nError opening file !\n\n";
		return;
	}



	// Closing the file.
	file.close();


	// Length of text in the file.
	int textSize = text.size();


	// Prompting user to input the pattern to be searched.
	cout << "Find :- ";

	while (1)
	{
		if (pattern == "")										// If nothing is nothing is entered.
		{
			getline(cin, pattern);
		}
		else
			break;
	}


	// Calling the "search" function which returns the indices on which the pattern exists in the text of the file.
	obj.search(text, pattern);
	cout << "\n\n\n";


	// If pattern is found.
	if (obj.condition == 1)
	{
		cout << "Replace :- ";
		getline(cin, replace);
		obj.replace(text, pattern, replace);
	}
	else
		cout << "pattern not found...";


	// Writing the file.
	ofstream myfile;


	// After find and replace is completed, print the modified text.
	if (obj.condition == 1)
	{
		myfile.open(input);
		myfile << obj.text1;
		myfile.close();
	}
	cout << "\n";
}
/* --------------------------------------- Ending Main Function. -------------------------------------- */







