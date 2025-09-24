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
```
## 🧪 Example Output
Buffer full? 1\
Got: A\
Got: B\
Got: C\
Got: D\
Got: E\
Buffer empty? 1
## 🚀 How It Works
* RB_Put() inserts data into the buffer at head.

* RB_Get() retrieves data from the buffer at tail.

* Both indices wrap around using:
        index = (index + 1) % size;
* One slot is always kept empty to distinguish full vs empty condition.
## 🔗 Next Step

This buffer can now be integrated into a UART driver:

* RX interrupt pushes incoming bytes into the buffer using RB_Put().

* Application code reads from the buffer using RB_Get().

## 📜 License

MIT License – feel free to use this in your own projects.
