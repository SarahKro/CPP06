/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skroboth <skroboth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 15:28:10 by skroboth          #+#    #+#             */
/*   Updated: 2026/02/14 17:33:45 by skroboth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

enum TypeIndex {
    CHAR_IDX = 0,
    INT_IDX = 1,
    FLOAT_IDX = 2,
    DOUBLE_IDX = 3
};

static const int ASCII_MAX = 127;
static const int ASCII_MIN = 0;

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
	return (*this);
}

static void	printValues(char c, int i, float f, double d, Type check[4])
{
	if (check[CHAR_IDX] == VALID)
		std::cout << "char: '" << c << "'\n";
	else if (check[CHAR_IDX] == NON_PRINT)
		std::cout << "char: Non displayable\n";
	else
		std::cout << "char: impossible\n";
	if (check[INT_IDX] == VALID)
		std::cout << "int: " << i << "\n";
	else
		std::cout << "int: impossible\n";
	if (check[FLOAT_IDX] == VALID)
		std::cout << "float: " << std::fixed << std::setprecision(1) << f << "f\n";
	else
		std::cout << "float: impossible\n";
	if (check[DOUBLE_IDX] == VALID)
		std::cout << "double: " << std::fixed << std::setprecision(1) << d << "\n";
	else
		std::cout << "double: impossible\n";
}

static void validateChar(int intValue, char &charValue, Type &status) 
{
    if (intValue < ASCII_MIN || intValue > ASCII_MAX)
        status = INVALID;
    else if (!std::isprint(intValue))
        status = NON_PRINT;
    else 
	{
        charValue = static_cast<char>(intValue);
        status = VALID;
    }
}

static void	charConverter(const std::string &input)
{
	Type	check[4] = {VALID, VALID, VALID, VALID};

	char c = input[1];
	if (!std::isprint(c))
		check[CHAR_IDX] = NON_PRINT;
	int i = static_cast<int>(c);
	float f = static_cast<float>(c);
	double d = static_cast<double>(c);
	printValues(c, i, f, d, check);
}

static void	intConverter(const std::string &input)
{
	Type	check[4] = {VALID, VALID, VALID, VALID};
	int		i = 0;
	char	c = '0';
	long	l = std::strtol(input.c_str(), NULL, 10);
	
	if (l > std::numeric_limits<int>::max() || l < std::numeric_limits<int>::min())
		{	
			std::cerr << "Error: Invalid input\n";
			return;
		}
	else
		i = static_cast<int>(l); // INT conversion
	float f = static_cast<float>(i); // FLOAT conversion
	double d = static_cast<double>(i); // DOUBLE conversion
	validateChar(i, c, check[CHAR_IDX]); //CHAR conversion
	printValues(c, i, f, d, check);
	return;
}

static void	floatDoubleConverter(const std::string &input, bool isFloat)
{
	Type	check[4] = {VALID, VALID, VALID, VALID};
	int		i = 0;
	char	c = '0';

    double temp = std::strtod(input.c_str(), NULL);
    float f = static_cast<float>(temp); 
    double d = isFloat ? static_cast<double>(f) : temp;
	// if float -> conversion from float
	
	if (std::isnan(d) || std::isinf(d))
		check[INT_IDX] = INVALID;
	else if (d > std::numeric_limits<int>::max() || d < std::numeric_limits<int>::min())
		check[INT_IDX] = INVALID;
	else
		i = static_cast<int>(f); // INT conversion
	validateChar(i, c, check[CHAR_IDX]); //CHAR conversion
	printValues(c, i, f, d, check);
}

static Type	getType(const std::string &input)
{
	size_t	i = 0;
	bool	hasDigit = false;
	bool	hasDecimal = false;
	bool	hasF = false;

	if (input[i] == '+' || input[i] == '-')
		i++;
	if (i >= input.length()) //input is only a sign
		return (INVALID);
	if (input == "nanf" || input == "+inff" || input == "-inff" || input == "inff")
		return (FLOAT);
	if (input == "nan" || input == "+inf" || input == "-inf" || input == "inf")
		return (DOUBLE);
	if (input.length() == 3 && input[0] == '\'' && input[2] == '\'')
		return (CHAR);
	for (; i < input.length(); i++)
	{
		if (std::isdigit(input[i]))
			hasDigit = true;
		else if (input[i] == '.')
		{
			if (hasDecimal || hasF)
				return (INVALID);
			hasDecimal = true;
		}
		else if (input[i] == 'f')
		{
			if (hasF)
				return (INVALID);
			if (i != input.length() - 1)
				return (INVALID);
			hasF = true;
		}
		else
			return (INVALID);
	}
	if (hasDigit && hasF && hasDecimal)
		return (FLOAT);
	if (hasDigit && hasDecimal)
		return (DOUBLE);
	if (hasDigit && !hasF && !hasDecimal)
		return (INT);
	return (INVALID);
}

void ScalarConverter::convert(const std::string &input)
{
	std::cout << "INPUT: " << input << "\n";
	if (input.empty())
	{
		std::cerr << "Error: empty input\n";
		return ;
	}
	Type type = getType(input);
	switch (type)
	{
		case(CHAR) : charConverter(input); break;
		case(INT) : intConverter(input); break;
		case(FLOAT) : floatDoubleConverter(input, true); break;
		case(DOUBLE) : floatDoubleConverter(input, false); break;
		default : std::cerr << "Error: Invalid input\n"; break;
	}
}
