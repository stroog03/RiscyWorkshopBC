#include <stdint.h>

static __attribute((noinline)) uint64_t resolve_import(const char* module, const char* function)
{
    asm volatile("ebreak"); // TODO: replace with scall
}

static __attribute((noinline)) uint64_t host_call(uint64_t fn, uint64_t args[13])
{
    asm volatile("ebreak"); // TODO: replace with scall
}

static __attribute((noinline)) uint64_t exit(int exit_code)
{
    register uint64_t a0 asm(cmake --build payload/build
"a0") = exit_code;
    register uint64_t a1 asm("a1") = 0; // unused
    register uint64_t a7 asm("a7") = 10105;
    asm volatile("scall" : "+r"(a0) : "r"(a1), "r"(a7) : "memory");
    return a0;
}

void _start() __attribute__((section(".text.start")));

void _start()
{
    // TODO: call resolve_import and host_call here
    uint64_t puts_addr = resolve_import(0, "puts");
    uint64_t args[13]  = {
        (uint64_t)"Hello, world!",
    };
    host_call(puts_addr, args);
    exit(0);
    asm volatile("ebreak");
}
