package engine;

import common.Pair;

import java.time.LocalDate;
import java.util.TreeSet;

public class Query3 {

    public static Pair<Long,Long> totalPosts(Main_Struct com, LocalDate begin, LocalDate end){
        TreeSet<Post> posts = com.getPostsBetweenDate(
                begin.atStartOfDay(),
                end.atStartOfDay(),
                null, null, Post.class);
        Long a = posts.stream().filter(Answer.class::isInstance).count();
        Long q = posts.stream().filter(Question.class::isInstance).count();

        return new Pair<>(a, q);
    }
}
