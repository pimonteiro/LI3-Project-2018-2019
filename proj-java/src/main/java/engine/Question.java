package engine;

import java.time.LocalDateTime;
import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Question extends Post {

    private Map<Long,Answer> answers;
    private String title;
    private List<String> tags;
    private long n_answers;

    private List<String> tagstoList(String tags){
        String regexString = Pattern.quote("<") + "(.*?)" + Pattern.quote(">");
        Pattern pattern = Pattern.compile(regexString);
        Matcher matcher = pattern.matcher(tags);
        List<String> tmp = new ArrayList<>();
        while(matcher.find()){
            String textInBetween = matcher.group(1); // Since (.*?) is capturing group 1
            tmp.add(textInBetween);
        }

        return tmp;
    }

    public Question(long id, long owner_id, long score, LocalDateTime creation_date, String title, long n_answers,
                    long comments, String tags, Map<Long,Answer> answersl){

        super(id, owner_id, score, creation_date, comments);
        this.title = title;
        this.n_answers = n_answers;
        this.tags = new ArrayList<>(tagstoList(tags));
        this.answers = new HashMap<>();

        for(Map.Entry<Long,Answer> a : answersl.entrySet()){
            this.answers.put(a.getKey(), a.getValue().clone());
        }
    }


    public Question(Question q){
        super(q);
        this.title = q.title;
        this.n_answers = q.n_answers;
        this.tags = q.tags;
        this.answers = new HashMap<>();

        for(Map.Entry<Long,Answer> a : q.answers.entrySet()){
            this.answers.put(a.getKey(), a.getValue().clone());
        }
    }

    public Question(long id, long owner_id, long score, LocalDateTime creation_date, long n_comments, String title,
                    long n_answers, String tags){
        super(id, owner_id, score, creation_date, n_comments);
        this.title = title;
        this.n_answers = n_answers;
        this.tags = tags == null ? new ArrayList<>() : new ArrayList<>(tagstoList(tags));
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
    public java.lang.String toString(){
        return "Question{" +
               "answers=" + answers +
               ", title=" + title +
               ", tags=" + tags +
               ", n_answers=" + n_answers +
               '}' + super.toString();
    }

    public Question clone(){
        return new Question(this);
    }

    public void addAnswer(Answer a){
        this.answers.put(a.getId(), a);
    }

}
