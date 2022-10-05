package pl.put.poznan.transformer.rest;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.web.bind.annotation.*;
import pl.put.poznan.transformer.logic.*;

import java.util.Arrays;


@RestController
@RequestMapping("/{text}")
public class TextTransformerController {
    @RequestMapping(method = RequestMethod.GET, produces = "application/json")
    public String get(@PathVariable String text,
                      @RequestParam(value="transforms", defaultValue="upper") String[] transforms) {

        String result = text;

        for (String transform : transforms) {
            switch(transform) {
                case "lower":
                    result = new LowerCaseDecorator(result).decore();
                    break;
                case "upper":
                    result = new UpperCaseDecorator(result).decore();
                    break;
                case "inverse":
                    result = new InverseDecorator(result).decore();
                    break;
                case "capitalise":
                    result = new CapitaliseDecorator(result).decore();
                    break;
                case "repeated-deleted":
                    result = new RepeatedDeletedDecorator(result).decore();
                    break;
                case "num-to-text":
                    result = new NumbersToTextDecorator(result).decore();
                    break;
                case "latex":
                    result = new LatexDecorator(result).decore();
                    break;
                case "long-to-short":
                    result = new ShortcutFullNameDecorator(result).decore();
                    break;
                case "short-to-long":
                    result = new FullToShortcutDecorator(result).decore();
                    break;
                default:
                    throw new RuntimeException();
            }
        }
        return result;
    }
}


