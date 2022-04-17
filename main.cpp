#include <iostream>
#include <fstream>

using namespace std;
ofstream outputFile;
ifstream inputFile;

// global constants
const int ROWS = 15;
const int COLS = 30;
const char TAKEN = '*';
const char EMPTY = '#';

// array for seats and columns
char seating[15][30];

// initialize total sales to 0
double totalSales = 0;

// functions declared for case statements
void displayMenu();
int getChoice();
void displaySeats(char[][COLS]);
void displayPrices(double *);
void updatePrices(double *);
void displaySales(double);
void purchaseTicket(char [][COLS], double *, double&);

// assigning prices to each row in an array
double prices[ROWS] = {23, 23, 24, 24, 24, 25, 25, 25, 25, 25, 24, 24, 24, 23, 23};

int main()
{
    // open this file to store seating prices
	ofstream movieFile;
	movieFile.open("Seatingprices.txt");

    // using a for loop to update txt file
	for(int a = 0; a < ROWS; a++)
	{
		movieFile << prices[a] << endl;
	}
	movieFile.close();

    // this loop will create 15 by 30 for seating, and it will be represented by pound signs
	for(int a = 0; a < ROWS; a++)
	{
		for(int b = 0; b < COLS; b++)
		{
			seating[a][b] = '#';
		}
	}

    // declaring choice as an int
	int receiveChoice;

    // this loop will execute program
	do
	{
		displayMenu();
		receiveChoice = getChoice();
	}while(receiveChoice != 6);

}  	// end main

// displaying menu function
void displayMenu()
{
	cout << "\t       C++ Theatre       " << endl;
	cout << "\t 1. View available seats " << endl;
	cout << "\t 2. View seating prices " << endl;
	cout << "\t 3. Update seating prices " << endl;
	cout << "\t 4. Purchase a ticket " << endl;
	cout << "\t 5. View ticket sales " << endl;
	cout << "\t 6. Quit " << endl;
	cout << "Pick an option from 1-6 to view movie tickets: ";
}

// this function will get choice and put into case statements to call the other functions
int getChoice()
{
    // user input
	int choice;
	cin >> choice;

    // switch case for choice
	switch(choice)
	{
		case 1: displaySeats(seating);
					return 0;
                    break;
		case 2: displayPrices(prices);
					return 0;
					break;
		case 3: updatePrices(prices);
					return 0;
					break;
		case 4: purchaseTicket(seating, prices, totalSales);
					return 0;
					break;
		case 5: displaySales(totalSales);
					break;
		case 6: return 6;
					break;
		default: cout << "Please choose a valid option from the list!" << endl;
	}
}

// displaying all seats
void displaySeats(char seating[][COLS])
{
    // loop to show available seats
	for(int a = 0; a < ROWS; a++)
	{
		cout << "Rows:" << a + 1 << "\t";
		for(int b = 0; b < COLS; b++)
		{
			cout << seating[a][b];
		}
		cout << endl;
	}

    // seating specifications
	cout << "# = Available" <<  endl;
	cout << "* = Taken seat(s)" << endl;
}

// displaying prices function
void displayPrices(double *prices)
{
    //opening movie file to view prices
	ifstream movieFile;
	movieFile.open("Seatingprices.dat");

    // loop for seats
	for(int a = 0; a < ROWS; a++)
	{
		cout << "Rows:" << a + 1 << "\t";
		movieFile >> prices[a];
        // pointer for prices + a
		cout << *(prices + a) << endl;
	}
	movieFile.close();
}

// user can update prices
void updatePrices(double *rowPrices)
{
    // sending numeric data to txt file
	inputFile.open("seatingPrices.txt");

    // prompt user and update prices and close file
	for(int a = 0; a < ROWS; a++)
	{
		inputFile >> *(rowPrices + a);
		cout << "Enter your seat prices for row " << a + 1 << ": \t";
		cin >> rowPrices[a];

	}
	inputFile.close();

	cout << endl;				// cleaner program
}

// display current sales function
void displaySales(double totalSales)
{
	cout << "Your movie total is: " << totalSales;
	cout << endl;
}

// purchase ticket function
void purchaseTicket(char seating[][COLS], double *prices, double&totalSales)
{
    // getting user input
	char ans;
	cout << "Do you want to display seat chart? (y or n)" << endl;
	cin >> ans;

    // calling seating function
	if(ans == 'Y' || ans == 'y')
	{
		displaySeats(seating);
	}

	int rows;
	cout << "Enter the row number" << endl;
	cin >> rows;

    // validation loop
	while(rows > 15 || rows < 0)
	{
		cout << "You have to select a valid option for rows" << endl;
		cin >> rows;
	}

	int columns;
	cout << "Enter a seat number you would like" << endl;
	cin >> columns;

	while(columns > 30 || columns < 0)
	{
		cout << "You have to select a valid option for a seat number" << endl;
		cin >> columns;
	}

    // validation if statement if user selects a taken seat
	if(seating[rows - 1][columns - 1] == '*')
	{
		cout << "You have to select a different seat, this one is taken" << endl;
		purchaseTicket(seating, prices, totalSales);
	}

	seating[rows - 1][columns - 1] = '*';
	totalSales += *(prices + rows - 1);
}

