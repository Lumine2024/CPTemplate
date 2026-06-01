#pragma once
#include "common.h"

struct CdqBase {
	int n;
	void run(int _n) {
		cdq(0, _n);
	}
	void run() {
		cdq(0, n);
	}
	virtual void solve_cross(int l, int m, int r) = 0;
	virtual void merge(int l, int m, int r) = 0;

private:
	void cdq(int l, int r) {
		if(r <= l + 1) return;
		int mid = (l + r) / 2;
		cdq(l, mid);
		solve_cross(l, mid, r);
		cdq(mid, r);
		merge(l, mid, r);
	}

protected:
	CdqBase() {}
};
