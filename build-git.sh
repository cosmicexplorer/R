#!/bin/sh

START_MSG="if you cancel during the make step, just run again with 'make -j\${MAKE_JOBS}'"

echo -e "\033[1;33m(${START_MSG})\033[1;0m"

set -euxo pipefail

# use $1, or default to -j2
MAKE_JOBS="${1:-2}"

SVN_REVISION_FILE='SVN-REVISION'

function get_svn_revision {
  git log --format=%B -n 1 \
    | grep '^git-svn-id'
    | sed -E 's#^git-svn-id: https://svn.r-project.org/R/[^@]*@([0-9]+).*$#\1#'
}

function get_svn_last_changed_date {
  git log -1 --pretty='format:%ad' --date=iso \
    | cut -d' ' -f1
}

# Download recommended packages
tools/rsync-recommended

./configure

make -C doc/manual \
     front-matter \
     html-non-svn

printf "Revision: %s\n" "$(get_svn_revision)" \
       > "$SVN_REVISION_FILE"

printf "Last Changed Date: %s\n" "$(get_svn_last_changed_date)" \
       >> "$SVN_REVISION_FILE"

# do the make
make -j"$MAKE_JOBS"
