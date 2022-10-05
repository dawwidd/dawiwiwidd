package pl.put.poznan.transformer.logic;

/**
 * Convert special characters to latex notation
 *
 * @author Dawid
 */
public class LatexDecorator extends Decorator{

    public LatexDecorator(String text) {
        this.text = text;
    }

    public String convert(String character) {
        switch(character) {
            case "%": return "\\%";
            case "$": return "\\$";
            case "{": return "\\{";
            case "_": return "\\_";
            case "¶": return "\\P";
            case "‡": return "\\ddag";
            case "|": return "\\textbar";
            case ">": return "\\textgreater";
            case "–": return "\\textendash";
            case "™": return "\\texttrademark";
            case "¡": return "\\texttexclamdown";
            case "£": return "\\pounds";
            case "#": return "\\#";
            case "&": return "\\&";
            case "}": return "\\}";
            case "§": return "\\S";
            case "†": return "\\dag";
            case "\\": return "\\textbackslash";
            case "<": return "\\textless";
            case "—": return "\\textemdash";
            case "®": return "\\textregistered";
            case "¿": return "\\textquestiondown";
            case "ⓐ": return "\\textcircled{a}";
            case "©": return "\\copyright";
            default: return character;
        }
    }

    @Override
    public String decore() {
        {
            String result= "";
            for(int i=0;i<text.length();i++)
            {
                result += convert(String.valueOf(text.charAt(i)));
            }
            return result.trim();
        }
    }
}