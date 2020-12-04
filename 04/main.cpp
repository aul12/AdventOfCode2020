#include <filesystem>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>

auto parseFile(const std::filesystem::path &path) -> std::vector<std::map<std::string, std::string>> {
    std::ifstream stream{"input"};

    enum class State {
            KEY, VALUE, AFTER_NEWLINE
    } state = State::KEY;

    std::string currKey, currVal;
    std::map<std::string, std::string> currEntries;
    std::vector<std::map<std::string, std::string>> ret;

    char c;
    while (stream >> std::noskipws >> c) {
        switch (state) {
            case State::KEY:
                if (c != ':') {
                    currKey += c;
                } else {
                    state = State::VALUE;
                }
                break;
            case State::VALUE:
                if (c != ' ' and c != '\n') {
                    currVal += c;
                } else {
                    currEntries.emplace(currKey, currVal);
                    currKey.clear();
                    currVal.clear();
                    if (c == ' ') {
                        state = State::KEY;
                    } else {
                        state = State::AFTER_NEWLINE;
                    }
                }
                break;
            case State::AFTER_NEWLINE:
                if (c == '\n') {
                    ret.emplace_back(currEntries);
                    currEntries.clear();
                } else {
                    currKey += c;
                }
                state = State::KEY;
                break;

        }
    }

    return ret;
}

auto verifyPassport(const std::map<std::string, std::string> &passport) -> bool {
    try {
        int byr = std::stoi(passport.at("byr"));
        if (byr < 1920 or byr > 2002) {
            return false;
        }

        int iyr = std::stoi(passport.at("iyr"));
        if (iyr < 2010 or iyr > 2020) {
            return false;
        }

        int eyr = std::stoi(passport.at("eyr"));
        if (eyr < 2020 or eyr > 2030) {
            return false;
        }

        auto hgtString = passport.at("hgt");
        int hgt = std::stoi(hgtString);
        auto unit = std::string{hgtString[hgtString.size() - 2]} + hgtString[hgtString.size() - 1];
        if (unit == "cm") {
            if (hgt < 150 or hgt > 193) {
                return false;
            }
        } else if (unit == "in") {
            if (hgt < 59 or hgt > 76) {
                return false;
            }
        } else {
            return false;
        }

        auto hcl = passport.at("hcl");
        if (hcl[0] != '#' or hcl.size() != 7) {
            return false;
        }

        for (auto i=1; i<hcl.size(); ++i) {
            auto c = hcl[i];
            if (c < '0' or (c > '9' and c < 'a') or c > 'f') {
                return false;
            }
        }

        auto ecl = passport.at("ecl");
        if (ecl != "amb" and ecl != "blu" and ecl != "brn" and ecl != "gry" and ecl != "grn" and ecl != "hzl" and
            ecl != "oth") {
            return false;
        }

        auto pidString = passport.at("pid");
        auto pid = std::stol(pidString);
        if (pidString.size() != 9) {
            return false;
        }
    } catch (const std::invalid_argument &e) {
        return false;
    }
    return true;
}

int main() {
    auto passports = parseFile("input");
    auto corrPassports = 0U;

    for (const auto &passport : passports) {
        std::map<std::string, bool> fieldsExist{
                {"byr", false},
                {"iyr", false},
                {"eyr", false},
                {"hgt", false},
                {"hcl", false},
                {"ecl", false},
                {"pid", false}
        };

        for (const auto &[key, _] : passport) {
            auto it = fieldsExist.find(key);
            if (it != fieldsExist.end()) {
                it->second = true;
            }
        }

        bool allExist = true;
        for (const auto &[_, exist] : fieldsExist) {
            if (!exist) {
                allExist = false;
                break;
            }
        }

        if (allExist and verifyPassport(passport))
            corrPassports += 1;
        }

        std::cout << corrPassports << std::endl;
        return 0;
    }
