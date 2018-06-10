package engine;
import common.*;

import java.time.LocalDate;
import java.util.Date;
import java.util.TreeSet;

public class Query3 {

    public static Pair<Long,Long> totalPosts(Main_Struct com, LocalDate begin, LocalDate end){
        TreeSet<Post> posts = com.getPostsBetweenDate(
                begin.atStartOfDay(),
                end.atStartOfDay(),
                null,null, 0);
        Long a = posts.stream().filter(p -> p instanceof Answer).count();
        Long q = posts.stream().filter(p -> p instanceof Question).count();
        Pair<Long,Long> ret = new Pair<>(a,q);

        return ret;
    }
}
