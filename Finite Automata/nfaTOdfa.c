/*
 * File: nfaTOdfa.c
 * Authors: Jessica Chen, Shadiya Akhter
 * CSC 173 | George Ferguson | Project 1
 * Last Modified: 09/14/24
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "nfaTOdfa.h"
#include "dfa.h"
#include "nfa.h"
#include "LinkedList.h"
#include "IntHashSet.h"

DFA NFA_to_DFA(NFA nfa){
    IntHashSet start = new_IntHashSet(nfa->num_states);
    IntHashSet_insert(start, 0);

    LinkedList dfa_states = new_LinkedList();
    LinkedList_add_at_end(dfa_states, start);

    LinkedList accepting = new_LinkedList();

    DFA dfa = new_DFA(1);

    for (int i = 0; i < LinkedList_size(dfa_states); i++){
        IntHashSet curr_dfa_state = LinkedList_elementAt(dfa_states, i);

        for (int sym = 0; sym < 128; sym++){
            IntHashSet new_dfa_state = new_IntHashSet(nfa->num_states);

            IntHashSetIterator iterator = IntHashSet_iterator(curr_dfa_state);
            while (IntHashSetIterator_hasNext(iterator)){
                int nfa_state = IntHashSetIterator_next(iterator);
                IntHashSet_union(new_dfa_state, NFA_get_transitions(nfa, nfa_state, sym));
            }
            free(iterator);

            if (!IntHashSet_isEmpty(new_dfa_state)){
                int new_state_index = -1;
                for (int j = 0; j < LinkedList_size(dfa_states); j++){
                    if (IntHashSet_equals(new_dfa_state, LinkedList_elementAt(dfa_states, j))){
                        new_state_index = j;
                        break;
                    }
                }
                if (new_state_index == -1){
                    LinkedList_add_at_end(dfa_states, new_dfa_state);
                    new_state_index = LinkedList_size(dfa_states) -1;

                    DFA_set_transition(dfa, DFA_get_size(dfa), sym, new_state_index);

                    IntHashSetIterator accept_iter = IntHashSet_iterator(new_dfa_state);
                    while (IntHashSetIterator_hasNext(accept_iter)){
                        int state = IntHashSetIterator_next(accept_iter);
                        if (NFA_get_accepting(nfa, state)){
                            DFA_set_accepting(dfa, new_state_index, true);
                            break;
                        }
                    }
                    free(accept_iter);
                } else {
                    IntHashSet_free(new_dfa_state);
                }
                DFA_set_transition(dfa, i, sym, new_state_index);
            } else {
                IntHashSet_free(new_dfa_state);
            }
        }
    }
    LinkedList_free(dfa_states, true);
    LinkedList_free(accepting, false);

    return dfa;
}