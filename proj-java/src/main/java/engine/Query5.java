package engine;

import java.util.List;
import java.util.TreeSet;
import common.*;

public class Query5 {

    public void get_user_info(Main_Struct com, long id) throws NoProfileFoundException {
        TreeSet<Post> post_history = new TreeSet<>(new PostCreationDateComparator());

        Profile p = com.getProfile(id);
        StringBuilder aboutme = new StringBuilder();
        aboutme.append(p.getAbout_me());

        List<Long> pts = p.getPosts().stream().map()
    }
}
