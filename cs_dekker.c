/**
 * Experimenting with synchronization and memory consistency. Dekker's
 * algorithm version of critical sections.
 *
 *
 * Course: Advanced Computer Architecture, Uppsala University
 * Course Part: Lab assignment 2
 *
 * Author: Andreas Sandberg <andreas.sandberg@it.uu.se>
 * Revision (2015, 2016): German Ceballos <german.ceballos@it.uu.se>
 */

#include <assert.h>

#include "lab2.h"
#include "unistd.h"

#if defined(__GNUC__) && defined(__SSE2__)
/** Macro to insert memory fences */
#define MFENCE() __builtin_ia32_mfence()
#else
#error Memory fence macros not implemented for this platform.
#endif

static volatile int flag[2] = { 0, 0 };
static volatile int turn = 0;

/**
 * Enter a critical section. Implementation using Dekker's algorithm.
 *
 * \param thread Thread ID, either 0 or 1.
 */
static void
impl_enter_critical(int thread)
{
        assert(thread == 0 || thread == 1);

        /* Set want to get in flag to thread ID */
        flag[thread] = 1;
        MFENCE();
        /* HINT: Since Dekker's algorithm only works for 2 threads,
         * with the ID 0 and 1, you may use !thread to get the ID the
         * other thread. */

        /* TASK: Implement entry code for Dekker's algorithm here */

          // Spin lock algoritm for dekker.


          while (flag[!thread] == 1) { //Synchronize with other thread
            if (turn != thread) {   //Not my turn, set flag to 0
              flag[thread] = 0;
              MFENCE();
              while (turn != thread) {}; //Spin on lock until my turn
              flag[thread] = 1; // My turn, woho! Show it to other thread
              MFENCE();
            };
        };

};

/**
 * Exit from a critical section.
 *
 * \param thread Thread ID, either 0 or 1.
 */
static void
impl_exit_critical(int thread)
{
        assert(thread == 0 || thread == 1);

        /* TASK: Implement exit code for Dekker's algorithm here */
        /* Set flag to 0 and set turn to the other thread */

        if (thread == 0) {
          turn = 1;
          flag[thread] = 0;
          MFENCE();
        } else {
          turn = 0;
          flag[thread] = 0;
          MFENCE();
        };



};


critical_section_impl_t cs_impl_dekker = {
        .name = "dekker",
        .desc = "Dekker's algorithm",

        .max_threads = 2,

        .enter = &impl_enter_critical,
        .exit = &impl_exit_critical
};

/*
 * Local Variables:
 * mode: c
 * c-basic-offset: 8
 * indent-tabs-mode: nil
 * c-file-style: "linux"
 * End:
 */
