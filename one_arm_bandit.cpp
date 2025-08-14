#include <iostream>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()

using namespace std;

int tot_winnings;
int balance;

int calculate_Winnings(char field[3][3], int bet);
int one_arm_bandit(int deposit,int balance);
void Betting(int balance);


int main()
{
	char grid[3][3] = {{ 'A', 'A', 'A' },{ 'O', 'A', 'O' },{ 'X', 'X', 'X' } };

	for (int i = 0; i < 3; i++)    // Outer loop for rows
	{     
		for (int j = 0; j < 3; j++)     // Inner loop for columns
		{  
			cout <<"      "<< grid[i][j] << " "; // Print each element with a space
		}
		cout << endl << endl;
		// New line after each row
	}

	char start;
	cout << "\nDo you want to start the one arm gambit (y/n) : ";
	cin >> start;

	if (start == 'y' || start == 'Y')
	{
		Betting(balance);
	}
	else
	{
		cout << "\n\nUntill next time, Goodbye\n";
	}
	return 0;
}


void Betting(int balance)
{

	int deposit;

	cout << "\nHow much do you want to deposit? \n\n     500 SEK \n     300 SEK \n     100 SEK ";
	cout << "\n\nDeposit :";
	cin >> deposit;

	balance = balance + deposit;

	if (deposit == 100 || deposit == 300 || deposit == 500)
	{
		one_arm_bandit(deposit, balance);
	}
	else
	{
		cout << "\nInvalid input\n";
		Betting(balance);
	}
}


int one_arm_bandit(int deposit, int balance)
{
	int bet;
	cout << "\nHow much do you want to bet before your game? ";
	cin >> bet;

	if (balance >= deposit)
	{
		balance = deposit - bet;
		char selection;
		cout << "\nPull the one arm \n\n     PULL (P)\n     STOP (S)\n";
		cout << "\nDO IT NOW: ";
		cin >> selection;
		if (selection == 'P' || selection == 'p')
		{
			srand(time(0));                           // Initialize the random seed
			char symbols[] = { 'X', 'O', 'A' };       // Characters to randomly select from
			char grid[3][3];                          // 3x3 array to hold the random symbols

			// Populate the grid with random symbols
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					grid[i][j] = symbols[rand() % 3];  // Randomly assign 'X', 'O', or 'A'
				}
			}

			// Display the 3x3 grid
			cout << "\nRandomly generated 3x3 grid of symbols:\n\n";
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					cout << "      " << grid[i][j] << " ";  // Print each symbol with spacing
				}
				cout << endl << endl;
			}

			// Call calculatePayout with the 3x3 grid and bet
			int winnings = calculate_Winnings(grid, bet);  // Pass the whole grid, not grid[3][3]
			cout << "\nYou won " << winnings << " SEK." << endl;

			tot_winnings = tot_winnings + winnings;

			cout << "\nYour total winnings are " << tot_winnings << " SEK." << endl;

			balance = balance + winnings;

			cout << "\nYour full balance is " << balance << " SEK\n";

			if (balance >= 0)
			{
				cout << "\nDo you want to play again? (y/n) : ";
				char select;
				cin >> select;
				if (select == 'y' || select == 'Y')
				{
					one_arm_bandit(deposit, balance);
				}
				else
				{
					cout << "\nPlease withdraw your winnings and balnce of the deposit, " << balance << " SEK\n";
					cout << "\nUntill next time , Goodbyee\n";
					exit(0);
				}
			}
			else
			{
				cout << "\nDeposit again ";
				Betting(balance);
			}
		}
		else
		{
			exit(0);
		}
	}
	else
	{
		cout << "\nInvalid input\n";
		Betting(balance);
	}

	
}


int calculate_Winnings(char field[3][3], int bet)
{
	int lines = 0;

	for (int i = 0; i < 3; ++i)     	// Check rows for matching symbols (horizontal lines)
	{
		if (field[i][0] == field[i][1] && field[i][1] == field[i][2])
		{
			lines++;                   // Horizontal match
		}
	}

	for (int i = 0; i < 3; ++i)        	// Check columns for matching symbols (vertical lines)
	{
		if (field[0][i] == field[1][i] && field[1][i] == field[2][i])
		{
			lines++;                   // Vertical match
		}
	}

	if (field[0][0] == field[1][1] && field[1][1] == field[2][2])       // Check diagonals for matching symbols  Left-to-right diagonal (top-left to bottom-right)
	{
		lines++;                       // Diagonal match
	}

	if (field[0][2] == field[1][1] && field[1][1] == field[2][0])      // Right-to-left diagonal (top-right to bottom-left)
	{
		lines++;                       // Diagonal match
	}

	// Calculate winnings based on the number of matching lines
	int winnings = 0;
	if (lines == 1) winnings = 2 * bet;
	else if (lines == 2) winnings = 3 * bet;
	else if (lines == 3) winnings = 4 * bet;
	else if (lines == 4) winnings = 5 * bet;
	else if (lines == 5) winnings = 7 * bet;
	else if (lines == 6) winnings = 10 * bet;

	return winnings;
}

