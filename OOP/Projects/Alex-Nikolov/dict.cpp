#include <iostream>
#include <fstream>
#include <cstdlib>
#include "word.h"
#include "dict.h"
using namespace std;

Dictionary::Dictionary(const char* fileName)
{
    ifstream file(fileName);
    string line;
    while (getline (file, line))
    {
        Word tempWord(line);
        dict.push_back(tempWord);
    }
    for (int i = 0; i < dict.size() - 1; i++)
    {
        for (int j = i + 1; j < dict.size(); j++)
        {
            if (dict[i].getName() == dict[j].getName())
            {
                cout << "Error: Two entries with the same name " << dict[i].getName() << endl;
                system("pause");
            }
        }
    }
}

int Dictionary::getSize() const
{
    return dict.size();
}

Word Dictionary::getWord(int number) const
{
    return dict[number];
}

void Dictionary::addEntry(Word newWord)
{
    dict.push_back(newWord);
}

void Dictionary::editName(int number, string edit)
{
    dict[number].setName(edit);
}

void Dictionary::editDerDieDas(int number, string edit)
{
    dict[number].setDerDieDas(edit);
}

void Dictionary::editPlural(int number, string edit)
{
    dict[number].setPlural(edit);
}

void Dictionary::editMeaning(int number, string edit)
{
    dict[number].setMeaning(edit);
}

void Dictionary::editPartOfSpeech(int number, string edit)
{
    dict[number].setPartOfSpeech(edit);
}

void Dictionary::editPastTense(int number, string edit)
{
    dict[number].setPastTense(edit);
}

bool Dictionary::doesContain(string wordName, int& number)
{
    for (int i = 0; i < getSize(); i++)
    {
        if (dict[i].getName() == wordName)
        {
            number = i;
            return true;
        }
    }
    return false;
}

string Dictionary::toString() const
{
    string helper;
    for (int i = 0; i < getSize(); i++)
    {
        helper += dict[i].toString();
        helper += '\n';
    }
    return helper;
}

void Dictionary::eraseEntry(int number)
{
    dict.erase(dict.begin() + number);
}

