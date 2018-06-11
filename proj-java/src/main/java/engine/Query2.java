package engine;

import common.Comparators.ProfileNPostsComparator;

import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.TreeSet;
import java.util.stream.Collectors;

public class Query2 {

    public static List<Long> top_most_active(Main_Struct com, int N){
        HashMap<Long,Profile> profiles = com.getProfiles();
        TreeSet<Profile> ret = new TreeSet<>(new ProfileNPostsComparator());

        Iterator<Profile> it = profiles.values().iterator();
        while (it.hasNext()) {
            Profile q = it.next();
            ret.add(q);
        }
        return ret.stream().map(p -> p.getId())
                .limit(N)
                .collect(Collectors.toList());
    }
}