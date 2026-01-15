// Property of: Justin Campbell; UT EID: jsc4348
                                                                                                                                                                                           
// Purpose of Use: COE 322 - 13370                                                                                                                                                                                                          

// Description: This program constitues exercise 1 in the Infectious Disease Simulation Project. In this program, a simulation is run to model the health condition of a single individual under four states: 
// on a day-by-day basis. Pseudo-random number generator functions are used to update these conditions, and the status of the individual is output to the terminal for each day. It is assumed that the individual for whom the simulation is being run is healthy and not vaccinated at the beginning of the study, and the simulation will end when the individual has either become recovered from an infection, or become vaccinated. 

// 1) Healthy but not vaccinated
// 2) Vaccinated
// 3) Infected
// 4) Recovered
                                                                                                                                                                                                                       
//////////////////////////////////////////////////////////////////////////////////////////////                                                                                                                                             
#include "Infectious_Disease_Simulation_Library.h"
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <ctime>
#include <random>
#include <cstdlib>
#include <vector>
using std :: cout;
using std :: cin;
using std :: endl;
using std :: string;
using std :: to_string;
using std :: rand;
using std :: vector;


///////////////////////////////////////////////////////////////////////////////////////////                                                                                                                                                 

int main(){

  // The following code is used to subject an individual, healthy, person to collection of pseudo-randomly-generated disease parameters, and to track their state as they recover.                                                          
  srand(time(0));

  int n = 6;
  string single_person_model_condition = "Y";

  while(single_person_model_condition == "Y"){

    cout << "Please input the name of an individual whose health condition is to be monitored" << endl;

    string input_name;

    cin >> input_name;

    // Important: The assumption is that the individual, (before health condition is to be monitored) is healthy, and not vaccinated. Their health status is initialized to a value of 0.                                                     

    int status_main = 0;

    // Initialize object for individual "input_name":                                                                                                                                                                                      

    Person input(status_main,input_name);

    // Use "while" loop to monitor the health condition of an individual "input" until recovered:                                                                                                                                             
    // Each loop constitutes a collection of events that occurs in a single day                                                                                                                                                               
    int day = 1;
    bool simulation_condition = 0;

    while (simulation_condition == 0){

      // Return status to main at beginning of each day:                                                                                                                                                                                      
      status_main = input.get_status();

      // At the beginning of each day, the health status of (sick) individual needs to be updated:                                                                                                                                         

      if (status_main > 0){

	input.update(status_main);

      }

      // Output health condition status to the terminal at the beginning of the day:                                                                                                                                                                                  
                                                                                                                                                                                                                                           
      cout << "On day " << day << " " << input_name << " is " << input.status_string() << endl;

      bool stable_condition = input.is_stable();

      if (stable_condition == 1 ){

        simulation_condition = 1;

      }


      // Invoke Pseudorandom-number Generated Infection Algorithm to Infect Individual if healthy and not vaccinated:                                                                                                                         
      if (status_main == 0){

	bool infect_condition;

	infect_condition = input.infect_gen_rand();

	// If "infect_gen_rand()" returns a value of 1, invoke a second random-number generator function to infect individual for "n" number of days                                                                                       
                                                                                                                                                                                                                                           
	if (infect_condition == 1){

	  // Infect healthy and not vaccinated person for 5 days: 

	  input.infect(n);

	  status_main = input.get_status();

	}

      }

      // Increase the day count by one:                                                                                                                                                                                                       
      day++;

    }

    // Prompt user to run another simulation to model single person infection tracking or exit:                                                                                                                                               

    cout << " Would you like to run another infectious-disease simulation of a single individual?" << endl;
    cout << " Enter 'Y' for yes. Enter any other key for no. " << endl;

    cin >> single_person_model_condition;

  }

}

