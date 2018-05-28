import engine.TCDCommunity;

public class StackOverflowMVCApp {


    private static TCDCommunity loadData(){
        return new TCDCommunity(); // TODO A preencher com o load
    }

    public static void main(String[] args) {
        TCDCommunity com = loadData();
        StackOverflowView view = new StackOverflowView();
        StackOverflowController control = new StackOverflowController();

        control.setModel(com);
        control.setView(view);
        control.startFlow();


        System.out.println("GoodBye!\n" + java.time.LocalDateTime.now());
        System.exit(0);
    }
}
