/**
 * Implementation of test cases using critical sections.
 *
 *
 * Course: Advanced Computer Architecture, Uppsala University
 * Course Part: Lab assignment 2
 *
 * Author: Andreas Sandberg <andreas.sandberg@it.uu.se>
 * Revision (2015,2016): German Ceballos <german.ceballos@it.uu.se>
 */

#include "lab2.h"
#include "pthread.h"

pthread_mutex_t mutex;

pthread_mutex_init(&mutex, NULL);

/**
 * Code for thread 0, increments the shared variable 'data',
 * through a local variable
 */
static void
increase(int thread, int iterations, volatile int *data)
{
        for (int i = 0; i < iterations; i++) {
                int a;
                /* TASK: Use enter_critical(thread) and
                 * exit_critical(thread) to define a critical section
                 * around the code that needs to execute atomically.
                 */
                enter_critical(thread);
                a = *data;
                a++;
                *data = a;
                exit_critical(thread);
        }
}

/**
 * Code for thread 1, decrements the shared variable 'data',
 * through a local variable
 */
static void
decrease(int thread, int iterations, volatile int *data)
{
        for (int i = 0; i < iterations; i++) {
                int a;
                /* TASK: Use enter_critical(thread) and
                 * exit_critical(thread) to define a critical section
                 * around the code that needs to execute atomically.
                 */
                enter_critical(thread);
                a = *data;
                a--;
                *data = a;
                exit_critical(thread);
        }
}

/* Code for enter_critical function, locks *data */

static void
enter_critical(thread) {

        pthread_mutex_lock(&mutex); //Lock the critical section
        printf("Thread %s is in critical section", thread);
}

static void
exit_critical(thread) {

        pthread_mutex_unlock(&mutex); //Lock the critical section
        printf("Thread %s leaves critical section", thread);
}

test_impl_t test_impl_critical = {
        .name = "critical",
        .desc = "Modify a shared variable protected by critical sections",

        .num_threads = 2,
        .test = { &increase, &decrease }
};


test_impl_t test_impl_critical4 = {
        .name = "critical4",
        .desc = "Modify a shared variable protected by critical sections",

        .num_threads = 4,
        .test = {
                &increase, &decrease,
                &increase, &decrease,
        }
};

test_impl_t test_impl_critical8 = {
        .name = "critical8",
        .desc = "Modify a shared variable protected by critical sections",

        .num_threads = 8,
        .test = {
                &increase, &decrease,
                &increase, &decrease,

                &increase, &decrease,
                &increase, &decrease
        }
};

/*
 * Local Variables:
 * mode: c
 * c-basic-offset: 8
 * indent-tabs-mode: nil
 * c-file-style: "linux"
 * End:
 */
