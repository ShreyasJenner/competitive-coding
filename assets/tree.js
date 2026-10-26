// Binary trees: a static drawing, and a step-through of a recursion that shows
// what each call hands back to its parent.
//
// Trees use LeetCode's level-order format, with null for a missing child:
//   [3, 5, 1, 6, 2, 0, 8, null, null, 7, 4]
//
// Static figure:
//   <figure class="treeviz" id="t"></figure>
//   Tree.draw(document.getElementById("t"), values, { labels: { 5: "6" } });
//   (labels are keyed by node value and drawn under the node)
//
// Stepper:
//   <div class="treeviz no-print" id="s"></div>
//   Tree.mount(document.getElementById("s"), { values, p: 5, q: 4 });
//
// Steps come from an algorithm function (default Tree.lca), which gets the
// built tree and the options and returns plain step objects:
//   { cur, stack, ret, note }   cur = node id or null; stack = node ids;
//                               ret = { id: "label" } for calls that returned
// A later lesson can pass `algorithm: mySize` with the same step shape.
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

  // Level order -> { nodes: [{ id, val, left, right, depth, x }], root }.
  // Ids are positions in `nodes`; x is the in-order position, so the drawing
  // never overlaps.
  function build(values) {
    const nodes = [];
    const make = (val, depth) => (nodes.push({ id: nodes.length, val, left: null, right: null, depth }), nodes.length - 1);
    if (!values.length || values[0] == null) return { nodes, root: null };
    const root = make(values[0], 0);
    const level = [root];
    for (let i = 1, k = 0; i < values.length; k++) {
      const par = nodes[level[k]];
      for (const side of ["left", "right"]) {
        if (i < values.length && values[i] != null) level.push(par[side] = make(values[i], par.depth + 1));
        i++;
      }
    }
    let x = 0;
    (function inorder(id) {
      if (id == null) return;
      inorder(nodes[id].left);
      nodes[id].x = x++;
      inorder(nodes[id].right);
    })(root);
    return { nodes, root };
  }

  const GAP = 46, ROW = 62, R = 16;

  // Returns { svg, circles, labels } so a stepper can restyle the nodes.
  function render(tree) {
    const { nodes } = tree;
    const width = Math.max(1, nodes.length) * GAP;
    const depth = Math.max(0, ...nodes.map((t) => t.depth));
    const root = svg("svg", { viewBox: `0 0 ${width} ${(depth + 1) * ROW + 10}`, role: "img",
      "aria-label": "binary tree" });
    const pos = (t) => [t.x * GAP + GAP / 2, t.depth * ROW + R + 6];
    for (const t of nodes)
      for (const c of [t.left, t.right])
        if (c != null) {
          const [x1, y1] = pos(t), [x2, y2] = pos(nodes[c]);
          root.append(svg("line", { x1, y1, x2, y2, class: "tr-edge" }));
        }
    const circles = [], labels = [];
    for (const t of nodes) {
      const [x, y] = pos(t);
      const g = svg("g", { class: "tr-node" });
      g.append(svg("circle", { cx: x, cy: y, r: R }), svg("text", { x, y: y + 5, "text-anchor": "middle" }, String(t.val)));
      const lab = svg("text", { x, y: y + R + 15, "text-anchor": "middle", class: "tr-ret" }, "");
      root.append(g, lab);
      circles[t.id] = g;
      labels[t.id] = lab;
    }
    return { svg: root, circles, labels };
  }

  function draw(container, values, { labels = {}, marks = {} } = {}) {
    const tree = build(values);
    const r = render(tree);
    for (const t of tree.nodes) {
      if (labels[t.val] != null) r.labels[t.id].textContent = labels[t.val];
      if (marks[t.val]) r.circles[t.id].classList.add(marks[t.val]);
    }
    container.prepend(r.svg);
    return tree;
  }

  // Mirrors the recursive LC 236 solution. Calls on an empty child aren't
  // shown as steps; the parent's note says the side was empty.
  function lca(tree, { p, q }) {
    const { nodes } = tree;
    const steps = [], stack = [], ret = {};
    const name = (id) => (id == null ? "null" : String(nodes[id].val));
    const snap = (cur, note) => steps.push({ cur, stack: [...stack], ret: { ...ret }, note });

    function call(id) {
      if (id == null) return null;
      const t = nodes[id];
      stack.push(id);
      if (t.val === p || t.val === q) {
        ret[id] = "↑ " + t.val;
        snap(id, `Call on ${t.val}: it is ${t.val === p ? "p" : "q"}. Return ${t.val} at once, without looking below.`);
        stack.pop();
        return id;
      }
      if (t.left == null && t.right == null) {
        ret[id] = "↑ null";
        snap(id, `Call on ${t.val}: a leaf that is not p or q. Both children are empty, so return null.`);
        stack.pop();
        return null;
      }
      snap(id, `Call on ${t.val}: not p or q. Ask the left subtree first.`);
      const l = call(t.left);
      snap(id, `Back at ${t.val}: the left side ${t.left == null ? "is empty, so it gives null" : `handed back ${name(l)}`}. Now ask the right.`);
      const r = call(t.right);
      let out, why;
      if (l != null && r != null) { out = id; why = `Both sides found something, so ${t.val} is the lowest common ancestor`; }
      else if (l != null || r != null) { out = l ?? r; why = `Only one side found something, so pass ${name(out)} up unchanged`; }
      else { out = null; why = "Neither side found p or q"; }
      ret[id] = "↑ " + name(out);
      snap(id, `At ${t.val}: left gave ${name(l)}, right gave ${t.right == null ? "null (empty)" : name(r)}. ${why}: return ${name(out)}.`);
      stack.pop();
      return out;
    }
    snap(null, `Find the LCA of p = ${p} and q = ${q}. Each call reports what it found in its own subtree.`);
    const ans = call(tree.root);
    snap(null, `The root's call returned ${name(ans)}. That is the answer.`);
    return steps;
  }

  // Mirrors the pair-returning LC 337 solution: each call hands back
  // (rob, skip) = the most money in its subtree if it is robbed / if it isn't.
  function robPair(tree) {
    const { nodes } = tree;
    const steps = [], stack = [], ret = {};
    const snap = (cur, note) => steps.push({ cur, stack: [...stack], ret: { ...ret }, note });
    const show = ([r, s]) => `(${r}, ${s})`;

    function call(id) {
      if (id == null) return [0, 0];
      const t = nodes[id];
      stack.push(id);
      if (t.left == null && t.right == null) {
        ret[id] = show([t.val, 0]);
        snap(id, `Call on leaf ${t.val}: robbed it is worth ${t.val}, skipped it is worth 0. Return (${t.val}, 0).`);
        stack.pop();
        return [t.val, 0];
      }
      snap(id, `Call on ${t.val}: ask both children for their pairs first.`);
      const a = call(t.left), b = call(t.right);
      const r = t.val + a[1] + b[1];
      const s = Math.max(...a) + Math.max(...b);
      ret[id] = show([r, s]);
      snap(id, `At ${t.val}: children gave ${show(a)} and ${show(b)}. Rob ${t.val}: ${t.val} + ${a[1]} + ${b[1]} = ${r} ` +
        `(both children skipped). Skip it: ${Math.max(...a)} + ${Math.max(...b)} = ${s} (each child takes its better half).`);
      stack.pop();
      return [r, s];
    }
    snap(null, "Each call returns (rob, skip): the best for its subtree if this node is robbed, and if it isn't.");
    const [r, s] = call(tree.root);
    snap(null, `The root returned (${r}, ${s}). The answer is the larger: ${Math.max(r, s)}.`);
    return steps;
  }

  function mount(root, { values, p, q, algorithm = lca, pick = true } = {}) {
    const tree = build(values);
    root.innerHTML = "";
    const r = render(tree);
    const fig = el("div", "tr-fig");
    fig.append(r.svg);

    const stackLine = el("p", "gr-stack");
    const note = el("p", "st-note");
    const controls = el("div", "st-controls");
    const prev = el("button", "", "◀ Back");
    const next = el("button", "", "Step ▶");
    const run = el("button", "", "Run ▶▶");
    const reset = el("button", "", "Reset");
    const counter = el("span", "st-count");
    controls.append(prev, next, run, reset, counter);

    const opts = { p, q };
    if (pick) {
      for (const key of ["p", "q"]) {
        const lab = el("label", "gr-toggle", `${key} = `);
        const sel = document.createElement("select");
        for (const t of tree.nodes) sel.append(new Option(String(t.val), String(t.val), false, t.val === opts[key]));
        sel.addEventListener("change", () => { opts[key] = Number(sel.value); rebuild(); });
        lab.append(sel);
        controls.append(lab);
      }
    }
    root.append(fig, stackLine, note, controls,
      el("p", "gr-hint", "Labels under a node show what its call returned. Arrow keys step."));

    let steps = [], k = 0, timer = null;
    function rebuild() {
      stop();
      steps = algorithm(tree, opts);
      k = 0;
      show();
    }
    function show() {
      const s = steps[k];
      for (const t of tree.nodes) {
        const c = r.circles[t.id];
        c.setAttribute("class", "tr-node");
        if (t.val === opts.p || t.val === opts.q) c.classList.add("tr-target");
        if (s.stack.includes(t.id)) c.classList.add("tr-onstack");
        if (t.id === s.cur) c.classList.add("tr-cur");
        r.labels[t.id].textContent = s.ret[t.id] ?? "";
      }
      stackLine.textContent = s.stack.length
        ? "call stack: " + s.stack.map((id) => `f(${tree.nodes[id].val})`).join(" → ")
        : "call stack: empty";
      note.textContent = s.note || "";
      counter.textContent = `${k + 1} / ${steps.length}`;
      prev.disabled = k === 0;
      next.disabled = run.disabled = k === steps.length - 1;
    }
    function stop() { clearInterval(timer); timer = null; run.textContent = "Run ▶▶"; }

    prev.onclick = () => { stop(); if (k > 0) { k--; show(); } };
    next.onclick = () => { stop(); if (k < steps.length - 1) { k++; show(); } };
    reset.onclick = () => { stop(); k = 0; show(); };
    run.onclick = () => {
      if (timer) return stop();
      run.textContent = "Pause";
      timer = setInterval(() => {
        if (k >= steps.length - 1) return stop();
        k++;
        show();
      }, 700);
    };
    root.tabIndex = 0;
    root.addEventListener("keydown", (e) => {
      if (e.target.tagName === "SELECT") return;
      if (e.key === "ArrowRight") { next.click(); e.preventDefault(); }
      if (e.key === "ArrowLeft") { prev.click(); e.preventDefault(); }
    });
    rebuild();
  }

  window.Tree = { build, draw, mount, lca, robPair };
})();
