/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skroboth <skroboth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:46:10 by skroboth          #+#    #+#             */
/*   Updated: 2026/02/12 15:03:31 by skroboth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"
#include "Data.hpp"

#define GREEN "\033[32m"
#define RESET "\033[0m"

int main()
{
    Data *tester = new Data;
    tester->name = "Tsuru";
    tester->age = 70;
    tester->superpower = "Embarassing people";

    
    std::cout << GREEN << "Original pointer: " << RESET << tester << "\n";
    
    uintptr_t raw = Serializer::serialize(tester);
    std::cout << GREEN << "After serialization: " << RESET << raw << "\n";

    
    tester = Serializer::deserialize(raw);
    std::cout << GREEN << "Deserialized pointer: " << RESET << tester << "\n\n";
    std::cout << GREEN << "Saved data\nName: " << RESET << tester->name 
    << GREEN << "\nAge: " << RESET << tester->age 
    << GREEN << "\nSuperpower: " << RESET << tester->superpower << "\n";

    delete(tester);
    return(0);
}