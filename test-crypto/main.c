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

#define FOO_ENTER_ID 3
#define ATTEST_ID 1

#define ENTRY_ID FOO_ENTER_ID

SM_INPUT(foo, whatever, data, len) {}

void SM_ENTRY(foo) foo_enter(uint8_t *challenge, uint16_t len, uint8_t *res) {
    pr_info("Hello from Foo");
    sancus_tag(challenge, len, res);
    pr_info("Computed tag");
}

int main() {
    msp430_io_init();

    pr_info("hello!");

    int id = sancus_enable(&foo);
    ASSERT(id);
    ASSERT(sm_register_existing(&foo));

    uint8_t challenge[16], result[16];

    uint16_t args[] = {(uint16_t) challenge, 16, (uint16_t) result};
    uint16_t retval;

    // this hangs when executing handle_attest, but succeeds with foo_enter
    ASSERT( sm_call_id(id, ENTRY_ID, args, 3, &retval) );
    ASSERT(!retval);

    pr_info("All done!\n");
    EXIT();
}
