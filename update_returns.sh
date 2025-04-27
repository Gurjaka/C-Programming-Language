# !/usr/bin/env bash

# Process all C files recursively
find . -type f -name '*.c' | while read -r file; do
    echo "Processing: $file"
    modified=false

    # 1. Ensure stdlib.h is included
    if ! grep -qE '#include\s*<stdlib\.h>' "$file"; then
        awk '
        BEGIN { last_include=0 }
        /^#include/ { last_include=NR }
        { lines[NR]=$0 }
        END {
            for (i=1; i<=NR; i++) {
                print lines[i]
                if (i == last_include) {
                    print "#include <stdlib.h>"
                }
            }
        }
        ' "$file" > "$file.tmp" && mv "$file.tmp" "$file"
        modified=true
    fi

    # 2. Process the main function properly
    awk '
    BEGIN {
        in_main = 0
        brace_level = 0
        found_return = 0
    }
    {
        line = $0

        # Detect main function start (loose match)
        if (line ~ /int[[:space:]]+main[[:space:]]*\(.*\)/) {
            in_main = 1
        }

        if (in_main) {
            # Track braces
            brace_level += gsub(/\{/, "{", line)
            brace_level -= gsub(/\}/, "}", line)

            # Replace return 0 and 1
            gsub(/return[[:space:]]+0[[:space:]]*;/, "return EXIT_SUCCESS;", line)
            gsub(/return[[:space:]]+1[[:space:]]*;/, "return EXIT_FAILURE;", line)

            # Detect if already a good return
            if (line ~ /return[[:space:]]+(EXIT_SUCCESS|EXIT_FAILURE)[[:space:]]*;/) {
                found_return = 1
            }

            # If line is just a closing brace and we are at end of main without return
            if (brace_level == 0 && found_return == 0 && line ~ /^[[:space:]]*\}[[:space:]]*$/) {
                print "    return EXIT_SUCCESS;"
                found_return = 1
                in_main = 0
            }
            # If line is closing brace and found return
            else if (brace_level == 0 && found_return == 1 && line ~ /^[[:space:]]*\}[[:space:]]*$/) {
                in_main = 0
            }
        }

        print line
    }
    ' "$file" > "$file.tmp" && mv "$file.tmp" "$file"

    modified=true

    if [ "$modified" = true ]; then
        echo "Modified: $file"
    fi
done

echo ""
echo "Formatting all code with clang-format..."

# 3. clang-format everything properly
find . -type f -name '*.c' -exec clang-format -i {} +

echo "Done!"
