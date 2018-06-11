package engine;

import common.Exceptions.NoTagFoundException;

import java.time.LocalDate;
import java.time.LocalTime;
import java.util.*;
import java.util.function.Function;
import java.util.stream.Collectors;

public class Query11 {

    static List<Long> mostUsedBestRep(Main_Struct cum, int N, LocalDate begin, LocalDate end){

        TreeSet<Profile> topProfiles = new TreeSet<>(
                Comparator.comparing(Profile::getReputation, Comparator.reverseOrder()));
        topProfiles.addAll(cum.getProfiles().values());


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
                                  return cum.getTag(f);
                              }catch(NoTagFoundException e){
                                  return null;
                              }
                          }).filter(Objects::nonNull).collect(Collectors.toList());

    }
}
