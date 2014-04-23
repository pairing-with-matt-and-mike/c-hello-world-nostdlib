#define SYSCALL_WRITE 1
#define SYSCALL_EXIT 60

#define STDOUT_FD 1

typedef long long int64;

void syscall_1(int64 syscall_number, int64 arg1) {
  asm(
      "mov %0, %%rax\n"
      "mov %1, %%rdi\n"
      "syscall"
      :
      : "r"(syscall_number), "r"(arg1)
      : "%rax", "%rdi"
  );
}

void syscall_3(int64 syscall_number, int64 arg1, int64 arg2, int64 arg3) {
  asm(
      "mov %0, %%rax\n"
      "mov %1, %%rdi\n"
      "mov %2, %%rsi\n"
      "mov %3, %%rdx\n"
      "syscall"
      :
      : "r"(syscall_number), "r"(arg1), "r"(arg2), "r"(arg3)
      : "%rax", "%rdi", "%rsi", "%rdx"
  );
}


/* http://en.wikipedia.org/wiki/X86_calling_conventionsq */
/* http://www.ibiblio.org/gferg/ldp/GCC-Inline-Assembly-HOWTO.html */

int x(int n) {
  int index[n];
}

int strlen(char* string) {
  int index = 0;
  while (string[index] != '\0') {
    index++;
  }
  return index;
}

void exit(int return_code) {
  syscall_1(SYSCALL_EXIT, return_code);
}

void puts(char* message) {
  syscall_3(SYSCALL_WRITE, STDOUT_FD, message, strlen(message));
}

void _start(void) {
  exit(main());
}

int main(void) {
  puts("Hello World");
  return 7;
}
