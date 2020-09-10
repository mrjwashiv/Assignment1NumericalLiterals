#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct numLit
{
	string lit;
	bool valid;
};

//Takes decimal in exponent as valid,
//two exponents is valid
//Exponent doesnt have an int is valid
//just e is valid
//Two signs for exponent is wrong


void validateFile(string&);
void getInput(string&);
void deleteSpaces(string&);
int getNumOfLines(string);
void formatLine(string&);
bool hasExponent(string);
string* breakLiteral(string);
bool checkSigns(string&);
bool checkForNumber(string);
int hasDecimal(string);
bool decimalValid(string, int);
bool checkDigits(string);
void writeToFile(string, numLit[], int);
void outputToConsole(numLit[], int);
void printMenu();
void checkLiteral();


int main()
{
	printMenu();
	checkLiteral();
}

void validateFile(string& fileName)
{
	bool isValid = false;
	bool lineValid;
	string numLiteral;

	while (!isValid)
	{
		ifstream inputFile(fileName);

		if (inputFile.is_open())
		{
			lineValid = true;

			while (getline(inputFile, numLiteral) && lineValid)
			{
				lineValid = numLiteral.size() < 50;
			}
			
			isValid = lineValid;

			if (!isValid)
			{
				cout << "File is invalid, please try a different file8 >> ";
				getline(cin, fileName);
				cout << endl;
			}
		}
		else
		{
			cout << "File is invalid, please try a different file >> ";
			getline(cin, fileName);
			cout << endl;
		}
	}
}

void getInput(string& input)
{
	cout << "Please enter a txt file >> ";
	getline(cin, input);
	cout << endl;

	formatLine(input);
	validateFile(input);
}

void deleteSpaces(string& input)
{
	for (int i = 0; i < input.length() && input[i] == ' '; i++)
	{
		input.erase(i, 1);
		i--;
	}

	for (int i = input.length() - 1; i >= 0 && input[i] == ' '; i--)
	{
		input.erase(i, 1);
	}
}

int getNumOfLines(string fileName)
{
	int numOfLines = 0;
	string line;
	ifstream file(fileName);

	while (getline(file, line))
	{
		numOfLines++;
	}

	return numOfLines;
}

void formatLine(string& input)
{
	for (int i = 0; i < input.length(); i++)
	{
		input[i] = tolower(input[i]);
	}

	deleteSpaces(input);
}

bool hasExponent(string lit)
{
	for (int i = 0; i < lit.size(); i++)
	{
		if (lit[i] == 'e')
		{
			return true;
		}
	}

	return false;
}

string* breakLiteral(string lit)
{
	int exponentLocation = lit.find("e");
	string* num = new string[2];

	num[0] = lit.substr(0, exponentLocation); //integral
	num[1] = lit.substr(exponentLocation + 1);    //exponent

	return num;
}

bool checkSigns(string& lit)
{
	for (int i = 1; i < lit.size(); i++)
	{
		if (lit[i] == '-' || lit[i] == '+')
		{
			return false;
		}
	}

	if (lit[0] == '-' || lit[0] == '+')
	{
		lit.erase(0, 1);
	}

	return true;
}

bool checkForNumber(string lit)
{
	for (int i = 0; i < 3 && i < lit.size(); i++)
	{
		if (lit[i] >= '0' && lit[i] <= '9')
		{
			return true;
		}
	}

	return false;
}

int hasDecimal(string lit)
{
	for (int i = 0; i < lit.size(); i++)
	{
		if (lit[i] == '.')
		{
			return i;
		}
	}

	return -1;
}

bool decimalValid(string lit, int decimalLoc)
{
	int deciCount = 0;
	for (int i = 0; i < lit.size(); i++)
	{
		if (lit[i] == '.')
		{
			deciCount++;
		}

		if (deciCount > 1)
		{
			return false;
		}
	}


	if (decimalLoc != 0)
	{
		if ((lit[decimalLoc - 1] >= '0' && lit[decimalLoc - 1] <= '9') || (lit[decimalLoc + 1] >= '0' && lit[decimalLoc + 1] <= '9'))
		{
			return true;
		}
	}
	else
	{
		if (lit[decimalLoc + 1] >= '0' && lit[decimalLoc + 1] <= '9')
		{
			return true;
		}
	}

	return false;
}

bool checkDigits(string lit)
{
	for (int i = 0; i < lit.size(); i++)
	{
		if (!(lit[i] >= '0' && lit[i] <= '9'))
		{
			return false;
		}
	}

	return true;
}

void writeToFile(string fileName, numLit lits[], int size)
{
	ofstream outputFile;
	outputFile.open(fileName);

	string notValid = "is NOT a valid numeric literal";
	string valid = "is a valid numeric literal";

	for (int i = 0; i < size; i++)
	{
		if (lits[i].valid)
		{
			outputFile << left << setw(10) << lits[i].lit << valid << endl;
		}
		else
		{
			outputFile << left << setw(10) << lits[i].lit << notValid << endl;
		}
	}

	outputFile.close();
}

void outputToConsole(numLit lits[], int size)
{
	string notValid = "is NOT a valid numeric literal";
	string valid = "is a valid numeric literal";

	for (int i = 0; i < size; i++)
	{
		if (lits[i].valid)
		{
			cout << left << setw(10) << lits[i].lit << valid << endl;
		}
		else
		{
			cout << left << setw(10) << lits[i].lit << notValid << endl;
		}
	}
}

void printMenu()
{
	cout << "/************************************************************** " << endl;
	cout << "*                                                             * " << endl;
	cout << "*                    NUMERICAL LITERALS                       * " << endl;
	cout << "*                                                             * " << endl;
	cout << "**************************************************************/ " << endl << endl;

	cout << "WELCOME USER!" << endl << endl;
	cout << "# TO GET STARTED, ENTER THE TXT FILE NAME WITH YOUR LITERALS TO BE EVALUATED" << endl;
	cout << "# NEXT THE LITERALS WILL BE EVALUATED AND RESULTS WILL BE OUTPUTTED" << endl;
	cout << "ENJOY THE PROGRAM!!!" << endl << endl;
}

void checkLiteral()
{
	string iFileName;
	string oFileName = "TextFile2.txt";
	string numLiteral;
	bool hasExp;
	bool signsValid;
	bool hasNumInFirst2;
	int hasDeci;
	bool deciValid;
	bool digitValid;
	string integral;
	string exponent;
	string* num = new string;
	int count = 0;

	getInput(iFileName);

	int size = getNumOfLines(iFileName);
	numLit* literals = new numLit[size];

	ifstream inputFile(iFileName);

	if (inputFile.is_open())
	{
		while (getline(inputFile, numLiteral))
		{
			literals[count].lit = numLiteral;

			formatLine(numLiteral);

			hasExp = hasExponent(numLiteral);
			integral = numLiteral;

			if (hasExp)
			{
				//Break literal into two parts, integral and exponent
				num = breakLiteral(numLiteral);
				integral = *(num);
				exponent = *(num + 1);

				//Check exponent
				signsValid = checkSigns(exponent);
				digitValid = checkDigits(exponent);

				if (!(signsValid && digitValid) || exponent == "")
				{
					literals[count].valid = false;
				}
			}

			//Time to check integral

			//Check signs
			signsValid = checkSigns(integral);
					
			//Check if theres a number in the first two spots
			hasNumInFirst2 = checkForNumber(integral);

			if (!(signsValid && hasNumInFirst2))
			{
				literals[count].valid = false;
			}

			//Check if it has a decimal
			hasDeci = hasDecimal(integral);

			if (hasDeci != -1)
			{
				//Check decimal
				deciValid = decimalValid(integral, hasDeci);

				if (deciValid)
				{
					integral.erase(hasDeci, 1);
				}
				else
				{
					literals[count].valid = false;
				}
			}
				
			digitValid = checkDigits(integral);

			if (!digitValid)
			{
				literals[count].valid = false;
			}
			//make sure it's not already false
			else if(literals[count].valid != false)
			{
				literals[count].valid = true;
			}
			count++;
		}
		inputFile.close();

		writeToFile(oFileName, literals, size);
		outputToConsole(literals, size);
	}
}