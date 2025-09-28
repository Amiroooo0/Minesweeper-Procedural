#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <ctime>
#include <iomanip>
#include <string>
#include <cstring>
#include <fstream>

// I have defined a number of color strings with their corresponding names for convenience
#define RED "31"
#define GREEN "32"
#define ORANGE "33"
#define BLUE "34"
#define MAGENTA "35"
#define WHITE "97"
#define BLACK "30"

using namespace std ;

// Prototype of major functions
unsigned short int menu (  ) ;
bool singleMode ( unsigned int & , unsigned int & , string &  ) ;
int  cursor ( int & , int & , char  , bool flgF = 0 ) ;
void fillTable ( int  , int  ) ;
bool strike ( int  , int  ) ;

// Prototype of minor functions
void sleepMilis ( unsigned int  ) ;
void hideCursor (  ) ;
void showCursor (  ) ;
void gotoXY ( int  , int  ) ;
void setColor ( const string&  ) ;
void unicode ( int  , int  ) ;
void color ( char  ) ;
void swapPlayerInfo ( int  , int  ) ;

// An struct for save players data
struct playerInfo
{
	string name ;
	unsigned short int flags ;
	unsigned int time ;
} ;


// Global variable

unsigned int writingsLocation [ 5 ] [ 2 ] ;
string writings [ 5 ] [ 2 ] , temp ;

char front [ 24 ] [ 24 ] [ 2 ] ;
unsigned int back [ 24 ] [ 24 ] [ 2 ] ;

playerInfo players [ 10000 ] ;

int main (  )
{
	unsigned int correctFlags = 0 , timeSpent = 0 , i = 0 , j , k ;
	string playerName = " " ;
	bool flgW = 0 ;
	
	while ( 1 )
	{
		correctFlags = 0 ; 
		timeSpent = 0 ;
		flgW = 0 ;
		playerName = " " ;
		
		switch ( menu ( ) ) // Each time call the menu, based on its output, we perform one of the menu's tasks
		{
			case 1 : // This case opens the single mode.
			{
				flgW = singleMode ( correctFlags , timeSpent , playerName ) ;
				// Call the single mode function with all the arguments that have been referenced
				// And store the output of the function, which indicates the user's win or loss, in a flag
				
				ofstream save ( "leaderboard" , ios::app ) ;
				save << playerName << " " << correctFlags << " " << timeSpent << flush << "\n" ;
				save . close (  ) ;
				// Open the file, save the user's information in it, and then close it
				
				if ( flgW ) // Based on the value of the flag, decide whether to declare the user a winner or a loser
				{
					system ( "cls" ) ;
					gotoXY ( 0 , 0 ) ;
					
					color ( 'l' ) ;
					cout << "╔═════════════════════════════════════════════════╗\n" ;
					cout << "║                                                 ║\n" ;
					cout << "║                    you won !                    ║\n" ;
					cout << "║ correct Flags :             time Spent :        ║\n" ;
					cout << "║                                                 ║\n" ;
					cout << "║             press enter to continue ...         ║\n" ;
					cout << "╚═════════════════════════════════════════════════╝\n" ;
					
					color ( 's' ) ;
					gotoXY ( 3 , 2 ) ;
					cout << "correct Flags : " << correctFlags ;
					gotoXY ( 3 , 30 ) ;
					cout << "time Spent : " << timeSpent ;
					gotoXY ( 5 , 14 ) ;
					cout << "press enter to continue ..." ;
					
					while ( getch (  ) != 13 ) ;
				}
				else
				{
					system ( "cls" ) ;
					gotoXY ( 0 , 0 ) ;
					
					color ( 'p' ) ;
					cout << "╔═════════════════════════════════════════════════╗\n" ;
					cout << "║                                                 ║\n" ;
					cout << "║                   you lost !                    ║\n" ;
					cout << "║ correct Flags :             time Spent :        ║\n" ;
					cout << "║                                                 ║\n" ;
					cout << "║             press enter to continue ...         ║\n" ;
					cout << "╚═════════════════════════════════════════════════╝\n" ;
					
					color ( 's' ) ;
					gotoXY ( 3 , 2 ) ;
					cout << "correct Flags : " << correctFlags ;
					gotoXY ( 3 , 30 ) ;
					cout << "time Spent : " << timeSpent ;
					gotoXY ( 5 , 14 ) ;
					cout << "press enter to continue ..." ;
					
					while ( getch (  ) != 13 ) ;
				}
				break ;
			}
			case 2 : // In this case, we display the leaderboard
			{
				system ( "cls" ) ;
				gotoXY ( 0 , 0 ) ;
				color ( 'a' ) ;
				cout << "╔═════════════════════════════════════════════════╗\n" ;
				cout << "║ Rank     Name          timeSpent  correctFlags  ║\n" ;
				cout << "║                                                 ║\n" ;
				cout << "║ 1        Amirooooo       183          100       ║\n" ;
				
				players [ 0 ] . name  = "Amirooooo" ; // Amirooooo is GOAT
				players [ 0 ] . time  = 183 ;
				players [ 0 ] . flags = 100 ;
				
				// Open the file, retrieve the data, and sort it right there
				// First by the number of correct flags, and second by the elapsed time
				ifstream save ( "leaderboard" ) ;
				for ( i = 1 ; save >> players [ i ] . name >> players [ i ] . flags >> players [ i ] . time ; i++ )
					for ( j = 1 ; j < i ; j++ )
						if ( players [ i ] . flags > players [ j ] . flags )
							swapPlayerInfo ( i , j ) ;
						else if ( players [ i ] . flags == players [ j ] . flags )
							if ( players [ i ] . time < players [ j ] . time )
								swapPlayerInfo ( i , j ) ;
				
				// Now, display data and close the file
				for ( j = 1 ; j <= i ; j++ )
				{
					gotoXY ( 3 + j , 0 ) ;
					cout << "║                                                 ║\n" ;
					
					gotoXY ( 3 + j , 2 ) ;
					cout << j + 1 ;
					
					gotoXY ( 3 + j , 11 ) ;
					cout << players [ j ] . name  ;
					
					gotoXY ( 3 + j , 40 ) ;
					cout << players [ j ] . flags ;
					
					gotoXY ( 3 + j , 27 ) ;
					cout << players [ j ] . time  ;
				}
				
				gotoXY ( 2 + j , 0 ) ;
				cout << "║                                                 ║\n" ;
				cout << "║             press enter to continue ...         ║\n" ;
				cout << "╚═════════════════════════════════════════════════╝\n" ;
				
				while ( getch (  ) != 13 ) ;
				save . close (  ) ;
				break ;
			}
			case 3 : // This case will be added in future updates , Stay tuned for future updates
			{
				system ( "cls" ) ;
				gotoXY ( 0 , 0 ) ;
				color ( 'm' ) ;
					cout << "╔═════════════════════════════════════════════════╗\n" ;
					cout << "║                                                 ║\n" ;
					cout << "║               🥰  coming soon  🥰               ║\n" ;
					cout << "║                                                 ║\n" ;
					cout << "║             press enter to continue ...         ║\n" ;
					cout << "║                                                 ║\n" ;
					cout << "╚═════════════════════════════════════════════════╝\n" ;
				while ( getch ( ) != 13 ) ;
				break ;	
			}
			case 4 : // In this case, we exit the game
			{
				system ( "cls" ) ;
				color ( 'w' ) ;
				return 0 ;
				break ;
			}
		}
	}  
}

unsigned short int menu (  ) // The menu function, each time it is called , provides an output that indicates the desired operation
{
	hideCursor (  ) ;
	int x = 5 , y = 24 , i , result = 2 ;
	system ( " cls " ) ;
	
	setColor ( "90" ) ;
	cout << "╔════════════════════════════════════════════════╗\n" ;
	cout << "║╲╲                                            ╱╱║\n" ;
	cout << "║  ╲╲                                        ╱╱  ║\n" ;
	cout << "║    ╲╲         📈 leaderboard 📉          ╱╱    ║\n" ;
	cout << "║      ╲╲                                ╱╱      ║\n" ;
	cout << "║        ╲╲             🢁              ╱╱        ║\n" ;
	cout << "║          ╲╲                        ╱╱          ║\n" ;
	cout << "║            ╔══════════════════════╗            ║\n" ;
	cout << "║            ║                      ║            ║\n" ;
	cout << "║            ║     mine sweeper     ║            ║\n" ;
	cout << "║  💣💣💣    ║                      ║    ☠ ☠ ☠   ║\n" ;
	cout << "║  single    ║      created by      ║    versus  ║\n" ;
	cout << "║   mode     ║                      ║     mode   ║\n" ;
	cout << "║  💣💣💣    ║      Amiroooooo      ║    ☠ ☠ ☠   ║\n" ;
	cout << "║            ║                      ║            ║\n" ;
	cout << "║            ╚══════════════════════╝            ║\n" ;
	cout << "║          ╱╱                       ╲╲           ║\n" ;
	cout << "║        ╱╱                           ╲╲         ║\n" ;
	cout << "║      ╱╱                               ╲╲       ║\n" ;
	cout << "║    ╱╱             ❌ exit ❌            ╲╲     ║\n" ;
	cout << "║  ╱╱                                       ╲╲   ║\n" ;
	cout << "║╱╱                                           ╲╲ ║\n" ;                                                            
	cout << "╠════════════════════════════════════════════════╣\n" ;
	cout << "║ hint : you can choose options with 'WASD' & 'E'║\n" ;
	cout << "╚════════════════════════════════════════════════╝\n" ;
	
	// The writings string is for the central components of the menu, which change color each time
	// Therefore, it is two-dimensional: one dimension contains the value, and the other contains its color
	
	writings [ 0 ] [ 0 ] = "Mine" ;
	writings [ 0 ] [ 1 ] = RED ;	
	
	writings [ 1 ] [ 0 ] = "Sweeper" ;
	writings [ 1 ] [ 1 ] = BLUE ;
	
	writings [ 2 ] [ 0 ] = "Created" ;
	writings [ 2 ] [ 1 ] = ORANGE ;
	
	writings [ 3 ] [ 0 ] = "by" ;
	writings [ 3 ] [ 1 ] = GREEN ;
	
	writings [ 4 ] [ 0 ] = "Amiroooooo" ;
	writings [ 4 ] [ 1 ] = MAGENTA ;
	
	// Here, the position of each central menu item is stored and initialized
	
	writingsLocation [ 0 ] [ 0 ] = 9  ;
	writingsLocation [ 0 ] [ 1 ] = 19 ;
	
	writingsLocation [ 1 ] [ 0 ] = 9  ;
	writingsLocation [ 1 ] [ 1 ] = 24 ;
	
	writingsLocation [ 2 ] [ 0 ] = 11 ;
	writingsLocation [ 2 ] [ 1 ] = 20 ;
	
	writingsLocation [ 3 ] [ 0 ] = 11 ;
	writingsLocation [ 3 ] [ 1 ] = 28 ;
	
	writingsLocation [ 4 ] [ 0 ] = 13 ;
	writingsLocation [ 4 ] [ 1 ] = 20 ;
	
	while ( 1 ) // Print each member in an infinite loop
	{
		for ( i = 0 ; i < 5 ; i++ )
		{
			gotoXY ( writingsLocation [ i ] [ 0 ] , writingsLocation [ i ] [ 1 ] ) ;
			setColor ( writings [ i ] [ 1 ] ) ;
			cout << writings [ i ] [ 0 ] ;
		}
		
		// Change the color of each member cyclically
		temp = writings [ 0 ] [ 1 ] ;
		writings [ 0 ] [ 1 ] = writings [ 1 ] [ 1 ] ;
		writings [ 1 ] [ 1 ] = writings [ 2 ] [ 1 ] ;
		writings [ 2 ] [ 1 ] = writings [ 3 ] [ 1 ] ;
		writings [ 3 ] [ 1 ] = writings [ 4 ] [ 1 ] ;
		writings [ 4 ] [ 1 ] = temp ;
		
		if ( _kbhit ( ) ) // If the user presses a key, the program enters this condition and get a character
		{
			char order = getch (  ) ; 
			gotoXY ( x , y ) ;
			setColor ( BLACK ) ;
			cout << "🢂" ; // This line removes the previous arrow
			switch ( order ) // Here, based on each character, the selection is moved or confirmed, and the function's output is returned
			{
				case 'w' : case 'W' :
					cout << "\b " ;
					gotoXY ( 5 , 24 ) ;
					x = 5 ;
					y = 24 ;
					setColor ( WHITE ) ;
					cout << "🢁" ;
					result = 2 ;
					break ;
				case 'a' : case 'A' :
					cout << "\b " ;
					gotoXY ( 11 , 10 ) ;
					x = 11 ;
					y = 10 ;
					setColor ( WHITE ) ;
					cout << "🢀" ;
					result = 1 ;
					break ;
				case 's' : case 'S' :
					cout << "\b " ;
					gotoXY ( 17 , 24 ) ;
					x = 17 ;
					y = 24 ;
					setColor ( WHITE ) ;
					cout << "🢃" ;
					result = 4 ;
					break ;
				case 'd' : case 'D' :
					cout << "\b " ;
					gotoXY ( 11 , 38 ) ;
					x = 11 ;
					y = 38 ;
					setColor ( WHITE ) ;
					cout << "🢂" ;
					result = 3 ;
					break ;
				case 'e' : case 'E' :
					return result ;
			}
		}
		sleepMilis ( 500 ) ; // It delays each color change by 500 milliseconds
	}
}

bool singleMode ( unsigned int &flgR , unsigned int &finalTime , string &name ) // This function is for single-player mode
{
	int i , j , startTime , flgNum = 100 , con ;
	char order ;
	
	system ( "cls" ) ;
	setColor ( WHITE ) ;
	showCursor (  ) ;
	
	cout << "╔════════════════════════════════════════════════════╗\n" ;
	cout << "║                                                    ║\n" ;
	cout << "║   guide : you can switch between cells with 'WASD' ║\n" ;
	cout << "║  and select them with 'E' and freeze them with 'F' ║\n" ;
	cout << "║          what is your name ?                       ║\n" ;
	cout << "║                                                    ║\n" ;
	cout << "╚════════════════════════════════════════════════════╝\n" ;
	
	gotoXY ( 4 , 31 ) ;
	color ( 't' ) ;
	getline ( cin , name ) ;
	
	// Table printing operation
	
	hideCursor ( ) ;
	system ( "cls" ) ;
	setColor ( ORANGE ) ;
	
	cout << "╔═════════════════════════════════════════════════╗\n" ;
	for ( i = 0 ; i < 24 ; i++ )
	{
		cout << "║                                                 ║\n" ;
		for ( j = 0 ; j < 24 ; j++ )
			{
				front [ i ] [ j ] [ 0 ] = '?' ;
				front [ i ] [ j ] [ 1 ] = 'w' ;
				back  [ i ] [ j ] [ 0 ] =  0  ;
				back  [ i ] [ j ] [ 1 ] =  1  ;
			}
	}
	cout << "╠═════════════════════════════════════════════════╣\n" ;
	cout << "║                                                 ║\n" ;
	cout << "║                                                 ║\n" ;
	cout << "║                                                 ║\n" ;
	cout << "╚═════════════════════════════════════════════════╝" ;

	setColor ( WHITE ) ;
	for ( i = 0 ; i < 24 ; i++ )
	{
		gotoXY ( i + 1 , 2 ) ;
		for ( j = 0 ; j < 24 ; j++ )
			cout << "🞖" << " " ;
	}
	
	gotoXY ( 27 , 2 ) ;
	cout << "🩵 " << name ;
	gotoXY ( 27 , 24 ) ;
	cout << "🕗 0" ;
	gotoXY ( 27 , 42 ) ;
	cout << "🚩 100" ;
	
	i = 0 ;
	j = 0 ;
	gotoXY ( i + 1 , 2 * j + 2 ) ;
	setColor ( ORANGE ) ;
	cout << "🞖" ;
	
	while ( 1 ) // Get the position of the first strike and we store it in i & j
	{
		order = getch ( ) ; 
		if ( !cursor ( i , j , order , true ) )
			break ;
	}
	
	fillTable ( i , j ) ; // Now fill the table based on the first strike
	strike ( i , j ) ; // Apply the strike
	gotoXY ( i + 1 , 2 * j + 2 ) ;
	setColor ( ORANGE ) ;
	unicode ( i , j ) ; // Turn on the cursor after the strike
	startTime = clock (  ) ; // Store the start time

	while ( 1 )
	{
		if ( flgR == 100 ) // If the number of correct flags reaches one hundred, which is the number of bombs, the game ends with a win
			return 1 ;
		gotoXY ( 27 , 45 ) ;
		setColor ( WHITE ) ;
		cout << flgNum << " " ; // The number of flags is constantly updated
		
		gotoXY ( 27 , 27 ) ;
		cout << ( clock (  ) - startTime ) / 1000 ; // The elapsed time is constantly updated
		finalTime = ( clock (  ) - startTime ) / 1000 ; // And at each moment, it is assigned to the final value
		
	 	if ( _kbhit ( ) ) // If a key is pressed, the character's value is immediately received, and the cursor moves there and switches to that value
	 	{
			order = getch ( ) ;
			con = cursor ( i , j , order ) ;
			switch ( con )
			{
				case 0 :
					if ( !strike ( i , j ) )
						return 0 ;
					break ;
				case 1 : // If its value is a flag, the related colors' values are printed and stored, and the remaining flags are decreased
					if ( front [ i ] [ j ] [ 0 ] != 'f' )
					{
						flgNum-- ;
						gotoXY ( i + 1 , 2 * j + 2 ) ;
						front [ i ] [ j ] [ 0 ] = 'f' ;
						color ( 'c' ) ;
						unicode ( i , j ) ;
						front [ i ] [ j ] [ 1 ] = 'c' ;
						back [ i ] [ j ] [ 1 ] = 0 ;
						if ( back [ i ] [ j ] [ 0 ] == 9 )
							flgR++ ; // If the flag is on a bomb, one is added to the count of correct flags
					}
					else // If there is already a flag at the desired location, the above actions are performed in reverse
					{
						flgNum++ ;
						gotoXY ( i + 1 , 2 * j + 2 ) ;
						front [ i ] [ j ] [ 0 ] = '?' ;
						color ( 'w' ) ;
						unicode ( i , j ) ;
						front [ i ] [ j ] [ 1 ] = 'w' ;
						back [ i ] [ j ] [ 1 ] = 1 ;
						if ( back [ i ] [ j ] [ 0 ] == 9 )
							flgR-- ;
					}
			}
		}
	}
}

int cursor ( int &i , int &j , char order , bool flgF ) // Moving the cursor and processing orders is possible with this function
{
	gotoXY ( i + 1 , 2 * j + 3 ) ;
	switch ( order )
	{
		case 'w' : case 'W' :
			if ( i - 1 >= 0 )
			{
				color ( front [ i ] [ j ] [ 1 ] ) ;
				cout << "\b" ;
				unicode ( i , j ) ;
					
				i-- ;
					
				gotoXY ( i + 1 , 2 * j + 2 ) ;
				setColor ( "33" ) ;
				unicode ( i , j ) ;
			}
			return 2 ;
			break ;
		case 's' : case 'S' :
			if ( i + 1 < 24 )
			{
				color ( front [ i ] [ j ] [ 1 ] ) ;
				cout << "\b" ;
				unicode ( i , j ) ;
					
				i++ ;
					
				gotoXY ( i + 1 , 2 * j + 2 ) ;
				setColor ( "33" ) ;
				unicode ( i , j ) ;
			}
			return 2 ;
			break ;
		case 'a' : case 'A' :
			if ( j - 1 >= 0 )
			{
				color ( front [ i ] [ j ] [ 1 ] ) ;
				cout << "\b" ;
				unicode ( i , j ) ;
					
				j-- ;
					
				gotoXY ( i + 1 , 2 * j + 2 ) ;
				setColor ( "33" ) ;
				unicode ( i , j ) ;
			}
			return 2 ;		
		case 'd' : case 'D' :
			if ( j + 1 < 24 )
			{
				color ( front [ i ] [ j ] [ 1 ] ) ;
				cout << "\b" ;
				unicode ( i , j ) ;
					
				j++ ;
					
				gotoXY ( i + 1 , 2 * j + 2 ) ;
				setColor ( "33" ) ;
				unicode ( i , j ) ;
			}
			return 2 ;
			break ;
		case 'f' : case 'F' :
			if ( flgF )
				return 2 ;	
			else
				return 1 ;
			break ;
		case 'e' : case 'E' :
			return 0 ;
			break ;
		default :
			return 2 ;
	}
}

void fillTable ( int x , int y ) // This function places the bombs and assigns values to the surrounding cells
{
	srand ( static_cast < unsigned int > ( time ( NULL ) ) ) ; // Initializing the rand function with the help of the system time
	int i , j , k ;
	
	for ( k = 0 ; k < 100 ; k++ ) // K represents the number of bombs ready to be distributed
	{
		i = rand ( ) % 24 ; // Random selection of one of the twenty-four possible lengths
		j = rand ( ) % 24 ; // Random selection of one of the twenty-four possible widths
		if ( back [ i ] [ j ] [ 0 ] == 9 || ( i < x+2 && i > x-2 && j < y+2 && j > y-2 ) )
			k-- ; // If there is a bomb at the desired location or if the desired location is the first selected cell or one of the eight surrounding cells, this bomb is redistributed
		else // If the above conditions are not met, the bomb is placed in a random cell, and the surrounding cells are ++ by one
		{
			back [ i ] [ j ] [ 0 ] = 9 ;
			if ( back [ i-1 ] [ j ] [ 0 ] != 9 )
				back [ i-1 ] [ j ] [ 0 ]++ ;
			if ( back [ i ] [ j-1 ] [ 0 ] != 9 )
				back [ i ] [ j-1 ] [ 0 ]++ ;
			if ( back [ i+1 ] [ j ] [ 0 ] != 9 )
				back [ i+1 ] [ j ] [ 0 ]++ ;
			if ( back [ i ] [ j+1 ] [ 0 ] != 9 )
				back [ i ] [ j+1 ] [ 0 ]++ ;
			if ( back [ i-1 ] [ j-1 ] [ 0 ] != 9 )	
				back [ i-1 ] [ j-1 ] [ 0 ]++ ;
			if ( back [ i+1 ] [ j+1 ] [ 0 ] != 9 )
				back [ i+1 ] [ j+1 ] [ 0 ]++ ;
			if ( back [ i+1 ] [ j-1 ] [ 0 ] != 9 )
				back [ i+1 ] [ j-1 ] [ 0 ]++ ;
			if ( back [ i-1 ] [ j+1 ] [ 0 ] != 9 )
				back [ i-1 ] [ j+1 ] [ 0 ]++ ;
		}
	}
}

bool strike ( int x , int y ) // This function takes the position of a strike and returns the game's continuation or end status as a Boolean
{
	if ( x < 0 || x == 24 || y < 0 || y == 24 ) // If it is out of bounds, it returns a value of one , it is used in recursive mode
		return 1 ;
	if ( back [ x ] [ y ] [ 1 ] == 0 ) // If the desired location has already been used, it returns a value of one ,it is used in recursive mode
		return 1 ;
	switch ( back [ x ] [ y ] [ 0 ] )
	{
		case 10 : // If it was a flag, return one
			return 1 ;
			break ;
		case 9 : // If it was a bomb, all bombs explode with a beautiful motion, and the value one is returned to signify the end of the game
			gotoXY ( x + 1 , 2 * y + 2 ) ;
			setColor ( "31" ) ;
			cout << "⛯\a" ;
			
			sleepMilis ( 400 ) ;
			for ( int i = 24 ; i > 0 ; i-- )
			{
				gotoXY ( i , 0 ) ;
				cout << "║" ;
			}
			
			sleepMilis ( 400 ) ;
			gotoXY ( 0 , 0 ) ;
			cout << "╔═════════════════════════════════════════════════╗" ;
			
			sleepMilis ( 400 ) ;
			for ( int i = 1 ; i < 25 ; i++ )
			{
				gotoXY ( i , 50 ) ;
				cout << "║" ;
			}
			
			sleepMilis ( 400 ) ;
			gotoXY ( 25 , 0 ) ;
			cout << "╚═════════════════════════════════════════════════╝" ;
			
			for ( int i = 0 ; i < 24 ; i++ )
				for ( int j = 0 ; j < 24 ; j++ )
					if ( back [ i ] [ j ] [ 0 ] == 9 )
					{
						sleepMilis ( 100 ) ;
						gotoXY ( i + 1 , 2 * j + 2 ) ;
						cout << "⛯" ;
					}
			
			return 0 ;
			break ;
		case 0 : // If the cell value is zero, the surrounding cells are called recursively.
			front [ x ] [ y ] [ 0 ] = '0' ;
			front [ x ] [ y ] [ 1 ] = 'y' ;
			gotoXY ( x + 1 , 2 * y + 2 ) ;
			color ( 'y' ) ;
			unicode ( x , y ) ; // display
			back [ x ] [ y ] [ 1 ] = 0 ; // The cell is marked as used
			
			// If it has not been used, it is called
			if ( back [ x - 1 ] [ y ] [ 1 ] )
				strike ( x - 1 , y ) ;
			if ( back [ x ] [ y + 1 ] [ 1 ] )
				strike ( x , y + 1 ) ;
			if ( back [ x + 1 ] [ y ] [ 1 ] )
				strike ( x + 1 , y ) ;
			if ( back [ x ] [ y - 1 ] [ 1 ] )
				strike ( x , y - 1 ) ;
				
			return 1 ;
			break ;		
		default : // If there are numbers in the cells, they are revealed, and the cell is marked as used and 1 returns
			gotoXY ( x + 1 , 2 * y + 2 ) ;
			front [ x ] [ y ] [ 0 ] = back [ x ] [ y ] [ 0 ] + 48 ;
			switch ( front [ x ] [ y ] [ 0 ] )
			{
				case '1' :
					color ( 'l' ) ;
					unicode ( x , y ) ;
					front [ x ] [ y ] [ 1 ] = 'l' ;
					back [ x ] [ y ] [ 1 ] = 0 ;
					break ;
				case '2' :
					color ( 'b' ) ;
					unicode ( x , y ) ;
					front [ x ] [ y ] [ 1 ] = 'b' ;
					back [ x ] [ y ] [ 1 ] = 0 ;
					break ;
				case '3' :
					color ( 'm' ) ;
					unicode ( x , y ) ;
					front [ x ] [ y ] [ 1 ] = 'm' ;
					back [ x ] [ y ] [ 1 ] = 0 ;
					break ;
				case '4' :
					color ( 'p' ) ;
					unicode ( x , y ) ;
					front [ x ] [ y ] [ 1 ] = 'p' ;
					back [ x ] [ y ] [ 1 ] = 0 ;
					break ;
				case '5' :
					color ( 's' ) ;
					unicode ( x , y ) ;
					front [ x ] [ y ] [ 1 ] = 's' ;
					back [ x ] [ y ] [ 1 ] = 0 ;
					break ;
				case '6' :
					color ( 'v' ) ;
					unicode ( x , y ) ;
					front [ x ] [ y ] [ 1 ] = 'v' ;
					back [ x ] [ y ] [ 1 ] = 0 ;
					break ;
				case '7' :
					color ( 'y' ) ;
					unicode ( x , y ) ;
					front [ x ] [ y ] [ 1 ] = 'y' ;
					back [ x ] [ y ] [ 1 ] = 0 ;
					break ;
				case '8' :
					color ( 'a' ) ;
					unicode ( x , y ) ;
					front [ x ] [ y ] [ 1 ] = 'a' ;
					back [ x ] [ y ] [ 1 ] = 0 ;
			}
			return 1 ;
	}
}

void gotoXY ( int x , int y ) // This function moves the cursor to the location specified in the input arguments
{
	HANDLE consoleHandle = GetStdHandle ( STD_OUTPUT_HANDLE ) ;
	COORD cursorCoord ;
	cursorCoord . X = y ;
	cursorCoord . Y = x ;
	SetConsoleCursorPosition ( consoleHandle , cursorCoord ) ;
}

void sleepMilis ( unsigned int mseconds ) // This function delays the program's execution by the specified milliseconds
{
	clock_t goal = mseconds + clock ( ) ;
	while ( goal > clock ( ) ) ;
}

void hideCursor (  )
{
    cout << "\033[?25l" ;
}

void showCursor (  )
{
    cout << "\033[?25h" ;
}

void setColor ( const string& colorCode )
{
    cout << "\033[" << colorCode << "m" ;
}

void unicode ( int i , int j ) // This function prints the Unicode state of each element of the array onto the screen
{
	switch ( front [ i ] [ j ] [ 0 ] )
	{
		case '?' :
			cout << "🞖" ;
			break ;
		case '0' :
			cout << "⓪" ;
			break ;
		case '1' :
			cout << "①" ;
			break ;
		case '2' :
			cout << "②" ;
			break ;
		case '3' :
			cout << "③" ;
			break ;
		case '4' :
			cout << "④" ;
			break ;
		case '5' :
			cout << "⑤" ;
			break ;
		case '6' :
			cout << "⑥" ;
			break ;
		case '7' :
			cout << "⑦" ;
			break ;
		case '8' :
			cout << "⑧" ;
			break ;
		case 'f':
			cout << "❆" ;
	}
}

void color ( char c ) // This function uses the setColor function based on the first character of each color
{
	switch ( c )
	{
		case 'r' :
			setColor ( "31" ) ;
			break ;
		case 'g' :
			setColor ( "32" ) ;
			break ;
		case 'o' :
			setColor ( "33" ) ;
			break ;
		case 'b' :
			setColor ( "34" ) ;
			break ;
		case 'm' :
			setColor ( "35" ) ;
			break ;
		case 'c' :
			setColor ( "36" ) ;
			break ;
		case 'w' :
			setColor ( "97" ) ;
			break ;
		case 'p' :
			setColor ( "91" ) ;
			break ;
		case 'l' :
			setColor ( "92" ) ;
			break ;
		case 'y' :
			setColor ( "93" ) ;
			break ;
		case 'a' :
			setColor ( "94" ) ;
			break ;
		case 'v' :
			setColor ( "95" ) ;
			break ;
		case 't' :
			setColor ( "96" ) ;
			break ;
		case 's' :
			setColor ( "90" ) ;
	}
}

void swapPlayerInfo ( int i , int j )
{
	playerInfo temp ;
	
	temp . name = players [ i ] . name ;
	temp . flags = players [ i ] . flags ;
	temp . time = players [ i ] . time ;
	
	players [ i ] . name = players [ j ] . name ;
	players [ i ] . flags = players [ j ] . flags ;
	players [ i ] . time = players [ j ] . time ;
	
	players [ j ] . name = temp . name ;
	players [ j ] . flags = temp . flags ;
	players [ j ] . time = temp . time ;
}
