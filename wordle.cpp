#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> result;
    wordleHelper(in, "", floating, dict, result, 0);
    return result;
}

// Define any helper functions here
void wordleHelper(const std::string& in, std::string current, std::string floating, 
                  const std::set<std::string>& dict, std::set<std::string>& result, int pos)
{
    if (pos == in.length())
    {
        if (dict.find(current) != dict.end() && floating.empty())
        {
            result.insert(current);
        }
        return;
    }

    if (in[pos] != '-')
    {
        wordleHelper(in, current + in[pos], floating, dict, result, pos + 1);
    }
    else
    {
        std::set<char> usedFloating;
        for (size_t i = 0; i < floating.size(); i++)
        {
            char c = floating[i];
            if (usedFloating.find(c) != usedFloating.end())
                continue;
            usedFloating.insert(c);
            std::string newFloating = floating;
            newFloating.erase(i, 1);
            wordleHelper(in, current + c, newFloating, dict, result, pos + 1);
        }

        int dashesLeft = 0;
        for (size_t i = pos; i < in.length(); i++)
        {
            if (in[i] == '-') dashesLeft++;
        }

        if (dashesLeft > floating.length())
        {
            for (char c = 'a'; c <= 'z'; c++)
            {
                if (floating.find(c) != std::string::npos)
                    continue;
                wordleHelper(in, current + c, floating, dict, result, pos + 1);
            }
        }
    }
}
