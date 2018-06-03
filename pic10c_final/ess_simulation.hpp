//
//  ess_simulation.hpp
//  pic10c_final
//
//  Created by Yugantar Prakash on 6/1/18.
//  Copyright © 2018 Yugantar Prakash. All rights reserved.
//

#ifndef ess_simulation_hpp
#define ess_simulation_hpp

#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>

/**
 simulation class will store a whole simulation
 */

class Agents
{
protected:
    std::size_t health;
    std::size_t food;

public:
    Agents(): health(10), food(10){}
    virtual ~Agents() = default; //pure virtual destructor to not allow creation of
};

class predator : public Agents
{
public:
    predator(): Agents(){}//constructor
    ~predator() = default;
};

class tit_4_tat : public Agents
{
private:
    bool decieved;//stores True if during the last iteration the agent was decieved
public:
    tit_4_tat(): Agents(), decieved(false){}//constructor
    ~tit_4_tat() = default;
};





class simulation
{
private:
    std::vector<std::shared_ptr<Agents>> all_players; //storing all the agents currently alive
    std::unordered_map<std::size_t, std::size_t> population; //stores the number of each agent every iteration
    
public:
    simulation(std::size_t);
    void run_simulation(); //run the simulation, updating the values of each agent in the vector and storing a map of the number of each type of agents
    
    void battle(const std::shared_ptr<Agents>, const std::shared_ptr<Agents>);
    
    size_t num_of_predators(); //finds the number of predator agents in the vector
};


bool operator<(const std::shared_ptr<Agents>, const std::shared_ptr<Agents>);
bool operator==(const std::shared_ptr<Agents>, const std::shared_ptr<Agents>);

bool is_predator(const std::shared_ptr<Agents> an_agent);



#endif /* ess_simulation_hpp */
