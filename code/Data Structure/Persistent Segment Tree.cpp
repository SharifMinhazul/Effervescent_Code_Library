const int mxn = 4e5+5;
int root[mxn], leftchild[25*mxn], rightchild[25*mxn], value[25*mxn], a[mxn];
int now = 0, n, sz = 1;
int l, r;

int build(int L, int R){
	int node = ++now;
	if(L == R){
		//initialize
		//value[node] = a[L];
		return node;
	}
	int mid = (L+R)>>1;
	leftchild[node] = build(L, mid);
	rightchild[node] = build(mid+1, R);
	//combine
	//value[node] = value[leftchild[node]] + value[rightchild[node]];
	return node;
}

int update(int nownode, int L, int R, int ind, int val){
	int node = ++now;
	if(L == R){
		//value[node] = value[nownode]+val;
		//update value[node]
		return node;
	}
	int mid = (L+R)>>1;
	leftchild[node] = leftchild[nownode];
	rightchild[node] = rightchild[nownode];
	if(mid >= ind){//change condition as required
		leftchild[node] = update(leftchild[nownode], L, mid, ind, val);
	}
	else{
		rightchild[node] = update(rightchild[nownode], mid+1, R, ind, val);
	}
	//value[node] = value[leftchild[node]] + value[rightchild[node]];
	//combine value[node]
	return node;
}


int query(int nownode, int L, int R){
	if(l > R || r < L) return 0;
	
	if(L>=l && r >= R){
		return value[nownode];
	}
	int mid = (L+R)>>1;
	//change as required
	return query(leftchild[nownode], L, mid) + query(rightchild[nownode], mid+1, R);
}

void persistant(){
	root[0] = build(1, n);
	while(m--){
		if(ck == 2){
			cout << query(root[idx], 1, n) << "\n";
		}
		else{
		    	root[sz++] = update(root[idx], 1, n, ind, val);
		}
	}
}
