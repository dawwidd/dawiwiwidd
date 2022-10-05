#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>

class JednorekiBandyta {
    private:
        double cost; //koszt pojedynczej gry
        double rewardPercentage; //procent kosztu przechodzący do puli nagród
        double winProbability; //prawdopodobieństwo wygranej
        double winningPool = 0; //pula nagród
        int gameCount = 0; //liczba rozegranych gier

        double winRate; //stosunek ilości zwycięstw do rozegranych gier
        double wins=0.0; //ilość zwycięstw

    public:
        //gettery i settery
        bool setCost(double x){
            if(x>0){
                cost = x;
                return true;
            }
            else{return false;}
        }
        double getCost(){return cost;}

        bool setRewardPercentage(double x){
            if(x>=1 && x<=70){
                rewardPercentage = x;
                return true;
            }
            else{return false;}
        }
        double getRewardPercentage(){return rewardPercentage;}
        
        bool setWinProbability(double x){
            if(x>=0.1 && x<=0.2){
                winProbability = x;
                return true;
            }
            else{return false;}
        }
        double getWinProbability(){return winProbability;}

        double getWinningPool(){return winningPool;}

        int getGameCount(){return gameCount;}

        //przeprowadzenie gry
        void Play(){
            gameCount++;
            winningPool+= rewardPercentage * cost / 100.0f; //obliczenie sumy przechodzącej do puli nagród
            int rnd = rand()%(int(1.0/winProbability)); //generowanie losowej liczby
            if(rnd==0){
                std::cout<<"You win "<<winningPool<<"!"<<std::endl;
                winningPool = 0;
                wins++;
            }
            else{std::cout<<"You lose!"<<std::endl;}
        }

        //obliczanie stosunku zwycięstw do rozegranych gier
        void calcWinRate(){
            winRate=100*wins/gameCount;
        }

        double getWinRate(){return winRate;}

};


int main(){
    srand(time(NULL));

    JednorekiBandyta Game; //utworzenie instancji gry
    
    //sprawdzenie poprawności warunków
    if(Game.setCost(1000) &&
       Game.setRewardPercentage(60) &&
       Game.setWinProbability(0.1))
       {
            std::string action="play";
            
            //pętla główna
            while(action!="stop"){
                Game.Play();
                Game.calcWinRate();
                std::cout<<"Your win to lose ratio equals: "<<Game.getWinRate()<<"%"<<std::endl;
                std::cout<<"Write \"play\" for another game, \"stop\" to finish playing."<<std::endl;
                std::cin>>action;
            }
       }
    else{
        std::cout<<"At least one of the values is incorrect"<<std::endl;
    }

    

    
    
}