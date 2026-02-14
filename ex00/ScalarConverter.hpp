/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skroboth <skroboth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 15:17:32 by skroboth          #+#    #+#             */
/*   Updated: 2026/02/14 16:07:15 by skroboth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <iostream>
#include <string>
#include <cmath>
#include <limits>
#include <iomanip>
#include <cstdlib>

enum Type {
    CHAR,
    INT,
    FLOAT,
    DOUBLE,
    VALID,
    NON_PRINT,
    INVALID
};

class ScalarConverter{
  
    private:
        ScalarConverter();
        ScalarConverter(const ScalarConverter &);
        ~ScalarConverter();
        ScalarConverter &operator=(const ScalarConverter &);
    
    public:
        static void convert(const std::string &input);
};



#endif