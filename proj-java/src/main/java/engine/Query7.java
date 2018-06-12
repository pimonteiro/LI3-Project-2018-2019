package engine;

import common.Pair;

import java.time.LocalDate;
import java.time.LocalTime;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.TreeSet;
import java.util.stream.Collectors;

public class Query7 {

    private Query7(){}

    /**
     * @param q     Question a analisar
     * @param begin Data de inicio
     * @param end   Data do fim
     * @return Par com o numero de respostas entre as datas e o ID da Question.
     *
     * @brief Conta o número de respostas entre duas datas, de uma Question
     * Percorrendo cada resposta da pergunta, verificamos se esta está dentro das datas. Se estiver, incrementamos um
     * contador
     * para devolver no fim.
     */

    private static Pair<Integer,Long> count_answers(Question q, LocalDate begin, LocalDate end){
        int n = 0;
        Map<Long,Answer> ans = q.getAnswers();
        Iterator<Answer> it = ans.values().iterator();
        while(it.hasNext()){
            Answer a = it.next();
            if(a.isBetweenDates(begin.atStartOfDay(), end.atTime(LocalTime.MAX))){
                n++;
            }
        }
        return new Pair<>(n, q.getId());
    }

    /**
     * @param com   Estrutura com os dados.
     * @param N     Número de Posts
     * @param begin Data de inicio
     * @param end   Data do fim
     * @return Lista com os IDs das Questoes entre as datas pedidas, com mais respostas tambem entre estas datas.
     *
     * @brief Procura as Question com mais respostas entre as datas pedidas.
     * Tanto as Question como as Answer têm de estar entre as datas pedidas. Usando a Tardis para recolher
     * todas as Question entre as datas, para cada uma chama-se o metodo auxiliar que calcula o numero de repostas no
     * intervalo
     * de tempo. É adicionado o par resultante de cada uma a uma lista ordenada pelo maior número de respostas,
     * devolvendo apenas N.
     */

    public static List<Long> mostAnsweredQuestions(Main_Struct com, int N, LocalDate begin, LocalDate end){
        TreeSet<? extends Post> questions = com.getPostsBetweenDate(begin.atStartOfDay(), end.atTime(LocalTime.MAX),
                                                                    null, null, Question.class);

        TreeSet<Pair<Integer,Long>> tmp = new TreeSet<>((a, b) -> {
            int t = b.getFst() - a.getFst();
            if(t == 0) return 1;
            return t;
        });

        Iterator<? extends Post> it = questions.iterator();
        while(it.hasNext()){
            Question q = (Question) it.next();
            Pair<Integer,Long> pp = count_answers(q, begin, end);
            tmp.add(pp);
        }

        return tmp.stream().limit(N).map(Pair::getSnd).collect(Collectors.toList());
    }
}
