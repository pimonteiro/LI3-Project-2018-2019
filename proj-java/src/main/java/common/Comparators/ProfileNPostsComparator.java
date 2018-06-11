package common.Comparators;

import engine.Profile;

import java.util.Comparator;

/**
 *  @brief Método que compara 2 utilizadores em relação ao seu número de posts
 *  @param p1,p2 2 perfis distintos
 *  @return Número posts ordenados por ordem decrescente
 */

public class ProfileNPostsComparator implements Comparator<Profile> {

    public int compare(Profile p1, Profile p2){
        if(p1.getN_posts() == p2.getN_posts()) return 1;
        return (int) (p2.getN_posts() - p1.getN_posts()); //Ordem decrescente de posts
    }
}
