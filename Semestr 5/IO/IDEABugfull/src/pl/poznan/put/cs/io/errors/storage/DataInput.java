package pl.poznan.put.cs.io.errors.storage;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

/**
 * Controls loading data from the given input.
 */
public class DataInput {

    private String inputName;

    private int size;

    private List<Double> numbers = new ArrayList<Double>();

    int[][] matrix;

    public DataInput(String inputName) {
        this.inputName = inputName;

    }

    private void initializeMatrix() {
        matrix = new int[size][size];
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                matrix[i][j] = 0;
            }
        }
    }

    /**
     * Loads data from the given input. The first line is the number of .
     *
     * @throws Exception
     */
    public void load() throws Exception {
        numbers.clear();
        BufferedReader input = getBufferedReader();
        try {
            String line = null;
            int x = 0;
            int y = 0;
            // read operation
            line = input.readLine();
            if (line != null) {
                size = Integer.parseInt(line.trim());
            }
            initializeMatrix();
            while ((line = input.readLine()) != null && line.length() > 0) {
                for (int i = 0; i < line.length(); i++) {
                    matrix[x][y] = Integer.parseInt(String.valueOf(line.charAt(i)));
                }
                y++;
                x = 0;
            }
        } catch (Exception ex) {
            throw ex;
        } finally {
            try {
                if (input != null) {
                    input.close();
                }
            } catch (IOException ex) {
                throw ex;
            }
        }
    }

    private BufferedReader getBufferedReader() throws FileNotFoundException {
        if (inputName.equalsIgnoreCase("console")) {
            return new BufferedReader(new InputStreamReader(System.in));
        }
        return new BufferedReader(new FileReader(new File(inputName)));
    }

    public int[][] getMatrix() {
        return matrix;
    }

}
