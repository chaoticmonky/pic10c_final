//
//  main.cpp
//  pic10c_final
//
//  Created by Yugantar Prakash on 6/1/18.
//  Copyright © 2018 Yugantar Prakash. All rights reserved.
//

#include <iostream>
#include "ess_simulation.hpp"


int main() {
//    std::shared_ptr<Agents> a1(new predator);
//    std::shared_ptr<Agents> a2(new tit_4_tat);
//    a1->add_food(15);
//    a1->sub_health();
//    std::cout << a1  << std::endl;
//
//    (is_predator(a1))? std::cout << "predator it is:"  << std::endl: std::cout << "it isnt'" << std::endl;
//    (is_predator(a2))? std::cout << "predator it is:"  << std::endl: std::cout << "it isnt'" << std::endl;
//
//    (a1 < a2)? std::cout << "a1 is predator and a2 is t"  << std::endl: std::cout << "a1 is not predator" << std::endl;
//    (a2 < a1)? std::cout << "a2 is predator and a1 is t"  << std::endl: std::cout << "a2 is not predator" << std::endl;
    int matrix[4] = {2, 0, 6, 1};
    simulation s1(10, matrix, 30);//10 agents each, with 30 food as the requirement for reproduction
    std::cout << s1.num_of_predators() << " :number of predators alive" << std::endl;
    s1.battle(0, 5);
    s1.battle(0, 11);
    s1.battle(11, 5);
    for(auto i = 0; i<10;++i) s1.battle(0, 10+i);
    
    s1.check_reproducability();
    std::cout << s1.num_of_predators() << " :number of predators alive" << std::endl;
    return 0;
}
