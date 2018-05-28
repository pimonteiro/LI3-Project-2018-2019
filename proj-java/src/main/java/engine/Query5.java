package engine;

import sun.reflect.generics.tree.Tree;

import java.util.ArrayList;
import java.util.List;
import java.util.TreeSet;
import common.*;

public class Query5 {

    public void get_user_info(Main_Struct com, long id) throws NoProfileFoundException {
        TreeSet<Post> post_history = new TreeSet<>(new PostCreationDateComparator());

        Profile p = com.getProfile(id);
        StringBuilder aboutme = new StringBuilder();
        aboutme.append(p.getAbout_me());

        //TODO Get 10 latest posts
    }
}
