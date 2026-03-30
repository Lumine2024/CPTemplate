#pragma once
#include "common.h"

template<class Info> struct CdqBase {
	vector<Info> infos;
	explicit CdqBase(const vector<Info> &v) : infos(v) {}
	void run() {
		cdq(0, static_cast<int>(infos.size()));
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
