package engine;

import common.Comparators.PostCreationDateComparator;
import common.Exceptions.NoPostFoundException;
import common.Exceptions.NoProfileFoundException;
import common.Exceptions.NoTagFoundException;

import java.time.LocalDateTime;
import java.util.Comparator;
import java.util.HashMap;
import java.util.TreeSet;

/**
 * @brief Classe com a Estruta Principal como sendo 3 HashMaps para perfis,posts e tags e a Estrutura das Datas:Tardis.
 */

public class Main_Struct {

    private HashMap<Long,Profile> profiles;
    private HashMap<Long,Post> posts;
    private HashMap<String,Long> tags;
    private Tardis tardis64;

    /**
     * @brief Construtor vazio da Estrutura Principal
     */

    public Main_Struct(){
        this.profiles = new HashMap<>();
        this.posts = new HashMap<>();
        this.tags = new HashMap<>();
        this.tardis64 = new Tardis();
    }

    /**
     * @brief Construtor por cópia da Estrutura Principal
     */

    public Main_Struct(Main_Struct ms){
        this.profiles = ms.getProfiles();
        this.posts = ms.getPosts();
        this.tags = ms.getTags();
        this.tardis64 = ms.tardis64;
    }

    /**
     * @brief Getters da Estrutura Principal
     */

    public HashMap<Long,Profile> getProfiles(){
        HashMap<Long,Profile> ret = new HashMap<>();
        for(Profile p : this.profiles.values()){
            ret.put(p.getId(), p);
        }
        return ret;
    }

    public HashMap<Long,Post> getPosts(){
        HashMap<Long,Post> ret = new HashMap<>();
        for(Post p : this.posts.values()){
            if(p instanceof Answer){
                ret.put(p.getId(), p);
            }else{
                ret.put(p.getId(), p);
            }
        }
        return ret;
    }

    public HashMap<String,Long> getTags(){
        HashMap<String,Long> ret = new HashMap<>();
        for(String s : this.tags.keySet()){
            ret.put(s, this.tags.get(s));
        }
        return ret;
    }

    public TreeSet<Question> getAllQuestions(){
        TreeSet<Question> tmp = new TreeSet<>(new PostCreationDateComparator());
        this.posts.values()
                  .stream()
                  .filter(Question.class::isInstance)
                  .map(Question.class::cast)
                  .forEach(tmp::add);


        return tmp;
    }


    public TreeSet<Answer> getAllAnswers(){
        TreeSet<Answer> tmp = new TreeSet<>(new PostCreationDateComparator());
        this.posts.values()
                  .stream()
                  .filter(Answer.class::isInstance)
                  .map(Answer.class::cast)
                  .forEach(tmp::add);


        return tmp;
    }

    public TreeSet<Post> getAllPosts(){
        return this.tardis64.getAll();
    }

    /**
     * @brief Dado um post verifica se o mesmo está entre 2 datas
     */

    public <T extends Post> TreeSet<? extends Post> getPostsBetweenDate(LocalDateTime start, LocalDateTime end,
                                                                        Comparator<Answer> an,
                                                                        Comparator<Question> ques, Class<T> type){
        return this.tardis64.getBetweenBy(start, end, an, ques, type);
    }

    public Profile getProfile(long id) throws NoProfileFoundException{
        Profile p = this.profiles.get(id);
        if(p == null){
            throw new NoProfileFoundException();
        }
        return p.clone();
    }

    public Post getPost(long id) throws NoPostFoundException{
        Post p = this.posts.get(id);
        if(p == null){
            throw new NoPostFoundException();
        }
        return p.clone();
    }

    public long getTag(String tag) throws NoTagFoundException{
        Long id = this.tags.get(tag);
        if(id == null){
            throw new NoTagFoundException();
        }
        return id;
    }

    /**
     * @param p Perfil a adicionar
     * @brief Adiciona um perfil à HashMap de perfis.
     */

    public void addProfile(Profile p){
        if(!this.profiles.containsKey(p.getId()))
            this.profiles.put(p.getId(), p);
    }


    /**
     * @param a Answer a adicionar
     * @brief Adiciona uma answer à HashMap de answers.
     */

    public void addAnswer(Answer a){
        if(!this.posts.containsKey(a.getId()))
            this.posts.put(a.getId(), a);

        tardis64.insert(a);

        Question q = (Question) this.posts.get(a.getParent_id());
        if(q != null)
            q.addAnswer(a);

        Profile p = this.profiles.get(a.getOwner_id());
        if(p != null)
            p.addPost(a);

    }


    /**
     * @param q Questão a adicionar
     * @brief Adiciona uma questão à HashMap de questões.
     */

    public void addQuestion(Question q){
        if(!this.posts.containsKey(q.getId()))
            this.posts.put(q.getId(), q);

        tardis64.insert(q);

        Profile p = this.profiles.get(q.getOwner_id());
        if(p != null)
            p.addPost(q);

    }

    /**
     * @brief Adiciona uma tag à HashMap de tags.
     */

    public void addTag(long id, String s){
        if(!this.tags.containsKey(s))
            this.tags.put(s, id);
    }
}
