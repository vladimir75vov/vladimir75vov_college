using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Calculator
{
    public class Calculator
    {
        public static double calculate(string doubleOneStr, string action, string doubleTwoStr)
        {
            double doubleOne;
            double doubleTwo;
            try
            {
                if (doubleOneStr.Any(c => char.IsLetter(c)))
                    throw new Exception("Первый символ False");
                else
                    doubleOne = Convert.ToDouble(doubleOneStr);
            }
            catch (Exception e) //отлов исключения
            {
                Console.WriteLine($"Ошибка: {e.Message}");
                return 0;
            }

            try
            {
                if (doubleTwoStr.Any(c => char.IsLetter(c)))
                    throw new Exception("Второй символ False");
                else
                    doubleTwo = Convert.ToDouble(doubleTwoStr);
            }
            catch (Exception e) //отлов исключения
            {
                Console.WriteLine($"Ошибка: {e.Message}");
                return 0;
            }

            if (action == "+")
                return (double)doubleOne + doubleTwo;

            if (action == "-")
                return (double)doubleOne - doubleTwo;

            if (action == "*")
                return (double)doubleOne * doubleTwo;

            if (action == "/")
                return (double)doubleOne / doubleTwo;

            if (action == "%")
                return (double)doubleOne % doubleTwo;

            try
            {
                throw new Exception("Нету оператора");
            }
            catch (Exception e) //отлов исключения
            {
                Console.WriteLine($"Ошибка: {e.Message}");
                return 0;
            }
        }
        public double Calculate(string doubleOne, string action, string doubleTwo)
        {
            return calculate(doubleOne, action, doubleTwo);
        }
    }
}
