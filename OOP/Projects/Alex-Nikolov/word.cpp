#include <iostream>
#include <cstdlib>
using namespace std;
#include "word.h"
#include "stringstuff.h"

Word::Word (string entry)
{
    setPartOfSpeech(getStringPartOfSpeech(entry));
    setName(getStringName(entry));
    setMeaning(getStringMeaning(entry));
    if (getPartOfSpeech() == "NOUN")
    {
        setDerDieDas(getStringGender(entry));
        setPlural(getStringPlural(entry));
    }
    if (getPartOfSpeech() == "VERB")
        setPastTense(getStringPastTense(entry));
    if (getPartOfSpeech() != "VERB" &&
        getPartOfSpeech() != "NOUN" &&
        getPartOfSpeech() != "ADJ")
        cout << "Error: Entry not recognized.";
}

Word::~Word ()
{

}

void Word::uglyPrint()
{
    if (getPartOfSpeech() == "NOUN")
    {
        cout << getName() << ", " << getPartOfSpeech() << ", "
             << getDerDieDas() << " " << getName() << ", die " << getPlural()
             << ", " << getMeaning() << endl;
    }
    if (getPartOfSpeech() == "VERB")
    {
        cout << getName() << ", " << getPartOfSpeech() << "; "
             << getPastTense() << "; " << getMeaning() << endl;
    }
    if (getPartOfSpeech() == "ADJ")
    {
        cout << getName() << ", " << getPartOfSpeech() << ", "
             << getMeaning() << endl;
    }
}

void Word::print(string a)
{
    if (a == "cls")
        system("cls");
    if (getPartOfSpeech() == "NOUN")
    {
        cout << getDerDieDas() << " " << getName() << ", die " <<
                getPlural() << endl << getMeaning();
    }
    if (getPartOfSpeech() == "VERB")
    {
        cout << getName() << ", " << getPastTense() << endl <<
                getMeaning();
    }
    if (getPartOfSpeech() == "ADJ")
    {
        cout << getName() << endl << getMeaning();
    }
}

string Word::toString () const
{
    string temp;
    if (getPartOfSpeech() == "NOUN")
    {
        temp += getName();
        temp += "*NOUN*";
        temp += getDerDieDas();
        temp += "*";
        temp += getPlural();
        temp += "*";
        temp += getMeaning();
        return temp;
    }
    if (getPartOfSpeech() == "VERB")
    {
        temp += getName();
        temp += "*VERB*";
        temp += getPastTense();
        temp += "*";
        temp += getMeaning();
        return temp;
    }
    if (getPartOfSpeech() == "ADJ")
    {
        temp += getName();
        temp += "*ADJ*";
        temp += getMeaning();
        return temp;
    }
}

