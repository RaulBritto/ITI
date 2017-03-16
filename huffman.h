using namespace std;

struct NO{
	unsigned int frequency;
	char code[9];
	//string code;
	char value;
	bool leaf; // todos freq sao true
};
typedef struct NO huffTree;



struct TreeVector{
	vector<NO> *p;
};
typedef struct TreeVector treeVector;
