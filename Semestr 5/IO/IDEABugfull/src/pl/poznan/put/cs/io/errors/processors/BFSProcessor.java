package pl.poznan.put.cs.io.errors.processors;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.Set;

public class BFSProcessor {

    List<Integer> list = new ArrayList<Integer>();
    Set<Integer> visitedNodes = new HashSet<Integer>();
    Queue<Integer> queue = new LinkedList<Integer>();
    List<Integer> result = new ArrayList<Integer>();
    int[][] matrix;

    /**
     * Starts the BFS algorithms for the whole graph
     *
     * @param matrix holds the graph
     * @return list of nodes
     */
    public List<Integer> process(int[][] matrix) {
        this.matrix = matrix;
        int beginningNode = getBeginningNode();
        if (beginningNode == -1) {
            return null;
        }
        queue.add(new Integer(beginningNode));
        search(beginningNode);
        result.addAll(findNodesWthoutNeighbors());
        return result;
    }

    /**
     * Runs the BFS algorithm for the given node
     *
     * @param nodeNo number of the node
     */
    private void search(int nodeNo) {
        visitedNodes.add(new Integer(nodeNo));
        List<Integer> allValidNeighbors = getAllValidNeighbors(nodeNo);
        queue.addAll(allValidNeighbors);
        visitedNodes.addAll(allValidNeighbors);
        Integer head = queue.poll();
        if (head == null) {
            return;
        }
        result.add(new Integer(nodeNo));
        if (queue.peek() == null) {
            return;
        }
        search(head);
    }

    /**
     * Looks for the node with the lowest index number, which has got at least
     * one neighbor
     *
     * @return the lowest possible index of the node, which has got at least one
     * neighbor
     */
    private int getBeginningNode() {
        for (int i = 0; i < matrix.length; i++) {
            if (getAllValidNeighbors(i).size() != 0) {
                return i;
            }
        }
        return -1;
    }

    /**
     * Returns the neighbors if a node, which haven't been visited yet
     *
     * @param nodeNo node index
     * @return the list of nodes indexes, which haven't been visited yet
     */
    private List<Integer> getAllValidNeighbors(int nodeNo) {
        List<Integer> neighbors = new ArrayList<Integer>();
        for (int i = 0; i < matrix.length; i++) {
            if (matrix[nodeNo][i] == 1
                    && visitedNodes.contains(new Integer(i))) {
                neighbors.add(new Integer(i));
            }
        }
        return neighbors;
    }

    /**
     * Finds all nodes without neighbors
     *
     * @return list of nodes indexes without neighbors
     */
    private List<Integer> findNodesWthoutNeighbors() {
        List<Integer> result = new ArrayList<Integer>();
        for (int i = 0; i < matrix.length; i++) {
            if (!visitedNodes.contains(new Integer(i))) {
                result.add(new Integer(i));
            }
        }
        return result;
    }
}
