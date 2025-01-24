#pragma comment(lib, "winmm.lib")
#include <iostream>
#include <conio.h>
#include <fstream>
#include <windows.h>
#include<cstdlib>
#include<sstream>
#include<vector>
#include<iomanip>
#include<string>
#include<chrono>
#include<algorithm>
using namespace std;
class Node
{
public:
	char data;
	Node* left;
	Node* right;
	Node()
	{
		left = NULL;
		right = NULL;
	}
};
class BST
{
private:
	Node* root;
public:
	BST();
	bool isEmpty();
	void insert(char item);
	bool search(char item);
	void preOrder(Node* Root);
	void inOrder(Node* Root);
	void postOrder(Node* Root);
	long long countLeafNodes(Node* Root);
	long long countNonLeafNodes(Node* Root);
	long long getSize(Node* Root);
	int getMax(Node* Root);
	int getSmallest(Node* Root);
	Node* getRoot();
	void setRoot(Node* Root);
	void cleanBST(Node* Root);
	~BST();
};
void BST::cleanBST(Node* Root)
{
	if (root == NULL || Root == NULL)
	{
		return;
	}
	cleanBST(Root->left);
	cleanBST(Root->right);
	delete Root;
	root = NULL;
}
BST::BST()
{
	root = NULL;
}
bool BST::isEmpty()
{
	return (root == NULL);
}

void BST::insert(char item)
{
	Node* temp = new Node();
	temp->data = item;
	if (isEmpty())
	{
		root = temp;
		return;
	}
	Node* parent = NULL;
	Node* traverse = root;
	while (1)
	{
		if (traverse == NULL)
		{
			if (temp->data > parent->data)
			{
				parent->right = temp;
				break;
			}
			if (temp->data < parent->data)
			{
				parent->left = temp;
				break;
			}
		}
		if (traverse->data == temp->data)
		{
			delete temp;
			return;
		}
		if (temp->data > traverse->data)
		{
			parent = traverse;
			traverse = traverse->right;
			continue;
		}
		if (temp->data < traverse->data)
		{
			parent = traverse;
			traverse = traverse->left;
			continue;
		}
	}
}
bool BST::search(char item)
{
	Node* traverse = root;
	while (1)
	{
		if (traverse == NULL)
		{
			return false;
		}
		if (item == traverse->data)
		{
			return true;
		}
		if (item > traverse->data)
		{
			traverse = traverse->right;
			continue;
		}
		if (item < traverse->data)
		{
			traverse = traverse->left;
			continue;
		}
	}
}
void BST::preOrder(Node* Root)
{
	if (Root == NULL)
	{
		return;
	}
	cout << Root->data << ' ';
	preOrder(Root->left);
	preOrder(Root->right);
}
void BST::inOrder(Node* Root)
{
	if (Root == NULL)
	{
		return;
	}
	inOrder(Root->left);
	cout << Root->data << ' ';
	inOrder(Root->right);
}
void BST::postOrder(Node* Root)
{
	if (Root == NULL)
	{
		return;
	}
	postOrder(Root->left);
	postOrder(Root->right);
	cout << Root->data << ' ';
}
long long BST::countLeafNodes(Node* Root)
{
	if (Root == NULL)
	{
		return 0;
	}
	if (Root->left == NULL && Root->right == NULL)
	{
		return 1;
	}
	return countLeafNodes(Root->left) + countLeafNodes(Root->right);
}
long long BST::countNonLeafNodes(Node* Root)
{
	if (Root == NULL)
	{
		return 0;
	}
	if (Root->left == NULL && Root->right == NULL)
	{
		return 0;
	}
	return 1 + countNonLeafNodes(Root->left) + countNonLeafNodes(Root->right);
}
long long BST::getSize(Node* Root)
{
	if (Root == NULL)
	{
		return 0;
	}
	return 1 + getSize(Root->left) + getSize(Root->right);
}
int BST::getMax(Node* Root)
{
	if (Root == NULL)
	{
		return 0;
	}
	if (Root->right == NULL)
	{
		return Root->data;
	}
	return getMax(Root->right);
}
int BST::getSmallest(Node* Root)
{
	if (Root == NULL)
	{
		return 0;
	}
	if (Root->left == NULL)
	{
		return Root->data;
	}
	return getSmallest(Root->left);
}
Node* BST::getRoot()
{
	return root;
}
void BST::setRoot(Node* Root)
{
	root = Root;
}
BST::~BST()
{
	cleanBST(root);
}
class Wordscapes {
private:
	string toUse;										//Input word from file
	BST toSearch;										//To be stored in here for searching. Max amount of searches will be n = 30
	short CONTROL_VARIABLE;
	string playerName;

public:
	Wordscapes()
	{
		srand(static_cast<unsigned int>(time(0)));
		//Constructor randomizes seed based on current time
		toUse = "";										//Constructor initializes the string with NULL. BST already has a constructor so need to
		CONTROL_VARIABLE = 6;							//initialize BST
	}
	void takingInput()
	{
		ifstream fin("Dictionary.txt");						//My dictionary of capital 5 letter words
		fin.seekg(0, ios::end);								//Jump to the last byte which is the last character in the file
		streamoff wordNum = (fin.tellg() / 7) + 1;
		//Divide the total number of bytes by 5(Number of letters in each word) + 2(2 bytes taken
		fin.seekg((rand() % wordNum) * 7, ios::beg);		//by \n). Then we choose a random word by taking mod of random number by total number of
		fin >> toUse;										//words and multiply by number of bytes for jumping to the starting byte of the chosen
		fin.close();										//word. We input the word and close the file.
	}
	void storeBST()
	{
		toSearch.cleanBST(toSearch.getRoot());				//If a previous word was stored in the tree we need to clean it.
		if (toUse.size())									//If the size of the word is greater than 0 then we store in BST. Just a small error handle
		{
			for (unsigned short loop = 0; loop < toUse.size(); loop++)
			{
				toSearch.insert(toUse[loop]);				//Insert every character in the BST
			}
		}
	}
	void printTitle()						//Prints the title of the game
	{
		system("color 6");
		cout << " \t\t\t\t__          __           _" << endl;
		cout << " \t\t\t\t\\ \\        / /          | |" << endl;
		cout << " \t\t\t\t \\ \\  /\\  / /__  _ __ __| |___  ___ __ _ _ __   ___  ___" << endl;
		cout << " \t\t\t\t  \\ \\/  \\/ / _ \\| '__/ _` / __|/ __/ _` | '_ \\ / _ \\/ __|" << endl;
		cout << " \t\t\t\t   \\  /\\  / (_) | | | (_| \\__ \\ (_| (_| | |_) |  __/\\__ \\" << endl;
		cout << " \t\t\t\t    \\/  \\/ \\___/|_|  \\__,_|___/\\___\\__,_| .__/ \\___||___/" << endl;
		cout << " \t\t\t\t                                        | |" << endl;
		cout << " \t\t\t\t                                        |_|" << endl;
		cout << endl << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
	void printCurrentWord(HANDLE& h, string& temp, unsigned short colorArray[])	//Prints the word supplied in temp with correct color codes
	{
		cout << "WORD:                                ";
		for (unsigned short loop = 0; loop < 5; loop++)
		{
			if (!toSearch.search(temp[loop])) {
				colorArray[loop] = 190;  // Change this line to set a different default color
			}
			cout << "|";									//Prints start of column in normal terminal color
			SetConsoleTextAttribute(h, colorArray[loop]);   //Change the color of the next character to be printed to correct code provided in array
			cout << temp[loop];								//Print the character
			SetConsoleTextAttribute(h, 7);					//Reset the color to default
			cout << "|";									//Print the end of current column
		}
		cout << "\n";										//Move to next line
	}
	void askInput(string& temp)
	{
		cout << "\n\nPlease enter an Uppercase 5 letter word:\t     ";		//Ask for input to be checked

		cin >> temp;
	}
	void firstErrorHandle(HANDLE& h, string temp[], unsigned short colorArray[][5], unsigned short counter)
	{
		bool errorer = true;					//Checks for error and then handles them        
		ifstream fin("Dictionary.txt");			//Opening file to check if it's a valid word. Will also be specified in help section
		string checker;							//Temp input from file				
		while (!fin.eof())
		{
			fin >> checker;
			if (checker.substr(0, 5) == temp[counter + 1])	//If the word entered by user actually exists in the file we update the error handler
			{
				errorer = false;				//Means no need to error handle
				break;
			}
		}
		fin.close();							//Close the file
		for (unsigned long long loop = 0; loop < temp[counter + 1].size(); loop++)	//Checking if the entered word is uppercase or not
		{
			if (temp[counter + 1][loop] < 'A' || temp[counter + 1][loop] > 'Z')
			{
				errorer = true;					//If a non uppercase letter is found then error handle
				break;
			}
		}
		while (temp[counter + 1].size() != 5 || errorer)			//If the size is not 5 or another error condition was encountered
		{
			system("CLS");
			for (unsigned short loop = 5; loop > 0; loop--)			//Ask the player to enter again
			{
				cout << "Please enter correctly again (" << loop << ")";
				Sleep(800);
				system("CLS");
			}
			printTitle();											//Bring the old screen back by reprinting the title and everything
			for (unsigned short loop = 0; loop <= counter; loop++)  //that followed
			{
				printCurrentWord(h, temp[loop], colorArray[loop]);
			}
			askInput(temp[counter + 1]);							//Prompt for input
			errorer = false;
			for (unsigned long long loop = 0; loop < temp[counter + 1].size(); loop++) //Checking if the new entered word is uppercase or not
			{
				if (temp[counter + 1][loop] < 'A' || temp[counter + 1][loop] > 'Z')
				{
					errorer = true;				//If a non uppercase letter is found then error handle
					break;
				}
			}
		}
	}
	void checkPresence(string& temp, unsigned short colorArray[])  //Checks the characters if they are in the actual word or not
	{
		for (unsigned short loop = 0; loop < 5; loop++)
		{
			if (toSearch.search(temp[loop]))		//If the letter is present in the word then
			{
				if (toUse[loop] == temp[loop])		//If the letter is present at the same location as is encountered in the user string
				{
					colorArray[loop] = 47;			//The word is at the correct location so update the color which is green
					continue;						//check next
				}
				colorArray[loop] = 111;				//If the letter is present in the word but not at the same location it is encountered then
				continue;							//update the corresponding color which is gold
			}
			colorArray[loop] = 64;					//If the letter was not found then update the color which is red
		}
	}
	bool winCheck(unsigned short colorArray[]) {
		for (unsigned short loop = 0; loop < 5; loop++) {
			if (colorArray[loop] != 47) {
				return false;
			}
		}
		return true;  // Make sure to return a value in all cases
	}
	void provideHint() {
		int hintCount = 5; // can adjust this count based on your preference
		vector<int> hintIndices;

		while (hintIndices.size() < hintCount) {
			int hintIndex = rand() % 5;
			if (find(hintIndices.begin(), hintIndices.end(), hintIndex) == hintIndices.end()) {
				hintIndices.push_back(hintIndex);
			}
		}

		cout << "\n\nHint: ";
		for (int index : hintIndices) {
			char hintLetter = toUse[index];
			cout << "Letter at position " << index + 1 << " is '" << hintLetter << "'. ";
		}
		cout << "\n";
	}
	void run()
	{
		cout << "Enter your name: ";
		cin >> playerName;
		auto startTime = chrono::high_resolution_clock::now(); // Capture start time here


		unsigned short count = 0;			//Count for how many tries the user took to guess the letter
		takingInput();						//Getting a word
		storeBST();							//Storing the word
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);			//Getting the terminal access for color changing
		string temp[7] = { "     " ,"     ","     ","     ","     ","     ", "     " };   //Save every input made by user for interfacing
		unsigned short colorArray[7][5] = { { 64, 64, 64, 64, 64 },				//Corresponding color codes for each letter in each word
											{ 64, 64, 64, 64, 64 },
											{ 64, 64, 64, 64, 64 },
											{ 64, 64, 64, 64, 64 },
											{ 64, 64, 64, 64, 64 },
											{ 64, 64, 64, 64, 64 },
											{ 64, 64, 64, 64, 64 } };
		bool win = false;												//Win status
		for (unsigned short counter = 0; counter < 6; counter++)		//Give the user 6 tries
		{
			if (win = winCheck(colorArray[counter]))					//exit condition for winning
			{
				break;
			}
			printTitle();								//Start interfacing
			for (unsigned short counter1 = 0; counter1 <= counter; counter1++)		//Print all the tries that have been made till now
			{
				printCurrentWord(hConsole, temp[counter1], colorArray[counter1]);   //Pass each try to be printed
			}
			cout << "\n\nDo you want a hint? (y/n): ";
			char hintChoice;
			cin >> hintChoice;

			if (hintChoice == 'y' || hintChoice == 'Y') {
				provideHint(); // Call the provideHint() method
			}
			askInput(temp[counter + 1]);								//Ask for input
			firstErrorHandle(hConsole, temp, colorArray, counter);		//Error handle the input
			checkPresence(temp[counter + 1], colorArray[counter + 1]);	//Check if the current input is correct or not
			count++;
			system("CLS");												//Clean for next input
		}
		auto endTime = chrono::high_resolution_clock::now();
		chrono::duration<double> elapsedTime = endTime - startTime;
		double seconds = elapsedTime.count();

		printTitle();								//Printing all the tries the user made in the whole game
		for (unsigned short counter1 = 0; counter1 <= count; counter1++)
		{
			printCurrentWord(hConsole, temp[counter1], colorArray[counter1]);
		}
		if (win)						//Self explanatory
		{
			cout << "\n\n\n\t\t\tYou win!";
			cout << "\n\n\t\t\tTime taken: " << seconds << " seconds\n";
			storeLeaderboard(playerName, seconds);
		}
		else
		{
			cout << "\n\n\n\t\t\tYou lose";
			cout << "\n\n\t\t\tTime taken: " << seconds << " seconds\n";

		}

		Sleep(3000);					//Start new game
		system("CLS");
		cout << "Returning to Main menu.";
		Sleep(3000);
		system("CLS");
		playInterface();
	}
	void storeLeaderboard(string playerName, double e)
	{

		ofstream leaderboardFile("Leaderboard.txt", ios::app);
		if (leaderboardFile.is_open())
		{
			leaderboardFile << playerName << " " << e << " seconds\n";
			leaderboardFile.close();
		}
		else
		{
			cout << "Error opening leaderboard file.\n";
		}
	}
	void displayLeaderboard() {
		ifstream leaderboardFile("Leaderboard.txt");
		if (leaderboardFile.is_open()) {
			vector<pair<string, double>> leaderboard;
			string line;

			while (getline(leaderboardFile, line)) {
				istringstream iss(line);
				string name;
				double time;

				if (iss >> name >> time) {
					leaderboard.push_back({ name, time });
				}
			}

			sort(leaderboard.begin(), leaderboard.end(), [](const auto& a, const auto& b) {
				return a.second < b.second;
				});

			if (!leaderboard.empty()) {
				for (const auto& entry : leaderboard) {
					cout << "\t\t\t\t\t" << entry.first << "\t" << entry.second << " seconds\n";
				}
			}
			else {
				cout << "\n\n\t\t\t\t\tNo games played yet.\n";
			}

			leaderboardFile.close();
		}
		else {
			cout << "\n\n\t\t\t\t\tNo games played yet.\n";
		}
	}

	void playInterface()
	{
		if (CONTROL_VARIABLE == 0)
		{
			PlaySound(TEXT("Abdullah.wav"), NULL, SND_LOOP | SND_ASYNC);
		}
		else if (CONTROL_VARIABLE == 1)
		{
			PlaySound(TEXT("Awaz.wav"), NULL, SND_LOOP | SND_ASYNC);
		}
		else if (CONTROL_VARIABLE == 2)
		{
			PlaySound(TEXT("Sooper.wav"), NULL, SND_LOOP | SND_ASYNC);
		}

		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		short enter = '1';
		short arrowKey = '1';
		short enter1 = 189;
		short enter2 = 7;
		short enter3 = 7;
		short enter4 = 7;
		short enter5 = 7;
		short enter6 = 7;
		string coutArray[6];
		coutArray[0].erase();
		coutArray[0] += "\n\n\t\t\t\t\t\tStart Game";
		coutArray[1].erase();
		coutArray[1] += "\n\n\t\t\t\t\t\tDefault Music";
		coutArray[2].erase();
		coutArray[2] += "\n\n\t\t\t\t\t\tLeaderboard";
		coutArray[3].erase();
		coutArray[3] += "\n\n\t\t\t\t\t\tHelp";
		coutArray[4].erase();
		coutArray[4] += "\n\n\t\t\t\t\t\tExit";
		short coutArrayIndex = 0;
		system("CLS");
		printTitle();
		cout << "\n\n\n\t\t\t";
		SetConsoleTextAttribute(h, enter1);
		cout << coutArray[0];
		SetConsoleTextAttribute(h, enter2);
		cout << coutArray[1];
		SetConsoleTextAttribute(h, enter3);
		cout << coutArray[2];
		SetConsoleTextAttribute(h, enter4);
		cout << coutArray[3];
		SetConsoleTextAttribute(h, enter5);
		cout << coutArray[4];
		SetConsoleTextAttribute(h, enter6);
		cout << coutArray[5];
		SetConsoleTextAttribute(h, 7);
		cout << endl;

		while (enter != 13)
		{
			enter = _getch();
			if (enter == 13)
			{
				break;
			}
			if (enter == 224)
			{
				arrowKey = _getch();
				if (arrowKey == 72)
				{
					if (coutArrayIndex == 0)
					{
						coutArrayIndex = 4;
					}
					else
					{
						coutArrayIndex--;
					}
				}
				else if (arrowKey == 80)
				{
					if (coutArrayIndex == 4)
					{
						coutArrayIndex = 0;
					}
					else
					{
						coutArrayIndex++;
					}
				}
				if (coutArrayIndex == 0)
				{
					enter1 = 189;
					enter2 = 7;
					enter3 = 7;
					enter4 = 7;
					enter5 = 7;
					enter6 = 7;
				}
				else if (coutArrayIndex == 1)
				{
					enter1 = 7;
					enter2 = 189;
					enter3 = 7;
					enter4 = 7;
					enter5 = 7;
					enter6 = 7;
				}
				else if (coutArrayIndex == 2)
				{
					enter1 = 7;
					enter2 = 7;
					enter3 = 189;
					enter4 = 7;
					enter5 = 7;
					enter6 = 7;
				}
				else if (coutArrayIndex == 3)
				{
					enter1 = 7;
					enter2 = 7;
					enter3 = 7;
					enter4 = 189;
					enter5 = 7;
					enter6 = 7;
				}
				else if (coutArrayIndex == 4)
				{
					enter1 = 7;
					enter2 = 7;
					enter3 = 7;
					enter4 = 7;
					enter5 = 189;
					enter6 = 7;
				}
				system("CLS");
				printTitle();
				cout << "\n\n\n\t\t\t";
				SetConsoleTextAttribute(h, enter1);
				cout << coutArray[0];
				SetConsoleTextAttribute(h, enter2);
				cout << coutArray[1];
				SetConsoleTextAttribute(h, enter3);
				cout << coutArray[2];
				SetConsoleTextAttribute(h, enter4);
				cout << coutArray[3];
				SetConsoleTextAttribute(h, enter5);
				cout << coutArray[4];
				SetConsoleTextAttribute(h, enter6);
				cout << coutArray[5];
				SetConsoleTextAttribute(h, 7);
				cout << endl;
			}
			else
			{
				continue;
			}
		}

		if (coutArrayIndex == 0)
		{
			system("CLS");
			run();
			return;
		}
		else if (coutArrayIndex == 1)
		{
			system("CLS");
			printTitle();
			HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
			short enter = '1';
			short arrowKey = '1';
			short enter1 = BACKGROUND_GREEN;
			short enter2 = 7;
			short enter3 = 7;
			string coutArray[6];
			coutArray[0].erase();
			coutArray[0] += "\n\n\t\t\t\t\t\tMusic 1";
			coutArray[1].erase();
			coutArray[1] += "\n\n\t\t\t\t\t\tMusic 2";
			coutArray[2].erase();
			coutArray[2] += "\n\n\t\t\t\t\t\tMusic 3";
			coutArray[3].erase();
			short coutArrayIndex = 0;
			system("CLS");
			printTitle();
			cout << "\n\n\n\t\t\t";
			SetConsoleTextAttribute(h, enter1);
			cout << coutArray[0];
			SetConsoleTextAttribute(h, enter2);
			cout << coutArray[1];
			SetConsoleTextAttribute(h, enter3);
			cout << coutArray[2];
			SetConsoleTextAttribute(h, 7);
			cout << endl;
			while (enter != 13)
			{
				enter = _getch();
				if (enter == 13)
				{
					break;
				}
				else if (enter == 27)
				{
					playInterface();
					return;
				}

				// Enter = 13 and \n = 10
				if (enter == 224)
				{
					arrowKey = _getch();
					if (arrowKey == 72) // up
					{
						if (coutArrayIndex == 0)
						{
							coutArrayIndex = 5;
						}
						else
						{
							coutArrayIndex--;
						}
					}
					else if (arrowKey == 80) // down
					{
						if (coutArrayIndex == 5)
						{
							coutArrayIndex = 0;
						}
						else
						{
							coutArrayIndex++;
						}
					}
					if (coutArrayIndex == 0)
					{
						enter1 = BACKGROUND_GREEN;
						enter2 = 7;
						enter3 = 7;
					}
					else if (coutArrayIndex == 1)
					{
						enter1 = 7;
						enter2 = BACKGROUND_GREEN;
						enter3 = 7;
					}
					else if (coutArrayIndex == 2)
					{
						enter1 = 7;
						enter2 = 7;
						enter3 = BACKGROUND_GREEN;
					}

					system("CLS");
					printTitle();
					cout << "\n\n\n\t\t\t";
					SetConsoleTextAttribute(h, enter1);
					cout << "" << coutArray[0];
					SetConsoleTextAttribute(h, enter2);
					cout << coutArray[1];
					SetConsoleTextAttribute(h, enter3);
					cout << coutArray[2];
					SetConsoleTextAttribute(h, 7);
					cout << endl;
				}
				else
				{
					continue;
				}
			}
			if (coutArrayIndex == 0) // Music 1
			{
				PlaySound(TEXT("Abdullah.wav"), NULL, SND_LOOP | SND_ASYNC);
				CONTROL_VARIABLE = 0;
				playInterface();
				return;
			}
			else if (coutArrayIndex == 1) // Music 2
			{
				PlaySound(TEXT("Awaz.wav"), NULL, SND_LOOP | SND_ASYNC);
				CONTROL_VARIABLE = 1;
				playInterface();
				return;
			}
			else if (coutArrayIndex == 2) // Music 3
			{
				PlaySound(TEXT("Sooper.wav"), NULL, SND_LOOP | SND_ASYNC);
				CONTROL_VARIABLE = 2;
				playInterface();
				return;
			}
			// play();
			return;
		}
		else if (coutArrayIndex == 2) // Leaderboard
		{
			system("CLS");
			printTitle();
			SetConsoleTextAttribute(h, 96);
			cout << "\n\n\n\t\t\t\t\tLeaderboard" << endl << endl << endl;
			SetConsoleTextAttribute(h, 7);
			displayLeaderboard();
			int key = _getch();
			playInterface();
			return;
		}
		else if (coutArrayIndex == 3) // Help menu
		{
			system("CLS");
			printTitle();
			SetConsoleTextAttribute(h, 96);
			cout << "\n\n\n\t\t\t\t\tHow To Play" << endl << endl << endl;
			SetConsoleTextAttribute(h, 7);
			cout << "\n\n\n\t\tGuess the Word in 6 tries\n"
				<< "\t\tEach guess must be a valid 5-letter word. The color of the tiles will change to show how close your guess was to the word\n"
				<< "\t\tWhen you Enter a word, If the respected Tile turns Green, It means the respected Tile Letter is in the Word and in the correct Tile\n"
				<< "\t\t.IF the respected Tile turns Yellow, It means the respected Tile Letter is in the Word and in the wrong spot/Tile\n";
			int key = _getch();
			playInterface();
			return;
		}
		else if (coutArrayIndex == 4) // Exit
		{
			cout << "\n\n\n\n\n\n\n";
			exit(0);
		}

		playInterface();
		return;
	}
};
int main()
{
	Wordscapes a;
	a.playInterface();
	int key = _getch();
	return 0;
}
