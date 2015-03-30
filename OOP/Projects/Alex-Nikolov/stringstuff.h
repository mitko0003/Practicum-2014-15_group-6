#ifndef STRINGSTUFF_H_
#define STRINGSTUFF_H_

std::string getStringGender(std::string);    //от дългия стринг на всяка дума
std::string getStringPlural(std::string);    //извлича съответната характеристика
std::string getStringPastTense(std::string);
std::string getStringMeaning(std::string);
std::string getStringName(std::string);
std::string getStringPartOfSpeech(std::string);
void helperMeaning(int, int, int, std::string, std::string&);  //в getStringMeaning помощна функция
bool containsMeaning(std::string, std::string);  //проверява дали втория стринг се среща в първия (като значение)
int numberOfMeanings(std::string);  //връща броя на значениеята на дума
std::string polishString(std::string);   //виж testMeaning в main

#endif /* STRINGSTUFF_H_ */
