package engine;

import common.Exceptions.NoPostFoundException;
import common.Exceptions.NoProfileFoundException;
import common.Exceptions.NoTagFoundException;

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
        this.tardis64 = ms.tardis64;
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

    public void addProfile(Profile p){
        if(!this.profiles.containsKey(p.getId()))
            this.profiles.put(p.getId(), p);
    }

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

    public void addQuestion(Question q){
        if(!this.posts.containsKey(q.getId()))
            this.posts.put(q.getId(), q);

        tardis64.insert(q);

        Profile p = this.profiles.get(q.getOwner_id());
        if(p != null)
            p.addPost(q);

    }

    public void addTag(long id, String s){
        if(!this.tags.containsKey(s))
            this.tags.put(s, id);
    }
}
