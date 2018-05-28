package common;

import java.util.Comparator;

public class ProfileNPostsComparator implements Comparator<Profile>{
    public int compare(Profile p1, Profile p2){
        return (int) (p2.getN_posts() - p1.getN_posts()); //Ordem decrescente de posts
    }
}
