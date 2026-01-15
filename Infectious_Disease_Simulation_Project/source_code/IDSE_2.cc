

// Property of: Justin Campbell; UT EID: jsc4348                                                                                                                                                                                            

// Purpose of Use: COE 322 - 13370                                                                                                                                                                                                          

// Description: This program constitutes the second exercise in the Infectious Disease Project. In this program, the health condition of an entire population of individuals will be simulated using pseudo-random number generator functions similar to those used in exercise 1. A status table will be output to the terminal reflecting the health status of each individual in the population on a day-by-day basis, and the simulation will run  until each individual  has recovered from an infection imposed during the simulation.                                                                                                                                                              

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

  int pop_num;
  vector<Person> population;
  int status_main = 0;
  int count = 1;

  // Prompt the user to input an integer number for the size of population for modeling:                                                                                                                                                   

  cout << "Please enter an integer corresponding to the number of individuals in the population you would like to monitor for the simulation. ";

  cin >> pop_num;

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
  int infected_number;
  int recovered_number;
  int healthy_not_vac_number = population.size();
  int vaccinated_number = 0;
  int infect_pool;
  int infected_today_rand;
  

  // Use while loop to randomly update the health status of each individual in the population until everyone has recovered from an infection while keeping track of the day count:                                                                                                                                                                                                                                                                                                    
  while(pop_simulation_condition == 1){

    // Invoke the "update_pop()" method to update the health condition of each individual at the beginning of the day:                                                                                                                     

    pop_obj.update_pop();

    // Invoke "population_return()" method to return the updated population vector for the beginning of the day:                                                                                                                           
                                                                                                                                                                                                                                           
    population = pop_obj.population_return();

    // Invoke "count_infected()", "count_recovered()", and "count_healthy_not_vac()" methods to return the number of individuals in the population in each of the three health categories for the day:                

    infected_number = pop_obj.count_infected();

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
      cout << healthy_not_vac_number << "                          " << vaccinated_number <<   "                            " << infected_number << "                             " << recovered_number<< endl;

    }

    // If there are still members of the population that are healthy, Invoke "random_infection()" method to randomly infected a single healthy member of the population:
                                                                                                                                                                                                                                           
    if (healthy_not_vac_number !=0){

      pop_obj.random_infection();

    }                                                                                                                                                                                                                                           
    // Invoke the "count_infected()" method again to return an updated number of infected members of the population: 

    infected_number = pop_obj.count_infected();

    // Exit the while loop when all individuals in population have recovered from infection:                                                                                                                                           \
                                                                                                                                                                                                                                           
    if(infected_number == 0){

      pop_simulation_condition = 0;

    }

    day++;


  }

  return 0;

}

