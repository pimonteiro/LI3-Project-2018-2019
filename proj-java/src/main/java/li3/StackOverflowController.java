package li3;

import common.Exceptions.NoPostFoundException;
import common.Exceptions.NoProfileFoundException;
import common.Exceptions.PostIsNotOfRightTypeException;
import common.Pair;
import engine.TCDCommunity;

import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.List;
import java.util.Scanner;

/**
 * @brief Controlador do flow do programa. Aqui controla-se os eventos conforme as escolhas do utilizador.
 */
public class StackOverflowController {

    private StackOverflowView viewTxt;
    private TCDCommunity com;

    public void setModel(TCDCommunity data){
        this.com = data;
    }

    public void setView(StackOverflowView txt){
        this.viewTxt = txt;
    }

    /**
     * Inicialização do flow do programa
     */
    public void startFlow(){
        Menu menu = this.viewTxt.getMenu(0);
        int op;
        Scanner a = new Scanner(System.in);
        do{
            menu.show();
            op = a.nextInt();
            switch(op){
                case 0:
                    return;
                case 1:
                    flowQuery1();
                    break;
                case 2:
                    flowQuery2();
                    break;
                case 3:
                    flowQuery3();
                    break;
                case 4:
                    flowQuery4();
                    break;
                case 5:
                    flowQuery5();
                    break;
                case 6:
                    flowQuery6();
                    break;
                case 7:
                    flowQuery7();
                    break;
                case 8:
                    flowQuery8();
                    break;
                case 9:
                    flowQuery9();
                    break;
                case 10:
                    flowQuery10();
                    break;
                case 11:
                    flowQuery11();
                    break;
                default:
                    System.out.println("Opcao Invalida.");
                    break;
            }
        }
        while(op != 0);
    }

    /**
     * Flow para a Query1
     */
    private void flowQuery1(){
        System.out.println("QUERY 1 = = = = = Info from Post");
        System.out.println("Post ID:");
        Scanner a = new Scanner(System.in);
        long id = a.nextInt();
        Pair<String,String> ret;
        long before = System.currentTimeMillis();
        try{
            ret = com.infoFromPost(id);
        }catch(NoPostFoundException e){
            System.out.println("No Post found with given ID.");
            return;
        }catch(NoProfileFoundException e){
            System.out.println("The owner of the given post doesn't exist.");
            return;
        }
        long after = System.currentTimeMillis();
        System.out.println("-----Results-----");
        System.out.println("Time: " + (after-before) + " ms");
        System.out.println("=>Title: " + ret.getFst());
        System.out.println("=>Owner: " + ret.getSnd());
    }

    /**
     * Flow para a Query2
     */
    private void flowQuery2(){
        System.out.println("QUERY 2 = = = = = Top Most Active Users");
        System.out.println("Number of users:");
        Scanner a = new Scanner(System.in);
        int n = a.nextInt();

        long before = System.currentTimeMillis();
        List<Long> ret = com.topMostActive(n);
        long after = System.currentTimeMillis();
        System.out.println("-----Results-----");
        System.out.println("Time: " + (after-before) + " ms");
        int i = 0;
        for(Long id : ret){
            System.out.println(i++ + " => " + id);
        }
    }

    /**
     * Flow para a Query3
     */
    private void flowQuery3(){
        System.out.println("QUERY 3 = = = = = Total Posts");
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd");
        Scanner a = new Scanner(System.in);

        System.out.println("Date of begin: (year-month-day)");
        String beginS = a.nextLine();
        LocalDate begin = LocalDate.parse(beginS, formatter);

        System.out.println("Date of end: (year-month-day)");
        String endS = a.nextLine();
        LocalDate end = LocalDate.parse(endS, formatter);

        long before = System.currentTimeMillis();
        Pair<Long,Long> ret = com.totalPosts(begin, end);
        long after = System.currentTimeMillis();
        System.out.println("-----Results-----");
        System.out.println("Time: " + (after-before) + " ms");
        System.out.println("=>Questions: " + ret.getFst());
        System.out.println("=>Answers:   " + ret.getSnd());
    }

    /**
     * Flow para a Query4
     */
    private void flowQuery4(){
        System.out.println("QUERY 4 = = = = = Questions with a Tag");
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd");
        Scanner a = new Scanner(System.in);

        System.out.println("Date of begin: (year-month-day)");
        String beginS = a.nextLine();
        LocalDate begin = LocalDate.parse(beginS, formatter);

        System.out.println("Date of end: (year-month-day)");
        String endS = a.nextLine();
        LocalDate end = LocalDate.parse(endS, formatter);

        System.out.println("Tag: ");
        String tag = a.nextLine();

        long before = System.currentTimeMillis();
        List<Long> ret = com.questionsWithTag(tag, begin, end);
        long after = System.currentTimeMillis();
        System.out.println("-----Results-----");
        System.out.println("Time: " + (after-before) + " ms");
        System.out.println("IDs: " + ret.toString());
    }

    /**
     * Flow para a Query5
     */
    private void flowQuery5(){
        System.out.println("QUERY5 = = = = = Info of a User");
        Scanner a = new Scanner(System.in);

        System.out.println("ID: ");
        Long id = a.nextLong();

        long before = System.currentTimeMillis();
        Pair<String,List<Long>> ret;
        try{
            ret = com.getUserInfo(id);
        }
        catch (NoProfileFoundException e){
            System.out.println("No user found");
            return;
        }
        long after = System.currentTimeMillis();
        System.out.println("-----Results-----");
        System.out.println("Time: " + (after-before) + " ms");
        System.out.println("Bio: " + ret.getFst());
        System.out.println("10 Posts: " + ret.getSnd().toString());
    }

    /**
     * Flow para a Query6
     */
    private void flowQuery6(){
        System.out.println("QUERY6 = = = = = Most Voted Awnsers");
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd");
        Scanner a = new Scanner(System.in);

        System.out.println("Date of begin: (year-month-day)");
        String beginS = a.nextLine();
        LocalDate begin = LocalDate.parse(beginS, formatter);

        System.out.println("Date of end: (year-month-day)");
        String endS = a.nextLine();
        LocalDate end = LocalDate.parse(endS, formatter);

        System.out.println("Number of: ");
        int N = a.nextInt();

        long before = System.currentTimeMillis();
        List<Long> ret = com.mostVotedAnswers(N, begin, end);
        long after = System.currentTimeMillis();
        System.out.println("-----Results-----");
        System.out.println("Time: " + (after-before) + " ms");
        System.out.println("IDs: " + ret.toString());
    }

    /**
     * Flow para a Query7
     */
    private void flowQuery7(){
        System.out.println("QUERY7 = = = = = Most Answered Questions");
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd");
        Scanner a = new Scanner(System.in);

        System.out.println("Date of begin: (year-month-day)");
        String beginS = a.nextLine();
        LocalDate begin = LocalDate.parse(beginS, formatter);

        System.out.println("Date of end: (year-month-day)");
        String endS = a.nextLine();
        LocalDate end = LocalDate.parse(endS, formatter);

        System.out.println("Number of: ");
        int N = a.nextInt();

        long before = System.currentTimeMillis();
        List<Long> ret = com.mostAnsweredQuestions(N, begin, end);
        long after = System.currentTimeMillis();
        System.out.println("-----Results-----");
        System.out.println("Time: " + (after-before) + " ms");
        System.out.println("IDs: " + ret.toString());
    }

    /**
     * Flow para a Query8
     */
    private void flowQuery8(){
        System.out.println("QUERY8 = = = = = Question with word on Title");
        Scanner a = new Scanner(System.in);

        System.out.println("Word: ");
        String word = a.nextLine();

        System.out.println("Number of: ");
        int N = a.nextInt();

        long before = System.currentTimeMillis();
        List<Long> ret = com.containsWord(N, word);
        long after = System.currentTimeMillis();
        System.out.println("-----Results-----");
        System.out.println("Time: " + (after-before) + " ms");
        System.out.println("IDs: " + ret.toString());
    }

    /**
     * Flow para a Query9
     */
    private void flowQuery9(){
        System.out.println("QUERY9  = = = = = Posts shared by two users");
        Scanner a = new Scanner(System.in);

        System.out.println("ID.1: ");
        long id1 = a.nextLong();

        System.out.println("ID.2: ");
        long id2 = a.nextLong();

        System.out.println("Number of: ");
        int N = a.nextInt();

        long before = System.currentTimeMillis();
        List<Long> ret;
        try{
            ret = com.bothParticipated(N, id1, id2);
        }
        catch (NoProfileFoundException e){
            System.out.println("One of users not found.");
            return;
        }
        catch (NoPostFoundException e){
            System.out.println("One post not found");
            return;
        }
        long after = System.currentTimeMillis();
        System.out.println("-----Results-----");
        System.out.println("Time: " + (after-before) + " ms");
        System.out.println("IDs: " + ret.toString());
    }

    /**
     * Flow para a Query10
     */
    private void flowQuery10(){
        System.out.println("QUERY10  = = = = = Best Answer of Post");
        Scanner a = new Scanner(System.in);

        System.out.println("ID: ");
        long id = a.nextLong();


        long before = System.currentTimeMillis();
        long ret;
        try{
            ret = com.betterAnswer(id);
        }
        catch (NoProfileFoundException e){
            System.out.println("One of users not found.");
            return;
        }
        catch (NoPostFoundException e){
            System.out.println("One post not found");
            return;
        }
        catch (PostIsNotOfRightTypeException e){
            System.out.println("Post is not a Question");
            return;
        }
        long after = System.currentTimeMillis();
        System.out.println("-----Results-----");
        System.out.println("Time: " + (after-before) + " ms");
        System.out.println("ID: " + ret);
    }

    /**
     * Flow para a Query11
     */
    private void flowQuery11(){
        System.out.println("QUERY11  = = = = = Most used Tag by the best reputation users");
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd");
        Scanner a = new Scanner(System.in);

        System.out.println("Date of begin: (year-month-day)");
        String beginS = a.nextLine();
        LocalDate begin = LocalDate.parse(beginS, formatter);

        System.out.println("Date of end: (year-month-day)");
        String endS = a.nextLine();
        LocalDate end = LocalDate.parse(endS, formatter);

        System.out.println("N: ");
        int n = a.nextInt();


        long before = System.currentTimeMillis();
        List<Long> ret = com.mostUsedBestRep(n, begin, end);
        long after = System.currentTimeMillis();
        System.out.println("-----Results-----");
        System.out.println("Time: " + (after-before) + " ms");
        System.out.println("IDs: " + ret.toString());
    }










}
