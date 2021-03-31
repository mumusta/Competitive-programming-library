ll seq[1024][1024], st[4*1024][4*1024], N, M;

void pre_y (int vx, int lx, int rx, int vy, int ly, int ry) {
	if (ly == ry)
		if (lx == rx) st[vx][vy] = seq[lx][ly];
		else st[vx][vy] = st[vx << 1][vy] + st[(vx << 1) + 1][vy];
	else {
		int my = ((ly + ry) >> 1); pre_y (vx, lx, rx, vy << 1, ly, my);
		pre_y (vx, lx, rx, (vy << 1) + 1, my + 1, ry);
		st[vx][vy] = st[vx][vy << 1] + st[vx][(vy << 1) + 1];
	}
}

void pre_x (int vx = 1, int lx = 0, int rx = N - 1) {
	if (lx != rx) {
		int mx = ((lx + rx) >> 1); pre_x (vx << 1, lx, mx);
		pre_x ((vx << 1) + 1, mx + 1, rx);
	} pre_y (vx, lx, rx, 1, 0, M - 1);
}

int Q_y (int vx, int vy, int tly, int try_, int ly, int ry) {
	if (ly > ry) return 0; int tmy = ((tly + try_) >> 1);
	if (ly == tly && try_ == ry) return st[vx][vy];
	return Q_y (vx, vy << 1, tly, tmy, ly, min(ry,tmy))
    + Q_y (vx, (vy << 1) + 1, tmy + 1, try_, max(ly,tmy + 1), ry);
}

int Q_x (int lx, int rx, int ly, int ry, int vx = 1, int tlx = 0, int trx = N-1) {
	if (lx > rx) return 0; int tmx = ((tlx + trx) >> 1);
	if (lx == tlx && trx == rx) return Q_y (vx, 1, 0, M - 1, ly, ry);
	return Q_x (lx, min(rx,tmx), ly, ry, vx << 1, tlx, tmx)
		+ Q_x (max(lx,tmx + 1), rx, ly, ry, (vx << 1) + 1, tmx + 1, trx);
}

void up_y (int vx, int lx, int rx, int vy, int ly, int ry, int x, int y, int va) {
	if (ly == ry) {
		if (lx == rx) st[vx][vy] = va;
		else st[vx][vy] = st[vx << 1][vy] + st[(vx << 1) + 1][vy];
	}
	else {
		int my = ((ly + ry) >> 1);
		if (y <= my) up_y (vx, lx, rx, vy << 1, ly, my, x, y, va);
		else up_y (vx, lx, rx, (vy << 1) + 1, my + 1, ry, x, y, va);
		st[vx][vy] = st[vx][vy << 1] + st[vx][(vy << 1) + 1];
	}
}

void up_x (int x, int y, int va, int vx = 1, int lx = 0, int rx = N - 1) {
	if (lx != rx) { int mx = ((lx + rx) >> 1);
		if (x <= mx) up_x (x, y, va, vx << 1, lx, mx);
		else up_x (x, y, va, (vx << 1) + 1, mx + 1, rx);
	} up_y (vx, lx, rx, 1, 0, M - 1, x, y, va);
}