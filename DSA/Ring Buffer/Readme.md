# Ring Buffer in C

A simple **ring buffer (circular buffer)** implementation in C, written for learning and integration into projects like UART drivers.

---

## 📖 What is a Ring Buffer?
A **ring buffer** is a fixed-size **FIFO (First-In, First-Out)** data structure.  
It uses two pointers:
- **head** → where new data is written
- **tail** → where old data is read

When head or tail reach the end of the buffer, they **wrap around** to the start.

This is very useful in embedded systems (e.g., UART RX/TX) to handle data streams efficiently.

---

## 📂 Files
- `ring_buffer.c` → Implementation + test code

---

## 🛠️ How to Build & Run
Compile using `gcc`:
```bash
gcc ring_buffer.c -o ring_buffer
./ring_buffer
