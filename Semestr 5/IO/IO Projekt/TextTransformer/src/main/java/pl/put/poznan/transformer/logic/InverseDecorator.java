package pl.put.poznan.transformer.logic;

public class InverseDecorator extends Decorator {

    public InverseDecorator(String text) {
        this.text = text;
    }

    @Override
    public String decore() {
        String[] dividedText = text.split(" ");
        String[] inverted = new String[dividedText.length];

        for (int j = 0; j < dividedText.length; j++) {
            String[] word = dividedText[j].split("");
            String[] result = new String[word.length];

            for (int i = 0; i < word.length; i++) {
                if (Character.isUpperCase(word[i].charAt(0)))
                    result[i] =(word[word.length - 1 - i]).toUpperCase();
                else
                    result[i] = (word[word.length - 1 - i]).toLowerCase();
            }
            ;

            inverted[j] = String.join("", result);
        }

        return String.join(" ", inverted);
    }
}