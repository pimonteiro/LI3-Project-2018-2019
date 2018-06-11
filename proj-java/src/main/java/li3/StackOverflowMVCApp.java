package li3;

import engine.TCDCommunity;

import java.util.Scanner;

public class StackOverflowMVCApp {


    private static TCDCommunity loadData(String path){
        TCDCommunity tmp = new TCDCommunity();
        tmp.load(path);
        return tmp;
    }

    public static void main(String[] args){
        Scanner in = new Scanner(System.in);
        System.out.println("[1] - Run all Querys\n[2] - Choose the Query");
        int ch = in.nextInt();
        if(ch == 1){
            Main o = new Main();
            o.controlled_main(args);
            System.exit(0);
        }

        TCDCommunity com = loadData(args[0]);
        StackOverflowView view = new StackOverflowView();
        StackOverflowController control = new StackOverflowController();

        control.setModel(com);
        control.setView(view);
        control.startFlow();


        System.out.println("GoodBye!\n" + java.time.LocalDateTime.now());
        System.exit(0);
    }
}
