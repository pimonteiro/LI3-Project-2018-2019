package engine;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.TreeSet;

public class Query8 {

    private Query8(){}

    /**
     * @param com  Estrutura com os dados.
     * @param N    Número de questoes.
     * @param word Palavra a verificar
     * @return Lista com os IDs das questoes que possuem.
     *
     * @brief Procura todas as questoes que contêm uma palavra no titulo, por ordem descendente.
     * Usando a Tardis para ter todas as questoes entre as datas, filtramos as que têm a palavra no titulo, até termos
     * N.
     */

    public static List<Long> containsWord(Main_Struct com, int N, String word){
        TreeSet<Question> seq = com.getAllQuestions();
        if(seq.isEmpty()) return new ArrayList<>();

        List<Long> ret = new ArrayList<>();
        Iterator<Question> it = seq.iterator();
        boolean flag = false;
        while(it.hasNext() && !flag){
            Question q = it.next();
            if(q.getTitle().contains(word)){
                if(ret.size() < N){
                    ret.add(q.getId());
                }
            }
            if(ret.size() == N) flag = true;
        }

        return ret;
    }
}
