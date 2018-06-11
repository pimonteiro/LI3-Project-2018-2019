package engine;

import common.Comparators.AnwserScoreComparator;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.TreeSet;

public class Query6 {

    public static List<Long> mostVotedAnswers(Main_Struct com, int N, LocalDate begin, LocalDate end){
        TreeSet<Answer> seq = com.getPostsBetweenDate(
                begin.atStartOfDay(),
                end.atStartOfDay(),
                new AnwserScoreComparator(),
                null,
                Answer.class);

        if(seq.size() == 0) return new ArrayList<>();

        int i = 0;
        List<Long> ret = new ArrayList<>();
        Iterator<Answer> it = seq.iterator();
        while(it.hasNext() && i < N){
            Answer a = it.next();
            ret.add(a.getId());
            i++;
        }

        return ret;
    }
}
