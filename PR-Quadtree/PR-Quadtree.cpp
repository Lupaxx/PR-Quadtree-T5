/**
 * UFRJ   - Universidade Federal do Rio de Janeiro
 * DMA/IM - Departamento de Matemática Aplicada do Instituto de Matemática
 *
 *          (MAE 016) Top. Eng. Dados B: Estruturas de Dados e seus Algoritmos
 *
 *          Tarefa de programação 5: PR-Quadtree
 *
 *          Prof. Milton R Ramirez (milton@matematica.ufrj.br)
 *          Data da criação    : 22 de dezembro de 2023
 *          Data da alteração: 22 de dezembro de 2023
 * 
 *          Grupo: 
 *              Luiza Costa Pacheco 119169147
 *              Eric Silva Kraus    115104789
 *              Felipe Gomes Táparo 119959237 
 *
 **/

#include <cmath>
#include <iostream>
#include <initializer_list>
#include <vector>
using namespace std;    

struct Point2D {
	int x;
	int y;
	Point2D(int _x, int _y)
	{
		x = _x;
		y = _y;
	}
	Point2D()
	{
		x = 0;
		y = 0;
	}
};

struct Reg_Node {
	Point2D pos;
	int data;
	Reg_Node(Point2D _pos, int _data = 0)
	{
		pos = _pos;
		data = _data;
	}
	Reg_Node() { pos = Point2D(); data = 0; }
};

class no_PR_Quadtree {
	Point2D topLeft;
	Point2D botRight;

	Reg_Node* n;

	bool eh_folha;

	no_PR_Quadtree* topLeftTree;
	no_PR_Quadtree* topRightTree;
	no_PR_Quadtree* botLeftTree;
	no_PR_Quadtree* botRightTree;
    
public:
	// Contrutor de raiz nula, tamanho nulo
	no_PR_Quadtree()
	{
		topLeft = Point2D(0, 0);
		botRight = Point2D(0, 0);
		n = NULL;
		eh_folha = true;
		topLeftTree = NULL;
		topRightTree = NULL;
		botLeftTree = NULL;
		botRightTree = NULL;
	}
	//  Contrutor para raiz nula, tamanho definido
	no_PR_Quadtree(Point2D topL, Point2D botR)
	{
		topLeft = topL;
		botRight = botR;
		n = NULL;
		eh_folha = true;
		topLeftTree = NULL;
		topRightTree = NULL;
		botLeftTree = NULL;
		botRightTree = NULL;
	}
	//Contrutor para raiz definida por lista, tamanho defnido
	no_PR_Quadtree(Point2D topL, Point2D botR, initializer_list<Point2D> points)
	{
		topLeft = topL;
		botRight = botR;
		n = NULL;
		eh_folha = true;
		topLeftTree = NULL;
		topRightTree = NULL;
		botLeftTree = NULL;
		botRightTree = NULL;
		int cont = 0;
		for (auto &p : points){
			Reg_Node p_(p);
        	insert(&p_);
		}
	}
	void insert(Reg_Node*);
	Reg_Node* search(Point2D);
	bool inBoundary(Point2D);
	vector<Reg_Node> searchInArea (Point2D, Point2D);
	Reg_Node* findNearestPoint(Point2D, double);

};

void no_PR_Quadtree::insert(Reg_Node* node)
{
	if (node == NULL)
		return;

	if (!inBoundary(node->pos))
		return;

	if (abs(topLeft.x - botRight.x) <= 1
		&& abs(topLeft.y - botRight.y) <= 1) {
		if (n == NULL)
			n = node;
		return;
	}

    if (eh_folha && n == NULL) {
        n = node;
        return;
    }

    if(eh_folha && n != NULL){
        eh_folha = false;
        insert(n);
    }

	if ((topLeft.x + botRight.x) / 2 >= node->pos.x) {
		if ((topLeft.y + botRight.y) / 2 >= node->pos.y) {
			if (topLeftTree == NULL)
				topLeftTree = new no_PR_Quadtree(
					Point2D(topLeft.x, topLeft.y),
					Point2D((topLeft.x + botRight.x) / 2,
						(topLeft.y + botRight.y) / 2));
			cout << "Desci pela topLeftTree com o ponto: "<< node->data << endl;
			topLeftTree->insert(node);
		}

		else {
			if (botLeftTree == NULL)
				botLeftTree = new no_PR_Quadtree(
					Point2D(topLeft.x,
						(topLeft.y + botRight.y) / 2),
					Point2D((topLeft.x + botRight.x) / 2,
						botRight.y));
			cout << "Desci pela botLeftTree com o ponto: "<< node->data << endl;
			botLeftTree->insert(node);
		}
	}
	else {
		if ((topLeft.y + botRight.y) / 2 >= node->pos.y) {
			if (topRightTree == NULL)
				topRightTree = new no_PR_Quadtree(
					Point2D((topLeft.x + botRight.x) / 2,
						topLeft.y),
					Point2D(botRight.x,
						(topLeft.y + botRight.y) / 2));
			cout << "Desci pela topRightTree com o ponto: "<< node->data << endl;
			topRightTree->insert(node);
		}

		// Indicates botRightTree
		else {
			if (botRightTree == NULL)
				botRightTree = new no_PR_Quadtree(
					Point2D((topLeft.x + botRight.x) / 2,
						(topLeft.y + botRight.y) / 2),
					Point2D(botRight.x, botRight.y));
			cout << "Desci pela botRightTree com o ponto: "<< node->data << endl;
			botRightTree->insert(node);
		}
	}
}

Reg_Node* no_PR_Quadtree::search(Point2D p)
{
	if (!inBoundary(p))
		return NULL;

	if (eh_folha && n != NULL)
		return n;

	if ((topLeft.x + botRight.x) / 2 >= p.x) {
		if ((topLeft.y + botRight.y) / 2 >= p.y) {
			if (topLeftTree == NULL)
				return NULL;
			return topLeftTree->search(p);
		}

		else {
			if (botLeftTree == NULL)
				return NULL;
			return botLeftTree->search(p);
		}
	}
	else {
		if ((topLeft.y + botRight.y) / 2 >= p.y) {
			if (topRightTree == NULL)
				return NULL;
			return topRightTree->search(p);
		}

		else {
			if (botRightTree == NULL)
				return NULL;
			return botRightTree->search(p);
		}
	}
};

bool no_PR_Quadtree::inBoundary(Point2D p)
{
	return (p.x >= topLeft.x && p.x <= botRight.x
			&& p.y >= topLeft.y && p.y <= botRight.y);
}

vector<Reg_Node> no_PR_Quadtree::searchInArea (Point2D topLeft, Point2D botRight)
{

	 vector<Reg_Node> result;

    // Ve se os pontos recebidos estão dentro da árvore
    if (!inBoundary(topLeft) || !inBoundary(botRight))
        return result;

    // Verifica se o nó atual é uma folha e se o ponto contido no nó está dentro da área de busca
    if (eh_folha && n != NULL && n->pos.x >= topLeft.x && n->pos.x <= botRight.x &&
        n->pos.y >= topLeft.y && n->pos.y <= botRight.y) {
        result.push_back(*n);
    }

    // Recursivamente chama a função para os outros quadrantes que podem estar contidos na área
    if (topLeftTree != NULL) {
        vector<Reg_Node> topLeftResult = topLeftTree->searchInArea(topLeft, botRight);
        result.insert(result.end(), topLeftResult.begin(), topLeftResult.end());
    }

    if (topRightTree != NULL) {
        vector<Reg_Node> topRightResult = topRightTree->searchInArea(topLeft, botRight);
        result.insert(result.end(), topRightResult.begin(), topRightResult.end());
    }

    if (botLeftTree != NULL) {
        vector<Reg_Node> botLeftResult = botLeftTree->searchInArea(topLeft, botRight);
        result.insert(result.end(), botLeftResult.begin(), botLeftResult.end());
    }

    if (botRightTree != NULL) {
        vector<Reg_Node> botRightResult = botRightTree->searchInArea(topLeft, botRight);
        result.insert(result.end(), botRightResult.begin(), botRightResult.end());
    }

    return result;

}

Reg_Node* no_PR_Quadtree::findNearestPoint(Point2D center, double R) {
	// Verifica se o centro está dentro dos limites da quadtree
	if (!inBoundary(center))
        return NULL;

    Reg_Node* nearest = NULL;

    // Se o nó atual é uma folha e está dentro do círculo, verifica se é o ponto mais próximo
    if (eh_folha && n != NULL) {
		// Calcula a distância euclidiana entre o ponto atual e o centro
        double distance = sqrt(pow(n->pos.x - center.x, 2) + pow(n->pos.y - center.y, 2));
		// Verifica se o ponto está dentro do círculo e se é mais próximo que o atual ponto mais próximo
        if (distance <= R && (nearest == NULL || distance < sqrt(pow(nearest->pos.x - center.x, 2) + pow(nearest->pos.y - center.y, 2)))) {
            nearest = n;
        }
    }

    // Recursivamente chama a função para os quadrantes que podem conter pontos dentro do círculo
    if (topLeftTree != NULL && topLeftTree->inBoundary(center)) {
        Reg_Node* topLeftNearest = topLeftTree->findNearestPoint(center, R);
		// Atualiza o ponto mais próximo se o ponto encontrado é mais próximo que o atual mais próximo
        if (topLeftNearest != NULL && (nearest == NULL || sqrt(pow(topLeftNearest->pos.x - center.x, 2) + pow(topLeftNearest->pos.y - center.y, 2)) < sqrt(pow(nearest->pos.x - center.x, 2) + pow(nearest->pos.y - center.y, 2)))) {
            nearest = topLeftNearest;
        }
    }

    if (topRightTree != NULL && topRightTree->inBoundary(center)) {
        Reg_Node* topRightNearest = topRightTree->findNearestPoint(center, R);
        if (topRightNearest != NULL && (nearest == NULL || sqrt(pow(topRightNearest->pos.x - center.x, 2) + pow(topRightNearest->pos.y - center.y, 2)) < sqrt(pow(nearest->pos.x - center.x, 2) + pow(nearest->pos.y - center.y, 2)))) {
            nearest = topRightNearest;
        }
    }

    if (botLeftTree != NULL && botLeftTree->inBoundary(center)) {
        Reg_Node* botLeftNearest = botLeftTree->findNearestPoint(center, R);
        if (botLeftNearest != NULL && (nearest == NULL || sqrt(pow(botLeftNearest->pos.x - center.x, 2) + pow(botLeftNearest->pos.y - center.y, 2)) < sqrt(pow(nearest->pos.x - center.x, 2) + pow(nearest->pos.y - center.y, 2)))) {
            nearest = botLeftNearest;
        }
    }

    if (botRightTree != NULL && botRightTree->inBoundary(center)) {
        Reg_Node* botRightNearest = botRightTree->findNearestPoint(center, R);
        if (botRightNearest != NULL && (nearest == NULL || sqrt(pow(botRightNearest->pos.x - center.x, 2) + pow(botRightNearest->pos.y - center.y, 2)) < sqrt(pow(nearest->pos.x - center.x, 2) + pow(nearest->pos.y - center.y, 2)))) {
            nearest = botRightNearest;
        }
    }

    return nearest;
}


