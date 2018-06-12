package engine;

import common.Exceptions.NoProfileFoundException;
import common.Pair;

import java.util.List;
import java.util.TreeSet;
import java.util.stream.Collectors;

public class Query5 {

    /**
     * @brief Devolve a Bio e os últimos 10 posts de um utilizador.
     * Depois de ir buscar ao HashMap da estrutura principal o utilizador, retorna se um par com a bio e os útltimos 10 posts.
     * Durante o parsing, o útilizador vai sendo atualizado com os posts em que aparece, por ordem decrescente.
     * @param com Estrutura com os dados.
     * @param id ID do utilizador.
     * @return Par com a bio e uma lista dos IDs dos últimos 10 posts deste.
     * @throws NoProfileFoundException Caso o utilizador não exista/já nao exista no banco de dados.
     */
    public static Pair<String,List<Long>> get_user_info(Main_Struct com, long id) throws NoProfileFoundException{
        Profile p = com.getProfile(id);

        TreeSet<Post> post_history = p.getPosts(10);

        List<Long> pts = post_history.stream().map(Post::getId).collect(Collectors.toList());
        return new Pair<>(p.getAbout_me(), pts);
    }

/*    public static Pair<String, List<Long>> get_user_info(Main_Struct com, long id) throws NoProfileFoundException {
        Profile p = com.getProfile(id);
        BoundedTreeSet<Post> post_history = p.getPosts();
        StringBuilder aboutme = new StringBuilder();
        aboutme.append(p.getAbout_me());

        List<Long> pts = new ArrayList<>();
        Iterator it = post_history.iterator();
        while(it.hasNext()) {
            Post q = (Post) it.next();
            pts.add(q.getId());
        }
        return new Pair<>(aboutme.toString(), pts);
    }*/
}
