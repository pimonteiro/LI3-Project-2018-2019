#include "post.h"
#include "answer.h"
#include "question.h"

struct post {
  size_t type; // 1 Question 2 Anser
  union content {
    QUESTION q;
    ANSWER a;
  }content;
};

// tens que ver se tipo = 1 ou = 2 para cada metodo e chamas o metodos correspondente
// do quesiton ou answer respectivamente
