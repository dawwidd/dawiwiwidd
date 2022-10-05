package pl.put.poznan.transformer.logic;

/**
 * Decorator class for converting numbers to text
 *
 * @author Dawid
 */
public class NumbersToTextDecorator extends Decorator{


    public NumbersToTextDecorator(String text) {
        this.text = text;
    }

    private final String[] basicNumbers = {
            " ",
            " jeden",
            " dwa",
            " trzy",
            " cztery",
            " pięć",
            " sześć",
            " siedem",
            " osiem",
            " dziewięć"
    };

    private final String[] tens = {
            "",
            " dziesięć",
            " dwadzieścia",
            " trzydzieści",
            " czterdzieści",
            " pięćdziesiąt",
            " sześćdziesiąt",
            " siedemdziesiąt",
            " osiemdziesiąt",
            " dziewięćdziesiąt"
    };

    private final String[] teens = {
            " dziesięć",
            " jedenaście",
            " dwanaście",
            " trzynaście",
            " czternaście",
            " piętnaście",
            " siedemnaście",
            " osiemnaście",
            " dziewiętnaście"
    };

    private final String[] hundreds ={
            " ",
            " sto",
            " dwieście",
            " trzysta",
            " czterysta",
            " pięćset",
            " sześćset",
            " siedemset",
            " osiemset",
            " dziewięćset"
    };

    private final String[] other = {
            "",
            " tys.",
            " mln.",
            " mld.",
            " bln.",
            " bld.",
            " tln.",
            " tld."
    };

    private String result = "";
    private int number;
    private int order = 0;
    private int i = 0;

    @Override
    public String decore() {
        number = Integer.valueOf(text);

        if(number==0) return "zero";

        while(number>0) {
            int digit = number % 10;
            number /= 10;

            if ((i==0)&&(number%100!=0 || digit !=0)) result = other[order] + result;
            if ((i==0)&&(number%10!=1)) result = basicNumbers[digit] + result;
            if ((i==0)&&(number%10==1))
            {
                result = teens[digit] + result;
                number/=10;
                i+=2;
                continue;
            }
            if (i==1) result = tens[digit] + result;
            if (i==2)
            {
                result = hundreds[digit] + result;
                i=-1;
                order++;
            }
            i++;
        }
        return result.trim();
    }
}
