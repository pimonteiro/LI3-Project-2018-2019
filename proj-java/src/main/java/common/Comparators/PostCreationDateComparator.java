package common.Comparators;

import engine.Post;

import java.util.Comparator;

/**
 *  @brief Método que dados 2 posts retorna o mais recente de data de criação
 *  @param p1,p2 2 posts distintos
 *  @return comparação entre 2 posts
 */

public class PostCreationDateComparator implements Comparator<Post> {

    public int compare(Post p1, Post p2){
        //if(p1.getCreation_date().equals(p2.getCreation_date())) return -1;
        return p2.getCreation_date().compareTo(p1.getCreation_date());
    }
}
