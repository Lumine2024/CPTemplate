#pragma once
#include "common.h"

struct ValSeg {
	ValSeg(int ma) : s((ma + 1) * 4), n(ma + 1) {}
	ValSeg() : n(0) {}
	void assign(int ma) {
		s.assign((ma + 1) * 4, 0);
		n = ma + 1;
	}
	void insert(int x) {
		_update(x, 1, 0, 0, n);
	}
	void erase(int x) {
		_update(x, -1, 0, 0, n);
	}
	int qpre(int x) const {
		int rk = qrv(x);
		return qvr(rk - 1);
	}
	int qsuc(int x) const {
		int rk = qrv(x + 1);
		return qvr(rk);
	}
	int qrv(int x) const {
		return _query(0, x, 0, 0, n);
	}
	int qvr(int k) const {
		return _qvr(k, 0, 0, n);
	}
	int size() const {
		return s[0];
	}
	int qcnt(int x) const {
		return _query(x, x + 1, 0, 0, n);
	}
	int qrange_cnt(int l, int r) const {
		return _query(l, r, 0, 0, n);
	}

private:
	vector<int> s;
	int n;
	void _update(int x, int dv, int rt, int rl, int rr) {
		if(rr - rl == 1) {
			s[rt] += dv;
			return;
		}
		int m = (rl + rr) >> 1, ls = rt * 2 + 1, rs = rt * 2 + 2;
		if(x < m) {
			_update(x, dv, ls, rl, m);
		} else {
			_update(x, dv, rs, m, rr);
		}
		s[rt] = s[ls] + s[rs];
	}
	ll _query(int ql, int qr, int rt, int rl, int rr) const {
		if(ql <= rl && qr >= rr) return s[rt];
		int m = (rl + rr) >> 1, ls = rt * 2 + 1, rs = rt * 2 + 2;
		ll ans = 0;
		if(ql < m) {
			ans += _query(ql, qr, ls, rl, m);
		}
		if(qr > m) {
			ans += _query(ql, qr, rs, m, rr);
		}
		return ans;
	}
	int _qvr(int k, int rt, int rl, int rr) const {
		if(rr - rl == 1) return rl;
		int m = (rl + rr) >> 1, ls = rt * 2 + 1, rs = rt * 2 + 2;
		if(k < s[ls]) {
			return _qvr(k, ls, rl, m);
		} else {
			return _qvr(k - s[ls], rs, m, rr);
		}
	}
};
