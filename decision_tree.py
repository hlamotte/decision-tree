# ctypes_test.py
import ctypes
import pathlib

def cpp_decision_tree(trainPath, testPath):
    # Load the shared library into ctypes
    libname = pathlib.Path().absolute() / "build/libDecisionTree.dylib"

    c_lib = ctypes.CDLL(libname)
    decisionTree = c_lib.decisionTree
    decisionTree.restype = ctypes.POINTER(ctypes.c_int)
    decisionTree.argtypes = [ctypes.c_char_p, ctypes.c_char_p]


    with open(testPath) as f:
        first_line = f.readline()
    number_predictions = first_line.count(',') + 1
    
    decisionTreeP = decisionTree(trainPath.encode('utf-8'), testPath.encode('utf-8'))

    predictions = [decisionTreeP[i] for i in range(number_predictions)]
    return predictions

if __name__ == "__main__":
    # running lazy tests
    trainPath = "test/resources/train.csv"
    testPath = "test/resources/test.csv"
    predictions = cpp_decision_tree(trainPath, testPath)
    print(predictions)

    trainPath = "test/resources/titanicTrain.csv"
    testPath = "test/resources/titanicTest.csv"
    predictions = cpp_decision_tree(trainPath, testPath)
    print(predictions)