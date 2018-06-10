package engine;

import common.ProfileNPostsComparator;

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
<<<<<<< HEAD
        while (it.hasNext()) {
=======
        int i = 0;
        while(it.hasNext() && i < N){
>>>>>>> 3ff5c29f97bca7a69db11bfd4c7a72d86602c73a
            Profile q = it.next();
            ret.add(q);
        }
<<<<<<< HEAD
        return ret.stream().map(p -> p.getId())
                .limit(N)
                .collect(Collectors.toList());
=======
        return ret.stream().map(Profile::getId).collect(Collectors.toList());
>>>>>>> 3ff5c29f97bca7a69db11bfd4c7a72d86602c73a
    }
}