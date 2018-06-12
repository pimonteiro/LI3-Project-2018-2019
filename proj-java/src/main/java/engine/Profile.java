package engine;

import common.Comparators.PostCreationDateComparator;

import java.util.Iterator;
import java.util.Set;
import java.util.TreeSet;

/**
 * @brief Perfil de um utilizador.
 * Possui um TreeSet de posts ordenados por data (descendente), a bio, o nome, o número de posts, o ID e a reputação
 * deste.
 */

public class Profile {

    private TreeSet<Post> posts;
    private String about_me;
    private String name;
    private long n_posts;
    private long id;
    private int reputation;


    /**
     * @param String a bio, name O nome, n_posts O número de posts, id o ID,reputation A reputação e posts TreeSet com
     *               os posts
     *               deste.
     * @brief Construtor parametrizado do Perfil
     **/

    public Profile(String about_me, String name, long n_posts, long id, int reputation, TreeSet<Post> posts){
        this.setPosts(posts);
        this.about_me = about_me;
        this.name = name;
        this.n_posts = n_posts;
        this.id = id;
        this.reputation = reputation;
    }

    /**
     * @brief Construtor por cópia do Perfil
     */

    public Profile(String about_me, String name, long id, int reputation){
        this.about_me = about_me;
        this.name = name;
        this.id = id;
        this.reputation = reputation;
        this.posts = new TreeSet<>(new PostCreationDateComparator());
        this.n_posts = 0;
    }

    /**
     * @brief Construtor vazio do Perfil
     */

    public Profile(){
        this.posts = new TreeSet<>(new PostCreationDateComparator());
        this.about_me = "";
        this.name = "";
        this.n_posts = 0;
        this.id = 0;
        this.reputation = 0;
    }

    /**
     * @brief Construtor por cópia do Perfil
     */

    public Profile(Profile p){
        this.setPosts(p.getPosts());
        this.about_me = p.getAbout_me();
        this.name = p.getName();
        this.n_posts = p.getN_posts();
        this.id = p.getId();
        this.reputation = p.getReputation();
    }

    /**
     * @brief Getters de um Perfil
     */

    public TreeSet<Post> getPosts(){
        TreeSet<Post> ret = new TreeSet<>(new PostCreationDateComparator());
        this.posts.forEach(p -> ret.add(p.clone()));
        return ret;
    }

    public TreeSet<Post> getPosts(int N){
        TreeSet<Post> ret = new TreeSet<>(new PostCreationDateComparator());
        Iterator<Post> it = this.posts.iterator();
        boolean flag = false;
        while(it.hasNext() && !flag){
            Post p = it.next();
            if(ret.size() < N) ret.add(p.clone());
            if(ret.size() == N) flag = true;
        }

        return ret;
    }

    public String getAbout_me(){
        return this.about_me;
    }

    public String getName(){
        return this.name;
    }

    public long getN_posts(){
        return this.n_posts;
    }

    public long getId(){
        return this.id;
    }

    public int getReputation(){
        return this.reputation;
    }

    /**
     * @brief Setters de um Perfil
     */

    public void setPosts(Set<Post> posts){
        this.posts = new TreeSet<>(new PostCreationDateComparator());
        posts.forEach(p -> this.posts.add(p.clone()));
    }

    public void setAbout_me(String about_me){
        this.about_me = about_me;
    }


    public void setName(String name){
        this.name = name;
    }


    public void setN_posts(long n_posts){
        this.n_posts = n_posts;
    }


    public void setId(long id){
        this.id = id;
    }


    public void setReputation(int reputation){
        this.reputation = reputation;
    }

    /**
     * @brief Método clone de um Perfil
     */

    @Override
    public Profile clone(){
        return new Profile(this);
    }

    /**
     * @brief Método equals de um Perfil
     */

    public boolean equals(Object o){
        if(o == this) return true;
        if(o == null || o.getClass() != this.getClass()) return false;
        Profile p = (Profile) o;
        return this.about_me.equals(p.getAbout_me()) &&
               this.name.equals(p.getName()) &&
               this.n_posts == p.getN_posts() &&
               this.reputation == p.getReputation() &&
               this.id == p.getId();
    }

    /**
     * @brief Método toString de um Perfil
     */

    public String toString(){
        return "Name: " + this.name + "AboutMe: " + this.about_me +
               "N_Posts: " + this.n_posts + "Reputation: " + this.reputation +
               "ID: " + this.id;
    }

    /**
     * @param a Post a adicionar
     * @brief Adiciona um post ao Set de posts do utilizador.
     */

    public void addPost(Post a){
        this.posts.add(a);
        ++(this.n_posts);
    }
}
