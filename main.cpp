#include <iostream>

using namespace std;

// --- START: Liberary ---
bool isIntegerBetween(long long number, long long from, long long to)
{
  return (number >= from && number <= to);
}

void print(string message)
{
  cout << message;
}

void printLine(string message)
{
  print(message);
  cout << '\n';
}

long long getInteger(string message)
{
  print(message);
  long long number;
  cin >> number;

  return number;
}

long long getBoundedIntegerUntil(long long from, long long to, string message,
  string errorMessage)
{
  long long number = getInteger(message);

  while(!isIntegerBetween(number, from, to))
  {
    printLine(errorMessage);
    number = getInteger(message);
  }

  return number;
}

// --- END: Liberary ---
enum Level {EASY = 1, MED = 2, HARD = 3, LEVEL_MIX = 4};

Level get_questions_level()
{
  short level = getBoundedIntegerUntil(1, 4, 
    "Enter questions level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ",
    "Wrong input, please try again...");
  
  return (Level) level;
}

enum Type {ADD = 1, SUB = 2, MUL = 3, DEV = 4, TYPE_MIX = 5};

Type get_questions_type()
{
  short type = getBoundedIntegerUntil(1, 5, 
    "Entery questions type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ",
    "Wrong input, please try again...");

  return (Type) type;
}

struct GameSettings {
  short questions_number;
  Level level;
  Type type;
};

void setDefaultTerminal()
{
  print("\033[49m\033[2J\033[H");
}

GameSettings get_game_settings()
{
  setDefaultTerminal();
  
  GameSettings game_settings;

  short questions_number = getBoundedIntegerUntil(1, 100, 
    "How many questions do you want to answer (1 -> 100)? ", 
    "Wrong input, please try again...");
  game_settings.questions_number = questions_number;

  Level level = get_questions_level();
  game_settings.level = level;

  Type type = get_questions_type();
  game_settings.type = type;

  return game_settings;
}
int main()
{
  GameSettings game_settings = get_game_settings();
} 