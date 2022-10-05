package recycling;

import java.util.ArrayList;
import java.util.TreeMap;
import java.util.HashMap;
import java.util.Scanner;


public class Wezel implements Comparable<Wezel>{

    private int id;

    //Konstruktor
    public Wezel(Integer id) {
        this.id = id;
    }

    //getter id
    public int getId() {
        return this.id;
    }

    public int compareTo(Wezel w) {
        return this.getId() - w.getId();
    }
    
    @Deprecated
    @Override
    protected void finalize() throws Throwable {
        System.out.println("Finalizowanie obiektu");
        super.finalize();
    }

    //Zad.12 ArrayList umożliwia dynamiczne dodawanie nowych elementów, dlatego jest lepszym wyborem od tradycyjnej listy
    public ArrayList<Wezel> polaczenia = new ArrayList<>();

    public void dodajPolaczenie(Wezel wzl) {
        this.polaczenia.add(wzl);
    }

    //Zad.13 Utworzenie TreeMap i HashMap
    public TreeMap<Wezel,Boolean> polaczeniaTree = new TreeMap<Wezel, Boolean>();

    public HashMap<Wezel,Boolean> polaczeniaHash = new HashMap<Wezel, Boolean>();

    //Zad.13 Dodanie połączenia za pomocą treemap i hashmap
    public void dodajPolaczenieTree(Wezel wzl) {
        this.polaczeniaTree.put(wzl, true);
    }

    public void dodajPolaczenieHash(Wezel wzl) {
        this.polaczeniaHash.put(wzl, true);
    }

    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);

        // Zad.6/7/11 Odśmiecacz uruchamia się tylko dla odpowiednio dużej liczby utworzonych obiektów
        // Aby móc dalej inicjalizować nowe obiekty, odśmiecacz musi zwolnić pamięć
        //
        for(int i = 0; i <=1000000; i++) {
            Wezel w1 = new Wezel(i);
            Wezel w2 = new Wezel(i);
            
            // w1.dodajPolaczenie(w2);
            // w2.dodajPolaczenie(w1);
            
            // w1.dodajPolaczenieTree(w2);
            // w2.dodajPolaczenieTree(w1);

            w1.dodajPolaczenieHash(w2);
            w2.dodajPolaczenieHash(w1);
        }
        s.nextLine();
        s.close();
    }
}