#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include "book.h"
/**
* Namespace for override some functions and operators
*/
namespace ofo//override functions and operators
{
    /**
    * \brief The function like std::to_string for std::vector<T>
    * 
    * Creates std::string for vector. Exsample Size: 3, array: 6, 3, 2 
    * \param array is std::vector with type T that supports function toTheString
    * \return - result of Translation
    */
	template<typename T>
	std::string toTheString(const std::vector<T>& array);
    /**
    * \brief edited name of function std::to_sting 
    *
    * Uses in graph (gm::GraphMatrix and gs::GraphStructure)
    * \param value with type as in std::to_string()
    * \return - result of Translation
    */
	template<typename T>
	std::string toTheString(const T& value);
    /**
    * \brief The function like std::to_string for std::string
    *
    * Uses in graph (gm::GraphMatrix and gs::GraphStructure)
    * \param line is std::string
    * \return - line that is std::string
    */
    template<>
    std::string toTheString(const wm::Event& Event);
    template<>
    std::string toTheString(const std::string& line);
    /**
    * \brief The function like std::to_string for double
    *
    * Removes extra zeros at the end of the number
    * \param value is number
    * \return - result of Translation
    */
    template<>
    std::string toTheString(const double& value);
    /**
    * \brief Append array2 to array1
    *
    * Uses for override operators '+' and '-' for std::vector
    * 
    * Adds all items of 'array2' to 'array1'
    * \param array1 is array to which is added
    * \param array2 is array from which to add
    */
	template<typename T>
	void appendArray(std::vector<T>& array1, const std::vector<T>& array2);
    /**
    * \brief Adding two std::vector
    * 
    * Adds 'array2' to 'array1'
    * \param array1 is first operand
    * \param array2 is second operand
    * \return - result of adding two arrays
    */
	template<typename T>
	std::vector<T> operator + (const std::vector<T>& array1, const std::vector<T>& array2);
    /**
    * \brief Subtraction two std::vector
    *
    * Subtract 'array2' from 'array1'. Subtraction uses the sizes of arrays. 
    * Array items do not matter. 
    * If 'array2' is larger than 'array1' then in result will be empty array
    * \param array1 is first operand
    * \param array2 is second operand
    * \return - result of Subtraction two arrays
    */
    template<typename T>
    std::vector<T> operator - (const std::vector<T>& array1, const std::vector<T>& array2);
    /**
    * \brief Comparison std::vector by sizes
    *
    * Comparison uses the sizes of arrays.
    * Array items do not matter.
    * \param array1 is first operand
    * \param array2 is second operand
    * \return - true if 'array1' < 'array2'
    * \return - false if 'array1' >= 'array2'
    */
	template<typename T>
	bool operator < (const std::vector<T>& array1, const std::vector<T>& array2);
    /**
    * \brief Comparison std::vector by sizes
    *
    * Comparison uses the sizes of arrays.
    * Array items do not matter
    * \param array1 is first operand
    * \param array2 is second operand
    * \return - true if 'array1' <= 'array2'
    * \return - false if 'array1' > 'array2'
    */
	template<typename T>
	bool operator <= (const std::vector<T>& array1, const std::vector<T>& array2);
    /**
    * \brief Comparison std::vector by sizes
    *
    * Comparison uses the sizes of arrays.
    * Array items do not matter
    * \param array1 is first operand
    * \param array2 is second operand
    * \return - true if 'array1' > 'array2'
    * \return - false if 'array1' <= 'array2'
    */
	template<typename T>
	bool operator > (const std::vector<T>& array1, const std::vector<T>& array2);
    /**
    * \brief Comparison std::vector by sizes
    *
    * Comparison uses the sizes of arrays.
    * Array items do not matter
    * \param array1 is first operand
    * \param array2 is second operand
    * \return - true if 'array1' >= 'array2'
    * \return - false if 'array1' < 'array2'
    */
	template<typename T>
	bool operator >= (const std::vector<T>& array1, const std::vector<T>& array2);
    /**
    * \brief Comparison std::vector by sizes
    *
    * Comparison uses the sizes of arrays.
    * Array items do not matter
    * \param array1 is first operand
    * \param array2 is second operand
    * \return - true if 'array1' == 'array2'
    * \return - false if 'array1' != 'array2'
    */
	template<typename T>
	bool operator == (const std::vector<T>& array1, const std::vector<T>& array2);
    /**
    * \brief Comparison std::vector by sizes
    *
    * Comparison uses the sizes of arrays.
    * Array items do not matter
    * \param array1 is first operand
    * \param array2 is second operand
    * \return - true if 'array1' != 'array2'
    * \return - false if 'array1' == 'array2'
    */
    template<typename T>
    bool operator != (const std::vector<T>& array1, const std::vector<T>& array2);
    /**
    * \brief Subtraction two std::string
    *
    * Subtract 'line2' from 'line1' if 'line2' is in 'line1' 
    * else result will be 'line1'
    * \param line1 is first operand
    * \param line2 is second operand
    * \return - result of Subtraction two lines
    */
    std::string operator - (const std::string& line1, const std::string& line2);
    /**
    * \brief Function for creating random value
    * 
    * Uses in graph (gm::GraphMatrix and gs::GraphStructure)
    * \param maxValue is the maximum value that a value can take
    * \return - random value
    */
    template<typename T>
    T randomValue(const T& maxValue);
    /**
    * \brief Function for creating random double value
    * 
    * Uses in graph (gm::GraphMatrix and gs::GraphStructure)
    * \param maxValue is the maximum value that a double value can take
    * \return - random double value
    */
    template<>
    double randomValue(const double& maxValue);
    /**
    * \brief Function for creating random std::string value
    *
    * Uses in graph (gm::GraphMatrix and gs::GraphStructure)
    * \param maxValue is line with the maximum size that a random line can take
    * \return - random line
    */
    template<>
    std::string randomValue(const std::string& maxValue);
    /**
    * \brief Function for creating random std::vector value
    *
    * Uses in graph (gm::GraphMatrix and gs::GraphStructure)
    * \param maxValue is array with the maximum size that a random array can take
    * \return - random array
    */
    template<typename T>
    std::vector<T> randomValue(const std::vector<T>& maxValue);
 }
namespace ofo
{
    template<typename T>
    std::string toTheString(const std::vector<T>& array)
    {
        std::string result = "";
        result += "Size: " + std::to_string(array.size()) + ", array: ";
        for (std::size_t i = 0; i < array.size(); i++) result += toTheString(array[i]) + " ";

        return result;
    }
    template<>
    std::string toTheString(const wm::Event& Event)
    {
        return Event.getName();
    }
    template<>
    std::string toTheString(const std::string& line)
    {
        return line;
    }
    template<>
    std::string toTheString(const double& value)
    {
        std::string line = std::to_string(value);
        while(true)
        {
            if (line.size() == 1) break;
            if (line[line.size() - 1] == '0') line.erase(line.size() - 1, 1);
            else if (line[line.size() - 1] == '.') line.erase(line.size() - 1, 1);
            else break;
        }

        return line;
    }
    template<typename T>
    std::string toTheString(const T& value)
    {
        return std::to_string(value);
    }
    template<typename T>
    void appendArray(std::vector<T>& array1, const std::vector<T>& array2)
    {
        for (std::size_t i = 0; i < array2.size(); i++) array1.push_back(array2[i]);
    }
    template<typename T>
    std::vector<T> operator + (const std::vector<T>& array1, const std::vector<T>& array2)
    {
        std::vector<T> array3 = array1;
        appendArray(array3, array2);
        return array3;
    }
    template<typename T>
    std::vector<T> operator - (const std::vector<T>& array1, const std::vector<T>& array2)
    {
        std::vector<T> array3;
        std::size_t size1 = array1.size(), size2 = array2.size();
        if (size2 >= size1) return array3;
        std::size_t newSize = size1 - size2;
        appendArray(array3, array1);
        array3.erase(array3.begin() + newSize, array3.end());

        return array3;
    }    
    template<typename T>
    bool operator < (const std::vector<T>& array1, const std::vector<T>& array2)
    {
        return (array1.size() < array2.size());
    }
    template<typename T>
    bool operator <= (const std::vector<T>& array1, const std::vector<T>& array2)
    {
        return (array1.size() <= array2.size());
    }
    template<typename T>
    bool operator > (const std::vector<T>& array1, const std::vector<T>& array2)
    {
        return (array1.size() > array2.size());
    }
    template<typename T>
    bool operator >= (const std::vector<T>& array1, const std::vector<T>& array2)
    {
        return (array1.size() >= array2.size());
    }
    template<typename T>
    bool operator == (const std::vector<T>& array1, const std::vector<T>& array2)
    {
        if (array1.size() != array2.size()) return false;
        for (std::size_t i = 0; i < array1.size(); i++)
        {
            if (array1[i] != array2[i]) return false;
        }

        return true;
    }
    template<typename T>
    bool operator != (const std::vector<T>& array1, const std::vector<T>& array2)
    {
        if (array1.size() != array2.size()) return true;
        for (std::size_t i = 0; i < array1.size(); i++)
        {
            if (array1[i] != array2[i]) return true;
        }

        return false;
    }
    std::string operator - (const std::string& line1, const std::string& line2)
    {
        std::string line3;     
        std::size_t index = line1.find(line2, 0);
        if (index + 1 == 0) return line1;
        line3 = line1;
        line3.erase(index, line2.size());

        return line3;
    } 
    template<typename T>
    T randomValue(const T& maxValue)
    {
        return rand() % (maxValue + 1);
    }
    template<>
    double randomValue(const double& maxValue)
    {
        return (double)(rand())/RAND_MAX * maxValue;
    }
    template<>
    std::string randomValue(const std::string& maxValue)
    {
        std::size_t size = rand() % (maxValue.size() + 1);
        std::string line = "";
        for (std::size_t i = 0; i < size; i++)
        {
            line+= 'a' + (rand() % 26);
        }
        return line;
    }
    template<typename T>
    std::vector<T> randomValue(const std::vector<T>& maxValue)
    {
        std::vector<T> array;
        std::size_t size = rand() % (maxValue.size() + 1);
        for (std::size_t i = 0; i < size; i++)
        {
            array.push_back(rand() % (abs(maxValue[i]) + 1));
        }

        return array;
    }
}
