#include <iostream>
#include <cmath>
#include <ctime>

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

float getFloat(string message)
{
  print(message);
  float number;
  cin >> number;

  return number;
}

unsigned getBoundedRandom(unsigned from, unsigned to)
{
  unsigned rangeSize = (to - from) + 1;
  int random = rand();
  unsigned randomInRange = random % rangeSize;
  unsigned randomValue = from + randomInRange;

  return randomValue;
}

// --- END: Liberary ---



void printResult(bool correctness, float typical_answer)
{
  if(correctness)
  {
    print("\033[42m\033[2J\033[H");
    printLine("Right Answer :-)");
  }
  else
  {
    print("\a\033[41m\033[2J\033[H");
    printLine("Wrong Answer :-(");
    printLine("The right answer is: " + to_string(typical_answer));
  }
}

enum Type {TYPE_ADD = 1, TYPE_SUB = 2, TYPE_MUL = 3, TYPE_DEV = 4, TYPE_MIX = 5};

enum Level {EASY = 1, MED = 2, HARD = 3, LEVEL_MIX = 4};

struct GameSettings {
  short questions_number;
  Level level;
  Type type;
};

enum Operator {OPERATOR_ADD = 1, OPERATOR_SUB = 2, OPERATOR_MUL = 3, 
  OPERATOR_DEV = 4};

struct Operands {
  short left;
  short right;
};

struct Question {
  Operands operands;
  Operator q_operator;
};

float calculator(Question question)
{
  float left_operand = (float) question.operands.left;
  float right_operand = (float) question.operands.right;
  
  switch(question.q_operator)
  {
    case OPERATOR_ADD:
      return left_operand + right_operand;
    case OPERATOR_SUB:
      return left_operand - right_operand;
    case OPERATOR_MUL:
      return left_operand * right_operand;
    case OPERATOR_DEV:
      return left_operand / right_operand;
  }

  return left_operand + right_operand;
}

bool is_correct(Question question, float answer)
{
  float typical_answer = calculator(question);
  float diff = typical_answer - answer;

  return (diff >= -0.1 && diff <= 0.1);
}

char operator_to_string(Operator q_operator)
{
  char operators[4] = {'+', '-', '*', '/'};

  return operators[q_operator - 1];
}

void generate_question(Question question)
{
  printLine(to_string(question.operands.left));
  printLine(to_string(question.operands.right) + " " 
    + operator_to_string(question.q_operator));
  printLine("__________");
}

Operator get_operator(Type type)
{
  if(type == TYPE_MIX)
    return (Operator) (getBoundedRandom(1, 4));

  return (Operator) (type);
}

Operands get_operands(Level level, Operands operands)
{
  if(level == LEVEL_MIX)
    level = (Level) (getBoundedRandom(1, 3));

  short operand_level = pow(10, (level - 1));

  operands.left = getBoundedRandom(1 * operand_level, 10 * operand_level);
  operands.right = getBoundedRandom(1 * operand_level, 10 * operand_level);
  
  return operands;
}

Question get_question(Level level, Type type)
{
  Question question;
  Operands operands;
  question.operands = get_operands(level, operands);
  question.q_operator = get_operator(type);

  return question;
}

void createQuestionHeader(short question_number, short questions_number)
{
  printLine("Question [" + to_string(question_number) + "/" + 
    to_string(questions_number) + "]");
}

bool play_question(short question_number, GameSettings game_settings)
{
  createQuestionHeader(question_number, game_settings.questions_number); 
  printLine("");

  Question question = get_question(game_settings.level, game_settings.type);

  generate_question(question);
  float answer = getFloat("");
  bool correctness = is_correct(question, answer);
  printResult(correctness, calculator(question));

  return correctness;
}

void play_questios(GameSettings game_settings)
{
  for(int num = 1; num <= game_settings.questions_number; ++num)
  {
    play_question(num, game_settings);
    
  }
}

Level get_questions_level()
{
  short level = getBoundedIntegerUntil(1, 4, 
    "Enter questions level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ",
    "Wrong input, please try again...");
  
  return (Level) level;
}

Type get_questions_type()
{
  short type = getBoundedIntegerUntil(1, 5, 
    "Entery questions type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ",
    "Wrong input, please try again...");

  return (Type) type;
}

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
  srand(time(nullptr));
  GameSettings game_settings = get_game_settings();
  printLine("");
  play_questios(game_settings);
  setDefaultTerminal();
} 