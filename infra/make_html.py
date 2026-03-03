import argparse
import json
import math
from datetime import datetime, timezone
from html import escape
from pathlib import Path


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Generate index.html visualization from report.json"
    )
    parser.add_argument(
        "--report-dir",
        default="reports",
        help="Directory containing report.json and output index.html",
    )
    return parser.parse_args()


def load_report(path: Path) -> dict:
    with path.open("r", encoding="utf-8") as handle:
        return json.load(handle)


def as_float(value) -> float | None:
    try:
        if value is None:
            return None
        return float(value)
    except (TypeError, ValueError):
        return None


def fmt_seconds(value) -> str:
    parsed = as_float(value)
    if parsed is None:
        return "n/a"
    return f"{parsed:.6f} s"


def fmt_ratio(value) -> str:
    parsed = as_float(value)
    if parsed is None or not math.isfinite(parsed):
        return "n/a"
    return f"{parsed:.3f}x"


def render_bar_rows(values: list[tuple[str, float]], bar_class: str) -> str:
    if not values:
        return "<p class='empty'>No data available.</p>"

    max_value = max(v for _, v in values)
    rows: list[str] = []
    for label, value in values:
        width = 0.0 if max_value <= 0.0 else (value / max_value) * 100.0
        rows.append(
            "<div class='bar-row'>"
            f"<div class='bar-label'>{escape(label)}</div>"
            "<div class='bar-track'>"
            f"<div class='bar-fill {bar_class}' style='width: {width:.2f}%'></div>"
            "</div>"
            f"<div class='bar-value'>{value:.6f} s</div>"
            "</div>"
        )
    return "\n".join(rows)


def build_html(report: dict, source_path: Path) -> str:
    run_spec = report.get("run_spec_report") or {}
    impl_report = report.get("impl_report") or {}

    seed = report.get("seed", "n/a")
    equivalent = run_spec.get("equivalent")
    status_text = "PASS" if equivalent else "FAIL"
    status_class = "status-pass" if equivalent else "status-fail"
    if equivalent is None:
        status_text = "n/a"
        status_class = "status-na"

    conventional_total = as_float(impl_report.get("conventional_runtime_s_total"))
    optimized_total = as_float(impl_report.get("optimized_runtime_s_total"))
    conventional_per_point = as_float(impl_report.get("conventional_runtime_per_point"))
    optimized_per_point = as_float(impl_report.get("optimized_runtime_per_point"))

    speedup = None
    if conventional_per_point is not None and optimized_per_point and optimized_per_point > 0:
        speedup = conventional_per_point / optimized_per_point

    impl_bars: list[tuple[str, float]] = []
    if conventional_total is not None:
        impl_bars.append(("Conventional", conventional_total))
    if optimized_total is not None:
        impl_bars.append(("Optimized", optimized_total))

    runtime_by_design = run_spec.get("runtime_s_by_design") or {}
    design_rows: list[tuple[str, float]] = []
    for name, value in runtime_by_design.items():
        parsed = as_float(value)
        if parsed is not None:
            design_rows.append((str(name), parsed))
    design_rows.sort(key=lambda item: item[1], reverse=True)

    rule_counts = run_spec.get("rule_application_counts") or {}
    rule_rows_html = []
    for rule, count in sorted(rule_counts.items(), key=lambda item: str(item[0])):
        rule_rows_html.append(
            f"<tr><td>{escape(str(rule))}</td><td>{escape(str(count))}</td></tr>"
        )
    if not rule_rows_html:
        rule_rows_html.append("<tr><td colspan='2' class='empty'>No data available.</td></tr>")

    generated_at = datetime.now(timezone.utc).isoformat()

    return f"""<!doctype html>
<html lang="en">
<head>
  <meta charset="utf-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1" />
  <title>Nightly Report</title>
  <style>
    :root {{
      --bg: #f6f7f9;
      --surface: #ffffff;
      --text: #1b1f2a;
      --muted: #667085;
      --line: #d0d5dd;
      --accent: #0f766e;
      --accent-2: #1d4ed8;
      --fail: #b42318;
      --na: #7a5af8;
    }}
    * {{ box-sizing: border-box; }}
    body {{
      margin: 0;
      font-family: "Segoe UI", Tahoma, Geneva, Verdana, sans-serif;
      color: var(--text);
      background:
        radial-gradient(circle at 15% 10%, #d1fae5 0, transparent 30%),
        radial-gradient(circle at 90% 5%, #dbeafe 0, transparent 28%),
        var(--bg);
    }}
    .container {{
      max-width: 980px;
      margin: 0 auto;
      padding: 24px 16px 40px;
    }}
    h1 {{ margin: 0 0 8px; font-size: 30px; }}
    .subtitle {{ margin: 0 0 20px; color: var(--muted); }}
    .grid {{
      display: grid;
      grid-template-columns: repeat(auto-fit, minmax(180px, 1fr));
      gap: 12px;
      margin-bottom: 18px;
    }}
    .card {{
      background: var(--surface);
      border: 1px solid var(--line);
      border-radius: 12px;
      padding: 12px;
    }}
    .card-title {{
      color: var(--muted);
      font-size: 12px;
      text-transform: uppercase;
      letter-spacing: .04em;
      margin-bottom: 6px;
    }}
    .card-value {{
      font-size: 20px;
      font-weight: 700;
    }}
    .status-pass {{ color: var(--accent); }}
    .status-fail {{ color: var(--fail); }}
    .status-na {{ color: var(--na); }}
    .section {{
      background: var(--surface);
      border: 1px solid var(--line);
      border-radius: 12px;
      padding: 14px;
      margin-top: 14px;
    }}
    .section h2 {{
      margin: 0 0 10px;
      font-size: 18px;
    }}
    .bar-row {{
      display: grid;
      grid-template-columns: 180px 1fr 120px;
      gap: 10px;
      align-items: center;
      margin-bottom: 8px;
    }}
    .bar-label {{ font-size: 14px; }}
    .bar-track {{
      height: 12px;
      background: #eef2f6;
      border-radius: 999px;
      overflow: hidden;
    }}
    .bar-fill {{
      height: 100%;
      border-radius: 999px;
    }}
    .impl-bar {{ background: linear-gradient(90deg, var(--accent), #34d399); }}
    .spec-bar {{ background: linear-gradient(90deg, var(--accent-2), #60a5fa); }}
    .bar-value {{
      text-align: right;
      font-variant-numeric: tabular-nums;
      color: #344054;
      font-size: 13px;
    }}
    table {{
      width: 100%;
      border-collapse: collapse;
    }}
    th, td {{
      text-align: left;
      padding: 8px;
      border-bottom: 1px solid #eaecf0;
      font-size: 14px;
    }}
    th {{ color: #475467; }}
    .empty {{ color: var(--muted); }}
    @media (max-width: 720px) {{
      .bar-row {{
        grid-template-columns: 1fr;
        gap: 4px;
      }}
      .bar-value {{ text-align: left; }}
    }}
  </style>
</head>
<body>
  <main class="container">
    <h1>Nightly Report</h1>
    <p class="subtitle">Source: {escape(str(source_path))}<br />Generated at: {escape(generated_at)}</p>

    <div class="grid">
      <article class="card">
        <div class="card-title">Seed</div>
        <div class="card-value">{escape(str(seed))}</div>
      </article>
      <article class="card">
        <div class="card-title">Spec Check</div>
        <div class="card-value {status_class}">{escape(status_text)}</div>
      </article>
      <article class="card">
        <div class="card-title">Conventional / Point</div>
        <div class="card-value">{escape(fmt_seconds(conventional_per_point))}</div>
      </article>
      <article class="card">
        <div class="card-title">Optimized / Point</div>
        <div class="card-value">{escape(fmt_seconds(optimized_per_point))}</div>
      </article>
      <article class="card">
        <div class="card-title">Speedup (Conv/Opt)</div>
        <div class="card-value">{escape(fmt_ratio(speedup))}</div>
      </article>
    </div>

    <section class="section">
      <h2>Implementation Runtime Totals</h2>
      {render_bar_rows(impl_bars, "impl-bar")}
    </section>

    <section class="section">
      <h2>Symbolic Runtime by Design</h2>
      {render_bar_rows(design_rows, "spec-bar")}
    </section>

    <section class="section">
      <h2>Rule Application Counts</h2>
      <table>
        <thead><tr><th>Rule</th><th>Count</th></tr></thead>
        <tbody>
          {"".join(rule_rows_html)}
        </tbody>
      </table>
    </section>
  </main>
</body>
</html>
"""


def main() -> None:
    args = parse_args()
    report_dir = Path(args.report_dir)
    report_path = report_dir / "report.json"
    html_path = report_dir / "index.html"

    report = load_report(report_path)
    html = build_html(report, report_path)
    html_path.write_text(html, encoding="utf-8")
    print(f"Generated {html_path}")


if __name__ == "__main__":
    main()
