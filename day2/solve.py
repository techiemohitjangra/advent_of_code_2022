class Player:
    __resolver: dict[str, str] = {'X': 'A', 'Y': 'B', 'Z': 'C'}

    def __init__(self, __move: str):
        if __move in self.__resolver:
            self.__move: str = self.__resolver[__move]
        else:
            self.__move: str = __move

    def getMove(self) -> str:
        return self.__move


class Round:
    __scores: dict[str, int] = {'A': 1, 'B': 2, 'C': 3}
    __beats: dict[str, str] = {'A': 'C', 'B': 'A', 'C': 'B'}

    def __init__(self, player1: Player, player2: Player):
        self.__player1: Player = player1
        self.__player2: Player = player2

    def result(self) -> int:
        if self.__player1.getMove() == self.__player2.getMove():
            return 3 + self.__scores[self.__player2.getMove()]
        if self.__beats[self.__player1.getMove()] == self.__player2.getMove():
            return 0 + self.__scores[self.__player2.getMove()]
        if self.__player1.getMove() == self.__beats[self.__player2.getMove()]:
            return 6 + self.__scores[self.__player2.getMove()]

        return 0

    def correctResult(self) -> int:
        if self.__player2.getMove() == 'B':
            return 3 + self.__scores[self.__player1.getMove()]
        if self.__player2.getMove() == 'A':
            return 0 + self.__scores[self.__beats[self.__player1.getMove()]]
        if self.__player2.getMove() == 'C':
            return 6 + self.__scores[self.__beats[self.__beats[self.__player1.getMove()]]]

        return 0


class Game:

    def __init__(self):
        self.__totalScore: int = 0
        self.__correctedTotalScore: int = 0

    def addRound(self, round: Round) -> None:
        self.__totalScore += round.result()
        self.__correctedTotalScore += round.correctResult()
        return None

    def getScore(self) -> int:
        return self.__totalScore

    def getCorrectedScore(self) -> int:
        return self.__correctedTotalScore


if __name__ == "__main__":
    with open("input", "r") as file:
        game = Game()
        for line in file.readlines():
            a, b = list(map(Player, line.strip().split()))
            round = Round(a, b)
            game.addRound(round)

        print(f"Final Score: {game.getScore()}")
        print(f"Final Corrected Score: {game.getCorrectedScore()}")

# part 2 unsolved
