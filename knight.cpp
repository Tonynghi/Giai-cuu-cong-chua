#include "knight.h"

//function for MG3
int MG3(int arr[100], int size){
    int arr2[size];
    for(int c=0;c<size;c++){
        arr2[c]=abs(arr[c]);
        arr2[c]=(17*arr2[c]+9)%257;
    }
    int max= arr2[0];
    int maxi=0;
    int min = arr2[0];
    int mini=0;
    for (int i=0;i<size;i++){
        if(arr2[i] > max){
            max=arr2[i];
            maxi=i;
        }
        if(arr2[i]<min){
            min=arr2[i];
            mini=i;
        }
    }
    return maxi+mini;
}

//function for MG4
int MG4(int arr[100], int size){
    int arr2[size];
    for(int c=0;c<size;c++){
        arr2[c]=abs(arr[c]);
        arr2[c]=(17*arr2[c]+9)%257;
    }
    int max2_3x=arr2[0];
    int max2_3i=0;
    if (arr2[0] == arr2[1] && arr2[0] == arr2[2]){
        max2_3x=-5;
        max2_3i=-7;
    } else{
        if(arr2[0]<arr2[1]){
            if(arr2[1]>arr2[2]){
                if(arr2[2] > arr2[0]){
                    max2_3x=arr2[2];
                    max2_3i=2;
                }
            }
            else if(arr2[1] < arr2[2]){
                max2_3x=arr2[1];
                max2_3i=1;
            }
        } else if (arr2[0] == arr2[1]){
            if (arr2[0] > arr2[2]){
                max2_3x=arr2[2];
                max2_3i=2;
            }
        } else{
            if (arr2[1] >= arr2[2]){
                max2_3x=arr2[1];
                max2_3i=1;
            }
            else
            {
                if (arr2[2] == arr2[0])
                {
                    max2_3x=arr2[1];
                    max2_3i=1;
                } else if(arr2[2]<arr2[0]){
                    max2_3x=arr2[2];
                    max2_3i=2;
                }
                
            }
            
        }
    }
    return max2_3x+max2_3i;
}

//funtion for MG1
int sumMaMi(int a[100], int asize){
    int max= a[0];
    int maxi=0;
    int min = a[0];
    int mini=0;
    for (int i=0;i<asize;i++){
        if(a[i] >= max){
            max=a[i];
            maxi=i;
        }
        if(a[i]<=min){
            min=a[i];
            mini=i;
        }
    }
    return maxi+mini;
}


//function to find sum of n largest 2 digit odd numbers 
int sumn(int n){
    int sum = 0;
    int ini = 99;
    for (int i = 0; i < n; i++){
        sum+=ini;
        ini=ini-2;
    }
    return sum;
}

//function to check whether prime or not
bool isPrime(int n){
    if (n < 2) return false;
    else if(n==2) return true;
    else{
        for (int i=2;i<n;i++){
            if(n%i==0) return false;
        }
        return true;
    }
}

//function to find the nearest prime number
int nearestPrime(int anc){
    int nearestPrimenum=anc+1;
    while (!isPrime(nearestPrimenum)){
        nearestPrimenum++;
    }
    return nearestPrimenum;
}

//function to find the nearest fibonacci number
int nearestFibo(int n){
    int npre = 1;
    int npo = 1;
    int sum = 0;
    while (sum <= n){
        sum=npo+npre;
        npre=npo;
        npo=sum;
    }
    return npre;
}


void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue) {
    cout << "HP=" << HP
        << ", level=" << level
        << ", remedy=" << remedy
        << ", maidenkiss=" << maidenkiss
        << ", phoenixdown=" << phoenixdown
        << ", rescue=" << rescue << endl;
}

void adventureToKoopa(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue) {
    ifstream ifs(file_input);
    ifs >> HP;  ifs >> level; ifs >> remedy; ifs >> maidenkiss; ifs >> phoenixdown;
    rescue=-1;


    //stats limit
    int maxHP=HP;

    //isArthur
    bool isArthur = false;
    if(HP==999) isArthur=true;

    //isLan
    bool isLan=false;
    if(isPrime(HP)) isLan=true;

    int i = 1; //event order
    string evcodestr;
    int evcode; //event code
    
    //enemy stats
    int b; //level calc
    int LevO; //level of enemy
    double baseDam; //baseDamage for each enemy

    //smol state variable
    bool isSmol = false; //Smol state after fighting with Shaman
    int smolCd = -1; //Cooldown of Smol

    //frog state variable
    bool isFrog = false; //frog state after fighting with Siren Vajsh
    int frogCd = -1;
    int oldLev; //old level

    //event list
    string eventstring;
    stringstream eventstream;
    getline(ifs, eventstring);getline(ifs, eventstring);
    int eventarraysize=0;
    eventstream << eventstring;
    string eventarr[100];
    while(eventstream >> eventarr[eventarraysize]) eventarraysize++; 

    //input files
    string filemgname;
    string fileasclname;
    string filemername;
    getline(ifs, filemgname,',');getline(ifs, fileasclname,',');getline(ifs, filemername);

    //asclepius
    bool asclemet=false;

    //merlin
    bool merlinmet=false;

    for(int r = 0; r<eventarraysize; r++){
        evcode=stoi(eventarr[r]);
        
        b = i%10;
        LevO = i>6?(b>5?b : 5) : b; //LevelO Calculation

        //mushMario
        int n1; //number of largest 2-digit odd numbers
        int s1; //sum of n1


        switch (evcode)
        {
        case 0:
        {
            rescue=1;
            break;
        }
        case 1: //MadBear
        {
            baseDam=1;
            if(level > LevO || isArthur) level++;
            else if(level < LevO) HP -= baseDam*LevO*10;
            break;
        }
        case 2: //Bandit
        {
            baseDam=1.5;
            if(level > LevO || isArthur) level++;
            else if(level < LevO) HP -= baseDam*LevO*10;
            break;
        }
        case 3: //LordLupin
        {
            baseDam=4.5;
            if(level > LevO || isArthur) level++;
            else if(level < LevO) HP -= baseDam*LevO*10;
            break;
        }
        case 4: //Elf
        {
            baseDam=7.5;
            if(level > LevO || isArthur) level++;
            else if(level < LevO) HP -= baseDam*LevO*10;
            break;
        }
        case 5: 
        {
            baseDam=9.5;
            if(level > LevO || isArthur) level++;
            else if(level < LevO) HP -= baseDam*LevO*10;
            break;
        }
        case 6:
        {
            if(level > LevO || isArthur) level+=2;
            else if(level < LevO){
                if (!isSmol && !isFrog){
                    smolCd=4;
                    isSmol=true;
                    HP=HP/5;
                    if(HP<1) HP=1;
                }
            };
            break;
        }
        case 7:
        {
            if(level > LevO || isArthur) level+=2;
            else if(level < LevO){
                if (!isFrog && !isSmol){
                    frogCd=3;
                    isFrog=true;
                    oldLev=level;
                    level=1;
                }
            };
            break;
        }
        case 11:
        {
            n1=((level + phoenixdown)%5 + 1)*3;
            s1= sumn(n1);
            HP=HP+(s1%100);
            HP=nearestPrime(HP);
            if(HP>maxHP)HP=maxHP;
            break;
        }
        case 12:
        {
            if(HP>1) HP=nearestFibo(HP);
            break;
        }
        case 15:
        {
            remedy=remedy+1;
            if(remedy>99) remedy=99;
            break;
        }
        case 16:
        {
            maidenkiss=maidenkiss+1;
            if(maidenkiss>99) maidenkiss=99;
            break;
        }
        case 17:
        {
            phoenixdown=phoenixdown+1;
            if(phoenixdown>99) phoenixdown=99;
            break;
        }
        case 18:
        {
            if (!merlinmet){
                ifstream merl(filemername);
                int n9;
                merl >> n9;
                string itnm;
                int qualitnm=0; //qualified item name
                for (int a=0; a<n9; a++){
                    merl >> itnm;
                    if(itnm.find("Merlin") != string::npos || itnm.find("merlin") != string::npos){
                        HP=HP+3;
                        if(HP>maxHP)HP=maxHP;
                        continue;
                    }
                    if(itnm.find('M') != string::npos || itnm.find('m') != string::npos) qualitnm++;
                    if(itnm.find('E') != string::npos || itnm.find('e') != string::npos) qualitnm=qualitnm+1;
                    if(itnm.find('R') != string::npos || itnm.find('r') != string::npos) qualitnm+=1;
                    if(itnm.find('L') != string::npos || itnm.find('l') != string::npos) qualitnm += 1;
                    if(itnm.find('I') != string::npos || itnm.find('i') != string::npos) qualitnm = qualitnm + 1;
                    if(itnm.find('N') != string::npos || itnm.find('n') != string::npos) qualitnm++;
                    if (qualitnm==6){
                        HP+=2;
                        if(HP>maxHP)HP=maxHP;
                    }
                }
                merlinmet=true;    
            }
            break;
        }
        case 19:
        {
            if(!asclemet){
                ifstream ascle(fileasclname);
                int r1, c1;
                int rowlim; int potion;
                ascle >> r1; ascle >> c1;
                for(int i=0;i<r1;i++){
                    rowlim=3;
                    for(int j=0;j<c1;j++){
                        ascle>>potion;
                        if (potion==16 && rowlim>0){ 
                            remedy=remedy+1;
                            if(remedy>99) remedy=99;
                            if(isSmol){
                                remedy--;
                                isSmol=false;
                                smolCd=-1;
                                HP=HP*5;
                            }
                            rowlim=rowlim-1;
                        }
                        else if(potion==17 && rowlim>0){
                            maidenkiss=maidenkiss+1;
                            if(maidenkiss>99) maidenkiss=99;
                            if(isFrog){
                                isFrog=false;
                                level=oldLev;
                                maidenkiss--;
                                frogCd=-1;
                            }
                            rowlim=rowlim-1;
                        }
                        else if (potion==18 && rowlim>0){
                            phoenixdown++;
                            if(phoenixdown>99) phoenixdown=99;
                            rowlim=rowlim-1;
                        }
                    }
                }
                asclemet=true;
            }
            break;
        }
        case 99:
        {
            if (isArthur) level=10;
            else if (isLan && level>7) level=10;
            else if(level==10)level=10;
            else return;
            break;
        }
        default:
        {
            ifstream namma(filemgname);
            int n2;
            namma >> n2;
            string n2hold;
            int n2int[n2];
            getline(namma,n2hold);
            for(int h=0;h<n2-1;h++){
                getline(namma,n2hold,',');
                n2int[h]=stoi(n2hold);
            }
            getline(namma,n2hold);
            n2int[n2-1]=stoi(n2hold);
            string evcodemg = to_string(evcode);
            int mgsize=0;
            while(evcode>0){
                mgsize++;
                evcode=evcode/10;
            }
            for(int i=2;i<mgsize;i++){
                switch (evcodemg[i])
                {
                case '1':
                {
                    HP=HP-sumMaMi(n2int, n2);
                    if(HP>maxHP) HP=maxHP;
                    if(HP<=0){
                        if(phoenixdown>0){
                            HP=maxHP;
                            if(isSmol){
                                isSmol=false;
                                smolCd=-1;
                            }
                            if (isFrog){
                                level=oldLev;
                                isFrog=false;
                                frogCd=-1;
                            }
                            phoenixdown--;
                        }
                        else break;
                    }
                    break;
                }
                case '2':
                {
                    bool isMou=true;
                    bool peak=false;
                    int i=1;
                    int mtx=n2int[0];
                    int mti=0;
                    while (i<n2){
                        if(!peak){
                            if(n2int[i]>n2int[i-1]){
                                mti=i;
                                mtx=n2int[i];
                            }
                            else if(n2int[i]<n2int[i-1]){
                                peak=true;
                            }
                            else{
                                isMou=false;
                                break;
                            }
                        }
                        else{
                            if(n2int[i]>=n2int[i-1]){
                                break;
                                isMou=false;
                            }
                        }
                        i++;
                    }
                    if (isMou) HP=HP-(mtx+mti);
                    else HP+=5;
                    if (HP>maxHP)HP=maxHP;
                    if(HP<=0){
                        if(phoenixdown>0){
                            HP=maxHP;
                            if(isSmol){
                                isSmol=false;
                                smolCd=-1;
                            }
                            if (isFrog){
                                level=oldLev;
                                isFrog=false;
                                frogCd=-1;
                            }
                            phoenixdown--;
                        }
                        else break;
                    }
                    break;
                }
                case '3':
                {
                    HP=HP-MG3(n2int, n2);
                    if (HP>maxHP)HP=maxHP;
                    if(HP<=0){
                        if(phoenixdown>0){
                            HP=maxHP;
                            if(isSmol){
                                isSmol=false;
                                smolCd=-1;
                            }
                            if (isFrog){
                                level=oldLev;
                                isFrog=false;
                                frogCd=-1;
                            }
                            phoenixdown--;
                        }
                        else break;
                    }
                    break;
                }
                case '4':
                {
                    HP=HP-MG4(n2int,n2);
                    if (HP>maxHP)HP=maxHP;
                    if(HP<=0){
                        if(phoenixdown>0){
                            HP=maxHP;
                            if(isSmol){
                                isSmol=false;
                                smolCd=-1;
                            }
                            if (isFrog){
                                level=oldLev;
                                isFrog=false;
                                frogCd=-1;
                            }
                            phoenixdown--;
                        }
                        else break;
                    }
                    break;
                }
                default:
                    break;
                }
            }
            break;
        }
        }
        //smol
        if (isSmol && smolCd > 0){
            if (remedy>0){
                smolCd=0;
                remedy=remedy-1;
            }
            else smolCd--;
        }
        if (smolCd==0){
            HP=HP*5;
            if(HP>maxHP) HP = maxHP;
            isSmol=false;
            smolCd--;
        }

        //frog
        if (isFrog && frogCd > 0){
            if (remedy>0){
                frogCd=0;
                remedy=remedy-1;
            }
            else frogCd--;
        }
        if (frogCd==0){
            level=oldLev;
            isFrog=false;
            frogCd--;
        }
        if (HP<=0){
            if (phoenixdown>0){
                HP=maxHP;
                            if(isSmol){
                                isSmol=false;
                                smolCd=-1;
                            }
                            if (isFrog){
                                level=oldLev;
                                isFrog=false;
                                frogCd=-1;
                            }
                phoenixdown=phoenixdown-1;
            } else{
                rescue=0;
            }
        }
        if (level>10) level=10;
        if(r+1==eventarraysize) rescue=1;
        display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
        i++; //event order
        if (rescue==1 || rescue==0) return; //end game if guini is rescued or knight is dead
    }
}