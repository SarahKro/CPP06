/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skroboth <skroboth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 13:55:36 by skroboth          #+#    #+#             */
/*   Updated: 2026/02/12 14:55:45 by skroboth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <iostream>
#include <stdint.h>

struct Data;

class Serializer
{
    private:
        Serializer();
        Serializer(const Serializer &other);
        ~Serializer();
        Serializer &operator=(const Serializer &other);

    public:
        static uintptr_t serialize(Data* ptr);
        static Data* deserialize(uintptr_t raw);
    
};


# endif