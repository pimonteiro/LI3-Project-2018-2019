import sun.applet.Main;

public class Query1 {

    public void get_info_from_post(Main_Struct com, Question q) throws NoProfileFound{
        String titulo = q.getTitle();
        String name;

        long owner_id = q.getOwner_id();
        Profile p = com.getProfile(owner_id);
        name = p.getName();

    }

    public void info_from_post(Main_Struct com, long id) throws NoPostFound, NoProfileFound{
        Post p = com.getPost(id);
        if(p.getType() == 1){
            get_info_from_post(com, (Question)p);
        }
        else{
            long parent_id = ((Answer) p).getParent_id();
            Question q = (Question) com.getPost(parent_id);
            get_info_from_post(com, q);
        }
    }
}
