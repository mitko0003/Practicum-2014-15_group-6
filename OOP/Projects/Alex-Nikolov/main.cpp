#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <ctime>

#include "stringstuff.h"
#include "word.h"
#include "dict.h"

using namespace std;

const string CLS = "cls";
const string EMPTY = "";
const char* FAVORITES = "favorites.txt";
const char* WORDS = "words.txt";
const char* NOUNS = "nouns.txt";
const char* VERBS = "verbs.txt";

Dictionary myDict(WORDS);
Dictionary favDict(FAVORITES);
Dictionary myNouns(NOUNS);
Dictionary myVerbs(VERBS);

void writeToFile(const Dictionary&, const char*);
void getChoice(string&, string);
void checkOption();
void input(string);
void google(const char*);
void edit();
void googleByMeaning();
void addToFavorites();
void deleteEntry(const char*);
void helperGoogle(const Dictionary&, string);
bool helperDelete(Dictionary&, const char*, string);
void testMeaning(Dictionary, const char*);
void writeToFileApp(const char*, string);
void testNouns();
void testVerbs();

int main ()
{
    system("title Dictionary 2.0 Main menu");
    system("cls");
    cout << "Press 1 to add an entry to the database." << endl <<
            "Press 2 to search for an entry in the database." << endl <<
            "Press 3 to edit an entry." << endl <<
            "Press 4 to delete entry from dictionary." << endl <<
            "Press 5 to view words that share meaning." << endl <<
            "Press 6 to add an existing entry to favorites." << endl <<
            "Press 7 to search for an entry in favorites." << endl <<
            "Press 8 to delete an existing entry in favorites." << endl <<
            "Press 9 to test your knowledge on word meanings." << endl <<
            "Press 10 to test your knowledge on your favorite words." << endl <<
            "Press 11 to test your knowledge on nouns." << endl <<
            "Press 12 to test your knowledge on verbs." << endl;
    int option;
    cin >> option;
    cin.ignore();
    switch (option)
    {
        case 1:
            input(EMPTY);
            break;
        case 2:
            google(WORDS);
            break;
        case 3:
            edit();
            break;
        case 4:
            deleteEntry(WORDS);
            break;
        case 5:
            googleByMeaning();
            break;
        case 6:
            addToFavorites();
            break;
        case 7:
            google(FAVORITES);
            break;
        case 8:
            deleteEntry(FAVORITES);
            break;
        case 9:
            testMeaning(myDict, WORDS);
            break;
        case 10:
            testMeaning(favDict, FAVORITES);
            break;
        case 11:
            testNouns();
            break;
        case 12:
            testVerbs();
            break;
    }
}

void checkOption()
{
    string option;
    getline (cin, option);
    if (option == "0")
        main ();
    else
    {
        cout << endl;
        while (option != "0")
        {
            cout << "Invalid input, please press 0 to go back to the main menu. ";
            getline (cin, option);
        }
        if (option == "0")
            main();
    }
}

void writeToFileApp(const char* fileName, string newEntry)
{
    ofstream file(fileName, ios::app);
    if (file.is_open())
        file << newEntry;
    file.close();
}

void input(string a)
{
    system("title Dictionary 2.0 Adding new entry");
    system("cls");
    string newEntry;
    string name;
    if (a == EMPTY)
    {
        cout << "Enter new word: ";
        getline (cin, name);
    }
    if (a != EMPTY)
        newEntry = a;
    for (int i = 0; i < myDict.getSize(); i++)
    {
        if (myDict.getWord(i).getName() == name)
        {
            cout << endl << "Error: Entry already exists. " <<
                    "Press 0 to go back to the main menu. ";
            checkOption();
        }
    }
    newEntry += name;
    newEntry += "*";
    string pos;
    cout << "Enter part of speech: ";
    getline (cin, pos);
    newEntry += pos;
    newEntry += "*";
    if (pos == "NOUN")
    {
        string ddd;
        cout << "Enter gender: ";
        getline (cin, ddd);
        newEntry += ddd;
        newEntry += "*";
        string pl;
        cout << "Enter plural: ";
        getline (cin, pl);
        newEntry += pl;
        newEntry += "*";
    }
    if (pos == "VERB")
    {
        string pt;
        cout << "Enter past tense: ";
        getline (cin, pt);
        newEntry += pt;
        newEntry += "*";
    }
    string m;
    cout << "Enter meaning: ";
    getline (cin, m);
    newEntry += m;
    newEntry += '\n';
    Word newWord (newEntry);
    writeToFileApp(WORDS, newEntry);
    if (newWord.getPartOfSpeech() == "NOUN")
    {
        writeToFileApp(NOUNS, newEntry);
    }
    if (newWord.getPartOfSpeech() == "VERB")
    {
        writeToFileApp(VERBS, newEntry);
    }
    myDict.addEntry(newWord);
    cout << endl << "Entry successfully added. Press 0 to return to the main menu. ";
    char option;
    cin >> option;
    if (option == '0')
        main();
}

void helperGoogle(const Dictionary& whichDict, string wantedEntry)
{
    for (int i = 0; i < whichDict.getSize(); i++)
    {
        if (whichDict.getWord(i).getName() == wantedEntry)
        {
            whichDict.getWord(i).print(CLS);
            cout << endl << endl << "Press 0 to go back to the main menu. ";
            checkOption();
        }
    }
}

void google(const char* fileName)
{
    if (fileName == WORDS)
        system("title Dictionary 2.0 Search for an entry");
    if (fileName == FAVORITES)
        system("title Dictionary 2.0 Search for an entry in favorites");
    system("cls");
    cout << "What are you looking for? ";
    string wantedEntry;
    getline (cin, wantedEntry);
    if (fileName == WORDS)
    {
        helperGoogle(myDict, wantedEntry);
        cout << endl << "Entry not found. " << endl <<
             "Press 0 if to go back to the main menu or press 'y' to add the entry. ";
        string option;
        getline(cin, option);
        if (option == "0")
            main ();
        if (option == "y")
            input(wantedEntry);
        else
        {
            cout << endl;
            while (option != "0" && option != "y")
            {
                cout << "Invalid input, please press 'y' if you would like to add " << wantedEntry <<
                        " to the dictionary or press 0 to go back to the main menu. ";
                getline (cin, option);
            }
            if (option == "0")
                main();
            if (option == "y")
                input(wantedEntry);
        }
    }
    if (fileName == FAVORITES)
    {
        helperGoogle(favDict, wantedEntry);
        cout << endl << "Entry not found. Press 0 to go back to the main menu. ";
        checkOption();
    }
}

void edit()
{
    system("title Dictionary 2.0 Edit an entry");
    system("cls");
    cout << "Which word would you like to edit? ";
    string wantedEntry;
    getline (cin, wantedEntry);
    for (int i = 0; i < myDict.getSize(); i++)
    {
        if (myDict.getWord(i).getName() == wantedEntry)
        {
            myDict.getWord(i).print(CLS);
            cout << endl << endl;
            if (myDict.getWord(i).getPartOfSpeech() == "NOUN")
            {
                cout << "Press 1 to edit the name." << endl <<
                        "Press 2 to edit the part of speech." << endl <<
                        "Press 3 to edit the gender." << endl <<
                        "Press 4 to edit the plural form." << endl <<
                        "Press 5 to edit the meaning." << endl;
                char option;
                cin >> option;
                cin.ignore();
                string edit;
                system("cls");
                int pos;
                switch (option)
                {
                    case '1':
                        cout << "Old name: " << myDict.getWord(i).getName() << endl;
                        getChoice(edit, "name");
                        myDict.editName(i, edit);
                        if (favDict.doesContain(wantedEntry, pos))
                        {
                            favDict.editName(pos, edit);
                            writeToFile(favDict, FAVORITES);
                        }
                        if (myNouns.doesContain(wantedEntry, pos))
                        {
                            myNouns.editName(pos, edit);
                            writeToFile(myNouns, NOUNS);
                        }
                        break;
                    case '2':
                        cout << "Old part of speech: " << myDict.getWord(i).getPartOfSpeech() << endl;
                        getChoice(edit, "part of speech");
                        myDict.editPartOfSpeech(i, edit);
                        if (favDict.doesContain(wantedEntry, pos))
                        {
                            favDict.editPartOfSpeech(pos, edit);
                            writeToFile(favDict, FAVORITES);
                        }
                        if (myNouns.doesContain(wantedEntry, pos))
                        {
                            myNouns.editPartOfSpeech(pos, edit);
                            writeToFile(myNouns, NOUNS);
                        }
                        break;
                    case '3':
                        cout << "Old gender: " << myDict.getWord(i).getDerDieDas() << endl;
                        getChoice(edit, "gender");
                        myDict.editDerDieDas(i, edit);
                        if (favDict.doesContain(wantedEntry, pos))
                        {
                            favDict.editDerDieDas(pos, edit);
                            writeToFile(favDict, FAVORITES);
                        }
                        if (myNouns.doesContain(wantedEntry, pos))
                        {
                            myNouns.editDerDieDas(pos, edit);
                            writeToFile(myNouns, NOUNS);
                        }
                        break;
                    case '4':
                        cout << "Old plural form: " << myDict.getWord(i).getPlural() << endl;
                        getChoice(edit, "plural form");
                        myDict.editPlural(i, edit);
                        if (favDict.doesContain(wantedEntry, pos))
                        {
                            favDict.editPlural(pos, edit);
                            writeToFile(favDict, FAVORITES);
                        }
                        if (myNouns.doesContain(wantedEntry, pos))
                        {
                            myNouns.editPlural(pos, edit);
                            writeToFile(myNouns, NOUNS);
                        }
                        break;
                    case '5':
                        cout << "Old meaning: " << myDict.getWord(i).getMeaning() << endl;
                        getChoice(edit, "meaning");
                        myDict.editMeaning(i, edit);
                        if (favDict.doesContain(wantedEntry, pos))
                        {
                            favDict.editMeaning(pos, edit);
                            writeToFile(favDict, FAVORITES);
                        }
                        if (myNouns.doesContain(wantedEntry, pos))
                        {
                            myNouns.editMeaning(pos, edit);
                            writeToFile(myNouns, NOUNS);
                        }
                        break;
                }
                writeToFile(myDict, WORDS);
                cout << endl << "Edit successful. Press 0 go to back to the main menu. ";
                checkOption();
            }
            if (myDict.getWord(i).getPartOfSpeech() == "VERB")
            {
                cout << "Press 1 to edit the name." << endl <<
                        "Press 2 to edit the part of speech." << endl <<
                        "Press 3 to edit the past tense." << endl <<
                        "Press 4 to edit the meaning." << endl;
                char option;
                cin >> option;
                cin.ignore();
                string edit;
                system("cls");
                int pos;
                switch (option)
                {
                    case '1':
                        cout << "Old name: " << myDict.getWord(i).getName() << endl;
                        getChoice(edit, "name");
                        myDict.editName(i, edit);
                        if (favDict.doesContain(wantedEntry, pos))
                        {
                            favDict.editName(pos, edit);
                            writeToFile(favDict, FAVORITES);
                        }
                        if (myVerbs.doesContain(wantedEntry, pos))
                        {
                            myVerbs.editName(pos, edit);
                            writeToFile(myVerbs, VERBS);
                        }
                        break;
                    case '2':
                        cout << "Old part of speech: " << myDict.getWord(i).getPartOfSpeech() << endl;
                        getChoice(edit, "part of speech");
                        myDict.editPartOfSpeech(i, edit);
                        if (favDict.doesContain(wantedEntry, pos))
                        {
                            favDict.editPartOfSpeech(pos, edit);
                            writeToFile(favDict, FAVORITES);
                        }
                        if (myVerbs.doesContain(wantedEntry, pos))
                        {
                            myVerbs.editPartOfSpeech(pos, edit);
                            writeToFile(myVerbs, VERBS);
                        }
                        break;
                    case '3':
                        cout << "Old past tense: " << myDict.getWord(i).getPastTense() << endl;
                        getChoice(edit, "past tense");
                        myDict.editPastTense(i, edit);
                        if (favDict.doesContain(wantedEntry, pos))
                        {
                            favDict.editPastTense(pos, edit);
                            writeToFile(favDict, FAVORITES);
                        }
                        if (myVerbs.doesContain(wantedEntry, pos))
                        {
                            myVerbs.editPastTense(pos, edit);
                            writeToFile(myVerbs, VERBS);
                        }
                        break;
                    case '4':
                        cout << "Old meaning: " << myDict.getWord(i).getMeaning() << endl;
                        getChoice(edit, "meaning");
                        myDict.editMeaning(i, edit);
                        if (favDict.doesContain(wantedEntry, pos))
                        {
                            favDict.editMeaning(pos, edit);
                            writeToFile(favDict, FAVORITES);
                        }
                        if (myVerbs.doesContain(wantedEntry, pos))
                        {
                            myVerbs.editMeaning(pos, edit);
                            writeToFile(myVerbs, VERBS);
                        }
                        break;
                }
                writeToFile(myDict, WORDS);
                cout << endl << "Edit successful. Press 0 go to back to the main menu. ";
                checkOption();
            }
            if (myDict.getWord(i).getPartOfSpeech() == "ADJ")
            {
                cout << "Press 1 to edit the name." << endl <<
                        "Press 2 to edit the part of speech." << endl <<
                        "Press 3 to edit the meaning." << endl;
                char option;
                cin >> option;
                cin.ignore();
                string edit;
                system("cls");
                int pos;
                switch (option)
                {
                    case '1':
                        cout << "Old name: " << myDict.getWord(i).getName() << endl;
                        getChoice(edit, "name");
                        myDict.editName(i, edit);
                        if (favDict.doesContain(wantedEntry, pos))
                        {
                            favDict.editName(pos, edit);
                            writeToFile(favDict, FAVORITES);
                        }
                        break;
                    case '2':
                        cout << "Old part of speech: " << myDict.getWord(i).getPartOfSpeech() << endl;
                        getChoice(edit, "part of speech");
                        myDict.editPartOfSpeech(i, edit);
                        if (favDict.doesContain(wantedEntry, pos))
                        {
                            favDict.editPartOfSpeech(pos, edit);
                            writeToFile(favDict, FAVORITES);
                        }
                        break;
                    case '3':
                        cout << "Old meaning: " << myDict.getWord(i).getMeaning() << endl;
                        getChoice(edit, "meaning");
                        myDict.editMeaning(i, edit);
                        if (favDict.doesContain(wantedEntry, pos))
                        {
                            favDict.editMeaning(pos, edit);
                            writeToFile(favDict, FAVORITES);
                        }
                        break;
                }
                writeToFile(myDict, WORDS);
                cout << endl << "Edit successful. Press 0 go to back to the main menu. ";
                checkOption();
            }
        }
    }
    cout << endl << "Entry not found. Press 0 to go back to the main menu. ";
    checkOption();
}

void getChoice(string& option, string characteristic)
{
    cout << endl << "Enter new " << characteristic << ": ";
    string newOption;
    getline (cin, newOption);
    option = newOption;
}

void writeToFile(const Dictionary& whichDict, const char* fileName)
{
    ofstream file(fileName, ios::out | ios::trunc);
    file << whichDict.toString();
    file.close();
}

void googleByMeaning()
{
    system("title Dictionary 2.0 Search by meaning");
    system("cls");
    string desiredMeaning;
    cout << "Enter meaning: ";
    getline (cin, desiredMeaning);
    bool firstMatch = false;
    for (int i = 0; i < myDict.getSize(); i++)
    {
        string meaning = myDict.getWord(i).getMeaning();
        if (containsMeaning(meaning, desiredMeaning) &&
            firstMatch == true)
        {
            cout << endl << endl;
            myDict.getWord(i).print(EMPTY);
        }
        if (containsMeaning(meaning, desiredMeaning) &&
            firstMatch == false)
        {
            firstMatch = true;
            myDict.getWord(i).print(CLS);
        }
    }
    if (firstMatch == false)
    {
        system("cls");
        cout << "No entries with the meaning '" << desiredMeaning << "' found." << endl << endl
             << "Press 0 to return to the main menu. ";
        checkOption();
    }
    else
    {
        cout << endl << endl << "Press 0 to return to the main menu. ";
        checkOption();
    }
}

void addToFavorites()
{
    system("title Dictionary 2.0 Add word to favorites");
    system("cls");
    string desiredWord;
    cout << "Enter word: ";
    getline (cin, desiredWord);
    for (int i = 0; i < myDict.getSize(); i++)
    {
        if (myDict.getWord(i).getName() == desiredWord)
        {
            ifstream fav(FAVORITES);
            for (int j = 0; j < favDict.getSize(); j++)
            {
                if (favDict.getWord(j).getName() == desiredWord)
                {
                    cout << endl << "Error: Entry already added to favorites." << endl <<
                            endl << "Press 0 to go back to the main menu. ";
                    fav.close();
                    checkOption();
                }
            }
            fav.close();
            ofstream file(FAVORITES, ios::app);
            string converted = myDict.getWord(i).toString();
            converted += '\n';
            file << converted;
            file.close();
            favDict.addEntry(myDict.getWord(i));
            cout << endl << "Entry successfully added to favorites." << endl << endl <<
                    "Press 0 to go back to the main menu. ";
            checkOption();
        }
    }
    cout << endl << "Entry not found. Press 0 to go back to the main menu. ";
    checkOption();
}

void deleteEntry(const char* fileName)
{
    if (fileName == FAVORITES)
        system("title Dictionary 2.0 Delete entry from favorites");
    if (fileName == WORDS)
        system("title Dictionary 2.0 Delete entry");
    system("cls");
    string desiredWord;
    cout << "Enter word: ";
    getline (cin, desiredWord);
    if (fileName == FAVORITES)
    {
        if(helperDelete(favDict, FAVORITES, desiredWord))
        {
            cout << endl << "Entry successfully deleted. " << endl << endl <<
                            "Press 0 to go back to the main menu. ";
        }
        else
            cout << endl << "Entry not found. Press 0 to go back to the main menu. ";
        checkOption();
    }
    else
    {
        if(helperDelete(myDict, WORDS, desiredWord))
        {
            helperDelete(favDict, FAVORITES, desiredWord);
            helperDelete(myNouns, NOUNS, desiredWord);
            helperDelete(myVerbs, VERBS, desiredWord);
            cout << endl << "Entry successfully deleted. " << endl << endl <<
                            "Press 0 to go back to the main menu. ";
        }
        else
            cout << endl << "Entry not found. Press 0 to go back to the main menu. ";
        checkOption();
    }
}

bool helperDelete(Dictionary& whichDict, const char* fileName, string desiredWord)
{
    for (int i = 0; i < whichDict.getSize(); i++)
    {
        if (whichDict.getWord(i).getName() == desiredWord)
        {
            whichDict.eraseEntry(i);
            writeToFile(whichDict, fileName);
            return true;
        }
    }
    return false;
}

/* Генерира думи от избран речни, на които трябва да бъде познато
   значението им. */
void testMeaning(Dictionary whichDict, const char* fileName)
{
    if (fileName == WORDS)
    {
        system("title Dictionary 2.0 Test knowledge");
    }
    if (fileName == FAVORITES)
        system("title Dictionary 2.0 Test knowledge from favorites");
    system("cls");
    double totalScore = 0;
    int numberOfPassedWords = 0;
    nextWord:

    string option;
    int counter = 0;
    int randomNumber;
    if (whichDict.getSize() > 0)
    {
        srand(time(0));
        randomNumber = rand() % whichDict.getSize();
    }
    else
    {
        cout << "No more words to test. " << endl;
        cout << "Press 0 to return to main menu. ";
        checkOption();
    }
    //За всяка дума запазва значението й в стринг
    string actualMeaning = whichDict.getWord(randomNumber).getMeaning();
    int guessedWords = 0;
    //Взимаме общия брой значения на дума
    int totalWords = numberOfMeanings(actualMeaning);
    cout << endl << "What is the meaning of " << whichDict.getWord(randomNumber).getName() << "? ";
    nextMeaning:

    string guessMeaning;
    //counter отбелязва колко пъти сме били в една и съща дума
    if (counter > 0)
        guessMeaning = option;
    if (counter == 0)
        getline (cin, guessMeaning);
    //При 0 се въщаме в main, при n преминаваме към следващата дума
    if (guessMeaning == "0")
        main();
    if (guessMeaning == "n")
    {
        cout << endl << "Just so you know, the meaning is '" << actualMeaning << "'" << endl;
        whichDict.eraseEntry(randomNumber);
        numberOfPassedWords++;
        cout << "Current score: " << ((double) totalScore / (double) numberOfPassedWords)*100 << "%" << endl;
        goto nextWord;
    }
    //Ако това, което сме отгатнали, се среща в значението и не сме изчерпали всички значения
    if (containsMeaning(actualMeaning, guessMeaning) && (guessedWords + 1) != totalWords)
    {
        string::size_type i = actualMeaning.find(guessMeaning);
        if (i != string::npos)
            actualMeaning.erase(i, guessMeaning.length());
        guessedWords++;
        cout << endl << "Correct! You've guessed " << guessedWords << "/" <<
                totalWords << "." << endl <<
                "Enter another meaning, press 'n' to skip this word or press 0 to go back to the main menu. ";
        counter++;
        getline (cin, option);
        if (option == "0")
            main();
        if (option == "n")
        {
            //polishString взима стринг, от които са изтрити някои значения и го прави по-красив
            cout << "Just so you know, the other meaning is '" << polishString(actualMeaning) << "'" << endl;
            whichDict.eraseEntry(randomNumber);
            numberOfPassedWords++;
            totalScore += (double) guessedWords / (double) totalWords;
            cout << "Current score: " << (totalScore / (double) numberOfPassedWords)*100 << "%" << endl;
            goto nextWord;
        }
        else
            goto nextMeaning;
    }
    if (containsMeaning(actualMeaning, guessMeaning) && (guessedWords + 1) == totalWords)
    {
        guessedWords++;
        cout << endl << "Excellent! You've guessed all the meanings! " << endl <<
                "Press 'n' to go to another word or press 0 to go to the main menu. ";
        getline (cin, option);
        if (option == "0")
            main();
        if (option == "n")
        {
            numberOfPassedWords++;
            totalScore += 1;
            whichDict.eraseEntry(randomNumber);
            cout << "Current score: " << (totalScore / (double) numberOfPassedWords)*100 << "%" << endl;
            goto nextWord;
        }

    }
    //Ако не сме отгатнали
    if (!containsMeaning(actualMeaning, guessMeaning))
    {
        cout << endl << "Sorry, that's not one of the meanings, try again. ";
        counter++;
        getline(cin, option);
        if (option == "0")
            main();
        if (option == "n")
        {
            cout << "Just so you know, the other meaning is '" << polishString(actualMeaning) << "'" << endl;
            whichDict.eraseEntry(randomNumber);
            totalScore += (double) guessedWords / (double) totalWords;
            numberOfPassedWords++;
            cout << "Current score: " << (totalScore / (double) numberOfPassedWords)*100 << "%" << endl;
            goto nextWord;
        }
        else
            goto nextMeaning;
    }
}

void testNouns()
{
    system("title Dictionary 2.0 Test nouns");
    system("cls");
    Dictionary copyDict = myNouns;
    double totalScore = 0;
    int numberOfPassedWords = 0;
    nextWord:

    string option;
    int counter = 0;
    int randomNumber;
    if (copyDict.getSize() > 0)
    {
        srand(time(0));
        randomNumber = rand() % copyDict.getSize();
    }
    else
    {
        cout << "No more words to test. " << endl;
        cout << "Press 0 to return to main menu. ";
        checkOption();
    }
    string actualGender = copyDict.getWord(randomNumber).getDerDieDas();
    string actualPlural = copyDict.getWord(randomNumber).getPlural();
    cout << endl << "Enter gender of " << copyDict.getWord(randomNumber).getName() << " ";
    string guessGender;
    getline (cin, guessGender);
    if (guessGender == "0")
        main();
    if (guessGender == "n" || guessGender != actualGender)
    {
        cout << endl << "Just so you know, the gender is '" << actualGender << "'" << endl;
        copyDict.eraseEntry(randomNumber);
        numberOfPassedWords++;
        cout << "Current score: " << ((double) totalScore / (double) numberOfPassedWords)*100 << "%" << endl;
        goto nextWord;
    }
    if (guessGender == actualGender)
    {
        cout << endl << "Correct! Now enter the plural form: ";
        totalScore += 0.5;
    }
    string guessPlural;
    getline (cin, guessPlural);
    if (guessPlural == "0")
        main();
    if (guessPlural == "n" || guessPlural != actualPlural)
    {
        cout << endl << "Just so you know, the plural is '" << actualGender << "'" << endl;
        copyDict.eraseEntry(randomNumber);
        numberOfPassedWords++;
        cout << "Current score: " << ((double) totalScore / (double) numberOfPassedWords)*100 << "%" << endl;
        goto nextWord;
    }
    if (guessPlural == actualPlural)
    {
        totalScore += 0.5;
        copyDict.eraseEntry(randomNumber);
        numberOfPassedWords++;
        cout << endl << "Correct! Current score: " << ((double) totalScore / (double) numberOfPassedWords)*100 << "%" << endl;;
        goto nextWord;
    }
}

void testVerbs()
{
    system("title Dictionary 2.0 Test verbs");
    system("cls");
    Dictionary copyDict = myVerbs;
    double totalScore = 0;
    int numberOfPassedWords = 0;
    nextWord:

    string option;
    int randomNumber;
    if (copyDict.getSize() > 0)
    {
        srand(time(0));
        randomNumber = rand() % copyDict.getSize();
    }
    else
    {
        cout << "No more words to test. " << endl;
        cout << "Press 0 to return to main menu. ";
        checkOption();
    }
    string actualPastTense = copyDict.getWord(randomNumber).getPastTense();
    cout << endl << "Enter past tense of " << copyDict.getWord(randomNumber).getName() << " ";
    string guessPastTense;
    getline (cin, guessPastTense);
    if (guessPastTense == "0")
        main();
    if (guessPastTense == "n" || guessPastTense != actualPastTense)
    {
        cout << endl << "Just so you know, the past tense is '" << actualPastTense << "'" << endl;
        copyDict.eraseEntry(randomNumber);
        numberOfPassedWords++;
        cout << "Current score: " << ((double) totalScore / (double) numberOfPassedWords)*100 << "%" << endl;
        goto nextWord;
    }
    if (guessPastTense == actualPastTense)
    {
        totalScore += 1;
        copyDict.eraseEntry(randomNumber);
        numberOfPassedWords++;
        cout << endl << "Correct! Current score: " << ((double) totalScore / (double) numberOfPassedWords)*100 << "%" << endl;
        goto nextWord;
    }
}
