// 
//  Created by Oleh Kurachenko
//         aka okurache
//  on 2018-07-01T02:29:06Z as a part of NaUKMA_POOP_Task1
//  
//  ask me      oleh.kurachenko@gmail.com , I'm ready to help
//  GitHub      https://github.com/OlehKurachenko
//  rate & CV   http://www.linkedin.com/in/oleh-kurachenko-6b025b111
//

#ifndef NAUKMA_POOP_TASK1_CONSOLE_COLORS_H
#define NAUKMA_POOP_TASK1_CONSOLE_COLORS_H

#if defined(unix) || defined(__unix__) || defined(__unix)
# define NAUKMA_POOP_TASK1_PHONEBOOK_H_COLORED_OUTPUT true
#else
# define NAUKMA_POOP_TASK1_PHONEBOOK_H_COLORED_OUTPUT false
#endif

#include <string>

namespace coloredPrint {
    const std::string BOLD_RED{ (NAUKMA_POOP_TASK1_PHONEBOOK_H_COLORED_OUTPUT) ? "\033[1;31m" : ""};

    const std::string BLUE{ (NAUKMA_POOP_TASK1_PHONEBOOK_H_COLORED_OUTPUT) ? "\033[0;34m" : ""};
    const std::string BOLD_BLUE{ (NAUKMA_POOP_TASK1_PHONEBOOK_H_COLORED_OUTPUT) ? "\033[1;34m" :
                                 ""};

    const std::string RESET{ (NAUKMA_POOP_TASK1_PHONEBOOK_H_COLORED_OUTPUT) ? "\033[0;0m" : ""};
}

#endif //NAUKMA_POOP_TASK1_CONSOLE_COLORS_H
