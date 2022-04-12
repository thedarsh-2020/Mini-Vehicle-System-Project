/**************************************************************************************************
 Name        : Mini_Project1
 Author      : Mostafa M A. Mottilib
 Description : Vehicle Control System Project
 **************************************************************************************************/
#include <stdio.h>
#include <string.h>


// Choosing between engine temp. controller OR not
#define ENGINE_TEMP_CONTROLLER 0


// Variables Declaration
char input;
char engine_state[4] = {'O', 'F', 'F', '\0'};
char ac_state[4] = {'O', 'F', 'F', '\0'};
char off[] = "OFF";
char on[] = "ON";
unsigned short int v_speed;
short int r_temp;

#if(ENGINE_TEMP_CONTROLLER)
char en_temp_cont[4] = {'O', 'F', 'F', '\0'};
unsigned short int en_temp;
#endif


// Functions Declaration
void START_DISPLAY(void);
void VEHICLE_ENGINE_ON(void);
void TRAFFIC_LIGHT_SETTING(void);
void VEHICLE_STATUS(void);
void ROOM_TEMPERATURE_INPUT(void);
void ROOM_TEMPERATURE_SETTING(void);

#if(ENGINE_TEMP_CONTROLLER)
void ENGINE_TEMPERATURE_INPUT(void);
void ENGINE_TEMPERATURE_SETTING(void);
#endif


int main(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	START_DISPLAY();
	return 0;
}


// Function to show all vehicle status
void VEHICLE_STATUS(void)
{
	printf("\nEngine is %s\n", engine_state);
	printf("AC is %s\n", ac_state);
	printf("Vehicle Speed: %hu Km/Hr\n", v_speed);
	printf("Room Temperature: %hd Degree/C\n", r_temp);

#if(ENGINE_TEMP_CONTROLLER)
	printf("Engine Temp. Controller is %s\n", en_temp_cont);
	printf("Engine Temperature: %hu Degree/C\n\n", en_temp);
#endif
}


void START_DISPLAY(void)
{
	while(1)
	{
		// Starting Menu
		printf("a. Turn ON the Vehicle Engine");
		printf("\nb. Turn OFF the Vehicle Engine\n");
		printf("c. Quit the System\n\n");

		// while loop to ensure the input and avoid any wrong inputs
		while(1)
		{
			scanf(" %c", &input);

			// Check input belongs to choices or not, and take care of upper OR lower letters
			if(input == 'a' || input == 'A' || input == 'b' || input == 'B' || input == 'c' || input == 'C')
				break;
			else
				printf("Wrong input\n");
		}

		// switch case to take an action according to input
		switch(input)
		{
		case 'A':
		case 'a':
			printf("Turn ON the Vehicle Engine\n");

			// Check engine state & turn it ON if it was OFF
			if(!(strcmp(engine_state, off)))
			{
				engine_state[0] = 'O';
				engine_state[1] = 'N';
				engine_state[2] = '\0';
			}

			// Going to Engine menu
			VEHICLE_ENGINE_ON();
			break;

		case 'B':
		case 'b':
			printf("Turn OFF the Vehicle Engine\n\n");

			// Check engine if ON, turn it OFF & back to starting menu
			if(!(strcmp(engine_state, on)))
			{
				engine_state[0] = 'O';
				engine_state[1] = 'F';
				engine_state[2] = 'F';
				engine_state[3] = '\0';
			}
			break;

		case 'C':
		case 'c':
			printf("Quit the System");

			// return to main func. & exit system
			return;
		}
	}
}


// Function to turn ON engine & controlling engine & room temp.
void VEHICLE_ENGINE_ON(void)
{

	while(1)
	{
		// Engine controller menu
		printf("\na. Turn OFF the Engine\n");
		printf("b. Set the Traffic Light Colour\n");
		printf("c. Set the Room Temperature (Temperature Sensor)\n");
#if(ENGINE_TEMP_CONTROLLER)
		printf("d. Set the engine temperature (Engine Temperature Sensor)\n");
#endif

#if(ENGINE_TEMP_CONTROLLER)
		// while loop to ensure the input and avoid any wrong inputs
		while(1)
		{
			scanf(" %c", &input);

			// Check input belongs to choices or not, and take care of upper OR lower letters
			if(input == 'a' || input == 'A' || input == 'b' || input == 'B' || input == 'c' || input == 'C' || input == 'd' || input == 'D')
				break;
			else
				printf("Wrong input\n");
		}
#else
		// while loop to ensure the input and avoid any wrong inputs
		while(1)
		{
			scanf(" %c", &input);

			// Check input belongs to choices or not, and take care of upper OR lower letters
			if(input == 'a' || input == 'A' || input == 'b' || input == 'B' || input == 'c' || input == 'C')
				break;
			else
				printf("Wrong input\n");
		}
#endif

		// switch case to take an action according to input
		switch(input)
		{
		case 'A':
		case 'a':
			printf("Turn OFF the Engine\n\n");

			// Turning OFF engine & return to starting menu
			engine_state[0] = 'O';
			engine_state[1] = 'F';
			engine_state[2] = 'F';
			engine_state[3] = '\0';
			return;

		case 'B':
		case 'b':
			printf("Set the Traffic Light Colour\n");

			// Going to traffic light function
			TRAFFIC_LIGHT_SETTING();
			break;

		case 'C':
		case 'c':
			printf("Set the Room Temperature (Temperature Sensor)\n");

			// Going to function to read temperature data
			ROOM_TEMPERATURE_INPUT();

			// Going to function that control room temp. based on the input data
			ROOM_TEMPERATURE_SETTING();
			break;

#if(ENGINE_TEMP_CONTROLLER)
		case 'D':
		case 'd':
			printf("Set the Engine Temperature (Engine Temperature Sensor)\n");

			// Going to function to read engine temperature data
			ENGINE_TEMPERATURE_INPUT();

			// Going to function that control engine temp. based on the input data
			ENGINE_TEMPERATURE_SETTING();
			break;
#endif
		}

		// Going to function to show all vehicle status
		VEHICLE_STATUS();
	}
}


// Function to take room temp. data from user
void ROOM_TEMPERATURE_INPUT(void)
{
	printf("Enter Required Room Temperature:\n");
	scanf(" %hd", &r_temp);
}


// Function to set room temp. based on the input data
void ROOM_TEMPERATURE_SETTING(void)
{
	if((r_temp < 10) || (r_temp > 30))
	{
		ac_state[0] = 'O';
		ac_state[1] = 'N';
		ac_state[2] = '\0';
		r_temp = 20;
	}
	else
	{
		ac_state[0] = 'O';
		ac_state[1] = 'F';
		ac_state[2] = 'F';
		ac_state[3] = '\0';
	}
}


// Function that control vehicle speed
void TRAFFIC_LIGHT_SETTING(void)
{
	printf("Enter the Required Colour:\n");

	// while loop to ensure the input and avoid any wrong inputs
	while(1)
	{
		scanf(" %c", &input);

		// Check input belongs to choices or not, and take care of upper OR lower letters
		if(input == 'g' || input == 'G' || input == 'o' || input == 'O' || input == 'r' || input == 'R')
			break;
		else
			printf("Wrong input\n");
	}

	// switch case to take an action according to input
	switch(input)
	{
	case 'G':
	case 'g':
		v_speed = 100;

		// After setting vehicle speed, going to room function to check temp
		ROOM_TEMPERATURE_SETTING();

#if(ENGINE_TEMP_CONTROLLER)
		// After setting vehicle speed, going to engine temp. function to check temp.
		ENGINE_TEMPERATURE_SETTING();
#endif
		break;

	case 'O':
	case 'o':
		v_speed = 30;

		// After checking vehicle speed, check engine temp. controller to turn it ON
		if(!(strcmp(ac_state, off)))
		{
			ac_state[0] = 'O';
			ac_state[1] = 'N';
			ac_state[2] = '\0';
		}
		r_temp = r_temp * (5/4) +1;

#if(ENGINE_TEMP_CONTROLLER)
		// checking engine temp. controller to turn it ON
		if(!(strcmp(en_temp_cont, off)))
		{
			en_temp_cont[0] = 'O';
			en_temp_cont[1] = 'N';
			en_temp_cont[2] = '\0';
		}
		en_temp = en_temp * (5/4) + 1;
#endif
		break;

	case 'R':
	case 'r':
		v_speed = 0;

		// After setting vehicle speed, going to room function to check temp.
		ROOM_TEMPERATURE_SETTING();

#if(ENGINE_TEMP_CONTROLLER)
		// After setting vehicle speed, going to engine temp. function to check temp.
		ENGINE_TEMPERATURE_SETTING();
#endif
		break;
	}
}


#if(ENGINE_TEMP_CONTROLLER)
// Function to take engine temp. data from user
void ENGINE_TEMPERATURE_INPUT(void)
{
	printf("Enter Required Engine Temperature:\n");
	scanf(" %hd", &en_temp);
}


// Function to set engine temp. controller based on the input data
void ENGINE_TEMPERATURE_SETTING(void)
{
	if((en_temp < 100) || (en_temp > 150))
	{
		en_temp_cont[0] = 'O';
		en_temp_cont[1] = 'N';
		en_temp_cont[2] = '\0';
		en_temp = 125;
	}
	else
	{
		en_temp_cont[0] = 'O';
		en_temp_cont[1] = 'F';
		en_temp_cont[2] = 'F';
		en_temp_cont[3] = '\0';
	}
}
#endif
