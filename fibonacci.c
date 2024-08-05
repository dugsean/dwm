void
fibonacci(Monitor *mon, int s) {
	unsigned int i, n, nx, ny, nw, nh, gappx, nwg, nhg;
	Client *c;

	for(n = 0, c = nexttiled(mon->clients); c; c = nexttiled(c->next), n++);
	if(n == 0)
		return;
	
  gappx = mon->gappx;
	nx = mon->wx+gappx/2;
	ny = gappx/2;
	nw = mon->ww-gappx;
	nh = mon->wh-gappx;
	
	for(i = 0, c = nexttiled(mon->clients); c; c = nexttiled(c->next)) {
		if((i % 2 && nh / 2 > 2 * c->bw)
		   || (!(i % 2) && nw / 2 > 2 * c->bw)) {
			if(i < n - 1) {
				if(i % 2)
					nh /= 2;
				else
					nw /= 2;
				if((i % 4) == 2 && !s)
					nx += nw;
				else if((i % 4) == 3 && !s)
					ny += nh;
			}
			if((i % 4) == 0) {
				if(s)
					ny += nh;
				else
					ny -= nh;
			}
			else if((i % 4) == 1)
				nx += nw;
			else if((i % 4) == 2)
				ny += nh;
			else if((i % 4) == 3) {
				if(s)
					nx += nw;
				else
					nx -= nw;
			}
			if(i == 0)
			{
				if(n != 1)
					nw = (mon->ww - gappx) * mon->mfact;
				ny = mon->wy + gappx/2;
			}
			else if(i == 1)
				nw = mon->ww - nw - gappx;
			i++;
		}
    nwg = nw - gappx > 0 ? nw - gappx : 0;
    nhg = nh - gappx > 0 ? nh - gappx : 0;
		resize(c, nx + gappx/2, ny + gappx/2, nwg - 2 * c->bw, nhg - 2 * c->bw, False);
	}
}

void
dwindle(Monitor *mon) {
	fibonacci(mon, 1);
}

void
spiral(Monitor *mon) {
	fibonacci(mon, 0);
}
