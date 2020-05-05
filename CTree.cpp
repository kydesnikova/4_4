#include "CTree.h"
#include <math.h>

void CTree::view_all()
{
	view(root, 0);
}

CTree::CTree(const char* n_name, int n_n, int n_key)
{
	CVetv * t = new CVetv(n_n, n_key);
	root = t;  
}

CTree::CTree(const char* fn, const char* n_name)
{
	FILE * f;
	fopen_s(&f, fn, "rt");
	if (!f)
	{
		printf("file not found");
		return;
	}
	char ts[255] = "";
	fgets(ts, 255, f);
	int inkey, ininf;
	sscanf_s(ts, "%i %i", &inkey, &ininf);
	CVetv * t = new CVetv(ininf, inkey);

	root = t;

	while (fgets(ts, 255, f)) {
		sscanf_s(ts, "%i %i", &inkey, &ininf);
		add(ininf, inkey);
	}
	fclose(f);
}

CVetv* CTree::find(int fnd)
{
	return find(fnd, root);
}

CVetv* CTree::find(int fnd, CVetv* dr) 
{
	if (!dr) return NULL;
	if (dr->key == fnd) return dr;
	if (dr->key > fnd) return find(fnd, dr->l);	
	else if (dr->key < fnd) return find(fnd, dr->r);
	else return NULL;
}

CVetv* CTree::add(int n_inf, int n_key)
{
	int	find = 0;
	CVetv *	prev = NULL;

	CVetv * t = root;				
	while (t && !find) {
		prev = t;
		if (n_key == t->key)
			find = 1;	 
		else
			if (n_key < t->key) t = t->l;
			else   t = t->r;
	}

	if (!find) {					
		t = new CVetv(n_inf, n_key);				
		if (n_key < prev->key)		
			prev->l = t;	
		else    prev->r = t;		
		return t;
	}
	else
		return NULL;
}

CVetv::CVetv(int inf, int key)
{
	this->inf = inf;
	this->key = key;
	l = r = NULL;
}

void CTree::view(CVetv* t, int lv)
{
	if (t) {
		view(t->r, lv + 1);		
		for (int i = 0; i < lv; i++)  printf("    ");
		printf(" %i\n", t->key);
		view(t->l, lv + 1); 		
	}
}

CTree::~CTree()
{
	del_vet(root->r);
	del_vet(root->l);
	delete root;
}

// нет удаления (нужна ссылка на предка которого мы удаляем)
void CTree::del_vet(CVetv* dr)
{
	if (dr) {
		del_vet(dr->r); dr->r = NULL;
		del_vet(dr->l); dr->l = NULL;
	}
}

int CTree::odd_cnt(CVetv* t) // параметр t (указатель на узел, можно начать с любой части дерева)
{
	int c = 0; // целочисленная переменная (счётчик)
	if (t) { // существует ли параметр t (узел)
		c += odd_cnt(t->r); // рекурсивный вызов, вправо идём и прибавляем c
		if (t->l != NULL) // проверка на то, существует ли левая ветвь (она нужна для дальнейшнего условия)
		{
			if (fmod(t->l->key, 2) == 0) c++; // проверка на чётность левой ветки (если да, то +1)
		}
		c += odd_cnt(t->l); // рекурсивный вызов, влево идём и прибавляем c
	}
	return c; // возвращаем c
}

int CTree::odd_cnt()
{
	return odd_cnt(root);
}

int CTree::depth_tree(CVetv* dr) 
{
	if (!dr) return NULL;

	int left, right;

	if (dr->l != NULL) 
	{
		left = depth_tree(dr->l);
	}
	else 
	{
		left = 0;
	}

	if (dr->r != NULL) 
	{
		right = depth_tree(dr->r);
	}
	else 
	{
		right = 0;
	}

	int max = left > right ? left : right;

	return max + 1;
}

int CTree::depth_tree() 
{
	return depth_tree(root);
}

