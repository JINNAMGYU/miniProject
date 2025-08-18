#include <iostream>
#include <string>
using namespace std;

class Player{
protected:
	string name;
	int hp,maxHp;
	int attack,defense;
	
public:
	Player(string name,int hp,int attack, int defense):name(name),hp(hp),maxHp(hp),attack(attack),defense(defense){}
	bool isDead(){return hp<=0;}
	int getAttack(){return attack;}
	int getDefense(){return defense;}
	void showStatus(){
		cout<<"===============================================\n";
		cout<<"     NAME    : "<<name<<'\n';
		cout<<"     HP      : "<<hp<<" / "<<maxHp<<'\n';
		cout<<"     ATTACK  : "<<attack<<'\n';
		cout<<"     Defense : "<<defense<<'\n';
		cout<<"===============================================\n";
	}
};

int main() {
    string t;
	cout<<"welcome! Enter your name!\n"<<">> ";
	getline(cin,t);
	
	Player player(t,10,5,5);
	player.showStatus();
	
    return 0;
}
