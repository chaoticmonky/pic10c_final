//
//  ess_simulation.cpp
//  pic10c_final
//
//  Created by Yugantar Prakash on 6/1/18.
//  Copyright © 2018 Yugantar Prakash. All rights reserved.
//

#include "ess_simulation.hpp"

simulation::simulation(std::size_t sz)//constructor
{
    //remember to use vector.push_back(std::make_shared<Predator>();
    //to make sure that the smart pointer is for the base class but it works with whatever the pointer actually points to
}


/**
 member function run_simulation. Makes different agents fight against each other
 Three stages:
 I: all agents are randomly selected and made to fight each other, implicitly updating the attributes
 II: kills or gives birth to new agents based on their attributes
 III: records the number of different agents alive for data analysis
*/
void simulation::run_simulation()
{

}

/**
 member function battle. makes the agents fight against each other.
 @parameter: agent1 is the first agent's pointer
 @parameter: agent2 is the second agent's pointer
*/

void simulation::battle(Agents agent1, Agents agent2)
{
    
}

bool is_predator(const std::shared_ptr<Agents> an_agent)
{
    
    std::shared_ptr<predator> predPtr = std::dynamic_pointer_cast<predator>(an_agent); //dynamic casting to predator
    
    
    
    if(predPtr) return true; //if it is a predator, then return true
    
    return false;//otherwise it is a tit_4_tat. return false
    
}

