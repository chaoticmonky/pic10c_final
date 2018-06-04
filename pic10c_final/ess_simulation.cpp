//
//  ess_simulation.cpp
//  pic10c_final
//
//  Created by Yugantar Prakash on 6/1/18.
//  Copyright © 2018 Yugantar Prakash. All rights reserved.
//

#include "ess_simulation.hpp"

/**
 member variable add_food. adds the food in the agent's storage
*/
void Agents::add_food(int increase)
{
    food+=increase;
}


void Agents::sub_health(){--health;} //decreases health by one

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


simulation::simulation(const std::size_t sz, int* matrix, std::size_t food_limit): reward_matrix(matrix), reproReq(food_limit)//constructor
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
    ;
}

/**
 member function battle. makes the agents fight against each other.
 @returns: the number of predators still alive
 */
size_t simulation::num_of_predators()
{
    if (is_predator(all_players[all_players.size()-1])) //only predators are left in the pool
    {
        return all_players.size();
    }
    else //there is at least one tit_4_tat agent alive
    {
        for (std::size_t i = 0; i<all_players.size(); ++i)
        {
            if (all_players[i]<all_players[i+1])
            {
                return i+1;
            }
        }
    }
    return 0;
}

void tit_4_tat::cheated()
{
    decieved = true;
}

bool tit_4_tat::check_cheated()//returns true if the agent was cheated last turn
{
    return decieved;
}
/**
 member function battle. makes the agents fight against each other.
 @parameter: agent1 is the first agent's pointer
 @parameter: agent2 is the second agent's pointer
 */

void simulation::battle(const std::size_t first, const std::size_t second)
{
    const std::shared_ptr<Agents> agent1(all_players[first]);
    const std::shared_ptr<Agents> agent2(all_players[second]);
    agent1->sub_health(); agent2->sub_health(); //decrease both their healths
    if (agent1 == agent2)//if the agents are same, their strategies will be the same
    {
        if (is_predator(agent1)) //predator vs predator
        {
            agent1->add_food(reward_matrix[3]);
            agent2->add_food(reward_matrix[3]);
            std::cout << "Defect vs Defect" << std::endl;
        }
        else //tit_4_tat vs tit_4_tat
        {
            agent1->add_food(reward_matrix[0]);
            agent2->add_food(reward_matrix[0]);
            std::cout << "Coop vs Coop" << std::endl;
        }
    }
    else if (agent1 < agent2)//agent1 is predator while agent2 tit_4_tat
    {
        if (!(agent2->check_cheated()))//agent2 was not cheated last turn
        {
            agent1->add_food(reward_matrix[2]); //agent1 has won
            agent2->add_food(reward_matrix[1]); //agent2 has lost
            agent2->cheated();
        }
        else //both decieved each other
        {
            agent1->add_food(reward_matrix[3]);
            agent2->add_food(reward_matrix[3]);
        }
    }
    else//agent2 is predator while agent1 tit_4_tat
    {
        if (!(agent1->check_cheated()))//agent2 was not cheated last turn
        {
            agent2->add_food(reward_matrix[2]); //agent1 has won
            agent1->add_food(reward_matrix[1]); //agent2 has lost
            agent1->cheated();
        }
        else //both decieved each other
        {
            agent1->add_food(reward_matrix[3]);
            agent2->add_food(reward_matrix[3]);
        }
    }
}
