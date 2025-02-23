/*
 * File: nfa.h
 * Creator: George Ferguson
 * Created: Thu Sep  1 17:54:41 2016
 */

#ifndef nfa_h
#define nfa_h

#include <stdbool.h>
#include "IntHashSet.h"

struct nfa {
    char* string;
    IntHashSet curr_states;
    int num_states;
    bool* accepts;
    IntHashSet** transitions;
};

typedef struct nfa *NFA;

extern NFA new_NFA(int nstates);

extern void NFA_free(NFA nfa);

extern int NFA_get_size(NFA nfa);

extern IntHashSet NFA_get_transitions(NFA nfa, int state, char sym);

extern void NFA_add_transition(NFA nfa, int src, char sym, int dst);

extern void NFA_add_transition_str(NFA nfa, int src, char *str, int dst);

extern void NFA_add_transition_all(NFA nfa, int src, int dst);

extern void NFA_set_accepting(NFA nfa, int state, bool value);

extern bool NFA_get_accepting(NFA nfa, int state);

extern bool NFA_execute(NFA nfa, char *input);

extern void NFA_print(NFA nfa);

extern char* NFA_get_string(NFA nfa);

extern void NFA_set_string(NFA nfa, char* str);

extern void reset_NFA(NFA nfa);

extern void NFA_repl(NFA nfa);

#endif
