//
//  ess_simulation.cpp
//  pic10c_final
//
//  Created by Yugantar Prakash on 6/1/18.
//  Copyright © 2018 Yugantar Prakash. All rights reserved.
//

#include "ess_simulation.hpp"


bool is_predator(const std::shared_ptr<Agents> an_agent)
{
    
    std::shared_ptr<predator> predPtr = std::dynamic_pointer_cast<predator>(an_agent); //dynamic casting to predator
    
    
    
    if(predPtr) return true; //if it is a predator, then return true
    
    return false;//otherwise it is a tit_4_tat. return false
    
}

bool operator<(const std::shared_ptr<Agents> agent1, const std::shared_ptr<Agents> agent2)//we will go with the rule that predators are less than tit_4_tat
{
    return (is_predator(agent2) < is_predator(agent1)) ? true: false;
}

bool operator==(const std::shared_ptr<Agents> agent1, const std::shared_ptr<Agents> agent2)
{
    return !(agent1 < agent2 || agent2 < agent1);
}


simulation::simulation(std::size_t sz)//constructor
{
    //remember to use vector.push_back(std::make_shared<Predator>();
    //to make sure that the smart pointer is for the base class but it works with whatever the pointer actually points to
    for (std::size_t i = 0; i<sz; ++i) {
        all_players.push_back( std::shared_ptr<Agents> (new predator) );
    }
    for (std::size_t i = 0; i<sz; ++i) {
        all_players.push_back( std::shared_ptr<Agents> (new tit_4_tat) );
    }
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
 @returns: the number of predators still alive
 */
size_t simulation::num_of_predators()
{
    if (is_predator(all_players[-1])) //only predators are left in the pool
    {
        return all_players.size();
    }
    else //there is at least one tit_4_tat agent alive
    {
        for (std::size_t i = 0; i<all_players.size(); ++i)
        {
            if (all_players[i]<all_players[i+1]) {
                return i+1;
            }
        }
    }
    return 0;
}

/**
 member function battle. makes the agents fight against each other.
 @parameter: agent1 is the first agent's pointer
 @parameter: agent2 is the second agent's pointer
 */

void simulation::battle(const std::shared_ptr<Agents> agent1, const std::shared_ptr<Agents> agent2)
{
    ;
}
