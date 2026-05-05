import random

print("Generating synthetic trace.txt file...")

with open("trace.txt", "w") as f:
    # Simulation of a main program running 10,000 times
    for i in range(10000):
        
        # Address 1: 100% Taken (e.g., an always-executed function call)
        f.write(" 0x400100,1\n")
        
        # Address 2: Inner loop model (9 times Taken, 1 time Not Taken)
        for j in range(10):
            if j < 9:
                f.write(" 0x400200,1\n") # Loop continues (Taken)
            else:
                f.write(" 0x400200,0\n") # Loop exits (Not Taken)
                
            # Address 3: A complex IF block with a 75% probability of being Taken
            if random.random() < 0.75:
                f.write(" 0x400300,1\n") # IF condition met (Taken)
            else:
                f.write(" 0x400300,0\n") # IF condition fails (Not Taken)

print("Successfully generated! Total: 210,000 branch lines.")
