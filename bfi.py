#!/usr/bin/env python3.6

import sys


def main(code):
    memory = {}
    pointer = 0
    stack = []

    ip = 0
    while ip < len(code):
        opcode = code[ip]
        if opcode == ">":
            pointer += 1
        elif opcode == "<":
            pointer -= 1
        elif opcode == "+":
            memory[pointer] = (memory.get(pointer, 0) + 1) % 256
        elif opcode == "-":
            memory[pointer] = (memory.get(pointer, 0) - 1) % 256
        elif opcode == ".":
            sys.stdout.write(chr(memory.get(pointer, 0)))
        elif opcode == ",":
            memory[pointer] = sys.stdin.read(1)
        elif opcode == "[":
            stack.append(ip)
        elif opcode == "]" and memory.get(pointer, 0):
            try:
                ip = stack.pop()
            except IndexError:
                raise RuntimeError("No loop match")
            continue
        ip += 1


if __name__ == "__main__":
    try:
        with open(sys.argv[1]) as f:
            main(f.read())
    except IndexError:
        print(f"Usage: {sys.argv[0]} filename.bf", file=sys.stderr)
        sys.exit(1)
