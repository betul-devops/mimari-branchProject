import random

# A script to convert Valgrind memory trace into a branch trace format (T/N)
try:
    with open('valgrind_output.txt', 'r') as f_in, open('random_trace.txt', 'w') as f_out:
        for line in f_in:
            if line.startswith('I '): # Catch only instruction fetches
                # Extract the address (e.g., I  0488f549,2 -> 0488f549)
                addr = line.split(',')[0].split()[1]
                
                # Assume 15% of instructions are branches for a realistic simulation
                if random.random() < 0.15: 
                    # Randomly assign Taken (T) or Not Taken (N)
                    outcome = 'T' if random.random() < 0.6 else 'N'
                    f_out.write(f"0x{addr} {outcome}\n")
                    
    print("Success! random_trace.txt has been generated and is ready for the simulator.")
except FileNotFoundError:
    print("Error: You need to run valgrind first to create valgrind_output.txt!")
