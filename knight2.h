#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

bool isPrime(int n); //Prime check function

bool isPyt(int n); //Pythagoras set check function

enum ItemType {ANTIDOTE, PHOENIXDOWNI, PHOENIXDOWNII, PHOENIXDOWNIII, PHOENIXDOWNIV};

/* Foward Declaration */

class BaseItem;
class Antidote;
class PhoenixDownI;
class PhoenixDownII;
class PhoenixDownIII;
class PhoenixDownIV;

class BaseKnight;

class ArmyKnights;

class Events;

/* Foward Declaration*/

/* * * BEGIN declarations of Item * * */

class BaseItem {
public:
    ItemType type;
    virtual ItemType getType() = 0;
    virtual bool canUse ( BaseKnight * knight ) = 0;
    virtual void use ( BaseKnight * knight ) = 0;
};

class Antidote : public BaseItem {
    ItemType type = ANTIDOTE;
    ItemType getType();
    bool canUse ( BaseKnight * knight );
    void use ( BaseKnight * knight );
};

class PhoenixDownI : public BaseItem {
    ItemType type = PHOENIXDOWNI;
    ItemType getType();
    bool canUse ( BaseKnight * knight );
    void use ( BaseKnight * knight );
};

class PhoenixDownII : public BaseItem {
    ItemType type = PHOENIXDOWNII;
    ItemType getType();
    bool canUse ( BaseKnight * knight );
    void use ( BaseKnight * knight );
};

class PhoenixDownIII : public BaseItem {
    ItemType type = PHOENIXDOWNIII;
    ItemType getType();
    bool canUse ( BaseKnight * knight );
    void use ( BaseKnight * knight );
};

class PhoenixDownIV : public BaseItem {
    ItemType type = PHOENIXDOWNIV;
    ItemType getType();
    bool canUse ( BaseKnight * knight );
    void use ( BaseKnight * knight );
};

/* * * END declarations of Item * * */

//Node for Singly Linked List(SLL) Bag
class Slot {
public:
    
    BaseItem * item;
    Slot * next;

    Slot(BaseItem * item); //Node constructor
};


/* * * BEGIN declarations of Bag * * */

class BaseBag {
public:
    int Max;
    int Amount = 0;
    int AntiAmount = 0;
    int PhoenixAmount = 0;

    BaseKnight * knight;
    
    //Pointers to Items
    Antidote * AntidotePtr = new Antidote;
    PhoenixDownI * PhoenixDownIPtr = new PhoenixDownI;
    PhoenixDownII * PhoenixDownIIPtr = new PhoenixDownII;
    PhoenixDownIII * PhoenixDownIIIPtr = new PhoenixDownIII;
    PhoenixDownIV * PhoenixDownIVPtr = new PhoenixDownIV;

    //head of linked list
    Slot * head;

    virtual void add_Item(BaseItem * item) = 0;
    virtual void deleteFirst() = 0;

    virtual bool insertFirst(BaseItem * item) = 0;
    virtual BaseItem * get(ItemType itemType) = 0;
    virtual string toString() const = 0;

    virtual void UseAntidote() = 0;
    virtual void UseFirstPhoenix() = 0;
};

class PaladinBag : public BaseBag{
public:
    int Max = 2147846347;

    void add_Item(BaseItem * item);
    void deleteFirst();

    PaladinBag(BaseKnight * Knight, int phoenixdownI, int antidote);

    bool insertFirst(BaseItem * item);
    BaseItem * get(ItemType itemType);
    string toString() const;

    void UseAntidote();
    void UseFirstPhoenix();
};

class DragonBag : public BaseBag{
public:
    int Max = 14;

    void add_Item(BaseItem * item);
    void deleteFirst();

    DragonBag(BaseKnight * Knight, int phoenixdownI, int antidote);

    bool insertFirst(BaseItem * item);
    BaseItem * get(ItemType itemType);
    string toString() const;

    void UseAntidote();
    void UseFirstPhoenix();
};

class LancelotBag : public BaseBag{
public:
    int Max = 16;

    void add_Item(BaseItem * item);
    void deleteFirst(); 

    LancelotBag(BaseKnight * Knight, int phoenixdownI, int antidote);

    bool insertFirst(BaseItem * item);
    BaseItem * get(ItemType itemType);
    string toString() const;

    void UseAntidote();
    void UseFirstPhoenix();
};

class NormalBag : public BaseBag{
public:
    int Max = 19;

    void add_Item(BaseItem * item);
    void deleteFirst();

    NormalBag(BaseKnight * Knight, int phoenixdownI, int antidote);

    bool insertFirst(BaseItem * item);
    BaseItem * get(ItemType itemType);
    string toString() const;

    void UseAntidote();
    void UseFirstPhoenix();
};

/* * * END declarations of Bag * * */


/* * * BEGIN declarations of Opponent * * */

class BaseOpponent {
public:
    int eventid;
    int gil;    
    int levelO;
    int baseDam;
    virtual int getGil() = 0;
    virtual int getID() = 0;
    virtual int getLEVELO() = 0;
    virtual void levelOCalc(int i) = 0;
    virtual void dealDam(BaseKnight * knight) = 0;
    virtual void dealPoisionDam(BaseKnight * knight) = 0;
    virtual int WinBet(BaseKnight * knight) = 0;
    virtual void LoseBet(BaseKnight * knight) = 0;
    virtual void HPSell(BaseKnight * knight) = 0;
    virtual void MaxHPregen(BaseKnight * knight) = 0;
    virtual void OWfight(ArmyKnights * army, BaseKnight * knight) = 0;
    virtual void Hadesfight(ArmyKnights * army, BaseKnight * knight) = 0;
};

class MadBear : public BaseOpponent {
public:
    int eventid = 1;
    int gil = 100;
    int levelO;
    int baseDam = 10;
    void levelOCalc(int i);
    void dealDam(BaseKnight * knight);
    int getGil();
    int getID();
    int getLEVELO();
    //omit func
    void dealPoisionDam(BaseKnight * knight);
    int WinBet(BaseKnight * knight);
    void LoseBet(BaseKnight * knight);
    void HPSell(BaseKnight * knight);
    void MaxHPregen(BaseKnight * knight);
    void OWfight(ArmyKnights * army, BaseKnight * knight);
    void Hadesfight(ArmyKnights * army, BaseKnight * knight);
};

class Bandit : public BaseOpponent {
public:
    int eventid = 2;
    int gil = 150;
    int levelO;
    int baseDam = 15;
    void levelOCalc(int i);
    void dealDam(BaseKnight * knight);
    int getGil();
    int getID();
    int getLEVELO();
    //omit func
    void dealPoisionDam(BaseKnight * knight);
    int WinBet(BaseKnight * knight);
    void LoseBet(BaseKnight * knight);
    void HPSell(BaseKnight * knight);
    void MaxHPregen(BaseKnight * knight);
    void OWfight(ArmyKnights * army, BaseKnight * knight);
    void Hadesfight(ArmyKnights * army, BaseKnight * knight);
};

class LordLupin : public BaseOpponent {
public:
    int eventid = 3;
    int gil = 450;
    int levelO;
    int baseDam = 45;
    void levelOCalc(int i);
    void dealDam(BaseKnight * knight);
    int getGil();
    int getID();
    int getLEVELO();
    //omit func
    void dealPoisionDam(BaseKnight * knight);
    int WinBet(BaseKnight * knight);
    void LoseBet(BaseKnight * knight);
    void HPSell(BaseKnight * knight);
    void MaxHPregen(BaseKnight * knight);
    void OWfight(ArmyKnights * army, BaseKnight * knight);
    void Hadesfight(ArmyKnights * army, BaseKnight * knight);
};

class Elf : public BaseOpponent {
public:
    int eventid = 4;
    int gil = 750;
    int levelO;
    int baseDam = 75;
    void levelOCalc(int i);
    void dealDam(BaseKnight * knight);
    int getGil();
    int getID();
    int getLEVELO();
    //omit func
    void dealPoisionDam(BaseKnight * knight);
    int WinBet(BaseKnight * knight);
    void LoseBet(BaseKnight * knight);
    void HPSell(BaseKnight * knight);
    void MaxHPregen(BaseKnight * knight);
    void OWfight(ArmyKnights * army, BaseKnight * knight);
    void Hadesfight(ArmyKnights * army, BaseKnight * knight);
};

class Troll : public BaseOpponent {
public:
    int eventid = 5;
    int gil = 800;
    int levelO;
    int baseDam = 95;
    void levelOCalc(int i);
    void dealDam(BaseKnight * knight);
    int getGil();
    int getID();
    int getLEVELO();
    //omit func
    void dealPoisionDam(BaseKnight * knight);
    int WinBet(BaseKnight * knight);
    void LoseBet(BaseKnight * knight);
    void HPSell(BaseKnight * knight);
    void MaxHPregen(BaseKnight * knight);
    void OWfight(ArmyKnights * army, BaseKnight * knight);
    void Hadesfight(ArmyKnights * army, BaseKnight * knight);
};

class Tornberry : public BaseOpponent {
public:
    int eventid = 6;
    int levelO;
    void levelOCalc(int i);
    void dealPoisionDam(BaseKnight * knight);
    int getID();
    int getLEVELO();
    //omit func
    int getGil();
    void dealDam(BaseKnight * knight);
    int WinBet(BaseKnight * knight);
    void LoseBet(BaseKnight * knight);
    void HPSell(BaseKnight * knight);
    void MaxHPregen(BaseKnight * knight);
    void OWfight(ArmyKnights * army, BaseKnight * knight);
    void Hadesfight(ArmyKnights * army, BaseKnight * knight);
};

class QueenOfCards : public BaseOpponent {
public:
    int eventid = 7;
    int levelO;
    int WinBet(BaseKnight * knight);
    void LoseBet(BaseKnight * knight);
    void levelOCalc(int i);
    int getID();
    int getLEVELO();
    //omit func
    int getGil();
    void dealDam(BaseKnight * knight);
    void dealPoisionDam(BaseKnight * knight);
    void HPSell(BaseKnight * knight);
    void MaxHPregen(BaseKnight * knight);
    void OWfight(ArmyKnights * army, BaseKnight * knight);
    void Hadesfight(ArmyKnights * army, BaseKnight * knight);
};

class NinadeRings : public BaseOpponent {
public:
    int eventid = 8;
    void HPSell(BaseKnight * knight);
    int getID();
    //omit func
    int getLEVELO();
    int getGil();
    void levelOCalc(int i);
    void dealDam(BaseKnight * knight);
    void dealPoisionDam(BaseKnight * knight);
    int WinBet(BaseKnight * knight);
    void LoseBet(BaseKnight * knight);
    void MaxHPregen(BaseKnight * knight);
    void OWfight(ArmyKnights * army, BaseKnight * knight);
    void Hadesfight(ArmyKnights * army, BaseKnight * knight);
};

class DurianGarden : public BaseOpponent {
public:
    int eventid = 9;
    void MaxHPregen(BaseKnight * knight);
    int getID();
    //omit func
    int getLEVELO();
    int getGil();
    void levelOCalc(int i);
    void dealDam(BaseKnight * knight);
    void dealPoisionDam(BaseKnight * knight);
    int WinBet(BaseKnight * knight);
    void LoseBet(BaseKnight * knight);
    void HPSell(BaseKnight * knight);
    void OWfight(ArmyKnights * army, BaseKnight * knight);
    void Hadesfight(ArmyKnights * army, BaseKnight * knight);
};

class OmegaWeapon : public BaseOpponent {
public:
    int eventid = 10;
    void OWfight(ArmyKnights * army, BaseKnight * knight);
    int getID();
    //omit func
    int getLEVELO();
    int getGil();
    void levelOCalc(int i);
    void dealDam(BaseKnight * knight);
    void dealPoisionDam(BaseKnight * knight);
    int WinBet(BaseKnight * knight);
    void LoseBet(BaseKnight * knight);
    void MaxHPregen(BaseKnight * knight);
    void HPSell(BaseKnight * knight);
    void Hadesfight(ArmyKnights * army, BaseKnight * knight);
};

class Hades : public BaseOpponent {
public:
    int eventid = 11;
    bool Hadeswon = false;
    void Hadesfight(ArmyKnights * army, BaseKnight * knight);
    int getID();
    //omit func
    int getLEVELO();
    int getGil();
    void levelOCalc(int i);
    void dealDam(BaseKnight * knight);
    void dealPoisionDam(BaseKnight * knight);
    int WinBet(BaseKnight * knight);
    void LoseBet(BaseKnight * knight);
    void MaxHPregen(BaseKnight * knight);
    void HPSell(BaseKnight * knight);
    void OWfight(ArmyKnights * army, BaseKnight * knight);
};

/* * * END declarations of Opponent * * */


/* * * BEGIN declarations of Knight * * */

enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };
class BaseKnight {
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    BaseBag * bag;
    KnightType knightType;

public:
    int knightBaseDam;
    bool poisioned = false;

    //ID Setter & Getter
    void setID(int x);
    int getID();

    //MAXHP Setter & Getter
    void setMAXHP(int x);
    int getMAXHP();

    //HP Setter & Getter
    void setHP(int x);
    int getHP();

    //LEVEL Setter & Getter
    void setLEVEL(int x);
    int getLEVEL();

    //GIL Setter & Getter
    void setGIL(int x);
    int getGIL();

    //KNIGHTTYPE Setter & Getter
    void setKNIGHTTYPE(KnightType x);
    KnightType getKNIGHTTYPE();

    //BAG Setter & Getter
    void setBAG(BaseBag * x);
    BaseBag * getBAG();

    static BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;

    virtual bool revive();
};

class PaladinKnight : public BaseKnight {
public:
    int knightBaseDam = 0.06;
    bool revive();
};

class DragonKnight : public BaseKnight {
public:
    int knightBaseDam = 0.075;
    bool revive();
};

class LancelotKnight : public BaseKnight {
public:
    int knightBaseDam = 0.05;
    bool revive();
};

class NormalKnight : public BaseKnight {
public:
    int knightBaseDam = 0;
    bool revive();
};

/* * * END declarations of Knight * * */


/* * * BEGIN declarations of Army * * */

class ArmyKnights {
public:
    int NumOfKnights; //number of knights
    BaseKnight **Army; //array of pointer to army knights
    int current = 0; //the current event's order

    bool PaladinShield = false;
    bool LancelotSpear = false;
    bool GuinevereHair = false;
    bool ExcaliburSword = false;

    bool OW_met = false; //check if the army has met Omega Weapon yet
    bool Hades_met = false; //check if the army has met Hades yet

    ArmyKnights (const string & file_armyknights);
    ~ArmyKnights();

    void receiveGil(int received); //recursive function to receive gils and handle excessed
    void receiveItem(BaseItem * item); //function to add items

    bool fight(BaseOpponent * opponent);
    bool adventure (Events * events);
    int count() const;
    BaseKnight * lastKnight() const;

    bool hasPaladinShield() const;
    bool hasLancelotSpear() const;
    bool hasGuinevereHair() const;
    bool hasExcaliburSword() const;

    void printInfo() const;
    void printResult(bool win) const;
};

/* * * END declarations of Army * * */


/* * * BEGIN declarations of Event * * */

class Events {
public:
    int *EventList;
    int NumOfEvents;
    int CurrentEvent;
    Events(const string file_events);
    ~Events();
    int count() const;
    int get(int i) const;
};

/* * * END declarations of Event * * */


/* * * BEGIN declarations of Adventure * * */

class KnightAdventure {
private:
    ArmyKnights * armyKnights;
    Events * events;

public:
    KnightAdventure();
    ~KnightAdventure(); // TODO:

    void loadArmyKnights(const string & file_armyknights);
    void loadEvents(const string & file_events);
    void run();
};

/* * * END declarations of Adventure * * */

#endif // __KNIGHT2_H__