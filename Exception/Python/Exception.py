import sys

try:
    number1 = int(input())
    number2 = int(input())
    print(number1/number2)
except ValueError:
    print("ValueError")
except ZeroDivisionError:
    print("ValueError")
except Exception:
    print("Exception")
print(sys.getsizeof(int))
print(sys.getsizeof(float))