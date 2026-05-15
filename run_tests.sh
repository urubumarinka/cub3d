#!/usr/bin/env bash

EXEC=./cub3D
TEST_DIR=maps
OUT=maps/test_report.txt
TMPDIR=$(mktemp -d)

# create/clear report
: > "$OUT"

if [ ! -x "$EXEC" ]; then
  echo "ERROR: $EXEC not found or not executable. Run 'make' first." | tee -a "$OUT"
  exit 1
fi

success=()
failed=()
opened=()

while IFS= read -r -d '' file; do
  echo "=== $file ===" >> "$OUT"
  stdout="$TMPDIR/out.stdout"
  stderr="$TMPDIR/out.stderr"

  # Run with a short timeout so GUI-opening tests don't hang the script.
  timeout 2s "$EXEC" "$file" >"$stdout" 2>"$stderr"
  rc=$?

  if [ $rc -eq 0 ]; then
    echo "RESULT: OK (exit 0)" >> "$OUT"
    success+=("$file")
    [ -s "$stderr" ] && { echo "STDERR:" >> "$OUT"; cat "$stderr" >> "$OUT"; }
  elif [ $rc -eq 124 ] || [ $rc -eq 137 ]; then
    # 124 = GNU timeout exit code, 137 = killed after timeout (SIGKILL)
    if [ -s "$stderr" ]; then
      echo "RESULT: FAIL (timeout + error output)" >> "$OUT"
      echo "STDERR:" >> "$OUT"
      cat "$stderr" >> "$OUT"
      failed+=("$file")
    else
      echo "RESULT: OPENED (no error output, timed out)" >> "$OUT"
      opened+=("$file")
    fi
  else
    echo "RESULT: FAIL (exit $rc)" >> "$OUT"
    [ -s "$stderr" ] && { echo "STDERR:" >> "$OUT"; cat "$stderr" >> "$OUT"; }
    failed+=("$file")
  fi

  # Ensure no lingering GUI processes from this run remain.
  pkill -f "$(pwd)/cub3D" 2>/dev/null || true

  echo "" >> "$OUT"
done < <(find "$TEST_DIR" -type f -print0)

# Summary
{
  echo "SUMMARY"
  echo "Total tests: $(find "$TEST_DIR" -type f | wc -l)"
  echo ""
  echo "Succeeded (exit 0): ${#success[@]}"
  for f in "${success[@]}"; do echo " - $f"; done
  echo ""
  echo "Opened (no error, timed out): ${#opened[@]}"
  for f in "${opened[@]}"; do echo " - $f"; done
  echo ""
  echo "Failed: ${#failed[@]}"
  for f in "${failed[@]}"; do echo " - $f"; done
} >> "$OUT"

echo "Report written to $OUT"
