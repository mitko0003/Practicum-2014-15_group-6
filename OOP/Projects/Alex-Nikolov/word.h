#ifndef WORDS_H_
#define WORDS_H_
#include <string>

class Word
{
   private:
       std::string name;
       std::string meaning;
       std::string partOfSpeech;
       std::string derDieDas;
       std::string plural;
       std::string pastTense;
   public:
       Word (std::string);   //създава дума спрямо дългия стринг от файла
       ~Word ();
       std::string getName() const { return name; }
       std::string getMeaning() const { return meaning; }
       std::string getPartOfSpeech() const { return partOfSpeech; }
       std::string getPlural() const { return plural; }
       std::string getPastTense() const { return pastTense; }
       std::string getDerDieDas() const { return derDieDas; }
       void setName(std::string n) { name = n; }
       void setMeaning(std::string m) { meaning = m; }
       void setPartOfSpeech(std::string pos) { partOfSpeech = pos; }
       void setPlural(std::string pl) { plural = pl; }
       void setPastTense(std::string pt) { pastTense = pt; }
       void setDerDieDas(std::string ddd) { derDieDas = ddd; }
       std::string toString() const;   //конвертира съществуваща дума обратно в стринг
       void uglyPrint();    //2 принта
       void print(std::string);

};

#endif
