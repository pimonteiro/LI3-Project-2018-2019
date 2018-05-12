import java.util.Set;
import java.util.TreeSet;

public class Profile {

    private TreeSet<Post> posts;
    private String about_me;
    private String name;
    private long n_posts;
    private long id;
    private int reputation;

    public Profile(String about_me, String name, long n_posts, long id, int reputation, TreeSet<Post> posts){
        this.setPosts(posts);
        this.about_me = about_me;
        this.name = name;
        this.n_posts = n_posts;
        this.id = id;
        this.reputation = reputation;
    }

    public Profile(){
        this.posts = new TreeSet<>();
        this.about_me = "";
        this.name = "";
        this.n_posts = 0;
        this.id = 0;
        this.reputation = 0;
    }

    public Profile(Profile p){
        this.setPosts(p.getPosts());
        this.about_me = p.getAbout_me();
        this.name = p.getName();
        this.n_posts = p.getN_posts();
        this.id = p.getId();
        this.reputation = p.getReputation();
    }

    public Set<Post> getPosts(){
        Set<Post> ret = new TreeSet<>();
        this.posts.forEach(p -> ret.add(p.clone()));
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

    public void setPosts(Set<Post> posts){
        this.posts = new TreeSet<>();
        posts.stream().forEach(p -> this.posts.add(p.clone()));
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

    public Profile clone(){
        return new Profile(this);
    }

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

    public String toString(){
        return "Name: " + this.name + "AboutMe: " + this.about_me +
               "N_Posts: " + this.n_posts + "Reputation: " + this.reputation +
               "ID: " + this.id;
    }
}
