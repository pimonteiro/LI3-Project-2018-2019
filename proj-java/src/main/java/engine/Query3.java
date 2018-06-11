package engine;

import common.Pair;

import java.time.LocalDate;
import java.time.LocalTime;
import java.util.TreeSet;

public class Query3 {

    public static Pair<Long,Long> totalPosts(Main_Struct com, LocalDate begin, LocalDate end){
        TreeSet<? extends Post> posts = com.getPostsBetweenDate(
                begin.atStartOfDay(),
                end.atTime(LocalTime.MAX),
                null, null, Post.class);

        Long a = posts.stream().filter(Answer.class::isInstance).count();
        Long q = posts.stream().filter(Question.class::isInstance).count();

        return new Pair<>(q, a);
    }
}
