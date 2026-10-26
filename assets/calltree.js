// The call tree of a recursive function of one integer argument, drawn so
// that repeated calls stand out: every call with the same argument gets the
// same colour, a tally counts calls per argument, and a "memo" toggle turns
// every repeat into a lookup that isn't expanded.
//
//   <div class="calltree no-print" id="ct"></div>
//   CallTree.mount(document.getElementById("ct"), {
//     n: 5, min: 2, max: 6,                   // problem size, and the slider's range
//     root: (n) => 0,                         // the first call's argument
//     children: (i, n) => [i + 1, i + 2],     // the calls f(i) makes
//     isBase: (i, n) => i >= n,               // base calls make no further calls
//     name: "best",                           // drawn as best(i) in the notes
//   });
// The defaults above are LC 198's best(i). Below the drawing, "calls for n = …"
// counts both versions for sizes far too big to draw (BigInt, no recursion
// into the exponential version).
(function () {
  const SVG = "http://www.w3.org/2000/svg";
  function el(tag, cls, text) {
    const e = document.createElement(tag);
    if (cls) e.className = cls;
    if (text != null) e.textContent = text;
    return e;
  }
  function svg(tag, attrs, text) {
    const e = document.createElementNS(SVG, tag);
    for (const [k, v] of Object.entries(attrs)) e.setAttribute(k, v);
    if (text != null) e.textContent = text;
    return e;
  }

  // Calls in the order they are made: { arg, depth, kids, base, hit }.
  // With memo, a call on an argument already worked out is a hit: it returns
  // the stored answer and makes no calls.
  function calls(o, n, memo) {
    const done = new Set();
    function call(arg, depth) {
      const t = { arg, depth, kids: [], base: o.isBase(arg, n), hit: false };
      if (t.base) return t;
      if (memo && done.has(arg)) return (t.hit = true), t;
      t.kids = o.children(arg, n).map((c) => call(c, depth + 1));
      done.add(arg);
      return t;
    }
    return call(o.root(n), 0);
  }

  // Exact call counts without building the tree.
  function count(o, n, memo) {
    if (memo) {
      const done = new Set();
      let total = 0;
      (function call(arg) {
        total++;
        if (o.isBase(arg, n) || done.has(arg)) return;
        o.children(arg, n).forEach(call);
        done.add(arg);
      })(o.root(n));
      return BigInt(total);
    }
    const c = new Map();   // arg -> calls made by one call on arg, itself included
    const f = (arg) => {
      if (c.has(arg)) return c.get(arg);
      const v = o.isBase(arg, n) ? 1n : 1n + o.children(arg, n).reduce((s, k) => s + f(k), 0n);
      c.set(arg, v);
      return v;
    };
    return f(o.root(n));
  }

  const GAP = 30, ROW = 46, R = 12;

  function draw(tree) {
    let leaves = 0, depth = 0;
    const all = [];
    (function place(t) {
      all.push(t);
      depth = Math.max(depth, t.depth);
      if (!t.kids.length) t.x = leaves++;
      else {
        t.kids.forEach(place);
        t.x = (t.kids[0].x + t.kids[t.kids.length - 1].x) / 2;
      }
    })(tree);
    const pos = (t) => [t.x * GAP + GAP / 2, t.depth * ROW + R + 4];
    const root = svg("svg", { viewBox: `0 0 ${leaves * GAP} ${depth * ROW + 2 * R + 8}`, role: "img",
      "aria-label": "recursion call tree" });
    for (const t of all)
      for (const k of t.kids) {
        const [x1, y1] = pos(t), [x2, y2] = pos(k);
        root.append(svg("line", { x1, y1, x2, y2, class: "tr-edge" }));
      }
    const nodes = [];
    for (const t of all) {
      const [x, y] = pos(t);
      const kind = t.base ? "ct-base" : t.hit ? "ct-hit" : `ct-c${t.arg % 6}`;
      const g = svg("g", { class: `ct-node ${kind}` });
      g.dataset.arg = t.arg;
      g.append(svg("circle", { cx: x, cy: y, r: t.base ? R * 0.7 : R }),
        svg("text", { x, y: y + 4, "text-anchor": "middle" }, String(t.arg)));
      root.append(g);
      nodes.push(g);
    }
    return { svg: root, nodes, all };
  }

  function mount(root, opts = {}) {
    const o = {
      n: 5, min: 2, max: 6, name: "best",
      root: () => 0,
      children: (i) => [i + 1, i + 2],
      isBase: (i, n) => i >= n,
      ...opts,
    };
    root.innerHTML = "";
    const fig = el("div", "ct-fig");
    const tally = el("div", "ct-tally");
    const stats = el("p", "gr-stats");
    const controls = el("div", "st-controls");

    const sizeLab = el("label", "gr-toggle", "n = ");
    const size = document.createElement("input");
    Object.assign(size, { type: "range", min: o.min, max: o.max, value: o.n });
    const sizeOut = el("span", "", String(o.n));
    sizeLab.append(size, " ", sizeOut);
    const memoLab = el("label", "gr-toggle");
    const memo = document.createElement("input");
    memo.type = "checkbox";
    memoLab.append(memo, " memo: look up repeats instead of recomputing");
    controls.append(sizeLab, memoLab);

    const big = el("p", "gr-stats");
    const bigLab = el("label", "gr-toggle", "calls for n = ");
    const bigN = document.createElement("input");
    Object.assign(bigN, { type: "number", min: 1, max: 100, value: 100, className: "st-input" });
    bigLab.append(bigN);
    const bigOut = el("span", "");
    big.append(bigLab, bigOut);

    root.append(controls, fig, stats, tally, big,
      el("p", "gr-hint", "A circle with k in it is one call " + o.name + "(k). Same number, same colour. " +
        "Small grey circles are base cases. Dashed circles are memo lookups. Click a number in the tally to " +
        "find every call on it."));

    let picked = null;
    function render() {
      const n = Number(size.value);
      sizeOut.textContent = String(n);
      const d = draw(calls(o, n, memo.checked));
      fig.replaceChildren(d.svg);

      const per = new Map();
      for (const t of d.all) if (!t.base) per.set(t.arg, (per.get(t.arg) || 0) + 1);
      tally.replaceChildren(el("span", "st-h", "calls per argument: "));
      [...per.keys()].sort((a, b) => a - b).forEach((arg) => {
        const chip = el("button", `ct-chip ct-c${arg % 6}`, `${o.name}(${arg}) ×${per.get(arg)}`);
        chip.onclick = () => { picked = picked === arg ? null : arg; mark(); };
        tally.append(chip);
      });
      const work = d.all.filter((t) => !t.base && !t.hit).length;
      stats.textContent = `${d.all.length} calls in total, ${work} of them doing real work` +
        (memo.checked ? ` (${d.all.filter((t) => t.hit).length} lookups).` : ".");
      function mark() {
        d.nodes.forEach((g) => g.classList.toggle("ct-dim", picked != null && Number(g.dataset.arg) !== picked));
        tally.querySelectorAll(".ct-chip").forEach((c) =>
          c.classList.toggle("ct-on", c.textContent.startsWith(`${o.name}(${picked})`)));
      }
      if (!per.has(picked)) picked = null;
      mark();
    }
    function renderBig() {
      const n = Math.max(1, Math.min(100, Math.floor(Number(bigN.value)) || 1));
      const plain = count(o, n, false), memod = count(o, n, true);
      const fmt = (b) => (b < 10n ** 7n ? b.toLocaleString("en") :
        `${b.toString()[0]}.${b.toString().slice(1, 3)} × 10^${b.toString().length - 1}`);
      bigOut.textContent = `: ${fmt(plain)} without the memo, ${fmt(memod)} with it.`;
    }
    size.addEventListener("input", render);
    memo.addEventListener("change", render);
    bigN.addEventListener("input", renderBig);
    render();
    renderBig();
  }

  window.CallTree = { mount, count };
})();
