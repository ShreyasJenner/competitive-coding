// Step-through visualiser for recursive code.
//
//   <div class="stepper" id="x"></div>
//   Stepper.mount(document.getElementById("x"), {
//     code: ["void dfs(int i) {", ...],     // lines shown, 1-based in steps
//     steps: [{ line, stack: ["dfs(0)", ...], vars: { path: '"a"' },
//               out: ['"a"'], note: "…" }, ...],
//   });
//
// Steps are plain data, so a lesson can precompute them, or generate them by
// running an instrumented JS copy of the algorithm (see Stepper.recorder).
(function () {
  function el(tag, cls, text) {
    const e = document.createElement(tag);
    if (cls) e.className = cls;
    if (text != null) e.textContent = text;
    return e;
  }

  function mount(root, { code, steps }) {
    root.innerHTML = "";
    const codeBox = el("pre", "st-code");
    const lines = code.map((txt, i) => {
      const ln = el("span", "st-line");
      ln.append(el("span", "st-ln", String(i + 1).padStart(2)), " " + txt + "\n");
      codeBox.append(ln);
      return ln;
    });

    const side = el("div", "st-side");
    const stackBox = el("div", "st-panel");
    const varsBox = el("div", "st-panel");
    const outBox = el("div", "st-panel");
    side.append(stackBox, varsBox, outBox);

    const note = el("p", "st-note");
    const controls = el("div", "st-controls");
    const prev = el("button", "", "◀ Back");
    const next = el("button", "", "Step ▶");
    const reset = el("button", "", "Reset");
    const counter = el("span", "st-count");
    controls.append(prev, next, reset, counter);

    const grid = el("div", "st-grid");
    grid.append(codeBox, side);
    root.append(grid, note, controls);

    let k = 0;
    function render() {
      const s = steps[k];
      lines.forEach((ln, i) => ln.classList.toggle("st-active", i + 1 === s.line));

      stackBox.innerHTML = "";
      stackBox.append(el("div", "st-h", "Call stack (top = running now)"));
      [...s.stack].reverse().forEach((f, i) =>
        stackBox.append(el("div", "st-frame" + (i === 0 ? " st-top" : ""), f)));

      varsBox.innerHTML = "";
      varsBox.append(el("div", "st-h", "State"));
      Object.entries(s.vars || {}).forEach(([key, v]) =>
        varsBox.append(el("div", "st-var", `${key} = ${v}`)));

      outBox.innerHTML = "";
      outBox.append(el("div", "st-h", "Output so far"));
      outBox.append(el("div", "st-var", (s.out || []).join("  ") || "—"));

      note.textContent = s.note || "";
      counter.textContent = `${k + 1} / ${steps.length}`;
      prev.disabled = k === 0;
      next.disabled = k === steps.length - 1;
    }

    prev.onclick = () => { if (k > 0) { k--; render(); } };
    next.onclick = () => { if (k < steps.length - 1) { k++; render(); } };
    reset.onclick = () => { k = 0; render(); };
    root.tabIndex = 0;
    root.addEventListener("keydown", (e) => {
      if (e.key === "ArrowRight") { next.click(); e.preventDefault(); }
      if (e.key === "ArrowLeft") { prev.click(); e.preventDefault(); }
    });
    render();
  }

  // Helper for generating steps from an instrumented algorithm:
  //   const r = Stepper.recorder();
  //   r.call("dfs(0)"); r.snap(line, vars, note); r.emit('"a"'); r.ret();
  //   Stepper.mount(node, { code, steps: r.steps });
  function recorder() {
    const stack = [], out = [], steps = [];
    return {
      steps,
      call(frame) { stack.push(frame); },
      ret() { stack.pop(); },
      emit(v) { out.push(v); },
      snap(line, vars, note) {
        steps.push({ line, stack: [...stack], vars: { ...vars }, out: [...out], note });
      },
    };
  }

  window.Stepper = { mount, recorder };
})();
