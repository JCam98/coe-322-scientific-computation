// Property of: Justin Campbell; UT EID: jsc4348                                                                                                                                                                                           
                                                                                                                                                                                                                      
// Purpose of Use: COE 322 - 13370                                                                                                                                                                                                         
                                                                                                                                                                                                                                           
// Description: This program constitutes the fourth exercise in the Infectious Disease Simulation Project. This program will run a simulation on a population of individuals, in under similar conditions to those posed in exercise 3. In addition to adjacent neighbors in a population being able to infect one another, the simulation will run with a non-zero number of individuals that are vaccinated at the beginning of the simulation. The effect that introducing vaccinated persons into the population will have on the propagation of the disease throughout the entire population will be the main objective of the study.                                   

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

                    
/////////////////////////////////////////////////////////////////////////////////////////////////        

int main(){

  srand(time(0));

  /////////////////////////////////////////////////////////////////////////////////////////                                                                                                                                                 
  int pop_num;
  vector<Person> population;
  int status_main = 0;
  int count = 1;

  // Prompt the user to input an integer number for the size of population for modeling:                                                                                                                                                   

  cout << "Please enter an integer corresponding to the number of individuals in the population you would like to monitor for the contagion simulation. ";

  cin >> pop_num;

  cout << endl;

  // Prompt the user to input a float number in the range (0,1) representing the percentage of the population that is vaccinated at the beginning of the simulation: 

  float vac_per;

  cout << "Please enter a decimal number in the range (0,1) for the percentage of the population that is to be chosen randomly for vaccination at the beginning of the simulation: ";

  cin >> vac_per;

  cout << endl;

  // Prompt the user to input a float number in the range (0,1) for the fixed probability of disease transmission upon contact:                                                                                                             
  float trans_prob;

  cout << "Please input a decimal number in the range (0,1) to represent the  probability (p) of disease transmission upon contact for the entire simulation  ";

  cin >> trans_prob;

  cout << endl;

  // Initialize "Person" object for each individual in population:                                                                                                                                                                          
  for (int i = 0; i< pop_num; i++){

    Person input_per(status_main,i);

    // Invoke "push_back()" method to append each "Person" object to "population" vector:                                                                                                                                                   
    population.push_back(input_per);

  }

  // Initialize "Population" object:                                                                                                                                                                                                        
  Population pop_obj(population);
  bool pop_simulation_condition = 1;
  int day = 1;
  string day_string;
  int day_string_len;
  int index_first_infected_per;
  int infected_number;
  int vaccinated_number;
  int recovered_number;
  int healthy_not_vac_number = population.size();
  int infect_pool;
  int vac_pool;
  int infected_today_rand;
  int vaccinated_today_rand;

  // Invoke "set_vaccination_per()" to pass in a fixed value for the percentage of the population that is vaccinated at the beginning of the simulation: 

  pop_obj.set_vaccination_per(vac_per);

  // Invoke "random_vaccination()" method to randomly vaccinate a percentage of the population according to the value passed in by "set_vaccination_per()":

  pop_obj.random_vaccination();

  // Invoke "set_probability_of_transfer()" method to pass in a fixed value for the neighboring infection probability:                                                                                                                      
  pop_obj.set_probability_of_transfer(trans_prob);

  // Invoke "random_infection()" method to randomly infected a single member of the population for the start of the simulation:                                                                                                          \ 
                                                                                                                                                                                                                                         
  pop_obj.random_infection();

  // Use while loop to randomly update the health status of each individual in the population until everyone has recovered from an infection while keeping track of the day count:                                                          
  while(pop_simulation_condition == 1){

    // Invoke the "update_pop()" method to update the health condition of each individual at the beginning of the day:                                                                                                                     

    pop_obj.update_pop();

    // Invoke "population_return()" method to return the updated population vector for the beginning of the day:                                                                                                                            
    population = pop_obj.population_return();

    if (day == 1){

      // Return the index of the first infected member of the population:                                                                                                                                                                  
                                                                                                                                                                                                                                          
      for (int i = 0; i< population.size(); i++){

        if ((population.at(i)).get_status() > 0){

          index_first_infected_per = i;

        }

      }

    }

    // Invoke "count_infected()", "count_vaccinated()", "count_recovered()", and "count_healthy_not_vac()" methods to return the number of individuals in the population in each of the four health categories for the day:                
                                                                                                                                                                                                                                        
                                                                                                                                                                                                                                          
    infected_number = pop_obj.count_infected();

    vaccinated_number = pop_obj.count_vaccinated();

    recovered_number = pop_obj.count_recovered();                                                                                                                                                                                          

    healthy_not_vac_number = pop_obj.count_healthy_not_vac();

    // Loop through the entire population and output each of the individuals' status for the beginning of the day:                                                                                                                                                                                                                                                                                                                                                                    
    if (day == 1){


      pop_obj.status_rep_format();

    }

    if (population.size()<=28){

      day_string = to_string(day);
      day_string_len = day_string.length();

      if (day_string_len == 1){

        cout << day << "          |";

      }

      else if(day_string_len == 2){

        cout << day << "         |";

      }


      for (int n = 0; n< population.size(); n++){

        cout << pop_obj.status_return(n) << "|";

      }

      cout << endl;

    }

    else{

      cout << day << "                   ";
      cout << healthy_not_vac_number << "                          " << vaccinated_number << "                            " << infected_number << "                             " << recovered_number<< endl;

    }

    // If there are still members of the population that are healthy, Invoke method "neighboring_infection()" to employ algorithm that uses fixed probability of neighboring infection value (read in by user) to spread infection from tho
    // se who are currently infected to their neighbors:                                                                                                                                                                                           
      if (healthy_not_vac_number !=0){

	pop_obj.neighboring_infection(index_first_infected_per);

      }

      // Research methods to output results of simulation (number of individuals in each category on day-by day basis for the large simulation case, and health status for each individual on day-by-day basis for small simulation case) i      // n source file to ".txt" file for data manipulation in Excel for exercises 3-5:                                                                                                                                                                
	// Exit the while loop when all individuals in population have recovered from infection:                                                                                                                                                
	if(infected_number == 0){

	  pop_simulation_condition = 0;

	}

      day++;


  }

  return 0;

}


