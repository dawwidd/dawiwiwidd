package pl.poznan.put.cs.io.errors;

import java.util.List;


import pl.poznan.put.cs.io.errors.processors.BFSProcessor;
import pl.poznan.put.cs.io.errors.storage.DataInput;
import pl.poznan.put.cs.io.errors.storage.DataOutput;

/**
 * This is the controller class, which reads the input, runs the computing and writes the output.
 */
public class Controller {

    private DataInput input;
    private DataOutput output;
    BFSProcessor bFSProcessor = new BFSProcessor();

    public Controller(String inputName, String outputName) {
        input = new DataInput(inputName);
        output = new DataOutput(outputName);
    }

    /**
     * Runs computation.
     */
    public void run() {
        // loads input data
        try {
            input.load();
        } catch (Exception e) {
            System.err.println("Wrong input (see trace)!");
            e.printStackTrace();
            return;
        }
        // process
        List<Integer> result = bFSProcessor.process(input.getMatrix());

        // write results
        try {
            output.save(result);
        } catch (Exception e) {
            System.err.println("Wrong output (see trace)!");
            e.printStackTrace();
        }
    }


    public static void main(String[] args) {
        String inputName = null;
        String outputName = "console";
        if (args.length == 0) {
            System.err
                    .println("Run with parameters: input <output>"
                            + " where input/output are names of files or console for standard in/out"
                            + "\nOperation - first line of the input (+,-,*,/,sort,mean,primals)");
            System.exit(-1);
        } else {
            inputName = args[0];
            // second parameter is optional
            if (args.length > 1) {
                outputName = args[1];
            }
        }
        final Controller controler = new Controller(inputName,
                outputName);
        controler.run();
    }

}
