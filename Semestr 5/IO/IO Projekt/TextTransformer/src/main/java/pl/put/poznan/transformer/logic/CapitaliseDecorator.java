package pl.put.poznan.transformer.logic;

import java.util.Locale;

/**
 * Making first letter of each word being capitalised
 * Not changing any other letter cases
 *
 * @author Adrian
 */
public class CapitaliseDecorator extends Decorator{

    public CapitaliseDecorator(String text) {
        this.text = text;
    }

    @Override
    public String decore() {

        String slowa[] = text.split(" ");
        String result = "";

        for(String s:slowa) {
            String pierwsza = s.substring(0,1);
            String reszta = s.substring(1);
            result += pierwsza.toUpperCase() + reszta.toLowerCase() + " ";
        }
        return result.trim();
    }
}