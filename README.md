*This project has been created as part of the 42 curriculum by mel-wahm.*

# Codexion

## Description
Codexion is a multi-threaded C simulation modeling a shared co-working hub where coders compete for limited USB dongles to compile quantum code. Each coder requires two adjacent dongles (left and right) simultaneously to compile before transitioning to debugging and refactoring phases. The simulation manages thread synchronization, prevents resource starvation, avoids deadlocks, and detects burnout precisely.

## Instructions

### Compilation
Build the binary using the provided `Makefile`:
```bash
make
```

### Execution
Run the executable with the required 8 arguments:
```bash
./codexion <number_of_coders> <time_to_burnout> <time_to_compile> <time_to_debug> <time_to_refactor> <number_of_compiles_required> <dongle_cooldown> <scheduler>
```

- `number_of_coders`: Number of coders and dongles ($N > 0$).
- `time_to_burnout`: Time in ms before a starving coder burns out.
- `time_to_compile`: Time in ms spent compiling (holds 2 dongles).
- `time_to_debug`: Time in ms spent debugging.
- `time_to_refactor`: Time in ms spent refactoring.
- `number_of_compiles_required`: Target compiles per coder to complete simulation.
- `dongle_cooldown`: Mandatory cooldown in ms after releasing a dongle.
- `scheduler`: Arbitration policy (`fifo` or `edf`).

#### Example Run:
```bash
./codexion 4 800 200 200 200 2 10 fifo
```

### Cleanup
```bash
make fclean
```

## Blocking Cases Handled
- **Deadlock Prevention**: Circular wait is eliminated by breaking resource symmetry (odd-numbered coders acquire left dongle first, even-numbered coders acquire right dongle first).
- **Starvation Prevention**: Fair arbitration is guaranteed via custom Min-Heap priority queues enforcing strict FIFO arrival or Earliest-Deadline-First (EDF) order with deterministic tie-breaking.
with a small trick on sleeping all the coders with odd ids for a small time.
- **Dongle Cooldown Handling**: `handle_cooldown` ensures dongles remain unavailable for `dongle_cooldown` ms after release while thread-safely managing queue waiters.
- **Precise Burnout Detection**: A dedicated monitor thread polls burnout states every 500 $\mu$s, guaranteeing log output within $<10$ ms of actual occurrence.
- **Log Serialization**: Output interleaving is prevented by wrapping all state logs in a global `print_mutex`. Stray prints after simulation termination are suppressed.

## Thread Synchronization Mechanisms
- **`pthread_mutex_t`**:
  - `available_mutex`: Protects each dongle's availability state and priority queue.
  - `count_mutex`: Ensures thread-safe access to timestamps (`last_compile_time`) and `compile_count`.
  - `end_mutex`: Synchronizes access to the `simulation_ends` state flag.
  - `print_mutex`: Serializes all terminal output to prevent interleaved logs.
- **`pthread_cond_t`**:
  - `waiters`: Used on each dongle to sleep waiting coders until dongles are released or simulation ends.
- **Custom Event Arbitration**: Min-Heap data structure embedded in each dongle to evaluate queue priority ($O(1)$ root access).

## Resources
- POSIX Threads Programming (`pthread_create`, `pthread_mutex_lock`, `pthread_cond_wait`).
- Operating Systems: Three Easy Pieces (Concurrency & Synchronization Primitives).
- **AI Usage**: AI was utilized to analyze theoretical concurrency edge cases, verify mathematical feasibility formulas, review POSIX condition variable standards, and assist in refactoring codebase modularity.
