package engine;


import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.TreeSet;

public class Tardis {

    // TODO PROPER DO THIS

    private List<List<TreeSet<Question>>> questions;
    private List<List<TreeSet<Answer>>> answers;

    public Tardis(){
        this.answers = new ArrayList<>(new ArrayList<>(new TreeSet<>()));
        this.questions  = new ArrayList<>(new ArrayList<>(new TreeSet<>()));

    }

    public Question getQuestion(LocalDateTime d){
        int day_index = d.getYear() - 2008;
        int monthDay_index = d.getMonthValue() -1 + (d.getDayOfYear() -1);

        return this.questions.get(day_index).get(monthDay_index).first();
    }

    public Answer getAnswer(LocalDateTime d){
        int day_index = d.getYear() - 2008;
        int monthDay_index = d.getMonthValue() -1 + (d.getDayOfYear() -1);

        return this.answers.get(day_index).get(monthDay_index).first();
    }
}
