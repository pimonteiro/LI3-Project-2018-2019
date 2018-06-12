package common.Comparators;

import engine.Question;

import java.util.Comparator;

/**
 * @brief Comparador que compara duas questões em relação ao numero de respostas de cada uma, ordenando por ordem
 * decrescente.
 * @param q1 Questao a ser comparada
 * @param q2 Questao a ser comparada
 * @return Resultado da comparação
 */
public class QuestionAnswerCountComparator implements Comparator<Question> {

    public int compare(Question q1, Question q2){
        return (int) (q2.getN_answers() - q1.getN_answers());
    }
}
