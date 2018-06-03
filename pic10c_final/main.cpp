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
    std::shared_ptr<Agents> a1(new predator);
    std::shared_ptr<Agents> a2(new tit_4_tat);
//    Agents* a1 = new predator;
//    Agents* a2 = new tit_4_tat;
    
    (is_predator(a1))? std::cout << "predator it is:"  << std::endl: std::cout << "it isnt'" << std::endl;
    (is_predator(a2))? std::cout << "predator it is:"  << std::endl: std::cout << "it isnt'" << std::endl;
    
    (a1 < a2)? std::cout << "a1 is predator and a2 is t"  << std::endl: std::cout << "a1 is not predator" << std::endl;
    (a2 < a1)? std::cout << "a2 is predator and a1 is t"  << std::endl: std::cout << "a2 is not predator" << std::endl;
    return 0;
}
