#ifndef HANDLER_H
#define HANDLER_H

#include <stack>
#include <string>

/**
 * \brief This struct represents instructions. Instructions are simple objects,
 * which two fields, which shall be used to determine the action of the handler.
 */
struct Instruction {
  Instruction(std::string argMsg, int argVal): msg(argMsg), value(argVal) {}
  const std::string msg;
  const int value;
};

/**
 * \brief This is the abstract class that implements Handlers. A handler has a
 * reference to a stack and to the next handler in the chain of responsibility.
 */
class Handler {
  public:
    Handler(Handler *next, std::stack<int> *stack): _next(next), _stack(stack) {
    }
    /**
     * \brief The virtual destructor. It deletes all the other handlers, via
     * a recursive call.
     */
    virtual ~Handler() {
      if (_next) {
        delete _next;
      }
    }
    /**
     * \brief This is the core method of the Chain of Responsibility pattern.
     * The handle method receveis an instruction, and, if this object "knows"
     * how to handle it, some action is performed, otherwise, the instruction
     * is simply sent to the next handler.
     * \param inst the Instruction that must be handled.
     */
    virtual void handle(Instruction* inst) = 0;
  protected:
    std::stack<int> *_stack; ///< The stack of the virtual machine.
    Handler* _next; ///< The next handler in the chain of responsibility.
};

class HandlerAdd : public Handler {
  public:
    HandlerAdd(Handler *next, std::stack<int> *stack): Handler(next, stack) {}
    /**
     * \brief handles an add instruction. Handling an add instruction
     * involves: reading and removing the two top values in the stack (call them
     * v1 and v2). Adding v1 and v2 (call the result v), pushing v onto the
     * stack.
     * An error happens if the stack contains less than two elements.
     */
    void handle(Instruction* inst) override;
};

class HandlerMul : public Handler {
  public:
    HandlerMul(Handler *next, std::stack<int> *stack): Handler(next, stack) {}
    /**
     * \brief handles a mul instruction. Handling a mul instruction
     * involves: reading and removing the two top values in the stack (call them
     * v1 and v2). Multiplying v1 and v2 (call the result v), pushing v onto the
     * stack.
     * An error happens if the stack contains less than two elements.
     */
    void handle(Instruction* inst) override;
};

class HandlerPop : public Handler {
  public:
    HandlerPop(Handler *next, std::stack<int> *stack): Handler(next, stack) {}
    /**
     * \brief handles a pop instruction. Handling a pop instruction
     * consists of simply removing the value that is on the top of the stack.
     * An error happens if the stack is empty.
     */
    void handle(Instruction* inst) override;
};

class HandlerPrint : public Handler {
  public:
    HandlerPrint(Handler *next, std::stack<int> *stack): Handler(next, stack) {}
    /**
     * \brief handles a print instruction. Handling a print instruction
     * consists of simply printing the value that is on the top of the stack.
     * That element is not removed by this action.
     * An error happens if the stack is empty.
     */
    void handle(Instruction* inst) override;
};

class HandlerPush : public Handler {
  public:
    HandlerPush(Handler *next, std::stack<int> *stack): Handler(next, stack) {}
    /**
     * \brief handles a push instruction. Handling a push instruction
     * consists of adding its parameters onto the top of the stack.
     */
    void handle(Instruction* inst) override;
};

#endif