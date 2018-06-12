package li3;

import engine.TCDCommunity;

import java.util.Scanner;

/**
 * Main do programa.
 */
public class StackOverflowMVCApp {

    /**
     *
     * @param path Caminho para os ficheiros.
     * @return Estrutura com os dados preenchidos.
     */
    private static TCDCommunity loadData(String path){
        TCDCommunity tmp = new TCDCommunity();
        long before = System.currentTimeMillis();
        tmp.load(path);
        long after = System.currentTimeMillis();
        System.out.println("Time to load: " + (after-before));
        return tmp;
    }

    /**
     * @brief Main. Onde se faz a verificação se devemos executar a nossa custom flow ou a dada pelos professores.
     * @param args Argumentos do programa.
     */
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
