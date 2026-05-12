#!/usr/bin/env bash

EXEC=./cub3D
TEST_DIR=tests
SUPP=mlx.supp
OUT=tests/leak_report.txt
TMPDIR=$(mktemp -d)

VALGRIND_ARGS=(
  --leak-check=full
  --show-leak-kinds=all
  --errors-for-leak-kinds=definite,possible,indirect
  --error-exitcode=99
)

if [ -f "$SUPP" ]; then
  VALGRIND_ARGS+=(--suppressions="$SUPP")
fi

cleanup() {
  pkill -f "$(pwd)/cub3D" 2>/dev/null || true
  rm -rf "$TMPDIR"
}
trap cleanup EXIT

: > "$OUT"

if [ ! -x "$EXEC" ]; then
  echo "ERROR: $EXEC not found or not executable. Run 'make' first." | tee -a "$OUT"
  exit 1
fi

passed=()
failed=()
unverified=()

while IFS= read -r -d '' file; do
  echo "=== $file ===" >> "$OUT"
  stdout="$TMPDIR/out.stdout"
  stderr="$TMPDIR/out.stderr"

  timeout 4s valgrind "${VALGRIND_ARGS[@]}" "$EXEC" "$file" >"$stdout" 2>"$stderr"
  rc=$?

  if [ $rc -eq 124 ] || [ $rc -eq 137 ]; then
    echo "RESULT: UNVERIFIED (timed out before clean exit)" >> "$OUT"
    unverified+=("$file")
  elif [ $rc -eq 99 ]; then
    echo "RESULT: FAIL (valgrind memory error/leak)" >> "$OUT"
    failed+=("$file")
  elif [ $rc -ge 128 ]; then
    echo "RESULT: FAIL (terminated by signal, exit $rc)" >> "$OUT"
    failed+=("$file")
  else
    # Non-zero app exits are expected for invalid maps; Valgrind would set rc=99 on memory issues.
    echo "RESULT: PASS (no valgrind-reported memory errors)" >> "$OUT"
    passed+=("$file")
  fi

  if [ -s "$stderr" ]; then
    echo "VALGRIND SUMMARY:" >> "$OUT"
    grep -E "HEAP SUMMARY|LEAK SUMMARY|definitely lost:|indirectly lost:|possibly lost:|ERROR SUMMARY:" "$stderr" >> "$OUT" || true
  fi

  pkill -f "$(pwd)/cub3D" 2>/dev/null || true
  echo "" >> "$OUT"
done < <(find "$TEST_DIR" -type f -name "*.cub" -print0)

{
  echo "SUMMARY"
  echo "Total .cub tests: $(find "$TEST_DIR" -type f -name "*.cub" | wc -l)"
  echo ""
  echo "Pass (no leaks): ${#passed[@]}"
  for f in "${passed[@]}"; do echo " - $f"; done
  echo ""
  echo "Unverified (timeout): ${#unverified[@]}"
  for f in "${unverified[@]}"; do echo " - $f"; done
  echo ""
  echo "Fail: ${#failed[@]}"
  for f in "${failed[@]}"; do echo " - $f"; done
} >> "$OUT"

echo "Leak report written to $OUT"
