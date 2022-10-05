package put.ai.games.myplayer;

import java.util.List;
import put.ai.games.game.Board;
import put.ai.games.game.Move;
import put.ai.games.game.Player;

public class MyPlayer extends Player {

    private Color myColor;
    private Color opponent;
    private final int maxDepth = 1;
    private int lose_depth = -1;
    private int win_depth = -1;
    private long time;
    boolean endOfTime;

    private Float evaluation(Board b){
        int my_figures = 0;
        int opponent_figures = 0;
        for(int i = 0; i < b.getSize(); i++) {
            for (int j = 0; j < b.getSize(); j++) {
                if (b.getState(i, j) == myColor) {
                    my_figures += 1;
                } else if (b.getState(i, j) == opponent) {
                    opponent_figures += 1;
                }
            }
        }
        float result_figures = (float)my_figures/opponent_figures;
        result_figures *= result_figures;
        float result_moves = (float)b.getMovesFor(myColor).size()/b.getMovesFor(opponent).size();
        if(maxDepth%2 == 1) result_figures = -result_figures;
        return result_figures*result_moves;
    }

    private Move getMove(Board b){
        lose_depth = -1;
        win_depth = -1;
        Move bestMove = null;
        Float bestValue = null;
        Float result;
        Board testBoard;
        List<Move> moves = b.getMovesFor(myColor);
        for(Move move : moves){
            testBoard = b.clone();
            testBoard.doMove(move);
            result = AlphaBeta(opponent, maxDepth, Integer.MIN_VALUE, Integer.MAX_VALUE, testBoard);
            if(endOfTime) break;
            if(win_depth == maxDepth){
                return move;
            }
            if(bestValue == null){
                bestValue = result;
                bestMove = move;
            }
            else if(bestValue == Float.MAX_VALUE && lose_depth > win_depth && result != -Float.MAX_VALUE && result != Float.MAX_VALUE){
                bestValue = result;
                bestMove = move;
            }
            else if(result == Float.MAX_VALUE && win_depth >= lose_depth){
                bestValue = result;
                bestMove = move;
            }
            else if(result != Float.MAX_VALUE && result > bestValue){
                bestValue = result;
                bestMove = move;
            }
        }
        return bestMove;
    }

    private Float AlphaBeta(Color turn, int depth, float alpha, float beta, Board b){
        if(System.currentTimeMillis()-time > getTime() - 2000) endOfTime = true;
        float value = 0f;
        Board testBoard;
        List<Move> moves = b.getMovesFor(turn);
        if(b.getWinner(turn) == opponent){
            lose_depth = depth;
            return -Float.MAX_VALUE;
        }
        if(b.getWinner(turn) == myColor){
            win_depth = depth;
            return Float.MAX_VALUE;
        }
        if(endOfTime || depth == 0){
            return evaluation(b);
        }
        for(Move move : moves){
            testBoard = b.clone();
            testBoard.doMove(move);
            value = -AlphaBeta(getOpponent(turn), depth - 1, -beta, -alpha, testBoard);
            if(value>10000 || value <=-10000) return -value;
            if(value > alpha) alpha = value;
            if(alpha >= beta) return alpha;
        }
        return alpha;
    }

    @Override
    public String getName() {
        return "Miłosz Grocholewski 145364";
    }

    @Override
    public Move nextMove(Board b) {
        endOfTime = false;
        time = System.currentTimeMillis();
        myColor = getColor();
        opponent = getOpponent(myColor);
        return getMove(b);
    }

    public static void main(String[] args){}
}
