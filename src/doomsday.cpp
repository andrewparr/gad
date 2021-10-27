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

#include <iostream>
#include <chrono>
#include <regex>

namespace {
    static const std::regex regex_date("(\\d*)[:|/|-](\\d*)[:|/|-](\\d*)");
}

Doomsday::Doomsday() :
    mt_(rd_()),
    dist_(0.0f, 1.0f) {
    std::string start_date("1900/1/1");
    std::string end_date("2100/1/1");
    setDateRange(start_date, end_date);
}

bool Doomsday::setDateRange(const std::string& start, const std::string& end) {

    if (!parseString(start, start_range_))
        return false;
    if (!parseString(end, end_range_))
        return false;

    if (end_range_ < start_range_)
        return false;

    newRandomDate();
    return true;
}

void Doomsday::newRandomDate() {
    auto day_range = std::chrono::duration_cast<date::days>((date::sys_days)end_range_  - (date::sys_days)start_range_).count();
    uint64_t random = static_cast<uint64_t>(dist_(mt_) * day_range);
    random += std::chrono::duration_cast<date::days>(((date::sys_days)start_range_).time_since_epoch()).count();
    std::chrono::system_clock::time_point tp{std::chrono::hours{random*24}};
    test_date_ = date::year_month_day{floor<date::days>(tp)};
}

bool Doomsday::parseString(const std::string& str, date::year_month_day& ymd) {
    std::cmatch result;
    bool ret = std::regex_match(str.c_str(), result, regex_date);
    if (!ret)
        return false;

    int year = std::stoi(std::string(result[1]));
    int month = std::stoi(std::string(result[2]));
    int day = std::stoi(std::string(result[3]));

    ymd = date::year{year}/month/day;
    return ymd.ok();
}

std::string Doomsday::date() {
    std::stringstream ss;
    ss << date::format("%e %B %Y", test_date_);
    return ss.str();
}

date::weekday Doomsday::day() {
    return date::weekday{test_date_};
}