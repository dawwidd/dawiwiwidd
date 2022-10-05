/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package put.ai.games.deusexmachinaplayer;

import java.util.List;

import put.ai.games.game.Board;
import put.ai.games.game.Move;
import put.ai.games.game.Player;

public class DeusExMachinaPlayer extends Player {

    private long moveStartTime;
    private boolean stop;
    private int maxDepth=1;
    private float maxVal;

    private Float score(Board board){
        Color enemy = getOpponent(getColor());
        Integer enemyMovesCount = board.getMovesFor(enemy).size();
        Integer myMovesCount = board.getMovesFor(getColor()).size();
        Integer boardSize = board.getSize();
        Integer countAllies = 0;
        Integer countEnemies = 0;
        for(int i=0; i<boardSize; i++) {
            for(int j=0; j<boardSize; j++) {
                if(board.getState(i, j) == getColor()) countAllies++;
                else if(board.getState(i, j) == getOpponent(getColor())) countEnemies++;
            }
        }
        if(enemyMovesCount==0) return this.maxVal;
        return (float) (countAllies-countEnemies) * (enemyMovesCount/myMovesCount);
    }

    private Move selectMove(Board b, int depth){
        Float maxVal = null;
        Move result = null;

        for(Move m : b.getMovesFor(this.getColor())){
            Board board = b.clone();
            board.doMove(m);
            Float val;

            if(depth==0 || this.stop) val = score(board);
            else val = AlphaBeta(board,depth,Integer.MIN_VALUE, Integer.MAX_VALUE, false);

            if(maxVal==null || val>maxVal) {
                maxVal = val;
                result=m;
            }
        }
        return result;
    }

    private Float AlphaBeta(Board b, int depth, float alpha, float beta, boolean turn) {
        if(depth == 0) {
            return score(b);
        }

        if(depth>0 && System.currentTimeMillis()-this.moveStartTime > getTime()/2 && !stop) {
            this.maxDepth--;
            this.stop = true;
            return score(b);
        }
        float val = 0f;
        Board dummyBoard;
        List<Move> moves;
        if(turn) moves = b.getMovesFor(this.getColor());
        else moves = b.getMovesFor(getOpponent(this.getColor()));

        for(Move m : moves) {
            dummyBoard = b.clone();
            dummyBoard.doMove(m);
            val = -1*AlphaBeta(dummyBoard, depth-1, -1*beta, -1*alpha, !turn);

            if(val > alpha) alpha = val;
            if(alpha >= beta) return alpha;
        }
        return alpha;
    }

    @Override
    public String getName() {
        return "Dawid Królak 145383 Adrian Piniek 144226";
    }

    @Override
    public Move nextMove(Board b) {
        this.moveStartTime = System.currentTimeMillis();

        this.stop=false;
        this.maxVal = b.getSize()*b.getSize();
        Move move = selectMove(b, this.maxDepth);

        if( (double)(System.currentTimeMillis()-moveStartTime) < getTime()/2) this.maxDepth++;
        return move;
    }

    public static void main(String args[]){}
}
