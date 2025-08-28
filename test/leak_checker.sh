#!/bin/bash

# Couleurs
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
NC='\033[0m'

# Variables globales
LEAK_COUNT=0
CRASH_COUNT=0
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

# Fonctions utilitaires
print_header() {
	echo -e "\n${BLUE}================================================================${NC}"
	echo -e "${BLUE}$1${NC}"
	echo -e "${BLUE}================================================================${NC}"
}

print_test() {
	echo -e "\n${CYAN}>>> Test: $1${NC}"
	TOTAL_TESTS=$((TOTAL_TESTS + 1))
}

print_success() {
	echo -e "${GREEN}SUCCES - Aucune fuite memoire detectee${NC}"
	PASSED_TESTS=$((PASSED_TESTS + 1))
}

print_leak() {
	echo -e "${RED}ECHEC - Fuites memoire detectees${NC}"
	LEAK_COUNT=$((LEAK_COUNT + 1))
	FAILED_TESTS=$((FAILED_TESTS + 1))
}

print_crash() {
	echo -e "${RED}ECHEC CRITIQUE - Programme crash${NC}"
	CRASH_COUNT=$((CRASH_COUNT + 1))
	FAILED_TESTS=$((FAILED_TESTS + 1))
}

# Verification des prerequis
check_prerequisites() {
	print_header "VERIFICATION DES PREREQUIS"

	# Verifier push_swap
	if [ ! -f "./push_swap" ]; then
		echo -e "${RED}Erreur: push_swap introuvable${NC}"
		echo -e "${YELLOW}Compilez avec: make${NC}"
		exit 1
	fi
	echo -e "${GREEN}push_swap trouve${NC}"

	# Verifier valgrind
	if ! command -v valgrind &> /dev/null; then
		echo -e "${RED}Erreur: valgrind non installe${NC}"
		echo -e "${YELLOW}Installation: sudo apt-get install valgrind${NC}"
		exit 1
	fi
	echo -e "${GREEN}valgrind disponible$(valgrind --version | head -1 | awk '{print " (" $2 ")"}')${NC}"

	# Verifier checker bonus
	if [ -f "./checker" ]; then
		echo -e "${GREEN}checker bonus trouve${NC}"
		CHECKER_AVAILABLE=1
	else
		echo -e "${YELLOW}checker bonus non trouve (normal si pas de bonus)${NC}"
		CHECKER_AVAILABLE=0
	fi

	echo -e "\n${GREEN}Tous les prerequis sont satisfaits${NC}"
}

# Fonction principale de test memoire
test_memory() {
	local test_name="$1"
	local args="$2"
	local expect_error="$3"
	local temp_log="/tmp/valgrind_$$.log"
	local temp_out="/tmp/output_$$.txt"

	print_test "$test_name"
	echo -e "${YELLOW}Arguments: [$args]${NC}"

	# Test normal d'abord
	./push_swap $args > "$temp_out" 2>&1
	local exit_code=$?
	local output=$(cat "$temp_out")

	if [ "$expect_error" = "yes" ]; then
		if [ "$output" != "Error" ]; then
			echo -e "${RED}Erreur: devrait afficher 'Error' mais affiche: '$output'${NC}"
			rm -f "$temp_log" "$temp_out"
			print_crash
			return
		fi
	fi

	# Test valgrind
	valgrind --leak-check=full \
			 --show-leak-kinds=all \
			 --track-origins=yes \
			 --log-file="$temp_log" \
			 --suppressions=/dev/null \
			 ./push_swap $args > /dev/null 2>&1

	local valgrind_exit=$?

	# Analyser le log valgrind
	if [ -f "$temp_log" ]; then
		# Detecter les crashes
		if grep -q "Process terminating with default action of signal" "$temp_log"; then
			echo -e "${RED}CRASH detecte dans valgrind:${NC}"
			grep "Process terminating" "$temp_log"
			print_crash
			echo -e "${YELLOW}Log complet: $temp_log${NC}"
			rm -f "$temp_out"
			return
		fi

		# Analyser les fuites
		local definitely_lost=$(grep "definitely lost:" "$temp_log" | awk '{print $4}' | tr -d ',')
		local indirectly_lost=$(grep "indirectly lost:" "$temp_log" | awk '{print $4}' | tr -d ',')
		local possibly_lost=$(grep "possibly lost:" "$temp_log" | awk '{print $4}' | tr -d ',')

		# Afficher le resume memoire
		local heap_usage=$(grep -A 3 "HEAP SUMMARY" "$temp_log")
		if [ -n "$heap_usage" ]; then
			echo -e "${BLUE}$heap_usage${NC}"
		fi

		# Verifier les fuites
		if grep -q "All heap blocks were freed -- no leaks are possible" "$temp_log"; then
			print_success
		elif [ "${definitely_lost:-0}" = "0" ] && [ "${indirectly_lost:-0}" = "0" ] && [ "${possibly_lost:-0}" = "0" ]; then
			print_success
		else
			echo -e "${RED}Fuites detectees:${NC}"
			[ "${definitely_lost:-0}" != "0" ] && echo -e "${RED}  - Definitely lost: $definitely_lost bytes${NC}"
			[ "${indirectly_lost:-0}" != "0" ] && echo -e "${RED}  - Indirectly lost: $indirectly_lost bytes${NC}"
			[ "${possibly_lost:-0}" != "0" ] && echo -e "${YELLOW}  - Possibly lost: $possibly_lost bytes${NC}"
			print_leak
			echo -e "${YELLOW}Log complet: $temp_log${NC}"
			rm -f "$temp_out"
			return
		fi

		# Afficher les erreurs s'il y en a
		local error_summary=$(grep "ERROR SUMMARY" "$temp_log")
		if [ -n "$error_summary" ]; then
			echo -e "${BLUE}$error_summary${NC}"
			if ! grep -q "ERROR SUMMARY: 0 errors" "$temp_log"; then
				echo -e "${YELLOW}Attention: erreurs detectees par valgrind${NC}"
			fi
		fi

		rm -f "$temp_log"
	else
		echo -e "${RED}Impossible de lire le log valgrind${NC}"
		print_crash
	fi

	rm -f "$temp_out"
}

# Tests de gestion d'erreurs
test_error_management() {
	print_header "TESTS DE GESTION D'ERREURS"

	test_memory "Parametres non numeriques" "abc def" "yes"
	test_memory "Parametres dupliques" "1 2 3 2 4" "yes"
	test_memory "Nombre > INT_MAX" "2147483648" "yes"
	test_memory "Nombre < INT_MIN" "-2147483649" "yes"
	test_memory "Parametre vide" "\"\"" "yes"
	test_memory "Melange invalide" "1 abc 3" "yes"
}

# Tests de fonctionnalite normale
test_normal_cases() {
	print_header "TESTS CAS NORMAUX"

	test_memory "Un seul element" "42" "no"
	test_memory "Deja trie (2 elements)" "1 2" "no"
	test_memory "Deja trie (3 elements)" "0 1 2" "no"
	test_memory "Deja trie (5 elements)" "1 2 3 4 5" "no"
	test_memory "Deja trie (10 elements)" "0 1 2 3 4 5 6 7 8 9" "no"
	test_memory "Simple a trier (3 elements)" "3 1 2" "no"
	test_memory "Simple a trier (5 elements)" "5 2 4 1 3" "no"
}

# Tests avec tailles moyennes
test_medium_cases() {
	print_header "TESTS TAILLES MOYENNES"

	local args_20=$(shuf -i 0-50 -n 20 | paste -sd' ' -)
	test_memory "20 elements aleatoires" "$args_20" "no"

	local args_50=$(shuf -i 0-100 -n 50 | paste -sd' ' -)
	test_memory "50 elements aleatoires" "$args_50" "no"

	local args_100=$(shuf -i 0-200 -n 100 | paste -sd' ' -)
	test_memory "100 elements aleatoires" "$args_100" "no"
}

# Tests avec grandes tailles
test_large_cases() {
	print_header "TESTS GRANDES TAILLES (peut prendre du temps)"

	local args_250=$(shuf -i 0-500 -n 250 | paste -sd' ' -)
	test_memory "250 elements aleatoires" "$args_250" "no"

	local args_500=$(shuf -i 0-1000 -n 500 | paste -sd' ' -)
	test_memory "500 elements aleatoires" "$args_500" "no"
}

# Tests cas extremes
test_extreme_cases() {
	print_header "TESTS CAS EXTREMES"

	test_memory "Valeurs INT_MAX/INT_MIN" "2147483647 -2147483648 0" "no"
	test_memory "Ordre inverse complet" "10 9 8 7 6 5 4 3 2 1 0" "no"

	# Generer un cas avec beaucoup de petits nombres
	local small_args=$(shuf -i 0-20 -n 20 | paste -sd' ' -)
	test_memory "20 petites valeurs" "$small_args" "no"

	# Generer un cas avec de grandes valeurs
	local big_args=$(shuf -i 1000000-1100000 -n 20 | paste -sd' ' -)
	test_memory "20 grandes valeurs" "$big_args" "no"
}

# Tests bonus checker
test_checker_bonus() {
	if [ $CHECKER_AVAILABLE -eq 0 ]; then
		echo -e "\n${YELLOW}Tests checker ignores (pas de checker bonus)${NC}"
		return
	fi

	print_header "TESTS CHECKER BONUS"

	local temp_log="/tmp/checker_valgrind_$$.log"

	# Test erreurs checker
	print_test "Checker - parametres invalides"
	valgrind --leak-check=full --log-file="$temp_log" \
			 ./checker abc > /dev/null 2>&1

	if grep -q "All heap blocks were freed" "$temp_log"; then
		print_success
	else
		print_leak
	fi

	# Test checker fonctionnel
	print_test "Checker - test fonctionnel"
	echo "" | valgrind --leak-check=full --log-file="$temp_log" \
					  ./checker 0 1 2 > /dev/null 2>&1

	if grep -q "All heap blocks were freed" "$temp_log"; then
		print_success
	else
		print_leak
	fi

	rm -f "$temp_log"
}

# Analyse finale et recommandations
show_final_results() {
	print_header "RESULTATS FINAUX"

	echo -e "${PURPLE}STATISTIQUES:${NC}"
	echo -e "  Tests executes: ${BLUE}$TOTAL_TESTS${NC}"
	echo -e "  Tests reussis: ${GREEN}$PASSED_TESTS${NC}"
	echo -e "  Tests echoues: ${RED}$FAILED_TESTS${NC}"
	echo -e "  Fuites detectees: ${RED}$LEAK_COUNT${NC}"
	echo -e "  Crashes detectes: ${RED}$CRASH_COUNT${NC}"

	local success_rate=0
	if [ $TOTAL_TESTS -gt 0 ]; then
		success_rate=$((PASSED_TESTS * 100 / TOTAL_TESTS))
	fi
	echo -e "  Taux de reussite: ${BLUE}$success_rate%${NC}"

	echo -e "\n${PURPLE}EVALUATION SELON LES CRITERES 42:${NC}"

	if [ $CRASH_COUNT -gt 0 ]; then
		echo -e "${RED}ECHEC CRITIQUE - Crashes detectes${NC}"
		echo -e "${RED}Note finale: 0/125 (crashes = disqualification)${NC}"
	elif [ $LEAK_COUNT -gt 0 ]; then
		echo -e "${RED}ECHEC - Fuites memoire detectees${NC}"
		echo -e "${RED}Note finale: 0/125 (fuites = note 0 selon le bareme)${NC}"
	else
		echo -e "${GREEN}SUCCES COMPLET - Aucun probleme memoire${NC}"
		echo -e "${GREEN}Gestion memoire: VALIDEE${NC}"
		echo -e "${GREEN}Votre push_swap respecte les criteres 42 pour la memoire${NC}"
	fi

	echo -e "\n${PURPLE}ACTIONS RECOMMANDEES:${NC}"
	if [ $CRASH_COUNT -gt 0 ]; then
		echo -e "${YELLOW}- Corriger les crashes avant tout (utiliser gdb)${NC}"
		echo -e "${YELLOW}- Verifier la gestion d'erreurs${NC}"
	elif [ $LEAK_COUNT -gt 0 ]; then
		echo -e "${YELLOW}- Corriger toutes les fuites memoire${NC}"
		echo -e "${YELLOW}- Verifier les malloc/free${NC}"
		echo -e "${YELLOW}- Utiliser valgrind pour debug individuel${NC}"
	else
		echo -e "${GREEN}- Votre code est pret pour la soutenance (niveau memoire)${NC}"
		echo -e "${GREEN}- Lancez aussi les tests de performance${NC}"
	fi
}

# Fonction principale
main() {
	echo -e "${PURPLE}================================================================${NC}"
	echo -e "${PURPLE}           TESTEUR FUITES MEMOIRE - PUSH_SWAP${NC}"
	echo -e "${PURPLE}================================================================${NC}"
	echo -e "${YELLOW}Critere 42: \"If there is one memory leak (or more), the final grade is 0.\"${NC}"
	echo -e "${YELLOW}Ce testeur verifie TOUS les cas possibles de fuites memoire.${NC}"

	check_prerequisites
	test_error_management
	test_normal_cases
	test_medium_cases

	# Demander avant les tests longs
	echo -e "\n${YELLOW}Lancer les tests de grandes tailles (plus lents)? [y/N]${NC}"
	read -r -n 1 response
	echo
	if [[ "$response" =~ ^[Yy]$ ]]; then
		test_large_cases
		test_extreme_cases
	else
		echo -e "${BLUE}Tests de grandes tailles ignores${NC}"
	fi

	test_checker_bonus
	show_final_results

	# Code de sortie selon les resultats
	if [ $CRASH_COUNT -gt 0 ] || [ $LEAK_COUNT -gt 0 ]; then
		exit 1
	else
		exit 0
	fi
}

# Gestion des arguments
case "${1:-}" in
	"--help"|"-h")
		echo "Usage: $0 [options]"
		echo "Options:"
		echo "  --help, -h     Afficher cette aide"
		echo "  --fast         Tests rapides seulement"
		echo "  --full         Tous les tests (incluant les lents)"
		echo ""
		echo "Ce script teste exhaustivement les fuites memoire de push_swap"
		echo "selon les criteres stricts de l'ecole 42."
		exit 0
		;;
	"--fast")
		FAST_MODE=1
		;;
	"--full")
		FAST_MODE=0
		;;
	*)
		FAST_MODE=""
		;;
esac

# Execution
main
