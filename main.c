#include <stdint.h>
#include <stdio.h>

int main() {
  typedef struct ConditionCodes {
    uint8_t z : 1;   // Zero
    uint8_t s : 1;   // Sign
    uint8_t p : 1;   // Parity
    uint8_t cy : 1;  // Carry
    uint8_t ac : 1;  // Half Carry
    uint8_t pad : 3;
  } ConditionCodes;

  typedef struct State8080 {
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t d;
    uint8_t e;
    uint8_t h;
    uint8_t l;
    uint16_t sp;
    uint16_t pc;
    uint8_t *memory;
    struct ConditionCodes cc;
    uint8_t int_enable;
  } State8080;

  void Emulate8080Op(State8080* state) {
    unsigned char *opcode = &state->memory[state->pc];

    switch (*opcode) {
      case 0x00:  // NOP
        break;
      case 0x01:  // LXI B, word
        state->c = opcode[1];
        state->b = opcode[2];
        state->pc += 2;
        break;
      case 0x41:  // MOV B,C
        state->b = state->c;
        break;
      case 0x42:  // MOV B,D
        state->b = state->d;
        break;
      case 0x43:  // MOV B,E
        state->b = state->e;
    }
    state->pc += 1;
  }

  printf("Hello World\n");
  printf("test");
  return 0;
}
