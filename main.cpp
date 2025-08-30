#include <iostream>
#include <string>
using namespace std;

static int resurrectionTime=50;

class Character{
protected:
	string name;
	int hp,maxHp;
	int attack,defense;
	int gold;
	int level;
public:
	Character(string name,int hp,int attack, int defense,int gold,int level):name(name),hp(hp),maxHp(hp),attack(attack),defense(defense), gold(gold),level(level){}
	bool isDead(){return hp<=0;}
	string getName(){return name;}
	int getHp(){return hp;}
	int getMaxHp(){return maxHp;}
	int getAttack(){return attack;}
	int getDefense(){return defense;}
	int getGold(){return gold;}
	int getLevel(){return level;}
	void takeDamage(int dmg){
		int damage=dmg-defense;
		if(damage<0) damage=0;
		
		hp-=damage;
		cout<<"-> "<<name<<" taked "<<damage<<" damage!!\n";
	}
	void attackTarget(Character& target){
		cout<<name<<" attack "<<target.name<<"...\n";
		int atk = attack + (attack * (rand() % 41) / 100);
		target.takeDamage(atk);
	}
	
	virtual void showStatus()=0;
};

const float STAT_GROWTH_RATE=0.2f;
const float EXP_GROWTH_RATE=0.1f;
const float UPGRADE_GOLD_RATE=5;
const float UPGRADE_STAT_RATE=5;

class Player : public Character {
protected:
	int weaponLevel=1;
	int armorLevel=1;
	int exp=0;
	int maxExp=100;
	
public:
	Player(string name,int hp,int attack, int defense,int gold,int level):Character(name, hp, attack, defense, gold, level){}
	int getWeapon(){return weaponLevel;}
	int getArmor(){return armorLevel;}
	int getExpPersent(){return exp*100/maxExp;}
	void adjustGold(int g){gold+=g;}
	void recoverHp(){
		hp+=maxHp/2;
		if(hp>=maxHp)
			hp=maxHp;
	}
	void levelUp(int e){
		exp+=e;
		while (exp >= maxExp) {
			cout<<"\n ### LEVEL UP "<<level<<"->"<<level+1<<" ###\n";
			level++;
			exp -= maxExp;
			maxExp += maxExp*EXP_GROWTH_RATE;
			hp += hp * STAT_GROWTH_RATE;
			maxHp += maxHp *STAT_GROWTH_RATE;
			attack += attack * STAT_GROWTH_RATE;
			defense += defense * STAT_GROWTH_RATE;
		}
	}
	void upgradeWeapon(){
		int r=rand()%100+1;
		if(r>weaponLevel*UPGRADE_GOLD_RATE){
			weaponLevel++;
			attack+=UPGRADE_STAT_RATE;
			cout<<" Weapon upgrade success!!!\n";
		}
		else{
			cout<<" Weapon upgrade fail...\n";
		}
	}
	void upgradeArmor(){
		int r=rand()%100+1;
		if(r>armorLevel*UPGRADE_GOLD_RATE){
			armorLevel++;
			defense+=UPGRADE_STAT_RATE;
			cout<<" Armor upgrade success!!!\n";
		}
		else{
			cout<<" Armor upgrade fail...\n";
		}
	}
	virtual void showStatus(){
		cout<<"====================STATUS=====================\n";
		cout<<"          NAME    : "<<name<<'\n';
		cout<<"          HP      : "<<hp<<" / "<<maxHp<<'\n';
		cout<<"          ATTACK  : "<<attack<<'\n';
		cout<<"          DEFENSE : "<<defense<<'\n';
		cout<<"          GOLD    : "<<gold<<"G\n";
		cout<<"          LEVEL   : "<<level<<"Lv ("<<exp*100/maxExp<<"%)\n";
		cout<<"===============================================\n";
	}
};

void showOption(){
	cout<<"(1) BlackSmith\n";
	cout<<"(2) Sleep\n";
	cout<<"(3) Hunting\n";
}


const int UPGRADE_WEAPON_COST_RATE=7;
const int UPGRADE_ARMOR_COST_RATE=7;
void showBlackSmith(Player& p){
	while(true){
		cout<<"\n++++++++++++++++++BLACKSMITH+++++++++++++++++++\n";
		cout<<"(1) Upgrade Weapon "<<p.getWeapon()<<" -> "<<p.getWeapon()+1<<" ("<<5*p.getWeapon()<<"G)\n";
		cout<<"(2) Upgrade Armor  "<<p.getArmor()<<" -> "<<p.getArmor()+1<<" ("<<5*p.getArmor()<<"G)\n";
		cout<<"(3) Back to Main\n";
		cout<<"\nGOLD : "<<p.getGold()<<"G\n";
	
		int opt;
		cout<<">> ";
		cin>>opt;
		
		
		if(opt==1){
			if(p.getGold()>=UPGRADE_WEAPON_COST_RATE*p.getWeapon()){
				p.adjustGold((-1)*UPGRADE_WEAPON_COST_RATE*p.getWeapon());
				p.upgradeWeapon();
			}
			else
				cout<<"\nyou dont have enough gold!\n\n";
		}
		else if(opt==2){
			if(p.getGold()>=UPGRADE_ARMOR_COST_RATE*p.getArmor()){
				p.adjustGold((-1)*UPGRADE_ARMOR_COST_RATE*p.getArmor());
				p.upgradeArmor();
			}
			else
				cout<<"\nyou dont have enough gold!\n\n";
		}
		else
			break;
	}
	cout<<"\n++++++++++++++++++BLACKSMITH+++++++++++++++++++\n\n";
}

void doSleep(Player& p){
	p.recoverHp();
	resurrectionTime--;
	cout<<p.getName()<<" recovers Hp! \n\n";
}

class Monster : public Character{
public:
	Monster(string name,int hp,int attack, int defense,int gold,int level):Character(name, hp, attack, defense, gold, level){}
	virtual void showStatus(){
		cout<<"\n      "<<name<<" (Lv"<<level<<")\n";
		cout<<"      "<<hp<<'/'<<maxHp<<'\n';
	}
};

struct MonsterData{
	string name;
	int hp,attack,defense,gold,level;
};
const MonsterData region1Monsters[]{
	{"Slime", 7, 6, 1,1,1},
	{"Mushroom", 7, 7, 1,5,2},
	{"Tree", 10,9,2,10,3},
	{"Monkey", 15,9,2,20,4},
	{"Tiger", 20,10,3,30,5}
};
const MonsterData region2Monsters[]{
	{"Bat", 12, 9, 2,25,5},
	{"Rat", 15, 9, 2,25,5},
	{"Ghost", 20,10,5,35,6},
	{"Quty Bear", 30,15,7,40,7},
	{"Golem", 50,15,10,45,8}
};
const MonsterData region3Monsters[]{
	{"Goat", 25, 15, 8,40,8},
	{"Eagle", 25, 17, 8,45,9},
	{"Mountain Spirit", 30,18,10,50,10},
	{"Hog", 40,20,15,55,11},
	{"Gorila", 50,25,15,60,12}
};
const MonsterData region4Monsters[]{
	{"Ghost Knight", 60, 20, 25,60,12},
	{"Moving Castle", 100, 30, 30,80,13},
	{"Dark Ghost", 80,35,25,80,14},
	{"Dark Golem", 150,40,40,90,15},
	{"Ghost King", 90,50,35,100,16}
};
const MonsterData region5Monsters[]{
	{"Imp", 110, 40, 35,90,16},
	{"Demon", 130, 50, 50,100,17},
	{"Magma Golem", 250,65,100,110,18},
	{"Demon of Fire", 150,70,60,120,19},
	{"Dragon", 300,100,88,150,20}
};
const MonsterData* allMonsers[]={region1Monsters,region2Monsters,region3Monsters,region4Monsters,region4Monsters,region5Monsters};

const int GET_EXP_RATE=20;
void battle(Player& p, Monster& m){
	cout<<"!!!!! "<<m.getName()<< " appear !!!!!\n";
	
	
	while(!p.isDead()&&!m.isDead()){
		m.showStatus();
		cout<<endl;
		cout<<"      "<<p.getName()<<" (Lv"<<p.getLevel()<<")\n";
		cout<<"      "<<p.getHp()<<"/"<<p.getMaxHp()<<"\n\n";
		cout<<"   (1) Attack\n";
		cout<<"   (2) Run\n";
		int choice;
		cout<<"  >> ";
		cin>>choice;
		
		if(choice==1){
			p.attackTarget(m);
			if(!m.isDead())
				m.attackTarget(p);
		}
		else if(choice==2){
			cout<<p.getName()<<" RunAway!\n";
			break;
		}
	}
	
	if (p.isDead()) {
        cout << "You were defeated...\n";
    } else if (m.isDead()) {
        cout << "You defeated " << m.getName() << "!\n";
        p.levelUp(m.getLevel()*GET_EXP_RATE);
		p.adjustGold(m.getGold());
    }
}


Monster spawner(int region){
	
	int index = rand() % 5;
	const MonsterData* regionMonsters=allMonsers[region-1];
	const MonsterData& data = regionMonsters[index];
}

void hunting(Player& p){
	cout<<"\n*****************HUNTING SPOT*******************\n\n";
	cout<<"       (1) Green Forest        (1Lv ~ 5Lv)\n";
	cout<<"       (2) Dark Cave           (4Lv ~ 8Lv)\n";
	cout<<"       (3) High Mountain       (8Lv ~ 12Lv)\n";
	cout<<"       (4) Fallen Kindom       (12Lv ~ 16Lv)\n";
	cout<<"       (5) Castle of DemonKing (16Lv ~ 20Lv)\n";
	cout<<"\nHP: "<<p.getHp()<<"/"<<p.getMaxHp()<<"   Lv"<<p.getLevel()<<" ("<<p.getExpPersent()<<"%)\n";
	cout<<">>";
	int choice;
	cin>>choice;
	
	switch(choice) {
    case 1: case 2: case 3: case 4: case 5:
        resurrectionTime--;
        Monster m = spawner(choice);
        battle(p, m);
        break;
	}
}

const int DEMONKING_HP=1000;
const int DEMONKING_ATTACK=300;
const int DEMONKING_DEFENSE=300;
const int DEMONKING_LEVEL=999;
							 
void finalBattle(Player& p){
	Monster demonKing("DemonKing",DEMONKING_HP,DEMONKING_ATTACK,DEMONKING_DEFENSE,0,DEMONKING_LEVEL);
	battle(p,demonKing);
}
							 
const int PLAYER_BEGINING_HP=10;
const int PLAYER_BEGINING_ATTACK=5;
const int PLAYER_BEGINING_DEFENSE=5;
const int PLAYER_BEGINING_GOLD=10;
const int PLAYER_BEGINING_LEVEL=1;

int main() {
	
	while(true){
    	string t;
		cout<<"welcome! Enter your name!\n"<<">> ";
		getline(cin,t);
		Player player(t,PLAYER_BEGINING_HP,PLAYER_BEGINING_ATTACK,PLAYER_BEGINING_DEFENSE,PLAYER_BEGINING_GOLD,PLAYER_BEGINING_LEVEL);
		resurrectionTime=50;
		
		int tmp;
		while(true){
			if(player.isDead()){
				cout<<player.getName()<<" is Dead...\n\n";
				break;
			}
			if(resurrectionTime==0){
				finalBattle(player);
				if(player.isDead()){
					cout<<player.getName()<<" is Dead...\n\n";
					break;
				}
				else{
					cout<<player.getName()<<" save the world!!!\n";
					return 0;
				}
			}
			
			cout<<"\n| MAIN |          Ressurect of DemonKing...D-"<<resurrectionTime<<"\n";
			player.showStatus();
			showOption();
			cout<<">> ";
			cin>>tmp;
			cin.ignore();
	
			if(tmp==1)
				showBlackSmith(player);
			if(tmp==2)
				doSleep(player);
			if(tmp==3)
				hunting(player);
		}
	}
    return 0;
}
