package engine;

import common.Comparators.AnswerCountComparator;
import common.Pair;

import java.time.LocalDate;
import java.time.LocalTime;
import java.util.*;
import java.util.stream.Collectors;

public class Query7 {

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

    public static List<Long> mostAnsweredQuestions(Main_Struct com, int N, LocalDate begin, LocalDate end){
        TreeSet<? extends Post> questions = com.getPostsBetweenDate(begin.atStartOfDay(), end.atTime(LocalTime.MAX), null, null, Question.class);

        TreeSet<Pair<Integer,Long>> tmp = new TreeSet<>((a,b) -> {
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
