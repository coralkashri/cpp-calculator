/**
 * Taken from: https://github.com/korelkashri/cpp-text-designer
 */

#ifndef DESIGNER_DESIGNER_H
#define DESIGNER_DESIGNER_H

#include <iostream>
#include <sstream>

namespace designer {
    enum color {
        BLACK = -2,
        WHITE = -1,
        BLUE = 1,
        RED = 2,
        GREEN = 3,
        YELLOW = 4,
        MAGENTA = 5,
        CYAN = 6
    };

    std::string make_colored(const std::string &text, color color, bool bold);

    std::string make_colored(const std::stringstream &text, color color, bool bold);

    std::string make_colored(const char *text, color color, bool bold);

    std::string make_colored(const std::ostream &text, color color, bool bold);

    std::string make_conditioned_colored(const std::string &text, color true_color, bool true_bold, color false_color, bool false_bold, bool condition);

    std::string make_conditioned_colored(const std::stringstream &text, color true_color, bool true_bold, color false_color, bool false_bold, bool condition);

    std::string make_conditioned_colored(const char *text, color true_color, bool true_bold, color false_color, bool false_bold, bool condition);

    std::string make_conditioned_colored(const std::ostream &text, color true_color, bool true_bold, color false_color, bool false_bold, bool condition);
}

#endif //DESIGNER_DESIGNER_H