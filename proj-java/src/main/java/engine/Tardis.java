package engine;


import java.time.LocalDateTime;
import java.util.*;
import java.util.stream.Collectors;

public class Tardis {

    private Map<Long,Map<Long,List<Post>>> posts;

    public Tardis(){
        this.posts = new HashMap<>();
    }

    public void insert(Object o){
        if(!(o instanceof Post)) return;
        Post tmp = (Post) o;

        long index_year = tmp.getCreation_date().getYear() - 2008;
        long index_mes = (tmp.getCreation_date().getDayOfMonth() - 1) + (31 * (tmp.getCreation_date().getMonthValue()
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
        posts.add(tmp);
    }


    // 0 - Questions and Answers
    // 1 - Questions
    // 2 - Answers
    public <E extends Post> TreeSet<E> getBetweenBy(LocalDateTime start, LocalDateTime end, Comparator<Answer> an,
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
            return (TreeSet<E>) returnQuestion;

        }
        if(type == Answer.class){
            TreeSet<Answer> returnAnswer = new TreeSet<>(an);
            List<Answer> la = tmp.stream()
                                 .filter(Answer.class::isInstance)
                                 .map(Answer.class::cast)
                                 .collect(Collectors.toList());
            returnAnswer.addAll(la);
            return (TreeSet<E>) returnAnswer;
        }

        if(type == Post.class){
            return (TreeSet<E>) new TreeSet<Post>(tmp);
        }
        return null;




     /*  List<Post> tmp = new ArrayList<>();

        Map<Long,List<Post>> anos = this.posts.get(index_ano_inicio);
        while(index_ano_inicio <= index_ano_fim){
            while(dia_inicio + 1 + (mes_inicio + 1) * 31 <= dia_fim + 1 + (mes_fim + 1) * 31){
                if(anos == null) break;
                if(anos.containsKey(index_mes_inicio)){
                    tmp.addAll(anos.get(index_ano_inicio));
                }
                if(dia_inicio < 31) ++dia_inicio;
                if(dia_inicio == 31 && mes_inicio < 11){
                    ++mes_inicio;
                    dia_inicio = 0;
                }
                index_mes_inicio = dia_inicio + (31 * mes_inicio);
            }
            dia_inicio = 0;
            mes_inicio = 0;

            anos = this.posts.get(++index_ano_inicio);
        }

        */

    }


}
