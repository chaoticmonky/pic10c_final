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
    
    (is_predator(a1))? std::cout << "predator it is:" : std::cout << "it isnt'";
    (is_predator(a2))? std::cout << "predator it is:" : std::cout << "it isnt'";
    
    return 0;
}
