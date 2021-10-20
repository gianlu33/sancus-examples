#include <msp430.h>
#include <stdio.h>
#include <stdlib.h>
#include <sancus/sm_support.h>
#include <sancus_support/sm_io.h>
#include <sancus_support/sm_control.h>

#include <stdint.h>
#include <string.h>
#include <sancus/reactive.h>

DECLARE_SM(foo, 0x1234);

// if you uncomment the SM_INPUT macro, check the correct ID with readelf
#define ENTRY_ID 0
//SM_INPUT(foo, whatever, data, len) {}

void SM_ENTRY(foo) foo_enter() {
    pr_info("Hello from Foo");
}


int main() {
    msp430_io_init();

    int id = sancus_enable(&foo);
    ASSERT(id);
    ASSERT(sm_register_existing(&foo));

    // this always works
    foo_enter();

    // this does not work with my sancus-compiler and with the SM_INPUT uncommented
    ASSERT( sm_call_id(id, ENTRY_ID, NULL, 0, NULL) );

    pr_info("All done!\n");
    EXIT();
}
