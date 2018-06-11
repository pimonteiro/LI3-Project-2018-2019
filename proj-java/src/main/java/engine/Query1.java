package engine;

import common.Exceptions.NoPostFoundException;
import common.Exceptions.NoProfileFoundException;
import common.Pair;

public class Query1 {

    private static Pair<String,String> get_info_from_post(Main_Struct com, Question q) throws NoProfileFoundException{
        String titulo = q.getTitle();
        String name;

        long owner_id = q.getOwner_id();
        Profile p = com.getProfile(owner_id);
        name = p.getName();

        return new Pair<>(titulo, name);

    }

    public static Pair<String,String> info_from_post(Main_Struct com, long id) throws
                                                                               NoPostFoundException,
                                                                               NoProfileFoundException{
        Post p = com.getPost(id);
        Pair<String,String> ret;
        if(p instanceof Question){
            ret = get_info_from_post(com, (Question) p);
        }else{
            long parent_id = ((Answer) p).getParent_id();
            Question q = (Question) com.getPost(parent_id);
            ret = get_info_from_post(com, q);
        }
        return ret;
    }
}
