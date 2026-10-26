// Course map: the single list of topics and lessons. Every lesson's nav and
// lessons/index.html are drawn from it, so a new lesson is added here only.
//
// Lessons live in lessons/<topic id>/<file>. In a lesson:
//   <nav class="course no-print" data-topic="backtracking" data-file="0002-….html"></nav>
// In lessons/index.html:
//   <div id="course-index"></div>
(function () {
  const TOPICS = [
    {
      id: "backtracking",
      title: "Backtracking",
      reference: "backtracking.html",
      lessons: [
        { file: "0001-keep-or-delete-backtracking.html", n: 1, title: "Keep or Delete", problem: "LC 301" },
        { file: "0002-dfs-the-tree-you-never-build.html", n: 2, title: "The Implicit Tree", problem: "LC 301" },
        { file: "0003-skip-equal-siblings.html", n: 3, title: "Skip Equal Siblings", problem: "LC 301" },
      ],
    },
    {
      id: "recursive-descent",
      title: "Recursive Descent",
      reference: "recursive-descent.html",
      lessons: [
        { file: "0004-one-call-one-expression.html", n: 4, title: "One Call, One Expression", problem: "LC 1106" },
      ],
    },
    {
      id: "graphs",
      title: "Graphs",
      reference: "graphs.html",
      lessons: [
        { file: "0005-every-cell-is-a-node.html", n: 5, title: "Every Cell Is a Node", problem: "LC 200" },
      ],
    },
    {
      id: "trees",
      title: "Trees",
      reference: "trees.html",
      lessons: [
        { file: "0006-ask-your-children.html", n: 6, title: "Ask Your Children", problem: "LC 236" },
      ],
    },
    {
      id: "dp",
      title: "Dynamic Programming",
      reference: "dp.html",
      lessons: [
        { file: "0007-ask-each-question-once.html", n: 7, title: "Ask Each Question Once", problem: "LC 198" },
        { file: "0008-two-answers-per-node.html", n: 8, title: "Two Answers per Node", problem: "LC 337" },
      ],
    },
  ];

  function a(href, text, cls) {
    const e = document.createElement("a");
    e.href = href;
    e.textContent = text;
    if (cls) e.className = cls;
    return e;
  }

  // Paths are relative to lessons/<topic>/.
  function renderNav(nav) {
    const topic = TOPICS.find((t) => t.id === nav.dataset.topic);
    if (!topic) return;
    const k = topic.lessons.findIndex((l) => l.file === nav.dataset.file);
    nav.innerHTML = "";

    const head = document.createElement("div");
    head.className = "course-head";
    head.append(a("../index.html", "All topics"), " / ", topic.title, " · ",
      a(`../../reference/${topic.reference}`, "Reference sheet"));
    nav.append(head);

    const list = document.createElement("ol");
    list.className = "course-list";
    topic.lessons.forEach((l, i) => {
      const li = document.createElement("li");
      li.value = l.n;
      if (i === k) {
        li.className = "here";
        li.textContent = l.title;
      } else {
        li.append(a(l.file, l.title));
      }
      list.append(li);
    });
    nav.append(list);

    const step = document.createElement("div");
    step.className = "course-step";
    if (k > 0) step.append(a(topic.lessons[k - 1].file, `← ${topic.lessons[k - 1].title}`));
    if (k >= 0 && k < topic.lessons.length - 1)
      step.append(a(topic.lessons[k + 1].file, `${topic.lessons[k + 1].title} →`, "next"));
    if (step.childNodes.length) nav.append(step);
  }

  // Paths are relative to lessons/.
  function renderIndex(root) {
    root.innerHTML = "";
    TOPICS.forEach((t) => {
      const h = document.createElement("h2");
      h.textContent = t.title;
      const ref = document.createElement("p");
      ref.className = "subtitle";
      ref.append(a(`../reference/${t.reference}`, "Reference sheet"), ` · ${t.lessons.length} lesson${t.lessons.length > 1 ? "s" : ""}`);
      const list = document.createElement("ol");
      list.className = "course-list";
      t.lessons.forEach((l) => {
        const li = document.createElement("li");
        li.value = l.n;
        li.append(a(`${t.id}/${l.file}`, l.title), ` · ${l.problem}`);
        list.append(li);
      });
      root.append(h, ref, list);
    });
  }

  document.addEventListener("DOMContentLoaded", () => {
    document.querySelectorAll("nav.course[data-topic]").forEach(renderNav);
    const idx = document.getElementById("course-index");
    if (idx) renderIndex(idx);
  });

  window.Course = { TOPICS };
})();
