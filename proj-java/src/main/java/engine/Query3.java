package engine;

import common.Pair;

import java.time.LocalDate;
import java.util.TreeSet;

public class Query3 {

    /**
     * @param com   Estrutura com os dados.
     * @param begin Data de inicio dos posts.
     * @param end   Data de fim dos posts.
     * @return Par com o número de questoes e de respostas.
     *
     * @brief Calcula quantos posts de cada tipo existem entre as datas indicadas.
     * Usando a Tardis para pedir os posts entre as datas (já ordenadas), apenas contamos quantos sao do tipo Answer e
     * quantos do tipo
     * Question.
     */

    public static Pair<Long,Long> totalPosts(Main_Struct com, LocalDate begin, LocalDate end){
        TreeSet<? extends Post> posts = com.getPostsBetweenDate(
                begin.atStartOfDay(),
                end.atStartOfDay(),
                null, null, Post.class);

        Long a = posts.stream().filter(Answer.class::isInstance).count();
        Long q = posts.stream().filter(Question.class::isInstance).count();

        return new Pair<>(q, a);
    }
}
