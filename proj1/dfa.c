/*
 * File: dfa.c
 * Authors: Jessica Chen, Shadiya Akhter
 * CSC 173 | George Ferguson | Project 1
 * Last Modified: 09/07/24
 */

#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "dfa.h"

// allocate and return new DFA
DFA new_DFA(int nstates){
    DFA dfa = (DFA)malloc(sizeof(struct dfa));
    dfa->curr_state = 0;
    dfa->num_states = nstates;
    dfa->transitions = (int**)malloc(nstates * sizeof(int*));
    for (int i = 0; i < nstates; i++){
        dfa->transitions[i] = (int *)malloc(128 * sizeof(int));
        for (int j = 0; j < 128; j++){
            dfa->transitions[i][j] = 0;
        }
    }
    dfa->accepts = (bool*)malloc(nstates * sizeof(bool));
    for (int i = 0; i < nstates; i++){
        dfa->accepts[i] = false;
    }
    return dfa;
}

// free the DFA
void DFA_free(DFA dfa){
    for (int i = 0; i < dfa->num_states; i++){
        free(dfa->transitions[i]);
    }
    free(dfa->transitions);
    free(dfa->accepts);
    free(dfa);
}

// return number of states in the DFA
int DFA_get_size(DFA dfa){
    return dfa->num_states;
}

// return the state specified by the given DFA's transition function
int DFA_get_transition(DFA dfa, int src, char sym){
    int n = sym;
    return dfa->transitions[src][n];
}

// set transition for DFA
void DFA_set_transition(DFA dfa, int src, char sym, int dst){
    int n = sym;
    dfa->transitions[src][n] = dst;
}

// set transition in DFA for each symbol in given string 
void DFA_set_transition_str(DFA dfa, int src, char *str, int dst){
    for (int i = 0; i <strlen(str); i++){
        int sym = str[i];
        dfa->transitions[src][sym] = dst;
    }
}

// set transitions in DFA for all input symbols
void DFA_set_transition_all(DFA dfa, int src, int dst){
    for (int i = 0; i < 128; i++){
        dfa->transitions[src][i] = dst;
    }
}

// set accepting / non-accepting state for DFA
void DFA_set_accepting(DFA dfa, int state, bool value) {
    dfa->accepts[state] = value;
}

// return true if DFA state is accepting
bool DFA_get_accepting(DFA dfa, int state){
    return dfa->accepts[state];
}

// running the DFA, return true if accepting, false if not
bool DFA_execute(DFA dfa, char *input){
    dfa->curr_state = 0;
    for (int i = 0; i <strlen(input); i++){
        int curr = dfa->curr_state;
        int sym = input[i];
        dfa->curr_state = DFA_get_transition(dfa, curr, sym);
    }
    return DFA_get_accepting(dfa, dfa->curr_state);
}

// get string for DFA
char* DFA_get_string(DFA dfa){
    return dfa->string;
}

// set string for DFA
void DFA_set_string(DFA dfa, char* str){
    dfa->string = str;
}

// REPL function for DFA 
void DFA_repl(DFA dfa) {
    char input[128];
    while (true) {
        printf("\nEnter an input string ('quit' to exit): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
        if (strcmp(input, "quit") == 0) {
            printf("\n");
            break;
        }
        bool result = DFA_execute(dfa, input);
        printf("Input \"%s\" -> %s\n", input, result ? "ACCEPT" : "REJECT");
    }
}