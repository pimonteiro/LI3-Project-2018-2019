package common;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class Question extends Post {

    private LocalDateTime creation_date;
    private HashMap<Long,Answer> answers;
    private String title;
    private List<String> tags; //TODO Maybe we can change with java
    private long id;
    private long owner_id;
    private long n_answers;
    private long comments;
    private long score;

    public Question(LocalDateTime creation_date, HashMap<Long,Answer> answers, String title_question, List<String> tags,
                    long id_question, long owner_id_question, long n_answers, long comments, long score){
        super(1); //1 - Questao
        this.creation_date = creation_date;
        setAnswers(answers);
        this.title = title_question;
        setTags(tags);
        this.id = id_question;
        this.owner_id = owner_id_question;
        this.n_answers = n_answers;
        this.comments = comments;
        this.score = score;
    }

    public Question(Question q){
        super(q);
        this.creation_date = q.getCreation_date();
        this.answers = q.getAnswers();
        this.title = q.getTitle();
        this.tags = q.getTags();
        this.id = q.getId();
        this.owner_id = q.getOwner_id();
        this.n_answers = q.getN_answers();
        this.comments = q.getComments();
        this.score = q.getScore();
    }

    public Question(){
        super();
        this.creation_date = LocalDateTime.now();
        this.answers = new HashMap<>();
        this.title = "";
        this.tags = new ArrayList<>();
        this.id = -1;
        this.owner_id = -1;
        this.n_answers = -1;
        this.comments = -1;
        this.score = -1;
    }

    public LocalDateTime getCreation_date(){
        return this.creation_date;
    }

    public HashMap<Long,Answer> getAnswers(){
        HashMap<Long,Answer> ret = new HashMap<>();
        this.answers.values().forEach(a -> ret.put(a.getId(), a.clone()));
        return ret;
    }

    public String getTitle(){
        return this.title;
    }

    public List<String> getTags(){
        List<String> ret = new ArrayList<>();
        this.tags.forEach(s -> ret.add(s));
        return ret;
    }

    public long getId(){
        return this.id;
    }

    public long getOwner_id(){
        return this.owner_id;
    }

    public long getN_answers(){
        return this.n_answers;
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

    public void setAnswers(HashMap<Long,Answer> answers){
        this.answers = new HashMap<>();
        answers.values().forEach(a -> this.answers.put(a.getId(), a.clone()));
    }

    public void setTitle(String title_question){
        this.title = title_question;
    }

    public void setTags(List<String> tags){
        this.tags = new ArrayList<>();
        tags.forEach(s -> tags.add(s));
    }

    public void setId(long id_question){
        this.id = id_question;
    }

    public void setOwner_id(long owner_id_question){
        this.owner_id = owner_id_question;
    }

    public void setN_answers(long n_answers){
        this.n_answers = n_answers;
    }

    public void setComments(long comments){
        this.comments = comments;
    }

    public void setScore(long score){
        this.score = score;
    }

    @Override
    public boolean equals(Object o){
        if(this == o) return true;
        if(o == null || o.getClass() != this.getClass()) return false;
        if(!super.equals(o)) return false;

        Question q = (Question) o;
        return this.id == q.getId() &&
               this.owner_id == q.getOwner_id() &&
               this.n_answers == q.getN_answers() &&
               this.comments == q.getComments() &&
               this.score == q.getScore() &&
               this.creation_date.equals(q.getCreation_date()) &&
               this.answers.equals(q.getAnswers()) &&
               this.title.equals(q.getTitle()) &&
               this.tags.equals(q.getTags());
    }

    public Question clone(){
        return new Question(this);
    }

    public String toString(){
        return "ID: " + this.id + "Onwer ID: " + this.owner_id +
               "N_answers: " + this.n_answers + "Comments: " + this.comments +
               "Score: " + this.score + "Creation Date :" + this.creation_date +
               "Title: " + this.title +
               "answers: " + this.answers.toString() + "Tags: " + this.tags.toString();
    }

}
