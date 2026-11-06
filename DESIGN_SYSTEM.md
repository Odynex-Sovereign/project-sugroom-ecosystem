# Design System — Project SuGROOM Ecosystem

**Context:** The repository currently contains **no user interface**. This document defines the brand and interaction principles that must be followed if and when any UI, documentation site, or control-plane surface is introduced.

---

## 1. Brand positioning

**Positioning statement**  
Software-defined millimeter precision for industrial and robotic systems, achieved through biomimetic compensatory algorithms.

**Personality**  
Precise • Calm • Trustworthy • Understated • Engineering-first  

**Avoid**
- Consumer “AI dashboard” aesthetics  
- Medical or healthcare imagery that could be misread as clinical claims  
- Hype language (“revolutionary”, “automatically gains clients”, fabricated customer counts)  
- Bright, playful, or child-oriented visual language (this is an industrial product)

---

## 2. Voice & tone

- Precise and evidence-based.  
- Prefer short, concrete sentences.  
- Admit limitations clearly (simulation vs. real hardware, public vs. proprietary coefficients).  
- Never promise outcomes that the software cannot guarantee.  

Example good tone:  
> “The inverse-tremor kernel reduces high-frequency components on the supplied telemetry vector. Measured latency on a 1024-sample batch is documented in the performance appendix.”

Example bad tone:  
> “SuGROOM magically turns any cheap robot into a precision machine and will grow your business automatically.”

---

## 3. Visual foundations (for any future UI or documentation site)

### Color tokens (suggested industrial palette)

| Token | Hex (light) | Hex (dark) | Usage |
|-------|-------------|------------|-------|
| `--bg-primary` | `#F7F8FA` | `#0F1419` | Page background |
| `--bg-surface` | `#FFFFFF` | `#1A2332` | Cards, panels |
| `--text-primary` | `#0F172A` | `#E2E8F0` | Body text |
| `--text-secondary` | `#475569` | `#94A3B8` | Secondary labels |
| `--accent` | `#1E3A5F` | `#3B82F6` | Primary actions, links |
| `--success` | `#166534` | `#22C55E` | Positive status |
| `--warning` | `#92400E` | `#F59E0B` | Caution |
| `--danger` | `#991B1B` | `#EF4444` | Errors, export-control blocks |
| `--border` | `#E2E8F0` | `#334155` | Dividers |

High contrast is mandatory. All interactive elements must meet WCAG 2.2 AA.

### Typography

- Prefer system or open industrial fonts (Inter, IBM Plex Sans, or equivalent).  
- Body: 16 px / 1.5 line-height minimum.  
- Monospace for code, telemetry values, and latency numbers.  
- No decorative display fonts.

### Spacing & layout

- 4 px base unit.  
- Comfortable density for engineering dashboards; avoid cramped consumer-app layouts.  
- Clear visual hierarchy: page title → section → data.

---

## 4. Component principles (future UI)

- **Empty states:** Explain what data is missing and the single next action.  
- **Error states:** Non-blaming, actionable recovery steps. Never hide export-control or safety blocks.  
- **Loading:** Prefer skeleton or determinate progress over indefinite spinners for long kernel runs.  
- **Forms:** Explicit labels, client + server validation, no dark patterns.  
- **Tables / telemetry views:** Sortable, filterable, keyboard accessible, exportable.

---

## 5. Accessibility standard

**Target:** WCAG 2.2 AA  

Required from day one of any UI:
- Keyboard-only operation  
- Visible focus indicators  
- Sufficient color contrast  
- Screen-reader labels for all controls  
- Captions / transcripts for any video  
- Clear language; avoid jargon without definition  

---

## 6. Information architecture (documentation site, if built)

```
/                    → Product overview + quick start
/docs/engines        → Per-engine reference
/docs/api            → C / C++ / Python API
/docs/performance    → Latency & memory numbers
/docs/compliance     → Export-control & safety
/docs/deploy         → Docker, Jetson, air-gapped
/license             → How to request commercial terms
```

No public “customer logos” or fabricated metrics.

---

## 7. Explicit non-goals for visual design

- Any surface that targets children or teenagers as primary users.  
- Social feeds, public profiles, or discovery features.  
- Gamification that encourages endless engagement.  
- Dark patterns around upgrades or data collection.

If an educational experience is ever desired, it must live in a separate product with its own design system, age gates, and privacy review.
