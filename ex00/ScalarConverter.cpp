/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skroboth <skroboth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 15:28:10 by skroboth          #+#    #+#             */
/*   Updated: 2026/02/11 14:50:02 by skroboth         ###   ########.fr       */
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
}

static void printValues(char c, int i, float f, double d, Type check[4])
{
	if(check[0] == VALID)
		std::cout << "char: " << c << "\n";
	else if (check[0] == NON_PRINT)
		std::cout << "char: Non displayable\n";
	else
		std::cout << "char: impossible\n";
	
	if(check[1] == VALID)
		std::cout << "int: " << i << "\n";
	else
		std::cout << "int: impossible\n";
	
	if(check[2] == VALID)
		std::cout << "float: " << f << "\n";
	else
		std::cout << "float: impossible\n";
	
	if(check[3] == VALID)
		std::cout << "double: " << d << "\n";
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
		l < std::numeric_limits<float>::min())
		check[2] = INVALID;
	else
		f = static_cast<float>(i); // FLOAT conversion
	
	if (l > std::numeric_limits<double>::max() ||
		l < std::numeric_limits<double>::min())
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
	// convert to other types
	return (true);
}

static void floatConverter(const std::string &input)
{
	Type check[4] = {VALID, VALID, VALID, VALID};
	int i = 0;
	char c = '0';
	float f = 0;
	double d = 0;

	long l = std::strtol(input.c_str(), NULL, 10);
	if (l > std::numeric_limits<float>::max() ||
		l < std::numeric_limits<float>::min())
		check[2] = INVALID;
	else
		f = static_cast<float>(l); // FLOAT conversion

	
	if (l > std::numeric_limits<int>::max() || 
		l < std::numeric_limits<int>::min())	
		check[1] = INVALID;
	else
		i = static_cast<int>(f); // INT conversion
	
	
	if (l > std::numeric_limits<double>::max() ||
		l < std::numeric_limits<double>::min())
		check[3] = INVALID;
	else
		d = static_cast<double>(f); // DOUBLE conversion
	
	if (i < 0 || i > 127)
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
	
	// convert to other types
	floatConverter(input);
	return (true);
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
	// convert to other types
	return(true);
}


static bool isNanInf(const std::string &input)
{
	if (input == "nan" || input == "nanf" || 
    input == "inf" || input == "inff" || 
    input == "+inf" || input == "+inff" ||
    input == "-inf" || input == "-inff")
	{
		// output info & convert to other types
		return(true);
	}
	return(false);
}

static bool	isValid(const std::string &input)
{
	int	decimal = 0;
	int i = 0;
	
	if (input[i] == '+' || input[i] == '-')
		i++;
		
	for (i; input[i]; i++)
	{
		if (input[i] == '.')
			decimal++;
		if (input[i] != '.' && !isdigit(input[i]) && input[i] != 'f')
		{
			//output error message --> invalid characters
			return(false);
		}
	}
	if (decimal > 1)
	{
		//output error message --> more than one decimal point
		return(false);
	}
	return(true);
}

void ScalarConverter::convert(const std::string &input)
{
	// Detect the type
	if (isNanInf(input))
		return ;
	if (!isValid(input))
		return ;
		
	bool (*checkFunctions[4])(const std::string &) = {&isChar, &isInt, &isFloat, &isDouble};
	for (int i = 0; i < 4; i++)
	{
		if (checkFunctions[i](input) == true)
			return ;
	}
	//output error message (couldnt find any type match)(but should actually not get to here)
	return ;
}
