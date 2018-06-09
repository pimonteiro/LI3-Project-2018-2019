package engine;

import java.time.LocalDateTime;
import java.util.Objects;


public abstract class Post implements Comparable<Post> {

    private long id;
    private LocalDateTime creation_date;
    private long owner_id;
    private long score;


    public Post(long id, long owner_id, long score, LocalDateTime creation_date){
        this.id = id;
        this.owner_id = owner_id;
        this.score = score;
        this.creation_date = creation_date;
    }

    public Post(Post p){
        this.id = p.id;
        this.owner_id = p.owner_id;
        this.score = p.score;
        this.creation_date = p.creation_date;
    }

    public long getId(){
        return this.id;
    }

    public long getOwner_id(){
        return this.owner_id;
    }

    public long getScore(){
        return score;
    }

    public LocalDateTime getCreation_date(){
        return this.creation_date;
    }

    @Override
    public String toString(){
        return "Post{" +
               "id=" + id +
               ", creation_date=" + creation_date +
               ", owner_id=" + owner_id +
               ", score=" + score +
               '}';
    }

    @Override
    public boolean equals(Object o){
        if(this == o) return true;
        if(o == null || getClass() != o.getClass()) return false;
        Post post = (Post) o;
        return id == post.id &&
               owner_id == post.owner_id &&
               score == post.score &&
               Objects.equals(creation_date, post.creation_date);
    }

    @Override
    public int hashCode(){
        return Objects.hash(id, creation_date, owner_id, score);
    }

    @Override
    public abstract Post clone();

    public int compareTo(Post p){
        return this.creation_date.compareTo(p.getCreation_date());
    }
}

