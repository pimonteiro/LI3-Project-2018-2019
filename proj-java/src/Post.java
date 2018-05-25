public abstract class Post {

    private long type;

    public Post(){
        this.type = -1;
    }

    public Post(long type){
        this.type = type;
    }

    public Post(Post p){
        this.type = p.getType();
    }

    public long getType(){
        return type;
    }

    public void setType(long type){
        this.type = type;
    }

    public abstract Post clone();

    public boolean equals(Object o){
        if(o == this) return true;
        if(o == null || o.getClass() != this.getClass()) return false;
        Post p = (Post) o;
        return this.type == p.getType();
    }

    public String toString(){
        return "Type: " + this.type;
    }

    //Reformular
    public int compareTo(Post p){ //TODO Is this right?
        if(p instanceof Answer){
            Answer a = (Answer) p;
            return ((Answer) this).getCreation_date().compareTo(a.getCreation_date());
        }
        if(p instanceof Question){
            Question q = (Question) p;
            return ((Question) this).getCreation_date().compareTo(q.getCreation_date());
        }
        return 0; //Im in doubt
    }
}
