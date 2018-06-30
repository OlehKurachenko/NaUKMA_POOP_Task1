// 
//  Created by Oleh Kurachenko
//         aka okurache
//  on 2018-06-29T21:33:34Z as a part of NaUKMA_POOP_Task1
//  
//  ask me      oleh.kurachenko@gmail.com , I'm ready to help
//  GitHub      https://github.com/OlehKurachenko
//  rate & CV   http://www.linkedin.com/in/oleh-kurachenko-6b025b111
//

#ifndef NAUKMA_POOP_TASK1_PHONEBOOK_H
#define NAUKMA_POOP_TASK1_PHONEBOOK_H

#if defined(unix) || defined(__unix__) || defined(__unix)
# define NAUKMA_POOP_TASK1_PHONEBOOK_H_COLORED_OUTPUT true
#else
# define NAUKMA_POOP_TASK1_PHONEBOOK_H_COLORED_OUTPUT false
#endif

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using std::istream;
using std::ostream;

using std::string;
using std::map;
using std::vector;

class Phonebook {
public:

    class Card;

    inline Phonebook() = default;

    inline ~Phonebook() = default;

    inline const Card &addUser(const string &userName);

    inline const Card &addPhoneNumber(const string &userName, const string &phoneNumber);

    inline const vector<string> listUsers() const;

    inline const Card &card(const string &userName) const;

    Phonebook(const Phonebook &) = delete;

    Phonebook &operator=(const Phonebook &) = delete;

private:

    map<const string, Card> _phonebook;

};

inline istream &operator>>(istream &istr, Phonebook &phonebook);

inline ostream &operator<<(ostream &ostr, const Phonebook &phonebook);

//  class Phonebook::Card

class Phonebook::Card {
public:

    inline Card(const string& userName);

    inline ~Card() = default;

    inline Card(const Card &) = default;

    inline void addPhoneNumber(const string &phoneNumber);

    inline const vector<string> &listNumbers() const { return _phones; }

    inline const string userName() const { return _userName; }

    Card &operator=(const Card &) = delete;

private:

    string _userName;
    vector<string> _phones;
};

//  utills

inline bool    phoneNumberIsValid(const string &phoneNumber); // TODO

//  class Phonebook definitions

inline const Phonebook::Card &Phonebook::addUser(const string &userName) {
    if (userName.length() == 0)
        throw std::runtime_error("Bad user name");
    if (this->_phonebook.find(userName) != this->_phonebook.end())
        throw std::runtime_error("User already exist");
    this->_phonebook.insert({userName, Phonebook::Card(userName)});
    return this->_phonebook.at(userName); //this->_phonebook[userName];
}

inline const Phonebook::Card &Phonebook::addPhoneNumber(const string &userName,
                                                        const string &phoneNumber) {
    if (userName.length() == 0)
        throw std::runtime_error("Bad user name");
    if (this->_phonebook.find(userName) == this->_phonebook.end())
        throw std::runtime_error("User does not exist");
    if (!phoneNumberIsValid(phoneNumber))
        throw std::runtime_error("Bad phone number");
    this->_phonebook.at(userName).addPhoneNumber(phoneNumber);
    return this->_phonebook.at(userName); //this->_phonebook[userName];
}

inline const vector<string> Phonebook::listUsers() const {
    vector<string> usersList;
    usersList.reserve(this->_phonebook.size());
    for (const std::pair<const string, Phonebook::Card> &userName : this->_phonebook)
        usersList.push_back(userName.first);
    return usersList;
}

inline const Phonebook::Card &Phonebook::card(const string &userName) const {
    if (userName.length() == 0)
        throw std::runtime_error("Bad user name");
    if (this->_phonebook.find(userName) == this->_phonebook.end())
        throw std::runtime_error("User does not exist");
    return this->_phonebook.at(userName); //this->_phonebook[userName];
}

inline ostream &operator<<(ostream &ostr, const Phonebook &phonebook)
{
    const vector<string> usersList = phonebook.listUsers();
    ostr << usersList.size() << std::endl;
    for (const string &userName: usersList) {
        const Phonebook::Card &userCard = phonebook.card(userName);
        ostr << userCard.listNumbers().size() << ' ' << userCard.userName();
        for (const string &phoneNumber: userCard.listNumbers())
            ostr << ' ' << phoneNumber;
        ostr << std::endl;
    }
    return ostr;
}

//inline istream &operator>>(istream &istr, Phonebook &phonebook) {
//    size_t  mapSize;
//    size_t  listSize;
//    string  nextName;
//    string  nextPhoneNumber;
//
//    istr >> mapSize;
//    for (size_t i{ 0 }; i < mapSize; ++i) {
//        istr >> listSize;
//
//    }
//}

//  class Phonebook::Card definitions

inline Phonebook::Card::Card(const string &userName):
    _userName(userName),
    _phones()
{ }

inline void Phonebook::Card::addPhoneNumber(const string &phoneNumber) {
    if (!phoneNumberIsValid(phoneNumber))
        throw std::runtime_error("Bad phone number");
    if (std::find(this->_phones.begin(), this->_phones.end(), phoneNumber) != this->_phones.end())
        throw std::runtime_error("Phone number already in card");
    this->_phones.push_back(phoneNumber);
}

//  utills definitions

inline bool phoneNumberIsValid(const string &phoneNumber) {
    return phoneNumber.size() != 0;
}

#endif //NAUKMA_POOP_TASK1_PHONEBOOK_H
