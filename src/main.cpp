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

#include "console_colors.h"
#include "Phonebook.h"

using std::cout;
using std::endl;

int main(const int argc, const char **argv) {
    if (argc < 3) {
        cout << coloredPrint::BLUE;
        cout << "Usage:" << endl;
        cout << "   " << argv[0] << " file_name list : list all contacts" << endl;
        cout << "   " << argv[0]
             << " file_name add user_name phone_number : add phone_number to list of numbers of "
                "user_name. If user_name does'n exist, it is being created" << endl;
        cout << coloredPrint::RESET;
        exit(0);
    }

    Phonebook p;

    std::ifstream ifstream(argv[1], std::ifstream::in);
    if (ifstream.is_open())
        ifstream >> p;

    if (argv[2] == std::string("list"))
    {
        if (argc == 3) {
            cout << coloredPrint::BLUE;
            cout << "Listing all contacts:" << endl;
            cout << coloredPrint::RESET;

            for (const string &userName: p.listUsers())
                verbosePrint(p.card(userName));
        }

        if (argc == 4) {
            if (p.has(argv[3])) {
                verbosePrint(p.card(argv[3]));
            } else {
                cout << coloredPrint::BLUE;
                cout << "No such person in contacts" << endl;
                cout << coloredPrint::RESET;
            }
        }
    }

    if (argv[2] == std::string("add") && argc == 5)
    {
        if (!p.has(argv[3])) {
            try {
                p.addUser(argv[3]);
            } catch (std::runtime_error &err) {
                cout << coloredPrint::BOLD_RED;
                cout << err.what() << endl;
                cout << coloredPrint::RESET;
                exit(0);
            }
        }
        try {
            const Phonebook::Card &card = p.addPhoneNumber(argv[3], argv[4]);
            cout << coloredPrint::BLUE;
            cout << "Card updated:" << endl;
            cout << coloredPrint::RESET;
            verbosePrint(card);
        } catch (std::runtime_error &err) {
            cout << coloredPrint::BOLD_RED;
            cout << err.what() << endl;
            cout << coloredPrint::RESET;
        }
    }

    if (argv[2] == std::string("remove")) {
        if (argc == 4) {
            try {
                p.removeUser(argv[3]);
            } catch (std::runtime_error &err) {
                cout << coloredPrint::BOLD_RED;
                cout << err.what() << endl;
                cout << coloredPrint::RESET;
            }
        }
        if (argc == 5) {
            try {
                const Phonebook::Card &card = p.removePhoneNumber(argv[3], argv[4]);
                cout << coloredPrint::BLUE;
                cout << "Card updated:" << endl;
                cout << coloredPrint::RESET;
                verbosePrint(card);
            } catch (std::runtime_error &err) {
                cout << coloredPrint::BOLD_RED;
                cout << err.what() << endl;
                cout << coloredPrint::RESET;
            }
        }
    }

    if (argv[2] == std::string("find") && argc == 4) {
        bool found { false };
        for (const Phonebook::Card &userCard: p.findByPhoneNumber(argv[3])) {
            if (!found)
                cout << coloredPrint::BLUE << "Persons found:" << endl << coloredPrint::RESET;
            found = true;
            verbosePrint(userCard);
        }
        if (!found)
            cout << coloredPrint::BLUE << "Nothing found" << endl << coloredPrint::RESET;
    }

    std::ofstream ofstream(argv[1], std::ofstream::out);
    ofstream << p;
    ofstream.close();

    return (0);
}
