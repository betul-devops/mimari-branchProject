import csv
import matplotlib.pyplot as plt

predictors = []
accuracy = []
miss_rate = []
cpi = []

# CSV oku
with open('results.csv', 'r') as file:
    reader = csv.DictReader(file)

    for row in reader:
        predictors.append(row['Predictor'])
        accuracy.append(float(row['Accuracy']))
        miss_rate.append(float(row['MissRate']))
        cpi.append(float(row['CPI']))

# Accuracy Graph
plt.figure(figsize=(8, 5))
plt.bar(predictors, accuracy)
plt.title("Prediction Accuracy vs Predictor Type")
plt.xlabel("Predictor")
plt.ylabel("Accuracy (%)")
plt.savefig("accuracy_graph.png")

# Miss Rate Graph
plt.figure(figsize=(8, 5))
plt.bar(predictors, miss_rate)
plt.title("Miss Rate vs Predictor Type")
plt.xlabel("Predictor")
plt.ylabel("Miss Rate (%)")
plt.savefig("missrate_graph.png")

# CPI Graph
plt.figure(figsize=(8, 5))
plt.bar(predictors, cpi)
plt.title("Estimated CPI vs Predictor Type")
plt.xlabel("Predictor")
plt.ylabel("CPI")
plt.savefig("cpi_graph.png")

print("Graphlar oluşturuldu.")