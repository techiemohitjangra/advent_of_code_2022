#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define u64 uint64_t
#define i64 int64_t
#define u32 uint32_t
#define i32 int32_t
#define f32 std::float32_t
#define f64 std::float64_t
#define f128 std::float128_t

using namespace std;

class Rucksack {
    vector<char> first;
    vector<char> second;
    vector<char> complete;

  public:
    Rucksack();
    Rucksack(string str) {
        string str1 = str.substr(0, str.length() / 2);
        string str2 = str.substr(str.length() / 2);
        this->first = this->parse(str1);
        this->second = this->parse(str2);
        this->complete = this->parse(str);
    }

    u64 priorityPart1() {
        for (int i = 0; i < this->first.size(); i++) {
            if (this->first[i] != '0' && this->first[i] == this->second[i]) {
                return i + 1;
            }
        }
        return '0';
    }

    vector<char> parse(const string &str) {
        vector<char> col(52, '0');
        for (const char &c : str) {
            if (islower(c)) {
                col[(int)c % (int)'a'] = c;
            } else {
                col[(int)c % (int)'A' + 26] = c;
            }
        }
        return col;
    }
    static u64 priorityPart2(Rucksack &first, Rucksack &second, Rucksack &third) {
        for (int i = 0; i < first.getComplete().size(); i++) {
            if (first[i] != '0' && first[i] == second[i] && second[i] == third[i]) {
                return i + 1;
            }
        }
        return '0';
    }

    vector<char> getComplete() { return this->complete; }

    char operator[](int index) { return this->complete[index]; }
};

u64 solve1(string fileName) {
    u64 result = 0, prior = 0;

    std::ifstream file;
    file.open(fileName, std::ios::in);
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            Rucksack bag = Rucksack(line);
            result += bag.priorityPart1();
            result += prior;
        }
    }
    file.close();
    return result;
}

u64 solve2(string fileName) {
    u64 result = 0, prior = 0;

    std::ifstream file;
    file.open(fileName, std::ios::in);
    if (file.is_open()) {
        std::string line1, line2, line3;
        while (getline(file, line1) && getline(file, line2) && getline(file, line3)) {
            Rucksack bag1 = Rucksack(line1);
            Rucksack bag2 = Rucksack(line2);
            Rucksack bag3 = Rucksack(line3);
            result += Rucksack::priorityPart2(bag1, bag2, bag3);
        }
    }
    file.close();
    return result;
}
int main() {
    std::cout << "Part 1: " << solve1("input") << std::endl;
    std::cout << "Part 2: " << solve2("input") << std::endl;
    return 0;
}
