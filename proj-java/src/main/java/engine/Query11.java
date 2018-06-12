package engine;

import common.Exceptions.NoTagFoundException;

import java.time.LocalDate;
import java.time.LocalTime;
import java.util.*;
import java.util.function.Function;
import java.util.stream.Collectors;

public class Query11 {

    private Query11(){

    }

    /**
     * @param com   Estrutura com os dados.
     * @param N     Delimitador
     * @param begin Data de começo
     * @param end   Data de fim
     * @return List de identificadores das tags
     *
     * @brief Seleciona os top N utilizadores, colhe os seus Posts, filtra-os pelas datas passadas, guarda todas as
     * tags
     * presentes juntamente com o numero de vezes que aparecem e por fim limita por N e converte para o identificador
     * correspondente
     */
    static List<Long> mostUsedBestRep(Main_Struct com, int N, LocalDate begin, LocalDate end){

        TreeSet<Profile> topProfiles = new TreeSet<>(
                Comparator.comparing(Profile::getReputation, Comparator.reverseOrder()));
        topProfiles.addAll(com.getProfiles().values());


        return topProfiles.stream()
                          .limit(N)
                          .map(Profile::getPosts)
                          .flatMap(set -> set.stream()
                                             .filter(p -> p.isBetweenDates(begin.atStartOfDay(),
                                                                           end.atTime(LocalTime.MAX))
                                                          && (p instanceof Question))
                                             .map(Question.class::cast)
                                             .map(Question::getTags)
                                             .flatMap(Collection::stream)

                          )
                          .collect(Collectors.groupingBy(Function.identity(), Collectors.counting()))
                          .entrySet()
                          .stream()
                          .sorted(Comparator.comparing(Map.Entry::getValue, Comparator.reverseOrder()))

                          .limit(N)
                          .map(Map.Entry::getKey)
                          .map(f -> {
                              try{
                                  return com.getTag(f);
                              }catch(NoTagFoundException e){
                                  return null;
                              }
                          })
                          .filter(Objects::nonNull)
                          .sorted()
                          .collect(Collectors.toList());

    }
}
