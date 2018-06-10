package engine;

import common.DateToLocalDate;
import common.QuestionCreationDateComparator;

import java.util.*;
import java.util.stream.Collectors;

public class Query4 {
    public List<Long> questions_with_tag(Main_Struct com, String tag, Date begin, Date end){
        TreeSet<Post> seq = com.getPostsBetweenDate(
                DateToLocalDate.dateToLocalDateTime(begin),
                DateToLocalDate.dateToLocalDateTime(end),
                null, new QuestionCreationDateComparator(), 1);
        if(seq.isEmpty()) return new ArrayList<>();

        List<Long> ret = seq.stream().filter(q -> ((Question)q).getTags().contains(tag)).map(q -> q.getId()).collect(Collectors.toList());

        return ret;
    }

/*
    public List<Long> questions_with_tag(Main_Struct com, String tag, Date begin, Date end){
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
