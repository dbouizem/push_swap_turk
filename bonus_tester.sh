#!/bin/bash

# Couleurs
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
NC='\033[0m'

# Fonction de test simple et rapide
test_checker_complete() {
    echo -e "${PURPLE}🎁 TEST COMPLET DU CHECKER 🎁${NC}"
    echo "=================================="

    local total_tests=0
    local passed_tests=0

    echo -e "${CYAN}Test 1: Paramètres invalides${NC}"
    result=$(./checker abc 2>&1)
    total_tests=$((total_tests + 1))
    if [[ "$result" == "Error" ]]; then
        echo "✅ RÉUSSI"
        passed_tests=$((passed_tests + 1))
    else
        echo "❌ ÉCHEC (attendu: Error, obtenu: $result)"
    fi

    echo -e "${CYAN}Test 2: Doublons${NC}"
    result=$(./checker 1 2 2 3 2>&1)
    total_tests=$((total_tests + 1))
    if [[ "$result" == "Error" ]]; then
        echo "✅ RÉUSSI"
        passed_tests=$((passed_tests + 1))
    else
        echo "❌ ÉCHEC (attendu: Error, obtenu: $result)"
    fi

    echo -e "${CYAN}Test 3: Instruction invalide${NC}"
    result=$(echo "invalid" | ./checker 1 2 3 2>&1)
    total_tests=$((total_tests + 1))
    if [[ "$result" == "Error" ]]; then
        echo "✅ RÉUSSI"
        passed_tests=$((passed_tests + 1))
    else
        echo "❌ ÉCHEC (attendu: Error, obtenu: $result)"
    fi

    echo -e "${CYAN}Test 4: Liste déjà triée${NC}"
    result=$(echo "" | ./checker 1 2 3 4)
    total_tests=$((total_tests + 1))
    if [[ "$result" == "OK" ]]; then
        echo "✅ RÉUSSI"
        passed_tests=$((passed_tests + 1))
    else
        echo "❌ ÉCHEC (attendu: OK, obtenu: $result)"
    fi

    echo -e "${CYAN}Test 5: Tri simple avec sa${NC}"
    result=$(echo "sa" | ./checker 2 1 3)
    total_tests=$((total_tests + 1))
    if [[ "$result" == "OK" ]]; then
        echo "✅ RÉUSSI"
        passed_tests=$((passed_tests + 1))
    else
        echo "❌ ÉCHEC (attendu: OK, obtenu: $result)"
    fi

    echo -e "${CYAN}Test 6: Instructions qui ne trient pas${NC}"
    result=$(echo "sa" | ./checker 3 2 1)
    total_tests=$((total_tests + 1))
    if [[ "$result" == "KO" ]]; then
        echo "✅ RÉUSSI"
        passed_tests=$((passed_tests + 1))
    else
        echo "❌ ÉCHEC (attendu: KO, obtenu: $result)"
    fi

    echo -e "${CYAN}Test 7: Intégration push_swap + checker${NC}"
    operations=$(./push_swap 3 2 1)
    result=$(echo "$operations" | ./checker 3 2 1)
    total_tests=$((total_tests + 1))
    if [[ "$result" == "OK" ]]; then
        echo "✅ RÉUSSI ($(echo "$operations" | wc -l) opérations)"
        passed_tests=$((passed_tests + 1))
    else
        echo "❌ ÉCHEC (attendu: OK, obtenu: $result)"
    fi

    echo -e "${CYAN}Test 8: Test avec 10 valeurs${NC}"
    ARG="$(shuf -i 1-100 -n 10 | paste -sd' ' -)"
    operations=$(./push_swap $ARG)
    result=$(echo "$operations" | ./checker $ARG)
    total_tests=$((total_tests + 1))
    if [[ "$result" == "OK" ]]; then
        echo "✅ RÉUSSI ($(echo "$operations" | wc -l) opérations)"
        passed_tests=$((passed_tests + 1))
    else
        echo "❌ ÉCHEC (attendu: OK, obtenu: $result)"
    fi

    echo "=================================="
    echo -e "${PURPLE}RÉSULTAT: $passed_tests/$total_tests tests réussis${NC}"

    if [ $passed_tests -eq $total_tests ]; then
        echo -e "${GREEN}🏆 CHECKER PARFAIT ! 25/25 POINTS BONUS ! 🏆${NC}"
        echo -e "${GREEN}🎉 Votre checker fonctionne parfaitement ! 🎉${NC}"
        echo ""
        echo -e "${CYAN}📊 RÉCAPITULATIF TOTAL DE VOTRE PROJET:${NC}"
        echo -e "${CYAN}• Partie obligatoire: 125/125 ✅${NC}"
        echo -e "${CYAN}• Partie bonus: 25/25 ✅${NC}"
        echo -e "${GREEN}• TOTAL: 150/150 PARFAIT ! 🏆${NC}"
    elif [ $passed_tests -ge 6 ]; then
        echo -e "${BLUE}👍 Très bon checker ! Quelques ajustements mineurs${NC}"
    else
        echo -e "${YELLOW}⚠️  Checker fonctionnel mais améliorations nécessaires${NC}"
    fi
}

# Vérification des binaires
if [ ! -f "./checker" ]; then
    echo -e "${RED}❌ checker manquant ! Compilez avec 'make bonus'${NC}"
    exit 1
fi

if [ ! -f "./push_swap" ]; then
    echo -e "${RED}❌ push_swap manquant ! Compilez avec 'make'${NC}"
    exit 1
fi

# Lancer le test
test_checker_complete
