/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skroboth <skroboth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 17:02:10 by skroboth          #+#    #+#             */
/*   Updated: 2026/02/14 17:31:57 by skroboth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

// int main(int argc, char **argv)
// {
//     if (argc != 2)
//     {
//         std::cerr << "Error: Exactly one argument allowed\n";
//         return(1);
//     }
//     ScalarConverter::convert(argv[1]);
//     return(0);
// }

int	main(int argc, char **argv)
{
	if (argc == 2)
		ScalarConverter::convert(argv[1]);

	ScalarConverter::convert("'A'");
	std::cout << "-------------------------" << std::endl;
	ScalarConverter::convert("~");
	std::cout << "-------------------------" << std::endl;
	ScalarConverter::convert("0");
	std::cout << "-------------------------" << std::endl;
	ScalarConverter::convert("128");
	std::cout << "-------------------------" << std::endl;
	ScalarConverter::convert("-1");
	std::cout << "-------------------------" << std::endl;
	ScalarConverter::convert("2147483647");
	std::cout << "-------------------------" << std::endl;
	ScalarConverter::convert("2147483648");
	std::cout << "-------------------------" << std::endl;
	ScalarConverter::convert("-2147483648");
	std::cout << "-------------------------" << std::endl;
	ScalarConverter::convert("-2147483649");
	std::cout << "-------------------------" << std::endl;
	ScalarConverter::convert("-2147483649");
	std::cout << "--------HERE-------------" << std::endl;
	ScalarConverter::convert("2222222222222222222222222222222222222");
	std::cout << "-------------------------" << std::endl;
	ScalarConverter::convert("22222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222");
	std::cout << "-------HERE--------------" << std::endl;
	ScalarConverter::convert("333e12");
	std::cout << "-------------------------" << std::endl;
	ScalarConverter::convert("333e-6");
	std::cout << "-------------------------" << std::endl;
	ScalarConverter::convert("333e12f");
	std::cout << "-------------------------" << std::endl;
	ScalarConverter::convert("333e-2f");
	std::cout << "-------------------------" << std::endl;
	ScalarConverter::convert("inff");
	std::cout << "-------------------------" << std::endl;
	ScalarConverter::convert("inf");
	std::cout << "-------------------------" << std::endl;
	ScalarConverter::convert("nan");
	std::cout << "-------------------------" << std::endl;
	ScalarConverter::convert("nanf");
	std::cout << "-------------------------" << std::endl;
	ScalarConverter::convert("float");
	std::cout << "-------------------------" << std::endl;
	ScalarConverter::convert("double");
	std::cout << "-------------------------" << std::endl;
	return (0);
}