/*
  Divyasiddha Shivashok
  Co-developed with Rohit Joshi
*/
//Battleship Project
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <time.h>
using namespace std;

//Initializes the two integer arrays that will be used as the grids
int userGrid[8][8], ComputerGrid[8][8]; 

//This variable will help the program identify a winner
bool PlayerWin, ComputerWin = false; 

int NumShips = 5; //will store the number of ships for the enemy and player to have

/*
To follow along for the game:
 0 = Empty space(Ocean)
 1 = Ship placed here -> S
 2 = Missed Shot - M
 3 = Hit and Sunk - H
*/

//repeat will be used in multiple loops and functions throughout the code to alert the code if it needs to repeat a certain section or not
bool repeat = true; 

//Clear boards by setting everything to 0
void fill()
{
  for (int r = 0; r <= 7; r++)
  {
    for (int c = 0; c <= 7; c++)
    {
      userGrid[r][c] = 0;
    }
  }
  for (int x = 0; x <= 7; x++)
  {
    for (int y = 0; y <= 7; y++)
    {
      ComputerGrid[x][y] = 0;
    }
  }
}

//Print computer board(not showing computer ships)
void printComputerBoard() 
{
  cout << "\n\nEnemy board: (undiscovered ships are hidden)\n";
  for (int x = 0; x <= 7; x++)
  {
    cout << '\n' << x+1 << "  ";
    for (int y = 0; y <= 7; y++)
    {
      switch (ComputerGrid[x][y])
      {
        case 0: 
          cout << "0 ";
        break;
        
        case 1: 
          cout << "0 ";
        break;
        
        case 2: 
          cout << "M ";
        break;
        
        case 3: 
          cout << "H ";
        break;
      }
    }
  }
  //Display bottom letters to guide the player
  cout << "\n   A B C D E F G H \n";
  cout << '\n';
}

//this function will display the board of the player
void printUserBoard() 
{
  cout << "\n\nYour board:\n";
  for (int r = 0; r <= 7; r++)
  {
    cout << '\n' << r+1 << "  ";
    
    for (int c = 0; c <= 7; c++)
    {
      switch (userGrid[r][c])
      {
        case 0: cout << "0 ";
        break;
        case 1: cout << "S ";
        break;
        case 2: cout << "M ";
        break;
        case 3: cout << "H ";
        break;
      }
    }
  }
  cout << "\n   A B C D E F G H \n";
  cout << '\n';
}

//Randomly select positions of ships for computer board
void enemy_ship_position() 
{
  srand (time(NULL)); 
  for (int i = 1; i <= NumShips; i++)
  {
    int row = 0; 
    int column = 0;
    do
    { 
      //'repeat' is used to repeat if same spot is entered
      bool repeat = true;
    
      //sets the variable row and column to a random integer from 0 to 7
      row = rand() % 8; 
      column = rand() % 8;
    
      if (ComputerGrid[row][column] != 1)
      {
        ComputerGrid[row][column] = 1; 
        repeat = false;
      }
      else 
      {
        repeat = true;
      }
    }
    while (repeat == false);
    //Using our functions inside other ones
    printComputerBoard();
  }
}

//The Player chooses positions to hit on enemy board
void user_BOMB_position()
{
  /*
    cNum will be the column char 
    converted to int through 
    ASCII conversion algortihm
  */ 
  int row = 0, cNum = 0;
  char column;
  
  cout << "\nCaptain, the ship is at your command. Choose a location to hit.";
  
  printComputerBoard();
  
  do
  {
    repeat = false;
    
    cout << "Enter row of location(1-8): ";
    cin >> row;
    cout << "Enter column of location(A-H): ";
    cin >> column;
    
    //Decrement row to change it to index scale for array(0-7)
    row--;
    
    //Sets A through H to 0 - 7 using ASCII values
    cNum = column - 65;
    
    /*
      2 Conditions for proper input(for row and column)
      Output a way to re-enter 
    */
    if (row < 0 || row > 7 ) 
    {
      repeat = true; 
      cout << "Invalid Guess. Please enter a value between 1 and 8\n";
    }
    if (cNum < 0 || cNum > 7 )
    {
      repeat = true; 
      cout << "Make sure the column is between A and H\n"; 
    }
  }
  while (repeat == true);

  
  switch (ComputerGrid[row][cNum])
  {
    case 0: 
    {
      cout << "\nYikes. You missed!";
      ComputerGrid[row][cNum] = 2;
    }
    break;
  
    case 1:
    {
      cout << "\nYou sunk an enemy ship!\n";
      ComputerGrid[row][cNum] = 3;
    }
    break;
  
    case 2:
    {
      cout << "\nYou missed...again? Didn't you already shoot here and miss? Big L. Yikes.\n";
    }
    break;
  
    case 3:
    {
      cout << "\nWhat are you doing? You already sunk a ship in this spot! This one counts as a Miss. \n";
    }
    break;
  }
  printComputerBoard();
}

//Computer bomb positions, chosen randomly
void enemy_BOMB_position() 
{
  cout << "The enemy fires. Check the board for their attack location!\n";
  
  srand (time(NULL)); 
  
  int row = 0; 
  int column = 0; 
  do
  {
    //Repeat in the case of the same spot being chosen multiple times
    bool repeat = false; 

    //rand position
    row = rand() % 8; 
    column = rand() % 8;

    
    switch (userGrid[row][column])
    {
      case 0:
      {
        cout << "\nThe enemy has missed!";
        userGrid[row][column] = 2;
      }
      break;
      
      case 1: 
      {
        cout << "\nWe've lost a ship!\n";
        userGrid[row][column] = 3;
      }
      break;
      
      case 2: 
      {
        repeat = true;
      }
      break;
      
      case 3: 
      {
        repeat = true;
      }
      break;
    }
  }
  while (repeat == true);
  
  printUserBoard();
}

//this function will check if either party has won
void setWinner() 
{
  PlayerWin = true;
  ComputerWin = true;
  
  for (int r = 0; r <= 7; r++)
  {
    for (int c = 0; c <= 7; c++)
    {
      if (userGrid[r][c] == 1)
      {
        ComputerWin = false;
      }
    }
  }
  
  for (int x = 0; x <= 7; x++)
  {
    for (int y = 0; y <= 7; y++)
    {
      if (ComputerGrid[x][y] == 1)
      {
        PlayerWin = false;
      }
    }
  }
  
}



int main() 
{
  
  fill();

  //Game UI and design:
  cout << "Welcome to Battleship. Game directions will show up as you play along. Enjoy!\n\n";
 
  cout << "How many ships would you like to have?\n(Please enter a number between 1 and 6): ";
  cin >> NumShips;

  if (NumShips > 6 || NumShips < 1)
  {
    cout << "\nError - Invalid Value. Must be between 1-6(inclusive)\nPlease restart the game :( \n";
  }
  else
  {
    enemy_ship_position();

    cout << "\n\nOn your board, \"S\" represents a placed ship, \"0\" represents the 'unknown waters', \"M\" represents any missed shots, and \"H\" represents a sunk ship.\n\n";

    cout << "\n\nLet's get started. Where do your ships go, captain? For each row pick a number 1 through 8, and for each column pick a letter (capitals only) A through H\n\n";

    //Player choosing their own ships
    for (int count = 1; count <= NumShips; count++) 
    {
      repeat = false;
      
      string NumberEntry = "";
      
      switch (count)
      {
        case 1: 
        {
          NumberEntry = " first ";
        }
        break;
        
        case 2: 
        {
          NumberEntry = " second ";
        }
        break;
        
        case 3: 
          {
            NumberEntry = " third ";
          }
        break;
        
        case 4: 
          {
            NumberEntry = " fourth ";
          }
        break;
        
        case 5: 
          {
            NumberEntry = " fifth ";
          }
        break;
        
        case 6: 
          {
            NumberEntry = " sixth ";
          }
        break;
      }
      
      int PlayerRow;
      char PlayerColumn;
      //int version of char column inputted by user(ASCII)
      int PlayerColumnNumber = 0; 
      
      do
      {
        repeat = false;
        
        cout << "Row choice for your" << NumberEntry << "ship: ";
        cin >> PlayerRow;
        cout << "Column choice for your" << NumberEntry << "ship: ";
        cin >> PlayerColumn;

        //proper index for array, so we decrement
        PlayerRow--; 
        
        PlayerColumnNumber = PlayerColumn - 65;
        
        //Checks if row/column selection are properly inputted
        if (PlayerRow < 0 || PlayerRow > 7 )
        {
          repeat = true; 
          cout << "Make sure your row is between 1 and 8\n";
        }
        if (PlayerColumnNumber < 0 || PlayerColumnNumber > 7 )
        {
          repeat = true; 
          cout << "Make sure your column is between A and H\n";
        }

        if (userGrid[PlayerRow][PlayerColumnNumber]!= 0)
        {
          cout << "You can't place multiple ships on the same coordinate. Please try again. \n"; 
          repeat = true;
        }
      }
      while (repeat == true);
      
      //assigns a value of 1 to selected coordinates, representing a placed ship
      userGrid[PlayerRow][PlayerColumnNumber] = 1; 
      
      cout << "\nYour placed ships so far: \n";
      printUserBoard();
    }
    do 
    {
      user_BOMB_position();
      enemy_BOMB_position();
      setWinner();
    }
    while (PlayerWin == false && ComputerWin == false);
    
    if (PlayerWin == true) 
    {
      cout << "\n\nYou beat the BOT. Nice job. Hope you feel good. Now go touch grass.\n\n";
    }
    if (ComputerWin == true) 
    {
      cout << "\n\nBro, you lost to a randomized computer xD. L+ Ratio\n\n";
    }
  }
}

/*
Outside sources - JF - GeeksForGeeks
*/
