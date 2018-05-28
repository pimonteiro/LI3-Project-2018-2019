import common.NoPostFoundException;
import common.NoProfileFoundException;
import common.Pair;
import engine.TCDCommunity;
import org.omg.PortableInterceptor.SYSTEM_EXCEPTION;

import java.util.List;
import java.util.Scanner;

public class StackOverflowController {
    private StackOverflowView viewTxt;
    private TCDCommunity com;

    public void setModel(TCDCommunity data){
        this.com = data;
    }

    public void setView(StackOverflowView txt){
        this.viewTxt = txt;
    }

    public void startFlow(){
        Menu menu = this.viewTxt.getMenu(0);
        int op;
        Scanner a = new Scanner(System.in);
        do {
            menu.show();
            op = a.nextInt();
            switch (op){
                case 1 :
                    flowQuery1();
                    break;
                case 2 :
                    flowQuery2();
                    break;
                default:
                    System.out.println("Opcao Invalida.");
                    break;
            }
        }
        while(op != 0);
    }



    private void flowQuery1(){
        System.out.println("QUERY 1 = = = = = Info from Post");
        System.out.println("Post ID:");
        Scanner a = new Scanner(System.in);
        long id = a.nextInt();
        Pair<String,String> ret;
        try{
            ret = com.infoFromPost(id);
        }
        catch (NoPostFoundException e){
            System.out.println("No Post found with given ID.");
            return;
        }
        catch (NoProfileFoundException e) {
            System.out.println("The owner of the given post doesn't exist.");
            return;
        }
        System.out.println("-----Results-----");
        System.out.println("=>Title: " + ret.getFst());
        System.out.println("=>Owner: " + ret.getSnd());
    }

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
}
