int64_t inv_cnt(vector<int> a) {
  int n = a.size();
  vector<int> tmp(n);
  function<int64_t(int,int)> solve = [&](int l, int r) -> int64_t {
    if (r - l <= 1) return 0;
    int m = (l + r) / 2;
    int64_t inv = solve(l, m) + solve(m, r);
    int i = l, j = m, k = l;
    while (i < m || j < r) {
      if (j == r || (i < m && a[i] <= a[j])) {
        tmp[k++] = a[i++];
      } else {
        inv += m - i;
        tmp[k++] = a[j++];
      }
    }
    for (int t = l; t < r; ++t) a[t] = tmp[t];
    return inv;
  };
  return solve(0, n);
}
