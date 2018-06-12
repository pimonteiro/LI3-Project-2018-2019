package li3;

import common.Exceptions.NoPostFoundException;
import common.Exceptions.NoProfileFoundException;
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
                case 1:
                    flowQuery1();
                    break;
                case 2:
                    flowQuery2();
                    break;
                case 3:
                    flowQuery3();
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
        Menu menu = this.viewTxt.getMenu(1);
        System.out.println("QUERY 1 = = = = = Info from Post");
        System.out.println("Post ID:");
        Scanner a = new Scanner(System.in);
        long id = a.nextInt();
        Pair<String,String> ret;
        try{
            ret = com.infoFromPost(id);
        }catch(NoPostFoundException e){
            System.out.println("No Post found with given ID.");
            return;
        }catch(NoProfileFoundException e){
            System.out.println("The owner of the given post doesn't exist.");
            return;
        }
        System.out.println("-----Results-----");
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
        List<Long> ret = com.topMostActive(n);
        System.out.println("-----Results-----");
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


        Pair<Long,Long> ret = com.totalPosts(begin, end);
        System.out.println("-----Results-----");
        System.out.println("=>Questions: " + ret.getFst());
        System.out.println("=>Answers:   " + ret.getSnd());
    }
}
