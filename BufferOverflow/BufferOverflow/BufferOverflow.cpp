// BufferOverflow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iomanip>
#include <iostream>

int main()
{
  std::cout << "Buffer Overflow Example" << std::endl;

  // Define the maximum buffer size
  const int MAX_BUFFER_SIZE = 20;

  const std::string account_number = "CharlieBrown42";

  // Buffer for user input
  char user_input[20];

  // Reads the first 20 characters
  std::cout << "Enter a value: ";
  std::cin.getline(user_input, MAX_BUFFER_SIZE);

  std::cout << "You entered: " << user_input << std::endl;
  std::cout << "Account Number = " << account_number << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
