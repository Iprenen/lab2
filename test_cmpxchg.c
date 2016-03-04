/**
 * Implementation of test cases using atomic and non-atomic cmpxchg.
 *
 *
 * Course: Advanced Computer Architecture, Uppsala University
 * Course Part: Lab assignment 2
 *
 * Author: Andreas Sandberg <andreas.sandberg@it.uu.se>
 * Revision (2015,2016): German Ceballos <german.ceballos@it.uu.se>
 */

#include "lab2.h"

#include "lab2_asm.h"

volatile int32_t flag = 0;

static void
increase(int thread, int iterations, volatile int *data)
{
        /* TASK: Implement a loop that increments *data by 1 using
         * non-atomic compare and exchange instructions. See lab2_asm.h.
         */

         for (int i = 0; i < iterations;) {
           if (*data == 0) {
             asm_cmpxchg_int32((int32_t *)data,0,1);
             i++;
           }
       }

}

static void
decrease(int thread, int iterations, volatile int *data)
{
        /* TASK: Implement a loop that decrements *data by 1 using
         * non-atomic compare and exchange instructions. See lab2_asm.h.
         */
         for (int i = 0; i < iterations;) {
           if (*data == 1) {
             asm_cmpxchg_int32((int32_t *)data,1,0);
             i++;
           }
       }

}


static void
increase_atomic(int thread, int iterations, volatile int *data)
{
        /* TASK: Implement a loop that increments *data by 1 using
         * atomic compare and exchange instructions. See lab2_asm.h.
         */

         for (int i = 0; i < iterations; i++) {
           while (1) {
            if (asm_atomic_cmpxchg_int32((int32_t *) &flag,0,1) == 0)
              break;
            while (flag != 0) {};
           }
           (*data)++;
           flag = 0;
       }


}

static void
decrease_atomic(int thread, int iterations, volatile int *data)
{
        /* TASK: Implement a loop that decrements *data by 1 using
         * atomic compare and exchange instructions. See lab2_asm.h.
         */
         for (int i = 0; i < iterations; i++) {
           while (1) {
            if (asm_atomic_cmpxchg_int32((int32_t *) &flag,0,1) == 0)
              break;
            while (flag != 0) {};
           }
           (*data)--;
           flag = 0;
       }

}

test_impl_t test_impl_cmpxchg_no_atomic = {
        .name = "cmpxchg_no_atomic",
        .desc = "Modify a shared variable using compare and exchange",

        .num_threads = 2,
        .test = { &increase, &decrease }
};

test_impl_t test_impl_cmpxchg_atomic = {
        .name = "cmpxchg_atomic",
        .desc = "Modify a shared variable using atomic compare and exchange",

        .num_threads = 2,
        .test = { &increase_atomic, &decrease_atomic }
};

/*
 * Local Variables:
 * mode: c
 * c-basic-offset: 8
 * indent-tabs-mode: nil
 * c-file-style: "linux"
 * End:
 */
