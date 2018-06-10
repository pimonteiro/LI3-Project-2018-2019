package engine;

import java.util.*;
import java.util.stream.Collectors;
//TODO FALTA RECEBER O POSTS DECENTES
public class Query4 {
    public List<Long> questions_with_tag(Main_Struct com, String tag, Date begin, Date end){
        TreeSet<Question> seq = new TreeSet<>(); //A mudar no futuro
        if(seq.isEmpty()) return new ArrayList<>();

        List<Long> ret = seq.stream().filter(q -> q.getTags().contains(tag)).map(q -> q.getId()).collect(Collectors.toList());

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
