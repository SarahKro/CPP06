/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skroboth <skroboth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 15:28:10 by skroboth          #+#    #+#             */
/*   Updated: 2026/02/14 16:58:52 by skroboth         ###   ########.fr       */
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

static void	floatConverter(const std::string &input)
{
	floatDoubleConverter(input, true);
}

static void	doubleConverter(const std::string &input)
{
	floatDoubleConverter(input, false);
}

static bool	isNanInf(const std::string &input)
{
	if (input == "nanf" || input == "+inff" || input == "-inff"
		|| input == "inff")
	{
		floatDoubleConverter(input, true);
		return (true);
	}
	if (input == "nan" || input == "+inf" || input == "-inf" || input == "inf")
	{
		floatDoubleConverter(input, false);
		return (true);
	}
	return (false);
}

static Type	getType(const std::string &input)
{
	size_t	i = 0;
	bool	hasDigit = false;
	bool	hasDecimal = false;
	bool	hasF = false;
	bool 	hasE = false;

	if (input[i] == '+' || input[i] == '-')
		i++;
	if (i >= input.length())
		return (INVALID);

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
		else if (input[i] == 'e')
		{
			if (hasE)
				return (INVALID);
			hasE = true;
		}
		else if (input[i] == 'f')
		{
			if (hasF)
				return (INVALID);
			if (i != input.length() - 1)
				return (INVALID); // f is somewhere inbetween
			hasF = true;
		}
		else
			return (INVALID);
	}
	if (hasDigit && hasF && hasDecimal)
		return (FLOAT);
	if (hasDigit && hasDecimal)
		return (DOUBLE);
	if (input.length() == 3 && input[0] == '\'' && input[2] == '\'')
		return (CHAR);
	if (hasDigit && !hasF && !hasE && !hasDecimal)
		return (INT);
	return (INVALID);
}

void ScalarConverter::convert(const std::string &input)
{
	if (input.empty())
	{
		std::cerr << "Error: empty input\n";
		return ;
	}
	if (isNanInf(input))
		return ;
	Type givenType = getType(input);
	Type type[4] = {CHAR, INT, FLOAT, DOUBLE};
	void (*checkFunctions[4])(const std::string &) = {&charConverter, &intConverter, &floatConverter, &doubleConverter};
	for (int i = 0; i < 4; i++)
	{
		if (givenType == type[i])
		{
			checkFunctions[i](input);
			return ;
		}
	}
	std::cerr << "Error: no type match found\n";
	return ;
}
