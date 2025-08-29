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
			maxExp += maxExp / 10;
			hp += hp / 5;
			maxHp += maxHp / 5;
			attack += attack / 5;
			defense += defense / 5;
		}
	}
	void upgradeWeapon(){
		int r=rand()%100+1;
		if(r>weaponLevel*5){
			weaponLevel++;
			attack+=5;
			cout<<" Weapon upgrade success!!!\n";
		}
		else{
			cout<<" Weapon upgrade fail...\n";
		}
	}
	void upgradeArmor(){
		int r=rand()%100+1;
		if(r>armorLevel*5){
			armorLevel++;
			defense+=5;
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
        p.levelUp(m.getLevel()*20);
		p.adjustGold(m.getGold());
    }
}

Monster spawner(int region){
	
	int index = rand() % 5;
	
	if(region==1){
		if (index == 0)
			return Monster("Slime", 7, 6, 1,1,1);
		else if (index == 1)
			return Monster("Mushroom", 7, 7, 1,5,2);
		else if (index == 2)
			return Monster("Tree", 10,9,2,10,3);
		else if (index == 3)
			return Monster("Monkey", 15,9,2,20,4);
		else
			return Monster("Tiger", 20,10,3,30,5);
	}
	else if(region==2){
		if (index == 0)
			return Monster("Bat", 12, 9, 2,25,5);
		else if (index == 1)
			return Monster("Rat", 15, 9, 2,25,5);
		else if (index == 2)
			return Monster("Ghost", 20,10,5,35,6);
		else if (index == 3)
			return Monster("Quty Bear", 30,15,7,40,7);
		else
			return Monster("Golem", 50,15,10,45,8);
	}
	else if(region==3){
		if (index == 0)
			return Monster("Goat", 25, 15, 8,40,8);
		else if (index == 1)
			return Monster("Eagle", 25, 17, 8,45,9);
		else if (index == 2)
			return Monster("Mountain Spirit", 30,18,10,50,10);
		else if (index == 3)
			return Monster("Hog", 40,20,15,55,11);
		else
			return Monster("Gorila", 50,25,15,60,12);
	}
	else if(region==4){
		if (index == 0)
			return Monster("Ghost Knight", 60, 20, 25,60,12);
		else if (index == 1)
			return Monster("Moving Castle", 100, 30, 30,80,13);
		else if (index == 2)
			return Monster("Dark Ghost", 80,35,25,80,14);
		else if (index == 3)
			return Monster("Dark Golem", 150,40,40,90,15);
		else
			return Monster("Ghost King", 90,50,35,100,16);
	}
	else{
		if (index == 0)
			return Monster("Imp", 110, 40, 35,90,16);
		else if (index == 1)
			return Monster("Demon", 130, 50, 50,100,17);
		else if (index == 2)
			return Monster("Magma Golem", 250,65,100,110,18);
		else if (index == 3)
			return Monster("Demon of Fire", 150,70,60,120,19);
		else
			return Monster("Dragon", 300,100,88,150,20);
	}
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

void finalBattle(Player& p){
	Monster demonKing("DemonKing",1000,100,100,0,999);
	battle(p,demonKing);
}

int main() {
	
	while(true){
    	string t;
		cout<<"welcome! Enter your name!\n"<<">> ";
		getline(cin,t);
		Player player(t,10,5,5,10,1);
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
