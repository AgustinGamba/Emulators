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
    uint16_t sp;  // Stack Pointer
    uint16_t pc;  // Program Counter
    uint8_t *memory;
    struct ConditionCodes cc;
    uint8_t int_enable;
  } State8080;

  // TODO: make it work
  static int parity(int x) { return 0; }

  void Emulate8080Op(State8080 * state) {
    // TODO: Test &state->memory[state->pc]
    // It should give an hex value in memory?
    unsigned char *opcode = &state->memory[state->pc];

    switch (*opcode) {
      case 0x00:  // NOP
        break;
        // TODO: Test opcode[1] and opcode[2]
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
        break;
      case 0x80: {  // ADD B
        // Math in higher precision to capture the carry
        uint16_t answer = (uint16_t)state->a + (uint16_t)state->b;

        // Zero flag: result == 0 => flag=1 ; else => clear flag
        // 0xff (1111 1111) & 0 == 0 ; else => answer
        state->cc.z = ((answer & 0xff) == 0);

        // Sign flag: bit 7 is set => set flag ; else=> clear flag
        // 0x80 (1000 0000) & answer only 1 if answer > 1000 0000
        state->cc.s = ((answer & 0x80) != 0);

        // Carry Flag, only if answer > 1111 1111 (uint8_t limit)
        state->cc.cy = (answer > 0xff);

        // Parity is handled by a subroutine
        state->cc.p = parity(answer & 0xff);

        state->a = answer & 0xff;
      }
        // TODO: create functions with the flags
      case 0x81: {  // ADD C
        uint16_t answer = (uint16_t)state->a + (uint16_t)state->c;
        state->cc.z = ((answer & 0xff) == 0);
        state->cc.s = ((answer & 0x80) != 0);
        state->cc.cy = (answer > 0xff);
        state->cc.p = parity(answer & 0xff);
        state->a = answer & 0xff;
      }
        // TODO: Test memory[offset]
      case 0x86: {  // ADD M
        // Ex: h = 1100 1011 && l = 0011 1101
        // 1100 1011 0000 0000 | 0011 1101 == 1100 1011 0011 1101
        uint16_t offset = (state->h << 8) | (state->l);
        uint16_t answer = (uint16_t)state->a + state->memory[offset];
        state->cc.z = ((answer & 0xff) == 0);
        state->cc.s = ((answer & 0x80) != 0);
        state->cc.cy = (answer > 0xff);
        state->cc.p = parity(answer & 0xff);
        state->a = answer & 0xff;
      }
      case 0xC6: {  // ADI byte
        uint16_t answer = (uint16_t)state->a + (uint16_t)opcode[1];
        state->cc.z = ((answer & 0xff) == 0);
        state->cc.s = ((answer & 0x80) != 0);
        state->cc.cy = (answer > 0xff);
        state->cc.p = parity(answer & 0xff);
        state->a = answer & 0xff;
        break;
      }
    }
    state->pc += 1;
  }

  /*struct State8080 state;
  state->a = 0xA9;
  state->b = 0xA8;
  state->c = 0xA7;
  state->d = 0xA6;
  state->e = 0xA5;
  state->h = 0xA4;
  state->l = 0xA3;
  state->sp = 0x00;
  state->pc = 0x01;

  state->int_enable = 0x00;*/

  printf("Hello World\n");
  return 0;
}
