package pl.put.poznan.transformer.logic;

/**
 * Making a word as its shortcut
 *
 *
 * @author Adrian
 */
public class FullToShortcutDecorator extends Decorator {

    public FullToShortcutDecorator(String text) {
        this.text = text;
    }


    public String decore() {

        String[] Short =
                {"prof.", "cd.", "cdn.", "CV", "dr", "itd.", "itp.", "lek.",
                        "lic.", "mgr", "NIP", "np.", "nr", "PESEL", "pl.", "płd.", "płn.", "p.o.", "RP",
                        "s.", "S.A.", "str.", "św.", "tj.", "tzn.", "ub.", "UE", "ul.", "USA", "wf",
                        "zach.", "zob."
                };
        String[] Long = { "profesor", "ciąg dalszy", "ciąg dalszy nastąpi", "curriculum vitae", "doktor", "i tak dalej",
                "i tym podobne", "lekarz", "licencjat", "magister", "Numer Identyfikacji Podatkowej", "na przykład",
                "numer", "Powszechny Elektroniczny System Ewidencji Ludności", "plac", "południe", "północ", "pełniący obowiązki",
                "Rzeczpospolita Polska", "strona", "spółka akcyjna", "strona", "święty", "to jest", "to znaczy",
                "tak zwany", "ubiegły", "Unia Europejska", "ulica", "United States of America", "wychowanie fizyczne",
                "wschodni", "zachód", "zobacz"
        };
        String result = "";
        String[] arr = text.split(" ");
        try {
            for (int i = 0; i < arr.length; i++) {
                //System.out.println(arr[i]);

                for (int k = 0; k < Short.length; k++) {

                    if (arr[i] == "") continue;

                    if (arr[i].equals(Long[k])) {
                        arr[i] = Short[k];
                        //System.out.println(arr[i]);
                        //System.out.println("Weszlo");
                    } else if (arr[i].equals("na") && arr[i + 1].equals("przykład")) {
                        arr[i] = "np.";
                        arr[i + 1] = "";
                    } else if (arr[i].equals("curriculum") && arr[i + 1].equals("vitae")) {
                        arr[i] = "CV";
                        arr[i + 1] = "";
                    } else if (arr[i].equals("Unia") && arr[i + 1].equals("Europejska")) {
                        arr[i] = "UE";
                        arr[i + 1] = "";
                    } else if (arr[i].equals("to") && arr[i + 1].equals("jest")) {
                        arr[i] = "tj.";
                        arr[i + 1] = "";
                    } else if (arr[i].equals("to") && arr[i + 1].equals("znaczy")) {
                        arr[i] = "tzn.";
                        arr[i + 1] = "";

                    }
                    else if (arr[i].equals("ciąg") && arr[i + 1].equals("dalszy")) {
                        arr[i] = "cd.";
                        arr[i + 1] = "";
                        if (arr[i + 2].equals("nastąpi")) arr[i]="cdn.";
                    }
//                    else if (arr[i].equals("ciąg") && arr[i + 1].equals("dalszy") && arr[i + 2].equals("nastąpi")) {
//                        arr[i] = "cdn.";
//                        arr[i + 1] = "";
//                        arr[i + 2] = "";
//                    }
//


                }
            }
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Złe zakończenie zdania!");

            return result="Złe zakończenie zdania!";
        }


        for (int a = 0; a < arr.length; a++) {
            result += arr[a] + " ";
        }
        return result.trim().replaceAll(" +", " ");

}

}

