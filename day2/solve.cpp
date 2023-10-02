#include <fstream>
#include <iostream>
#include <istream>
#include <string>
#include <unordered_map>
#include <vector>

// A = X = rock
// B = Y = paper
// C = Z = scissor
class Round {
    char player1, player2;
    std::unordered_map<char, char> resolver;
    std::unordered_map<char, int> score;
    std::unordered_map<char, char> beats;

  public:
    Round(char player1, char player2) {
        this->player1 = player1;
        this->player2 = player2;

        resolver['X'] = 'A';
        resolver['Y'] = 'B';
        resolver['Z'] = 'C';

        score['A'] = 1;
        score['B'] = 2;
        score['C'] = 3;

        beats['A'] = 'C';
        beats['B'] = 'A';
        beats['C'] = 'B';
        //     std::cout << "\tRound started" << std::endl;
    }
    // ~Round() { std::cout << "\tRound ended" << std::endl; }

    char resolveMove(char player2) {
        if (this->resolver.find(player2) != this->resolver.end())
            return this->resolver[player2];
        return ' ';
    }

    int result() {
        if (this->player1 == this->resolveMove(this->player2)) {
            return 3 + score[this->resolveMove(this->player2)];
        }
        if (beats[this->player1] == this->resolveMove(this->player2)) {
            return 0 + score[this->resolveMove(this->player2)];
        }
        if (this->player1 == beats[this->resolveMove(this->player2)]) {
            return 6 + score[this->resolveMove(this->player2)];
        }
        return 0;
    }

    int correctedResult() {
        if (this->player2 == 'Y') {
            return 3 + score[this->player1];
        }
        if (this->player2 == 'X') {
            return 0 + score[beats[this->player1]];
        }
        if (this->player2 == 'Z') {
            return 6 + score[beats[beats[this->player1]]];
        }
        return 0;
    }
};

class Game {
    int totalScore;
    int correctedTotalScore;
    // std::vector<Round> rounds;

  public:
    Game() {
        this->totalScore = 0;
        this->correctedTotalScore = 0;
        // std::cout << "Game started" << std::endl;
    }
    // ~Game() { std::cout << "Game ended" << std::endl; }
    void addRound(Round &round) {
        // rounds.push_back(round);
        this->totalScore += round.result();
        this->correctedTotalScore += round.correctedResult();
    }

    int getScore() { return this->totalScore; }
    int getCorrectedScore() { return this->correctedTotalScore; }
};

int main(int argc, char **argv) {

    Game game;
    std::ifstream file;
    file.open("input", std::ios::in);
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            char p1, p2;
            p1 = line[0];
            p2 = line[2];
            Round round = Round(p1, p2);
            // std::cout << line << std::endl;
            game.addRound(round);
        }
    }
    std::cout << "Part 1 score: " << game.getScore() << std::endl;
    std::cout << "Part 1 score: " << game.getCorrectedScore() << std::endl;
    file.close();

    return 0;
}
