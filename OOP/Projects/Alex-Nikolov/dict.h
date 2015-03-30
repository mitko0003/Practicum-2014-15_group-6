#ifndef DICT_H_
#define DICT_H_
#include <vector>
#include "word.h"

class Dictionary
{
    private:
        std::vector <Word> dict;
    public:
        Dictionary(const char*);
        int getSize() const;
        Word getWord(int) const;
        void addEntry(Word);
        void editName(int, std::string);
        void editPartOfSpeech(int, std::string);
        void editDerDieDas(int, std::string);
        void editPlural(int, std::string);
        void editMeaning(int, std::string);
        void editPastTense(int, std::string);
        bool doesContain(std::string, int&);
        std::string toString() const;
        void eraseEntry(int);
};

#endif // DICT_H_
