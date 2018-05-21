import java.util.HashMap;
import java.util.TreeSet;

public class Query2 {
    public void top_most_active(Main_Struct com, int N){
        HashMap<Long,Profile> profiles = com.getProfiles();
        BoundedTreeSet<Profile> ret = new BoundedTreeSet<>(N, new ProfileNPostsComparator());

        profiles.values().forEach(p -> ret.add(p.clone()));

        //TODO agora converter para o tipo de dados deles

    }
}
