package engine;


import java.time.LocalDateTime;
import java.util.*;
import java.util.stream.Collectors;


/**
 * @brief Class usada para guardar os Posts tendo por base o tempo
 */
public class Tardis {

    /**
     * Variavel de instancia que guarda os posts
     */
    private Map<Long,Map<Long,List<Post>>> posts;

    /**
     * Construtor vazio
     */
    public Tardis(){
        this.posts = new HashMap<>();
    }

    /**
     * Insere um Post na estrutua
     * @param o
     */
    public void insert(Post o){
        long index_year = o.getCreation_date().getYear() - 2008;
        long index_mes = (o.getCreation_date().getDayOfMonth() - 1) + (31 * (o.getCreation_date().getMonthValue()
                                                                             - 1));
        Map<Long,List<Post>> anos = this.posts.get(index_year);
        if(anos == null){
            this.posts.put(index_year, new HashMap<>());
            anos = this.posts.get(index_year);
        }

        List<Post> posts = anos.get(index_mes);
        if(posts == null){
            anos.put(index_mes, new ArrayList<>());
            posts = anos.get(index_mes);
        }

        posts.add(o);
    }

    /**
     * Retorna todos os posts
     * @return TreeSet com os Posts
     */
    public TreeSet<Post> getAll(){
        return this.posts.values()
                         .stream()
                         .flatMap(f -> f.values()
                                        .stream()
                                        .flatMap(Collection::stream)

                         ).collect(Collectors.toCollection(TreeSet::new));
    }

    /**
     * Retorna TreeSets de Posts ou sub-classes de Post ordenados pelo comparator passado
     * @param start Data de começo
     * @param end Data de fim
     * @param an Critério de comparação para as respostas
     * @param ques Critério de comparação para as questões
     * @param type Class que determina o tipo de TreeSet a ser devolvido
     * @param <E> Genérico que restringe os tripos a Posts ou subclasses
     * @return Coonjunto de Posts ordenados
     */
    public <E extends Post> TreeSet<? extends Post> getBetweenBy(LocalDateTime start, LocalDateTime end,
                                                                 Comparator<Answer> an,
                                                                 Comparator<Question> ques, Class<E> type){


        long index_ano_inicio = start.getYear() - 2008;
        long mes_inicio = start.getMonthValue() - 1;
        long dia_inicio = start.getDayOfMonth() - 1;
        long index_mes_inicio = ((dia_inicio) + (31 * (mes_inicio)));

        long index_ano_fim = end.getYear() - 2008;
        long dia_fim = end.getDayOfMonth() - 1;
        long mes_fim = end.getMonthValue() - 1;
        long index_mes_fim = (dia_fim) + (31 * (mes_fim));


        List<Post> tmp = this.posts.entrySet()
                                   .stream()
                                   .filter(f -> f.getKey() >= index_ano_inicio && f.getKey() <= index_ano_fim)
                                   .map(Map.Entry::getValue)
                                   .flatMap(f -> f.entrySet()
                                                  .stream()
                                                  .filter(sf -> sf.getKey() >= index_mes_inicio
                                                                && sf.getKey() <= index_mes_fim)
                                                  .map(Map.Entry::getValue)
                                                  .flatMap(Collection::stream)

                                   ).collect(Collectors.toList());


        if(type == Question.class){
            TreeSet<Question> returnQuestion = new TreeSet<>(ques);
            List<Question> lq = tmp.stream()
                                   .filter(Question.class::isInstance)
                                   .map(Question.class::cast)
                                   .collect(Collectors.toList());
            returnQuestion.addAll(lq);
            return returnQuestion;

        }
        if(type == Answer.class){
            TreeSet<Answer> returnAnswer = new TreeSet<>(an);
            List<Answer> la = tmp.stream()
                                 .filter(Answer.class::isInstance)
                                 .map(Answer.class::cast)
                                 .collect(Collectors.toList());
            returnAnswer.addAll(la);
            return returnAnswer;
        }

        if(type == Post.class){
            return new TreeSet<Post>(tmp);
        }
        return null;

    }


}
