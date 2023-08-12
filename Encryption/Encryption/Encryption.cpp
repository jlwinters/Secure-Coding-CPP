// Encryption.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <ctime>

/// <summary>
/// encrypt or decrypt a source string using the provided key
/// </summary>
/// <param name="source">input string to process</param>
/// <param name="key">key to use in encryption / decryption</param>
/// <returns>transformed string</returns>
std::string encrypt_decrypt(const std::string& source, const std::string& key)
{
    // get lengths now instead of calling the function every time.
    // this would have most likely been inlined by the compiler, but design for perfomance.
    const auto key_length = key.length();
    const auto source_length = source.length();

    // assert that our input data is good
    assert(key_length > 0);
    assert(source_length > 0);

    std::string output = source;

    // loop through the source string char by char
    for (size_t i = 0; i < source_length; ++i)
    {
      // transform each character based on an xor of the key modded constrained to key length using a mod
        output[i] = source[i] ^ key[i % key_length];
    }

    // our output length must equal our source length
    assert(output.length() == source_length);

    // return the transformed string
    return output;
}

std::string read_file(const std::string& filename)
{
    std::string file_text;

    try
    {
        std::ifstream readFile(filename, std::ios::in | std::ios::binary);
        if (readFile)
        {
            // Seek to the end of the file to get its size
            readFile.seekg(0, std::ios::end);
            std::streamsize file_size = readFile.tellg();
            readFile.seekg(0, std::ios::beg);

            // Resize the file_text string to accommodate the file's content
            file_text.resize(static_cast<size_t>(file_size));

            // Read the entire file into the file_text string
            if (readFile.read(&file_text[0], file_size))
            {
                // File reading successful
                readFile.close();
                return file_text;
            }
        }
        else
        {
            // Failed to open the file
            std::cout << "Failed to open file: " << filename << std::endl;
        }
    }
    catch (const std::exception& e)
    {
        // Exception occurred during file reading
        std::cout << "Failed to read file: " << e.what() << std::endl;
    }

    return std::string(); // Return an empty string in case of failure
}

std::string get_student_name(const std::string& string_data)
{
    std::string student_name;

    // find the first newline
    size_t pos = string_data.find('\n');
    // did we find a newline
    if (pos != std::string::npos)
    { // we did, so copy that substring as the student name
        student_name = string_data.substr(0, pos);
    }

    return student_name;
}

void save_data_file(const std::string& filename, const std::string& student_name, const std::string& key, const std::string& data)
{
    try
    {
        std::ofstream writeFile(filename, std::ios::out);
        if (writeFile)
        {
            // Write Student Name
            writeFile << student_name << std::endl;

            // Get the current timestamp
            std::time_t now = std::time(nullptr);
            std::tm localTime;
            localtime_s(&localTime, &now);

            // Write timestamp (yyyy-mm-dd)
            char buffer[80];
            std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &localTime);
            writeFile << buffer << std::endl;

            // Write key
            writeFile << key << std::endl;

            // Write data
            writeFile << data << std::endl;

            // Close file
            writeFile.close();
        }
        else
        {
            // Failed to open the file
            std::cout << "Failed to open file: " << filename << std::endl;
        }
    }
    catch (const std::exception& e)
    {
        // Exception occurred during file writing
        std::cout << "Failed to write file: " << e.what() << std::endl;
    }
}

int main()
{
    std::cout << "Encyption Decryption Test!" << std::endl;

    // input file format
    // Line 1: <students name>
    // Line 2: <Lorem Ipsum Generator website used> https://pirateipsum.me/ (could be https://www.lipsum.com/ or one of https://www.shopify.com/partners/blog/79940998-15-funny-lorem-ipsum-generators-to-shake-up-your-design-mockups)
    // Lines 3+: <lorem ipsum generated with 3 paragraphs> 
    //  Fire in the hole bowsprit Jack Tar gally holystone sloop grog heave to grapple Sea Legs. Gally hearties case shot crimp spirits pillage galleon chase guns skysail yo-ho-ho. Jury mast coxswain measured fer yer chains man-of-war Privateer yardarm aft handsomely Jolly Roger mutiny.
    //  Hulk coffer doubloon Shiver me timbers long clothes skysail Nelsons folly reef sails Jack Tar Davy Jones' Locker. Splice the main brace ye fathom me bilge water walk the plank bowsprit gun Blimey wench. Parrel Gold Road clap of thunder Shiver me timbers hempen halter yardarm grapple wench bilged on her anchor American Main.
    //  Brigantine coxswain interloper jolly boat heave down cutlass crow's nest wherry dance the hempen jig spirits. Interloper Sea Legs plunder shrouds knave sloop run a shot across the bow Jack Ketch mutiny barkadeer. Heave to gun matey Arr draft jolly boat marooned Cat o'nine tails topsail Blimey.

    const std::string file_name = "inputdatafile.txt";
    const std::string encrypted_file_name = "encrypteddatafile.txt";
    const std::string decrypted_file_name = "decrypteddatafile.txt";

    // Read the content of the data file
    const std::string source_string = read_file(file_name);

    // Get the student name from the data file
    const std::string student_name = get_student_name(source_string);

    // Encrypt source_string with the specified key
    const std::string key = "password";
    const std::string encrypted_string = encrypt_decrypt(source_string, key);

    // Save the encrypted string to a file
    save_data_file(encrypted_file_name, student_name, key, encrypted_string);

    // Decrypt the encrypted_string using the same key
    const std::string decrypted_string = encrypt_decrypt(encrypted_string, key);

    // Save the decrypted string to a file
    save_data_file(decrypted_file_name, student_name, key, decrypted_string);

    // Output the file names for reference
    std::cout << "Reading file: " << file_name << "\n" << "Encrypted file output: " << encrypted_file_name << "\n" << "Decrypted file output: " << decrypted_file_name << std::endl;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
