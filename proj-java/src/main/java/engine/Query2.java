package engine;

import common.Comparators.ProfileNPostsComparator;

import java.util.*;

public class Query2 {

    private Query2(){}

    /**
     * @param com Estrutura com os dados.
     * @param N   Número de perfis pretendidos.
     * @return Lista com os IDs dos n utilizadores.
     *
     * @brief Procura os top n utilizadores mais ativos.
     * Pegando em todos os perfis na estrutura principal, sao todos adicionados a uma TreeSet que organiza pelo número
     * de posts
     * que cada um possui.
     */

    public static List<Long> top_most_active(Main_Struct com, int N){
        HashMap<Long,Profile> profiles = com.getProfiles();
        TreeSet<Profile> ret = new TreeSet<>(new ProfileNPostsComparator());


        ret.addAll(profiles.values());


        List<Long> tmp = new ArrayList<>();
        long limit = N;
        for(Iterator<Profile> iterator = ret.iterator(); iterator.hasNext(); ){
            Profile profile = iterator.next();
            Long id = profile.getId();
            if(limit-- == 0) break;
            tmp.add(id);
        }

        return tmp;


    }
}