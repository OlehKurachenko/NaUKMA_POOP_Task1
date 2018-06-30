// 
//  Created by Oleh Kurachenko
//         aka okurache
//  on 2018-06-30T15:55:11Z as a part of NaUKMA_POOP_Task1
//  
//  ask me      oleh.kurachenko@gmail.com , I'm ready to help
//  GitHub      https://github.com/OlehKurachenko
//  rate & CV   http://www.linkedin.com/in/oleh-kurachenko-6b025b111
//

#include <iostream>
#include <fstream>
#include "Phonebook.h"

using std::cout;
using std::endl;

int main(const int argc, const char **argv) {
    if (argc < 3) {
        if (NAUKMA_POOP_TASK1_PHONEBOOK_H_COLORED_OUTPUT)
            cout << "\033[0;34m"; // blue
        cout << "Usage:" << endl;
        cout << "   " << argv[0] << " file_name list : list all contacts" << endl;
        cout << "   " << argv[0]
             << " file_name add user_name phone_number : add phone_number to list of numbers of "
                "user_name. If user_name does'n exist, it is being created" << endl;
        if (NAUKMA_POOP_TASK1_PHONEBOOK_H_COLORED_OUTPUT)
            cout << "\033[0;0m"; // reset
        exit(0);
    }

    Phonebook p;

    std::ifstream ifstream(argv[1], std::ifstream::in);
    if (ifstream.is_open())
        ifstream >> p;

    if (argc == 3 && argv[2] == std::string("list"))
    {
        if (NAUKMA_POOP_TASK1_PHONEBOOK_H_COLORED_OUTPUT)
            cout << "\033[0;34m"; // blue
        cout << "Listing all contacts:" << endl;
        if (NAUKMA_POOP_TASK1_PHONEBOOK_H_COLORED_OUTPUT)
            cout << "\033[0;0m"; // reset

        for (const string &userName: p.listUsers())
            verbosePrint(p.card(userName));
    }

    if (argc == 5 && argv[2] == std::string("add"))
    {
        if (!p.has(argv[3])) {
            try {
                p.addUser(argv[3]);
            } catch (std::runtime_error &err) {
                if (NAUKMA_POOP_TASK1_PHONEBOOK_H_COLORED_OUTPUT)
                    cout << "\033[1;31m"; // bold red
                cout << err.what() << endl;
                if (NAUKMA_POOP_TASK1_PHONEBOOK_H_COLORED_OUTPUT)
                    cout << "\033[0;0m"; // reset
                exit(0);
            }
        }
        try {
            const Phonebook::Card &card = p.addPhoneNumber(argv[3], argv[4]);
            if (NAUKMA_POOP_TASK1_PHONEBOOK_H_COLORED_OUTPUT)
                cout << "\033[0;34m"; // blue
            cout << "New number added:" << endl;
            if (NAUKMA_POOP_TASK1_PHONEBOOK_H_COLORED_OUTPUT)
                cout << "\033[0;0m"; // reset
            verbosePrint(card);
        } catch (std::runtime_error &err) {
            if (NAUKMA_POOP_TASK1_PHONEBOOK_H_COLORED_OUTPUT)
                cout << "\033[1;31m"; // bold red
            cout << err.what() << endl;
            if (NAUKMA_POOP_TASK1_PHONEBOOK_H_COLORED_OUTPUT)
                cout << "\033[0;0m"; // reset
        }
    }

//    p.addUser("Oleh Kurachenko");
//    std::cerr << "All ok\n";
//    p.addPhoneNumber("Oleh Kurachenko", "+380501656149");
//    std::cerr << "All ok\n";
//    p.addPhoneNumber("Oleh Kurachenko", "5663830");
//    std::cerr << "All ok\n";

    //p.addUser("Mr. Lololoshka");
    //p.addPhoneNumber("Mr. Lololoshka", "101");

    std::ofstream ofstream(argv[1], std::ofstream::out);
    ofstream << p;
    ofstream.close();

    return (0);
}
