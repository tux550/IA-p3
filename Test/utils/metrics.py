import numpy as np
from sklearn.metrics import precision_score, recall_score, f1_score, balanced_accuracy_score, confusion_matrix
from .run import run_train_test_save, run_load_test
from .np import numpy_from_file

def get_metrics(parameters_dict, save_prefix_path, display_cm=True):
    # Create parameters dictionary
    parameters_dict["filename_export_model"]="export/"+save_prefix_path+".mdl"
    # Y PRED
    y_pred = run_train_test_save(parameters_dict)
    y_pred = np.argmax(y_pred, axis=1)
    # Y TRUE
    y_true = numpy_from_file(parameters_dict["filename_y_test"])
    y_true = np.argmax(y_true, axis=1)
    # Generate Matrix
    if display_cm:
        cm = confusion_matrix(y_true, y_pred)
        print("CONFUSION MATRIX")
        print(cm)

    metrics = {
        "Balanced Accuracy" : balanced_accuracy_score(y_true, y_pred),
        "Precision" : precision_score(y_true, y_pred, average="weighted"),
        "Recall" : recall_score(y_true, y_pred, average="weighted"),
        "F1 Score" : f1_score(y_true, y_pred, average="weighted"),
    }

    return metrics

def get_load_metrics(parameters_dict, display_cm=True):
    # Y PRED
    y_pred = run_load_test(parameters_dict)
    y_pred = np.argmax(y_pred, axis=1)
    # Y TRUE
    y_true = numpy_from_file(parameters_dict["filename_y_test"])
    y_true = np.argmax(y_true, axis=1)
    # Generate Matrix
    if display_cm:
        cm = confusion_matrix(y_true, y_pred)
        print("CONFUSION MATRIX")
        print(cm)

    metrics = {
        "Balanced Accuracy" : balanced_accuracy_score(y_true, y_pred),
        "Precision" : precision_score(y_true, y_pred, average="weighted"),
        "Recall" : recall_score(y_true, y_pred, average="weighted"),
        "F1 Score" : f1_score(y_true, y_pred, average="weighted"),
    }

    return metrics