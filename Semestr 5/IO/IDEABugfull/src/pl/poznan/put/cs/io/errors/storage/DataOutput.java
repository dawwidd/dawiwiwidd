package pl.poznan.put.cs.io.errors.storage;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.util.List;

/**
 * Controls saving data to the given output.
 */
public class DataOutput {

    private String outputName = null;

    public DataOutput(String outputName) {
        this.outputName = outputName;
    }

    /**
     * Stores result to the given output. All elements are written line by line.
     *
     * @param result list with the list of numbers
     * @throws Exception
     */
    @SuppressWarnings("unchecked")
    public void save(List<Integer> result) throws Exception {
        BufferedWriter output = getBufferedWriter();
        try {

            output.write("");
            for (Integer i : result) {
                output.append(i.toString());
                output.newLine();
            }
        } catch (Exception ex) {
            throw ex;
        } finally {
            try {
                if (output != null) {
                    output.flush();
                    output.close();
                }
            } catch (IOException ex) {
                throw ex;
            }
        }

    }

    private BufferedWriter getBufferedWriter() throws IOException {
        if (outputName.equalsIgnoreCase("console")) {
            return new BufferedWriter(new OutputStreamWriter(System.out));
        }
        return new BufferedWriter(new FileWriter(new File(outputName)));
    }

}
