//Kobe Johnson

#include "keypad_sensor.h"


//Writes the key to a queue for IPC
void get_key_input(queue_t *keyQ)
{
	
	bool buttonPressed = false;
	//Grid that matches the kaypad
		int16_t grid[4][3] = 
	{
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9},
		{-1, 0, -1}
	};
	
	
	//Loops through each column/row and returns it and the corresponding integer to it
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j <3; j++) {
			//Check for input
			//Set buttonPressed to true 
			write_q(keyQ, grid[i][j]);
		}
	}
	//If no keys are pressed just return
	return;
}
//Gets input for the get_key_input function (Helper function)
bool input_detected(void)
{
	bool input_found = false;
	
	//Goes through input pins and checks for with row/column
	return input_found;
}