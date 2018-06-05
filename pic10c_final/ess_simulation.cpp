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
    for (std::size_t i = 0; i<sz; ++i) {
        all_players.push_back( std::shared_ptr<Agents> (new predator) );
    }
    for (std::size_t i = 0; i<sz; ++i) {
        all_players.push_back( std::shared_ptr<Agents> (new tit_4_tat) );
    }
}


/**
 member function run_simulation. Makes different agents fight against each other
 @parameter: iterations is the number of times each round of fighting happens
 Three stages are done for iteration number of times:
 I: all agents are randomly selected and made to fight each other, implicitly updating the attributes
 II: kills or gives birth to new agents based on their attributes
 III: records the number of different agents alive for data analysis
 */
void simulation::run_simulation(std::size_t iterations)
{
    for(int i=0; i<iterations; ++i)
    {
        //Stage I. fighting
        auto copy = all_players;
        std::random_shuffle(copy.begin(), copy.end());
        for (int j=0; j<all_players.size()/2; ++j)
        {
            battle(j, all_players.size()-j-1, copy);
            //for now, if it is odd, then the agent battles itself
        }
        
        //Stage II. deaths and births
        
        check_reproducability();//all new ones are born
        kill_old();//old ones are killed
        
        //Stage III. storing data
        population.insert(std::make_pair(num_of_predators(), all_players.size()-num_of_predators()));
        std::cout << " " << num_of_predators() << ":" << all_players.size()-num_of_predators() << std::endl;

    }
}

/**
 member function battle. makes the agents fight against each other.
 @returns: the number of predators still alive
 */
size_t simulation::num_of_predators()
{
    if (all_players.size() == 0) return 0;
    else if (is_predator(all_players[all_players.size()-1]))//only predators are left in the pool
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

void tit_4_tat::reversed_cheated()
{
    decieved = false;
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

void simulation::battle(const std::size_t first, const std::size_t second, std::vector<std::shared_ptr<Agents>> copy)
{
    const std::shared_ptr<Agents> agent1(copy[first]);
    const std::shared_ptr<Agents> agent2(copy[second]);
    agent1->sub_health(); agent2->sub_health(); //decrease both their healths
    if (agent1 == agent2)//if the agents are same, their strategies will be the same
    {
        if (is_predator(agent1)) //predator vs predator
        {
            agent1->add_food(reward_matrix[3]);
            agent2->add_food(reward_matrix[3]);
        }
        else //tit_4_tat vs tit_4_tat
        {
            if (agent1->check_cheated())//agent1 was cheated last time
            {
                agent1->add_food(reward_matrix[2]); //agent1 has won
                agent2->add_food(reward_matrix[1]); //agent2 has lost
                agent2->cheated();
                agent1->reversed_cheated();
            }
            else if (agent2->check_cheated())//agent2 was cheated last time
            {
                agent2->add_food(reward_matrix[2]); //agent1 has won
                agent1->add_food(reward_matrix[1]); //agent2 has lost
                agent1->cheated();
                agent2->reversed_cheated();
            }
            else //both cooperate
            {
            agent1->add_food(reward_matrix[0]);
            agent2->add_food(reward_matrix[0]);
            }
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

/**
 void member function check_reproducability
 checks if any agent has enough food to reproduce
 if so, then it adds another agent of the same type
*/
void simulation::check_reproducability()
{
    for (std::size_t i = 0; i<all_players.size(); ++i)
    {
        if (all_players[i]->get_food()>=reproReq)
        {
            all_players[i]->add_food(static_cast<int>(-reproReq+2));
            //cost for reproducting is all the food except 2
            
            //if the agent is a predator, it is added at the beginning. if the agent is tit_4_tat, it is added at the end
            (is_predator(all_players[i]))? all_players.insert(all_players.begin(), std::shared_ptr<Agents> (new predator)):all_players.insert(all_players.end(),std::shared_ptr<Agents> (new tit_4_tat));
        }
    }
}

/**
 void member function check_reproducability
 checks if any agent has 0 health
 if so, then it kills that agent
 */
void simulation::kill_old()
{
    for (std::size_t i = all_players.size()-1; i<all_players.size(); --i)
    {
        if (all_players[i]->get_health() <= 0) all_players.erase(all_players.begin() + i);
        //if the agent has health 0, it is deleted
    }
}
