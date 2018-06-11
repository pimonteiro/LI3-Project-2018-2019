package engine;

import java.time.LocalDate;
import java.time.LocalTime;
import java.util.*;
import java.util.function.Function;
import java.util.stream.Collectors;

public class Query11 {

    static List<Long> mostUsedBestRep(Main_Struct cum, int N, LocalDate begin, LocalDate end){

        TreeSet<Profile> topProfiles = new TreeSet<>(Comparator.comparingInt(Profile::getReputation));
        topProfiles.addAll(cum.getProfiles().values());


        Map<String,Long> tags = topProfiles.stream()
                                           .limit(N)
                                           .map(Profile::getPosts)
                                           .flatMap(set -> set.stream()
                                                              .filter(p -> p.isBetweenDates(begin.atStartOfDay(),
                                                                                            end.atTime(LocalTime.MAX))
                                                                           && (p instanceof Question))
                                                              .map(Question.class::cast).map(Question::getTags)
                                                              .map(f -> (f.split(
                                                                      "<(.*?)><(.*?)><(.*?)><(.*?)><(.*?)>")))
                                                              .flatMap(Arrays::stream)

                                           )
                                           .collect(Collectors.groupingBy(Function.identity(), Collectors.counting()));


        return null;
    }
}
