#!/bin/bash

# Couleurs
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
NC='\033[0m'

# Compteurs de points
TOTAL_POINTS=0
MAX_POINTS=125

# Fonctions utilitaires
print_header() {
    echo -e "\n${BLUE}================================${NC}"
    echo -e "${BLUE}$1${NC}"
    echo -e "${BLUE}================================${NC}"
}

print_test() {
    echo -e "${CYAN}Test: $1${NC}"
}

print_result() {
    if [ $1 -eq 1 ]; then
        echo -e "${GREEN}✅ RÉUSSI${NC}"
    else
        echo -e "${RED}❌ ÉCHEC${NC}"
    fi
}

add_points() {
    TOTAL_POINTS=$((TOTAL_POINTS + $1))
    echo -e "${PURPLE}Points ajoutés: +$1 (Total: $TOTAL_POINTS/$MAX_POINTS)${NC}"
}

# Vérification des binaires
check_binaries() {
    print_header "VÉRIFICATION DES BINAIRES"

    if [ ! -f "./push_swap" ]; then
        echo -e "${RED}❌ push_swap manquant ! Compilez avec 'make'${NC}"
        exit 1
    fi

    if [ ! -f "./checker_linux" ]; then
        echo -e "${YELLOW}⚠️  Téléchargement de checker_linux...${NC}"
        wget -q https://cdn.intra.42.fr/document/document/3516/checker_linux
        chmod +x checker_linux
        if [ ! -f "./checker_linux" ]; then
            echo -e "${RED}❌ Impossible de télécharger checker_linux${NC}"
            exit 1
        fi
    fi

    echo -e "${GREEN}✅ Tous les binaires sont présents${NC}"
}

# Section 1: Gestion d'erreurs (Obligatoire)
test_error_management() {
    print_header "SECTION 1: GESTION D'ERREURS"
    local success=1

    print_test "Paramètres non numériques"
    result=$(./push_swap abc 2>&1)
    if [[ "$result" == "Error" ]]; then
        print_result 1
    else
        print_result 0
        success=0
    fi

    print_test "Paramètres dupliqués"
    result=$(./push_swap 1 2 2 3 2>&1)
    if [[ "$result" == "Error" ]]; then
        print_result 1
    else
        print_result 0
        success=0
    fi

    print_test "Nombre > INT_MAX"
    result=$(./push_swap 2147483648 2>&1)
    if [[ "$result" == "Error" ]]; then
        print_result 1
    else
        print_result 0
        success=0
    fi

    print_test "Aucun paramètre"
    result=$(./push_swap)
    if [[ "$result" == "" ]]; then
        print_result 1
    else
        print_result 0
        success=0
    fi

    if [ $success -eq 1 ]; then
        add_points 25
        return 1
    else
        echo -e "${RED}❌ Section échouée - 0 points${NC}"
        return 0
    fi
}

# Section 2: Test d'identité
test_identity() {
    print_header "SECTION 2: TEST D'IDENTITÉ"
    local success=1

    print_test "Un seul élément: ./push_swap 42"
    result=$(./push_swap 42)
    if [[ "$result" == "" ]]; then
        print_result 1
    else
        print_result 0
        success=0
    fi

    print_test "Déjà trié: ./push_swap 0 1 2 3"
    result=$(./push_swap 0 1 2 3)
    if [[ "$result" == "" ]]; then
        print_result 1
    else
        print_result 0
        success=0
    fi

    print_test "Déjà trié (10 éléments): ./push_swap 0 1 2 3 4 5 6 7 8 9"
    result=$(./push_swap 0 1 2 3 4 5 6 7 8 9)
    if [[ "$result" == "" ]]; then
        print_result 1
    else
        print_result 0
        success=0
    fi

    if [ $success -eq 1 ]; then
        add_points 25
        return 1
    else
        echo -e "${RED}❌ Section échouée - 0 points${NC}"
        return 0
    fi
}

# Section 3: Version simple
test_simple_version() {
    print_header "SECTION 3: VERSION SIMPLE"

    print_test "Test ARG=\"2 1 0\""
    ARG="2 1 0"
    result=$(./push_swap $ARG | ./checker_linux $ARG)
    operations=$(./push_swap $ARG | wc -l)

    echo "Résultat checker: $result"
    echo "Nombre d'opérations: $operations"

    if [[ "$result" == "OK" ]] && [[ $operations -le 3 ]]; then
        print_result 1
        add_points 25
        return 1
    else
        print_result 0
        echo -e "${RED}❌ Section échouée - 0 points${NC}"
        return 0
    fi
}

# Section 4: Autre version simple
test_another_simple() {
    print_header "SECTION 4: AUTRE VERSION SIMPLE"
    local success=1

    print_test "Test ARG=\"1 5 2 4 3\""
    ARG="1 5 2 4 3"
    result=$(./push_swap $ARG | ./checker_linux $ARG)
    operations=$(./push_swap $ARG | wc -l)

    echo "Résultat checker: $result"
    echo "Nombre d'opérations: $operations (max: 12)"

    if [[ "$result" == "OK" ]] && [[ $operations -le 12 ]]; then
        print_result 1
    else
        print_result 0
        success=0
    fi

    print_test "Test avec 5 valeurs aléatoires (3 essais)"
    for i in {1..3}; do
        ARG=$(shuf -i 0-100 -n 5 | paste -sd' ' -)
        result=$(./push_swap $ARG | ./checker_linux $ARG)
        operations=$(./push_swap $ARG | wc -l)

        echo "Essai $i: $ARG"
        echo "Résultat: $result, Opérations: $operations"

        if [[ "$result" != "OK" ]] || [[ $operations -gt 12 ]]; then
            success=0
        fi
    done

    if [ $success -eq 1 ]; then
        add_points 25
        return 1
    else
        echo -e "${RED}❌ Section échouée - 0 points${NC}"
        return 0
    fi
}

# Section 5: Version moyenne (100 valeurs)
test_middle_version() {
    print_header "SECTION 5: VERSION MOYENNE (100 valeurs)"

    local total_score=0
    local tests=5

    for i in $(seq 1 $tests); do
        ARG=$(shuf -i 0-1000 -n 100 | paste -sd' ' -)
        echo "Test $i/5..."

        result=$(./push_swap $ARG | ./checker_linux $ARG)
        operations=$(./push_swap $ARG | wc -l)

        echo "Opérations: $operations"

        if [[ "$result" != "OK" ]]; then
            echo -e "${RED}❌ Échec du tri !${NC}"
            echo -e "${RED}❌ Section échouée - 0 points${NC}"
            return 0
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
        echo "Score pour ce test: $score/5"
    done

    local average=$((total_score / tests))
    echo -e "${BLUE}Score moyen: $average/5${NC}"

    add_points $((average * 5))
    return 1
}

# Section 6: Version avancée (500 valeurs)
test_advanced_version() {
    print_header "SECTION 6: VERSION AVANCÉE (500 valeurs)"

    local total_score=0
    local tests=3

    for i in $(seq 1 $tests); do
        ARG=$(shuf -i 0-5000 -n 500 | paste -sd' ' -)
        echo "Test $i/3... (cela peut prendre du temps)"

        result=$(./push_swap $ARG | ./checker_linux $ARG)
        operations=$(./push_swap $ARG | wc -l)

        echo "Opérations: $operations"

        if [[ "$result" != "OK" ]]; then
            echo -e "${RED}❌ Échec du tri !${NC}"
            echo -e "${RED}❌ Section échouée - 0 points${NC}"
            return 0
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
        echo "Score pour ce test: $score/5"
    done

    local average=$((total_score / tests))
    echo -e "${BLUE}Score moyen: $average/5${NC}"

    add_points $((average * 5))
    return 1
}

# Tests bonus (checker)
test_bonus() {
    print_header "SECTION BONUS: CHECKER"

    if [ ! -f "./checker" ]; then
        echo -e "${YELLOW}⚠️  Pas de checker bonus trouvé${NC}"
        return 0
    fi

    echo -e "${PURPLE}🎁 Tests bonus disponibles !${NC}"

    # Test gestion d'erreurs checker
    print_test "Checker - gestion d'erreurs"
    error1=$(./checker abc 2>&1)
    error2=$(./checker 1 2 2 2>&1)
    error3=$(echo "invalid" | ./checker 1 2 2>&1)

    local bonus_success=1
    [[ "$error1" == "Error" ]] || bonus_success=0
    [[ "$error2" == "Error" ]] || bonus_success=0
    [[ "$error3" == "Error" ]] || bonus_success=0

    # Test checker fonctionnel
    print_test "Checker - tests fonctionnels"
    ok_test=$(echo "" | ./checker 0 1 2)
    ko_test=$(echo "sa" | ./checker 0 9 1 8 2 7 3 6 4 5)
    combo_test=$(./push_swap 3 2 1 | ./checker 3 2 1)

    [[ "$ok_test" == "OK" ]] || bonus_success=0
    [[ "$combo_test" == "OK" ]] || bonus_success=0

    if [ $bonus_success -eq 1 ]; then
        echo -e "${GREEN}✅ Bonus réussi !${NC}"
        add_points 25
    else
        echo -e "${YELLOW}⚠️  Bonus partiel ou échec${NC}"
    fi
}

# Fonction principale
main() {
    echo -e "${PURPLE}🚀 TESTEUR OFFICIEL PUSH_SWAP - OBJECTIF 125/125 🚀${NC}"
    echo -e "${PURPLE}=====================================================${NC}"

    check_binaries

    # Tests obligatoires
    test_error_management
    test_identity
    test_simple_version
    test_another_simple
    test_middle_version
    test_advanced_version

    # Tests bonus (si partie obligatoire excellente)
    if [ $TOTAL_POINTS -ge 100 ]; then
        test_bonus
    else
        echo -e "${YELLOW}⚠️  Partie obligatoire insuffisante pour les bonus${NC}"
    fi

    # Résultat final
    print_header "RÉSULTAT FINAL"
    echo -e "${PURPLE}Score total: $TOTAL_POINTS/$MAX_POINTS${NC}"

    if [ $TOTAL_POINTS -eq 125 ]; then
        echo -e "${GREEN}🏆 PARFAIT ! 125/125 ! 🏆${NC}"
    elif [ $TOTAL_POINTS -ge 100 ]; then
        echo -e "${BLUE}👍 Très bien ! Partie obligatoire validée${NC}"
    elif [ $TOTAL_POINTS -ge 75 ]; then
        echo -e "${YELLOW}⚠️  Correct mais peut mieux faire${NC}"
    else
        echo -e "${RED}❌ Insuffisant - Révision nécessaire${NC}"
    fi
}

# Exécution
main
