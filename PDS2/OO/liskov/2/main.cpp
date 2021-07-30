#include <stack>
#include <iostream>

#include "Handler.h"

Instruction* readNextInstruction() {
  std::string msg;
  if (std::cin >> msg) {
    int value = 0;
    if (msg == "push") {
      std::cin >> value;
    }
    return new Instruction(msg, value);
  }
  return NULL;
}

int main() {
  std::stack<int> *stack = new std::stack<int>();
  Handler *handler = new HandlerAdd(NULL, stack);
  handler = new HandlerMul(handler, stack);
  handler = new HandlerPop(handler, stack);
  handler = new HandlerPrint(handler, stack);
  handler = new HandlerPush(handler, stack);
  Instruction *inst;
  while ((inst = readNextInstruction())) {
    handler->handle(inst);
    delete inst;
  }
  delete stack;
  delete handler;
  return 0;
}