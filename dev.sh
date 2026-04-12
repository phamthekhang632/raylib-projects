#!/bin/bash
set -e

# ── colors ──────────────────────────────────────────────────────────────────
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# ── config ───────────────────────────────────────────────────────────────────
BUILD_DIR="build"
SRC_DIR="src"
BINARY="raylib_project"

# ── helpers ──────────────────────────────────────────────────────────────────
log()  { echo -e "${CYAN}[dev]${NC} $1"; }
ok()   { echo -e "${GREEN}[ok]${NC} $1"; }
warn() { echo -e "${YELLOW}[warn]${NC} $1"; }
fail() { echo -e "${RED}[fail]${NC} $1"; exit 1; }

# ── usage ────────────────────────────────────────────────────────────────────
usage() {
  echo ""
  echo "  Usage: ./dev.sh [command]"
  echo ""
  echo "  Commands:"
  echo "    setup     Configure CMake and generate compile_commands.json"
  echo "    lint      Run clang-tidy on all source files"
  echo "    fix       Run clang-tidy and auto-fix issues"
  echo "    build     Build the project"
  echo "    run       Build and run the game"
  echo "    clean     Delete the build directory"
  echo "    all       setup + lint + build + run"
  echo ""
}

# ── commands ─────────────────────────────────────────────────────────────────
cmd_setup() {
  log "Configuring CMake..."
  cmake -B "$BUILD_DIR" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
  ok "Done — compile_commands.json generated in $BUILD_DIR/"
}

cmd_lint() {
  [ -f "$BUILD_DIR/compile_commands.json" ] || fail "No compile_commands.json found. Run './dev.sh setup' first."
  log "Running clang-tidy..."
  run-clang-tidy -p "$BUILD_DIR" "$SRC_DIR/" && ok "No issues found!" || warn "Warnings above need attention."
}

cmd_fix() {
  [ -f "$BUILD_DIR/compile_commands.json" ] || fail "No compile_commands.json found. Run './dev.sh setup' first."
  log "Running clang-tidy with auto-fix..."
  run-clang-tidy -p "$BUILD_DIR" -fix "$SRC_DIR/"
  ok "Done — review changes with: git diff"
}

cmd_build() {
  [ -d "$BUILD_DIR" ] || fail "Build directory not found. Run './dev.sh setup' first."
  log "Building..."
  cmake --build "$BUILD_DIR" --parallel
  ok "Build complete."
}

cmd_run() {
  cmd_build
  log "Running $BINARY..."
  echo ""
  "$BUILD_DIR/$BINARY"
}

cmd_clean() {
  log "Cleaning build directory..."
  rm -rf "$BUILD_DIR"
  ok "Cleaned."
}

cmd_all() {
  cmd_setup
  cmd_lint
  cmd_build
  cmd_run
}

# ── entry point ───────────────────────────────────────────────────────────────
case "$1" in
  setup) cmd_setup ;;
  lint)  cmd_lint  ;;
  fix)   cmd_fix   ;;
  build) cmd_build ;;
  run)   cmd_run   ;;
  clean) cmd_clean ;;
  all)   cmd_all   ;;
  *)     usage     ;;
esac
