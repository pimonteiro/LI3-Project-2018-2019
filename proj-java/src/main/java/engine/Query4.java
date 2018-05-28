package engine;

import java.util.Date;
import java.util.List;
import java.util.TreeSet;
import java.util.stream.Collectors;
import common.*;

public class Query4 {
    public void questions_with_tag(Main_Struct com, String tag, Date begin, Date end){
        TreeSet<Question> seq = new TreeSet<>(); //A mudar no futuro
        if(seq.isEmpty()) return;

        List<Question> ret = seq.stream().filter(q -> q.getTags().contains(tag)).collect(Collectors.toList());
        //TODO Converter para o tipo de retorno
    }
}
