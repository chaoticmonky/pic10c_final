# pic10c_final
Final Assignment for PIC 10C

I had been reading works of a few evolutionary biologists, including the Selfish Gene by Richard Dawkins, the book that inspired me to write this simulator. In the book, Dawkins refers to a simulation made in excel to find the evolutionary stable strategy in one of the basic type of games: repetitive prisoner's dilemma. I will describe the basic of the game now:

Game:
1. There are agents in the pool. They have food and health as attributes and two possible actions during the game: Cooperate or Defect.

2. Each iteration, two random agents are selected and they are pit against each other in a 'battle.'

3. The results of the battle are based on the actions they chose and how the food attribute changes for each agent is affected by that result.

4. At the end of the battle stage, health of each agents in the pool is decreased by one.

3. At the end of health deduction stage, all agents that have food over a prespecified threshold creates a daughter agent.

4. At the end of reproduction stage, any agent with health less than or equal to 0 is killed.

5. Steps 2-5 are repeated for for the number of iterations set by the user.

I created two main classes: simulation and agents. 'agents' class has subclasses, which are the types of agents we want in the pool. For my project, there are two:
1. predator: this agent always defects, regardless of any other factor.
2. tit for tat: this agent always cooperates, unless during the last battle it was cheated (the agent it was battling defected).

Rest all the attributes, including initial health and the threshold needed for reproduction remained the same, essentially mimicking two different types of strategies employed by members of the same species.

The simulation class stores all the agents in the pool as a vector of pointers to agents (std::vector<std::shared_ptr<Agents>> all_players), the reward matrix that determines how the food is updated after each battle (int* reward_matrix), the threshold for reproduction (std::size_t reproReq) and finally records the population of each type of agent during each iteration (std::unordered_multimap<std::size_t, std::size_t> population).

I'll now describe how each step 2-4 works.


Battle stage: simulation::run_simulation function runs each iteration. it creates a copy of the pool and randomly shuffles this copy to make sure agents battle against other agents at random. std::random_shuffle algorithm is used for this. next, the function calls the simulation::battle function for all agents . Indices of two agents and a copy of the pool are sent as parameters and depending on the states of the agents, their food attribute is changed.

Health Deduction stage: the health of both agents is deducted in the simulation::battle function, albiet before the battle even takes place, but that does not affect the simulation since the killing of old agents comes at the end.

Reproduction stage: this is covered by simulation::check_reproducability function, which checks for the whole pool if any agent has food equal to or more than the threshold, another agent of the same type is added to the pool while the agent's food is reduced to 2 since I decided that reproduction should be a costly action, like it is for most complex creatures today. std::for_each algorithm failed to be implement because when an agent was added to the pool, the iterator failed to increment properly while the algorithm was running. the failed attempt can be seen in comments of simulation::check_reproducability function

Killing stage: the all_players is iterated through, and any agent that has 0 health is killed using the vector::erase function. I thought about using std::for_each algorithm using a lambda function and a simple if statement, however that wasn't possible since all agents of same type are identical and there was no effcient way to delete an agent as well as update whole pool altogether (including shifting all other agents that followed the recently killed agent by one place to the left). The failed attempt can be seen to be commented out


Since my ideas for this project does not end with this quarter, I had to make sure the simulation was as generic as possible if different factors for it are changed. Primarily, I wanted to make sure that adding new agents with different strategies would be easy as the two agents used in this simulation are very basic.
