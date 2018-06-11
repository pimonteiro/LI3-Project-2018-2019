package li3;

import java.util.ArrayList;

public class StackOverflowView {

    private Menus menus;


    public StackOverflowView(){
        this.menus = initView();
    }


    public Menu getMenu(int i){
        return this.menus.getMenu(i);
    }


    private static Menus initView(){
        Menus menusSOF = new Menus();

        StringBuilder title = new StringBuilder();
        title.append(
                "\n  ___ _           _    ___              ___ _               ___                      ___                 _           \n");
        title.append(
                " / __| |_ __ _ __| |__/ _ \\__ _____ _ _| __| |_____ __ __  / _ \\ _  _ ___ _ _ _  _  | __|_ _____ __ _  _| |_ ___ _ _ \n");
        title.append(
                " \\__ \\  _/ _` / _| / / (_) \\ V / -_) '_| _|| / _ \\ V  V / | (_) | || / -_) '_| || | | _|\\ \\ / -_) _| || |  _/ -_) '_|\n");
        title.append(
                " |___/\\__\\__,_\\__|_\\_\\\\___/ \\_/\\___|_| |_| |_\\___/\\_/\\_/   \\__\\_\\\\_,_\\___|_|  \\_, | |___/_\\_\\___\\__|\\_,_|\\__\\___|_|  \n");
        title.append(
                "                                                                              |__/                                   \n");

        ArrayList<Opcao> op = new ArrayList<>();
        op.add(new Opcao("Query 1  -----> ", "[1]"));
        op.add(new Opcao("Query 2  -----> ", "[2]"));
        op.add(new Opcao("Query 3  -----> ", "[3]"));
        op.add(new Opcao("Query 4  -----> ", "[4]"));
        op.add(new Opcao("Query 5  -----> ", "[5]"));
        op.add(new Opcao("Query 6  -----> ", "[6]"));
        op.add(new Opcao("Query 7  -----> ", "[7]"));
        op.add(new Opcao("Query 8  -----> ", "[8]"));
        op.add(new Opcao("Query 9  -----> ", "[9]"));
        op.add(new Opcao("Query 10 -----> ", "[10]"));
        op.add(new Opcao("Query 11 -----> ", "[11]"));
        op.add(new Opcao("=============================", ""));

        Menu menu = new Menu(title.toString(), op);
        menusSOF.addMenu(0, menu);

        return menusSOF;
    }

}
