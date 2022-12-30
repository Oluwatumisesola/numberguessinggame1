//THIS IS AN EXAMPLE TO HELP YOU GET STARTED WITH THIS ASSIGNMENT

/*
Tumi Shoyoye
Due Date: July 13th 2022
Course:  C0P3014
Assignment:  Program 7 array
Professor: Sorgente

Description: number guessing games with a random number generator and an dynamic array

*************************************************************/
#include <iostream> //standard library for i/o
#include <string> // always include this when you use the string class
#include <fstream>
#include <ctime> //random number generator
using namespace std;


/*********************************************************
//Following is the declaration of a round of gameNumberGuess
**********************************************************/
class gameNumberGuess
{
public:
	int level;  //game level (1 or 2) 
	int maxGuesses; //max number of guesses (example 5 or 8)
	int upperValue; //upper range value (example 100 or 1000)
	int currentGuess; //current guess input by the user
	int solution;  //pseudo random generated number
	int smallNum; //lower value for feedback
	int largeNum; //higher value for feedback
	bool above; //current guess above the solution
	bool below; //current guess below the solution
	string name; //name of current player
	bool wonOrLost; //true or false for the current round of the game
};


//Declaration/ Prototypes for your functions will go here

//BE SURE TO ADD COMMENTS TO THE FUNCTION PROTOTYPES AND THE FUNCTION DEFINITIONS
// and comments throughout the code making it easier to read
void TestAndDouble(gameNumberGuess*& gameList, int count, int& size);
//doubles the size of the array when count equals size
void PrintPlayerResults(gameNumberGuess gameList[], int gameCount);
//Description:  Connects to an output file
//Prints the array results onto the screen and into the output file
void PlayOneRound(const string& name, gameNumberGuess& currentGame);
//Description:  Play one round of the number guess game
//Precondition: The data variable (string) and object (gameNumberGuess) have been declared
//			the string has a value before calling this function
//Postcondition: One round of the game Number Guess has been completed
void SetUpLevel(gameNumberGuess& currentGame);
//Precondition: The object (gameNumberGuess) has been declared before calling this function
//Postcondition: The member variables have been reset for a round of the game
//Description:  Sets up one round of the game
void GetGuessInput(gameNumberGuess& currentGame);
//Precondition: The object (gameNumberGuess) has been declared before calling this function
//Postcondition: The user has entered a guess 
//Description:  Displays the range, prompts, and gets the next guess from the user
bool ProcessGuess(gameNumberGuess& currentGame);
//Precondition: State what is true before the function is called.
//Postcondition: State what is true after the function has executed.
//Description:  returns true(guess matches solution) or false (lets the user know if the guess was too high or too low)
void GenerateSolutionNumber(gameNumberGuess& currentGame);
//Precondition: State what is true before the function is called.
//Postcondition: State what is true after the function has executed.
//Description:  Generates the solution number in the correct range


//HERE IS THE main function

int main()
{
	string yesOrNo = "y";

	//declare an array of gameNumberGuess objects
    gameNumberGuess* gameList; 
	//count the number of games
    int gameCount= 0;
    int size = 1;

    gameList = new gameNumberGuess[size];

	//want to play?
    cout << "Do you want to play? (Y)Yes or (N)No"; 
    cin >> yesOrNo;

	while (yesOrNo != "n" && yesOrNo != "N")
	{
        //make sure array is large
        //test and double
        TestAndDouble(gameList, gameCount, size);

		//ask for the name here, it may be a different player
		cout << "Enter your first name: ";
		//into the member variable name
		cin >> gameList[gameCount].name;

		//play one round
        PlayOneRound(gameList[gameCount].name, gameList[gameCount]);
		//add one to the gamecount
		gameCount++;

		//again?
        cout << "Do you want to play again? (Y for yes)(N for no)" << endl;
        cin >> yesOrNo;
		
	}
	
	//print results
    PrintPlayerResults(gameList, gameCount);
	//good bye and thanks
    cout << "Goodbye and thank you for playing!!" << endl;
	return  0;
}

//Function Implementations will go here

void TestAndDouble(gameNumberGuess*& gameList, int count, int& size)
{
    if (count == size)
    {
        size *= 2;
        //create a new temp array
        gameNumberGuess* temp = new gameNumberGuess[size];
        //copy all the objects into the temp array
            for (int i = 0; i < count; i++)
                {
                    temp[i] = gameList[i];
                }
        //delete the gameList pointer
        delete[] gameList;
        //point gameList to temp
        gameList = temp;
    }
        cout << "\ncount is " << count;
        cout << "\nsize is " << size << endl;
}

//*************************************************************************************
//Name:  PrintPlayerResults
//Precondition: State what is true before the function is called.
//Postcondition: State what is true after the function has executed.
//Description:  Connects to an output file
//Prints the array results onto the screen and into the output file
//*************************************************************************************

void PrintPlayerResults(gameNumberGuess gameList[], int gameCount)
{
	ofstream out;
	char filename[40];
	//user should enter filename with .txt extension
	cout << "Enter the filename: ";
	cin >> filename;
	//add to the file if the user enters the same file name
	out.open(filename, ios::app);

	cout << "\n***********************************\n";
	cout << "Name\t" << "Level\t" << "won or lost\n";
	//use a loop to print the array (name, level, WonOrLost) onto the screen
    for(int i = 0; i < gameCount; i++)
    {
        cout << gameList[i].name << "\t" << gameList[i].level << "\t" << gameList[i].wonOrLost << "\n";
    }
	out << "\n***********************************\n";
	out << "Name\t" << "Level\t" << "won or lost\n";
	//use a loop to print the array (name, level, WonOrLost) into the file
    for(int i = 0; i < gameCount; i++)
    {
        out << gameList[i].name << "\t" << gameList[i].level << "\t" << gameList[i].wonOrLost << "\n";
    }
	//close the file
	out.close();

}


//*************************************************************************************
//Name:  PlayOneRound
//Precondition: The data variable (string) and object (gameNumberGuess) have been declared
//			the string has a value before calling this function
//Postcondition: One round of the game Number Guess has been completed
//Description:  Plays one round of the game Number Guess
//*************************************************************************************

void PlayOneRound(const string& name, gameNumberGuess& currentGame)
{
	//set up level
    SetUpLevel(currentGame);
	//generate the random number solution
	GenerateSolutionNumber(currentGame);

    //reminds the user how many guesses they have
    cout << "REMINDER\n" << "You have " << currentGame.maxGuesses << " guesses."<< endl;

	//initalize bool and high/low values
	currentGame.above = 0;
	currentGame.below = 0;
	currentGame.smallNum = 1;
	currentGame.largeNum = currentGame.upperValue;

	cout << "PLAY small: " << currentGame.smallNum << endl;
	cout << "PLAY large: " << currentGame.largeNum << endl;

	//loop header, counting loop for the number of guesses
	for (int i = 1; i <= currentGame.maxGuesses; i++)
	{
		//tell the user what guess number they are on
        cout << "You are on Guess " << i << " of " << currentGame.maxGuesses;
		//get the next guess
        GetGuessInput(currentGame);
		//reset above and below bool values to false
		currentGame.below = 0;
		currentGame.above = 0;

		if (ProcessGuess(currentGame) == true)
		{
			cout << "\nYou won that round, " << name << "!\n";
            currentGame.wonOrLost = true;
			i = currentGame.maxGuesses; //stops the loop without a break statement
		} else 
        {
            cout << "\nYou lost that round, " << name << "!\n";
            currentGame.wonOrLost = false;
        }
	}
	//display the solution when they win or lose
    cout << "\nThe solution is " << currentGame.solution << endl;
}

//*************************************************************************************
//Name:  SetUpLevel
//Precondition: The object (gameNumberGuess) has been declared before calling this function
//Postcondition: The member variables have been reset for a round of the game
//Description:  Sets up one round of the game
//*************************************************************************************


void SetUpLevel(gameNumberGuess& currentGame)
{
	cout << "Level 1: 10 guesses, ranging from 1 to 3619" << endl; 
    cout << "Level 2: 4 guesses, ranging from 1 to 61903" << endl;
    cout << "Which level would you like to play?(1 or 2)"; 
    cin >> currentGame.level;
    cout << "\nYou selected Level " << currentGame.level << endl;

	if (currentGame.level == 1)
	{
		currentGame.upperValue = 3619;
		currentGame.maxGuesses = 10;
	}
	else if(currentGame.level == 2)
    {
        currentGame.upperValue = 61903;
        currentGame.maxGuesses = 4;
    }
	else  cout << "That is not a valid level. Enter 1 or 2\n";
}


//*************************************************************************************
//Name:  GetGuessInput
//Precondition: The object (gameNumberGuess) has been declared before calling this function
//Postcondition: The user has entered a guess 
//Description:  Displays the range, prompts, and gets the next guess from the user
//*************************************************************************************

void GetGuessInput(gameNumberGuess& currentGame)
{

	if (currentGame.below)
	{
		if (currentGame.smallNum < currentGame.currentGuess)
		{
			currentGame.smallNum = currentGame.currentGuess;
		}
	}
	if (currentGame.above)
    {
        if (currentGame.largeNum > currentGame.currentGuess)
		{
			currentGame.largeNum = currentGame.currentGuess;
		}
    }

	cout << "\nEnter a guess between " << currentGame.smallNum << " and " << currentGame.largeNum << " : ";
	cin >> currentGame.currentGuess;
}

//*************************************************************************************
//Name:  ProcessGuess
//Precondition: State what is true before the function is called.
//Postcondition: State what is true after the function has executed.
//Description:  returns true(guess matches solution) or false (lets the user know if the guess was too high or too low)
//*************************************************************************************

bool ProcessGuess(gameNumberGuess& currentGame)
{
	if (currentGame.currentGuess > currentGame.solution)
	{
		cout << "\nYour guess was too high.";
		currentGame.above = true;
		return false;
	}
    else if (currentGame.currentGuess < currentGame.solution)
    {
        cout << "\nYour guess was too low.";
		currentGame.below = true;
		return false;
    }
	else 
	{
		cout << "\nYou guessed correctly!";
		return true;
	}

}

//*************************************************************************************
//Name:  GenerateSolutionNumber
//Precondition: State what is true before the function is called.
//Postcondition: State what is true after the function has executed.
//Description:  Generates the solution number in the correct range
//*************************************************************************************

void GenerateSolutionNumber(gameNumberGuess& currentGame)
{

	srand((unsigned)time(0));
	currentGame.solution = 1 + rand() % currentGame.upperValue;
	
}