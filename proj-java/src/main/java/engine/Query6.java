package engine;

import common.AnwserScoreComparator;
import common.DateToLocalDate;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.TreeSet;

public class Query6 {

    public List<Long> mostVotedAnswers(Main_Struct com, int N, LocalDate begin, LocalDate end) {
        TreeSet<Post> seq = com.getPostsBetweenDate(
                DateToLocalDate.dateToLocalDateTime(begin),
                DateToLocalDate.dateToLocalDateTime(end),
                new AnwserScoreComparator(),
                null,
                1);

        if(seq.size() == 0) return new ArrayList<>();

        int i = 0;
        List<Long> ret = new ArrayList<>();
        Iterator<Post> it = seq.iterator();
        while(it.hasNext() && i < N){
            Answer a = (Answer) it.next();
            ret.add(a.getId());
            i++;
        }

        return ret;
    }
}
