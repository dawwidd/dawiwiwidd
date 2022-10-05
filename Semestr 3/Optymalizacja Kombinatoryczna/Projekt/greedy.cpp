#include <fstream>
#include <iostream>
#include <time.h>
#include <list>
#include <math.h>
#include <algorithm>
const int PAR = 10;
const int POPSIZE = 10;
const int ITER = 5;
const double ELITE = 0.2;
const double MUT = 0.01;
//std::pair<int,int> mydistances [] = {{3,7},{9,9},{9,8},{6,9},{9,1},{7,8},{6,1},{7,7},{6,2},{4,0}};
std::list <std::pair<int,int>> lista;
double * macierz;
double ssum = 0;
double best = 99999999999;
void generuj(){
    int para[2];
    bool was = false;
    do{
        was = false;
        para[0] = rand()%PAR;
        para[1] = rand()%PAR;
        for(auto &i: lista){
            if(i.first==para[0]&&i.second==para[1]){
                was = true;
            }
        }
    }while(was);
    std::pair<int,int> wspolrzedne (para[0],para[1]);
    lista.push_back(wspolrzedne);
}

void zapisz(int mode=0){
    std::ofstream output;
    output.open("out.txt",std::ios::out);
    output << PAR<<"\n";
    if(mode==0){
        std::list <std::pair<int,int>>::iterator it1;
        it1 = lista.begin();
        for(int y = 1;y<=PAR;y++){
            output<<y<<" "<<it1->first<<" "<<it1->second;
        }
        if(it1!=lista.end()){it1++;}
    }
    else if(mode==1){
        for(int y = 0; y<PAR;y++){
            for(int x = 0; x<PAR;x++){
                output<<macierz[y*PAR+x]<<" ";
            }
            output<<"\n";
        }

    }
    output.close();
}

int wczytaj(int mode = 0){
    std::ifstream plik;
    int ile = 0;
    plik.open("in.txt",std::ios::in);
    if(mode ==0){
        ile =0;
        plik>>ile;
        int a,b,c;
        for(int y = 0; y<ile;y++){
            plik>>a>>b>>c;
            std::pair<int , int> nowa = {b,c};
            lista.push_back(nowa);
        }
        macierz = new double [ile*ile];
        std::list <std::pair<int,int>>::iterator it1,it2;
        it1 = lista.begin();
        for(int y = 0;y<ile;y++){
            it2 = lista.begin(); 
            for(int x = 0;x<ile;x++){
                macierz[y*ile+x]= sqrt((double)((it1->first-it2->first)*(it1->first-it2->first)+(it1->second - it2->second)*(it1->second - it2->second)));
                it2++;
            }
            it1++;
        }
    }
    else if(mode==1){
        ile =0;
        plik>>ile;
        macierz = new double [ile*ile];
        for(int y = 0;y<ile;y++){
            for(int x = 0;x<ile;x++){
                plik>>macierz[y*ile+x];
            }
        }
    }
    plik.close();
    return ile;
}


void generator(int ile){
    
    srand(time(NULL));
    for(int i=0;i<ile;i++){
        generuj();
    }
    macierz = new double [ile*ile];
    std::list <std::pair<int,int>>::iterator it1,it2;
    it1 = lista.begin();
    for(int y = 0;y<ile;y++){
        it2 = lista.begin(); 
        for(int x = 0;x<ile;x++){
            macierz[y*ile+x]= sqrt((double)((it1->first-it2->first)*(it1->first-it2->first)+(it1->second - it2->second)*(it1->second - it2->second)));
            it2++;
        }
        it1++;
    }
}

void wypisz(){
    int z = 1;
    std::cout<<PAR<<std::endl;
    for(auto &i: lista){
            std::cout<<z<<" "<<i.first<<" "<<i.second<<std::endl;
            z+=1;
        }
}

std::pair<int,int> * findclosest(std::pair<int,int> &curpoint){
    std::list <std::pair<int,int>>::iterator it1,it2,it3;
    double dist = 0;
    std::pair<int,int> lowest;

    for(it1=lista.begin(); it1!=lista.end();++it1){
        if (it1->first!=curpoint.first || it1->second!=curpoint.second){
            double z = sqrt((double)((it1->first-curpoint.first)*(it1->first-curpoint.first)+(it1->second - curpoint.second)*(it1->second - curpoint.second)));
            if (z<dist||dist==0){
                it3 = it1;
                dist = z;
            }
        }
        else{
            it2 = it1;
        }
    }
    std::cout<<it2->first<<" "<<it2->second<<" -> "<<it3->first<<" "<<it3->second<<" + "<<dist<<std::endl;
    lista.erase(it2);
    ssum+=dist;

    return &(*it3);
}

class Chromosome{
int* miasta;
double fitness;
double dist;
public:
Chromosome(){
    fitness = 0;
    miasta = nullptr;
}
~Chromosome(){
    delete [] miasta;
    miasta = nullptr;
}
void randomize(int size){
    miasta = new int [size];
    for(int i =0;i<size;i++){
        miasta[i]=rand()%(size-i);
    } 
}
void setmiast(int tab[]){
    miasta = tab;
}
void setfitness(double f){fitness  =f;}
double getfiness() const {return fitness;}
int * getmiast() const {return miasta;}
int getpos(int x) const {return *(miasta+x);}
void setdist(double x){dist = x;}
double getdist(){return dist;}
};

bool compare(const Chromosome &c1,const Chromosome &c2){

    return (c1.getfiness()>c2.getfiness());
}

class Population{
const int GENSIZE;
Chromosome * populacja;
public:
Population(int a): GENSIZE(a){
    populacja = new Chromosome [POPSIZE];
    for(int i = 0;i<POPSIZE;i++){
        populacja[i].randomize(GENSIZE);
        //std::cout<<i<<"\n";
        //for(int y=0;y<GENSIZE;y++){
            //std::cout<<(populacja[i].getmiast())[y]<<" ";
        //}
        //std::cout<<"\n";
    }
}
~Population(){
    delete [] populacja;
}
void evaluate(){
    int * toev = new int[GENSIZE];
    double maxdist = 0;
    int * pula = new int [GENSIZE];
    int curmia = 0;
    for(int i =0;i<POPSIZE;i++){
        //std::cout<<"iteracja "<<i<<"\n";
        //for(int g =0;g<POPSIZE;g++){
        //for(int y=0;y<GENSIZE;y++){std::cout<<(populacja[g].getmiast())[y]<<" ";}
        //std::cout<<"\n";}
        double dist = 0;
        for(int c = 0;c<GENSIZE;c++){toev[c] = populacja[i].getpos(c);}
        //std::cout<<"toev2\n";
        //for(int p =0;p<GENSIZE;p++){std::cout<<toev[p]<<" ";}
        
        for(int y=0;y<GENSIZE;y++){pula[y]=y;}
        curmia = pula[toev[0]];
        if(curmia>=GENSIZE){curmia = rand()%GENSIZE;}
        //std::cout<<"miasta"<<curmia<<" ";
        for(int z=toev[0];z<GENSIZE-1;z++){pula[z]=pula[z+1];}
        for(int y=1;y<GENSIZE;y++){
            dist+= macierz[curmia*GENSIZE+pula[toev[y]]];
            curmia = pula[toev[y]];
            if(curmia>=GENSIZE-i){curmia = rand()%(GENSIZE-i);}
            //std::cout<<curmia<<" ";
            for(int z=toev[y];z<GENSIZE-1;z++){pula[z]=pula[z+1];}   
        }
        //std::cout<<"\n";
        dist+= macierz[curmia*GENSIZE+toev[0]];
        populacja[i].setfitness(dist);
        populacja[i].setdist(dist);
        if(dist>maxdist){maxdist = dist;}
        if(dist<best){best = dist;}
        
    }
    delete [] pula;
    for(int i=0;i<POPSIZE;i++){
        populacja[i].setfitness(maxdist - populacja[i].getfiness());
    }

}

int * crossover(int par1 [],int par2[]){
 
    int * newgene = new int [GENSIZE];
    for(int y =0; y<GENSIZE/2;y++){
        newgene[y]=par1[y];
    }
    for(int y =GENSIZE/2; y<GENSIZE;y++){
        newgene[y]=par2[y];
    }
    int tomut = rand()%GENSIZE;
    newgene[tomut] = (rand()%(GENSIZE - tomut));
    
    //delete [] newgene;
    /*std::cout<<"par1\n";
    for(int y =0; y<GENSIZE;y++){
        //std::cout<<par1[y]<<" ";
    }
    //std::cout<<"\npar2\n";
    for(int y =0; y<GENSIZE;y++){
        //std::cout<<par2[y]<<" ";
    }
    //std::cout<<"\nnowy\n";
    for(int y =0; y<GENSIZE;y++){
        //std::cout<<newgene[y]<<" ";
    }
    //std::cout<<"\n";*/
    return newgene;
    
}

void select(){
    double suma = 0;
    int * f = new int [GENSIZE];
    int * s = new int [GENSIZE];
    std::sort(populacja,populacja+POPSIZE,compare);
    
    Chromosome * newpop = new Chromosome [POPSIZE];
    for(int x = 0;x<POPSIZE;x++){
        suma+=populacja[x].getfiness();
    }
    for(int y = 0;y<POPSIZE*ELITE;y++){
        newpop[y].setmiast(populacja[y].getmiast());
    }
    for(int x = 0; x<POPSIZE;x++){
        populacja[x].setfitness(populacja[x].getfiness()/suma);
    }
    double cursum = 0;
    for(int u = POPSIZE-1;u>=0;u--){
                cursum+=populacja[u].getfiness();
                populacja[u].setfitness(cursum);
    }
    int fiu = 0;
    for(int z = POPSIZE * ELITE;z<POPSIZE;z++){
        double r1 = ((double)(rand()%10000))/10000;
        for(int u = POPSIZE-1;u>=0;u--){
            //std::cout<<z<<" "<<u<<" "<<r1<<" "<<populacja[u].getfiness()<<"\n";
            if(populacja[u].getfiness()>=r1){
                fiu = u;
                break;
            }
        }
        int secu = 0;
        do{
            double r2 = ((double)(rand()%10000))/10000;
            for(int u = POPSIZE-1;u>=0;u--){
                if(populacja[u].getfiness()>=r2){
                    secu = u;
                    break;
                }
            }
        }while(fiu==secu);
        for(int m = 0;m<GENSIZE;m++){
        f[m] = (populacja[fiu].getmiast())[m];
        s[m] = (populacja[secu].getmiast())[m];
        }
        newpop[z].setmiast(crossover(f,s));
    }
    
    for(int p = 0; p<POPSIZE;p++){
        populacja[p].setmiast(newpop[p].getmiast());
        populacja[p].setfitness(0);
    }
    for(int i = 0;i<POPSIZE;i++){
        for(int y=0;y<GENSIZE;y++){
            std::cout<<(newpop[i].getmiast())[y]<<" ";
        }
        std::cout<<"\n";
    }
    for(int i = 0;i<POPSIZE;i++){
        for(int y=0;y<GENSIZE;y++){
            std::cout<<(populacja[i].getmiast())[y]<<" ";
        }
        std::cout<<"\n";
    }
    delete [] newpop;
    
}
double returnbest(){return populacja[0].getdist();}
};

int main(){
    //generator(PAR);
    //wypisz();
    wczytaj(0);
    std::pair<int,int> * current = &(lista.front());
       int startx = current->first;
    int starty = current->second;
    while(lista.size()>1){current = findclosest(*current);}
    ssum+= sqrt((double)((startx-current->first)*(startx-current->first)+(starty - current->second)*(starty - current->second)));
    std::cout<<ssum<<std::endl;
    for(int i=0;i<PAR;i++){
        for(int y = 0;y<PAR;y++){
            std::cout<<macierz[i*PAR+y]<<" ";
        }
        std::cout<<"\n";
    }
    Population pop(PAR);
    for(int loop = 0; loop<ITER; loop++){
    pop.evaluate();
    pop.select();
    }
    std::cout<<best;
    delete [] macierz;
    macierz = nullptr;
    return 0;
}