// Reusable feedback widgets for lessons.
//
// Multiple choice:
//   <div class="quiz" data-answer="2">            (0-based index of correct option)
//     <p class="q">Question?</p>
//     <button class="opt">…</button> ×N
//     <p class="explain">Why the answer is right.</p>
//   </div>
//
// Fill-in drill (each input checked against its data-expect):
//   <div class="drill">
//     <p class="q">Instructions</p>
//     <div class="row"><code>input</code> <label>x <input data-expect="1"></label></div>
//     <button class="check">Check</button>
//     <p class="explain">Worked answer.</p>
//   </div>
(function () {
  function initQuiz(el) {
    const answer = Number(el.dataset.answer);
    const opts = [...el.querySelectorAll("button.opt")];
    opts.forEach((btn, i) => {
      btn.addEventListener("click", () => {
        if (el.classList.contains("done")) return;
        btn.classList.add(i === answer ? "correct" : "wrong");
        if (i === answer) {
          el.classList.add("done");
        } else {
          el.dataset.misses = Number(el.dataset.misses || 0) + 1;
        }
        updateScore();
      });
    });
  }

  // After a wrong check, a "Show answer" button appears that fills in the
  // expected values and reveals the worked answer, so nobody gets stuck.
  function initDrill(el) {
    const btn = el.querySelector("button.check");
    const inputs = [...el.querySelectorAll("input[data-expect]")];
    const reveal = document.createElement("button");
    reveal.className = "check reveal";
    reveal.textContent = "Show answer";
    reveal.hidden = true;
    btn.after(reveal);
    reveal.addEventListener("click", () => {
      inputs.forEach((inp) => {
        if (inp.value.trim() !== inp.dataset.expect) {
          inp.value = inp.dataset.expect;
          inp.classList.remove("correct", "wrong");
          inp.classList.add("revealed");
        }
      });
      el.classList.add("done");
      reveal.hidden = true;
    });
    btn.addEventListener("click", () => {
      let allOk = true;
      inputs.forEach((inp) => {
        const ok = inp.value.trim() === inp.dataset.expect;
        inp.classList.toggle("correct", ok);
        inp.classList.toggle("wrong", !ok);
        if (!ok) allOk = false;
      });
      if (allOk) el.classList.add("done");
      reveal.hidden = allOk || el.classList.contains("done");
      updateScore();
    });
  }

  // Optional: <p class="score" data-for="quiz"></p> shows first-try accuracy.
  function updateScore() {
    document.querySelectorAll(".score").forEach((s) => {
      const qs = [...document.querySelectorAll(".quiz")];
      const done = qs.filter((q) => q.classList.contains("done"));
      const firstTry = done.filter((q) => !Number(q.dataset.misses || 0));
      s.textContent = `${done.length}/${qs.length} answered · ${firstTry.length} on the first try`;
    });
  }

  // <button class="copy" data-target="id">Copy</button> copies a <pre>'s text.
  function initCopy(btn) {
    btn.addEventListener("click", async () => {
      const text = document.getElementById(btn.dataset.target).innerText;
      try {
        await navigator.clipboard.writeText(text);
        btn.textContent = "Copied";
      } catch {
        btn.textContent = "Select & copy manually";
      }
    });
  }

  document.addEventListener("DOMContentLoaded", () => {
    document.querySelectorAll(".quiz").forEach(initQuiz);
    document.querySelectorAll(".drill").forEach(initDrill);
    document.querySelectorAll("button.copy").forEach(initCopy);
    updateScore();
  });
})();
