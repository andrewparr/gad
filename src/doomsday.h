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

#ifndef DOOMSDAY_H
#define DOOMSDAY_H

#include <date/date.h>

#include <random>
#include <string_view>

class Doomsday {
public:
    Doomsday();
    bool setDateRange(std::string_view start, std::string_view end);
    void newRandomDate();
    std::string date();
    date::weekday day();

private:

    bool parseString(std::string_view str, date::year_month_day& date);

    date::year_month_day start_range_;
    date::year_month_day end_range_;
    date::year_month_day test_date_;

    // For random date generation
    std::random_device rd_;
    std::mt19937 mt_;
    std::uniform_real_distribution<float> dist_;
};

#endif  // DOOMSDAY_H