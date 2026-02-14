/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skroboth <skroboth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 17:29:20 by skroboth          #+#    #+#             */
/*   Updated: 2026/02/12 18:07:32 by skroboth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <cstdlib>

Base * generate(void)
{
    Base *winner;
    static bool seeded = false;
    if (!seeded)
    {
        std::srand(std::time(NULL));
        seeded = true;
    }
    int dice = std::rand() % 3;

    switch(dice)
    { 
        case 0:
            winner = new A();
            return(winner);
        case 1:
            winner = new B();
            return(winner);
        default:
            winner = new C();
            return(winner);
    }
    throw std::runtime_error("Could not choose a class");
    return(NULL); 
}

void identify(Base* p)
{
    if (dynamic_cast<A*>(p) != 0)
        std::cout << "A\n";
    else if (dynamic_cast<B*>(p) != 0)
        std::cout << "B\n";
    else if (dynamic_cast<C*>(p) != 0)
        std::cout << "C\n";
}

void identify(Base& p)
{
    if (dynamic_cast<A*>(&p) != 0)
        std::cout << "A\n";
    else if (dynamic_cast<B*>(&p) != 0)
        std::cout << "B\n";
    else if (dynamic_cast<C*>(&p) != 0)
        std::cout << "C\n";
}


int main()
{
    
    Base *random = generate();
    identify(random);
    identify(*random);

    delete random;
    return(0);
}
