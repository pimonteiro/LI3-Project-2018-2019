package engine;

import java.time.LocalDateTime;
import java.util.Objects;


public abstract class Post implements Comparable<Post> {

    private long id;
    private LocalDateTime creation_date;
    private long owner_id;
    private long score;
    private long n_comments;

    public Post(long id, long owner_id, long score, LocalDateTime creation_date, long n_comments){
        this.id = id;
        this.owner_id = owner_id;
        this.score = score;
        this.creation_date = creation_date;
        this.n_comments = n_comments;
    }


    public Post(Post p){
        this.id = p.id;
        this.owner_id = p.owner_id;
        this.score = p.score;
        this.creation_date = p.creation_date;
        this.n_comments = p.n_comments;
    }

    public long getId(){
        return this.id;
    }

    public long getOwner_id(){
        return this.owner_id;
    }

    public long getScore(){
        return this.score;
    }

    public long getN_comments(){
        return this.n_comments;
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
               ", n_comments=" + n_comments +
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
               n_comments == post.n_comments &&
               Objects.equals(creation_date, post.creation_date);
    }

    @Override
    public int hashCode(){
        return Objects.hash(id, creation_date, owner_id, score, n_comments);
    }

    @Override
    public abstract Post clone();

    public int compareTo(Post p){
        return this.creation_date.compareTo(p.getCreation_date());
    }
}

