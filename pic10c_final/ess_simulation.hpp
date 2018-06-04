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
    void add_food(int);
    void sub_health();
    virtual void cheated() = 0;
    virtual bool check_cheated() = 0;
};

class predator : public Agents
{
public:
    predator(): Agents(){}//constructor
    ~predator() = default;
    void cheated() override{}
    bool check_cheated() override {return true;}
    
};

class tit_4_tat : public Agents
{
private:
    bool decieved;//stores True if during the last iteration the agent was decieved
public:
    tit_4_tat(): Agents(), decieved(false){}//constructor
    ~tit_4_tat() = default;
    void cheated() override;
    bool check_cheated() override;
};





class simulation
{
private:
    std::vector<std::shared_ptr<Agents>> all_players; //storing all the agents currently alive
    std::unordered_map<std::size_t, std::size_t> population; //stores the number of each agent every iteration
    int* reward_matrix; // stores the rewards in the form: {T.T, T.P, P.T, P.P} (reward of the first agent when put against the second agent)
    
public:
    simulation(const std::size_t, int*);
    void run_simulation(); //run the simulation, updating the values of each agent in the vector and storing a map of the number of each type of agents
    
    void battle(const std::size_t, const std::size_t);
    
    size_t num_of_predators(); //finds the number of predator agents in the vector
};


bool operator<(const std::shared_ptr<Agents>, const std::shared_ptr<Agents>);
bool operator==(const std::shared_ptr<Agents>, const std::shared_ptr<Agents>);

bool is_predator(const std::shared_ptr<Agents> an_agent);



#endif /* ess_simulation_hpp */
