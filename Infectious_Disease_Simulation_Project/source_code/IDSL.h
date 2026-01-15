// Property of: Justin Campbell; UT EID: jsc4348

// Purpose of Use: COE 322: 13370 

// Description: This header file contains the library of class definitions ("Person", and "Population") that are used for the five exercises in the Infectious Disease Simulation Project. 

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

// Definition of the "Person" class:                                                                                                                                                                                                       

class Person {

 private:

  // Private Data Members:
                                                                                                                                                                                                              
  int status;
  int int_name;
  string string_name;

 public:

  // Define Constructor "Person" to pass in "status" from main and to be used for the modeling  of single individual                                                                                                                       

  Person(int in_status,string in_string_name):

    status(in_status), string_name(in_string_name){};

    // Define secondary constructor "Person" to pass in "status" from main and to be used for the modeling of entire population                                                         
  
  Person (int in_status, int in_int_name):

    status(in_status),int_name(in_int_name){};

  // Define "status_string()" method to return a description of individual's state as string:                                                                                                                                              

  string status_string(){

    string stat_str_msg;

    if (status == 0){

      stat_str_msg = "healthy but not vaccinated";

    }

    else if(status == -1){

      stat_str_msg = "recovered";

    }


    else if (status == -2){

      stat_str_msg = "vaccinated";

    }

    else if(status > 0) {

      string stat_str = to_string(status);

      stat_str_msg = "sick with " + stat_str + " days to go before recovery ";

    }

    return stat_str_msg;

  };


  // Define "get_status()" method to return integer status identifier:
                                                                                                                                                                     
  int get_status(){

    return status;

  };

  // Define "get_name()" method to return name of individual:                                                                                                                                                                              
                                                                                                                                                                                                                                           
  string get_name(){

    return string_name;

  };

  // Define "get_int_name()" method to return integer identifier for individual:                                                                                                                                                           
                                                                                                                                                                                                                                           
  int get_int_name(){

    return int_name;

  };

  // Define "update()" method to update individual's disease status to the following day:                                                                                                                                                  
                                                                                                                                                                                                         
   void update(int status_in){

    // If infected, and more than one day remaining until healthy, reduce the status identifier by one:                                                                                                                                    

    if (status_in > 1){

      status = status - 1;

    }

    // If infected, and one day remaining until healthy, reduce the status identifier by two:                                                                                                                                              
                                                                                                                                                                                                          
    else if (status_in == 1){

      status = status -2;

    }

    // If vaccinated, update the integer identifier for "status" to "-2":      

    else if (status_in == 1){

      status = status -2;

    }

    // If vaccinated, update the integer identifier for "status" to "-2":                                                                                                                                                                  
                                                                                                                                                                                                            
   else if (status_in == -2){

      status = status_in;

    }

};

  // Define "infect()" method to infect individual, for 'n' number of days:                                                                                                                                                                

  void infect(int n){

    status = n;

  };

  // Define "is_stable()" method to return a boolean indicator for the state "Individual has been  sick and is recovered, or Individual has been vaccinated (each stable conditions):                                                      

  bool is_stable(){

    bool stable_condition;

    if (status == -1 || status == -2){

      stable_condition = 1;

    }

    else {

      stable_condition = 0;

    }

    return stable_condition;

  };


  // Define "infect_gen_rand()" method to employ an arbitrary pseudo-random number generator for the purpose of infecting individual                                                                                                       
                                                                                                                                                                                                                                           
  bool infect_gen_rand(){

    bool infect_condition_per;
    int infect_pseudo_rand =  rand() % 101; // Generate random integer between 0 and 100                                                                                                                                                   
                                                                                                                                                                                                                                           
    int infect_threshold = rand() % 1001; // Set infection threshold to random number between 0 and 1000                                                                                                                                   

    // If random integer exceeds infection threshold (10 % probability on each function call) assign boolean value of 1 to infection condition, else assign a value of 0                                                                   
                                                                                                                                                                                                                                           

    if (infect_pseudo_rand >= infect_threshold){

      infect_condition_per = 1;

    }

    else {

      infect_condition_per = 0;

    }

    return infect_condition_per;

  };

};

// Definition of "Population" class to track disease propagation for a group of individuals ("Person" objects):                                                                                                                         

class Population{

  private:

    vector<Person>pop;
    int pop_size = pop.size();
    float trans_prob; // "trans_prob" is a fixed floating point number constituting the probability that a currently sick member of the population spreads their infection to a person in contact  
    float vac_per; // "vac_per" is a fixed floating point number constituting the percentage of the population that is vaccinated at the beginning of the simulation and read in from the user                                             


  public:

    // Define constructor "Population()" to pass a vector of "Person" objects into the "Population" class:                                                                                                                                 

  Population(vector<Person>pop_in):

    pop(pop_in){};

    // Define "update_pop()" method to loop through each of the individuals in the population and invoke the "update()" method from the "Person" class to update their status at the beginning of each day:            
   
  void update_pop(){

    int status_main;

    for (int i = 0; i < pop_size; i++){

      status_main = (pop.at(i)).get_status();

      (pop.at(i)).update(status_main);

    }

  };


  // Define "set_vaccination_per()" method to pass in a fixed value for the percentage of the population that is to be vaccinated at the beginning of the simulation:                                                                     


  void set_vaccination_per(float vac_per_in){

    vac_per = vac_per_in;

  };

  // Define "random_infection()" method to randomly infect a single individual ("Person" object) in the population:                                                                                                                      
                                                                                                                                                                                                                                           
  void random_infection(){

    int int_per_identifier = rand() % pop_size;

    Person rand_gen_per = pop.at(int_per_identifier);

    // Use pseudo-random number generator to randomly choose an individual of the population who has not been previously infected or vaccinated:                                                                                           

    while (rand_gen_per.get_status() != 0){

      int_per_identifier = rand() % pop_size;

      rand_gen_per = pop.at(int_per_identifier);

    }

    // Infect the individual for a fixed number of days(5):                                                                                                                                                                                
                                                                                                                                                                                                                                           
    int n = 6;

    (pop.at(int_per_identifier)).infect(n);

  };

  // Define "random_vaccination()" method to randomly vaccinate members of the population for the beginning of the study according to the fixed vaccination percentage value read in by "set_vaccination_per()":    

  void random_vaccination(){

    int i;
    int vac_num = (vac_per) * pop_size;
    int rand_per_gen;

    for (int i = 0; i< vac_num; i++){

      // Invoke random-number generator to randomly choose healthy member of the population to vaccinate:                                                                                                                                  

      rand_per_gen = rand() % pop_size;

      while ((pop.at(rand_per_gen)).get_status() != 0){

        rand_per_gen = rand() % pop_size;

      }

      (pop.at(rand_per_gen)).update(-2);

    }

  };


  // Define "count_infected()" method to keep track of the number of individuals in the population who are infected:                                                                                                                       
                                                                                                                                                                                                                                           
  int count_infected(){

    int infected_num = 0;

    // Use for loop to iterate through each of the "Person" objects in the population and increase the infected number count by one if their status is positive:                                                                         

    for (int jj = 0; jj< pop_size; jj++){

          if (((pop.at(jj)).get_status()) > 0){

            infected_num++;

          }

    }


    return infected_num;

  };

  // Define "count_vaccinated()" method to keep track of the number of individuals in the population who are vaccinated:                                                                                                               

  int count_vaccinated(){

    int vaccinated_num = 0;

    // Use for loop to iterate through each of the "Person" objects in the population and increase the vaccined number count by one if their status is -2:                                                  
                                                                                                                                                                                                                                     
    for (int i = 0; i< pop_size; i++){

      if (((pop.at(i)).get_status()) == -2){

	vaccinated_num++;

      }

    }

    return vaccinated_num;

  };

  // Define "count_recovered()" method to keep track of the number of individuals in the population who have recovered                                                                                                        
                                                                                                                                                                                                                                          
  int count_recovered(){

    int recovered_num = 0;

    // Use for loop to iterate through each of the "Person" objects in the population and increase the recovered count by one if their status is -1:                                                                                    

    for (int i = 0; i< pop_size; i++){

      if (((pop.at(i)).get_status()) == -1){

	recovered_num++;

      }

    }

    return recovered_num;

  };

  // Define "count_healthy_not_vac()" method to keep track of the number of individuals in the population who are healthy and not vaccinated:                                                                                           

  int count_healthy_not_vac(){

    int healthy_not_vac_num = 0;

    // Use for loop to iterate through each of the "Person" objects in the population and increase the healthy and not vaccinated count by one if their status is 0:                                                                   
                                                                                                                                                                                                                                          
    for (int i = 0; i< pop_size; i++){

      if (((pop.at(i)).get_status()) == 0){

	healthy_not_vac_num++;

      }

    }

    return healthy_not_vac_num;

  };

  // Define "status_rep_format()" to format the elements of the status report when output to the terminal                                                                                                                              
                                                                                                                                                                                                                                           
  void status_rep_format(){

    string int_name_string;
    int int_name_len;

    // If the number of members in the population is less than or equal to 28 (adjusting for the width of the terminal window), then output the status of each of the members for each day until the simulation concludes:             
                                                                                                                                                                                                                                           
    if (pop_size <= 28){

      cout << "Status Report for Population "  << endl;
      cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
      cout << "Day Number | Person Number" << endl;
      cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
      cout << "           |";

          for (int i = 0; i<pop_size; i++){

            int_name_string = to_string((pop.at(i)).get_int_name());

            int_name_len = int_name_string.length();

            if (int_name_len == 1){

              cout <<int_name_string << "      |";

            }

            else if(int_name_len == 2){

              cout << int_name_string << "     |";

            }

	  }

          cout << endl;

    }

    // If the number of members in the population exceeds 28, then, for readability purposes, output a table that reports the number of members in each of the four status categories until the simulation concludes:                   

    else {

      cout << "Status Report for Population "  << endl;
      cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" <<endl;
      cout << "Day Number|No. Healthy but not Vaccinated|" << " No. Vaccinated              | " << "No. Infected                 | " << "No. Recovered                 |" << endl;
      cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" <<endl;
    }

  };

  // Define method "population_return()" to return population vector to main program:                                                                                                                                                   

  vector<Person> population_return(){

    return pop;

  };

  // Define "status_return()" method to return a string identifier for the status of an individual in the population:                                                                                                                  
                                                                                                                                                                                                                                          
  string status_return(int per_num){

    string string_status;
    string string_status_ident;
    int string_status_len;

    if ((pop.at(per_num)).get_status() > 0){

      string_status = "Inf(" + to_string((pop.at(per_num)).get_status()) + ")";

      string_status_len = string_status.length();

      if (string_status_len == 6){

	string_status_ident = string_status + " ";

      }

      else if (string_status_len ==  7){

	string_status_ident = string_status;

      }

    }

    else if ((pop.at(per_num)).get_status() == 0) {

      string_status = "HNV";

      string_status_ident = string_status + "    ";

    }

    else if ((pop.at(per_num)).get_status() == -1){

      string_status = "REC";

      string_status_ident = string_status + "    ";

    }

    else if ((pop.at(per_num)).get_status() == -2){

      string_status = "HV";

      string_status_ident  = string_status + "     ";

    }

    return string_status_ident;

  };

  // Define "set_probability_of_transfer()" method to pass a fixed probability of infection value into the Population class:                                                                                                           \
                                                                                                                                                                          
  void set_probability_of_transfer(float trans_prob_in){

    trans_prob = trans_prob_in;

  };

  // Define "neighboring_infection()" method to spread infections from currently sick members of the population to their adjacent (neighboring) members using fixed probability of infection value. Note: It is assumed that any infected p  erson, regardless of which day they contracted the infection, can spread the disease to a neighbor as long as the probabi lity threshold is exceeded, and the number of days in which one person is sick is set to a fixed value of 5.  
                                                                                                                                                                                                                              
  void neighboring_infection(int index_first_infected_person){

    int neighbor_num = 2;
    int n = 6;
    int i;
    int rand_num_prob_compare_int;
    bool infect_neighbor_cond = 1;
    float rand_num_prob_compare_float;
    float rand_num_prob_compare_float_per;

    // If the first infected member of the population is the first index of the population vector, employ a single for loop moving from left to right to attempt to infect a single neighbor each day:                                 

    if (index_first_infected_person == 0){

      // Execute the while loop until either a neighbor has been infected (at most one neighbor can become infected each day for this particular case), or when all members of the population are either currently infected or have recover      ed                                                                                                                                                                                                                           
                                                                                                                                                                                                                                           
      i = 0;

      while (infect_neighbor_cond == 1 && i < (pop_size - 1)){

        if ((pop.at(i)).get_status() > 0) {

	  if ((pop.at(i+1)).get_status() == 0){

	    rand_num_prob_compare_int = rand() % 101;

	    rand_num_prob_compare_float = (float) rand_num_prob_compare_int;

	    rand_num_prob_compare_float_per = rand_num_prob_compare_float / 100;

	    // If the randomly generated number is less than or equal to the probability threshold, infect the neighbor for 5 days and terminate the function                                                                              

	    if (rand_num_prob_compare_float_per <= trans_prob){

	      (pop.at(i+1)).infect(n);

	    }

	    infect_neighbor_cond = 0;

	  }

	}

	  i++;

      }

    }

    // If the first infected member of the population is the last index of the population vector, employ a single for loop moving from right to left to attempt to infect a single neighbor each day:                                  
                                                                                                                                                                                                                                           
    else if (index_first_infected_person == pop_size - 1){

      // Execute the while loop until either a neighbor has been infected (at most one neighbor can become infected each day for this particular case), or when all members of the population are either currently infected or have recover      ed.                                                                                                                                                                                                                          
                                                                                                                                                                                                                                           
      infect_neighbor_cond = 1;

      i = pop_size - 1;

      while (infect_neighbor_cond == 1  && i >= 1){

         if ((pop.at(i)).get_status() > 0) {

	    if ((pop.at(i-1)).get_status() == 0){

	      rand_num_prob_compare_int = rand() % 101;

	      rand_num_prob_compare_float =(float) rand_num_prob_compare_int;

	      rand_num_prob_compare_float_per= rand_num_prob_compare_float /100;

	      // If the randomly generated number is less than or equal to the probability threshold, infect the neighbor for 5 days and exit the while loop:                                                                             
  
	      if (rand_num_prob_compare_float_per <= trans_prob){

		(pop.at(i-1)).infect(n);

	      }

	      infect_neighbor_cond = 0;

	    }

	 }

	 i = i - 1;

      }

    }

    // Execute the while loop until either a neighbor has been infected (at most one neighbor moving backwards through the population vector  can be infected each day), or when all members of the population have been determined to be e    ither currently infected or recovered:                                                                                                                                                                                        

    else {

      infect_neighbor_cond = 1;

      i = index_first_infected_person;

      while(infect_neighbor_cond == 1 && i >= 1){

	if ((pop.at(i)).get_status() > 0){

	  if ((pop.at(i-1)).get_status() == 0){

	    rand_num_prob_compare_int = rand() % 101;

	    rand_num_prob_compare_float =(float) rand_num_prob_compare_int;

	    rand_num_prob_compare_float_per= rand_num_prob_compare_float /100;

	    // If the randomly generated number is less than or equal to the probability threshold, infect the neighbor for 5 days and terminate the function                                                                          
                                                                                                                                                                                                                                           
	    if (rand_num_prob_compare_float_per <= trans_prob){

	      (pop.at(i-1)).infect(n);
	    }

	    infect_neighbor_cond = 0;

	  }

	}

	i = i - 1;

      }

      // Execute the while loop until either a neighbor has been infected (at most one neighbor moving forwards through the population vector  can be infected each day), or when all members of the population have been determined to be       either currently infected or recovered:                                                                                                                                                                                       
                                                                                                                                                                                                                                           
      infect_neighbor_cond = 1;

      i = index_first_infected_person;

      while (infect_neighbor_cond == 1 && i< (pop_size -1)){

	if ((pop.at(i)).get_status() > 0){

	  if ((pop.at(i+1)).get_status() == 0){

	    rand_num_prob_compare_int = rand() % 101;

	    rand_num_prob_compare_float =(float) rand_num_prob_compare_int;

	    rand_num_prob_compare_float_per= rand_num_prob_compare_float /100;

	    // If the randomly generated number is less than or equal to the probability threshold, infect the neighbor for 5 days and terminate the function     

	    if (rand_num_prob_compare_float_per <= trans_prob){

	      (pop.at(i+1)).infect(n);

	    }

	    infect_neighbor_cond = 0;

	  }

	}

	i++;

      }

    }

  };

    // Define "daily_exposure_generation()" method to allow for each member in the population to come into contact with a fixed number of other members who are chosen through a random-number generator function:                       
                                                                                                                                                                                                                                           
    vector<Person> daily_exposure_generation(int daily_exposure_num, int i){

      // Declare a vector of "Person" objects that will store the members of the population that the "ith" individual will be in contact with for the particular day:                                                                    
                                                                                                                                                                                                                                           
      vector<Person> exposure_pop;
      vector<int> exposure_pop_original_loc;
      bool duplicate_exposure_cond = 0;
      int rand_gen_person_contact;

      for (int j = 0; j < daily_exposure_num; j++){

        rand_gen_person_contact = rand() % pop_size;

        exposure_pop.push_back(pop.at(rand_gen_person_contact));

        exposure_pop_original_loc.push_back(rand_gen_person_contact);

        // If the number of elements in the vector "exposure_pop" exceeds one, then it must be checked that the member chosen for exposure is not a duplicate entry:                                                                     
                                                                                                                                                                                                                                           
        if (exposure_pop.size() > 1){

	  for (int k = 0;k < exposure_pop.size() - 1; k++){

	    if (rand_gen_person_contact == exposure_pop_original_loc.at(k)){

	      duplicate_exposure_cond= 1;

	    }

	  }

	}

        // If the member chosen for exposure is a duplicate entry, continue to generate random members of the population to append to the exposure population vector:                                                                    
                                                                                                                                                                                                                                           
        while (rand_gen_person_contact == i || duplicate_exposure_cond == 1){

          rand_gen_person_contact = rand() % pop_size;

	  exposure_pop.at(j) = pop.at(rand_gen_person_contact);

	  exposure_pop_original_loc.at(j) = rand_gen_person_contact;

	  // If the number of elements in the vector "exposure_pop" exceeds one, then it must be checked that the member chosen for exposure is not a duplicate entry:                                                                   
                                                                                                                                                                                                                                          
	  if (exposure_pop.size() > 1){

	    for (int k = 0;k < exposure_pop.size() - 1; k++){

	      if (rand_gen_person_contact == exposure_pop_original_loc.at(k)){

	        duplicate_exposure_cond= 1;

	      }

	      else {

	        duplicate_exposure_cond = 0;

	      }

	    }

	  }

	}

      }

      return exposure_pop;

    };


    // Define void method "attempted_group_infection()" to attempt to spread any infections attached to members of the population in contact with the single individual "ii"  during a particular day:                                    

    void attempted_group_infection(vector<Person>exposure_pop,int ii){

      int n = 6;
      int rand_num_prob_compare_int;
      float rand_num_prob_compare_float;
      float rand_num_prob_compare_float_per;

      if ((pop.at(ii)).get_status() == 0){

        for (int i = 0; i<exposure_pop.size(); i++){

          // If the member "i" of the population in contact with the member "ii" is currently infected, attempt to spread the infection to the member "ii":                                                                                

          if ((exposure_pop.at(i)).get_status() > 0){

	    rand_num_prob_compare_int = rand() % 101;

	    rand_num_prob_compare_float = (float) rand_num_prob_compare_int;

	    rand_num_prob_compare_float_per = rand_num_prob_compare_float / 100;

	    if (rand_num_prob_compare_float_per <= trans_prob){

	      (pop.at(ii)).infect(n);
	    
	    }

	  }

	}

    }

};

};




