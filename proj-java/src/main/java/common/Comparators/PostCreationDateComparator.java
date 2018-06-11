package common.Comparators;

import engine.Post;

import java.util.Comparator;

public class PostCreationDateComparator implements Comparator<Post> {

    public int compare(Post p1, Post p2){
        if(p1.getCreation_date().equals(p2.getCreation_date())) return -1;
        return p2.compareTo(p1);
    }
}
