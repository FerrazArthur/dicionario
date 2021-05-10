typedef struct{
        char *value;
}Info;
typedef struct BST{
	int balance;
        Info *inf;
        struct BST *left, *right;
}BST;
//--essas são estruturas para listas com elementos de informação Inf
typedef struct Node{
        Info *inf;
        struct Node *next;
}Node;
typedef struct{
        Node *first, *last;//como utilizarei apenas inserção no final, julgo pertinente manter registro do ultimo elemento para poupar processamento
}Head;
//--
//-essas são estruturas para listas com elementos de informação BST
typedef struct BSTNode{
        BST *inf;
        struct BSTNode *next;
}BSTNode;
typedef struct{
        BSTNode *first, *last;//como utilizarei apenas inserção no final, julgo pertinente manter registro do ultimo elemento para poupar processamento
}BSTHead;
//-
Info *createInfo(char *value){
        Info *inf=NULL;
	int  n = (strlen(value)/sizeof(char) + 1);
        if(inf = (Info *) malloc(sizeof(Info))){
		inf->value = (char *) malloc(sizeof(char)*n);
                strncpy(inf->value,value, n);
	}
        return inf;
}
//-
BSTHead *createBSTHeadLST(){//essa função sera chamada exclusivamente pela função insertLastBSTLST(...)
        BSTHead *ptr = NULL;
        if(ptr = (BSTHead *) malloc(sizeof(BSTHead)))
                ptr->first = ptr->last=NULL;
        if(!ptr)
                printf("Memoria insuficiente!\n");
        return ptr;
}
BSTNode *createBSTNodeLST(BST *inf){
        BSTNode *lst= NULL;
        if(lst = (BSTNode *) malloc(sizeof(BSTNode))){
                lst->inf = inf;
                lst->next = NULL;
        }
        if(!lst)
                printf("Memoria insuficiente!\n");
        return lst;
}
void insertLastBSTLST(BSTHead **lst,BST *inf){//cria a cabeça automaticamente caso seja passado um valor NULL
        BSTNode *ptr = NULL;
        if(!inf)
                return;
        if(!*lst)
                *lst = createBSTHeadLST();//cria a cabeça automaticamente caso seja passado um valor NULL;
        ptr = createBSTNodeLST(inf);
        if(*lst && ptr){
                if(!(*lst)->first)
                        (*lst)->first = (*lst)->last = ptr;//se first é NULL, ptr é apontado por first e last;
                else{
                        (*lst)->last->next = ptr;
                        (*lst)->last = ptr;
                }
        }
}
//tira o primeiro elemento da lista e o retorna
BSTNode *getFirstBSTLST(BSTHead *lst){
        BSTNode *ptr = NULL;
        if(lst && lst->first){
                if(lst->first == lst->last)//quando tiver apenas um elemento na lista para ser removido.
                        lst->last = NULL;
                ptr = lst->first;
                lst->first = ptr->next;
        }
        return ptr;
}
int isEmptyBSTLST(BSTHead *lst){
        if(!lst || !lst->first)
                return 1;
        return 0;
}
//-
void destroyBST(BST *bst);
BST *createNodeBST(Info *inf);
int isEmptyBST(BST *bst);
//--
Head *createHeadLST(){//essa função sera chamada exclusivamente pela função insertLastLST(...)
        Head *ptr = NULL;
        if(ptr = (Head *) malloc(sizeof(Head)))
                ptr->first = ptr->last=NULL;
        if(!ptr)
                printf("Memoria insuficiente!\n");
        return ptr;
}
Node *createNodeLST(Info *inf){
        Node *lst= NULL;
        if(lst = (Node *) malloc(sizeof(Node))){
                lst->inf = inf;
                lst->next = NULL;
        }
        if(!lst)
                printf("Memoria insuficiente!\n");
        return lst;
}
int isEmptyLST(Head *lst){
        if(!lst || !lst->first)
                return 1;
        return 0;
}
//essa função avança o ponteiro first de lst para a segunda posição e retorna a antiga primeira posição 
Node *getFirstLST(Head *lst){
        Node *ptr = NULL;
        if(!isEmptyLST(lst)){
                if(lst->first == lst->last)//quando tiver apenas um elemento na lista para ser removido.
                        lst->last = NULL;
                ptr = lst->first;
                lst->first = ptr->next;
        }
        return ptr;
}
//função que insere na ultima posição de uma lista
void insertLastLST(Head **lst, BST *bst){
//essa função recebe uma BST para que as verificações de condições sejam feitas aqui, reduzindo a complexidade das funções de manipulação de BST e facilitando o entendimento das mesmas.
        Node *ptr = NULL;
        if(isEmptyBST(bst))
                return;
        Info *inf = createInfo(bst->inf->value);//cria um novo endereço Info com valor  bst->inf->value
        if(!inf)
                return;
        if(!*lst)
                *lst = createHeadLST();//cria a cabeça automaticamente caso seja passado um valor NULL;
        ptr = createNodeLST(inf);
        if(*lst && ptr){
                if(!(*lst)->first)//se first é NULL, ptr é apontado por first e last;
                        (*lst)->first = (*lst)->last = ptr;
                else{//do contrário apenas last aponta pra ptr
                        (*lst)->last->next = ptr;
                        (*lst)->last = ptr;
                }
        }
}
//essa função retorna uma lista com i elementos escolhidos pelo usuário
Head *getlst(int i){
        char *x = NULL;
        BST *temp = NULL;
        Head *lst = NULL;
        while(i > 0){
                printf("Insira uma palavra: ");
                scanf("%s", x);
                temp = createNodeBST(createInfo(x));
		//aqui estamos usando um intermediário temp para que possamos reaproveitar o código de insertLastLST(..) para criar uma lista da forma convencional
                insertLastLST(&lst, temp);
                free(temp->inf);//a informação em lst não é temp->inf
		free(temp);
                i--;
        }
        return lst;
}
void freeLST(Head *lst){
        Node *pptr = NULL, *ptr = NULL;
        if(lst){
                ptr = lst->first;
                while(ptr){//libera memória de toda info e todo nó em Head 
                        pptr = ptr;
                        ptr = ptr->next;
                        free(pptr->inf);
                        free(pptr);
                }
                free(lst);
        }
}
void imprimeLST(Head *lst){
	Node *ptr = NULL;
	if(isEmptyLST(lst))
		return;
	ptr = lst->first;
	while(ptr){//imprime toda a lista Head 
		printf("%s, ", ptr->inf->value);
		ptr = ptr->next;
	}
	printf("\n");
	return;
}
//--
//retorna a subarvore esquerda 
BST *leftBST(BST *bst){
        BST *ptr = NULL;
        if(bst)//make sure bst is a pointer to a valid memory space
                ptr = bst->left;
        return ptr;
}
//retorna a subarvore direita
BST *rightBST(BST *bst){
        BST *ptr = NULL;
        if(bst)//make sure bst is a pointer to a valid memory space
                ptr = bst->right;
        return ptr;
}
//retorna o elemento de informação
Info *rootBST(BST *bst){//retorna o elemento de informação do nó bst
        Info *ptr = NULL;
        if(bst)
                ptr = bst->inf;
        return ptr;
}
int isEmptyBST(BST *bst){
        if(bst)
                return 0;
        return 1;
}
BST *createBST(){
        return NULL;
}
//retorna um BST com elemento de informação inf
BST *createNodeBST(Info *inf){
        BST *bst=NULL;
        if(!inf)
                printf("Informação nula!\n");
        bst = (BST *) malloc(sizeof(BST));
        if(inf && bst){
		bst->balance = 0;
                bst->inf= inf;
                bst->left=bst->right=NULL;
        }
        if(!bst)
                printf("Memória insuficiente!\n");
        return bst;
}
BST *searchBST(BST *bst, Info *inf){
//percorre recursivamente a arvore, caso encontre o elemento salva ele em ptr e retorne, caso contrário retorne ptr que estará vazio.
        static BST *ptr = NULL;
        if(!isEmptyBST(bst) && inf){
                if(strcmp(rootBST(bst)->value, inf->value) == 0)
                        ptr = bst;
	//enquanto não encontrar, passe recursivamente para as subarvores
                if(strcmp(rootBST(bst)->value, inf->value) > 0)
                        searchBST(leftBST(bst), inf);
                if(strcmp(rootBST(bst)->value, inf->value) < 0)
                        searchBST(rightBST(bst), inf);
        }
        return ptr;
}
//percorre recursivamente a arvore e retona NULL ou o elemento que aponta pro elemento com a informação buscada
BST *searchBST2(BST *bst, Info *inf){
	static BST *ptr = NULL;
	if(!isEmptyBST(bst) && inf){
		if(!isEmptyBST(bst->left)){//se existe a subarvore esquerda, procure em todos os nós dela;
			if(strcmp(rootBST(bst->left)->value, inf->value) == 0)//se essa sub.esquerda for o valor desejado, salve a raiz dela.
				ptr = bst;
	//enquanto não encontrar, passe recursivamente para as subarvores
                	searchBST2(leftBST(bst), inf);
                	searchBST2(rightBST(bst), inf);
		}
		if(!isEmptyBST(bst->right)){//se existe a subarvore direita, procura em todos os nós dela;
			if(strcmp(rootBST(bst->right)->value, inf->value) == 0)//se essa sub.direita for o valor desejado, salve a raiz dela 
				ptr = bst;
	//enquanto não encontrar, passe recursivamente para as subarvores
                	searchBST2(leftBST(bst), inf);
                	searchBST2(rightBST(bst), inf);
		}
	}
	return ptr;
}
void destroyBST(BST *bst){
        if(isEmptyBST(bst))//recursivamente deleta info e no de toda a arvore, começando do fim 
                return;
        destroyBST(leftBST(bst));
        destroyBST(rightBST(bst));
        free(rootBST(bst));
        free(bst);
        return;
}
int heightBST(BST *bst){//retorna qual a altura da arvore
//essa func procura pelo ramo com maior comprimento de nos e retorna a soma de um por um.
        int r, l;
        if(isEmptyBST(bst))
                return 0;
        r = 1 + heightBST(rightBST(bst));
        l = 1 + heightBST(leftBST(bst));
        if(r>l)
                return r;
        return l;
}
int weightBST(BST *bst){//retorna quantos nos existem na arvore
	if(isEmptyBST(bst))
		return 0;
	return 1 + weightBST(leftBST(bst)) + weightBST(rightBST(bst));//pra cada node, incrementa 1 
}
//retorna quantos nos nessa arvore nao possuem subarvores
int leavesBST(BST *bst){
	if(isEmptyBST(bst))
		return 0;
	if(isEmptyBST(leftBST(bst)) && isEmptyBST(rightBST(bst)))//se ao mesmo tempo não tiver subarvore a esquerda e a direita, retorna 1
		return 1;
	return leavesBST(leftBST(bst)) + leavesBST(rightBST(bst));//retorna chamadas recursivas até que toda a arvore tenha sido percorrida
}
//retorna quantos nós da arvore possuem ao menos uma subarvore
int fathersBST(BST *bst){
	if(isEmptyBST(bst))
		return 0;
	if(isEmptyBST(leftBST(bst)) || isEmptyBST(rightBST(bst)))//se bst tiver tiver alguma subarvore, retorna 1 + recursão
		return 1 + fathersBST(leftBST(bst)) + fathersBST(rightBST(bst));
}
//função recursiva auxiliar para encontrar a posição de new e o inserir na arvore
void auxInsertBST(BST *bst, BST *new){
        if (isEmptyBST(bst))
                return ;
        if(isEmptyBST(new) || strcmp(rootBST(bst)->value, rootBST(new)->value) == 0)//caso ja esteja na lista nao insira
                return ;
        if(strcmp(rootBST(new)->value, rootBST(bst)->value) < 0){
                if(isEmptyBST(leftBST(bst))){//encontrou insere
                        bst->left = new;
                        return ;
                }
                else
                        auxInsertBST(bst->left, new);
        }
        else{
                if(isEmptyBST(rightBST(bst))){//encontrou insere
                        bst->right = new;
                        return ;
                }
                else
                        auxInsertBST(bst->right, new);
        }
}
//insere em bst o elemento new
void insertBST(BST **bst, BST *new){
	if(isEmptyBST(*bst))//caso bst nao tenha elementos, new se tornara seu elemento
		*bst = new;
	else
		auxInsertBST(*bst, new);//do contrário, procure em bst a posição adequada a new para manter a ordem
}
//desce o avl pra esquerda de sua direita e a sua direita passa a ser avl;
void RR_RotationBST(BST **avl){
	BST *a = *avl;
	BST *b = rightBST(*avl);
	a->right = leftBST(b);
	b->left = a;
	a->balance = 0;
	b->balance = 0;
	*avl = b;
}
//desce avl para a direita da subarvore esquerda, e torna a subarvore esquerda o novo avl
void LL_RotationBST(BST **avl){
	BST *a = *avl;
	BST *b = leftBST(a);
	a->left = rightBST(b);
	b->right = a;
	a->balance = 0;
	b->balance = 0;
	*avl = b;
}
void LR_RotationBST(BST **avl){
	BST *c = *avl;
	BST *a = leftBST(c);
	BST *b = rightBST(a);
	c->left = rightBST(b);
	a->right = leftBST(b);
	b->left = a;
	b->right = c;
	switch(b->balance){
		case -1:
			a->balance = 0;
			c->balance = 1;
			break;
		case 0:
			a->balance = 0;
			c->balance = 0;
			break;
		case 1:
			a->balance = -1;
			c->balance = 0;
			break;
	}
	b->balance = 0;
	*avl = b;
}
void RL_RotationBST(BST **avl){
	BST *c = *avl;
	BST *a = rightBST(c);
	BST *b = leftBST(a);
	c->right = leftBST(b);
	a->left = rightBST(b);
	b->left = c;
	b->right = a;
	switch(b->balance){
		case -1:
			a->balance = 0;
			c->balance = 1;
			break;
		case 0:
			a->balance = 0;
			c->balance = 0;
			break;
		case 1:
			a->balance = -1;
			c->balance = 0;
			break;
	}
	b->balance = 0;
	*avl = b;
}
int auxInsertAVL(BST **avl, BST *new, int *growup){
	if(isEmptyBST(*avl)){//caso base
		*avl= new;
		*growup = 1;
		return 1;
	}
	if(strcmp(rootBST(new)->value, rootBST(*avl)->value) == 0)//repetido
		return 0;
	if(strcmp(rootBST(new)->value, rootBST(*avl)->value) < 0){//caminhar pela arvore esquerda
		if(auxInsertAVL(&(*avl)->left, new, growup)){
			if(*growup){
				switch((*avl)->balance){
					case 1:
						if(leftBST(*avl)->balance == 1)
							LL_RotationBST(avl);
						else
							LR_RotationBST(avl);
						*growup = 0;
						break;
					case 0:
						(*avl)->balance = 1;
						*growup = 1;
						break;
					case -1:
						(*avl)->balance = 0;
						*growup = 0;
						break;
				}
			}
			return 1;
		}
		else
			return 0;
	}
	if(strcmp(rootBST(new)->value, rootBST(*avl)->value) > 0){//caminhar pela arvore direita
		if(auxInsertAVL(&(*avl)->right, new, growup)){
			if(*growup){
				switch((*avl)->balance){
					case 1:
						(*avl)->balance = 0;
						*growup = 0;
						break;
					case 0:
						(*avl)->balance = -1;
						*growup = 1;
						break;
					case -1:
						if(rightBST(*avl)->balance == -1)
							RR_RotationBST(avl);
						else
							RL_RotationBST(avl);
						*growup = 0;
						break;
				}
			}
			return 1;
		}
		else
			return 0;
	}
	return 0;	
}
int insertAVL(BST **bst, BST *new){
	int growup = 0;
	return auxInsertAVL(bst, new, &growup);
}
//apenas percorre a arvore pela canhota até encontrar o fim e retorna o ultimo nó 
BST *findSmallestElementBST(BST *bst){
        BST *small = NULL;
        if(isEmptyBST(bst))
                return NULL;
        small = bst;
        while(leftBST(small)){
		small = leftBST(small);
        }
        return small;
}
//retorna o maior nó da arvore, o nó na extrema direita;
BST *findLargestElementBST(BST *bst){
        BST *large = NULL;
        if(isEmptyBST(bst))
                return NULL;
        large = bst;
        while(rightBST(large)){
		large = rightBST(large);
        }
        return large;
}
//função para buscar e deletar um elemento específico da arvore.
BST *deleteBST(BST *bst, Info *inf){
        BST *temp = NULL, *small = NULL, *smallprevs = NULL;
        if (isEmptyBST(bst))
                return bst;
        if (inf->value < rootBST(bst)->value)//procura pela arvore canhora
                bst->left = deleteBST(leftBST(bst), inf);
        else if (inf->value > rootBST(bst)->value)//procura pela arvore destra
                bst->right = deleteBST(rightBST(bst), inf);
        else{//encontrou o elemento, vamos deletar ele: 
                if(isEmptyBST(rightBST(bst))){//se não tem elemento à direita, retorne o elemento à esquerda
                        temp = leftBST(bst);
                        free(bst->inf);
                        free(bst);
                }
                else if(isEmptyBST(leftBST(bst))){//se nao tem elemento à esquerda, retorne o elemento à direita
                        temp = rightBST(bst);
                        free(bst->inf);
                        free(bst);
                }
                else{//agora caso tenha os dois lados: 
                        small = findSmallestElementBST(rightBST(bst));//encontre o menor BST possível na subarvore direita.
			//procuramos o elemento que aponta para small.como apagaremos small, esse elemento precisa apontar para NULL
			if(smallprevs = searchBST2(bst, small->inf))
				smallprevs->left = NULL;
			else//caso smallprevs == NULL, small é o elemento imediatamente a direita de bst
				bst->right = NULL;
                        temp = createNodeBST(createInfo(small->inf->value));//criamos um nó com o mesmo valor de small;
                        temp->right = rightBST(bst);//colocaremos ele no lugar de bst com essa duas linhas
                        temp->left = leftBST(bst);//essa aqui tbm
                        free(bst->inf);//agora resta apagar bst e small e junto com eles seus elementos de info
                        free(bst);
                        free(small->inf);
                        free(small);
                }
                return temp;//retornando temp, o elemento anterior vai apontar pra esse cara aqui e a arvora vai seguir firme e forte
        }
}
int getBalanceBST(BST *bst){
        if(isEmptyBST(bst))
                return 0;
        return heightBST(leftBST(bst)) - heightBST(rightBST(bst));
}
//assim como para a bst, vamos procurar o elemento e caminhar pela arvore ate encontrar ele 
int deleteAVL(BST **bst, char *value){
        int res;
        BST *temp = NULL;
        if(isEmptyBST(*bst))
            return 0;
        if(strcmp(value, rootBST(*bst)->value) < 0){//caso esteja pela arvore esquerda:
                if((res = deleteAVL(&(*bst)->left,value)) == 1){
                        if(getBalanceBST(*bst) >= 2){
                                if(heightBST((*bst)->right->left) <= heightBST((*bst)->right->right))
                                        RR_RotationBST(bst);
                                else
                                        RL_RotationBST(bst);
                        }
                }
        }
        if(strcmp(rootBST(*bst)->value, value) < 0){//caso esteja pela arvore direita:
                if((res = deleteAVL(&(*bst)->right, value)) == 1){
                        if(getBalanceBST(*bst) >= 2){
                                if(heightBST((*bst)->left->right) <= heightBST((*bst)->left->left) )
                                        LL_RotationBST(bst);
                                else
                                        LR_RotationBST(bst);
                        }
                }
        }
        if(strcmp(rootBST(*bst)->value, value) == 0){//encontrou o elemento
                if(isEmptyBST(leftBST(*bst)) || isEmptyBST(rightBST(*bst))){// nó tem uma subarvore ou nenhuma
                        temp = *bst;
                        if(leftBST(*bst) != NULL)
                                *bst = leftBST(*bst);
                        else
                                *bst = rightBST(*bst);
                free(temp);
                }
                else { // nó com 2 subarvores
                        temp = findSmallestElementBST(rightBST(*bst));
                        (*bst)->inf = rootBST(temp);
                        deleteAVL(&(*bst)->right, rootBST(*bst)->value);//remova o smallest e rebalance a arvore
                        if(getBalanceBST(*bst) >= 2){
                                        if(heightBST((*bst)->left->right) <= heightBST((*bst)->left->left))
                                                LL_RotationBST(bst);
                                        else
                                                LR_RotationBST(bst);
                        }
                }
                if (*bst != NULL)
                        (*bst)->balance = getBalanceBST(*bst);
                return 1;
        }
        (*bst)->balance = getBalanceBST(*bst);
        return res;
}
void auxPreOrderTraversalBST(BST *bst, Head **lst){
        if(isEmptyBST(bst))
                return;
        insertLastLST(lst, bst);//primeiro a gente insere, depois entra na recursão pela esquerda e direita
        auxPreOrderTraversalBST(leftBST(bst), lst);
        auxPreOrderTraversalBST(rightBST(bst), lst);
        return;
}
//retorna uma lista pré ordem
Head *preOrderTraversalBST(BST *bst){
        Head *lst = NULL;
        auxPreOrderTraversalBST(bst, &lst);
        return lst;
}
void auxInOrderTraversalBST(BST *bst, Head **lst){
        if(isEmptyBST(bst))
                return;
        auxInOrderTraversalBST(leftBST(bst), lst);
        insertLastLST(lst, bst);//primeiro entra na recursão pela esquerda, depois insere e entra na recursão novamente pela esquerda
        auxInOrderTraversalBST(rightBST(bst), lst);
}
//retorna uma lista em ordem
Head *inOrderTraversalBST(BST *bst){
        Head *lst = NULL;
        auxInOrderTraversalBST(bst, &lst);
        return lst;
}
void auxPostOrderTraversalBST(BST *bst, Head **lst){
        if(isEmptyBST(bst))
                return;
        auxPostOrderTraversalBST(leftBST(bst), lst);
        auxPostOrderTraversalBST(rightBST(bst), lst);
        insertLastLST(lst, bst);//primeiro entra nas recursões pela esquerda e direita e depois insere
}
//retorna uma lista post ordem
Head *postOrderTraversalBST(BST *bst){
        Head *lst = NULL;
        auxPostOrderTraversalBST(bst, &lst);
        return lst;
}
//retorna uma lista ordenada por level
Head *levelOrderTraversalBST(BST *bst){
        BSTNode *node = NULL;//isso é um Node que sua informação é do tipo BST* inf;
        BSTHead *queue = NULL;//essa é uma cabeça pra esse BSTNode, implementei com BSTNode *first, *last;
        Head *lst = NULL;
        insertLastBSTLST(&queue, bst);//insere a raiz no fim da fila de BSTNodes (caso queue == NULL, aloca espaço para queue)
        while(!isEmptyBSTLST(queue)){
                node = getFirstBSTLST(queue);//remove da queue e poe em node
                insertLastLST(&lst, node->inf);//copia a informação da bst armazenada em node e cria um elemento em lst com mesmo value, mas não msm endereço.
                insertLastBSTLST(&queue, leftBST(node->inf));//inserimos as subarvores canhota e destra na queue;
                insertLastBSTLST(&queue, rightBST(node->inf));//se não tiver subarvores, vai sair do loop
        }
        if(queue)
                free(queue);//libera o espaço da cabeça
        return lst;
}
Head *takeWhileLST(Head *lst, Info *inf){
        Node *ptr = NULL;
        Head *newlst = NULL;
        BST *temp = NULL;
        for(ptr = lst->first; ptr && ptr->inf->value != inf->value; ptr = ptr->next){//pra cara informação antes de inf(root), insira ela na nova lista
                temp = createNodeBST(createInfo(ptr->inf->value));//criamos um BST temporário com uma COPIA da informação(int) contida em ptr
		//minha implementação de insertLastLST recebe um *BST, então criamos temp como intermediário e logo em seguida nos livraremos dele.
		//insertlastLST não usa o nó de informação de temp, mas cria uma cópia de seu valor para outro *Info.
                insertLastLST(&newlst, temp);//caso newlst == NULL, a função insertLastLST vai alocar espaço para ele.
		free(temp->inf);//como não foi utilizado o endereço de temp->inf em nenhum outro lugar, podemos dar free sem medo
                free(temp);//bye bye
        }
        return newlst;
}
Head *dropWhileLST(Head *lst, Info *inf){
        Node *ptr = NULL;
        Head *newlst = NULL;
        BST *temp = NULL;
        for(ptr = lst->first; ptr && ptr->inf->value != inf->value; ptr = ptr->next);//a diferença aqui é que começaremos a partir de inf(root).
        if(ptr)//encontrado inf(root), caso ele seja diferente de NULL faremos
                for(ptr = ptr->next;ptr;ptr = ptr->next){//para cada Node depois de inf(root)
			temp = createNodeBST(createInfo(ptr->inf->value));//faremos o mesmo processo descrito em takeWhileLST().
                        insertLastLST(&newlst, temp);
			free(temp->inf);
                        free(temp);
                }
        return newlst;
}
/*
	o primeiro elemento de preOrder sempre será a raiz, então procuraremos os elementos menores que ele e os maiores que ele para dividir em suas subarvores
*/
BST *treeFromInOrderPreOrderBST(Head *preOrder, Head **inOrder){
//essa função recebe um ponteiro para ponteiro para que evite "double free" quando essa função é utilizada na main.
        BST *bst = NULL;
        Head *esq = NULL, *dir = NULL;
        Info *root = NULL;
	Node *temp = NULL;
        if (isEmptyLST(preOrder) || isEmptyLST(*inOrder))
                return bst;
	temp = getFirstLST(preOrder);
        root = temp->inf;//removemos de preOrder o primeiro elemento e copiamos seu valor para outro ponteiro p/ Info
	free(temp);
        if(!(bst = createNodeBST(root)))//o nó raiz bst é criado com a informação root;
                return bst;
        esq = takeWhileLST(*inOrder, root);//essa função vai gerar uma lista em ordem que vai até root mas sem incluir root.
        dir = dropWhileLST(*inOrder, root);//essa função vai gerar uma lista em ordem que vai de root até o fim de inOrder mas sem o root tbm.
        freeLST(*inOrder);
	inOrder = NULL;
        bst->left = treeFromInOrderPreOrderBST(preOrder, &esq);//subarvore esqueda de bst(root)
        bst->right = treeFromInOrderPreOrderBST(preOrder, &dir);//subarvore direita de bst(root)
        return bst;

}
//essa função cria uma lista seguindo a lógica de que a esquerda é menor que a direita e caso essa lista esteja em ordem crescente, retorna true
int isInOrderBST(BST *bst){
	if(isEmptyBST(bst)) 
		return 1;
	Head *inlst = inOrderTraversalBST(bst);//criando a lista
	if(isEmptyLST(inlst))
		return 1;
	int teste = 1;// se teste continuar 1 até o fim, então essa arvore esta em ordem crescente
	Node *ptr = inlst->first;
	Node *pptr = ptr;
	for(ptr = ptr->next; ptr; ptr = ptr->next){
		teste = pptr->inf->value <= ptr->inf->value ? teste : 0;//se em algum lugar, pptr > ptr, então teste passa a ser 0(false).
		pptr = ptr;
	}
	return teste;
}
//função para inverter todos os nós da arvore
BST *mirrorBST(BST *bst){
	BST *temp = NULL;
	if(isEmptyBST(bst))
		return NULL;
	mirrorBST(leftBST(bst));//caminhamos até o fundo da arvore com essas duas chamadas
	mirrorBST(rightBST(bst));//uma vez no fundo, voltamos trocando os nós uns com os outros até o topo novamente
	temp = bst->left;
	bst->left = bst->right;
	bst->right = temp;
	return bst;
}
