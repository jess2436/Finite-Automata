/*
 * File: main.c
 * Last Modified: 09/14/24
 */

#include <stdio.h>
#include "dfa.h"
#include "nfa.h"
#include "nfaTOdfa.h"

// PART 1: DFA

// DFA for recognizing exactly the string "xyzzy"
DFA DFA_exactly_xyzzy(){
    DFA dfa = new_DFA(6);
    DFA_set_transition(dfa, 0, 'x', 1);
    DFA_set_transition(dfa, 1, 'y', 2);
    DFA_set_transition(dfa, 2, 'z', 3);
    DFA_set_transition(dfa, 3, 'z', 4);
    DFA_set_transition(dfa, 4, 'y', 5);
    DFA_set_accepting(dfa, 5, true);
    return dfa;
}

// DFA for recognizing subsequence "987"
DFA DFA_subsequence_987(){
    DFA dfa = new_DFA(4);
    DFA_set_transition_all(dfa, 0, 0);
    DFA_set_transition(dfa, 0, '9', 1);
    DFA_set_transition_all(dfa, 1, 1);
    DFA_set_transition(dfa, 1, '8', 2);
    DFA_set_transition_all(dfa, 2, 2);
    DFA_set_transition(dfa, 2, '7', 3);
    DFA_set_accepting(dfa, 3, true);
    return dfa;
}

// DFA for recognizing strings containing two or three 4's
DFA DFA_counting4s(){
    DFA dfa = new_DFA(4);
    DFA_set_transition_all(dfa, 0, 0);
    DFA_set_transition(dfa, 0, '4', 1);
    DFA_set_transition_all(dfa, 1, 1);
    DFA_set_transition(dfa, 1, '4', 2);
    DFA_set_transition_all(dfa, 2, 2);
    DFA_set_transition(dfa, 2, '4', 3);
    DFA_set_transition_all(dfa, 3, 3);
    DFA_set_accepting(dfa, 2, true);
    DFA_set_accepting(dfa, 3, true);
    return dfa;
}

// DFA for recognizing binary strings with odd number of 0's and 1's
DFA DFA_odd_binary(){
    DFA dfa = new_DFA(4);
    DFA_set_transition(dfa, 0, '0', 1);
    DFA_set_transition(dfa, 1, '0', 0);
    DFA_set_transition(dfa, 0, '1', 2);
    DFA_set_transition(dfa, 2, '1', 0);
    DFA_set_transition(dfa, 1, '1', 3);
    DFA_set_transition(dfa, 3, '1', 1);
    DFA_set_transition(dfa, 2, '0', 3);
    DFA_set_transition(dfa, 3, '0', 2);
    DFA_set_accepting(dfa, 3, true);
    return dfa;
}

// PART 2: NFA

// NFA for recognizing strings that end with 'gh'
NFA NFA_gh_ending(){
    NFA nfa = new_NFA(3);
    NFA_add_transition_all(nfa, 0, 0);
    NFA_add_transition(nfa, 0, 'g', 1);
    NFA_add_transition(nfa, 1, 'h', 2);
    NFA_set_accepting(nfa, 2, true);
    return nfa;
}

// NFA for recognizing strings containing 'moo'
NFA NFA_moo(){
    NFA nfa = new_NFA(4);
    NFA_add_transition_all(nfa, 0, 0);
    NFA_add_transition(nfa, 0, 'm', 1);
    NFA_add_transition(nfa, 1, 'o', 2);
    NFA_add_transition(nfa, 2, 'o', 3);
    NFA_add_transition_all(nfa, 3, 3);
    NFA_set_accepting(nfa, 3, true);
    return nfa;
}

// NFA for recognizing strings that aren't partial anagrams of 'cyclically'
NFA NFA_cyclically(){
    NFA nfa = new_NFA(17);
    NFA_add_transition_all(nfa, 0, 0);
    NFA_add_transition(nfa, 0, 'a', 1);
    NFA_add_transition(nfa, 1, 'a', 2);
    NFA_add_transition_all(nfa, 2, 2);

    NFA_add_transition(nfa, 0, 'i', 3);
    NFA_add_transition(nfa, 3, 'i', 4);
    NFA_add_transition_all(nfa, 4, 4);

    NFA_add_transition(nfa, 0, 'y', 5);
    NFA_add_transition(nfa, 5, 'y', 6);
    NFA_add_transition(nfa, 6, 'y', 7);
    NFA_add_transition_all(nfa, 7, 7);

    NFA_add_transition(nfa, 0, 'c', 8);
    NFA_add_transition(nfa, 9, 'c', 10);
    NFA_add_transition(nfa, 11, 'c', 12);
    NFA_add_transition(nfa, 12, 'c', 13);
    NFA_add_transition_all(nfa, 13, 13);

    NFA_add_transition(nfa, 0, 'l', 13);
    NFA_add_transition(nfa, 13, 'l', 14);
    NFA_add_transition(nfa, 14, 'l', 15);
    NFA_add_transition(nfa, 15, 'l', 16);
    NFA_add_transition_all(nfa, 16, 16);

    NFA_set_accepting(nfa, 2, true);
    NFA_set_accepting(nfa, 4, true);
    NFA_set_accepting(nfa, 7, true);
    NFA_set_accepting(nfa, 13, true);
    NFA_set_accepting(nfa, 16, true);

    return nfa;
}

// main function for testing
int main(){

    printf("\nCSC173 Project 1 by Jessica Chen & Shadiya Akhter\n");
    printf("\n");

    // DFA TESTING

    // DFA Test: xyzzy
    DFA dfa_xyzzy = DFA_exactly_xyzzy();
    printf("Testing DFA that recognizes exactly 'xyzzy'...");
    DFA_repl(dfa_xyzzy);
    DFA_free(dfa_xyzzy);

    // DFA Test: subsequence 987
    DFA dfa_987 = DFA_subsequence_987();
    printf("Testing DFA that recognizes exactly subsequence '987'...");
    DFA_repl(dfa_987);
    DFA_free(dfa_987);

    // DFA Test: counting 4's
    DFA dfa_4count = DFA_counting4s();
    printf("Testing DFA that recognizes two or three 4's in a string...");
    DFA_repl(dfa_4count);
    DFA_free(dfa_4count);

    // DFA Test: odd binary
    DFA dfa_binary = DFA_odd_binary();
    printf("Testing DFA that recognizes an odd number of binary values 0 and 1...");
    DFA_repl(dfa_binary);
    DFA_free(dfa_binary);

    // NFA TESTING

    // NFA Test: strings ending in 'gh'
    NFA nfa_gh = NFA_gh_ending();
    printf("Testing NFA that recognizes strings ending in 'gh'...");
    NFA_repl(nfa_gh);
    NFA_free(nfa_gh);

    // NFA Test: strings that contain 'moo'
    NFA nfa_with_moo = NFA_moo();
    printf("Testing NFA that recognizes strings containing 'moo'...");
    NFA_repl(nfa_with_moo);
    NFA_free(nfa_with_moo);

    // NFA Test: strings that are not partial anagrams of 'cyclically'
    NFA nfa_anagram = NFA_cyclically();
    printf("Testing NFA that recognizes strings which are not partial anagrams of 'cyclically'...");
    NFA_repl(nfa_anagram);
    NFA_free(nfa_anagram);

    // NFA TO DFA TESTING

    // NFA to DFA: strings ending in 'gh'
    DFA dfa_gh = NFA_to_DFA(nfa_gh);
    printf("DFA for strings ending in 'gh' has %d states.\n", DFA_get_size(dfa_gh));
    printf("Testing DFA for strings ending in 'gh'...\n");
    DFA_repl(dfa_gh);
    DFA_free(dfa_gh);
    NFA_free(nfa_gh);

    // NFA to DFA: strings containing 'moo'
    DFA dfa_moo = NFA_to_DFA(nfa_with_moo);
    printf("DFA for strings containing 'moo' has %d states.\n", DFA_get_size(dfa_moo));
    printf("Testing DFA for strings containing 'moo'...\n");
    DFA_repl(dfa_moo);
    DFA_free(dfa_moo);
    NFA_free(nfa_with_moo);

    return 0;
}
