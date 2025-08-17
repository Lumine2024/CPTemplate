#pragma once
#include <bits/stdc++.h>
#include "Constants.hpp"
using namespace std;
using ll = long long;
using ull = unsigned long long;

struct EK {
    struct Edge {
        int u, v, ne;
        ll flow, weight;
    };
    vector<Edge> edges;
    vector<int> h, pre;
    vector<ll> mf, d;
    vector<bool> vis;
    int n;

    EK(int _n) : n(_n), h(_n, -1), d(_n, inf), mf(_n, 0), pre(_n, 0), vis(_n, 0) {}

    void add(int u, int v, ll flow, ll weight) {
        edges.push_back({u, v, h[u], flow, weight});
        h[u] = edges.size() - 1;
        edges.push_back({v, u, h[v], 0, -weight});
        h[v] = edges.size() - 1;
    }

    pair<ll, ll> solve() {
        ll cost = 0, flow = 0;
        while(_spfa()) {
            for(int v = n - 1; v > 0;) {
                int i = pre[v];
                edges[i].flow -= mf[n - 1];
                edges[i ^ 1].flow += mf[n - 1];
                v = edges[i].u;
            }
            flow += mf[n - 1];
            cost += mf[n - 1] * d[n - 1];
        }
        return { cost, flow };
    }

private:
    bool _spfa() {
        for(int i = 0; i < n; ++i) {
            mf[i] = 0;
            d[i] = inf;
            vis[i] = false;
        }
        queue<int> q;
        q.push(0);
        d[0] = 0;
        mf[0] = inf;
        vis[0] = true;
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            vis[u] = false;
            for(int i = h[u]; i != -1; i = edges[i].ne) {
                int v = edges[i].v;
                ll f = edges[i].flow, w = edges[i].weight;
                if(f > 0 && d[v] > d[u] + w) {
                    d[v] = d[u] + w;
                    pre[v] = i;
                    mf[v] = min(mf[u], f);
                    if(!vis[v]) {
                        q.push(v);
                        vis[v] = true;
                    }
                }
            }
        }
        return mf[n - 1] > 0;
    }
};