int64_t inv_cnt(vector<int> &a) {
	if (a.size() <= 1) return 0;
	int n = a.size();
	vector<int> left(a.begin(), a.begin() + n / 2);
	vector<int> right(a.begin() + n / 2, a.end());
	int64_t ret = inv_cnt(left) + inv_cnt(right);
	for (int i = 0, j = 0, k = 0; i < (int)left.size() || j < (int)right.size();) {
		if (i == (int)left.size()) a[k++] = right[j++];
		else if (j == (int)right.size()) a[k++] = left[i++];
		else if (left[i] <= right[j]) a[k++] = left[i++];
		else {
			ret += (int)left.size() - i;
			a[k++] = right[j++];
		}
	}
	return ret;
}
