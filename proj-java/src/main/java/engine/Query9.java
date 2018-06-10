package engine;

import common.NoProfileFoundException;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.TreeSet;

public class Query9 {

    public static List<Long> bothParticipated(Main_Struct com, int N, long id1, long id2) throws NoProfileFoundException{
        Profile p1 = com.getProfile(id1);
        if(p1.getN_posts() == 0) return new ArrayList<>();
        Profile p2 = com.getProfile(id2);
        if(p2.getN_posts() == 0) return new ArrayList<>();

        TreeSet<Post> posts = p1.getPosts();
        Iterator<Post> it = posts.iterator();

        return null;

    }
}
