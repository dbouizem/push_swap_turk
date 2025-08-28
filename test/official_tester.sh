#!/bin/bash

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
NC='\033[0m'

# Point counters
TOTAL_POINTS=0
MAX_POINTS=125

# Utility functions
print_header() {
	echo -e "\n${BLUE}================================================================${NC}"
	echo -e "${BLUE}$1${NC}"
	echo -e "${BLUE}================================================================${NC}"
}

print_test() {
	echo -e "${CYAN}Test: $1${NC}"
}

print_result() {
	if [ $1 -eq 1 ]; then
		echo -e "${GREEN}SUCCESS${NC}"
	else
		echo -e "${RED}FAILED${NC}"
	fi
}

add_points() {
	TOTAL_POINTS=$((TOTAL_POINTS + $1))
	echo -e "${PURPLE}Points added: +$1 (Total: $TOTAL_POINTS/$MAX_POINTS)${NC}"
}

# Binary verification
check_binaries() {
	print_header "BINARY VERIFICATION"

	if [ ! -f "./push_swap" ]; then
		echo -e "${RED}push_swap missing! Compile with 'make'${NC}"
		exit 1
	fi

	if [ ! -f "./checker_linux" ]; then
		echo -e "${YELLOW}Downloading checker_linux...${NC}"
		if command -v wget >/dev/null 2>&1; then
			wget -q https://cdn.intra.42.fr/document/document/3516/checker_linux 2>/dev/null
		elif command -v curl >/dev/null 2>&1; then
			curl -s -o checker_linux https://cdn.intra.42.fr/document/document/3516/checker_linux
		else
			echo -e "${RED}Neither wget nor curl available for download${NC}"
			echo -e "${YELLOW}Please place checker_linux manually in the directory${NC}"
			exit 1
		fi

		if [ -f "./checker_linux" ]; then
			chmod +x checker_linux
		else
			echo -e "${RED}Cannot download checker_linux${NC}"
			echo -e "${YELLOW}Please place checker_linux manually in the directory${NC}"
			exit 1
		fi
	fi

	# Verify checker_linux is executable
	if [ ! -x "./checker_linux" ]; then
		chmod +x checker_linux
	fi

	echo -e "${GREEN}All binaries are present${NC}"
}

# Enhanced error management test
test_error_management() {
	print_header "SECTION 1: ERROR MANAGEMENT"
	local success=1
	local temp_file="/tmp/push_swap_test_$$"

	print_test "Non-numeric parameters"
	./push_swap abc > "$temp_file" 2>&1
	result=$(cat "$temp_file")
	if [[ "$result" == "Error" ]]; then
		print_result 1
	else
		echo -e "${YELLOW}Output: '$result' (expected: 'Error')${NC}"
		print_result 0
		success=0
	fi

	print_test "Duplicate parameters"
	./push_swap 1 2 2 3 > "$temp_file" 2>&1
	result=$(cat "$temp_file")
	if [[ "$result" == "Error" ]]; then
		print_result 1
	else
		echo -e "${YELLOW}Output: '$result' (expected: 'Error')${NC}"
		print_result 0
		success=0
	fi

	print_test "Number > INT_MAX"
	./push_swap 2147483648 > "$temp_file" 2>&1
	result=$(cat "$temp_file")
	if [[ "$result" == "Error" ]]; then
		print_result 1
	else
		echo -e "${YELLOW}Output: '$result' (expected: 'Error')${NC}"
		print_result 0
		success=0
	fi

	print_test "Number < INT_MIN"
	./push_swap -2147483649 > "$temp_file" 2>&1
	result=$(cat "$temp_file")
	if [[ "$result" == "Error" ]]; then
		print_result 1
	else
		echo -e "${YELLOW}Output: '$result' (expected: 'Error')${NC}"
		print_result 0
		success=0
	fi

	# CORRECTION: Test des paramètres vides
	print_test "Empty string parameter"
	./push_swap "" > "$temp_file" 2>&1
	result=$(cat "$temp_file")
	if [[ "$result" == "Error" ]] || [[ "$result" == "" ]]; then
		print_result 1
	else
		echo -e "${YELLOW}Output: '$result' (expected: 'Error' or empty)${NC}"
		print_result 0
		success=0
	fi

	# CORRECTION: Test sans paramètres
	print_test "No parameters"
	./push_swap > "$temp_file" 2>&1
	exit_code=$?
	result=$(cat "$temp_file")
	if [[ "$result" == "" ]] && [[ $exit_code -eq 0 ]]; then
		print_result 1
	else
		echo -e "${YELLOW}Output: '$result', Exit code: $exit_code (expected: empty output, exit 0)${NC}"
		print_result 0
		success=0
	fi

	# CORRECTION: Test avec caractères invalides dans une chaîne
	print_test "String with invalid characters"
	./push_swap "1 2a 3" > "$temp_file" 2>&1
	result=$(cat "$temp_file")
	if [[ "$result" == "Error" ]]; then
		print_result 1
	else
		echo -e "${YELLOW}Output: '$result' (expected: 'Error')${NC}"
		print_result 0
		success=0
	fi

	# CORRECTION: Test avec des espaces multiples
	print_test "Multiple spaces between numbers"
	./push_swap "1  2   3" > "$temp_file" 2>&1
	result=$(cat "$temp_file")
	# Ce test devrait réussir si le parsing gère les espaces multiples
	if [[ "$result" == "" ]] || [[ "$result" == "sa"* ]] || [[ "$result" == "ra"* ]] || [[ "$result" == "pb"* ]]; then
		print_result 1
	else
		echo -e "${YELLOW}Output: '$result' (should handle multiple spaces)${NC}"
		print_result 0
		success=0
	fi

	# Test avec signe plus
	print_test "Numbers with plus sign"
	./push_swap "+42" "+1" "+3" > "$temp_file" 2>&1
	result=$(cat "$temp_file")
	# Ce test devrait réussir si le parsing gère les signes +
	if [[ "$result" == "" ]] || [[ "$result" == "sa"* ]] || [[ "$result" == "ra"* ]] || [[ "$result" == "pb"* ]]; then
		print_result 1
	else
		echo -e "${YELLOW}Output: '$result' (should handle + signs)${NC}"
		print_result 0
		success=0
	fi

	rm -f "$temp_file"

	if [ $success -eq 1 ]; then
		add_points 25
		return 1
	else
		echo -e "${RED}Section failed - 0 points${NC}"
		return 0
	fi
}

# Enhanced identity test
test_identity() {
	print_header "SECTION 2: IDENTITY TEST"
	local success=1

	print_test "Single element: ./push_swap 42"
	result=$(./push_swap 42 2>/dev/null)
	if [[ "$result" == "" ]]; then
		print_result 1
	else
		echo -e "${YELLOW}Output: '$result' (expected: empty)${NC}"
		print_result 0
		success=0
	fi

	print_test "Already sorted (3 elements): ./push_swap 0 1 2"
	result=$(./push_swap 0 1 2 2>/dev/null)
	if [[ "$result" == "" ]]; then
		print_result 1
	else
		echo -e "${YELLOW}Output: '$result' (expected: empty)${NC}"
		print_result 0
		success=0
	fi

	print_test "Already sorted (5 elements): ./push_swap 1 2 3 4 5"
	result=$(./push_swap 1 2 3 4 5 2>/dev/null)
	if [[ "$result" == "" ]]; then
		print_result 1
	else
		echo -e "${YELLOW}Output: '$result' (expected: empty)${NC}"
		print_result 0
		success=0
	fi

	print_test "Already sorted (10 elements): ./push_swap 0 1 2 3 4 5 6 7 8 9"
	result=$(./push_swap 0 1 2 3 4 5 6 7 8 9 2>/dev/null)
	if [[ "$result" == "" ]]; then
		print_result 1
	else
		echo -e "${YELLOW}Output: '$result' (expected: empty)${NC}"
		print_result 0
		success=0
	fi

	print_test "Already sorted with negatives: ./push_swap -5 -2 0 3 7"
	result=$(./push_swap -5 -2 0 3 7 2>/dev/null)
	if [[ "$result" == "" ]]; then
		print_result 1
	else
		echo -e "${YELLOW}Output: '$result' (expected: empty)${NC}"
		print_result 0
		success=0
	fi

	# CORRECTION: Test avec deux éléments identiques mais déjà triés
	print_test "Two different elements already sorted: ./push_swap 1 2"
	result=$(./push_swap 1 2 2>/dev/null)
	if [[ "$result" == "" ]]; then
		print_result 1
	else
		echo -e "${YELLOW}Output: '$result' (expected: empty)${NC}"
		print_result 0
		success=0
	fi

	if [ $success -eq 1 ]; then
		add_points 25
		return 1
	else
		echo -e "${RED}Section failed - 0 points${NC}"
		return 0
	fi
}

# Enhanced simple version test
test_simple_version() {
	print_header "SECTION 3: SIMPLE VERSION"

	print_test "Test ARG=\"2 1 0\""
	ARG="2 1 0"

	# Check if sorting works
	result=$(./push_swap $ARG 2>/dev/null | ./checker_linux $ARG 2>/dev/null)
	operations=$(./push_swap $ARG 2>/dev/null | wc -l)

	echo "Checker result: $result"
	echo "Number of operations: $operations (max: 3)"

	if [[ "$result" == "OK" ]] && [[ $operations -le 3 ]]; then
		print_result 1
		add_points 25
		return 1
	else
		print_result 0
		echo -e "${RED}Section failed - 0 points${NC}"
		if [[ "$result" != "OK" ]]; then
			echo -e "${RED}Sorting doesn't work correctly${NC}"
		fi
		if [[ $operations -gt 3 ]]; then
			echo -e "${RED}Too many operations: $operations (max: 3)${NC}"
		fi
		return 0
	fi
}

# Enhanced another simple test
test_another_simple() {
	print_header "SECTION 4: ANOTHER SIMPLE VERSION"
	local success=1

	print_test "Test ARG=\"1 5 2 4 3\""
	ARG="1 5 2 4 3"
	result=$(./push_swap $ARG 2>/dev/null | ./checker_linux $ARG 2>/dev/null)
	operations=$(./push_swap $ARG 2>/dev/null | wc -l)

	echo "Checker result: $result"
	echo "Number of operations: $operations (max: 12)"

	if [[ "$result" == "OK" ]] && [[ $operations -le 12 ]]; then
		print_result 1
	else
		print_result 0
		success=0
		if [[ "$result" != "OK" ]]; then
			echo -e "${RED}Sorting doesn't work${NC}"
		fi
		if [[ $operations -gt 12 ]]; then
			echo -e "${RED}Too many operations: $operations (max: 12)${NC}"
		fi
	fi

	print_test "Test with 5 random values (5 attempts)"
	local random_success=0
	for i in {1..5}; do
		# CORRECTION: Utiliser des valeurs distinctes
		ARG=$(shuf -i 0-100 -n 5 | sort -u | head -5 | paste -sd' ' -)
		# Vérifier qu'on a bien 5 valeurs distinctes
		count=$(echo $ARG | wc -w)
		if [ $count -lt 5 ]; then
			# Régénérer si on n'a pas 5 valeurs distinctes
			ARG=$(shuf -i 0-1000 -n 5 | paste -sd' ' -)
		fi

		result=$(./push_swap $ARG 2>/dev/null | ./checker_linux $ARG 2>/dev/null)
		operations=$(./push_swap $ARG 2>/dev/null | wc -l)

		echo "Attempt $i: $ARG"
		echo "Result: $result, Operations: $operations"

		if [[ "$result" == "OK" ]] && [[ $operations -le 12 ]]; then
			random_success=$((random_success + 1))
		fi
	done

	echo "Successful attempts: $random_success/5"
	if [ $random_success -ge 4 ]; then
		print_result 1
	else
		print_result 0
		success=0
	fi

	if [ $success -eq 1 ]; then
		add_points 25
		return 1
	else
		echo -e "${RED}Section failed - 0 points${NC}"
		return 0
	fi
}

# Enhanced middle version test
test_middle_version() {
	print_header "SECTION 5: MIDDLE VERSION (100 values)"

	local total_score=0
	local tests=5
	local failed_tests=0

	for i in $(seq 1 $tests); do
		# CORRECTION: S'assurer que les valeurs sont uniques
		ARG=$(shuf -i 0-1000 -n 100 | sort -u | head -100 | paste -sd' ' -)
		echo "Test $i/$tests..."

		# CORRECTION: Vérifier le timeout plus clairement
		timeout 30s ./push_swap $ARG > /tmp/push_swap_output_$$ 2>/dev/null
		if [ $? -eq 124 ]; then
			echo -e "${RED}Timeout! Algorithm too slow${NC}"
			failed_tests=$((failed_tests + 1))
			rm -f /tmp/push_swap_output_$$
			continue
		fi

		result=$(cat /tmp/push_swap_output_$$ | ./checker_linux $ARG 2>/dev/null)
		operations=$(cat /tmp/push_swap_output_$$ | wc -l)
		rm -f /tmp/push_swap_output_$$

		echo "Operations: $operations"

		if [[ "$result" != "OK" ]]; then
			echo -e "${RED}Sorting failed!${NC}"
			failed_tests=$((failed_tests + 1))
			continue
		fi

		local score=0
		if [ $operations -lt 700 ]; then
			score=5
		elif [ $operations -lt 900 ]; then
			score=4
		elif [ $operations -lt 1100 ]; then
			score=3
		elif [ $operations -lt 1300 ]; then
			score=2
		elif [ $operations -lt 1500 ]; then
			score=1
		fi

		total_score=$((total_score + score))
		echo "Score for this test: $score/5"
	done

	if [ $failed_tests -gt 0 ]; then
		echo -e "${RED}$failed_tests tests failed - Section failed${NC}"
		return 0
	fi

	local average=$((total_score / tests))
	echo -e "${BLUE}Average score: $average/5${NC}"

	add_points $((average * 5))
	return 1
}

# Enhanced advanced version test
test_advanced_version() {
	print_header "SECTION 6: ADVANCED VERSION (500 values)"

	local total_score=0
	local tests=3
	local failed_tests=0

	for i in $(seq 1 $tests); do
		# CORRECTION: S'assurer que les valeurs sont uniques
		ARG=$(shuf -i 0-5000 -n 500 | sort -u | head -500 | paste -sd' ' -)
		echo "Test $i/$tests... (may take time)"

		# CORRECTION: Améliorer la gestion du timeout
		timeout 60s ./push_swap $ARG > /tmp/push_swap_output_$$ 2>/dev/null
		timeout_status=$?

		if [ $timeout_status -eq 124 ]; then
			echo -e "${RED}Timeout! Algorithm too slow for 500 elements${NC}"
			failed_tests=$((failed_tests + 1))
			rm -f /tmp/push_swap_output_$$
			continue
		fi

		result=$(cat /tmp/push_swap_output_$$ | ./checker_linux $ARG 2>/dev/null)
		operations=$(cat /tmp/push_swap_output_$$ | wc -l)
		rm -f /tmp/push_swap_output_$$

		echo "Operations: $operations"

		if [[ "$result" != "OK" ]]; then
			echo -e "${RED}Sorting failed!${NC}"
			failed_tests=$((failed_tests + 1))
			continue
		fi

		local score=0
		if [ $operations -lt 5500 ]; then
			score=5
		elif [ $operations -lt 7000 ]; then
			score=4
		elif [ $operations -lt 8500 ]; then
			score=3
		elif [ $operations -lt 10000 ]; then
			score=2
		elif [ $operations -lt 11500 ]; then
			score=1
		fi

		total_score=$((total_score + score))
		echo "Score for this test: $score/5"
	done

	if [ $failed_tests -gt 0 ]; then
		echo -e "${RED}$failed_tests tests failed - Section failed${NC}"
		return 0
	fi

	local average=$((total_score / tests))
	echo -e "${BLUE}Average score: $average/5${NC}"

	add_points $((average * 5))
	return 1
}

# Enhanced bonus tests
test_bonus() {
	print_header "SECTION BONUS: CHECKER"

	if [ ! -f "./checker" ]; then
		echo -e "${YELLOW}No bonus checker found${NC}"
		return 0
	fi

	local bonus_success=1

	# Checker error management test
	print_test "Checker - error management"

	error1=$(./checker abc 2>&1)
	error2=$(./checker 1 2 2 2>&1)
	error3=$(echo "invalid" | ./checker 1 2 2>&1)

	if [[ "$error1" == "Error" ]]; then
		echo "Invalid parameter: OK"
	else
		echo -e "${RED}Invalid parameter: '$error1' (expected: Error)${NC}"
		bonus_success=0
	fi

	if [[ "$error2" == "Error" ]]; then
		echo "Duplicates: OK"
	else
		echo -e "${RED}Duplicates: '$error2' (expected: Error)${NC}"
		bonus_success=0
	fi

	if [[ "$error3" == "Error" ]]; then
		echo "Invalid instruction: OK"
	else
		echo -e "${RED}Invalid instruction: '$error3' (expected: Error)${NC}"
		bonus_success=0
	fi

	# Checker functional test
	print_test "Checker - functional tests"

	ok_test=$(echo "" | ./checker 0 1 2 2>/dev/null)
	ko_test=$(echo "sa" | ./checker 0 9 1 8 2 7 3 6 4 5 2>/dev/null)
	combo_test=$(./push_swap 3 2 1 2>/dev/null | ./checker 3 2 1 2>/dev/null)

	if [[ "$ok_test" == "OK" ]]; then
		echo "Sorted list: OK"
	else
		echo -e "${RED}Sorted list: '$ok_test' (expected: OK)${NC}"
		bonus_success=0
	fi

	if [[ "$ko_test" == "KO" ]]; then
		echo "Unsorted list: KO (correct)"
	else
		echo -e "${RED}Unsorted list: '$ko_test' (expected: KO)${NC}"
		bonus_success=0
	fi

	if [[ "$combo_test" == "OK" ]]; then
		echo "push_swap + checker combo: OK"
	else
		echo -e "${RED}Combo: '$combo_test' (expected: OK)${NC}"
		bonus_success=0
	fi

	if [ $bonus_success -eq 1 ]; then
		echo -e "${GREEN}Bonus successful!${NC}"
		add_points 25
	else
		echo -e "${YELLOW}Partial bonus or failed${NC}"
	fi
}

# Main function
main() {
	echo -e "${PURPLE}================================================================${NC}"
	echo -e "${PURPLE}        OFFICIAL PUSH_SWAP TESTER - TARGET 125/125${NC}"
	echo -e "${PURPLE}================================================================${NC}"

	check_binaries

	# Mandatory tests
	test_error_management
	test_identity
	test_simple_version
	test_another_simple
	test_middle_version
	test_advanced_version

	# Bonus tests (if mandatory part is excellent)
	if [ $TOTAL_POINTS -ge 100 ]; then
		test_bonus
	else
		echo -e "${YELLOW}Mandatory part insufficient for bonus (need 100+ points)${NC}"
	fi

	# Final result
	print_header "FINAL RESULT"
	echo -e "${PURPLE}Total score: $TOTAL_POINTS/$MAX_POINTS${NC}"

	if [ $TOTAL_POINTS -eq 125 ]; then
		echo -e "${GREEN}PERFECT! 125/125!${NC}"
		echo -e "${GREEN}Your push_swap is ready for defense!${NC}"
	elif [ $TOTAL_POINTS -ge 100 ]; then
		echo -e "${BLUE}Very good! Mandatory part validated${NC}"
		echo -e "${BLUE}Excellent score for mandatory part${NC}"
	elif [ $TOTAL_POINTS -ge 75 ]; then
		echo -e "${YELLOW}Correct but can be improved${NC}"
		echo -e "${YELLOW}Improve your algorithm's efficiency${NC}"
	else
		echo -e "${RED}Insufficient - Revision needed${NC}"
		echo -e "${RED}Fix basic errors before optimizing${NC}"
	fi

	# Advice based on score
	if [ $TOTAL_POINTS -lt 50 ]; then
		echo -e "\n${YELLOW}Advice:${NC}"
		echo -e "${YELLOW}- Check your error management${NC}"
		echo -e "${YELLOW}- Make sure sorting works${NC}"
		echo -e "${YELLOW}- Test with valgrind for memory leaks${NC}"
	elif [ $TOTAL_POINTS -lt 100 ]; then
		echo -e "\n${YELLOW}Advice:${NC}"
		echo -e "${YELLOW}- Optimize your algorithm for large lists${NC}"
		echo -e "${YELLOW}- Implement Turk algorithm or radix sort${NC}"
		echo -e "${YELLOW}- Test with complex edge cases${NC}"
	fi
}

# Argument verification
if [ "$1" = "--help" ] || [ "$1" = "-h" ]; then
	echo "Usage: $0 [options]"
	echo "Options:"
	echo "  --help, -h    Display this help"
	echo ""
	echo "This script tests your push_swap according to 42's official criteria."
	echo "It checks errors, performance and functionality."
	exit 0
fi

# Signal handling for cleanup
trap 'echo -e "\n${RED}Test interrupted${NC}"; rm -f /tmp/push_swap_*_$$; exit 1' INT TERM

# Execution
main
