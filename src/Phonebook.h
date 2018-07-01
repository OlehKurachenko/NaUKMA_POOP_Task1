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

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

#include "console_colors.h"

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

    inline void removeUser(const string &userName);

    inline const Card &addPhoneNumber(const string &userName, const string &phoneNumber);

    inline const Phonebook::Card &removePhoneNumber(const string &userName,
                                                    const string &phoneNumber);

    inline const vector<Card> findByPhoneNumber(const string &phoneNumber);

    inline const vector<string> listUsers() const;

    inline bool has(const string &userName) const;

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

    inline void removePhoneNumber(const string &phoneNumber);

    inline const vector<string> &listNumbers() const { return _phones; }

    inline const string userName() const { return _userName; }

    Card &operator=(const Card &) = delete;

private:

    string _userName;
    vector<string> _phones;
};

inline void verbosePrint(const Phonebook::Card &card);

//  utills

inline bool phoneNumberIsValid(const string &phoneNumber);

//  class Phonebook definitions

inline const Phonebook::Card &Phonebook::addUser(const string &userName) {
    if (userName.length() == 0)
        throw std::runtime_error("Bad user name");
    if (this->has(userName))
        throw std::runtime_error("User already exist");
    this->_phonebook.insert({userName, Phonebook::Card(userName)});
    return this->_phonebook.at(userName); //this->_phonebook[userName];
}

inline const Phonebook::Card &Phonebook::addPhoneNumber(const string &userName,
                                                        const string &phoneNumber) {
    if (userName.length() == 0)
        throw std::runtime_error("Bad user name");
    if (!this->has(userName))
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

inline bool Phonebook::has(const string &userName) const {
    return (this->_phonebook.find(userName) != this->_phonebook.end());
}

inline const Phonebook::Card &Phonebook::card(const string &userName) const {
    if (userName.length() == 0)
        throw std::runtime_error("Bad user name");
    if (!this->has(userName))
        throw std::runtime_error("User does not exist");
    return this->_phonebook.at(userName); //this->_phonebook[userName];
}

inline void Phonebook::removeUser(const string &userName) {
    if (userName.length() == 0)
        throw std::runtime_error("Bad user name");
    if (!this->has(userName))
        throw std::runtime_error("User does not exist");
    this->_phonebook.erase(userName);
}

inline const Phonebook::Card &Phonebook::removePhoneNumber(const string &userName, const string &phoneNumber) {
    if (userName.length() == 0)
        throw std::runtime_error("Bad user name");
    if (!this->has(userName))
        throw std::runtime_error("User does not exist");
    this->_phonebook.at(userName).removePhoneNumber(phoneNumber);
    return this->_phonebook.at(userName);
}

inline const vector<Phonebook::Card> Phonebook::findByPhoneNumber(const string
                                                                         &phoneNumber) {
    vector<Phonebook::Card> found;
    const vector<string> usersList = this->listUsers();
    for (const string &userName: usersList) {
        const Phonebook::Card &userCard = this->card(userName);
        if (std::find(userCard.listNumbers().begin(), userCard.listNumbers().end(), phoneNumber) !=
                userCard.listNumbers().end())
            found.push_back(userCard);
    }
    return found;
}

inline ostream &operator<<(ostream &ostr, const Phonebook &phonebook)
{
    const vector<string> usersList = phonebook.listUsers();
    ostr << usersList.size() << std::endl;
    for (const string &userName: usersList) {
        const Phonebook::Card &userCard = phonebook.card(userName);
        ostr << userCard.listNumbers().size() << std::endl << userCard.userName();
        for (const string &phoneNumber: userCard.listNumbers())
            ostr << std::endl << phoneNumber;
        ostr << std::endl;
    }
    return ostr;
}

inline istream &operator>>(istream &istr, Phonebook &phonebook) {
    size_t  mapSize;
    size_t  listSize;
    string  nextName;
    string  nextPhoneNumber;

    istr >> mapSize;
    for (size_t i{ 0 }; i < mapSize; ++i) {
        istr >> listSize;
        getline(istr, nextName); // pass the end of line
        getline(istr, nextName);
        phonebook.addUser(nextName);
        for (size_t j{ 0 }; j < listSize; ++j) {
            getline(istr, nextPhoneNumber);
            phonebook.addPhoneNumber(nextName, nextPhoneNumber);
        }
    }
}

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

inline void Phonebook::Card::removePhoneNumber(const string &phoneNumber) {
    std::vector<string>::iterator phoneNumberToRemove = std::find(this->_phones.begin(),
                                                                  this->_phones.end(), phoneNumber);
    if (phoneNumberToRemove == this->_phones.end())
        throw std::runtime_error("No such phone number");
    this->_phones.erase(phoneNumberToRemove);
}

inline void verbosePrint(const Phonebook::Card &card) {
    if (NAUKMA_POOP_TASK1_PHONEBOOK_H_COLORED_OUTPUT)
        std::cout << "\033[0;36m"; // cyan
    std::cout << "Person: ";
    if (NAUKMA_POOP_TASK1_PHONEBOOK_H_COLORED_OUTPUT)
        std::cout << "\033[1;36m"; // bold cyan
    std::cout << card.userName() << std::endl;

    for (const string &phoneNumber : card.listNumbers())
        std::cout << "   " << phoneNumber << std::endl;
    if (NAUKMA_POOP_TASK1_PHONEBOOK_H_COLORED_OUTPUT)
        std::cout << "\033[0;0m"; // reset
}

//  utills definitions

inline bool phoneNumberIsValid(const string &phoneNumber) {
    return phoneNumber.size() != 0;
}

#endif //NAUKMA_POOP_TASK1_PHONEBOOK_H
