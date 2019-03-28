#include "pch.h"
#include <iostream>
#include <string>
#include <iomanip>
#include<vector>
#include<algorithm>
using namespace std;

int Time = 0;
class Warrior;
class City;
class Headquarter {
public:
	int hp;
	string color;
	Warrior* warriors;
	int position;
	int* warriorhp;
	int* warriorpower;
	int* warriorseq;
	int* warriornum;
	bool isstop;
	int totalnum;
	City* ct;
	bool success;
	Headquarter(int , int , int* , int* , int*,int,City*);
	~Headquarter();
	void Produce();
	void show();
};
class Weapon;
int K;
class Warrior {
public:
	int hp,power;
	int index;
	int loyalty;
	string name;
	vector<Weapon*> wp;
	Headquarter* hq;
	int position;
	City* ct;
	Warrior(int a,int b, const char* c, Headquarter* d) {
		hp = a;
		power = b;
		name = c;
		hq = d;
		index = d->totalnum;
		position = 0;
		loyalty = d->hp - hp;
	}
	Warrior() {
		hp = 0;
		power = 0;
		name = "";
		hq = NULL;
		position = 0;
	}
	virtual ~Warrior();
	virtual void show();
	virtual void move();
	virtual void run();
	virtual void attack();
	virtual void rob(Warrior*);
	virtual void victory(Warrior*);
};
class Weapon {
public:
	string name;
	int index;
	int hp,power;
	Warrior* wr;
	Weapon() { index = -1; };
	virtual void attack(Warrior* s) {};
	virtual void setnew(Warrior* s) { wr = s; };
	virtual ~Weapon() {};
};
class Sword :public Weapon {
public:
	Sword(Warrior*s) {
		index = 0;
		hp = -1;
		wr = s;
		name = "sword";
	}
	void attack(Warrior*s) {
		int power = wr->power / 5;
		s->hp = s->hp - power;
	}
};
class Bomb :public Weapon {
public:
	Bomb(Warrior* s) {
		index = 1;
		hp = 1;
		wr = s;
		name = "bomb";
	}
	void attack(Warrior* s) {
		int power = wr->power * 2 / 5;
		s->hp = s->hp - power;
		if (wr->name != "ninja") { wr->hp = wr->hp - power / 2; }
		hp =hp- 1; 
	}
};
class Arrow :public Weapon {
public:Arrow(Warrior* s) {
		index = 2;
		hp = 2;
		wr = s;
		name = "arrow";
	}
	void attack(Warrior*s) {
		int power = wr->power * 3 / 10;
		s->hp = s->hp - power;
		hp = hp - 1;
	}
};
class Dragon :public Warrior {
public:
	float morale;
	static int total;
	Dragon(int a,int b, Headquarter* d) :Warrior(a, b,"dragon", d), morale(float(hq->hp - hp) / float(hp)) {
		if (index % 3 == 0) { Weapon* p = new Sword(this); wp.push_back(p); }
		if (index % 3 == 1) {
			Weapon* p = new Bomb(this);
			wp.push_back(p);
		}
		if (index % 3 == 2) { Weapon* p = new Arrow(this); wp.push_back(p);}
		cout << setw(3) << setfill('0') << Time / 60 << ":00 " << hq->color << " " << name << " " << hq->totalnum << " born" <<endl;
	}
};
class Ninja :public Warrior {
public:
	static int total;
	Ninja(int a,int b, Headquarter* d) :Warrior(a,b, "ninja", d) {
		if (index % 3 == 0) { Weapon* x = new Sword(this); Weapon* y = new Bomb(this); wp.push_back(x); wp.push_back(y); }
		if (index % 3 == 1) { Weapon* x = new Bomb(this); Weapon* y = new Arrow(this); wp.push_back(x); wp.push_back(y);}
		if (index % 3 == 2) { Weapon* x = new Arrow(this); Weapon* y = new Sword(this); wp.push_back(x); wp.push_back(y);}
		cout << setw(3) << setfill('0') << Time / 60 << ":00 " << hq->color << " " << name << " " << hq->totalnum << " born" << endl;
	}
};
class Iceman :public Warrior {
public:
	Weapon iw;
	static int total;
	Iceman(int a, int b,Headquarter* d) :Warrior(a,b, "iceman", d) {
		if (index % 3 == 0) { Weapon* p = new Sword(this); wp.push_back(p); }
		if (index % 3 == 1) {
			Weapon* p = new Bomb(this);
			wp.push_back(p);
		}
		if (index % 3 == 2) { Weapon* p = new Arrow(this); wp.push_back(p); }
		cout << setw(3) << setfill('0') << Time / 60 << ":00 " << hq->color << " " << name << " " << hq->totalnum << " born" << endl;
	}
	void move() {
		hp = hp - hp / 10;
		Warrior::move();
	}
};
class Lion :public Warrior {
public:
	Lion(int a,int b, Headquarter* d) :Warrior(a, b,"lion", d) {
		if (index % 3 == 0) { Weapon* p = new Sword(this); wp.push_back(p); }
		if (index % 3 == 1) {
			Weapon* p = new Bomb(this);
			wp.push_back(p);
		}
		if (index % 3 == 2) { Weapon* p = new Arrow(this); wp.push_back(p); }
		cout << setw(3) << setfill('0') << Time / 60 << ":00 " << hq->color << " " << name << " " << hq->totalnum << " born" << endl;
		cout << "Its loyalty is " << loyalty << endl;
	}
	bool isrun() {
		return loyalty <= 0;
	}
	void move() {
		loyalty -= K;
		Warrior::move();
	}
};
class Wolf :public Warrior {
public:
	Wolf(int a, int b,Headquarter* d) :Warrior(a,b, "wolf", d) {
		cout << setw(3) << setfill('0') << Time / 60 << ":00 " << hq->color << " " << name << " " << hq->totalnum << " born" << endl;
	}
};
class City {
public:
	City* left, *right;
	Warrior *redone, *blueone, *newred, *newblue;
	int x;
	Headquarter* hq;
	City(int n) {
		x = n;
		left = NULL;
		right = NULL;
		hq = NULL;
		redone = NULL;
		blueone = NULL;
		newred = NULL;
		newblue = NULL;
	}
	City(){
		left = NULL;
		right = NULL;
		hq = NULL;
		redone = NULL;
		blueone = NULL;
		newred = NULL;
		newblue = NULL;
	}
	~City() {
		if (redone) {
			delete redone;
		}
		if (blueone) {
			delete blueone;
		}
	}
	void battle();
};
bool sort1(const Weapon* a1, const Weapon* a2) {
	if (a1 == NULL || a2 == NULL) {
		return false;
	}
	if (a1->index == 2 && a2->index == 2) {
		return a1->hp < a2->hp;
	}
	else {
		return a1->index < a2->index;
	}
}
bool sort2(const Weapon* a1, const Weapon* a2) {
	if (a1 == NULL || a2 == NULL) {
		return false;
	}
	if (a1->index == 2 && a2->index == 2) {
		return a1->hp > a2->hp;
	}
	else {
		return a1->index < a2->index;
	}
}
void clearw(vector<Weapon*>& v) {
	if (v.size() > 0) {
		vector<Weapon*>::iterator it;
		for (it = v.begin(); it != v.end();) {
			if ((*it) == NULL) {
				it = v.erase(it);
			}
			else {
				++it;
			}
		}
	}
}
Warrior::~Warrior() {
	if (!wp.empty()) {
		for (int i = 0; i < wp.size(); ++i) {
			delete wp[i];
		}
	}
}
void Warrior::run() {
	cout << setw(3) << setfill('0') << Time / 60 << ":05 " << hq->color << " lion " << index << " ran away" << endl;
}
void Warrior::attack() {
	clearw(wp);
	if(wp.size()>1){
		sort(wp.begin(), wp.end(), sort1);
	}
}
void Warrior::rob(Warrior* w) {
	if (name=="wolf"&&w->name != "wolf"&&w->wp.size()>0) {
		sort(w->wp.begin(), w->wp.end(), sort2);
		int x = w->wp[0]->index;
		string wpn = w->wp[0]->name;
		int num = 0;
		for (int i = 0;i<w->wp.size(); ++i) {
			if (wp.size() >= 10 || w->wp[i]->index != x) {
				break;
			}
			w->wp[i]->setnew(this);
			wp.push_back(w->wp[i]);
			w->wp[i] = NULL;
			++num;
		}
		cout << setw(3) << setfill('0') << Time / 60 << ":35 " << hq->color << " wolf " << index << " took " << num << " " << wpn
			<< " from " << w->hq->color << " " << w->name << " " << w->index << " in city " << ct->x << endl;
		clearw(w->wp);
	}
}
void Warrior::victory(Warrior* w) {
	if (w->wp.size() > 0) {
		clearw(w->wp);
		if (w->wp.size() > 1) {
			sort(w->wp.begin(), w->wp.end(), sort2);
		}
		for (int i = 0; i < w->wp.size(); ++i) {
			if (wp.size() >= 10) {
				break;
			}
			w->wp[i]->setnew(this);
			wp.push_back(w->wp[i]);
			w->wp[i] = NULL;
		}
		clearw(w->wp);
	}
}
void Warrior::show() {
	if (hp>0) {
		int i, j, k; i = 0; j = 0; k = 0;
		for (int m = 0; m < wp.size(); ++m) {
			if (wp[m]) {
				if (wp[m]->index == 0) { ++i; }
				if (wp[m]->index == 1) { ++j; }
				if (wp[m]->index == 2) { ++k; }
			}
		}
		cout << setw(3) << setfill('0') << Time / 60 << ":55 " << hq->color << " " << name << " " << index
			<< " has " << i << " sword " << j << " bomb " << k << " arrow and " << hp << " elements" << endl;
	}
}
void City::battle() {
	if (redone&&blueone) {
		redone->attack();
		blueone->attack();
		vector<Weapon*>::iterator r = redone->wp.begin();
		vector<Weapon*>::iterator b = blueone->wp.begin();
		int round = 0;
		while ( (redone->wp.size() > 0 || blueone->wp.size() > 0)&&round<10000) {
			++round;
			if (x % 2 == 0) {
				if (blueone->wp.size() > 0) {
					(*b)->attack(redone);
					if ((*b)->hp == 0) {
						delete *b;
						b = blueone->wp.erase(b);
						if (b == blueone->wp.end()) { b = blueone->wp.begin(); }
					}
					else {
						++b;
						if (b == blueone->wp.end()) { b = blueone->wp.begin(); }
					}
					if (redone->hp <= 0 || blueone->hp <= 0) { break; }
				}
				if (redone->wp.size() > 0) {
					(*r)->attack(blueone);
					if ((*r)->hp == 0) {
						delete *r;
						r = redone->wp.erase(r);
						if (r == redone->wp.end()) { r = redone->wp.begin(); }
					}
					else {
						++r; if (r == redone->wp.end()) { r = redone->wp.begin(); }
					}if (redone->hp <= 0 || blueone->hp <= 0) { break; }
				}
			}
			else {
				if (redone->wp.size() > 0) {
					(*r)->attack(blueone);
					if ((*r)->hp == 0) {
						delete *r;
						r = redone->wp.erase(r);
						if (r == redone->wp.end()) { r = redone->wp.begin(); }
					}
					else {
						++r; if (r == redone->wp.end()) { r = redone->wp.begin(); }
					}if (redone->hp <= 0 || blueone->hp <= 0) { break; }
				}
				if (blueone->wp.size() > 0) {
					(*b)->attack(redone);
					if ((*b)->hp == 0) {
						delete *b;
						b = blueone->wp.erase(b);
						if (b == blueone->wp.end()) { b = blueone->wp.begin(); }
					}
					else {
						++b;
						if (b == blueone->wp.end()) { b = blueone->wp.begin(); }
					}
					if (redone->hp <= 0 || blueone->hp <= 0) { break; }
				}
			}
		}
		if (redone->hp > 0 && blueone->hp > 0) {
			cout << setw(3) << setfill('0') << Time / 60 << ":40 both red " << redone->name << " " << redone->index
				<< " and blue " << blueone->name << " " << blueone->index << " were alive in city " << x << endl;
			if (redone->name == "dragon") {
				cout << setw(3) << setfill('0') << Time / 60 << ":40 red dragon " << redone->index << " yelled in city " << x << endl;
			}
			if (blueone->name == "dragon") {
				cout << setw(3) << setfill('0') << Time / 60 << ":40 blue dragon " << blueone->index << " yelled in city " << x << endl;
			}
			return;
		}
		if (redone->hp <= 0 && blueone->hp <= 0) {
			cout << setw(3) << setfill('0') << Time / 60 << ":40 both red " << redone->name << " " << redone->index
				<< " and blue " << blueone->name << " " << blueone->index << " died in city " << x << endl;
			delete redone, blueone;
			redone = NULL;
			blueone = NULL;
			return;
		}
		if (redone->hp > 0 && blueone->hp <= 0) {
			cout << setw(3) << setfill('0') << Time / 60 << ":40 red " << redone->name << " " << redone->index << " killed blue "
				<< blueone->name << " " << blueone->index << " in city " << x << " remaining " << redone->hp << " elements" << endl;
			if (redone->name == "dragon") {
				cout << setw(3) << setfill('0') << Time / 60 << ":40 red dragon " << redone->index << " yelled in city " << x <<endl;
			}redone->victory(blueone);
			delete blueone;
			blueone = NULL;
			return;
		}
		if (blueone->hp > 0 && redone->hp <= 0) {
			cout << setw(3) << setfill('0') << Time / 60 << ":40 blue " << blueone->name << " " << blueone->index << " killed red "
				<< redone->name << " " << redone->index << " in city " << x << " remaining " << blueone->hp << " elements" << endl;
			if (blueone->name == "dragon") {
				cout << setw(3) << setfill('0') << Time / 60 << ":40 blue dragon " << blueone->index << " yelled in city " << x << endl;
			}blueone->victory(redone);
			delete redone;
			redone = NULL;
			return;
		}
	}
}
Headquarter::Headquarter(int m, int s, int* whp, int*wpow,int* wseq, int n,City* c) {
	hp = m;
	ct = c;
	success = false;
	if (s == 0) {
		color = "red";
	}
	else {
		color = "blue";
	}
	warriornum = new int[n];
	warriorhp = new int[n];
	warriorpower = new int[n];
	warriorseq = new int[n];
	position = 0;
	totalnum = 0;
	isstop = false;
	warriors = NULL;
	for (int i = 0; i < n; i++) {
		warriornum[i] = 0;
		warriorhp[i] = whp[i];
		warriorpower[i] = wpow[i];
		warriorseq[i] = wseq[i];
	}
}
void Headquarter::Produce() {
	if (!isstop) {
		int j = Time / 60;
		if (hp >= warriorhp[warriorseq[j % 5]]) {
			if (warriorseq[j % 5] == 0) {
				warriornum[0]++;
				totalnum++;
				warriors= new Dragon(warriorhp[0], warriorpower[0], this);
			}
			if (warriorseq[j % 5] == 1) {
				warriornum[1]++;
				totalnum++;
				warriors= new  Ninja(warriorhp[1], warriorpower[1], this);
			}
			if (warriorseq[j % 5] == 2) {
				warriornum[2]++;
				totalnum++;
				warriors = new  Iceman(warriorhp[2], warriorpower[2], this);
			}
			if (warriorseq[j % 5] == 3) {
				warriornum[3]++;
				totalnum++;
				warriors = new Lion(warriorhp[3], warriorpower[3], this);
			}
			if (warriorseq[j % 5] == 4) {
				warriornum[4]++;
				totalnum++;
				warriors = new Wolf(warriorhp[4], warriorpower[4], this);
			}
			hp -= warriorhp[warriorseq[j % 5]];
		}
		else {
			isstop = true;
		}
	}
}
Headquarter::~Headquarter() {
	if (warriors) {
		delete warriors;
	}
	delete warriornum;
	delete warriorhp;
	delete warriorseq;
}
void Headquarter::show() {
	cout << setw(3) << setfill('0') << Time/60 << ":50 " << hp << " elements in " << color << " headquarter" << endl;
}
void Warrior::move() {
	cout << setw(3) << setfill('0') << Time / 60 << ":10 ";
	if (hq->color == "red") {
		if (position == 0) {
			ct = hq->ct;
			position = 1;
			ct->newred = this;
			hq->warriors = NULL;
		}
		else if (ct->hq) {
			if (ct->hq->color == "blue") {
				cout << hq->color << " " << name << " " << index << " reached " << ct->hq->color << " headquarter with " << hp
					<< " elements and force " << power << endl;
				hq->success = true;
				return;
			}
			else {
				ct->right->newred = this;
				ct->redone = NULL;
				ct = ct->right;
				++position;
			}
		}else {
			ct->right->newred = this;
			ct->redone = NULL;
			ct = ct->right;
			++position;
		}
	}
	else {
		if (position == 0) {
			ct = hq->ct;
			position = ct->x;
			ct->newblue = this;
			hq->warriors = NULL;
		}
		else if (ct->hq) {
			if (ct->hq->color == "red") {
				cout << hq->color << " " << name << " " << index << " reached " << ct->hq->color << " headquarter with " << hp
					<< " elements and force " << power << endl;
				hq->success = true;
				return;
			}
			else {
				ct->left->newblue = this;
				ct->blueone = NULL;
				ct = ct->left;
				position -= 1;
			}
		} else{
			ct->left->newblue = this;
			ct->blueone = NULL;
			ct = ct->left;
			position -= 1;
		}
	}
	cout << hq->color << " " << name << " " << index << " marched to city " << ct->x << " with " << hp
		<< " elements and force " << power << endl;
	return;
}
int main() {
	int t, mhp,n,endtime;
	int hp[5];
	int power[5];
	int rseq[5] = { 2,3,4,1,0 };
	int bseq[5] = { 3,0,1,2,4 };
	cin >> t;
	for (int i = 1; i <= t; ++i) {
		cin >> mhp >> n >> K >> endtime;
		for (int j = 0; j < 5; ++j) {
			cin >> hp[j];
		}
		City **ct = new City*[n];
		for (int k = 0; k < 5; ++k) {
			cin >> power[k];
		}
		for (int m = 0; m < n; ++m) {
			ct[m] = new City(m + 1);
		}
		if (n > 1) {
			ct[0]->right = ct[1];
			ct[n - 1]->left = ct[n - 2];
			for (int m = 1; m < n - 1; ++m) {
				ct[m]->left = ct[m - 1];
				ct[m]->right = ct[m + 1];
			}
		}
		Headquarter red(mhp, 0, hp, power,rseq, 5,ct[0]);
		ct[0]->hq = &red;
		Headquarter blue(mhp, 1, hp, power,bseq, 5,ct[n-1]);
		ct[n - 1]->hq = &blue;
		cout << "Case " << i << ":" <<endl;
		for (Time = 0; Time <= endtime; Time = Time + 5) {
			if (Time % 60 == 0&&(!red.isstop||!blue.isstop)) {
				red.Produce();
				blue.Produce();
			}
			if (Time % 60 == 5) {
				if (red.warriors) {
					if (red.warriors->name == "lion"&&red.warriors->loyalty <= 0) {
						red.warriors->run();
						delete red.warriors;
						red.warriors = NULL;
					}
				}
				for (int m = 0; m < n; ++m) {
					if (ct[m]->redone) {
						if (ct[m]->redone->name == "lion"&&ct[m]->redone->loyalty <= 0) {
							ct[m]->redone->run();
							delete ct[m]->redone;
							ct[m]->redone = NULL;
						}
					}
					if (ct[m]->blueone) {
						if (ct[m]->blueone->name == "lion"&&ct[m]->blueone->loyalty <= 0) {
							ct[m]->blueone->run();
							delete ct[m]->blueone;
							ct[m]->blueone = NULL;
						}
					}
				}
				if (blue.warriors) {
					if (blue.warriors->name == "lion"&&blue.warriors->loyalty <= 0) {
						blue.warriors->run();
						delete blue.warriors;
						blue.warriors = NULL;
					}
				}
			}
			if (Time % 60 == 10) {
				if (ct[0]->blueone) {
					ct[0]->blueone->move();
					cout << setw(3) << setfill('0') << Time / 60 << ":10 red headquarter was taken" << endl;
				}
				if (red.warriors) {
					red.warriors->move();
				}
				if (n > 1) {
					if (ct[1]->blueone) {
						ct[1]->blueone->move();
					}
					for (int h = 1; h < n - 1; ++h) {
						if (ct[h - 1]->redone) {
							ct[h - 1]->redone->move();
						}
						if (ct[h + 1]->blueone) {
							ct[h + 1]->blueone->move();
						}
					}
					if (ct[n - 2]->redone) {
						ct[n - 2]->redone->move();
					}
				}
				if (blue.warriors) {
					blue.warriors->move();
				}
				if (ct[n - 1]->redone) {
					ct[n-1]->redone->move();
					cout << setw(3) << setfill('0') << Time / 60 << ":10 blue headquarter was taken" << endl;
				}
				for (int i = 0; i < n; ++i) {
					if (ct[i]->newred) {
						ct[i]->redone = ct[i]->newred;
						ct[i]->newred = NULL;
					}if (ct[i]->newblue) {
						ct[i]->blueone = ct[i]->newblue;
						ct[i]->newblue = NULL;
					}
				}
			}
			if (red.success || blue.success) { break; }
			if (Time % 60 == 35) {
				for (int i = 0; i < n; ++i) {
					if (ct[i]->redone&&ct[i]->blueone) {
						ct[i]->redone->rob(ct[i]->blueone);
						ct[i]->blueone->rob(ct[i]->redone);
					}
				}
			}
			if (Time % 60 == 40) {
				for (int i = 0; i < n; ++i) {
						ct[i]->battle();
				}
			}
			if (Time % 60 == 50) {
				red.show();
				blue.show();
			}
			if (Time % 60 == 55) {
				if (red.warriors) {
					red.warriors->show();
				}
				for (int i = 0; i < n; ++i) {
					if (ct[i]->redone) {
						ct[i]->redone->show();
					}
					if (ct[i]->blueone) {
						ct[i]->blueone->show();
					}
				}
				if (blue.warriors) {
					blue.warriors->show();
				}
			}
		}
		for (int i = 0; i < n; ++i) {
			if (ct[i]) {
				delete ct[i];
			}
		}delete[] ct;
	}
	return 0;
}

