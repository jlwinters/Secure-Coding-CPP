// Exceptions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdexcept>

// Custom exception derived from std::exception
class CustomException : public std::exception
{
public:
    const char* what() const noexcept override
    {
        return "Custom Exception";
    }
};

bool do_even_more_custom_application_logic()
{

    std::cout << "Running Even More Custom Application Logic." << std::endl;

    throw std::exception("Standard Exception"); // Throw a standard exception

    return true;
}
void do_custom_application_logic()
{
    std::cout << "Running Custom Application Logic." << std::endl;

    try
    {
        // Wrap the call to do_even_more_custom_application_logic() with an exception handler
        do_even_more_custom_application_logic();
        std::cout << "Even More Custom Application Logic Succeeded." << std::endl;
    }
    catch (const std::exception& e)
    {
        // Catch std::exception, display a message and the exception.what()
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    // Throw a custom exception derived from std::exception
    throw CustomException();

    std::cout << "Leaving Custom Application Logic." << std::endl;
}

float divide(float num, float den)
{
    if (den == 0) // Check if the denominator is zero
    {
        throw std::runtime_error("Divide by zero error"); // Throw an exception if it is
    }
    return (num / den);
}

void do_division() noexcept
{
    try
    {
        // Create an exception handler to capture ONLY the exception thrown by divide
        float numerator = 10.0f;
        float denominator = 0;

        auto result = divide(numerator, denominator);
        std::cout << "divide(" << numerator << ", " << denominator << ") = " << result << std::endl;
    }
    catch (const std::runtime_error& e)
    {
        // Catch std::runtime_error specifically
        std::cerr << "Exception Caught: " << e.what() << std::endl;
    }
}

int main()
{
    std::cout << "Exceptions Tests!" << std::endl;

    try
    {
        do_division();
        do_custom_application_logic();
    }
    // Custom exception handler
    catch (const CustomException& e1)
    {
        // Catch the custom exception explicitly in main
        std::cout << "Custom Exception Caught: " << e1.what() << std::endl;
    }
    // Standard exception handler
    catch (const std::exception& e2)
    {
        std::cout << "Standard Exception Caught: " << e2.what() << std::endl;
    }
    // Uncaught exception handler
    catch (...)
    {
        std::cout << "Unexpected Exception Caught" << std::endl;
    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
