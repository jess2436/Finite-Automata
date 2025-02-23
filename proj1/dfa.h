/*
 * File: dfa.h
 */

#ifndef DFA_H
#define DFA_H

#include <stdbool.h>

struct dfa{
    char* string;
    int curr_state;
    int num_states;
    bool* accepts;
    int** transitions;
};

typedef struct dfa *DFA;

extern DFA new_DFA(int nstates);

extern void DFA_free(DFA dfa);

extern int DFA_get_size(DFA dfa);

extern int DFA_get_transition(DFA dfa, int src, char sym);

extern void DFA_set_transition(DFA dfa, int src, char sym, int dst);

extern void DFA_set_transition_str(DFA dfa, int src, char *str, int dst);

extern void DFA_set_transition_all(DFA dfa, int src, int dst);

extern void DFA_set_accepting(DFA dfa, int state, bool value);

extern bool DFA_get_accepting(DFA dfa, int state);

extern bool DFA_execute(DFA dfa, char *input);

extern void DFA_print(DFA dfa);

extern char* DFA_get_string(DFA dfa);

extern void DFA_set_string(DFA dfa, char* str);

extern void DFA_repl(DFA dfa);

#endif
