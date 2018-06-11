package engine;

import common.Comparators.PostCreationDateComparator;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.TreeSet;

public class Query8 {

    public static List<Long> containsWord(Main_Struct com, int N, String word){
        TreeSet<Question> seq = com.getAllQuestions();
        if(seq.isEmpty()) return new ArrayList<>();

        TreeSet<Question> tmp = new TreeSet<>(new PostCreationDateComparator());
        seq.forEach(q -> tmp.add(q));

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
