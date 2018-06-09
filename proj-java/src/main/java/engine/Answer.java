package engine;

import java.time.LocalDateTime;

public class Answer extends Post {

    private LocalDateTime creation_date;
    private long id;
    private long owner_id;
    private long parent_id;
    private long comments;
    private long score;

    public Answer(LocalDateTime creation_date, long id, long owner_id, long parent_id, long comments, long score){
        super(2); //2 - Resposta
        this.creation_date = creation_date;
        this.id = id;
        this.owner_id = owner_id;
        this.parent_id = parent_id;
        this.comments = comments;
        this.score = score;
    }

    public Answer(){
        super();
        this.creation_date = LocalDateTime.now();
        this.id = -1;
        this.owner_id = -1;
        this.parent_id = -1;
        this.comments = -1;
        this.score = -1;
    }

    public Answer(Answer a){
        this.creation_date = a.getCreation_date();
    }

    public LocalDateTime getCreation_date(){
        return this.creation_date;
    }

    public long getId(){
        return this.id;
    }

    public long getOwner_id(){
        return this.owner_id;
    }

    public long getParent_id(){
        return this.parent_id;
    }

    public long getComments(){
        return this.comments;
    }

    public long getScore(){
        return this.score;
    }

    public void setCreation_date(LocalDateTime creation_date){
        this.creation_date = creation_date;
    }

    public void setId(long id){
        this.id = id;
    }

    public void setOwner_id(long owner_id){
        this.owner_id = owner_id;
    }

    public void setParent_id(long parent_id){
        this.parent_id = parent_id;
    }

    public void setComments(long comments){
        this.comments = comments;
    }

    public void setScore(long score){
        this.score = score;
    }

    public Answer clone(){
        return new Answer(this);
    }

    public boolean equals(Object o){
        if(o == this) return true;
        if(o == null || o.getClass() != this.getClass()) return false;
        if(!super.equals(o)) return false;
        Answer a = (Answer) o;
        return this.creation_date.equals(((Answer) o).getCreation_date()) &&
               this.id == a.getId() && this.owner_id == a.getOwner_id() &&
               this.parent_id == a.getParent_id() && this.comments == a.getComments() &&
               this.score == a.getScore();
    }

    public String toString(){
        return super.toString() + "Creation Date: " + this.creation_date.toString() + "ID: " + this.id +
               "Owner ID: " + this.owner_id + "Parent ID: " + this.parent_id +
               "Comments: " + this.comments + "Score :" + this.score;
    }
}
