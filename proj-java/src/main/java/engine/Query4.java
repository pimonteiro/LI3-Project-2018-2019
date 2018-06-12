package engine;

import common.Comparators.QuestionCreationDateComparator;

import java.time.LocalDate;
import java.time.LocalTime;
import java.util.ArrayList;
import java.util.List;
import java.util.TreeSet;
import java.util.stream.Collectors;

public class Query4 {

    /**
     * @brief Procura as qestoes que possuem uma tag entre especificas datas, por ordem decrescente
     * Usando a Tardis para ter as questoes entre as datas (ja ordenadas), filtramos aquelas que tenham a tag na sua lista de tags.
     * @param com Estrutura com os dados.
     * @param tag Tag a ser procurada.
     * @param begin Data de inicio.
     * @param end Data do fim.
     * @return Lista de IDs de todas as questoes com a tag.
     */

    public static List<Long> questions_with_tag(Main_Struct com, String tag, LocalDate begin, LocalDate end){
        TreeSet<? extends Post> seq = com.getPostsBetweenDate(
                begin.atStartOfDay(),
                end.atTime(LocalTime.MAX),
                null, new QuestionCreationDateComparator(), Question.class);
        if(seq.isEmpty()) return new ArrayList<>();

        return seq.stream()
                  .filter(q -> ((Question) q).getTags().contains(tag))
                  .map(Post::getId)
                  .collect(Collectors.toList());
    }

/*
    public static List<Long> questions_with_tag(Main_Struct com, String tag, Date begin, Date end){
        TreeSet<Question> seq = new TreeSet<>(); //A mudar no futuro
        if(seq.isEmpty()) return new ArrayList<>();

        Iterator it = seq.iterator();
        List<Long> ret = new ArrayList<>();
        while(it.hasNext()){
            Question q = (Question) it.next();
            if(q.getTags().contains(tag))
                ret.add(q.getId());
        }
        return ret;
    }
*/
}
