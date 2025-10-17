#!/usr/bin/env bash

check_c_style() {
	printf "checking c++ style... "
	if [[ -z "$(command -v "$1")" ]]; then
		echo "error: $1 not found"
		echo "please install clang-format for formatting"
		return 1
	fi

	find src -type f -regex ".*\.\(cpp\|hpp\)" -print0 | xargs -0 -P"$(nproc)" -n2 "$1" -n -Werror &>> clang-format.log

	rc=0
	if grep -q "error" clang-format.log; then
		printf "ERROR\n"
		echo ""
		cat clang-format.log
		rc=1
	else
		printf "OK\n"
	fi

	rm clang-format.log

	return $rc
}

check_cppcheck() {
	printf "checking cppcheck... "
	if [[ -z "$(command -v "$1")" ]]; then
		echo "error: $1 not found"
		return 1	
	fi

	rc=0

	if $1 --enable=warning,performance,style,information,portability --suppress=missingInclude --suppress=missingIncludeSystem --suppress=normalCheckLevelMaxBranches --suppress=unmatchedSuppression --suppress=checkersReport --error-exitcode=1 --quiet -j "$(nproc)" src &> cppcheck.log; then
		printf "OK\n"
	else
		printf "ERROR\n"
		cat cppcheck.log
		rc=1
	fi

	rm cppcheck.log
	
	return $rc
}

CLANG_FORMAT_BIN="${CLANG_FORMAT_BIN:-"clang-format"}"
CPPCHECK_BIN="${CPPCHECK_BIN:-"cppcheck"}"

check_c_style "$CLANG_FORMAT_BIN" || exit 1
check_cppcheck "$CPPCHECK_BIN" || exit 1
