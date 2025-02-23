/*
 * File: nfa.c
 * Authors: Jessica Chen, Shadiya Akhter
 * CSC 173 | George Ferguson | Project 1
 * Last Modified: 09/14/24
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "nfa.h"
#include "IntHashSet.h"

// allocate and return new NFA
NFA new_NFA(int nstates){
    NFA nfa = (NFA)malloc(sizeof(struct nfa));
    nfa->curr_states = NULL;
    nfa->num_states = nstates;
    nfa->transitions = (IntHashSet**)malloc(nstates * sizeof(IntHashSet*));
    for (int i = 0; i < nstates; i++){
        nfa->transitions[i] = (IntHashSet *)malloc(128 * sizeof(IntHashSet));
    }
    for (int i = 0; i < nstates; i++) {
        for (int j = 0; j < 128; j++) {
            nfa->transitions[i][j] = new_IntHashSet(nfa->num_states);
        }
    }
    nfa->accepts = (bool*)malloc(nstates * sizeof(bool));
    for (int i = 0; i < nstates; i++) {
        nfa->accepts[i] = false;
    }
    return nfa;
}

// free NFA
void NFA_free(NFA nfa){
    for (int i = 0; i < nfa->num_states; i++) {
        for (int j = 0; j < 128; j++){
            IntHashSet_free(nfa->transitions[i][j]);
        }
        free(nfa->transitions[i]);
    }
    free(nfa->transitions);
    IntHashSet_free(nfa->curr_states);
    free(nfa->accepts);
    free(nfa);
}

// return number of states in NFA
int NFA_get_size(NFA nfa){
    return nfa->num_states;
}

// return set of next states using NFA's transition function
IntHashSet NFA_get_transitions(NFA nfa, int state, char sym){
    int n = sym;
    return (nfa->transitions)[state][n];
}

// add state dst for given NFA 
void NFA_add_transition(NFA nfa, int src, char sym, int dst){
    int n = sym;
    if(!IntHashSet_lookup(nfa->transitions[src][n], dst)){
        IntHashSet_insert(nfa->transitions[src][n], dst);
    }
}

// add transition for given NFA, each symbol in string
void NFA_add_transition_str(NFA nfa, int src, char *str, int dst){
    for (int i = 0; i < strlen(str); i++){
        int sym = str[i];
        if(IntHashSet_lookup(nfa->transitions[src][sym], dst)){
            IntHashSet_insert(nfa->transitions[src][sym], dst);
        }
    }
}

// add transition for given NFA, each input symbol
void NFA_add_transition_all(NFA nfa, int src, int dst){
    for (int j = 0; j < 128; j++){
        if(!IntHashSet_lookup(nfa->transitions[src][j], dst)){
            IntHashSet_insert(nfa->transitions[src][j], dst);
        }
    }
}

// set acceptance of NFA state
void NFA_set_accepting(NFA nfa, int state, bool value){
    nfa->accepts[state] = value;
}

// return if NFA state accepts
bool NFA_get_accepting(NFA nfa, int state){
    return nfa->accepts[state];
}

// running the NFA, return true if accepting, false if not
bool NFA_execute(NFA nfa, char *input){
    reset_NFA(nfa);
    IntHashSet temp;
    for (int i = 0; i < strlen(input); i++){
        int sym = input[i];
        temp = new_IntHashSet(nfa->num_states);
        IntHashSetIterator curr_iterate = IntHashSet_iterator(nfa->curr_states);
        while (IntHashSetIterator_hasNext(curr_iterate)) {
            int curr = IntHashSetIterator_next(curr_iterate);
            IntHashSet_union(temp, NFA_get_transitions(nfa, curr, sym));
        }
        free(curr_iterate);
        IntHashSet_free(nfa->curr_states);
        nfa->curr_states = temp;
        IntHashSet_union(nfa->curr_states, temp);
    }
    bool accepted = false;
    IntHashSetIterator accept_iterate = IntHashSet_iterator(nfa->curr_states);
    while (IntHashSetIterator_hasNext(accept_iterate)){
        int curr = IntHashSetIterator_next(accept_iterate);
        if (nfa->accepts[curr] == true){
            accepted = true;
        }
    }
    free(accept_iterate);
    return accepted;
}

// get string for NFA
char* NFA_get_string(NFA nfa){
    return nfa->string;
}

// set string for NFA
void NFA_set_string(NFA nfa, char* str){
    nfa->string = str;
}

// reset NFA
void reset_NFA(NFA nfa){
    if (nfa->curr_states != NULL){
        IntHashSet_free(nfa->curr_states);
    }
    nfa->curr_states = new_IntHashSet(nfa->num_states);
    IntHashSet_insert(nfa->curr_states, 0);
}

// REPL function for NFA
void NFA_repl(NFA nfa) {
    char input[128];
    while (true) {
        printf("\nEnter an input string ('quit' to exit): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
        if (strcmp(input, "quit") == 0) {
            printf("\n");
            break;
        }
        bool result = NFA_execute(nfa, input);
        printf("Input \"%s\" -> %s\n", input, result ? "ACCEPT" : "REJECT");
    }
}