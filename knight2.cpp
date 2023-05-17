#include "knight2.h"

//Prime check function
bool isPrime(int n){
    if (n < 2) return false;
    else if(n ==2 ) return true;
    else {
        for (int i = 2; i<n; i++){
            if(n%i==0) return false;
        }
        return true;
    }
}

//Pythagoras set check function
bool isPyt(int n){
    int a, b, c;
    if (n > 100 && n < 999){
        int nclone = n; //clone to hold maxhp data

        //input digits
        a = nclone / 100;
        nclone = nclone%100;
        b = nclone / 10;
        nclone = nclone%10;
        c = nclone;

        //function
        if (pow(a, 2) == pow(b, 2) + pow(c, 2)) return true;
        else if (pow(b, 2) == pow(a, 2) + pow(c, 2)) return true;
        else if (pow(c, 2) == pow(b, 2) + pow(a, 2)) return true;
        else return false;
    } else return false;
}

/* * * BEGIN implementation of SLL node Slot * * */

Slot::Slot(BaseItem * item){
    this->item = item;
    this->next = nullptr;
};

/* * * END implementation of SLL node Slot * * */

/* * * BEGIN implementation of class BaseBag * * */

/*
void BaseBag::add_Item(BaseItem * item){
    if(this->Amount < this->Max){
        Slot * new_Item = new Slot(item);
        new_Item->next = this->head;
        this->head = new_Item;
        Amount++;
    }
};*/


//PaladinBag
void PaladinBag::add_Item(BaseItem * item){
    Slot * new_Item = new Slot(item);
    new_Item->next = this->head;
    this->head = new_Item;
    if(item->getType()==ANTIDOTE) this->AntiAmount++;
    else this->PhoenixAmount++;
    this->Amount++;
};

void PaladinBag::deleteFirst(){
    if(head==nullptr) return;
    else{
        Slot * temp = this->head;
        this->head = this->head->next;
        delete temp;
        this->Amount--;
    }
};

PaladinBag::PaladinBag(BaseKnight * Knight, int phoenixdownI, int antidote){
    this->knight = Knight;

    //point head to null first
    this->head = nullptr;

    //add PhoenixDownI
    for(int i = 0; i < phoenixdownI; i++){
        this->add_Item(PhoenixDownIPtr);
    }

    //add antidote
    for(int i = 0; i < antidote; i++){
        this->add_Item(AntidotePtr);
    }
    
};

bool PaladinBag::insertFirst(BaseItem * item){
    return true;
};

BaseItem * PaladinBag::get(ItemType itemType){
    Slot * tmp = this->head;
    while(tmp != nullptr){
        if(tmp->item->getType() == itemType){
            return tmp->item;
        }
        else tmp = tmp->next;
    }
    return nullptr;
};

void PaladinBag::UseAntidote(){
    if(AntiAmount>0){
        Slot * tmp = this->head;
        for(int i = 0; i < this->Amount; i++){
            if(tmp->item->getType() == ANTIDOTE){
                break;
            } else tmp = tmp->next;
        }
        
        BaseItem * itemhold = tmp->item;
        tmp->item = this->head->item;
        this->head->item = itemhold;

        this->deleteFirst();
        this->AntiAmount--;
    } else return;
};

void PaladinBag::UseFirstPhoenix(){
    if(PhoenixAmount > 0){
        Slot * tmp = this->head;
        for(int i = 0; i < this->Amount; i++){
            if(2*this->knight->getHP() <= this->knight->getMAXHP()){
                if(tmp->item->getType() == PHOENIXDOWNIV) break;
                else if(3*this->knight->getHP() <= this->knight->getMAXHP()){
                    if(tmp->item->getType() == PHOENIXDOWNIII) break;
                    else if(4*this->knight->getHP() <= this->knight->getMAXHP()){
                        if(tmp->item->getType() == PHOENIXDOWNII) break;
                        else if(this->knight->getHP() <= 0){
                            if(tmp->item->getType() == PHOENIXDOWNI) break;
                        }
                    }
                }
            }
            tmp = tmp->next;
        }
        
        if(tmp == nullptr) return;

        BaseItem * itemhold = tmp->item;
        tmp->item = this->head->item;
        this->head->item = itemhold;

        this->head->item->use(this->knight);
        this->deleteFirst();
        this->PhoenixAmount--;
    } else return;
};

string PaladinBag::toString() const{
    string BagInfo = "Bag[count=" + to_string(Amount) + ";";

    string typeItem[5] = {"Antidote", "PhoenixI", "PhoenixII", "PhoenixIII", "PhoenixIV"};

    if(head == nullptr){
        BagInfo += "]";
    } else {
        Slot * tmp;
        tmp = head;

        while (tmp->next != nullptr){
            BagInfo += typeItem[tmp->item->getType()] + ",";
            tmp = tmp->next;
        }

        BagInfo += typeItem[tmp->item->getType()] + "]";
    }

    return BagInfo;
};

//DragonBag
void DragonBag::add_Item(BaseItem * item){
    Slot * new_Item = new Slot(item);
    new_Item->next = this->head;
    this->head = new_Item;
    this->PhoenixAmount++;
    this->Amount++;
};

void DragonBag::deleteFirst(){
    if(head==nullptr) return;
    else{
        Slot * temp = this->head;
        this->head = this->head->next;
        delete temp;
        this->Amount--;
    }
};

DragonBag::DragonBag(BaseKnight * Knight, int phoenixdownI, int antidote){
    this->knight = Knight;

    //point head to null first
    this->head = nullptr;

    //add PhoenixDownI
    for(int i = 0; i < phoenixdownI; i++){
        this->add_Item(PhoenixDownIPtr);
    }

    //add antidote
    for(int i = 0; i < antidote; i++){
        this->add_Item(AntidotePtr);
    }
    
};

bool DragonBag::insertFirst(BaseItem * item){
    if(item->getType() == ANTIDOTE ) return false;
    else{
        if(this->Amount < this->Max) return true;
        else return false;
    }
};

BaseItem * DragonBag::get(ItemType itemType){
    Slot * tmp = this->head;
    while(tmp != nullptr){
        if(tmp->item->getType() == itemType){
            return tmp->item;
        }
        else tmp = tmp->next;
    }
    return nullptr;
};

void DragonBag::UseAntidote(){
    return;
};

void DragonBag::UseFirstPhoenix(){
    if(PhoenixAmount > 0){
        Slot * tmp = this->head;
        for(int i = 0; i < this->Amount; i++){
            if(2*this->knight->getHP() <= this->knight->getMAXHP()){
                if(tmp->item->getType() == PHOENIXDOWNIV) break;
                else if(3*this->knight->getHP() <= this->knight->getMAXHP()){
                    if(tmp->item->getType() == PHOENIXDOWNIII) break;
                    else if(4*this->knight->getHP() <= this->knight->getMAXHP()){
                        if(tmp->item->getType() == PHOENIXDOWNII) break;
                        else if(this->knight->getHP() <= 0){
                            if(tmp->item->getType() == PHOENIXDOWNI) break;
                        }
                    }
                }
            }
            tmp = tmp->next;
        }
        
        if(tmp == nullptr) return;

        BaseItem * itemhold = tmp->item;
        tmp->item = this->head->item;
        this->head->item = itemhold;

        this->head->item->use(this->knight);
        this->deleteFirst();
        this->PhoenixAmount--;
    } else return;
};

string DragonBag::toString() const{
    string BagInfo = "Bag[count=" + to_string(Amount) + ";";

    string typeItem[5] = {"Antidote", "PhoenixI", "PhoenixII", "PhoenixIII", "PhoenixIV"};

    if(head == nullptr){
        BagInfo += "]";
    } else {
        Slot * tmp;
        tmp = head;

        while (tmp->next != nullptr){
            BagInfo += typeItem[tmp->item->getType()] + ",";
            tmp = tmp->next;
        }

        BagInfo += typeItem[tmp->item->getType()] + "]";
    }

    return BagInfo;
};

//LancelotBag
void LancelotBag::add_Item(BaseItem * item){
    Slot * new_Item = new Slot(item);
    new_Item->next = this->head;
    this->head = new_Item;
    if(item->getType()==ANTIDOTE) this->AntiAmount++;
    else this->PhoenixAmount++;
    this->Amount++;
};

void LancelotBag::deleteFirst(){
    if(head==nullptr) return;
    else{
        Slot * temp = this->head;
        this->head = this->head->next;
        delete temp;
        this->Amount--;
    }
};

LancelotBag::LancelotBag(BaseKnight * Knight, int phoenixdownI, int antidote){
    this->knight = Knight;

    //point head to null first
    this->head = nullptr;

    //add PhoenixDownI
    for(int i = 0; i < phoenixdownI; i++){
        this->add_Item(PhoenixDownIPtr);
    }

    //add antidote
    for(int i = 0; i < antidote; i++){
        this->add_Item(AntidotePtr);
    }
    
};

bool LancelotBag::insertFirst(BaseItem * item){
    if(this->Amount < this->Max) return true;
    else return false;
};

BaseItem * LancelotBag::get(ItemType itemType){
    Slot * tmp = this->head;
    while(tmp != nullptr){
        if(tmp->item->getType() == itemType){
            return tmp->item;
        }
        else tmp = tmp->next;
    }
    return nullptr;
};

void LancelotBag::UseAntidote(){
    if(AntiAmount>0){
        Slot * tmp = this->head;
        for(int i = 0; i < this->Amount; i++){
            if(tmp->item->getType() == ANTIDOTE){
                break;
            } else tmp = tmp->next;
        }
        
        BaseItem * itemhold = tmp->item;
        tmp->item = this->head->item;
        this->head->item = itemhold;

        this->deleteFirst();
        this->AntiAmount--;
    } else return;
};

void LancelotBag::UseFirstPhoenix(){
    if(PhoenixAmount > 0){
        Slot * tmp = this->head;
        for(int i = 0; i < this->Amount; i++){
            if(2*this->knight->getHP() <= this->knight->getMAXHP()){
                if(tmp->item->getType() == PHOENIXDOWNIV) break;
                else if(3*this->knight->getHP() <= this->knight->getMAXHP()){
                    if(tmp->item->getType() == PHOENIXDOWNIII) break;
                    else if(4*this->knight->getHP() <= this->knight->getMAXHP()){
                        if(tmp->item->getType() == PHOENIXDOWNII) break;
                        else if(this->knight->getHP() <= 0){
                            if(tmp->item->getType() == PHOENIXDOWNI) break;
                        }
                    }
                }
            }
            tmp = tmp->next;
        }
        
        if(tmp == nullptr) return;

        BaseItem * itemhold = tmp->item;
        tmp->item = this->head->item;
        this->head->item = itemhold;

        this->head->item->use(this->knight);
        this->deleteFirst();
        this->PhoenixAmount--;
    } else return;
};

string LancelotBag::toString() const{
    string BagInfo = "Bag[count=" + to_string(Amount) + ";";

    string typeItem[5] = {"Antidote", "PhoenixI", "PhoenixII", "PhoenixIII", "PhoenixIV"};

    if(head == nullptr){
        BagInfo += "]";
    } else {
        Slot * tmp;
        tmp = head;

        while (tmp->next != nullptr){
            BagInfo += typeItem[tmp->item->getType()] + ",";
            tmp = tmp->next;
        }

        BagInfo += typeItem[tmp->item->getType()] + "]";
    }

    return BagInfo;
};

//NormalBag
void NormalBag::add_Item(BaseItem * item){
    Slot * new_Item = new Slot(item);
    new_Item->next = this->head;
    this->head = new_Item;
    if(item->getType()==ANTIDOTE) this->AntiAmount++;
    else this->PhoenixAmount++;
    this->Amount++;
};

void NormalBag::deleteFirst(){
    if(head==nullptr) return;
    else{
        Slot * temp = this->head;
        this->head = this->head->next;
        delete temp;
        this->Amount--;
    }
};

NormalBag::NormalBag(BaseKnight * Knight, int phoenixdownI, int antidote){
    this->knight = Knight;

    //point head to null first
    this->head = nullptr;

    //add PhoenixDownI
    for(int i = 0; i < phoenixdownI; i++){
        this->add_Item(PhoenixDownIPtr);
    }

    //add antidote
    for(int i = 0; i < antidote; i++){
        this->add_Item(AntidotePtr);
    }
    
};

bool NormalBag::insertFirst(BaseItem * item){
    if(this->Amount < this->Max) return true;
    else return false;
};

BaseItem * NormalBag::get(ItemType itemType){
    Slot * tmp = this->head;
    while(tmp != nullptr){
        if(tmp->item->getType() == itemType){
            return tmp->item;
        }
        else tmp = tmp->next;
    }
    return nullptr;
};

void NormalBag::UseAntidote(){
    if(AntiAmount>0){
        Slot * tmp = this->head;
        for(int i = 0; i < this->Amount; i++){
            if(tmp->item->getType() == ANTIDOTE){
                break;
            } else tmp = tmp->next;
        }
        
        BaseItem * itemhold = tmp->item;
        tmp->item = this->head->item;
        this->head->item = itemhold;

        this->deleteFirst();
        this->AntiAmount--;
    } else return;
};

void NormalBag::UseFirstPhoenix(){
    if(PhoenixAmount > 0){
        Slot * tmp = this->head;
        for(int i = 0; i < this->Amount; i++){
            if(2*this->knight->getHP() <= this->knight->getMAXHP()){
                if(tmp->item->getType() == PHOENIXDOWNIV) break;
                else if(3*this->knight->getHP() <= this->knight->getMAXHP()){
                    if(tmp->item->getType() == PHOENIXDOWNIII) break;
                    else if(4*this->knight->getHP() <= this->knight->getMAXHP()){
                        if(tmp->item->getType() == PHOENIXDOWNII) break;
                        else if(this->knight->getHP() <= 0){
                            if(tmp->item->getType() == PHOENIXDOWNI) break;
                        }
                    }
                }
            }
            tmp = tmp->next;
        }
        
        if(tmp == nullptr) return;

        BaseItem * itemhold = tmp->item;
        tmp->item = this->head->item;
        this->head->item = itemhold;

        this->head->item->use(this->knight);
        this->deleteFirst();
        this->PhoenixAmount--;
    } else return;
};

string NormalBag::toString() const{
    string BagInfo = "Bag[count=" + to_string(Amount) + ";";

    string typeItem[5] = {"Antidote", "PhoenixI", "PhoenixII", "PhoenixIII", "PhoenixIV"};

    if(head == nullptr){
        BagInfo += "]";
    } else {
        Slot * tmp;
        tmp = head;

        while (tmp->next != nullptr){
            BagInfo += typeItem[tmp->item->getType()] + ",";
            tmp = tmp->next;
        }

        BagInfo += typeItem[tmp->item->getType()] + "]";
    }

    return BagInfo;
};

/* * * END implementation of class BaseBag * * */

/* * * BEGIN implementation of class BaseItem * * */

ItemType Antidote::getType(){
    return type;
};

bool Antidote::canUse(BaseKnight * knight){
    if (knight->poisioned) return true;
    else return false;
};

void Antidote::use(BaseKnight * knight){
    if (Antidote::canUse(knight)) knight->poisioned = false;
};

ItemType PhoenixDownI::getType(){
    return type;
};

bool PhoenixDownI::canUse(BaseKnight * knight){
    if (knight->getHP() <= 0) return true;
    else return false;
};

void PhoenixDownI::use(BaseKnight * knight){
    if (PhoenixDownI::canUse(knight)) knight->setHP(knight->getMAXHP());
};

ItemType PhoenixDownII::getType(){
    return type;
};

bool PhoenixDownII::canUse(BaseKnight * knight){
    if (knight->getHP() < (knight->getMAXHP()/4)) return true;
    else return false;
};

void PhoenixDownII::use(BaseKnight * knight){
    if (PhoenixDownII::canUse(knight)) knight->setHP(knight->getMAXHP());
};

ItemType PhoenixDownIII::getType(){
    return type;
};

bool PhoenixDownIII::canUse (BaseKnight * knight){
    if (knight->getHP() < (knight->getMAXHP()/3)) return true;
    else return false;
};

void PhoenixDownIII::use(BaseKnight * knight){
    if (PhoenixDownIII::canUse(knight)){
        if (knight->getHP() <= 0) knight->setHP(knight->getMAXHP());
        else knight->setHP(knight->getHP() + knight->getMAXHP()/4);
    } 
};

ItemType PhoenixDownIV::getType(){
    return type;
};

bool PhoenixDownIV::canUse(BaseKnight * knight){
    if (knight->getHP() < (knight->getMAXHP()/2)) return true;
    else return false;
};

void PhoenixDownIV::use(BaseKnight * knight){
    if (PhoenixDownIV::canUse(knight)){
        if (knight->getHP() <= 0) knight->setHP(knight->getMAXHP());
        else knight->setHP(knight->getHP() + knight->getMAXHP()/5);
    } 
};

/* * * END implementation of class BaseItem * * */

/* * * BEGIN implementation of class Events * * */
Events::Events(const string file_events){
    //input file
    ifstream ev(file_events);

    // getting number of events
    ev >> NumOfEvents;

    //string & stream to store event list
    string EventString;
    stringstream EventStream;
    string StringEventList[NumOfEvents];

    //add event list into stream
    getline(ev, EventString);
    getline(ev, EventString);
    EventStream << EventString;

    //add events into a string array
    for(int i = 0; i < NumOfEvents; i++){
        EventStream >> StringEventList[i];
    }
    
    EventList = new int[NumOfEvents];

    //covert array to int
    for(int i = 0; i < NumOfEvents; i++){
        EventList[i] = stoi(StringEventList[i]);
    }
};

Events::~Events(){
    delete[] EventList;
}

int Events::count() const {
    return NumOfEvents;
};

int Events::get(int i) const {
    return EventList[i];
}

/* * * END implementation of class Events * * */

/* * * BEGIN implementation of class BaseOpponent * * */


//MadBear
void MadBear::levelOCalc(int i){
    this->levelO = (i + this->eventid)%10 + 1;
};

void MadBear::dealDam(BaseKnight * knight){
    knight->setHP( knight->getHP() - this->baseDam*(this->levelO - knight->getLEVEL()));
};

int MadBear::getGil(){
    return this->gil;
};

int MadBear::getID(){
    return this->eventid;
};

int MadBear::getLEVELO(){
    return this->levelO;
};

/* omit function */
void MadBear::dealPoisionDam(BaseKnight * knight){return;};
int MadBear::WinBet(BaseKnight * knight){return 0;};
void MadBear::LoseBet(BaseKnight * knight){return;};
void MadBear::HPSell(BaseKnight * knight){return;};
void MadBear::MaxHPregen(BaseKnight * knight){return;};
void MadBear::OWfight(ArmyKnights * army, BaseKnight * knight){return;};
void MadBear::Hadesfight(ArmyKnights * army, BaseKnight * knight){return;};
/* omit function */


//Bandit
void Bandit::levelOCalc(int i){
    this->levelO = (i + this->eventid)%10 + 1;
};

void Bandit::dealDam(BaseKnight * knight){
    knight->setHP( knight->getHP() - baseDam*(levelO - knight->getLEVEL()));
};

int Bandit::getGil(){
    return this->gil;
};

int Bandit::getID(){
    return this->eventid;
};

int Bandit::getLEVELO(){
    return this->levelO;
};

/* omit function */
void Bandit::dealPoisionDam(BaseKnight * knight){return;};
int Bandit::WinBet(BaseKnight * knight){return 0;};
void Bandit::LoseBet(BaseKnight * knight){return;};
void Bandit::HPSell(BaseKnight * knight){return;};
void Bandit::MaxHPregen(BaseKnight * knight){return;};
void Bandit::OWfight(ArmyKnights * army, BaseKnight * knight){return;};
void Bandit::Hadesfight(ArmyKnights * army, BaseKnight * knight){return;};
/* omit function */


//LordLupin
void LordLupin::levelOCalc(int i){
    this->levelO = (i + this->eventid)%10 + 1;
};

void LordLupin::dealDam(BaseKnight * knight){
    knight->setHP( knight->getHP() - baseDam*(levelO - knight->getLEVEL()));
};

int LordLupin::getGil(){
    return this->gil;
};

int LordLupin::getID(){
    return this->eventid;
};

int LordLupin::getLEVELO(){
    return this->levelO;
};

/* omit function */
void LordLupin::dealPoisionDam(BaseKnight * knight){return;};
int LordLupin::WinBet(BaseKnight * knight){return 0;};
void LordLupin::LoseBet(BaseKnight * knight){return;};
void LordLupin::HPSell(BaseKnight * knight){return;};
void LordLupin::MaxHPregen(BaseKnight * knight){return;};
void LordLupin::OWfight(ArmyKnights * army, BaseKnight * knight){return;};
void LordLupin::Hadesfight(ArmyKnights * army, BaseKnight * knight){return;};
/* omit function */


//Elf
void Elf::levelOCalc(int i){
    this->levelO = (i + this->eventid)%10 + 1;
};

void Elf::dealDam(BaseKnight * knight){
    knight->setHP( knight->getHP() - baseDam*(levelO - knight->getLEVEL()));
};

int Elf::getGil(){
    return this->gil;
};

int Elf::getID(){
    return this->eventid;
};

int Elf::getLEVELO(){
    return this->levelO;
};

/* omit function */
void Elf::dealPoisionDam(BaseKnight * knight){return;};
int Elf::WinBet(BaseKnight * knight){return 0;};
void Elf::LoseBet(BaseKnight * knight){return;};
void Elf::HPSell(BaseKnight * knight){return;};
void Elf::MaxHPregen(BaseKnight * knight){return;};
void Elf::OWfight(ArmyKnights * army, BaseKnight * knight){return;};
void Elf::Hadesfight(ArmyKnights * army, BaseKnight * knight){return;};
/* omit function */


//Troll
void Troll::levelOCalc(int i){
    this->levelO = (i + this->eventid)%10 + 1;
};

void Troll::dealDam(BaseKnight * knight){
    knight->setHP( knight->getHP() - baseDam*(levelO - knight->getLEVEL()));
};

int Troll::getGil(){
    return this->gil;
};

int Troll::getID(){
    return this->eventid;
};

int Troll::getLEVELO(){
    return this->levelO;
};

/* omit function */
void Troll::dealPoisionDam(BaseKnight * knight){return;};
int Troll::WinBet(BaseKnight * knight){return 0;};
void Troll::LoseBet(BaseKnight * knight){return;};
void Troll::HPSell(BaseKnight * knight){return;};
void Troll::MaxHPregen(BaseKnight * knight){return;};
void Troll::OWfight(ArmyKnights * army, BaseKnight * knight){return;};
void Troll::Hadesfight(ArmyKnights * army, BaseKnight * knight){return;};
/* omit function */


//Tornberry
void Tornberry::levelOCalc(int i){
    this->levelO = (i + this->eventid)%10 + 1;
};

void Tornberry::dealPoisionDam(BaseKnight * knight){
    if(knight->getKNIGHTTYPE() != DRAGON){
        knight->poisioned = true;
    }
}

int Tornberry::getID(){
    return this->eventid;
};

int Tornberry::getLEVELO(){
    return this->levelO;
};

/* omit function */
int Tornberry::getGil(){return 0;};
void Tornberry::dealDam(BaseKnight * knight){return;};
int Tornberry::WinBet(BaseKnight * knight){return 0;};
void Tornberry::LoseBet(BaseKnight * knight){return;};
void Tornberry::HPSell(BaseKnight * knight){return;};
void Tornberry::MaxHPregen(BaseKnight * knight){return;};
void Tornberry::OWfight(ArmyKnights * army, BaseKnight * knight){return;};
void Tornberry::Hadesfight(ArmyKnights * army, BaseKnight * knight){return;};
/* omit function */


//QueenOfCards
void QueenOfCards::levelOCalc(int i){
    this->levelO = (i + this->eventid)%10 + 1;
};

int QueenOfCards::WinBet(BaseKnight * knight){
    return knight->getGIL() * 2;
};

void QueenOfCards::LoseBet(BaseKnight * knight){
    knight->setGIL(knight->getGIL() / 2);
};

int QueenOfCards::getID(){
    return this->eventid;
};

int QueenOfCards::getLEVELO(){
    return this->levelO;
};

/* omit function */
int QueenOfCards::getGil(){return 0;};
void QueenOfCards::dealDam(BaseKnight * knight){return;};
void QueenOfCards::dealPoisionDam(BaseKnight * knight){return;};
void QueenOfCards::HPSell(BaseKnight * knight){return;};
void QueenOfCards::MaxHPregen(BaseKnight * knight){return;};
void QueenOfCards::OWfight(ArmyKnights * army, BaseKnight * knight){return;};
void QueenOfCards::Hadesfight(ArmyKnights * army, BaseKnight * knight){return;};
/* omit function */


//NinadeRings
void NinadeRings::HPSell(BaseKnight * knight){
    if (knight->getKNIGHTTYPE() == PALADIN){
        knight->setHP(knight->getHP() + knight->getMAXHP()/5);
    } else{
        if ((knight->getHP() < knight->getMAXHP()/3) && knight->getGIL() >= 50){
            knight->setGIL(knight->getGIL() - 50);
            knight->setHP(knight->getHP() + knight->getMAXHP()/5);
        }
    }
};

int NinadeRings::getID(){
    return this->eventid;
};

/* omit function */
int NinadeRings::getLEVELO(){return 0;};
int NinadeRings::getGil(){return 0;};
void NinadeRings::levelOCalc(int i){return;};
void NinadeRings::dealDam(BaseKnight * knight){return;};
void NinadeRings::dealPoisionDam(BaseKnight * knight){return;};
int NinadeRings::WinBet(BaseKnight * knight){return 0;};
void NinadeRings::LoseBet(BaseKnight * knight){return;};
void NinadeRings::MaxHPregen(BaseKnight * knight){return;};
void NinadeRings::OWfight(ArmyKnights * army, BaseKnight * knight){return;};
void NinadeRings::Hadesfight(ArmyKnights * army, BaseKnight * knight){return;};
/* omit function */


//DurianGarden
void DurianGarden::MaxHPregen(BaseKnight * knight){
    knight->setHP(knight->getMAXHP());
};

int DurianGarden::getID(){
    return this->eventid;
};

/* omit function */
int DurianGarden::getLEVELO(){return 0;};
int DurianGarden::getGil(){return 0;};
void DurianGarden::levelOCalc(int i){return;};
void DurianGarden::dealDam(BaseKnight * knight){return;};
void DurianGarden::dealPoisionDam(BaseKnight * knight){return;};
int DurianGarden::WinBet(BaseKnight * knight){return 0;};
void DurianGarden::LoseBet(BaseKnight * knight){return;};
void DurianGarden::HPSell(BaseKnight * knight){return;};
void DurianGarden::OWfight(ArmyKnights * army, BaseKnight * knight){return;};
void DurianGarden::Hadesfight(ArmyKnights * army, BaseKnight * knight){return;};
/* omit function */


//OmegaWeapon
void OmegaWeapon::OWfight(ArmyKnights * army, BaseKnight * knight){
    if(army->OW_met == false){
        if (knight->getKNIGHTTYPE()==DRAGON){
            army->OW_met = true;
            knight->setLEVEL(10);
            knight->setGIL(999);
        } else if(knight->getLEVEL() == 10 && knight->getHP() == knight->getMAXHP()){
            army->OW_met = true;
            knight->setGIL(999);
        } else {
            knight->setHP(0);
        }
    }
};

int OmegaWeapon::getID(){
    return this->eventid;
};

/* omit function */
int OmegaWeapon::getLEVELO(){return 0;};
int OmegaWeapon::getGil(){return 0;};
void OmegaWeapon::levelOCalc(int i){return;};
void OmegaWeapon::dealDam(BaseKnight * knight){return;};
void OmegaWeapon::dealPoisionDam(BaseKnight * knight){return;};
int OmegaWeapon::WinBet(BaseKnight * knight){return 0;};
void OmegaWeapon::LoseBet(BaseKnight * knight){return;};
void OmegaWeapon::HPSell(BaseKnight * knight){return;};
void OmegaWeapon::MaxHPregen(BaseKnight * knight){return;};
void OmegaWeapon::Hadesfight(ArmyKnights * army, BaseKnight * knight){return;};
/* omit function */


//Hades
void Hades::Hadesfight(ArmyKnights * army, BaseKnight * knight){
    if(army->Hades_met == false){
        if (knight->getLEVEL()==10){
            army->Hades_met = true;
            army->PaladinShield = true;
        } else if(knight->getLEVEL() >= 8 && knight->getKNIGHTTYPE() == PALADIN){
            army->Hades_met = true;
            army->PaladinShield = true;
        } else {
            knight->setHP(0);
        }
    }
};

int Hades::getID(){
    return this->eventid;
};

/* omit function */
int Hades::getLEVELO(){return 0;};
int Hades::getGil(){return 0;};
void Hades::levelOCalc(int i){return;};
void Hades::dealDam(BaseKnight * knight){return;};
void Hades::dealPoisionDam(BaseKnight * knight){return;};
int Hades::WinBet(BaseKnight * knight){return 0;};
void Hades::LoseBet(BaseKnight * knight){return;};
void Hades::HPSell(BaseKnight * knight){return;};
void Hades::MaxHPregen(BaseKnight * knight){return;};
void Hades::OWfight(ArmyKnights * army, BaseKnight * knight){return;};
/* omit function */

/* * * END implementation of class BaseOpponent * * */

/* * * BEGIN implementation of class BaseKnight * * */

//ID Setter & Getter
void BaseKnight::setID(int x) {
    this->id = x;
}
int BaseKnight::getID() {
    return this->id;
}

//MAXHP Setter & Getter
void BaseKnight::setMAXHP(int x) {
    this->maxhp = x;
}
int BaseKnight::getMAXHP() {
    return this->maxhp;
}

//HP Setter & Getter
void BaseKnight::setHP(int x) {
    this->hp = x;
    if(this->hp > this->maxhp) this->hp = this->maxhp;
}
int BaseKnight::getHP() {
    return this->hp;
}

//LEVEL Setter & Getter
void BaseKnight::setLEVEL(int x) {
    this->level = x;
    if(this->level > 10) this->level = 10;
}
int BaseKnight::getLEVEL() {
    return this->level;
}

//GIL Setter & Getter
void BaseKnight::setGIL(int x) {
    this->gil = x;
}
int BaseKnight::getGIL() {
    return this->gil;
}

//KNIGHTTYPE Setter & Getter
void BaseKnight::setKNIGHTTYPE(KnightType x) {
    this->knightType = x;
}
KnightType BaseKnight::getKNIGHTTYPE() {
    return this->knightType;
}

//BAG Setter & Getter
void BaseKnight::setBAG(BaseBag * x) {
    this->bag = x;
}
BaseBag * BaseKnight::getBAG() {
    return this->bag;
}

//create method
BaseKnight * BaseKnight::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
    if (isPrime(maxhp)){ //PALADIN
        //allocate memory
        PaladinKnight * Knight = new PaladinKnight;

        //Set stats
        Knight->setID(id);
        Knight->setMAXHP(maxhp);
        Knight->setHP(maxhp);
        Knight->setLEVEL(level);
        Knight->setGIL(gil);
        Knight->setKNIGHTTYPE(PALADIN);

        //Set bag
        PaladinBag * Palbag = new PaladinBag(Knight, phoenixdownI, antidote);
        Knight->setBAG(Palbag);

        //return pointer to new object
        return Knight;

    } else if (maxhp == 888){ //LANCELOT
        //allocate memory
        LancelotKnight * Knight = new LancelotKnight;

        //Set stats
        Knight->setID(id);
        Knight->setMAXHP(maxhp);
        Knight->setHP(maxhp);
        Knight->setLEVEL(level);
        Knight->setGIL(gil);
        Knight->setKNIGHTTYPE(LANCELOT);

        //Set bag
        LancelotBag * Lanbag = new LancelotBag(Knight, phoenixdownI, antidote);
        Knight->setBAG(Lanbag);

        //return pointer to new object
        return Knight;

    } else if (isPyt(maxhp)){ //DRAGON
        //allocate memory
        DragonKnight * Knight = new DragonKnight;

        //Set stats
        Knight->setID(id);
        Knight->setMAXHP(maxhp);
        Knight->setHP(maxhp);
        Knight->setLEVEL(level);
        Knight->setGIL(gil);
        Knight->setKNIGHTTYPE(DRAGON);

        //Set bag
        DragonBag * Drabag = new DragonBag(Knight, phoenixdownI, antidote);
        Knight->setBAG(Drabag);

        //return pointer to new object
        return Knight;

    }
    else { //NORMAL
        //allocate memory
        NormalKnight * Knight = new NormalKnight;

        //Set stats
        Knight->setID(id);
        Knight->setMAXHP(maxhp);
        Knight->setHP(maxhp);
        Knight->setLEVEL(level);
        Knight->setGIL(gil);
        Knight->setKNIGHTTYPE(NORMAL);

        //Set bag
        NormalBag * Norbag = new NormalBag(Knight, phoenixdownI, antidote);
        Knight->setBAG(Norbag);

        //return pointer to new object
        return Knight;
    }
};

string BaseKnight::toString() const {
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
    s += "[Knight:id:" + to_string(id) 
        + ",hp:" + to_string(hp) 
        + ",maxhp:" + to_string(maxhp)
        + ",level:" + to_string(level)
        + ",gil:" + to_string(gil)
        + "," + bag->toString()
        + ",knight_type:" + typeString[knightType]
        + "]";
    return s;
};

bool BaseKnight::revive(){
    if(this->getHP() < 0) this->getBAG()->UseFirstPhoenix();
    if(this->getHP() < 0){
        if(this->getGIL() >= 100){
            this->setHP(this->getMAXHP()/2);
            this->setGIL(this->getGIL()-100);
            return true;
        } else return false;
    } else return true;
};

bool PaladinKnight::revive(){
    if(this->getHP() < 0) this->getBAG()->UseFirstPhoenix();
    if(this->getHP() < 0){
        if(this->getGIL() >= 100){
            this->setHP(this->getMAXHP()/2);
            this->setGIL(this->getGIL()-100);
            return true;
        } else return false;
    } else return true;
};

bool DragonKnight::revive(){
    if(this->getHP() < 0) this->getBAG()->UseFirstPhoenix();
    if(this->getHP() < 0){
        if(this->getGIL() >= 100){
            this->setHP(this->getMAXHP()/2);
            this->setGIL(this->getGIL()-100);
            return true;
        } else return false;
    } else return true;
};

bool LancelotKnight::revive(){
    if(this->getHP() < 0) this->getBAG()->UseFirstPhoenix();
    if(this->getHP() < 0){
        if(this->getGIL() >= 100){
            this->setHP(this->getMAXHP()/2);
            this->setGIL(this->getGIL()-100);
            return true;
        } else return false;
    } else return true;
};

bool NormalKnight::revive(){
    if(this->getHP() < 0) this->getBAG()->UseFirstPhoenix();
    if(this->getHP() < 0){
        if(this->getGIL() >= 100){
            this->setHP(this->getMAXHP()/2);
            this->setGIL(this->getGIL()-100);
            return true;
        } else return false;
    } else return true;
};

/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class ArmyKnights * * */

ArmyKnights::ArmyKnights(const string & file_armyknights){
    ifstream ak(file_armyknights);
    
    //input number of knights
    ak >> NumOfKnights;

    Army = new BaseKnight*[NumOfKnights]; //array of knights

    //variables to hold the value of input
    int IDhold, MAXHPhold, LEVELhold, GILhold, ANTIDOTEhold, PHOENIXDOWNIhold;

    //Create Knight and add to array
    for(int i = 0; i < NumOfKnights; i++){
        // add data into hold variables
        ak >> MAXHPhold; ak >> LEVELhold; ak >> PHOENIXDOWNIhold; ak >> GILhold; ak >> ANTIDOTEhold;
        
        IDhold = i+1; //id of the knight

        //create knight
        Army[i] = Army[i]->create(IDhold, MAXHPhold, LEVELhold, GILhold, ANTIDOTEhold, PHOENIXDOWNIhold);
    }
};

ArmyKnights::~ArmyKnights(){
    for(int i = 0; i < NumOfKnights; i++){
        delete Army[i];
    }
    delete[] Army;
};

//recursive function to receive gils and handle excessed gils:
void ArmyKnights::receiveGil(int gil){ 
    int received = gil;
    for(int i = this->NumOfKnights - 1; i >= 0; i--){
        if(Army[i]->getGIL() + received > 999){
            Army[i]->setGIL(999);
            received = received + Army[i]->getGIL() - 999;
        } else{
            Army[i]->setGIL(Army[i]->getGIL() + received);
            break;
        }
    }
}; 

void ArmyKnights::receiveItem(BaseItem * item){
    int i = this->NumOfKnights - 1;
    while(i >= 0){
        if(Army[i]->getBAG()->insertFirst(item)){
            Army[i]->getBAG()->add_Item(item);
            break;
        }
        else i--;
    }
};

bool ArmyKnights::fight(BaseOpponent * opponent){

    //Madbear, Bandit, LordLupin, Elf, Troll, Tornberry, Queen Of Cards
    if (opponent->getID() <= 7){
        opponent->levelOCalc(current);

        //Madbear, Bandit, LordLupin, Elf, Troll
        if (opponent->getID() <= 5){
            if(this->lastKnight()->getKNIGHTTYPE() == LANCELOT || Army[NumOfKnights-1]->getKNIGHTTYPE() == PALADIN){
                this->receiveGil(opponent->getGil());
            }
            else {
                if(this->lastKnight()->getLEVEL() >= opponent->getLEVELO()){
                    this->receiveGil(opponent->getGil());
                }
                else{
                    opponent->dealDam(this->lastKnight());
                }
            }
        } else if(opponent->getID() == 6) {  //Tornberry
            if(this->lastKnight()->getLEVEL() >= opponent->getLEVELO()){
                this->lastKnight()->setLEVEL(this->lastKnight()->getLEVEL()+1);
            }
            else{
                if(this->lastKnight()->getKNIGHTTYPE()!=DRAGON && this->lastKnight()->getBAG()->AntiAmount > 0){
                    this->lastKnight()->getBAG()->UseAntidote();
                }
                else if(this->lastKnight()->getKNIGHTTYPE()!=DRAGON && this->lastKnight()->getBAG()->AntiAmount <= 0){
                    this->lastKnight()->setHP(this->lastKnight()->getHP() - 10);
                    for(int i = 0; i < 3; i++){
                        this->lastKnight()->getBAG()->deleteFirst();
                        if(this->lastKnight()->getBAG()->PhoenixAmount > 0) this->lastKnight()->getBAG()->PhoenixAmount--;
                    }
                }
            }
        } else {         //Queen Of Cards
            if(this->lastKnight()->getLEVEL() >= opponent->getLEVELO()){
                this->receiveGil(opponent->WinBet(this->lastKnight()));
            }
            else{
                opponent->LoseBet(this->lastKnight());
            }
        }
    }
    
    //Nina The Rings
    else if(opponent->getID() == 8){
        opponent->HPSell(this->lastKnight());
    }
    
    //Durian Garden
    else if(opponent->getID() == 9){
        opponent->MaxHPregen(this->lastKnight());
    }
    
    //Omega Weapon
    else if (opponent->getID() == 10){
        if(!this->OW_met) {
            opponent->OWfight(this, this->lastKnight());
        }
    }
    
    //Hades
    else if (opponent->getID() == 11){
        if(!this->Hades_met) {
            opponent->Hadesfight(this, this->lastKnight());
        }
    }

    if(this->lastKnight()->getHP()<=0){
        if(!this->lastKnight()->revive()){
            delete Army[NumOfKnights-1];
            NumOfKnights--;                            
        }
    }

    if (this->NumOfKnights <= 0) return false;
    else return true;
};

bool ArmyKnights::adventure (Events * event){
    bool combat;
    int initial_Amount;
    bool canContinue;
    bool UltiDefeated = false;
    for(int i = 0; i < event->count(); i++){
        combat = false;
        initial_Amount = this->lastKnight()->getBAG()->Amount;
        this->current = i;
        if(event->get(i) == 1){
            MadBear * opponent = new MadBear;
            combat = true;
            canContinue = this->fight(opponent);
            delete opponent;
        } else if(event->get(i) == 2){
            Bandit * opponent = new Bandit;
            combat = true;
            canContinue = this->fight(opponent);
            delete opponent;
        } else if(event->get(i) == 3){
            LordLupin * opponent = new LordLupin;
            combat = true;
            canContinue = this->fight(opponent);
            delete opponent;
        } else if(event->get(i) == 4){
            Elf * opponent = new Elf;
            combat = true;
            canContinue = this->fight(opponent);
            delete opponent;
        } else if(event->get(i) == 5){
            Troll * opponent = new Troll;
            combat = true;
            canContinue = this->fight(opponent);
            delete opponent;
        } else if(event->get(i) == 6){
            Tornberry * opponent = new Tornberry;
            combat = true;
            canContinue = this->fight(opponent);
            delete opponent;
        } else if(event->get(i) == 7){
            QueenOfCards * opponent = new QueenOfCards;
            combat = true;
            canContinue = this->fight(opponent);
            delete opponent;
        } else if(event->get(i) == 8){
            NinadeRings * opponent = new NinadeRings;
            canContinue = this->fight(opponent);
            delete opponent;
        } else if(event->get(i) == 9){
            DurianGarden * opponent = new DurianGarden;
            canContinue = this->fight(opponent);
            delete opponent;
        } else if(event->get(i) == 10){
            OmegaWeapon * opponent = new OmegaWeapon;
            combat = true;
            canContinue = this->fight(opponent);
            delete opponent;
        } else if(event->get(i) == 11){
            Hades * opponent = new Hades;
            combat = true;
            canContinue = this->fight(opponent);
            delete opponent;
        } else if(event->get(i) == 112){
            PhoenixDownII * item = new PhoenixDownII;
            this->receiveItem(item);
            canContinue = true;
        } else if(event->get(i) == 113){
            PhoenixDownIII * item = new PhoenixDownIII;
            this->receiveItem(item);
            canContinue = true;
        } else if(event->get(i) == 114){
            PhoenixDownIV * item = new PhoenixDownIV;
            this->receiveItem(item);
            canContinue = true;
        } else if(event->get(i) == 95){
            this->PaladinShield = true;
            canContinue = true;
        } else if(event->get(i) == 96){
            this->LancelotSpear = true;
            canContinue = true;
        } else if(event->get(i) == 97){
            this->GuinevereHair = true;
            canContinue = true;
        } else if(event->get(i) == 98){
            if(this->hasPaladinShield() && this->hasLancelotSpear() && this->hasGuinevereHair()) this->ExcaliburSword = true;
            canContinue = true;
        } else if(event->get(i) == 99){
            if(this->hasExcaliburSword()) UltiDefeated = true;
            else if(this->hasPaladinShield() && this->hasLancelotSpear() && this->hasGuinevereHair()){
                int UltiHP = 5000;
                int damage;
                for(int j = NumOfKnights - 1; j >= 0; j--){
                    if(Army[j]->getKNIGHTTYPE() == PALADIN || Army[j]->getKNIGHTTYPE() == DRAGON || Army[j]->getKNIGHTTYPE() == LANCELOT){
                        damage = Army[j]->getHP() * Army[j]->getLEVEL() * Army[j]->knightBaseDam;
                        UltiHP -= damage;
                        if(UltiHP > 0){
                            delete Army[j];
                            NumOfKnights--;
                        } else{
                            UltiDefeated = true;
                            break;
                        }
                    } else continue;
                }
                if(UltiHP > 0){
                    for(int j = 0; j < NumOfKnights; j++){
                        delete Army[j];
                    }
                    NumOfKnights = 0;
                    canContinue = false;
                }
            } else{
                for(int j = 0; j < NumOfKnights; j++){
                    delete Army[j];
                }
                NumOfKnights = 0;
                canContinue = false;
            }
        }

        if(combat && this->lastKnight()->getBAG()->Amount==initial_Amount) this->lastKnight()->getBAG()->UseFirstPhoenix();

        this->printInfo();

        if(!canContinue) return false;
        if(UltiDefeated) return true;
    }
    return false;
};

BaseKnight* ArmyKnights::lastKnight() const{
    if(NumOfKnights == 0) return nullptr;
    else return Army[NumOfKnights-1];
};

int ArmyKnights::count() const{
    return NumOfKnights;
};

bool ArmyKnights::hasPaladinShield() const {
    return PaladinShield;
};

bool ArmyKnights::hasLancelotSpear() const {
    return LancelotSpear;
};

bool ArmyKnights::hasGuinevereHair() const {
    return GuinevereHair;
};

bool ArmyKnights::hasExcaliburSword() const{
    return ExcaliburSword;
};

void ArmyKnights::printInfo() const {
    cout << "No. knights: " << this->count();
    if (this->count() > 0) {
        BaseKnight * lknight = lastKnight(); // last knight
        cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
        << ";LancelotSpear:" << this->hasLancelotSpear()
        << ";GuinevereHair:" << this->hasGuinevereHair()
        << ";ExcaliburSword:" << this->hasExcaliburSword()
        << endl
        << string(50, '-') << endl;
};

void ArmyKnights::printResult(bool win) const {
    cout << (win ? "WIN" : "LOSE") << endl;
};

/* * * END implementation of class ArmyKnights * * */

/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure() {
    armyKnights = nullptr;
    events = nullptr;
};

KnightAdventure::~KnightAdventure(){
    delete armyKnights;
    delete events;
}

void KnightAdventure::loadArmyKnights(const string & file_armyknights){
    armyKnights = new ArmyKnights(file_armyknights);
};

void KnightAdventure::loadEvents(const string & file_events){
    events = new Events(file_events);
}

void KnightAdventure::run(){
    this->armyKnights->printResult(armyKnights->adventure(this->events));
};

/* * * END implementation of class KnightAdventure * * */