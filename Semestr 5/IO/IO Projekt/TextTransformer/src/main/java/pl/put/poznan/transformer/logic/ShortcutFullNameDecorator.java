package pl.put.poznan.transformer.logic;

/**
 * Explains the shortcut to its full name
 *
 *
 * @author Adrian
 */
public class ShortcutFullNameDecorator extends Decorator {

    public ShortcutFullNameDecorator(String text) {this.text = text;}


    @Override
    public String decore() {

        String[] Short =
                {"prof.","cd.","cdn.","CV","dr","itd.","itp.","lek.",
                        "lic.","mgr","NIP","np.","nr","PESEL","pl.","płd.","płn.","p.o.","RP",
                        "s.","S.A.","str.","św.","tj.","tzn.","tzw.","ub.","UE","ul.","USA","wf","wsch",
                        "zach.","zob."
                };
        String[] Long={"profesor","ciąg dalszy","ciąg dalszy nastąpi","curriculum vitae","doktor","i tak dalej",
                "i tym podobne","lekarz","licencjat","magister","Numer Identyfikacji Podatkowej","na przykład",
                "numer","Powszechny Elektroniczny System Ewidencji Ludności","plac","południe","północ","pełniący obowiązki",
                "Rzeczpospolita Polska","strona","spółka akcyjna","strona","święty","to jest","to znaczy",
                "tak zwany","ubiegły","Unia Europejska","ulica","United States of America","wychowanie fizyczne",
                "wschodni","zachód","zobacz"
        };
        String result ="";
        //System.out.println(Short.length);
        //System.out.println(zdanie);
        String[] arr = text.split(" ");

        for (int i=0; i<arr.length;i++){
            //System.out.println(arr[i]);

            for (int k =0; k< Short.length;k++){
                if (arr[i].equals(Short[k])){
                    arr[i]=Long[k];
                    //System.out.println(arr[i]);
                    //System.out.println("Weszlo");
                }
                //System.out.println("Iteracja");

            }

        }
//        for (int i=0;i<Short.length;i++ ){  //Sprawdzenie słownika
//            System.out.println(Short[i] +" "+ Long[i]);
//    }
        for (int a=0;a<arr.length;a++){
            result += arr[a] + " ";
        }
        return result.trim();
    }
}
