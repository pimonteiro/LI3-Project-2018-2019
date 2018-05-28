package engine;

import common.*;

public class Query1 {

    private Pair<String,String> get_info_from_post(Main_Struct com, Question q) throws NoProfileFoundException {
        String titulo = q.getTitle();
        String name;

        long owner_id = q.getOwner_id();
        Profile p = com.getProfile(owner_id);
        name = p.getName();

        return new Pair<>(titulo,name);

    }

    public Pair<String,String> info_from_post(Main_Struct com, long id) throws NoPostFoundException, NoProfileFoundException {
        Post p = com.getPost(id);
        Pair<String,String> ret;
        if(p.getType() == 1){
            ret = get_info_from_post(com, (Question) p);
        }else{
            long parent_id = ((Answer) p).getParent_id();
            Question q = (Question) com.getPost(parent_id);
            ret = get_info_from_post(com, q);
        }
        return ret;
    }
}
