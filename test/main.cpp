#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

const int WIDTH = 15;
const int HEIGHT = 15;

enum Direction { UP, DOWN, LEFT, RIGHT };

struct Cell {
  int x;
  int y;
  bool visited;
};

Direction getRandomDirection() {
  return static_cast<Direction>(rand() % 4);
}

bool isValidMove(const std::vector<std::vector<Cell>>& maze, int x, int y) {
  return x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT && !maze[x][y].visited;
}

void generateMaze(std::vector<std::vector<Cell>>& maze, int x, int y) {
  maze[x][y].visited = true;

  std::vector<Direction> directions = {UP, DOWN, LEFT, RIGHT};
  std::random_shuffle(directions.begin(), directions.end());

  for (const auto& direction : directions) {
    int newX = x;
    int newY = y;

    switch (direction) {
      case UP:
        newY -= 2;
        break;
      case DOWN:
        newY += 2;
        break;
      case LEFT:
        newX -= 2;
        break;
      case RIGHT:
        newX += 2;
        break;
    }

    if (isValidMove(maze, newX, newY)) {
      switch (direction) {
        case UP:
          maze[x][y - 1].visited = true;
          break;
        case DOWN:
          maze[x][y + 1].visited = true;
          break;
        case LEFT:
          maze[x - 1][y].visited = true;
          break;
        case RIGHT:
          maze[x + 1][y].visited = true;
          break;
      }

      generateMaze(maze, newX, newY);
    }
  }
}

void printMaze(const std::vector<std::vector<Cell>>& maze) {
  for (int i = 0; i < HEIGHT; ++i) {
    for (int j = 0; j < WIDTH; ++j) {
      if (maze[j][i].visited) {
        std::cout << "  ";
      } else {
        std::cout << "██";
      }
    }
    std::cout << std::endl;
  }
}

int main() {
  srand(static_cast<unsigned>(time(nullptr)));

  std::vector<std::vector<Cell>> maze(WIDTH, std::vector<Cell>(HEIGHT));

  for (int i = 0; i < WIDTH; ++i) {
    for (int j = 0; j < HEIGHT; ++j) {
      maze[i][j] = {i, j, false};
    }
  }

  generateMaze(maze, 1, 1);
  printMaze(maze);

  return 0;
}
