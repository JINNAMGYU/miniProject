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
		cout<<name<<" taked "<<damage<<" damage!!\n";
	}
	void attackTarget(Character& target){
		cout<<name<<" attack "<<target.name<<"...\n";
		target.takeDamage(attack);
	}
	
	virtual void showStatus()=0;
};

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
		hp+=hp/2;
		if(hp>=maxHp)
			hp=maxHp;
	}
	void levelUp(int e){
		exp+=e;
		if(exp>=maxExp){
			cout<<" ### LEVEL UP "<<level<<"->"<<level+1<<" ###\n";
			level++;
			exp-=maxExp;
			maxExp+=maxExp/10;
			hp+=hp/10;
			maxHp+=maxHp/15;
			attack+=attack/15;
			defense+=defense/15;
		}
	}
	void upgradeWeapon(){weaponLevel++; attack+=5;}
	void upgradeArmor(){armorLevel++; defense+=5;}
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
			if(p.getGold()>=5*p.getWeapon()){
				p.adjustGold((-1)*5*p.getWeapon());
				p.upgradeWeapon();
			}
			else
				cout<<"\nyou dont have enough gold!\n\n";
		}
		else if(opt==2){
			if(p.getGold()>=5*p.getArmor()){
				p.adjustGold((-1)*5*p.getArmor());
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

void battle(Player& p, Monster& m){
	cout<<"!!!!! "<<m.getName()<< " appear !!!!!\n";
	
	while(!p.isDead()&&!m.isDead()){
		m.showStatus();
		cout<<endl;
	
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
        p.levelUp(m.getLevel()*10);
		p.adjustGold(m.getGold());
    }
}

Monster spawner(int m){
	string name[]={"Slime", "Treeknight", "Mushroom"};
	int index = rand() % 3;

    if (index == 0)
        return Monster(name[index], 5, 1, 1,1,1);
    else if (index == 1)
        return Monster(name[index], 7, 2, 1,5,2);
    else
        return Monster(name[index], 10,3,2,10,3);
}

void greenForest(Player& p){
	resurrectionTime--;
	Monster m=spawner(1);
	battle(p,m);
}

void hunting(Player& p){
	cout<<"\n*****************HUNTING SPOT*******************\n\n";
	cout<<"       (1) Green Forest        (1Lv ~ 5Lv)\n";
	cout<<"       (2) Dark Cave           (4Lv ~ 9Lv)\n";
	cout<<"       (3) High Mountain       (8Lv ~ 13Lv)\n";
	cout<<"       (4) Fallen Kindom       (12Lv ~ 17Lv)\n";
	cout<<"       (5) Castle of DemonKing (16Lv ~ 20Lv)\n";
	cout<<"\nHP: "<<p.getHp()<<"/"<<p.getMaxHp()<<"   Lv"<<p.getLevel()<<" ("<<p.getExpPersent()<<"%)\n";
	cout<<">>";
	int choice;
	cin>>choice;
	
	if(choice==1)
		greenForest(p);
}

int main() {
    string t;
	cout<<"welcome! Enter your name!\n"<<">> ";
	getline(cin,t);
	Player player(t,10,5,5,100,1);
	
	int tmp;
	while(true){
		cout<<"\n| MAIN |          Ressurect of DemonKing...D-"<<resurrectionTime<<"\n";
		player.showStatus();
		showOption();
		cout<<">> ";
		cin>>tmp;
	
		if(tmp==1)
			showBlackSmith(player);
		if(tmp==2)
			doSleep(player);
		if(tmp==3)
			hunting(player);
	}
	
    return 0;
}
