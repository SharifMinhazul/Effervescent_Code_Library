const int MXCHR = 26;
/*
take an object of suffixAutomata
call extend(c) for each character c in string
call Process() to initiate the important values
*/
struct suffixAutomata {
    /**
     * len -> largest string length of the corresponding endpos-equivalent class
     * link -> longest suffix that is another endpos-equivalent class
     * firstpos -> end position of the first occurrence of the largest string of
     *that node
     **/
    struct state {
        int link, len;
        int next[MXCHR];
        state() {}
        state(int l) {
            len = l;
            link = -1;
            for (int i = 0; i < MXCHR; i++) next[i] = -1;
        }
    };
    vector<state> node;
    int sz, last;
    vector<int> cnt, distinct, firstPos, occur, SA;
    vector<vector<int>> adj;  // suffix links tree
    // cnt and SA for counting sort the nodes.
    int L;

    suffixAutomata() {
        node.push_back(state(0));
        firstPos.push_back(-1);
        occur.push_back(0);
        last = 0;
        sz = 0;
        L = 0;
    }
    int getID(char c) {
        return c - 'a';  // change according to problem
    }
    void extend(char c) {
        int idx = ++sz, p = last, id = getID(c);
        L++;
        node.push_back(state(node[last].len + 1));
        firstPos.push_back(node[idx].len - 1);
        occur.push_back(1);

        while (p != -1 && node[p].next[id] == -1) {
            node[p].next[id] = idx;
            p = node[p].link;
        }
        if (p == -1)
            node[idx].link = 0;
        else {
            int q = node[p].next[id];
            if (node[p].len + 1 == node[q].len)
                node[idx].link = q;
            else {
                int clone = ++sz;
                state x = node[q];
                x.len = node[p].len + 1;
                node.push_back(x);
                firstPos.push_back(firstPos[q]);
                occur.push_back(0);
                while (p != -1 && node[p].next[id] == q) {
                    node[p].next[id] = clone;
                    p = node[p].link;
                }
                node[idx].link = node[q].link = clone;
            }
        }
        last = idx;
    }
    void Process() {
        cnt.resize(sz + 1);
        distinct.resize(sz + 1);
        SA.resize(sz + 1);
        adj.resize(sz + 1);
        for (int i = 0; i <= sz; i++) cnt[node[i].len]++;
        for (int i = 1; i <= L; i++) cnt[i] += cnt[i - 1];
        for (int i = 0; i <= sz; i++) SA[--cnt[node[i].len]] = i;
        for (int i = sz; i > 0; i--) {
            int idx = SA[i];
            occur[node[idx].link] += occur[idx];
            adj[node[idx].link].push_back(idx);
            distinct[idx] = 1;
            for (int j = 0; j < MXCHR; j++) {
                if (node[idx].next[j] != -1)
                    distinct[idx] += distinct[node[idx].next[j]];
            }
        }  // counts distinct substrings and occurance of each state
        for (int i = 0; i < MXCHR; i++)
            if (node[0].next[i] != -1) distinct[0] += distinct[node[0].next[i]];
    }
    pair<int, int> lcs(string &str) {
        int mxlen = 0, bestpos = -1, pos = 0, len = 0;
        int u = 0;  // LCS of two string. returns start position and length
        for (char c : str) {
            int v = getID(c);
            while (u && node[u].next[v] == -1) {
                u = node[u].link;
                len = node[u].len;
            }
            if (node[u].next[v] != -1) {
                len++;
                u = node[u].next[v];
            }
            if (len > mxlen) {
                mxlen = len;
                bestpos = pos;
            }
            pos++;
        }
        return {bestpos - mxlen + 1, mxlen};
    }
    state &operator[](int index) { return node[index]; }
};

