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
		update(x, 1);
	}
	void erase(int x) {
		update(x, -1);
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
		return qrange_cnt(0, x);
	}
	int qvr(int k) const {
		return [&](auto &&qry) {
			return qry(qry, k, 0, 0, n);
		}([&](auto &&qry, int k, int rt, int rl, int rr) -> int {
			if(rr - rl == 1) return rl;
			int m = (rl + rr) >> 1, ls = rt * 2 + 1, rs = rt * 2 + 2;
			if(k < s[ls]) return qry(qry, k, ls, rl, m);
			return qry(qry, k - s[ls], rs, m, rr);
		});
	}
	int size() const {
		return s[0];
	}
	int qcnt(int x) const {
		return qrange_cnt(x, x + 1);
	}
	int qrange_cnt(int l, int r) const {
		return [&](auto &&qry) {
			return qry(qry, l, r, 0, 0, n);
		}([&](auto &&qry, int ql, int qr, int rt, int rl, int rr) -> int {
			if(ql <= rl && qr >= rr) return s[rt];
			int m = (rl + rr) >> 1, ls = rt * 2 + 1, rs = rt * 2 + 2;
			int ans = 0;
			if(ql < m) ans += qry(qry, ql, qr, ls, rl, m);
			if(qr > m) ans += qry(qry, ql, qr, rs, m, rr);
			return ans;
		});
	}

private:
	vector<int> s;
	int n;
	void update(int x, int dv) {
		[&](auto &&upd) {
			upd(upd, x, dv, 0, 0, n);
		}([&](auto &&upd, int x, int dv, int rt, int rl, int rr) -> void {
			if(rr - rl == 1) {
				s[rt] += dv;
				return;
			}
			int m = (rl + rr) >> 1, ls = rt * 2 + 1, rs = rt * 2 + 2;
			if(x < m) upd(upd, x, dv, ls, rl, m);
			else upd(upd, x, dv, rs, m, rr);
			s[rt] = s[ls] + s[rs];
		});
	}
};
