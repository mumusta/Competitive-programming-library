

// [Segment Tree With Lazy Propagation]

int seq[10] = { 0 }, st[10*4+5] = { 0 }, lazy[10*4+5] = { 0 };
void pre(int id = 1, int l = 0, int r = 9){
    if (l == r){
        st[id] = seq[l]; return;
    } int mid = ((l+r) >> 1);
    pre(id*2,l,mid); pre(id*2+1,mid+1,r); // process all under me
    st[id] = st[id*2] + st[id*2+1];
// now the two childs are known then the current equal to summation of them
}

void lazy_update(int id, int l, int r, int v){
    st[id] += (r-l+1) * v;  // update the current range
    lazy[id] += v;
// add in lazy[id] the new value that have to be added in the tree
// under the current node in the future if needed
}

void shift_down(int id, int l, int r){
    int mid = ((l+r) >> 1);
    // update the two childs in lazy manner
    lazy_update(id*2,l,mid,lazy[id]);
    lazy_update(id*2+1,mid+1,r,lazy[id]);
    lazy[id] = 0;// then we have nothing to update of the current node childs
}

void update(int x, int y, int v, int id = 1, int l = 0, int r = 9){
    if (x > r || y < l) return;
    // if current range(l, r) is out of range of x and y

    if (x <= l && r <= y) { lazy_update(id,l,r,v); return; }
    // if current range(l, r) is part of x and y update it

    // actually because we are here then there is an intersection

    if (l != r){ // if it is not leaf node
        shift_down(id,l,r);
// update the childs because we need them updated as we go down now
    } int mid = ((l+r) >> 1);
    update(x,y,v,id*2,l,mid); update(x,y,v,id*2+1,mid+1,r);
    st[id] = st[id*2] + st[id*2+1];
}

int sum(int x, int y, int id = 1, int l = 0, int r = 9){
    if (x > r || y < l) return 0;
    if (x <= l && r <= y) return st[id];
    if (l != r) shift_down(id,l,r);
    int mid = ((l+r) >> 1);
    return sum(x,y,id*2,l,mid) + sum(x,y,id*2+1,mid+1,r);
}


