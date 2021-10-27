/*
MIT License

Copyright (c) 2021 Andrew Parr

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "doomsday.h"

#include <boost/program_options.hpp>

#include <thread>
#include <iostream>
#include <string_view>

namespace po = boost::program_options;

void showHeader() {
    std::cout << "Gimme a date!\n";
    std::cout << "Use ";
    for (unsigned i = 0; i < 7; ++i) {
        date::weekday wd(i);
        if (i > 0)
            std::cout << ", ";
        std::cout << i << " = " << date::format("%A", wd);
    }
    std::cout << std::endl;
}

int main(int argc, char *argv[]) {
    int n=1;
    std::string start_date("1900/1/1");
    std::string end_date("2100/1/1");

    try {
        po::options_description desc("Gimme a date!\nOptions:");
        desc.add_options()
            ("help,h", "Display this help")
            (",n", po::value(&n), "number of dates to test")
            ("start_date,s", po::value(&start_date), "The random date will not be earlier than this date.")
            ("end_date,e", po::value(&end_date), "The random date will be before this date.");
        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("help")) {
            std::cout << desc << "\n";
            return 0;
        }

        Doomsday doomsday;
        if (!doomsday.setDateRange(start_date, end_date)) {
            std::cerr << "Invalid date specified\n";
            return -1;
        }

        showHeader();
        while (n--) {
            std::cout << doomsday.date() << "\n";
            unsigned i;
            std::cin >> i;
            if (i > 7) i %= 7;
            date::weekday ans(i);
            if (ans != doomsday.day()) {
                std::cout << "Wrong, your answer was " << date::format("%A", ans) << "\n";
                std::cout << "The correct answer is " << date::format("%A", doomsday.day()) << "\n";
                std::this_thread::sleep_for(std::chrono::seconds(3));
                return 1;
            }
            std::cout << "Correct\n";
        }

    } catch (const po::error& ex) {
        std::cerr << ex.what() << '\n';
        return -1;
    }
    return 0;
}