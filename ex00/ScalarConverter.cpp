/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skroboth <skroboth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 15:28:10 by skroboth          #+#    #+#             */
/*   Updated: 2026/02/11 17:20:07 by skroboth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter()
{
}

ScalarConverter::ScalarConverter(const ScalarConverter &)
{
}

ScalarConverter::~ScalarConverter()
{
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &)
{
	return(*this);
}

static void printValues(char c, int i, float f, double d, Type check[4])
{
	if(check[0] == VALID)
		std::cout << "char: '" << c << "'\n";
	else if (check[0] == NON_PRINT)
		std::cout << "char: Non displayable\n";
	else
		std::cout << "char: impossible\n";
	
	if(check[1] == VALID)
		std::cout << "int: " << i << "\n";
	else
		std::cout << "int: impossible\n";
	
	if(check[2] == VALID)
		std::cout << "float: " << std::setprecision(1) << f << "f\n";
	else
		std::cout << "float: impossible\n";
	
	if(check[3] == VALID)
		std::cout << "double: " << std::setprecision(1) << d << "\n";
	else
		std::cout << "double: impossible\n";
}


static void	charConverter(const std::string &input)
{
	Type check[4] = {VALID, VALID, VALID, VALID};
	char c = input[1];
	
	if (!std::isprint(c))
		check[0] = NON_PRINT;
	
	int i = static_cast<int>(c);
	float f = static_cast<float>(c);
	double d = static_cast<double>(c);
	printValues(c, i, f, d, check);
}

static bool	isChar(const std::string &input)
{
	if (input.length() != 3)
		return (false);
	if (input[0] != '\'' || input[2] != '\'')
		return (false);
	charConverter(input);
	return (true);
}

static void intConverter(const std::string &input)
{
	Type check[4] = {VALID, VALID, VALID, VALID};
	int i = 0;
	char c = '0';
	float f = 0;
	double d = 0;

	long l = std::strtol(input.c_str(), NULL, 10);
	if (l > std::numeric_limits<int>::max() || 
		l < std::numeric_limits<int>::min())	
		check[1] = INVALID;
	else
		i = static_cast<int>(l); // INT conversion
	
	if (l > std::numeric_limits<float>::max() ||
		l < -std::numeric_limits<float>::max())
		check[2] = INVALID;
	else
		f = static_cast<float>(i); // FLOAT conversion
	
	if (l > std::numeric_limits<double>::max() ||
		l < -std::numeric_limits<double>::max())
		check[3] = INVALID;
	else
		d = static_cast<double>(i); // DOUBLE conversion
	
	if (i < 0 || i > 127)
		check[0] = INVALID;
	else if (!std::isprint(i))
		check[0] = NON_PRINT;
	else
		c = static_cast<char>(i); // CHAR conversion
		
	printValues(c, i, f, d, check);
}

static bool	isInt(const std::string &input)
{
	if (input[0] != '-' && input[0] != '+' && !std::isdigit(input[0]))
		return (false);
	for (int i = 1; input[i]; i++)
	{
		if (!std::isdigit(input[i]))
			return (false);
	}
	intConverter(input);
	return (true);
}

static void floatConverter(const std::string &input)
{
	Type check[4] = {VALID, VALID, VALID, VALID};
	int i = 0;
	char c = '0';
	float f = static_cast<float>(std::atof(input.c_str())); // FLOAT conversion
	double d = static_cast<double>(f); //double conversion
	
	if (std::isnan(f) || std::isinf(f))
		check[1] = INVALID;
	else if (f > std::numeric_limits<int>::max() || 
		f < std::numeric_limits<int>::min())	
		check[1] = INVALID;
	else
		i = static_cast<int>(f); // INT conversion
	
	if (check[1] == INVALID || i < 0 || i > 127)
		check[0] = INVALID;
	else if (!std::isprint(i))
		check[0] = NON_PRINT;
	else
		c = static_cast<char>(f); // CHAR conversion
		
	printValues(c, i, f, d, check);
}

static bool	isFloat(const std::string &input)
{
	bool decimal = false;

	if (input[input.length() - 1] != 'f')
		return (false);
		
	for(int i = 0; input[i]; i++)
	{
		if (input[i] == '.')
			decimal = true;
	}
	if (!decimal)
		return(false);
	
	floatConverter(input);
	return (true);
}

static void doubleConverter(const std::string &input)
{
	Type check[4] = {VALID, VALID, VALID, VALID};
	int i = 0;
	char c = '0';
	double d = std::atof(input.c_str()); //double conversion
	float f = static_cast<float>(d); // float conversion
	
	if (std::isnan(d) || std::isinf(d))
		check[1] = INVALID;
	else if (d > std::numeric_limits<int>::max() || 
		d < std::numeric_limits<int>::min())	
		check[1] = INVALID;
	else
		i = static_cast<int>(d); // INT conversion
	
	if (check[1] == INVALID || i < 0 || i > 127)
		check[0] = INVALID;
	else if (!std::isprint(i))
		check[0] = NON_PRINT;
	else
		c = static_cast<char>(d); // CHAR conversion
		
	printValues(c, i, f, d, check);
}

static bool	isDouble(const std::string &input)
{
	bool decimal = false;
	
	if (input[0] != '-' && input[0] != '+' && !std::isdigit(input[0]))
		return (false);
	for (int i = 1; input[i]; i++)
	{
		if (!std::isdigit(input[i]) && input[i] != '.')
		return (false);
		if (input[i] == '.')
			decimal = true;
	}
	if (!decimal)
		return(false);

	doubleConverter(input);
	return(true);
}

static bool isNanInf(const std::string &input)
{
	if (input == "nanf" || input == "+inff" || input == "-inff" || input == "inff")
    {
        floatConverter(input); 
        return true;
    }
    if (input == "nan" || input == "+inf" || input == "-inf" || input == "inf")
    {
        doubleConverter(input);  
        return true;
    }
	return(false);
}

static bool	isValid(const std::string &input)
{
	size_t i = 0;
	
    if (input[i] == '+' || input[i] == '-')
        i++;
    if (i >= input.length())
        return false;
    
    bool hasDigit = false;
    bool hasDecimal = false;
    bool hasF = false;
    
    for (; i < input.length(); i++)
    {
        if (std::isdigit(input[i]))
            hasDigit = true;
        else if (input[i] == '.')
        {
            if (hasDecimal || hasF)
                return false;
            hasDecimal = true;
        }
        else if (input[i] == 'f')
        {
            if (hasF) 
                return false;
				if (i != input.length() - 1) 
                return false; //f is somewhere inbetween
            hasF = true;
        }
        else
            return false;
    }
    
    if (!hasDigit)
        return false;
    
    if (hasF && !hasDecimal) //float only with decimal point
        return false;
    
    return true;
}

void ScalarConverter::convert(const std::string &input)
{
	if (input.empty())
    {
        std::cerr << "Error: empty input" << std::endl;
        return;
    }

	if (isNanInf(input))
		return ;
		
    if (!isValid(input))
    {
        std::cerr << "Error: invalid input" << std::endl;
        return;
    }
		
	bool (*checkFunctions[4])(const std::string &) = {&isChar, &isInt, &isFloat, &isDouble};
	for (int i = 0; i < 4; i++)
	{
		if (checkFunctions[i](input) == true)
			return ;
	}
	//output error message (couldnt find any type match)(but should actually not get to here)
	std::cerr << "Error: no type match found" << std::endl;
	return ;
}
