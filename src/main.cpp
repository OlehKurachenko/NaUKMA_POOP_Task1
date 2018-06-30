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

    p.addUser("Oleh Kurachenko");
    std::cerr << "All ok\n";
    p.addPhoneNumber("Oleh Kurachenko", "+380501656149");
    std::cerr << "All ok\n";
    p.addPhoneNumber("Oleh Kurachenko", "5663830");
    std::cerr << "All ok\n";

    std::ofstream ofstream(argv[1], std::ofstream::out);
    ofstream << p;
    ofstream.close();

    return (0);
}
