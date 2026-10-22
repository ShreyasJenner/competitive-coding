// Step-through visualiser for searches on a grid of land ('1') and water ('0').
//
//   <div class="gridviz no-print" id="g"></div>
//   Grid.mount(document.getElementById("g"), {
//     rows: ["11000", "11000", "00100"],   // initial grid; click a cell to toggle it
//     markToggle: true,                    // show the "mark on arrival" checkbox
//   });
//
// Steps come from an algorithm function (default Grid.floodDFS), which gets
// the cells (array of arrays of 0/1) and the options, and returns plain step
// objects: { seen, cur, scan, stack, count, note }. `seen[r][c]` is 0 or the
// island number. A later lesson can pass `algorithm: myBFS` with the same
// step shape (`stack` then just holds the frontier).
(function () {
  function el(tag, cls, text) {
    const e = document.createElement(tag);
    if (cls) e.className = cls;
    if (text != null) e.textContent = text;
    return e;
  }

  const DIRS = [[1, 0], [-1, 0], [0, 1], [0, -1]];  // down, up, right, left
  const key = ([r, c]) => `(${r},${c})`;

  // Mirrors the LC 200 scan + recursive fill. With mark off, a cell is never
  // marked, so the fill bounces between neighbours until maxSteps.
  function floodDFS(cells, { mark = true, maxSteps = 600 } = {}) {
    const m = cells.length, n = cells[0].length;
    const seen = cells.map((row) => row.map(() => 0));
    const steps = [], stack = [];
    let count = 0, scan = null, stopped = false;
    const snap = (cur, note) => {
      if (steps.length >= maxSteps) { stopped = true; return; }
      steps.push({ seen: seen.map((r) => [...r]), cur, scan, stack: [...stack], count, note });
    };

    function fill(r, c, from) {
      if (stopped) return;
      if (r < 0 || c < 0 || r >= m || c >= n) {
        snap(null, `${key([r, c])} is off the grid: return.`); return;
      }
      if (!cells[r][c]) { snap([r, c], `${key([r, c])} is water: return.`); return; }
      if (seen[r][c]) { snap([r, c], `${key([r, c])} is already marked: return.`); return; }
      stack.push([r, c]);
      if (mark) seen[r][c] = count;
      snap([r, c], mark
        ? `Arrive at ${key([r, c])}: mark it island ${count}, then try its 4 neighbours.`
        : `Arrive at ${key([r, c])}${from ? ` from ${key(from)}` : ""}, but nothing is marked.`);
      for (const [dr, dc] of DIRS) {
        if (stopped) return;
        fill(r + dr, c + dc, [r, c]);
      }
      stack.pop();
      if (!stopped) snap([r, c], `All 4 neighbours of ${key([r, c])} are done: return.`);
    }

    for (let r = 0; r < m && !stopped; r++)
      for (let c = 0; c < n && !stopped; c++) {
        scan = [r, c];
        if (cells[r][c] && !seen[r][c]) {
          count++;
          snap(null, `Scan finds unmarked land at ${key([r, c])}: island ${count}. Start a fill.`);
          fill(r, c, null);
        } else {
          snap(null, `Scan ${key([r, c])}: ${cells[r][c] ? "already marked" : "water"}, skip.`);
        }
      }
    if (stopped) {
      steps[steps.length - 1].note +=
        ` …and it never ends. Stopped after ${maxSteps} steps, with the call stack ${stack.length} deep.`;
    } else {
      scan = null;
      snap(null, `Scan finished: ${count} island${count === 1 ? "" : "s"}.`);
    }
    return steps;
  }

  function mount(root, { rows, markToggle = false, algorithm = floodDFS, maxSteps } = {}) {
    let cells = rows.map((row) => [...row].map((ch) => (ch === "1" ? 1 : 0)));
    const m = cells.length, n = cells[0].length;

    root.innerHTML = "";
    const board = el("div", "gr-board");
    board.style.gridTemplateColumns = `repeat(${n}, 1fr)`;
    board.style.maxWidth = `${n * 2.4}rem`;
    const tiles = cells.map((row, r) => row.map((_, c) => {
      const t = el("button", "gr-cell");
      t.type = "button";
      t.title = `(${r},${c}): click to toggle land/water`;
      t.addEventListener("click", () => { cells[r][c] ^= 1; rebuild(); });
      board.append(t);
      return t;
    }));

    const stats = el("p", "gr-stats");
    const stackLine = el("p", "gr-stack");
    const note = el("p", "st-note");
    const controls = el("div", "st-controls");
    const prev = el("button", "", "◀ Back");
    const next = el("button", "", "Step ▶");
    const run = el("button", "", "Run ▶▶");
    const reset = el("button", "", "Reset");
    const counter = el("span", "st-count");
    controls.append(prev, next, run, reset, counter);

    let markBox = null;
    if (markToggle) {
      const lab = el("label", "gr-toggle");
      markBox = document.createElement("input");
      markBox.type = "checkbox";
      markBox.checked = true;
      markBox.addEventListener("change", rebuild);
      lab.append(markBox, " mark a cell on arrival");
      controls.append(lab);
    }

    const hint = el("p", "gr-hint", "Click a cell to toggle land/water. Arrow keys step.");
    root.append(board, stats, stackLine, note, controls, hint);

    let steps = [], k = 0, timer = null;
    function rebuild() {
      stop();
      steps = algorithm(cells, { mark: markBox ? markBox.checked : true, maxSteps });
      k = 0;
      render();
    }
    function render() {
      const s = steps[k];
      tiles.forEach((row, r) => row.forEach((t, c) => {
        const id = s.seen[r][c];
        t.className = "gr-cell" + (cells[r][c] ? " gr-land" : " gr-water");
        if (id) t.classList.add("gr-seen", `gr-isl${((id - 1) % 6) + 1}`);
        if (s.cur && s.cur[0] === r && s.cur[1] === c) t.classList.add("gr-cur");
        if (s.scan && s.scan[0] === r && s.scan[1] === c) t.classList.add("gr-scan");
        if (s.stack.some(([a, b]) => a === r && b === c)) t.classList.add("gr-onstack");
        t.textContent = id ? String(id) : "";
      }));
      stats.textContent = `islands counted: ${s.count} · call stack depth: ${s.stack.length}`;
      const shown = s.stack.slice(-6).map((p) => `fill${key(p)}`);
      stackLine.textContent = s.stack.length
        ? (s.stack.length > 6 ? "… → " : "") + shown.join(" → ")
        : "call stack: empty (the scan is running)";
      note.textContent = s.note || "";
      counter.textContent = `${k + 1} / ${steps.length}`;
      prev.disabled = k === 0;
      next.disabled = run.disabled = k === steps.length - 1;
    }
    function stop() { clearInterval(timer); timer = null; run.textContent = "Run ▶▶"; }

    prev.onclick = () => { stop(); if (k > 0) { k--; render(); } };
    next.onclick = () => { stop(); if (k < steps.length - 1) { k++; render(); } };
    reset.onclick = () => { stop(); k = 0; render(); };
    run.onclick = () => {
      if (timer) return stop();
      run.textContent = "Pause";
      timer = setInterval(() => {
        if (k >= steps.length - 1) return stop();
        k++;
        render();
      }, 220);
    };
    root.tabIndex = 0;
    root.addEventListener("keydown", (e) => {
      if (e.key === "ArrowRight") { next.click(); e.preventDefault(); }
      if (e.key === "ArrowLeft") { prev.click(); e.preventDefault(); }
    });
    rebuild();
  }

  window.Grid = { mount, floodDFS };
})();
