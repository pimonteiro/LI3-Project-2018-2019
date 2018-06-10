package engine;

import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.stream.Collectors;

import common.*;

public class Query2 {

    public List<Long> top_most_active(Main_Struct com, int N){
        HashMap<Long, Profile> profiles = com.getProfiles();
        BoundedTreeSet<Profile> ret = new BoundedTreeSet<>(N, new ProfileNPostsComparator());

        profiles.values().forEach(p -> ret.add(p.clone()));
        return ret.stream().map(p -> p.getId()).collect(Collectors.toList());
    }

/*    public List<Long> top_most_active(Main_Struct com, int N){
        HashMap<Long, Profile> profiles = com.getProfiles();
        BoundedTreeSet<Profile> ret = new BoundedTreeSet<>(N, new ProfileNPostsComparator());

        Iterator<Profile> it = profiles.values().iterator();
        while(it.hasNext()){
            Profile q = (Profile) it.next();
            ret.add(q);
        }

        return ret.stream().map(p -> p.getId()).collect(Collectors.toList());
    }*/
}
