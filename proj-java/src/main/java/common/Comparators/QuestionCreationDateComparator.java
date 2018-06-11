package common.Comparators;

import engine.Question;

import java.util.Comparator;

/**
 *  @brief Método que dadas 2 questões retorna a mais recente de data de criação
 *  @param q1,q2 2 questões distintas
 *  @return comparação entre 2 questões
 */

public class QuestionCreationDateComparator implements Comparator<Question> {

    public int compare(Question q1, Question q2){
        return q2.getCreation_date().compareTo(q1.getCreation_date());
    }
}
