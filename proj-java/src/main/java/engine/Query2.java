package engine;

import common.Comparators.ProfileNPostsComparator;

import java.util.HashMap;
import java.util.List;
import java.util.TreeSet;
import java.util.stream.Collectors;

public class Query2 {

    public static List<Long> top_most_active(Main_Struct com, int N){
        HashMap<Long,Profile> profiles = com.getProfiles();
        TreeSet<Profile> ret = new TreeSet<>(new ProfileNPostsComparator());

        ret.addAll(profiles.values());

        /* O Iterator entra aqui:
            stream -> getID para todos -> corta N
            iterator -> vai percorrendo e contando -> chega a N para


            como fizeste na query8
         */
        return ret.stream().map(Profile::getId)
                  .limit(N)
                  .collect(Collectors.toList());
    }
}