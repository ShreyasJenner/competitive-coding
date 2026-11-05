#include "../../src/leetcode/460.cpp"
#include "../testlib.hpp"

#include <csignal>
#include <cstring>
#include <random>
#include <set>
#include <string>
#include <tuple>
#include <unistd.h>
#include <unordered_map>
#include <vector>

struct Op {
  bool put;
  int key, value;  // value is unused for get
};

Op put(int k, int v) { return {true, k, v}; }
Op get(int k) { return {false, k, 0}; }

// Reference cache, O(log n) per call rather than O(1): one ordered set holds
// every key as (use count, time of last use, key), so the smallest entry is
// always the one to evict.
struct Reference {
  int cap, clock = 0;
  std::unordered_map<int, std::tuple<int, int, int>> entry;  // key -> (value, count, time)
  std::set<std::tuple<int, int, int>> order;      // (count, time, key)

  Reference(int cap) : cap(cap) {}

  void touch(int key) {
    auto &[value, count, time] = entry.at(key);
    order.erase({count, time, key});
    count++, time = ++clock;
    order.insert({count, time, key});
  }

  int get(int key) {
    auto it = entry.find(key);
    if (it == entry.end()) return -1;
    touch(key);
    return std::get<0>(it->second);
  }

  void put(int key, int value) {
    if (auto it = entry.find(key); it != entry.end()) {
      std::get<0>(it->second) = value;
      touch(key);
      return;
    }
    if ((int)entry.size() == cap) {
      int victim = std::get<2>(*order.begin());
      order.erase(order.begin());
      entry.erase(victim);
    }
    entry[key] = {value, 1, ++clock};
    order.insert({1, clock, key});
  }
};

// The results of every get, in order.
template <class Cache> std::vector<int> run(int cap, const std::vector<Op> &ops) {
  Cache cache(cap);
  std::vector<int> out;
  for (const Op &op : ops) {
    if (op.put) cache.put(op.key, op.value);
    else out.push_back(cache.get(op.key));
  }
  return out;
}

std::string show(int cap, const std::vector<Op> &ops) {
  std::string s = "cap=" + std::to_string(cap) + ":";
  for (const Op &op : ops)
    s += op.put ? " put(" + std::to_string(op.key) + "," + std::to_string(op.value) + ")"
                : " get(" + std::to_string(op.key) + ")";
  return s;
}

std::string show(const std::vector<int> &v) {
  std::string s = "gets [";
  for (size_t i = 0; i < v.size(); i++) s += (i ? "," : "") + std::to_string(v[i]);
  return s + "]";
}

// For long runs: where the gets first differ, and what came just before.
std::string first_diff(const std::vector<Op> &ops, const std::vector<int> &got,
                       const std::vector<int> &want, bool mine) {
  size_t g = 0;
  for (size_t i = 0; i < ops.size(); i++) {
    if (ops[i].put) continue;
    if (g >= got.size() || got[g] != want[g]) {
      const std::vector<int> &v = mine ? got : want;
      return "call #" + std::to_string(i + 1) + " get(" + std::to_string(ops[i].key) +
             ") = " + (g < v.size() ? std::to_string(v[g]) : "?");
    }
    g++;
  }
  return "?";
}

// Every case has a time limit. Correct code takes about a second here (these
// builds are unoptimised, with sanitizers), but an eviction that scans the
// whole cache is O(capacity) per put, and 1e5 evictions with capacity 1e4
// take minutes. O(log n) per call (a std::set) passes, as it does on LeetCode. Then SIGALRM fires: report this
// case as failed and stop the run. Only write() is safe inside a signal
// handler, so the message is built before each case starts.
const int LIMIT = 6;  // seconds
char timeout_msg[512];

void write_int(int x) {
  char buf[16];
  int k = sizeof buf;
  do buf[--k] = '0' + x % 10; while (x /= 10);
  ssize_t r = write(1, buf + k, sizeof buf - k);
  (void)r;
}

void on_timeout(int) {
  ssize_t r = write(1, timeout_msg, strlen(timeout_msg));
  // The same line testlib::summary() prints, counting this case as failed.
  r = write(1, "cases: ", 7);
  write_int(testlib::passed);
  r = write(1, " passed, ", 9);
  write_int(testlib::failed + 1);
  r = write(1, " failed\n", 8);
  (void)r;
  _exit(1);
}

void check(int cap, const std::vector<Op> &ops, const std::string &label = "") {
  std::string shown = label.empty() ? show(cap, ops) : label;
  std::vector<int> want = run<Reference>(cap, ops);
  snprintf(timeout_msg, sizeof timeout_msg,
           "FAIL  %s  ->  still running after %d s\n"
           "      want: each get and put in O(1). Is something scanning the whole cache? "
           "(later cases not run)\n",
           shown.c_str(), LIMIT);
  alarm(LIMIT);
  std::vector<int> got = run<LFUCache>(cap, ops);
  alarm(0);
  if (label.empty()) testlib::record(got == want, shown, show(got), show(want));
  else if (got == want) testlib::record(true, shown, "all gets match", "");
  else testlib::record(false, shown, first_diff(ops, got, want, true), first_diff(ops, got, want, false));
}

// One case covering `runs` random short sequences on a tiny cache and only a
// few keys, so that evictions and ties happen all the time. Reports the
// first mismatch.
void stress(int runs) {
  std::mt19937 rng(460);
  for (int r = 0; r < runs; r++) {
    int cap = 1 + rng() % 4, keys = 2 + rng() % 5;
    std::vector<Op> ops(1 + rng() % 30);
    for (Op &op : ops)
      op = rng() % 2 ? put(rng() % keys, rng() % 100) : get(rng() % keys);
    std::vector<int> want = run<Reference>(cap, ops);
    std::vector<int> got = run<LFUCache>(cap, ops);
    if (got != want) {
      testlib::record(false, "random " + show(cap, ops), show(got), show(want));
      return;
    }
  }
  testlib::record(true, std::to_string(runs) + " random sequences, capacity 1-4, keys 0-6",
                  "all match reference", "");
}

std::vector<Op> random_ops(int n, int keys, int put_percent, unsigned seed) {
  std::mt19937 rng(seed);
  std::vector<Op> ops(n);
  for (Op &op : ops)
    op = (int)(rng() % 100) < put_percent ? put(rng() % keys, rng() % 1000000001)
                                          : get(rng() % keys);
  return ops;
}

int main() {
  signal(SIGALRM, on_timeout);
  // LeetCode example
  check(2, {put(1, 1), put(2, 2), get(1), put(3, 3), get(2), get(3), put(4, 4), get(1), get(3), get(4)});
  // capacity 1: every new key replaces the old one
  check(1, {put(2, 1), get(2), put(3, 2), get(2), get(3)});
  // a get on a missing key changes nothing
  check(1, {get(5), put(5, 5), get(5), get(6), get(5)});
  check(2, {put(1, 1), get(9), put(2, 2), put(3, 3), get(1), get(2), get(3)});
  // a put on a key that is there updates the value and counts as a use, so 2 goes, not 1
  check(2, {put(1, 1), put(2, 2), put(1, 10), put(3, 3), get(1), get(2), get(3)});
  check(2, {put(1, 1), put(1, 2), put(1, 3), get(1), put(2, 5), put(3, 6), get(1), get(2), get(3)});
  // a tie goes by last use, not by when the key went in: 2 went in after 1 but was used before it
  check(2, {put(1, 1), put(2, 2), get(2), get(1), put(3, 3), get(2), get(1), get(3)});
  check(3, {put(1, 1), put(2, 2), put(3, 3), get(3), get(1), get(2), put(4, 4), get(3), get(1), get(2), get(4)});
  // after an eviction the new key has count 1, the lowest again: put(4,4) must evict 3, not 2
  check(2, {put(1, 1), get(1), get(1), put(2, 2), get(2), get(2), get(2), put(3, 3), put(4, 4),
            get(1), get(3), get(2), get(4)});
  // 0 and 1e9 are real values, not "missing"
  check(2, {put(0, 0), get(0), put(100000, 1000000000), get(100000), get(0)});
  // an evicted key that comes back starts again from count 1
  check(2, {put(1, 1), get(1), get(1), get(1), put(2, 2), get(2), put(3, 3), get(3), get(3),
            put(1, 7), put(4, 4), get(1), get(2), get(3), get(4)});
  stress(3000);
  // big runs: an O(capacity) scan per call doesn't finish
  check(10000, random_ops(200000, 100001, 50, 1), "capacity 10000, 2e5 random calls on keys 0-1e5");
  {
    std::vector<Op> ops;
    for (int i = 0; i < 100000; i++) ops.push_back(put(i, i));
    check(10000, ops, "capacity 10000, 1e5 puts of new keys (90000 evictions)");
  }
  {
    std::vector<Op> ops;
    for (int i = 0; i < 10000; i++) ops.push_back(put(i, i));
    std::vector<Op> more = random_ops(100000, 10000, 30, 3);
    ops.insert(ops.end(), more.begin(), more.end());
    check(10000, ops, "capacity 10000, filled, then 1e5 calls on those keys");
  }
  {
    // one key used 1e5 times, then 1e5 new keys that each push out the last one
    std::vector<Op> ops = {put(0, 0)};
    for (int i = 0; i < 100000; i++) ops.push_back(get(0));
    for (int i = 1; i <= 99999; i++) ops.push_back(put(i, i)), ops.push_back(get(i - 1));
    check(2, ops, "capacity 2: key 0 used 1e5 times, then 99999 new keys");
  }
  return testlib::summary();
}
