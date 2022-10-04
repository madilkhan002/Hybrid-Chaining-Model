#include<iostream>
#include"graphics.h"
using namespace std;

// binary search tree
class TreeNode {
public:
	TreeNode* right;
	TreeNode* left;
	int val;
	TreeNode(int val) :val(val), left(0), right(0) {}
};

class BST {
public:
	TreeNode* bstRoot;
	BST() {
		bstRoot = 0;
	}

	void bstInsert(int val) {
		bstRoot = bstInsertHelper(val, bstRoot);
	}

	bool search(int val) {
		TreeNode* temp = bstRoot;
		while (temp) {
			if (val == temp->val) return 1;
			else if (val < temp->val) temp = temp->left;
			else if (val > temp->val) temp = temp->right;
		}
		return 0;
	}


private:
	//insertion helper
	TreeNode* bstInsertHelper(int val, TreeNode* r) {
		if (!r) {
			TreeNode* newNode = new TreeNode(val);
			r = newNode;
			return r;
		}
		if (val < r->val) {
			r->left = bstInsertHelper(val, r->left);
		}
		else if (val > r->val) {
			r->right = bstInsertHelper(val, r->right);
		}
		return r;
	}
};

//AVL
class AvlNode {
public:
	AvlNode* right;
	AvlNode* left;
	int val;
	BST bstObj;
	AvlNode(int val) :val(val), left(0), right(0) {}
};

class AVL {
public:
	AvlNode* AvlRoot = 0;

	TreeNode* getBSTRoot(int val) {
		AvlNode* temp = avlSearch(val % 10);
		return temp->bstObj.bstRoot;
	}

	void insert(int val) {
		AvlRoot = insertHelper(val, AvlRoot);
	}

	void avlConverter() {
		AvlRoot = avlConverterHelper(AvlRoot);
	}

	void addElement(int val) {
		AvlNode* temp = avlSearch(val % 10);
		//insert first in hashTree(AVL) then in BST
		if (temp == 0) {
			insert(val % 10);
			temp = avlSearch(val % 10);
		}
		temp->bstObj.bstInsert(val);
	}

	bool searchElement(int val) {
		AvlNode* temp = avlSearch(val % 10);
		if (temp) {
			if (temp->bstObj.search(val)) {
				return true;
			}
		}
		return false;
	}

	//get the balance factor
	int getBalanceFactor(AvlNode* r) {
		if (!r) return -1;
		return (height(r->left) - height(r->right));
	}

	//search avl key
	AvlNode* avlSearch(int val) {
		AvlNode* temp = AvlRoot;
		while (temp) {
			if (temp->val == val) return temp;
			else if (val < temp->val) temp = temp->left;
			else if (val > temp->val) temp = temp->right;
		}
		return nullptr;
	}

private:
	//height
	int height(AvlNode* r) {
		if (!r) return -1;
		int x, y;
		x = height(r->left);
		y = height(r->right);
		if (x > y) return x + 1;
		else return y + 1;
	}

	//Left Roation
	AvlNode* leftRotation(AvlNode* r) {
		AvlNode* rR = r->right;
		AvlNode* rL = rR->left;
		rR->left = r;
		r->right = rL;
		return rR;
	}
	//Right Roation
	AvlNode* rightRotation(AvlNode* r) {
		AvlNode* rL = r->left;
		AvlNode* lR = rL->right;
		rL->right = r;
		r->left = lR;
		return rL;
	}

	//insert node helper
	AvlNode* insertHelper(int val, AvlNode* r) {
		if (!r) {
			AvlNode* n(new AvlNode(val));
			r = n;
			return r;
		}
		if (val < r->val) {
			r->left = insertHelper(val, r->left);
		}
		else if (val > r->val) {
			r->right = insertHelper(val, r->right);
		}
		return r;
	}

	//avl converter
	AvlNode* avlConverterHelper(AvlNode* r) {
		if (!r) return r;
		r->left = avlConverterHelper(r->left);
		r->right = avlConverterHelper(r->right);

		int bf = getBalanceFactor(r);

		if (bf >= 2 && getBalanceFactor(r->left) >= 0) {
			return rightRotation(r);
		}
		else if (bf >= 2 && getBalanceFactor(r->left) < 0) {
			r->left = leftRotation(r->left);
			return rightRotation(r);
		}
		else if (bf <= -2 && getBalanceFactor(r->right) <= 0) {
			return leftRotation(r);
		}
		else if (bf <= -2 && getBalanceFactor(r->right) > 0) {
			r->right = rightRotation(r->right);
			return leftRotation(r);
		}
		return r;
	}

};

//height of any tree
int height(AvlNode* r) {
	if (!r) return -1;
	int x, y;
	x = height(r->left);
	y = height(r->right);
	if (x > y) return x + 1;
	else return y + 1;
}
//get the balance tree
int getBalanceFactor(AvlNode* r) {
	if (!r) return -1;
	return (height(r->left) - height(r->right));
}

//display AVL
void displayTree(AvlNode* r, int x, int y, int gap, bool& imbalance) {
	if (!r) return;
	circle(x, y, 25);
	string s = to_string(r->val);
	char ch[5];
	int i = 0;
	for (char c : s) {
		ch[i++] = c;
	}
	ch[i] = '\0'; //null

	outtextxy(x - 3, y - 6, ch);//display the value

	if (r->left) {
		line(x, y + 25, x - 20 * gap, y + 45);
		displayTree(r->left, x - 20 * gap, y + 70, gap - 1, imbalance);
	}
	if (r->right) {
		line(x, y + 25, x + 15 * gap, y + 50);
		displayTree(r->right, x + 15 * gap, y + 75, gap - 2, imbalance);
	}

	//display the balance factor
	if (getBalanceFactor(r) > 1 || getBalanceFactor(r) < -1 && imbalance == false) {
		setcolor(14);
		outtextxy(x + 30, y - 15, "< - - Imbalanced Here");
		setcolor(15);
		imbalance = true;
	}
}

//input
int input(int x, int y) {
	string s;
	char ch;
	int i = 0;
	int counter = 0;
	while (1) {
		outtextxy(x + 262 + i, 84, "|");
		ch = getch();
		if (ch == 13 && s.length() > 0) {
			break;
		}
		else if (ch == 8 && i >= 8) {
			s.pop_back();
			i -= 8;
			outtextxy(x + 262 + i, 84, "   ");
			counter--;
		}
		else if (ch >= '0' && ch <= '9' && counter < 4) {
			char n[2];
			n[0] = ch;
			n[1] = '\0';
			outtextxy(x + 262 + i, 84, n);
			s.push_back(ch);
			i += 8;
			counter++;
		}
	}


	return stoi(s);
}


//display BST
void displayBSTHelper(TreeNode* r, int x, int y, int gap) {
	if (!r) return;

	circle(x, y, 25);
	setfillstyle(SOLID_FILL, CYAN);
	floodfill(x + 1, y + 1, WHITE);
	string s = to_string(r->val);

	char ch[10];
	int i = 0;
	for (char c : s) {
		ch[i++] = c;
	}
	ch[i] = '\0';
	outtextxy(x - 7, y - 7, ch);
	if (r->left) {
		line(x, y + 25, x - 20 * gap, y + 45);
		displayBSTHelper(r->left, x - 20 * gap, y + 70, gap - 1);
	}
	if (r->right) {
		line(x, y + 25, x + 15 * gap, y + 50);
		displayBSTHelper(r->right, x + 15 * gap, y + 75, gap - 2);
	}
}

//search element in BST
void searchDisplayBST(TreeNode* r, int val) {
	int x = 600, y = 250, g = 10;
	TreeNode* t = r;
	while (t) {
		if (t->val == val) {
			setfillstyle(SOLID_FILL, DARKGRAY);
			floodfill(x, y - 3, WHITE);
			delay(800);

			outtextxy(550, 600, "VALUE FOUND!");
			setfillstyle(SOLID_FILL, RED);
			floodfill(x, y - 3, WHITE);
			break;
		}
		else if (val < t->val) {
			x = x - 20 * g;
			y = y + 70;
			g = g - 1;
			t = t->left;
		}
		else {
			x = x + 15 * g;
			y = y + 75;
			g = g - 2;
			t = t->right;
		}
	}
	if (t == nullptr) {
		outtextxy(530, 600, "ERROR 404! VALUE NOT FOUND");
	}
}

//show the bst
void displayBST(TreeNode* r, int val, bool search) {
	cleardevice();
	outtextxy(525, 50, "BINARY SEARCH TREE");

	//exit
	outtextxy(570, 100, "Go Back");
	rectangle(560, 90, 635, 125);
	int x = 600, y = 250;
	int x1, y1;
	displayBSTHelper(r, x, y, 10);
	//search the value
	if (search == true) {
		searchDisplayBST(r, val);
	}

	while (1) {

		while (!ismouseclick(WM_LBUTTONDOWN)) {}
		getmouseclick(WM_LBUTTONDOWN, x1, y1);
		if (x1 >= 560 && x1 <= 635 && y1 >= 90 && y1 <= 125) {
			break;
		}
	}
}

//search element in avl
void searchDisplayAVL(AvlNode* r, int val) {
	int x = 600, y = 250, g = 10;
	AvlNode* t = r;

	while (t) {
		if (t->val == val) {
			setfillstyle(SOLID_FILL, RED);
			floodfill(x - 9, y - 8, WHITE);

			break;
		}
		else if (val < t->val) {
			x = x - 20 * g;
			y = y + 70;
			g = g - 1;
			t = t->left;
		}
		else if (val > t->val) {
			x = x + 15 * g;
			y = y + 75;
			g = g - 2;
			t = t->right;
		}
	}
}


//initialze the screen
void initializeScreen() {
	outtextxy(450, 20, "-  -  -  -  -  -  -  -  HYBRID CHAINING MODEL  -  -  -  -  -  -  -  -");
	rectangle(570, 80, 700, 105);
	outtextxy(513, 83, "Value:");

	rectangle(490, 130, 570, 155);
	outtextxy(510, 135, "Insert");

	//search
	rectangle(590, 130, 670, 155);
	outtextxy(608, 135, "Search");

	//exit
	rectangle(690, 130, 770, 155);
	outtextxy(718, 135, "Exit");
}


int startup() {
	int gd = DETECT;
	int gm;
	initwindow(400, 568, "Menu", 430, 70);

	readimagefile("Menu.jpg", 0, 0, 400, 568);

	//rectangle(70, 175, 320, 215);		//hybrid chaining model
	//rectangle(170, 233, 227, 273);	//exit

	int x = 0, y = 0;

	while (1) {
		while (!ismouseclick(WM_LBUTTONDOWN)) {}
		getmouseclick(WM_LBUTTONDOWN, x, y);

		if (x >= 70 && x <= 320 && y >= 175 && y <= 215) {
			closegraph();
			int gd = DETECT;
			int gm;
			initwindow(1300, 700, "Hashing Tree", 30, 10);
			outtextxy(600, 350, "Loading");		delay(500);
			outtextxy(600, 350, "Loading.");	delay(500);
			outtextxy(600, 350, "Loading..");	delay(500);
			outtextxy(600, 350, "Loading...");	delay(500);
			cleardevice();
			return 0;
		}
		else if (x >= 170 && x <= 227 && y >= 233 && y <= 273) {
			cleardevice();
			outtextxy(160, 230, "Thank You :)");
			delay(1500);
			return 1;
		}
	}
}


int main() {
	int a = startup();
	if (a == 1) {
		return 0;
	}
	else {
		initializeScreen();

		//coordinates 
		int x = 600, y = 250;
		AVL o;

		int x1 = -1;
		int y1 = -1;

		int val = 0;


		while (1) {

			while (!ismouseclick(WM_LBUTTONDOWN)) {}

			getmouseclick(WM_LBUTTONDOWN, x1, y1);

			bool imbalance = false;

			if (x1 >= 520 && x1 <= 700 && y1 >= 80 && y1 <= 105) {
				val = input(315, 50);
			}

			if (x1 >= 490 && x1 <= 570 && y1 >= 130 && y1 <= 155) {
				o.addElement(val);	 //add element in bst & in avl
				displayTree(o.AvlRoot, x, y, 10, imbalance);	// display the avl



				if (imbalance) {	 // balancing
					delay(2000);
					o.avlConverter();
					cleardevice();
					initializeScreen();
					displayTree(o.AvlRoot, x, y, 10, imbalance);
				}

				searchDisplayAVL(o.AvlRoot, val % 10);//display the key

				//search the key
				displayTree(o.AvlRoot, x, y, 10, imbalance);// display the key

				{
					//display the bst of searched key
					delay(1000);
					displayBST(o.getBSTRoot(val), 0, false);
				}

				//initaize the main screen again
				cleardevice();
				initializeScreen();
				displayTree(o.AvlRoot, x, y, 10, imbalance);
			}
			else if (x1 >= 590 && x1 <= 670 && y1 >= 130 && y1 <= 155) {
				if (o.avlSearch(val % 10)) {

					searchDisplayAVL(o.AvlRoot, val % 10);//display the key

					outtextxy(550, 600, "Key Found!");

					//display the bst of searched key
					delay(1000);

					displayBST(o.getBSTRoot(val), val, true);

					//display the hashtree
					bool imbalace = false;
					cleardevice();
					initializeScreen();
					displayTree(o.AvlRoot, x, y, 10, imbalace);
				}
				else {
					outtextxy(550, 600, "Error 404! Key Not Found!");
					delay(1000);
					bool imbalance = false;
					cleardevice();
					initializeScreen();
					displayTree(o.AvlRoot, x, y, 10, imbalance);
				}
			}
			else if (x1 >= 690 && x1 <= 770 && y1 >= 130 && y1 <= 155) {
				rectangle(687, 100, 737, 125);
				cleardevice();
				outtextxy(580, 330, "Thank You :)");
				delay(2000);
				break;
			}
		}
	}

	closegraph();
	return 0;
}
