package engine;

import common.Comparators.AnwserScoreComparator;

import java.time.LocalDate;
import java.time.LocalTime;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.TreeSet;

public class Query6 {

    /**
     * @brief Procura as Answer com mais votos(maior score)
     * Usando a Tardis para ter as repostas entre as datas pedidas(já ordenadas por score), adicionam-se N ou menos a uma lista
     * de IDs para retornar.
     * @param com Estrutura com os dados.
     * @param N Número de Answers
     * @param begin Data de inicio
     * @param end Data do fim
     * @return Lista com os IDs das respostas.
     */
    public static List<Long> mostVotedAnswers(Main_Struct com, int N, LocalDate begin, LocalDate end){
        TreeSet<? extends Post> seq = com.getPostsBetweenDate(
                begin.atStartOfDay(),
                end.atTime(LocalTime.MAX),
                new AnwserScoreComparator(),
                null,
                Answer.class);

        if(seq.size() == 0) return new ArrayList<>();

        int i = 0;
        List<Long> ret = new ArrayList<>();
        Iterator<? extends Post> it = seq.iterator();
        while(it.hasNext() && i < N){
            Answer a = (Answer) it.next();
            ret.add(a.getId());
            i++;
        }

        return ret;
    }
}
