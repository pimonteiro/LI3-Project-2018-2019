package engine;

import java.time.LocalDateTime;
import java.util.*;

public class Question extends Post {

    private Map<Long,Answer> answers;
    private String title;
    private List<String> tags; //TODO Maybe we can change with java
    private long n_answers;


    public Question(long id, long owner_id, long score, LocalDateTime creation_date, String title, long n_answers,
                    long comments, List<String> tags, Map<Long,Answer> answersl){

        super(id, owner_id, score, creation_date, comments);
        this.title = title;
        this.n_answers = n_answers;
        this.tags = new ArrayList<>(tags);
        this.answers = new HashMap<>();

        for(Map.Entry<Long,Answer> a : answersl.entrySet()){
            this.answers.put(a.getKey(), a.getValue().clone());
        }
    }


    public Question(Question q){
        super(q);
        this.title = q.title;
        this.n_answers = q.n_answers;
        this.tags = new ArrayList<>(q.tags);
        this.answers = new HashMap<>();

        for(Map.Entry<Long,Answer> a : q.answers.entrySet()){
            this.answers.put(a.getKey(), a.getValue().clone());
        }
    }

    public Question(long id, long owner_id, long score, LocalDateTime creation_date, long n_comments, String title, long n_answers){
        super(id, owner_id, score, creation_date, n_comments);
        this.title = title;
        this.n_answers = n_answers;

        this.tags = new ArrayList<>();
        this.answers = new HashMap<>();

    }

    public Map<Long,Answer> getAnswers(){
        return answers;
    }

    public String getTitle(){
        return title;
    }

    public List<String> getTags(){
        return tags;
    }

    public long getN_answers(){
        return n_answers;
    }


    @Override
    public boolean equals(Object o){
        if(this == o) return true;
        if(o == null || getClass() != o.getClass()) return false;
        if(!super.equals(o)) return false;
        Question question = (Question) o;
        return n_answers == question.n_answers &&
               Objects.equals(answers, question.answers) &&
               Objects.equals(title, question.title) &&
               Objects.equals(tags, question.tags);
    }

    @Override
    public int hashCode(){

        return Objects.hash(super.hashCode(), answers, title, tags, n_answers);
    }

    @Override
    public String toString(){
        return "Question{" +
               "answers=" + answers +
               ", title='" + title + '\'' +
               ", tags=" + tags +
               ", n_answers=" + n_answers +
               '}' + super.toString();
    }

    public Question clone(){
        return new Question(this);
    }

}
