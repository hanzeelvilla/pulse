# Roadmap

Incremental plan to rebuild Pulse into a web-controlled, multi-screen LED display.

## Architecture

- **Firmware (this repo)**: ESP32 + MAX7219 matrix. Connects out to the backend as a WebSocket client. Stays "dumb" — just renders whatever the backend sends, no direct calls to external APIs.
- **Backend**: NestJS server with a WebSocket Gateway. Acts as the single intermediary between the frontend(s) and the device, and owns all external API calls (Spotify, GitHub) — keeps secrets server-side and the device/frontend simple. Supports multiple frontend clients connected at once: a change from any one of them is broadcast to the `/frontend` namespace (not just echoed back to the sender), so every connected frontend stays in sync.
- **Persistence**: SQLite via TypeORM. Only for data that must survive a restart — device pairing/credentials and the Spotify refresh token. Everything else (active screen, timer/pomodoro state, GitHub cache) stays in memory.
- **Frontend**: [pulse-frontend](https://github.com/hanzeelvilla/pulse-frontend) (React + Vite). Talks only to the backend via WebSocket (`socket.io-client`), never directly to the device or to external APIs.

## Phases

- [x] **Phase 0 — Firmware reset**: minimal "Hello World" scroll sketch, docs rewritten.
- [x] **Phase 1 — Firmware: basic connectivity**: WiFi on the ESP32, auto-reconnect, serial logging of status/IP. No networking features yet.
- [x] **Phase 2 — Firmware: screen abstraction**: introduce a `Screen` interface, refactor the current scroll sketch into the first real screen: **Free Text**. Still fully local.
- [x] **Phase 3 — Backend: NestJS skeleton with Gateway**: NestJS project with a `WebSocketGateway`. Separate device vs. frontend clients from the start (e.g. namespaces `/device` and `/frontend`). One event ("set free text"), in-memory state. No Spotify/GitHub yet.
- [ ] **Phase 4 — Firmware ↔ Backend: first end-to-end loop**: ESP32 connects to the Gateway as a WebSocket client and displays the text it receives.
- [ ] **Phase 5 — Frontend: first vertical slice**: React+Vite app with `socket.io-client` connected to the Gateway. Free text input → full loop: frontend → backend → ESP32 → display.
- [ ] **Phase 6 — Device identity**: pairing/API key (or JWT) so the Gateway knows which device is which, and the `/device` namespace isn't open to anyone. Introduce SQLite + TypeORM here to persist device credentials. Needed before exposing the backend outside the local network.
- [ ] **Phase 7 — Screen switching**: "active screen" modeled in the backend, switch UI in the frontend, screen-change handling in firmware. Second screen: **Clock** (no external dependencies).
- [ ] **Phase 8 — Interactive screens**: **Timer/Stopwatch** and **Pomodoro** — commands (start/stop/reset) over the same Gateway, not just static content.
- [ ] **Phase 9 — External integrations (NestJS modules)**: `SpotifyModule` (OAuth/refresh + polling, secret stays server-side, refresh token persisted in SQLite) and `GithubModule` (fetch/cache contributions, in-memory cache), each pushing content to the ESP32 through the Gateway when their screen is active.
- [ ] **Phase 10 — Remaining screens + deployment**: **Days until payday** screen, real deployment of backend and frontend, robust reconnection handling, brightness control from the web.
