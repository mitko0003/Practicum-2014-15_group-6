#include <iostream>
using namespace std;

#include "stringstuff.h"

void helperMeaning(int i, int countingStars, int someNumber, string a, string& helper)
{
    for (i; i < a.size(); i++)
    {
        if (a[i] == '*')
            countingStars++;
        if (countingStars == someNumber)
            break;
    }
    i++;
    for (i; i < a.size(); i++)
    {
        helper += a[i];
    }
}

string getStringGender(string a)
{
    int countingStars = 0;
    for (unsigned int i = 0; i < a.size(); i++)
    {
        if (a[i] == '*')
        {
            countingStars++;
        }
        if (countingStars == 2)
        {
            int copyI = i;
            char gender = a[copyI + 2];
            switch (gender)
            {
                case 'e':
                    return "der";
                    break;
                case 'i':
                    return "die";
                    break;
                case 'a':
                    return "das";
                    break;
            }
        }
    }
}

string getStringPlural(string a)
{
    int countingStars = 0;
    unsigned int i = 0;
    for (i; i < a.size(); i++)
    {
        if (a[i] == '*')
        {
            countingStars++;
        }
        if (countingStars == 3)
        {
            i++;
            break;
        }
    }
    string helper;
    while (a[i] != '*')
    {
        helper += a[i];
        i++;
    }
    return helper;
}

string getStringPastTense(string a)
{
    int countingStars = 0;
    unsigned int i = 0;
    for (i; i < a.size(); i++)
    {
        if (a[i] == '*')
        {
            countingStars++;
        }
        if (countingStars == 2)
        {
            i++;
            break;
        }
    }
    string helper;
    while (a[i] != '*')
    {
        helper += a[i];
        i++;
    }
    return helper;
}


string getStringMeaning(string a)
{
    unsigned int i = 0;
    for (i; i < a.size(); i++)
    {
        if (a[i] == '*')
            break;
    }
    i++;
    int countingStars = 0;
    string helper;
    switch (a[i])
    {
        case 'N':
            helperMeaning(i, countingStars, 3, a, helper);
            return helper;
        case 'V':
            helperMeaning(i, countingStars, 2, a, helper);
            return helper;
        case 'A':
            helperMeaning(i, countingStars, 1, a, helper);
            return helper;
    }
}

string getStringName(string a)
{
    unsigned int i = 0;
    string helper;
    for (i; i < a.size(); i++)
    {
        if (a[i] != '*')
            helper += a[i];
        if (a[i] == '*')
            break;
    }
    return helper;
}

string getStringPartOfSpeech(string a)
{
    unsigned int i = 0;
    string helper;
    int countingStars = 0;
    for (i; i < a.size(); i++)
    {
        if (a[i] == '*')
            countingStars++;
        if (countingStars == 1)
            break;
    }
    i++;
    if (a[i] == 'A')
        return "ADJ";
    if (a[i] == 'N')
        return "NOUN";
    if (a[i] == 'V')
        return "VERB";
}


bool containsMeaning(string bigMeaning, string smallMeaning)
{
    if (bigMeaning.size() < smallMeaning.size())
        return false;
    unsigned int smallCounter = 0;
    unsigned int matchBeginning = 0;
    unsigned int matchEnd = 0;
    for (unsigned int i = 0; i < bigMeaning.size() - smallMeaning.size() + 1; i++)
    {
        smallCounter = 0;
        if (bigMeaning[i] == smallMeaning[0])
        {
            matchBeginning = i;
            for (unsigned int j = i; j < i + smallMeaning.size(); j++)
            {
                if (bigMeaning[j] != smallMeaning[smallCounter])
                {
                    break;
                }
                else
                {
                    matchEnd = j;
                    smallCounter++;
                }
            }
            if ((smallCounter == smallMeaning.size())
            && (matchBeginning == 0 || (bigMeaning[matchBeginning - 1] == ' ' && bigMeaning[matchBeginning - 2] == ','))
            && (bigMeaning[matchEnd + 1] == '\0' || (bigMeaning[matchEnd + 1] == ' ' && bigMeaning[matchEnd + 2] == '(') || bigMeaning[matchEnd + 1] == ','))
                return true;
        }
    }
    return false;
}

int numberOfMeanings(string meaning)
{
    bool inWord = false;
    int counter = 0;
    bool withinParentheses = false;
    for (unsigned int i = 0; i < meaning.size(); i++)
    {
        if (meaning[i] == '(')
        {
            withinParentheses = true;
            continue;
        }
        if (meaning[i] == ')')
        {
            withinParentheses = false;
            continue;
        }
        if (meaning[i] == ',' && !withinParentheses)
        {
            counter++;
            continue;
        }
    }
    return counter+1;
}

string polishString(string meaning)
{
    string helper;
    string tempWord;
    int wordCounter = 0;
    bool inWord = false;
    bool withinParentheses = false;
    bool shouldIWriteWithinParethesis = false;
    for (unsigned int i = 0; i < meaning.size(); i++)
    {
        if (meaning[i] == '(')
        {
            if (isalpha(meaning[i - 2]))
            {
                tempWord += " ";
                tempWord += meaning[i];
                shouldIWriteWithinParethesis = true;
            }
            withinParentheses = true;
            continue;
        }
        if (meaning[i] == ')')
        {
            if (shouldIWriteWithinParethesis)
            {
                tempWord += meaning[i];
                helper += tempWord;
                tempWord = "";
            }
            withinParentheses = false;
        }
        if (withinParentheses && shouldIWriteWithinParethesis)
        {
            tempWord += meaning[i];
        }
        if (isalpha(meaning[i]) && !inWord && !withinParentheses)
        {
            inWord = true;
            tempWord += meaning[i];
            continue;
        }
        if (isalpha(meaning[i]) && inWord && i != meaning.size() - 1 && !withinParentheses)
        {
            tempWord += meaning[i];
            continue;
        }
        if ((!isalpha(meaning[i]) && inWord) || (isalpha(meaning[i]) && i == meaning.size() - 1) && !withinParentheses)
        {
            if (wordCounter > 0 && !isalpha(meaning[i]) && inWord && !withinParentheses)
            {
                inWord = false;
                helper += ", ";
                helper += tempWord;
                tempWord = "";
                continue;
            }
            if (wordCounter == 0 && !isalpha(meaning[i]) && inWord && !withinParentheses)
            {
                inWord = false;
                helper += tempWord;
                tempWord = "";
                wordCounter++;
                continue;
            }
            if (wordCounter > 0 && isalpha(meaning[i]) && i == meaning.size() - 1 && !withinParentheses)
            {
                helper += ", ";
                tempWord += meaning[i];
                helper += tempWord;
                tempWord = "";
                continue;
            }
            if (wordCounter == 0 && isalpha(meaning[i]) && i == meaning.size() - 1 && !withinParentheses)
            {
                tempWord += meaning[i];
                helper += tempWord;
                tempWord = "";
                wordCounter++;
                continue;
            }
        }
    }
    return helper;
}
