package engine;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.TreeSet;

public class Query8 {

    public static List<Long> containsWord(Main_Struct com, int N, String word){
        TreeSet<Post> seq = com.getAllPosts();
        // TODO
        if(seq.isEmpty()) return new ArrayList<>();

        List<Long> ret = new ArrayList<>();
        Iterator<Post> it = seq.iterator();
        boolean flag = false;
        while(it.hasNext() && !flag){
            Question q = (Question) it.next();
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
