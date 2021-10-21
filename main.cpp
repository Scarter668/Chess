
#include "Board.h"

#include <iostream>
#include <thread>




using std::cout;
using std::cin;







//------------------------------------------------------------------------------'

// C++ programs start by executing the function main
int main()
{
	//cout << "Hello, World!\n";



	// Create an instance of the  window.
	ChessBoard win{};
	
	srand( time(nullptr));



	return Graph_lib::gui_main();
}

//------------------------------------------------------------------------------
