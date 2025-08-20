#include <iostream>
#include <string>
using namespace std;

class Player{
protected:
	string name;
	int hp,maxHp;
	int attack,defense;
	int gold;
	int weaponLevel=1;
	int armorLevel=1;
	
public:
	Player(string name,int hp,int attack, int defense,int gold):name(name),hp(hp),maxHp(hp),attack(attack),defense(defense), gold(gold){}
	bool isDead(){return hp<=0;}
	int getAttack(){return attack;}
	int getDefense(){return defense;}
	int getGold(){return gold;}
	int getWeapon(){return weaponLevel;}
	int getArmor(){return armorLevel;}
	void adjustGold(int g){gold+=g;}
	void upgradeWeapon(){weaponLevel++; attack+=5;}
	void upgradeArmor(){armorLevel++; defense+=5;}
	void showStatus(){
		cout<<"====================STATUS=====================\n";
		cout<<"          NAME    : "<<name<<'\n';
		cout<<"          HP      : "<<hp<<" / "<<maxHp<<'\n';
		cout<<"          ATTACK  : "<<attack<<'\n';
		cout<<"          DEFENSE : "<<defense<<'\n';
		cout<<"          GOLD    : "<<gold<<"G\n";
		cout<<"===============================================\n";
	}
};

void showOption(){
	cout<<"(1) BlackSmith\n";
	cout<<"(2) Sleep\n";
	cout<<"(3) Adventure\n";
}

void showBlackSmith(Player& p){
	while(true){
		cout<<"\n++++++++++++++++++BLACKSMITH+++++++++++++++++++\n";
		cout<<"(1) Upgrade Weapon "<<p.getWeapon()<<" -> "<<p.getWeapon()+1<<" ("<<5*p.getWeapon()<<"G)\n";
		cout<<"(2) Upgrade Armor  "<<p.getArmor()<<" -> "<<p.getArmor()+1<<" ("<<5*p.getArmor()<<"G)\n";
		cout<<"(3) Back to Main\n";
		cout<<"\n "<<p.getGold()<<"G\n";
	
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

int main() {
    string t;
	cout<<"welcome! Enter your name!\n"<<">> ";
	getline(cin,t);
	Player player(t,10,5,5,100);
	
	while(true){
		player.showStatus();
		showOption();
		int tmp;
		cout<<">> ";
		cin>>tmp;
	
		if(tmp==1)
			showBlackSmith(player);
	}
	
    return 0;
}
