struct ST_Lazy {
  int N;
  struct Node {
    int64_t sum;
    int64_t max_val;
    int64_t min_val;
  };
  vector<Node> t;
  vector<int64_t> lazy_add, pending_set;
  vector<char> has_set;
  const int64_t NEG_INF = LLONG_MIN / 4;
  const int64_t POS_INF = LLONG_MAX / 4;

  ST_Lazy(int _n = 0) {
    init(_n);
  }

  void init(int _n) {
    N = _n;
    t.resize(N << 2, {0, 0, 0}); // if there are negative values, change {0, 0, 0} to {0, NEG_INF, POS_INF}
    lazy_add.resize(N << 2, 0);
    pending_set.resize(N << 2, 0);
    has_set.resize(N << 2, false);
  }

  void build(int n, int s, int e, const vector<int64_t> &a) {
    if (s == e) {
      t[n] = {a[s], a[s], a[s]};
      return;
    }
    int m = (s + e) >> 1;
    build(n << 1, s, m, a);
    build(n << 1 | 1, m + 1, e, a);
    pull_up(n);
  }

  void build(const vector<int64_t> &a) {
    init((int)a.size());
    if (N) build(1, 0, N - 1, a);
  }

  inline void apply_set(int n, int s, int e, int64_t val) {
    has_set[n] = true;
    pending_set[n] = val;
    lazy_add[n] = 0;
    int64_t len = e - s + 1;
    t[n].sum = val * len;
    t[n].max_val = val;
    t[n].min_val = val;
  }

  inline void apply_add(int n, int s, int e, int64_t val) {
    if (has_set[n]) pending_set[n] += val;
    else lazy_add[n] += val;
    int64_t len = e - s + 1;
    t[n].sum += val * len;
    t[n].max_val += val;
    t[n].min_val += val;
  }

  inline void push_down(int n, int s, int e) {
    if (s == e) return;
    int m = (s + e) >> 1;
    if (has_set[n]) {
      apply_set(n << 1, s, m, pending_set[n]);
      apply_set(n << 1 | 1, m + 1, e, pending_set[n]);
      has_set[n] = false;
      pending_set[n] = 0;
    }
    if (lazy_add[n]) {
      apply_add(n << 1, s, m, lazy_add[n]);
      apply_add(n << 1 | 1, m + 1, e, lazy_add[n]);
      lazy_add[n] = 0;
    }
  }

  inline void pull_up(int n) {
    t[n].sum = t[n << 1].sum + t[n << 1 | 1].sum;
    t[n].max_val = max(t[n << 1].max_val, t[n << 1 | 1].max_val);
    t[n].min_val = min(t[n << 1].min_val, t[n << 1 | 1].min_val);
  }

  void range_set(int n, int s, int e, int l, int r, int64_t val) {
    if (r < s || e < l || l > r) return;
    if (l <= s && e <= r) {
      apply_set(n, s, e, val);
      return;
    }
    push_down(n, s, e);
    int m = (s + e) >> 1;
    range_set(n << 1, s, m, l, r, val);
    range_set(n << 1 | 1, m + 1, e, l, r, val);
    pull_up(n);
  }
  void range_set(int l, int r, int64_t val) {
    if (l > r) return;
    if (N) range_set(1, 0, N - 1, l, r, val);
  }

  void range_add(int n, int s, int e, int l, int r, int64_t val) {
    if (r < s || e < l || l > r) return;
    if (l <= s && e <= r) {
      apply_add(n, s, e, val);
      return;
    }
    push_down(n, s, e);
    int m = (s + e) >> 1;
    range_add(n << 1, s, m, l, r, val);
    range_add(n << 1 | 1, m + 1, e, l, r, val);
    pull_up(n);
  }
  void range_add(int l, int r, int64_t val) {
    if (l > r) return;
    if (N) range_add(1, 0, N - 1, l, r, val);
  }

  int64_t range_sum(int n, int s, int e, int l, int r) {
    if (r < s || e < l || l > r) return 0;
    if (l <= s && e <= r) return t[n].sum;
    push_down(n, s, e);
    int m = (s + e) >> 1;
    return range_sum(n << 1, s, m, l, r) + range_sum(n << 1 | 1, m + 1, e, l, r);
  }
  int64_t range_sum(int l, int r) {
    if (l > r) return 0;
    if (N) return range_sum(1, 0, N - 1, l, r);
    return 0;
  }

  int64_t range_max(int n, int s, int e, int l, int r) {
    if (r < s || e < l || l > r) return NEG_INF;
    if (l <= s && e <= r) return t[n].max_val;
    push_down(n, s, e);
    int m = (s + e) >> 1;
    return max(range_max(n << 1, s, m, l, r), range_max(n << 1 | 1, m + 1, e, l, r));
  }
  int64_t range_max(int l, int r) {
    if (l > r) return NEG_INF;
    if (N) return range_max(1, 0, N - 1, l, r);
    return NEG_INF;
  }

  int64_t range_min(int n, int s, int e, int l, int r) {
    if (r < s || e < l || l > r) return POS_INF;
    if (l <= s && e <= r) return t[n].min_val;
    push_down(n, s, e);
    int m = (s + e) >> 1;
    return min(range_min(n << 1, s, m, l, r), range_min(n << 1 | 1, m + 1, e, l, r));
  }
  int64_t range_min(int l, int r) {
    if (l > r) return POS_INF;
    if (N) return range_min(1, 0, N - 1, l, r);
    return POS_INF;
  }

  Node get(int n, int s, int e, int idx) {
    if (s == e) return t[n];
    push_down(n, s, e);
    int m = (s + e) >> 1;
    if (idx <= m) return get(n << 1, s, m, idx);
    else return get(n << 1 | 1, m + 1, e, idx);
  }
  Node get(int idx) {
    if (N) return get(1, 0, N - 1, idx);
    return {0, NEG_INF, POS_INF};
  }

  int64_t point_get(int n, int s, int e, int idx) {
    if (s == e) return t[n].sum;
    push_down(n, s, e);
    int m = (s + e) >> 1;
    if (idx <= m) return point_get(n << 1, s, m, idx);
    else return point_get(n << 1 | 1, m + 1, e, idx);
  }
  int64_t point_get(int idx) {
    if (N) return point_get(1, 0, N - 1, idx);
    return 0;
  }

  // find first index in [l, r] with value >= val, or -1 if none
  int find_first_at_least(int n, int s, int e, int l, int r, int64_t val) {
    if (r < s || e < l || l > r) return -1;
    if (t[n].max_val < val) return -1;
    if (s == e) return s;
    push_down(n, s, e);
    int m = (s + e) >> 1;
    int res = find_first_at_least(n << 1, s, m, l, r, val);
    if (res != -1) return res;
    return find_first_at_least(n << 1 | 1, m + 1, e, l, r, val);
  }
  int find_first_at_least(int l, int r, int64_t val) {
    if (l > r) return -1;
    if (N) return find_first_at_least(1, 0, N - 1, l, r, val);
    return -1;
  }

  // find last index in [l, r] with value >= val, or -1 if none
  int find_last_at_least(int n, int s, int e, int l, int r, int64_t val) {
    if (r < s || e < l || l > r) return -1;
    if (t[n].max_val < val) return -1;
    if (s == e) return s;
    push_down(n, s, e);
    int m = (s + e) >> 1;
    int res = find_last_at_least(n << 1 | 1, m + 1, e, l, r, val);
    if (res != -1) return res;
    return find_last_at_least(n << 1, s, m, l, r, val);
  }
  int find_last_at_least(int l, int r, int64_t val) {
    if (l > r) return -1;
    if (N) return find_last_at_least(1, 0, N - 1, l, r, val);
    return -1;
  }

  int find_first_at_most(int n, int s, int e, int l, int r, int64_t val) {
    if (r < s || e < l || l > r) return -1;
    if (t[n].min_val > val) return -1;
    if (s == e) return s;
    push_down(n, s, e);
    int m = (s + e) >> 1;
    int res = find_first_at_most(n << 1, s, m, l, r, val);
    if (res != -1) return res;
    return find_first_at_most(n << 1 | 1, m + 1, e, l, r, val);
  }
  int find_first_at_most(int l, int r, int64_t val) {
    if (l > r) return -1;
    if (N) return find_first_at_most(1, 0, N - 1, l, r, val);
    return -1;
  }
  int find_last_at_most(int n, int s, int e, int l, int r, int64_t val) {
    if (r < s || e < l || l > r) return -1;
    if (t[n].min_val > val) return -1;
    if (s == e) return s;
    push_down(n, s, e);
    int m = (s + e) >> 1;
    int res = find_last_at_most(n << 1 | 1, m + 1, e, l, r, val);
    if (res != -1) return res;
    return find_last_at_most(n << 1, s, m, l, r, val);
  }
  int find_last_at_most(int l, int r, int64_t val) {
    if (l > r) return -1;
    if (N) return find_last_at_most(1, 0, N - 1, l, r, val);
    return -1;
  }

  // find smallest index i such that prefix sum(0..i) >= target. works only with non-negative values. -1 if none
  int find_by_prefixSum(int64_t target) {
    if (N == 0 || t[1].sum < target) return -1;
    int n = 1, s = 0, e = N - 1;
    while (s != e) {
      push_down(n, s, e);
      int m = (s + e) >> 1;
      if (t[n << 1].sum >= target) {
        n = n << 1;
        e = m;
      } else {
        target -= t[n << 1].sum;
        n = n << 1 | 1;
        s = m + 1;
      }
    }
    return s;
  }

  // find any index i in [l, r] such that a[i] = max(a[l..r]), or -1 if none
  int find_index_of_max(int n, int s, int e, int l, int r, int64_t val) {
    if (r < s || e < l || l > r) return -1;
    if (t[n].max_val < val) return -1;
    if (s == e) return s;
    push_down(n, s, e);
    int m = (s + e) >> 1;
    int res = find_index_of_max(n << 1, s, m, l, r, val);
    if (res != -1) return res;
    return find_index_of_max(n << 1 | 1, m + 1, e, l, r, val);
  }
  int find_index_of_max(int l, int r) {
    if (N == 0) return -1;
    int64_t max_in_range = range_max(l, r);
    return find_index_of_max(1, 0, N - 1, l, r, max_in_range);
  }

  // find any index i in [l, r] such that a[i] = min(a[l..r]), or -1 if none
  int find_index_of_min(int n, int s, int e, int l, int r, int64_t val) {
    if (r < s || e < l || l > r) return -1;
    if (t[n].min_val > val) return -1;
    if (s == e) return s;
    push_down(n, s, e);
    int m = (s + e) >> 1;
    int res = find_index_of_min(n << 1, s, m, l, r, val);
    if (res != -1) return res;
    return find_index_of_min(n << 1 | 1, m + 1, e, l, r, val);
  }
  int find_index_of_min(int l, int r) {
    if (l > r) return -1;
    if (N == 0) return -1;
    int64_t min_in_range = range_min(l, r);
    return find_index_of_min(1, 0, N - 1, l, r, min_in_range);
  }

  // returns largest r >= start such that sum(start..r) <= maxSum. -1 if none.
  // This uses prefix-search: find smallest idx with prefix >= prefixBefore + maxSum.
  int max_right_by_sum(int start, int64_t maxSum) {
    if (!N) return start - 1;
    if (start < 0) start = 0;
    if (start >= N) return N - 1;
    int64_t prefixBefore = (start == 0 ? 0 : range_sum(0, start - 1));
    int64_t target = prefixBefore + maxSum;
    int idx = find_by_prefixSum(target);
    if (idx == -1) {
      int r = N - 1;
      if (r < start) return start - 1;
      return r;
    }
    int64_t pref_at_idx = range_sum(0, idx);
    int r;
    if (pref_at_idx == target) r = idx;
    else r = idx - 1;
    if (r < start) return start - 1;
    if (r >= N) return N - 1;
    return r;
  }

  void print() {
    for (int i = 0; i < N; i++) {
      cout << point_get(i) << " \n"[i == N - 1];
    }
  }
};
