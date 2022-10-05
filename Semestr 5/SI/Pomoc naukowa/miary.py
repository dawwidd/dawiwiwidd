i = float(input('Ilosc danych: '))
TP = float(input('True positive (TP): '))
FP = float(input('False positive (FP): '))
FN = float(input('False negative (FN): '))
TN = float(input('True negative (TN): '))


precision = TP / (TP + FP)
recall = TP / (TP + FN)
accuracy = (TP + TN) / (TP + TN + FP + FN)

print(f'Precision: {round(precision, 2)} \nRecall: {round(recall, 2)}\nAccuracy {round(accuracy, 2)} \n')

# Ziczek Zuziczek
