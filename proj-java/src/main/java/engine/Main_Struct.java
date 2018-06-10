package engine;

import common.NoPostFoundException;
import common.NoProfileFoundException;
import common.NoTagFoundException;

import java.time.LocalDateTime;
import java.util.Comparator;
import java.util.HashMap;
import java.util.TreeSet;

public class Main_Struct {

    private HashMap<Long,Profile> profiles;
    private HashMap<Long,Post> posts;
    private HashMap<String,Long> tags;
    private Tardis tardis64;

    public Main_Struct(){
        this.profiles = new HashMap<>();
        this.posts = new HashMap<>();
        this.tags = new HashMap<>();
    }

    public Main_Struct(Main_Struct ms){
        this.profiles = ms.getProfiles();
        this.posts = ms.getPosts();
        this.tags = ms.getTags();
    }

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
                ret.put(((Answer) p).getId(), p);
            }else{
                ret.put(((Question) p).getId(), p);
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

    public TreeSet<Post> getPostsBetweenDate(LocalDateTime start, LocalDateTime end, Comparator<Answer> an, Comparator<Question> ques, int type){
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

    public void addProfile(Profile p){
        if(!this.profiles.containsKey(p.getId()))
            this.profiles.put(p.getId(), p);
    }

    public void addAnswer(Answer a){
        if(!this.posts.containsKey(a.getId()))
            this.posts.put(a.getId(), a);

        // TODO INSERT TARDIS; INSERT IN QUESTION; INSERT USER
    }

    public void addQuestion(Question q){
        if(!this.posts.containsKey(q.getId()))
            this.posts.put(q.getId(), q);

        // TODO INSERT IN USER
    }

    public void addTag(long id, String s){
        if(!this.tags.containsKey(s))
            this.tags.put(s, id);
    }
}
