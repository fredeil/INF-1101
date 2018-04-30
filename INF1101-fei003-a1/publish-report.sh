#!/bin/bash
function program_is_installed {
  # set to 1 initially
  local return_=1
  # set to 0 if not found
  type $1 >/dev/null 2>&1 || { local return_=0; }
  # return value
  echo "$return_"
}


if [ $(program_is_installed markdown-pdf) ]; then
    markdown-pdf report.md
    open report.pdf
else
    npm install -g markdown-pdf
    markdown-pdf report.md
fi
